
#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2019 Keith Sloan <keith@sloan-home.co.uk>               *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Library General Public License for more details.                  *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with this program; if not, write to the Free Software   *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         * 
#*   Acknowledgements :                                                    *
#*                                                                         *
#***************************************************************************
__title__="FreeCAD Geant4 Workbench - GDML exporter Version"
__author__ = "Keith Sloan <keith@sloan-home.co.uk>"
__url__ = ["https://github.com/KeithSloan/FreeCAD_Geant4"]

import FreeCAD, os, Part, math
from FreeCAD import Vector

from Geant4 import *
from MyG4py import *
#from enums import *

import g4py.Qmaterials, g4py.Qgeom
import g4py.ExN01pl, g4py.ParticleGun

try: import FreeCADGui
except ValueError: gui = False
else: gui = True

#***************************************************************************
# Tailor following to your requirements ( Should all be strings )          *
# no doubt there will be a problem when they do implement Value
if open.__module__ in ['__builtin__', 'io']:
    pythonopen = open # to distinguish python built-in open function from the one declared here

#################################
#  Setup Geant4 environment
#################################
#  set geometry
g4py.Qmaterials.Construct()
g4py.Qgeom.Construct()

#  minimal physics list
g4py.ExN01pl.Construct()

#  initialize
gRunManager.Initialize()

#  visualization
gApplyUICommand("/vis/open OGLSX")
gApplyUICommand("/vis/scene/create")
gApplyUICommand("/vis/scene/add/volume")
gApplyUICommand("/vis/sceneHandler/attach")


class switch(object):
    value = None
    def __new__(class_, value):
        class_.value = value
        return True

def case(*args):
    return any((arg == switch.value for arg in args))


def ConstructWorld(self):
    # Python has automatic garbage collection system.
    # Geometry objects must be defined as GLOBAL not to be deleted.
    global sld_world, lv_world, pv_world, va_world

    sld_world= G4Box("world", 1.*m, 1.*m, 1.*m)
    lv_world= G4LogicalVolume(sld_world, self.air, "world")
    pv_world= G4PVPlacement(G4Transform3D(), lv_world, "world",
                            None, False, 0)

    va_world= G4VisAttributes()
    va_world.SetVisibility(False)
    lv_world.SetVisAttributes(va_world)

    # solid object (dummy)
#    global sld_brep_box, sld_sld, lv_sld, pv_sld

#    sld_sld= G4Box("dummy", 10.*cm, 10.*cm, 10.*cm)

#    p1 = G4ThreeVector(0.0,0.0,0.0)
#    p2 = G4ThreeVector(0.0,50.0,0.0)


def report_object(obj) :
    
    print("Placement")
    print("Pos   : "+str(obj.Placement.Base))
    print("axis  : "+str(obj.Placement.Rotation.Axis))
    print("angle : "+str(obj.Placement.Rotation.Angle))
    
    while switch(obj.TypeId) :

      if case("Part::Sphere") :
         print("Sphere Radius : "+str(obj.Radius))
         break
           
      if case("Part::Box") : 
         print("cube : ("+ str(obj.Length)+","+str(obj.Width)+","+str(obj.Height)+")")
         break

      if case("Part::Cylinder") : 
         print("cylinder : Height "+str(obj.Height)+ " Radius "+str(obj.Radius))
         break
   
      if case("Part::Cone") :
         print("cone : Height "+str(obj.Height)+ " Radius1 "+str(obj.Radius1)+" Radius2 "+str(obj.Radius2))
         break

      if case("Part::Torus") : 
         print("Torus")
         print(obj.Radius1)
         print(obj.Radius2)
         break

      if case("Part::Prism") :
         print("Prism")
         break

      if case("Part::RegularPolygon") :
         print("RegularPolygon")
         break

      if case("Part::Extrusion") :
         print("Extrusion")
         break

      if case("Circle") :
         print("Circle")
         break

      if case("Extrusion") : 
         print("Wire extrusion")
         break

      print("Other")
      print(obj.TypeId)
      break

def fc2g4Vec(v) :
    return(G4ThreeVector(v[0],v[1],v[2]))

