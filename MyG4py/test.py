import sys
sys.path.append("/usr/lib/freecad/lib")

import Geant4
import FreeCAD

from Geant4 import G4ThreeVector

#print dir(Geant4)
b = FreeCAD.Vector(0,1,2)
v=G4ThreeVector(b[0],b[1],b[2])
v=G4ThreeVector(0.,1.,2.)
print v
