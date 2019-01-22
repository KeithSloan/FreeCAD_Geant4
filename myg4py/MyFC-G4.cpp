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
#include "MyFC-G4.hh"

class MyG4TriangularFacet : public G4TriangularFacet
{

public:
      MyG4TriangularFacet(Base::Vector3f& v0,
                          Base::Vector3f& v1,
                          Base::Vector3f& v2);
//      Virtual ~MyFC_2_G4TriangularFace();

private:
};


MyG4TriangularFacet::MyG4TriangularFacet(Base::Vector3f &v0,
                          Base::Vector3f& v1,
                          Base::Vector3f& v2)
                                         
{
G4TriangularFacet(G4ThreeVector(v0.x,v0.y,v0.z),
                  G4ThreeVector(v1.x,v1.y,v1.z),
                  G4ThreeVector(v2.x,v2.y,v2.z),
              ABSOLUTE);
}
