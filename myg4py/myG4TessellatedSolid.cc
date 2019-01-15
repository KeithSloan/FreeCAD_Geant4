#include <boost/python.hpp>
#include "G4Version.hh"
#include "G4TessellatedSolid.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(myg4py)
//BOOST_PYTHON_MODULE(myG4VSolid)

// ====================================================================
// module definition
// ====================================================================
 {
   class_<G4TessellatedSolid, G4TessellatedSolid*, boost::noncopyable>
     ("G4TessellatedSolid", "solid class", no_init)
     // ---
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
 }
