#include <boost/python.hpp>
#include "G4Version.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4VFacet.hh"
#include "G4Polyhedron.hh"
#include "G4AffineTransform.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(myg4py)

// ====================================================================
// module definition
// ====================================================================
 {
   class_<G4TessellatedSolid, G4TessellatedSolid*, boost::noncopyable>
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

   class_<G4VFacet, G4VFacet*, boost::noncopyable>
     ("G4VFacet", "solid class", no_init)
     // ---
     .def("SetVertex",      &G4TriangularFacet::SetVertex)

     // operators
     .def(self == self)
     ;
   
   class_<G4TriangularFacet, bases<G4VFacet> , boost::noncopyable>
     ("G4TriangularFacet", "solid class")
     // ---
     .def("SetVertex",      &G4TriangularFacet::SetVertex)

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
 }
