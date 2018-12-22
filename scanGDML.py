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

def createBox(solid,x,y,z) :
    print("Create Box : x "+str(x)+" y "+str(y)+" z "+str(z))

def createCons() :
    print("Create Cons ")

def createTrap(Z,Y1,X1,X2,X3,X4,TA1,TA2) :
    print("Create Trap : z "+str(Z)+" Y1 "+str(Y1)+" X1 "+str(X1)
	   +" X2 "+str(X2)+" X3 "+str(X3)+" X4 "+str(X4)+" TA1 "
           +str(TA1)+" TA2 "+str(TA2))

def createTubs() :
    print("Create Tubs ")

def parseLogicalVolume(lv) :
    print("Parse Logical Volume "+str(lv.GetName()))
#   print dir(lv)
    solid = lv.GetSolid()
    while switch(type(solid)) :
       if case(Geant4.G4geometry.G4Box):
	      X = solid.GetXHalfLength()*2
              Y = solid.GetYHalfLength()*2
	      Z = solid.GetZHalfLength()*2
 	      createBox(solid,X,Y,Z)
	      break
      
       if case(Geant4.G4geometry.G4Cons):
              createCons()
              break
 
       if case(Geant4.G4geometry.G4Tubs):
              createTubs()
              break

       if case(Geant4.G4geometry.G4Trap):
 	      Z  = solid.GetZHalfLength()*2
              Y1 = solid.GetHalfLength1()*2 
	      X1 = solid.getHalfLength1()*2
	      X2 = solid.getHalfLength2()*2
	      X3 = solid.getHalfLength3()*2
	      X4 = solid.getHalfLength4()*2
	      TA1 = solid.getTanAlpha1()
	      TA2 = solid.getTanAlpha2()
              creatTrap(Z,Y1,X1,X2,X3,X4,TA1,TA2)
	      break

       print "Solid type : "+str(type(solid))+" Not yet supported\n"
       break
          


def browsePhysicalVolume(pv):
    print("\nPhysical Volume  : "+str(pv.GetName()))
    lv = pv.GetLogicalVolume()
    num = lv.GetNoDaughters()
    if num == 0 :
       parseLogicalVolume(lv)
    else :
       print("Num Daughters : "+str(num))
       for i in range(0,num,1) :
           pvd = lv.GetDaughter(i)
           browsePhysicalVolume(pvd)

def main() :
    print "Main"
    gdml_parser = G4GDMLParser()
    gdml_parser.Read(G4String(str(filename)))

#    Reader = gdml_parser.GetReader()

#    wv = gdml_parser.GetWorldVolume(G4String(str("Default")))
    wv = gdml_parser.GetWorldVolume()
    #LV = WV.GetLogicalVolume()

    num = browsePhysicalVolume(wv)

#filename = "/home/keith/GDML-Test-Files/lhcbvelo.gdml"
#filename = "/home/keith/GDML-Test-Files/test4.gdml"
#filename = "/home/keith/GDML-Test-Files/test5.gdml"
filename = "/home/keith/GDML-Test-Files/test6.gdml"

main()

