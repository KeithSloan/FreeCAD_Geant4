#include "G4GDMLWriteSetup.hh"

G4VphysicalVolume* g4wv = G4TransportationManager:: 
GetTransportationManager()->GetNavigatorForTracking() 
->GetWorldVolume(); 

G4GDMLWriter g4writer("/path/to/gdml.xsd", "/path/to/output.gdml"); 

g4writer.DumpGeometryInfo(g4wv);
