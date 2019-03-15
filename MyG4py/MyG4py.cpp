// C++ includes
#include <iostream>
#include <boost/python.hpp>
// CLHEP includes
#include "CLHEP/Vector/ThreeVector.h"
// Geant4 includes
#include "G4Version.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4VFacet.hh"
#include "G4Polyhedron.hh"
#include "G4AffineTransform.hh"
// FreeCAD includes
#include "Base/Vector3D.h"

using namespace std;
using namespace boost::python;

// ====================================================================
// Function definitions Class then Function
// ====================================================================
class MyG4TriangularFacet : public G4TriangularFacet
{

public:
     MyG4TriangularFacet();

     MyG4TriangularFacet(Base::Vector3d v0,
                         Base::Vector3d v1,
                         Base::Vector3d v2);

     MyG4TriangularFacet(const G4ThreeVector & v0,
                         const G4ThreeVector & v1,
                         const G4ThreeVector & v2);

//      Virtual ~MyFC_2_G4TriangularFace();

private:
};


// Constructors
MyG4TriangularFacet::MyG4TriangularFacet() {cout << "Default";}

MyG4TriangularFacet::MyG4TriangularFacet(Base::Vector3d v0,
                          Base::Vector3d v1,
                          Base::Vector3d v2)

{
G4cout << "Facet Constructor FreeCAD : ";
G4TriangularFacet(G4ThreeVector(v0.x,v0.y,v0.z),
                  G4ThreeVector(v1.x,v1.y,v1.z),
                  G4ThreeVector(v2.x,v2.y,v2.z),
              ABSOLUTE);
}

MyG4TriangularFacet::MyG4TriangularFacet(const G4ThreeVector &v0,
                        const G4ThreeVector &v1,
                        const G4ThreeVector &v2)

{
G4cout << "Facet Constructor G4 : " << v0 << " : " << v1 << " : " << v2;
// Not sure why the following line does not work
//G4TriangularFacet(v0,v1,v2,ABSOLUTE);
// Try the long way
G4TriangularFacet facet;
facet.SetVertex(0,v0);
facet.SetVertex(1,v1);
facet.SetVertex(2,v2);
}

//MyG4TriangularFacet::MyG4TriangularFacet(CLHEP::HepVector& v0,
//                        CLHEP::HepVector& v1,
//                        CLHEP::HepVector& v2)

//{
//G4TriangularFacet(v0,v1,v2,ABSOLUTE);
//}


// ====================================================================
// module definition
// ====================================================================
BOOST_PYTHON_MODULE(MyG4py)
{
   class_<G4VFacet, G4VFacet*, boost::noncopyable>
     ("G4VFacet", "solid class", no_init)
     // ---
     .def("SetVertex",      &G4TriangularFacet::SetVertex)

     // operators
     .def(self == self)
     ;

    class_<G4TessellatedSolid, bases<G4VSolid> , boost::noncopyable>
//    class_<G4TessellatedSolid, G4TessellatedSolid* , boost::noncopyable>
//     ("G4TessellatedSolid", "solid class", no_init)
     ("G4TessellatedSolid", "solid class")
     // ---
     .def("AddFacet",            &G4TessellatedSolid::AddFacet)
     .def("GetNumberOfFacets",   &G4TessellatedSolid::GetNumberOfFacets)
     .def("SetSolidClosed",      &G4TessellatedSolid::SetSolidClosed)
     // Does not compile clean - depreciated ??
     //.def("CreatePolyhedron",    &G4TessellatedSolid::CreatePolyhedron) 
     // Following appear to be depreciated
     //.def("CreateNURBS",         &G4TessellatedSolid::CreateNURBS) 


     .def("GetCubicVolume",    &G4TessellatedSolid::GetCubicVolume)
#if G4VERSION_NUMBER >=820
     .def("GetSurfaceArea",    &G4TessellatedSolid::GetSurfaceArea)
#endif
#if G4VERSION_NUMBER >=800
     .def("GetPointOnSurface", &G4TessellatedSolid::GetPointOnSurface)
#endif
     // operators
     .def(self == self)
     ;

   enum_<G4FacetVertexType>("VertexType")
        .value("A",ABSOLUTE)
        .value("R",RELATIVE)
        ;
   
   class_<G4TriangularFacet, bases<G4VFacet> , boost::noncopyable>
     ("G4TriangularFacet", "solid class")
     .def(init<G4ThreeVector,G4ThreeVector,G4ThreeVector,G4FacetVertexType>())
     // ---
     .def("SetVertex",             &G4TriangularFacet::SetVertex)
     .def("GetArea",               &G4TriangularFacet::GetArea)
     .def("IsDefined",             &G4TriangularFacet::IsDefined)
     .def("GetNumberOfVertices",   &G4TriangularFacet::GetNumberOfVertices)
     .def("GetVertex",             &G4TriangularFacet::GetVertex)

     // operators
     .def(self == self)
     ;

   class_<G4AffineTransform, G4AffineTransform*, boost::noncopyable>
     ("G4AffineTransform", "solid class" )
     // ---
     .def("SetNetRotation",      &G4AffineTransform::SetNetRotation)
     .def("SetNetTranslation",   &G4AffineTransform::SetNetTranslation)

     // operators
     .def(self == self)
     ;

   class_<MyG4TriangularFacet, bases<G4TriangularFacet>> ("MyG4TriangularFacet")
     // Constructors 
     .def(init<Base::Vector3d, Base::Vector3d, Base::Vector3d>())
     .def(init<G4ThreeVector,G4ThreeVector,G4ThreeVector>())

     // operators
     .def(self == self)
     ;

 }
