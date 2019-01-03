FreeCAD.addImportType("GDML (*.gdml)","importGDML")
FreeCAD.addExportType("GDML (*.gdml)","exportGDML")
import sys
sys.path.append("/home/keith/geant4.10.05/environments/g4py/lib")
for p in sys.path:
	print (p)
