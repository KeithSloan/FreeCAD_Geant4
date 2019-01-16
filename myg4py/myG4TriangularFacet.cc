#include <boost/python.hpp>
#include "G4Version.hh"
#include "G4TriangularFacet.hh"

using namespace boost::python;

BOOST_PYTHON_MODULE(myg4py)

// ====================================================================
// module definition
// ====================================================================
 {
   class_<G4TriangularFacet, G4TriangularFacet*, boost::noncopyable>
//     ("G4TriangularFacet", "solid class", no_init)
     ("G4TriangularFacet", "solid class")
     // ---
     .def("SetVertex",      &G4TriangularFacet::SetVertex)

     // operators
     .def(self == self)
     ;
 }
