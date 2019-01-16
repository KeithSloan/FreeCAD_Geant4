#include <boost/python.hpp>
#include "G4Version.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4VFacet.hh"

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
     .def("AddFacet",       &G4TessellatedSolid::AddFacet)
     .def("GetName",        &G4TessellatedSolid::GetName)
     .def("SetName",        &G4TessellatedSolid::SetName)
     .def("DumpInfo",       &G4TessellatedSolid::DumpInfo)

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
   
   class_<G4TriangularFacet, G4TriangularFacet*, boost::noncopyable>
     ("G4TriangularFacet", "solid class")
     // ---
     .def("SetVertex",      &G4TriangularFacet::SetVertex)

     // operators
     .def(self == self)
     ;

   class_<G4VFacet, G4VFacet*, boost::noncopyable>
     ("G4TVFacet", "solid class", no_init)
     // ---
     .def("SetVertex",      &G4VFacet::SetVertex)

     // operators
     .def(self == self)
     ;
 }
