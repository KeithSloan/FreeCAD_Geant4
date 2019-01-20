//***************************************************************************
//*                                                                         *
//*   Copyright (c) 2019 Keith Sloan <keith@sloan-home.co.uk>               *
//*                                                                         *
//*   This program is free software; you can redistribute it and/or modify  *
//*   it under the terms of the GNU Lesser General Public License (LGPL)    *
//*   as published by the Free Software Foundation; either version 2 of     *
//*   the License, or (at your option) any later version.                   *
//*   for detail see the LICENCE text file.                                 *
//*                                                                         *
//*   This program is distributed in the hope that it will be useful,       *
//*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
//*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
//*   GNU Library General Public License for more details.                  *
//*                                                                         *
//*   You should have received a copy of the GNU Library General Public     *
//*   License along with this program; if not, write to the Free Software   *
//*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
//*   USA                                                                   *
//*                                                                         *
//*   Acknowledgements :                                                    *
//*                                                                         *
//***************************************************************************
#ifndef FC_G4_LIB_H
#define FC_G4_LIB_H

// G4 Includes
#include <G4TriangularFacet.hh>

// FreeCAD Includes
#include <FCConfig.h>
#include <Vector3D.h>
#include <Base/Matrix.h>
//#include <Gui/Workbench.h>

//#include <Base/Placement.h>
//#include <Base/Rotation.h

namespace FC_G4_LIB {

/**
 * @author Keith Sloan
 */

//class G4TriangularFacet MyFC_2_G4TriangularFace
class MyFC_2_G4TriangularFace
{

public:
      MyFC_2_G4TriangularFace();
      G4TriangularFace init(&Vector3 X,  &Vector3 Y, &Vector3 Z);
//      Virtual ~MyFC_2_G4TriangularFace();
      G4TriangularFacet& returnFacet() {return facet;}

private:
      G4TriangularFacet facet;
};

//class G4TriangularFacet MyG4_2_FC_Placement
class MyG4_2_FC_Placement
{

public:
      MyG4_2_FC_Placement();
//     Virtual ~MyG4_2_FC_Placement();
      &Matrix4D returnMatrix() {return matrix;}

private:
     Matrix4D matrix;
};

} // namespace FC_G4_LIB

class MyPlacement
{
public:
        MyPlacement();

protected:
};

#endif

