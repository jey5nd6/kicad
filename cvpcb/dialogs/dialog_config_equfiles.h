/**
 * @file dialog_config_equfiles.h
 */

/*
 * This program source code file is part of KICAD, a free EDA CAD application.
 *
 * Copyright (C) 2010-2015 Jean-Pierre Charras jp.charras at wanadoo.fr
 * Copyright (C) 1992-2021 Kicad Developers, see AUTHORS.TXT for contributors.
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

#ifndef _DIALOG_CONFIG_EQUFILES_H_
#define _DIALOG_CONFIG_EQUFILES_H_

#include <dialog_config_equfiles_base.h>

class DIALOG_CONFIG_EQUFILES : public DIALOG_CONFIG_EQUFILES_BASE
{
public:
    DIALOG_CONFIG_EQUFILES( CVPCB_MAINFRAME* parent );
    ~DIALOG_CONFIG_EQUFILES() {};

private:
    void Init();

    // Virtual event handlers
    void OnCloseWindow( wxCloseEvent& event ) override;
    void OnOkClick( wxCommandEvent& event ) override;
    void OnAddFiles( wxCommandEvent& event ) override;
    void OnEditEquFile( wxCommandEvent& event ) override;
    void OnRemoveFiles( wxCommandEvent& event ) override;
    void OnButtonMoveUp( wxCommandEvent& event ) override;
    void OnButtonMoveDown( wxCommandEvent& event ) override;

    int getEnvVarCount()                // Get the number of rows in env var table
    {
        return m_gridEnvVars->GetTable()->GetRowsCount();
    }

    bool isPathRelativeAllowed()
    {
        return m_rbPathOptionChoice->GetSelection() == 1;
    }

    CVPCB_MAINFRAME* m_Parent;
    wxString         m_UserLibDirBufferImg;

    bool m_ListChanged;
};

#endif      // _DIALOG_CONFIG_EQUFILES_H_
