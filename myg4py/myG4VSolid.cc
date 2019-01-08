#include <boost/python.hpp>
#include "G4Version.hh"
#include "G4VSolid.hh"

using namespace boost::python;

// ====================================================================
// module definition
// ====================================================================
void export_G4VSolid()
 {
   class_<G4VSolid, G4VSolid*, boost::noncopyable>
     ("G4VSolid", "solid class", no_init)
     // ---
     .def("GetName",        &G4VSolid::GetName)
     .def("SetName",        &G4VSolid::SetName)
     .def("DumpInfo",       &G4VSolid::DumpInfo)

     .def("GetCubicVolume",    &G4VSolid::GetCubicVolume)
#if G4VERSION_NUMBER >=820
     .def("GetSurfaceArea",    &G4VSolid::GetSurfaceArea)
#endif
#if G4VERSION_NUMBER >=800
     .def("GetPointOnSurface", &G4VSolid::GetPointOnSurface)
#endif
     // operators
     .def(self == self)
     ;
 }