def createFacet(v0,v1,v2) :
    print("Create Facet : ")
    print(str(v0)+" : "+str(v1)+" : "+str(v2))
# following should work but does not wait for weyner response in forum
#    facet = MyG4TriangularFacet(v0,v1,v2)
    v0g4 = fc2g4Vec(v0)
    v1g4 = fc2g4Vec(v1)
    v2g4 = fc2g4Vec(v2)
    facet = MyG4TriangularFacet(v0g4,v1g4,v2g4)
#   facet = G4VFacet() cannot be initiated from python
#   G4TrianglerFacet needs to be constructed with all three vectors
#   otherwise Isdefined is false and one gets an error 
# need to convert FreeCAD base.Vector to Geant4 vector Hep3Vector
    return(facet)

def mesh2Tessellate(mesh) :
     print "mesh"
     print mesh
     print dir(mesh)
     print "Facets"
     print mesh.Facets
     print "mesh topology"
     print dir(mesh.Topology)
     print mesh.Topology

#     add name of TessellateSolid
     tessellate = G4TessellatedSolid()
#    mesh.Topology[0] = points
#    mesh.Topology[1] = faces
     for fc_facet in mesh.Topology[1] : 
         print(fc_facet)
         g4_facet = createFacet(mesh.Topology[0][fc_facet[0]],
                                mesh.Topology[0][fc_facet[1]],
                                mesh.Topology[0][fc_facet[2]])
         tessellate.AddFacet(g4_facet)


def process_Mesh(obj) :
    print (obj)
    print dir(obj)
    mesh2Tessellate(obj.Mesh)

def shape2Tessellate(shape) :
     import MeshPart
     return mesh2Tessellate(MeshPart.meshFromShape(Shape=shape, Deflection = 0.0))
#            Deflection= params.GetFloat('meshdeflection',0.0))) 

def process_Object_Shape(obj) :
    print("Process Object Shape")
    print(obj)
    print(obj.PropertiesList)
    shape = obj.Shape
    print shape
    print(shape.ShapeType)
    while switch(shape.ShapeType) : 

         if case("Mesh::Feature") :
            print("Mesh")
	    mesh2Tessellate(mesh) 
            break

	 print("ShapeType Not handled")
         print(shape.ShapeType)
         break

#   Dropped through to here
#   Need to check has Shape
    print("Faces")
    for f in shape.Faces :
        print f
#        print dir(f)

# Virtual function    G4solid = myG4VSolid()
# G4solid = G4BREPSolid() G4BREPSolid depreciated

#   Create Mesh from shape & then create Tessellated Solid in Geant4
    mesh2Tessellate(shape2Tessellate(shape))

    #dir   = G4ThreeVector(0.,1.,0.)
    #axis  = G4ThreeVector(0.,1.,0.) 
    #point = G4Point3D(0.,0.,0.)
    #point = G4ThreeVector(0.,0.,0.)
    #G4FPlane(dir,axis,point,1)

def process_object(obj) :
   
    print("Process Object")
    while switch(obj.TypeId) :

      if case("Part::Cut") :
         print("Cut")
         break

      if case("Part::Fuse") :
         print("Union")
         break

      if case("Part::Common") :
         print("intersection")
         break

      if case("Part::MultiFuse") :
         print("Multifuse") 
         break

      if case("Part::MultiCommon") :
         print("Multi Common / intersection")
         break

      if case("Mesh::Feature") :
         print("Mesh Feature") 
         process_Mesh(obj)
         break

# Need to check obj has attribute Shape
      process_Object_Shape(obj)
      break

def export(exportList,filename) :
    "called when FreeCAD exports a file"
    
    # process Objects
    print("\nStart GDML Export 0.1")

    for obj in exportList :
        print(obj)
        print("Name : "+obj.Name)
        print("Type : "+obj.TypeId) 
        report_object(obj)
        process_object(obj)

    # write GDML file              
    print("Write to GDML file")
    #navigator= gTransportationManager.GetNavigatorForTracking()
    #world_volume= navigator.GetWorldVolume()

    #gdml_parser = G4GDMLParser()
    #gdml_parser.Write(filename, world_volume)
    
    FreeCAD.Console.PrintMessage("successfully exported "+filename)
