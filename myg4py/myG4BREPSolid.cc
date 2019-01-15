#include <boost/python.hpp>
#include "G4Version.hh"
#include "G4BREPSolid.hh"

using namespace boost::python;

//BOOST_PYTHON_MODULE(myg4py)
BOOST_PYTHON_MODULE(myG4VSolid)

// ====================================================================
// module definition
// ====================================================================
 {
   class_<G4BREPSolid, G4BREPSolid*, boost::noncopyable>
     ("G4BREPSolid", "BREP solid class", no_init)
     // ---
     //.def("GetName",        &G4VSolid::GetName)
     //.def("SetName",        &G4VSolid::SetName)
     //.def("DumpInfo",       &G4VSolid::DumpInfo)

     //.def("GetCubicVolume",    &G4VSolid::GetCubicVolume)
#if G4VERSION_NUMBER >=820
     //.def("GetSurfaceArea",    &G4VSolid::GetSurfaceArea)
#endif
#if G4VERSION_NUMBER >=800
     //.def("GetPointOnSurface", &G4VSolid::GetPointOnSurface)
#endif
     // operators
     //.def(self == self)
     ;
 }
