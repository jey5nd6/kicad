/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2018 Jean-Pierre Charras jp.charras at wanadoo.fr
 * Copyright (C) 1992-2021 KiCad Developers, see AUTHORS.txt for contributors.
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

#ifndef EDA_SHAPE_H
#define EDA_SHAPE_H

#include <eda_units.h>
#include <convert_to_biu.h>
#include <math_for_graphics.h>
#include <trigo.h>
#include <geometry/shape_poly_set.h>
#include <geometry/geometry_utils.h>

class LINE_READER;
class EDA_DRAW_FRAME;
class FOOTPRINT;
class MSG_PANEL_ITEM;


enum class EDA_SHAPE_TYPE : int
{
    SEGMENT = 0,
    RECT,
    ARC,
    CIRCLE,
    POLYGON,
    CURVE,        ///< Bezier
    LAST          ///< marker for list end
};


class EDA_SHAPE
{
public:
    EDA_SHAPE( EDA_SHAPE_TYPE aType, int aDefaultLineWidth );

    // Do not create a copy constructor & operator=.
    // The ones generated by the compiler are adequate.

    ~EDA_SHAPE();

    void SwapShape( EDA_SHAPE* aImage );

    wxString ShowShape() const;

    wxString EDA_SHAPE_TYPE_asString() const;

    void SetFilled( bool aFlag ) { m_filled = aFlag; }

    bool IsFilled() const
    {
        switch( m_shape )
        {
        case EDA_SHAPE_TYPE::RECT:
        case EDA_SHAPE_TYPE::CIRCLE:
        case EDA_SHAPE_TYPE::POLYGON:
            return m_filled;

        case EDA_SHAPE_TYPE::SEGMENT:
        case EDA_SHAPE_TYPE::ARC:
        case EDA_SHAPE_TYPE::CURVE:
            return false;

        case EDA_SHAPE_TYPE::LAST: // Make CLang compiler happy
            return false;
        }

        return false;       // Make GCC compiler happy
    }

    void SetWidth( int aWidth ) { m_width = aWidth; }
    int GetWidth() const        { return m_width; }

    /**
     * Set the angle for arcs, and normalizes it within the range 0 - 360 degrees.
     *
     * @param aAngle is tenths of degrees, but will soon be degrees.
     * @param aUpdateEnd set to true to update also arc end coordinates m_thirdPoint, so must
     *                   be called after setting m_Start and m_End.
     */
    virtual void SetAngle( double aAngle, bool aUpdateEnd = true );
    double GetAngle() const { return m_angle; }

    void SetShape( EDA_SHAPE_TYPE aShape )          { m_shape = aShape; }
    EDA_SHAPE_TYPE GetShape() const                 { return m_shape; }

    void SetBezControl1( const wxPoint& aPoint )    { m_bezierC1 = aPoint; }
    const wxPoint& GetBezControl1() const           { return m_bezierC1; }

    void SetBezControl2( const wxPoint& aPoint )    { m_bezierC2 = aPoint; }
    const wxPoint& GetBezControl2() const           { return m_bezierC2; }

    void SetShapePos( const wxPoint& aPos );
    wxPoint GetShapePos() const;

    /**
     * Return the starting point of the graphic.
     */
    const wxPoint& GetStart() const         { return m_start; }
    int GetStartY()                         { return m_start.y; }
    int GetStartX()                         { return m_start.x; }
    void SetStart( const wxPoint& aStart )  { m_start = aStart; }
    void SetStartY( int y )                 { m_start.y = y; }
    void SetStartX( int x )                 { m_start.x = x; }

    /**
     * Return the ending point of the graphic.
     */
    const wxPoint& GetEnd() const           { return m_end; }
    int GetEndY()                           { return m_end.y; }
    int GetEndX()                           { return m_end.x; }
    void SetEnd( const wxPoint& aEnd )      { m_end = aEnd; }
    void SetEndY( int y )                   { m_end.y = y; }
    void SetEndX( int x )                   { m_end.x = x; }

    /**
     * Function GetThirdPoint
     * returns the third point point of the graphic
     */
    const wxPoint& GetThirdPoint() const           { return m_thirdPoint; }
    int GetThirdPointY()                           { return m_thirdPoint.y; }
    int GetThirdPointX()                           { return m_thirdPoint.x; }
    void SetThirdPoint( const wxPoint& aPoint )    { m_thirdPoint = aPoint; }
    void SetThirdPointY( int y )                   { m_thirdPoint.y = y; }
    void SetThirdPointX( int x )                   { m_thirdPoint.x = x; }

    // Some attributes are read only, since they are derived from m_Start, m_End, and m_Angle.
    // No Set...() function for these attributes.

    wxPoint getCenter() const;
    wxPoint GetArcStart() const      { return m_end; }
    wxPoint GetArcEnd() const;
    wxPoint GetArcMid() const;
    std::vector<wxPoint> GetRectCorners() const;

    /**
     * @return the angle of the starting point of this arc, between 0 and 3600 in 0.1 deg.
     */
    double GetArcAngleStart() const;

    /**
     * @return the angle of the ending point of this arc, between 0 and 3600 in 0.1 deg.
     */
    double GetArcAngleEnd() const;

    /**
     * Return the radius of this item.
     *
     * Has meaning only for arcs and circles.
     */
    int GetRadius() const;

