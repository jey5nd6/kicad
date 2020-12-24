/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013-2017 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 * Copyright (C) 2017-2020 KiCad Developers, see CHANGELOG.TXT for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef PCB_SELECTION_TOOL_H
#define PCB_SELECTION_TOOL_H

#include <memory>

#include <math/vector2d.h>
#include <project/board_project_settings.h>
#include <tool/action_menu.h>
#include <tool/tool_menu.h>
#include <tools/pcb_selection_conditions.h>
#include <tools/pcb_tool_base.h>
#include <tools/pcb_selection.h>

class PCB_BASE_FRAME;
class BOARD_ITEM;
class GENERAL_COLLECTOR;

namespace KIGFX
{
    class GAL;
}


typedef void (*CLIENT_SELECTION_FILTER)( const VECTOR2I&, GENERAL_COLLECTOR&, PCB_SELECTION_TOOL* );


/**
 * PCB_SELECTION_TOOL
 *
 * Our sample selection tool: currently supports:
 * - pick single objects (click LMB)
 * - add objects to existing selection (Shift+LMB)
 * - draw selection box (drag LMB)
 * - handles FOOTPRINTs properly (i.e. selects either FOOTPRINT or its PADs, TEXTs, etc.)
 * - takes into account high-contrast & layer visibility settings
 * - invokes InteractiveEdit tool when user starts to drag selected items
 */
class PCB_SELECTION_TOOL : public PCB_TOOL_BASE
{
public:
    PCB_SELECTION_TOOL();
    ~PCB_SELECTION_TOOL();

    /// @copydoc TOOL_BASE::Init()
    bool Init() override;

    /// @copydoc TOOL_BASE::Reset()
    void Reset( RESET_REASON aReason ) override;

    /**
     * Function Main()
     *
     * The main loop.
     */
    int Main( const TOOL_EVENT& aEvent );

    /**
     * Function GetSelection()
     *
     * Returns the set of currently selected items.
     */
    PCB_SELECTION& GetSelection();

    /**
     * Function RequestSelection()
     *
     * Returns the current selection set, filtered according to aFlags and aClientFilter.
     * If the set is empty, performs the legacy-style hover selection.
     *
     * @param aConfirmLockedItems if true the user will be prompted if they want to drop locked
     *                            items from the selection or override the locks
     */
    PCB_SELECTION& RequestSelection( CLIENT_SELECTION_FILTER aClientFilter,
                                     bool aConfirmLockedItems = false );

    ///> Select a single item under cursor event handler.
    int CursorSelection( const TOOL_EVENT& aEvent );

    ///> Clear current selection event handler.
    int ClearSelection( const TOOL_EVENT& aEvent );
    void ClearSelection( bool aQuietMode = false );

    ///> Item selection event handler.
    int SelectItem( const TOOL_EVENT& aEvent );
    void AddItemToSel( BOARD_ITEM* aItem, bool aQuietMode = false );

    ///> Select all items on the board
    int SelectAll( const TOOL_EVENT& aEvent );

    ///> Multiple item selection event handler
    int SelectItems( const TOOL_EVENT& aEvent );

    ///> Item unselection event handler.
    int UnselectItem( const TOOL_EVENT& aEvent );
    void RemoveItemFromSel( BOARD_ITEM* aItem, bool aQuietMode = false );

    ///> Multiple item unselection event handler
    int UnselectItems( const TOOL_EVENT& aEvent );

    void BrightenItem( BOARD_ITEM* aItem );
    void UnbrightenItem( BOARD_ITEM* aItem );

    /**
     * Function select()
     * Takes necessary action mark an item as selected.
     *
     * @param aItem is an item to be selected.
     */
    void select( BOARD_ITEM* aItem );

    /**
     * Function selectable()
     * Checks conditions for an item to be selected.
     *
     * @return True if the item fulfills conditions to be selected.
     */
    bool Selectable( const BOARD_ITEM* aItem, bool checkVisibilityOnly = false ) const;

    /**
     * Function guessSelectionCandidates()
     * Tries to guess best selection candidates in case multiple items are clicked, by doing
     * some brain-dead heuristics.
     * @param aCollector is the collector that has a list of items to be queried.
     * @param aWhere is the selection point to consider
     */
    void GuessSelectionCandidates( GENERAL_COLLECTOR& aCollector, const VECTOR2I& aWhere ) const;

