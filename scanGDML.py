print "Starting"
from Geant4 import *
import Geant4.G4gdml
import inspect
import pprint
print "Module imported"


class switch(object):
    value = None
    def __new__(class_, value):
        class_.value = value
        return True

def case(*args):
    return any((arg == switch.value for arg in args))

def createBox(solid) :
    print("Create Box : \n")

def browsePhysicalVolume(LV):
    num = LV.GetNoDaughters()
    print("Logical Volume  : "+str(LV.GetName())+'\n')
    print("Num Daughters : "+str(num)+'\n')
    for i in range(1,num,1) :
       pv  = LV.GetDaughter(i)
       lvd = pv.GetLogicalVolume()
       if ( lvd.GetNoDaughters() == 0) :
          print("Logical Volume  : "+str(lvd.GetName())+'\n')

          print("Parse Logical Volume \n")
#          print dir(lvd)
          solid = lvd.GetSolid()
          while switch(type(solid)) :
              if case(Geant4.G4geometry.G4Box):
		 createBox(solid)
		 break

	      print "Solid type : "+str(type(solid))+" Not yet supported"
              break
          
#          G4type = solid.GetEntityType()
#          print("Solid : "+str(G4String(G4type))+" : "+entity+"\n")


def main() :
    print "Main"
    gdml_parser = G4GDMLParser()
    gdml_parser.Read(G4String(str(filename)))

#    Reader = gdml_parser.GetReader()

#    WV = gdml_parser.GetWorldVolume(G4String(str("Default")))
    WV = gdml_parser.GetWorldVolume()
    LV = WV.GetLogicalVolume()

    num = browsePhysicalVolume(LV)

filename = "/home/keith/GDML-Test-Files/test4.gdml"
main()