    /**
     * Initialize the start arc point.
     *
     * Can be used for circles to initialize one point of the cicumference.
     */
    void SetArcStart( const wxPoint& aArcStartPoint )
    {
        m_end = aArcStartPoint;
    }

    /**
     * Initialize the end arc point.
     *
     * Can be used for circles to initialize one point of the cicumference.
     */
    void SetArcEnd( const wxPoint& aArcEndPoint )
    {
        m_thirdPoint = aArcEndPoint;
    }

    void SetArcCenter( const wxPoint& aCenterPoint ) { m_start = aCenterPoint; }

    /**
     * Set the three controlling points for an arc.
     *
     * NB: these are NOT what's currently stored, so we have to do some calculations behind
     * the scenes.  However, they are what SHOULD be stored.
     */
    void SetArcGeometry( const wxPoint& aStart, const wxPoint& aMid, const wxPoint& aEnd );

    // Accessors:
    const std::vector<wxPoint>& GetBezierPoints() const { return m_bezierPoints; }

    /**
     * Build and return the list of corners in a std::vector<wxPoint>
     *
     * It must be used only to convert the SHAPE_POLY_SET internal corner buffer to a list of
     * wxPoints, and nothing else, because it duplicates the buffer, that is inefficient to know
     * for instance the corner count.
     */
    const std::vector<wxPoint> BuildPolyPointsList() const;

    /**
     * @return the number of corners of the polygonal shape
     */
    int GetPointCount() const;

    // Accessors to the polygonal shape
    SHAPE_POLY_SET& GetPolyShape() { return m_poly; }
    const SHAPE_POLY_SET& GetPolyShape() const { return m_poly; }

    /**
     * @return true if the polygonal shape is valid (has more than 2 points)
     */
    bool IsPolyShapeValid() const;

    void SetPolyShape( const SHAPE_POLY_SET& aShape ) { m_poly = aShape; }

    void SetBezierPoints( const std::vector<wxPoint>& aPoints ) { m_bezierPoints = aPoints; }

    /**
     * Rebuild the m_BezierPoints vertex list that approximate the Bezier curve
     * by a list of segments.
     *
     * Has meaning only for S_CURVE DRAW_SEGMENT shape.
     *
     * @param aMinSegLen is the min length of segments approximating the bezier. The shape's last
     *                   segment can be shorter.  This parameter avoids having too many very short
     *                   segment in list. Good values are between m_Width/2 and m_Width.
     */
    void RebuildBezierToSegmentsPointsList( int aMinSegLen );

    void SetPolyPoints( const std::vector<wxPoint>& aPoints );

    /**
     * Make a set of SHAPE objects representing the EDA_SHAPE.  Caller owns the objects.
     */
    // fixme: move to shape_compound
    std::vector<SHAPE*> MakeEffectiveShapes() const;

    void ShapeGetMsgPanelInfo( EDA_DRAW_FRAME* aFrame, std::vector<MSG_PANEL_ITEM>& aList );

    /**
     * Return the length of the track using the hypotenuse calculation.
     *
     * @return the length of the track
     */
    double GetLength() const;

    /**
     * Convert the shape to a closed polygon.
     *
     * Used in filling zones calculations.  Circles and arcs are approximated by segments.
     *
     * @param aCornerBuffer is a buffer to store the polygon.
     * @param aClearanceValue is the clearance around the pad.
     * @param aError is the maximum deviation from a true arc.
     * @param aErrorLoc whether any approximation error shoule be placed inside or outside
     * @param ignoreLineWidth is used for edge cut items where the line width is only
     *        for visualization
     */
    void TransformShapeWithClearanceToPolygon( SHAPE_POLY_SET& aCornerBuffer, int aClearanceValue,
                                               int aError, ERROR_LOC aErrorLoc,
                                               bool ignoreLineWidth ) const;

protected:
    void move( const wxPoint& aMoveVector );
    void rotate( const wxPoint& aRotCentre, double aAngle );
    void flip( const wxPoint& aCentre, bool aFlipLeftRight );
    void scale( double aScale );

    // To be implemented by concrete classes
    virtual double getParentOrientation() const = 0;
    virtual wxPoint getParentPosition() const = 0;

    const EDA_RECT getBoundingBox() const;

    void computeArcBBox( EDA_RECT& aBBox ) const;

    bool hitTest( const wxPoint& aPosition, int aAccuracy = 0 ) const;
    bool hitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy = 0 ) const;

    const std::vector<wxPoint> buildBezierToSegmentsPointsList( int aMinSegLen  ) const;

protected:
    EDA_SHAPE_TYPE       m_shape;        // Shape: line, Circle, Arc
    int                  m_width;        // thickness of lines ...
    bool                 m_filled;       // Pretty much what it says on the tin...
    wxPoint              m_start;        // Line start point or Circle and Arc center
    wxPoint              m_end;          // Line end point or circle and arc start point

    wxPoint              m_thirdPoint;   // Used only for Arcs: arc end point
    double               m_angle;        // Used only for Arcs: Arc angle in 1/10 deg

    wxPoint              m_bezierC1;     // Bezier Control Point 1
    wxPoint              m_bezierC2;     // Bezier Control Point 2

    std::vector<wxPoint> m_bezierPoints;
    SHAPE_POLY_SET       m_poly;         // Stores the S_POLYGON shape
};

#endif  // EDA_SHAPE_H