    /**
     * Function SelectionMenu()
     * Shows a popup menu to trim the COLLECTOR passed as aEvent's parameter down to a single
     * item.
     *
     * NOTE: this routine DOES NOT modify the selection.
     */
    int SelectionMenu( const TOOL_EVENT& aEvent );

    /**
     * Rebuilds the selection from the EDA_ITEMs' selection flags.  Commonly called after
     * rolling back an undo state to make sure there aren't any stale pointers.
     */
    void RebuildSelection();

    SELECTION_FILTER_OPTIONS& GetFilter()
    {
        return m_filter;
    }

    ///> Sets up handlers for various events.
    void setTransitions() override;

    ///> Zooms the screen to center and fit the current selection.
    void zoomFitSelection();

    BOARD* GetBoard() const
    {
        return board();
    }

    void EnterGroup();

    /**
     * Leave the currently entered group.
     *
     * @param aSelectGroup when true will select the group after leaving
     */
    void ExitGroup( bool aSelectGroup = false );

    void FilterCollectorForGroups( GENERAL_COLLECTOR& aCollector ) const;

    PCB_GROUP* GetEnteredGroup() { return m_enteredGroup; }

    ///> Applies the SELECTION_FILTER_OPTIONS to a collection of items
    void FilterCollectedItems( GENERAL_COLLECTOR& aCollector );

private:

    /**
     * Function selectPoint()
     * Selects an item pointed by the parameter aWhere. If there is more than one item at that
     * place, there is a menu displayed that allows one to choose the item.
     *
     * @param aWhere is the place where the item should be selected.
     * @param aOnDrag indicates whether a drag operation is being performed.
     * @param aSelectionCancelledFlag allows the function to inform its caller that a selection
     * was cancelled (for instance, by clicking outside of the disambiguation menu).
     * @param aClientFilter allows the client to perform tool- or action-specific filtering.
     * @return True if an item was selected, false otherwise.
     */
    bool selectPoint( const VECTOR2I& aWhere, bool aOnDrag = false,
                      bool* aSelectionCancelledFlag = NULL,
                      CLIENT_SELECTION_FILTER aClientFilter = NULL );

    /**
     * Function selectCursor()
     * Selects an item under the cursor unless there is something already selected or aSelectAlways
     * is true.
     * @param aForceSelect forces to select an item even if there is an item already selected.
     * @param aClientFilter allows the client to perform tool- or action-specific filtering.
     * @return true if eventually there is an item selected, false otherwise.
     */
    bool selectCursor( bool aForceSelect = false,
                       CLIENT_SELECTION_FILTER aClientFilter = NULL );

    /**
     * Function selectMultiple()
     * Handles drawing a selection box that allows one to select many items at
     * the same time.
     *
     * @return true if the function was cancelled (i.e. CancelEvent was received).
     */
    bool selectMultiple();

    /**
     * Allows the selection of a single item from a list via pop-up menu.  The items are
     * highlighted on the canvas when hovered in the menu.  The collector is trimmed to
     * the picked item.
     * @param aTitle (optional) Allows the menu to be titled (ie: "Clarify Selection").
     * @return true if an item was picked
     */
    bool doSelectionMenu( GENERAL_COLLECTOR* aItems, const wxString& aTitle );

    /**
     * Expands the current track selection to the next boundary (junctions, pads, or all)
     */
    int expandConnection( const TOOL_EVENT& aEvent );

    /**
     * Selects all copper connections belonging to the same net(s) as the
     * items in the selection
     */
    int selectNet( const TOOL_EVENT& aEvent );

    enum STOP_CONDITION
    {
        /** Stop at any place where more than two traces meet
         *
         * Because vias are also traces, this makes selection stop at a
         * via if there is a trace on another layer as well, but a via
         * with only one connection will be selected. */
        STOP_AT_JUNCTION,
        /** Stop when reaching a pad */
        STOP_AT_PAD,
        /** Select the entire net */
        STOP_NEVER
    };

    /**
     * Selects connecteed tracks and vias.
     *
     * @param aStopCondition where to stop selecting more items
     */
    void selectConnectedTracks( BOARD_CONNECTED_ITEM& aSourceItem, STOP_CONDITION aStopCondition );

