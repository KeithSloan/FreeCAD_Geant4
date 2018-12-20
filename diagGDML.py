print "Starting"
from Geant4 import *
import Geant4.G4gdml
import inspect
import pprint
print "Module imported"

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
          print dir(lvd)
          solid = lvd.GetSolid()
          print "solid\n"
  	  if type(solid) == Geant4.G4geometry.G4Box :
		print "FOUND"
          print repr(solid)
          print "++inspect++"
          print inspect.getmembers(solid)
          print "==vars=="
          print(vars(solid))
          print "--dir--"
          print dir(solid)
          print "Name : "+str(solid.GetName())+"\n"
          solid.DumpInfo()
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

