/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2015-2016 Mario Luzeiro <mrluzeiro@ua.pt>
 * Copyright (C) 1992-2020 KiCad Developers, see AUTHORS.txt for contributors.
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

/**
 * @file  cdummyblock.h
 */

#ifndef _DUMMY_BLOCK_H_
#define _DUMMY_BLOCK_H_

#include "cobject.h"

/**
 * A dummy block is used to fill the polygons. It will only will be intercepted
 * from top or from bottom.
 */
class DUMMY_BLOCK : public OBJECT_3D
{
public:
    explicit DUMMY_BLOCK( const BBOX_3D& aBBox );

    void SetColor( SFVEC3F aObjColor ) { m_diffusecolor = aObjColor; }

    bool Intersect( const RAY& aRay, HITINFO& aHitInfo ) const override;
    bool IntersectP(const RAY& aRay , float aMaxDistance ) const override;
    bool Intersects( const BBOX_3D& aBBox ) const override;
    SFVEC3F GetDiffuseColor( const HITINFO& aHitInfo ) const override;

private:
    SFVEC3F m_diffusecolor;
};


#endif // _DUMMY_BLOCK_H_