    /**
     * Selects all items with the given net code
     * @param aNetCode is the target net to select
     * @param aSelect is true to add the items to the selection, false to remove them (deselect)
     */
    void selectAllItemsOnNet( int aNetCode, bool aSelect = true );

    /**
     * Selects all items with the given sheet timestamp/UUID name
     * (the sheet path)
     * The path of the root sheet is "/"
     */
    void selectAllItemsOnSheet( wxString& aSheetPath );

    ///> Selects all footprints belonging to same sheet, from Eeschema,
    ///> using crossprobing
    int selectSheetContents( const TOOL_EVENT& aEvent );

    ///> Selects all footprints belonging to same hierarchical sheet
    ///> as the selected footprint (same sheet path).
    int selectSameSheet( const TOOL_EVENT& aEvent );

    ///> Find dialog callback.
    void findCallback( BOARD_ITEM* aItem );

    ///> Find an item.
    int find( const TOOL_EVENT& aEvent );

    ///> Invoke filter dialog and modify current selection
    int filterSelection( const TOOL_EVENT& aEvent );

    ///> Returns true if the given item passes the current SELECTION_FILTER_OPTIONS
    bool itemPassesFilter( BOARD_ITEM* aItem );

    /**
     * Function pickSmallestComponent()
     * Allows one to find the smallest (in terms of bounding box area) item from the list.
     *
     * @param aCollector containes the list of items.
     */
    BOARD_ITEM* pickSmallestComponent( GENERAL_COLLECTOR* aCollector );

    /**
     * Function unselect()
     * Takes necessary action mark an item as unselected.
     *
     * @param aItem is an item to be unselected.
     */
    void unselect( BOARD_ITEM* aItem );

    /**
     * Function highlight()
     * Highlights the item visually.
     * @param aItem is an item to be be highlighted.
     * @param aHighlightMode should be either SELECTED or BRIGHTENED
     * @param aGroup is the group to add the item to in the BRIGHTENED mode.
     */
    void highlight( BOARD_ITEM* aItem, int aHighlightMode, PCB_SELECTION* aGroup = nullptr );

    /**
     * Function unhighlight()
     * Unhighlights the item visually.
     * @param aItem is an item to be be highlighted.
     * @param aHighlightMode should be either SELECTED or BRIGHTENED
     * @param aGroup is the group to remove the item from.
     */
    void unhighlight( BOARD_ITEM* aItem, int aHighlightMode, PCB_SELECTION* aGroup = nullptr );

    /**
     * Function selectionContains()
     * @return True if the given point is contained in any of selected items' bounding box.
     */
    bool selectionContains( const VECTOR2I& aPoint ) const;

    int hitTestDistance( const wxPoint& aWhere, BOARD_ITEM* aItem, int aMaxDistance ) const;

    /**
     * Event handler to update the selection VIEW_ITEM.
     */
    int updateSelection( const TOOL_EVENT& aEvent );

    /**
     * Pass the selection to a conditional menu for updating.
     */
    int UpdateMenu( const TOOL_EVENT& aEvent );

    const GENERAL_COLLECTORS_GUIDE getCollectorsGuide() const;

private:
    void highlightInternal( BOARD_ITEM* aItem, int aHighlightMode,
                            PCB_SELECTION* aSelectionViewGroup, bool isChild);

    void unhighlightInternal( BOARD_ITEM* aItem, int aHighlightMode,
                              PCB_SELECTION* aSelectionViewGroup, bool isChild);

    PCB_BASE_FRAME*  m_frame;     // Pointer to the parent frame
    PCB_SELECTION    m_selection; // Current state of selection

    SELECTION_FILTER_OPTIONS m_filter;

    bool m_additive;              // Items should be added to selection (instead of replacing)
    bool m_subtractive;           // Items should be removed from selection
    bool m_exclusive_or;          // Items' selection state should be toggled
    bool m_multiple;              // Multiple selection mode is active
    bool m_skip_heuristics;       // Heuristics are not allowed when choosing item under cursor

    PCB_GROUP*        m_enteredGroup;          // If non-null, selections are limited to
                                               // members of this group
    KIGFX::VIEW_GROUP m_enteredGroupOverlay;   // Overlay for the entered group's frame.


    /// Private state (opaque pointer/compilation firewall)
    class PRIV;
    std::unique_ptr<PRIV> m_priv;
};

#endif /* PCB_SELECTION_TOOL_H */