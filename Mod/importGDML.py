# -*- coding: utf8 -*-

#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2017-2018 Keith Sloan <keith@sloan-home.co.uk>          *
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
#*                                                                         *
#***************************************************************************
__title__="FreeCAD - Geant4 GDML importer"
__author__ = "Keith Sloan <keith@sloan-home.co.uk>"
__url__ = ["https://github.com/KeithSloan/FreeCAD_Geant4"]

printverbose = True

print "Starting"

import FreeCAD, os, sys, re, math
import Part, PartGui
from Geant4 import *
#from ctypes import *
import Geant4.G4gdml

print "Imported"

if FreeCAD.GuiUp:
    import FreeCADGui
    gui = True
else:
    if printverbose: print("FreeCAD Gui not present.")
    gui = False


import Part


if open.__module__ == '__builtin__':
    pythonopen = open # to distinguish python built-in open function from the one declared here


#try:
#    _encoding = QtGui.QApplication.UnicodeUTF8
#    def translate(context, text):
#        "convenience function for Qt translator"
#        from PySide import QtGui
#        return QtGui.QApplication.translate(context, text, None, _encoding)
#except AttributeError:
#    def translate(context, text):
#        "convenience function for Qt translator"
#        from PySide import QtGui
#        return QtGui.QApplication.translate(context, text, None)

def open(filename):
    "called when freecad opens a file."
    global doc
    global pathName
    docname = os.path.splitext(os.path.basename(filename))[0]
    doc = FreeCAD.newDocument(docname)
    if filename.lower().endswith('.gdml'):
        processGDML(filename)
    return doc

def insert(filename,docname):
    "called when freecad imports a file"
    global doc
    global pathName
    groupname = os.path.splitext(os.path.basename(filename))[0]
    try:
        doc=FreeCAD.getDocument(docname)
    except NameError:
        doc=FreeCAD.newDocument(docname)
    if filename.lower().endswith('.gdml'):
        processGDML(filename)

class switch(object):
    value = None
    def __new__(class_, value):
        class_.value = value
        return True

def case(*args):
    return any((arg == switch.value for arg in args))

def processPlacement(pv) :
    print("Process Placement")
    print("Volume Rotation")
    print pv.GetRotation()
    print("Object Rotation")
    print pv.GetObjectRotationValue()
    print("Volume Translation")
    tran = pv.GetTranslation()
    #print dir(tran)
    print tran
    print("Object Translation")
    print pv.GetObjectTranslation()
   

def createBox(pv,lx,ly,lz) :
    print "CreateBox : "
#    print solid.attrib
#    mycube=doc.addObject('Part::Box',volref.get('ref')+'_'+solid.get('name')+'_')
    mycube=doc.addObject('Part::Box','nameBox')
    mycube.Length = lx
    mycube.Width  = ly
    mycube.Height = lz
    print "length : "+str(lx)+' width : '+str(ly)+' height : '+str(lz)
#    base = FreeCAD.Vector(lx-x/2,ly-y/2,lz-z/2)
#    mycube.Placement = processPlacement(base,rot)
#    print mycube.Placement.Rotation

    #mycube.Placement = processPlacement(pv)
    processPlacement(pv)
    mycube.ViewObject.DisplayMode = 'Wireframe'
    return(mycube)

def makeCylinder(solid,r) :
    mycyl = doc.addObject('Part::Cylinder',solid.get('name')+'_')
    mycyl.Height = getVal(solid,'z')
    mycyl.Radius = r
    if solid.get('aunit' == 'rad') :
       mycyl.Angle = 180 * float(solid.get('deltaphi')) / math.pi
    if solid.get('aunit' == 'degrees') :
       mycyl.Angle = solid.get('deltaphi')
    return mycyl

def createTube(solid,volref,lx,ly,lz,rot) :
    print "CreateTube : "
    print solid.attrib
    rmax = getVal(solid,'rmax')
    rmin = solid.get('rmin')
    if ( rmin is None or rmin == 0 ) :
       mytube = makeCylinder(solid,rmax)
    else :
       mytube = doc.addObject('Part::Cut','Tube_'+solid.get('name')+'_')
       mytube.Base = makeCylinder(solid,rmax)
       mytube.Tool = makeCylinder(solid,rmin)

    print "Position : "+str(lx)+','+str(ly)+','+str(lz)
    base = FreeCAD.Vector(lx,ly,lz)
    mytube.Placement = processPlacement(base,rot)
    print mytube.Placement.Rotation

def createGDMLCone(volref,solid,material) :
    from GDMLObjects import GDMLCone, ViewProvider
    print "CreateCone : "
    mycone=FreeCAD.ActiveDocument.addObject("Part::FeaturePython","GDMLCone")
    rmin1 = solid.GetInnerRadiusMinusZ()
    rmax1 = solid.GetInnerRadiusPlusZ()
    rmin2 = solid.GetOuterRadiusMinusZ()
    rmax2 = solid.GetOuterRadiusPlusZ()
    z = solid.GetZHalfLength()*2
    startphi = solid.GetStartPhiAngle()
    deltaphi = solid.GetDeltaPhiAngle()
    GDMLCone(mycone,rmin1,rmax1,rmin2,rmax2,z,startphi,deltaphi, \
            "rad","mm",material)
    print("GDMLCone initiated")
    ViewProvider(mycone.ViewObject)
    print("GDMLCone ViewProvided - added")
    return(mycone)

def createGDMLBox(volref,solid,material) :
    from GDMLObjects import GDMLBox, ViewProvider
    print "CreateBox : "
    mybox=FreeCAD.ActiveDocument.addObject("Part::FeaturePython","GDMLBox")
    x = solid.GetXHalfLength()*2
    y = solid.GetYHalfLength()*2
    z = solid.GetZHalfLength()*2
    GDMLBox(mybox,x,y,z,"mm",material)
    ViewProvider(mybox.ViewObject)
    #print "Logical Position : "+str(lx)+','+str(ly)+','+str(lz)
    #base = FreeCAD.Vector(lx-x/2,ly-y/2,lz-z/2)
    #mycube.Placement = processPlacement(base,rot)
    #print mycube.Placement.Rotation
    #mycube.ViewObject.DisplayMode = 'Wireframe'
    return mybox


def parseLogicalVolume(lv,pv) :
    print("Parse Logical Volume "+str(lv.GetName()))
#   print dir(lv)
    solid = lv.GetSolid()
    G4mat = lv.GetMaterial()
    material = str(G4mat.GetName())
    while switch(type(solid)) :
       if case(Geant4.G4geometry.G4Box):
              obj = createGDMLBox(pv,solid,material)
              break

       if case(Geant4.G4geometry.G4Cons):
              obj = createGDMLCone(pv,solid,material)
              break

       if case(Geant4.G4geometry.G4Tubs):
              createTubs()
              break

       if case(Geant4.G4geometry.G4Trap):
              Z  = solid.GetZHalfLength()*2
              #Y1 = solid.GetHalfLength1()*2
              #X1 = solid.getHalfLength1()*2
              #X2 = solid.getHalfLength2()*2
              #X3 = solid.getHalfLength3()*2
              #X4 = solid.getHalfLength4()*2
              #TA1 = solid.getTanAlpha1()
              #TA2 = solid.getTanAlpha2()
              #createTrap(Z,Y1,X1,X2,X3,X4,TA1,TA2)
              createTrap(1,2,3,4,5,6,7,8)
              break

       if case(Geant4.G4geometry.G4SubtractionSolid) :
              subtractSolid()
              break

       if case(Geant4.G4geometry.G4UnionSolid) :
              unionSolid()
              break

       print "Solid type : "+str(type(solid))+" Not yet supported\n"
       break

#    print "Deal with Translation and Rotation"
#    t3v = pv.GetObjectTranslation()
#    print "X : "+str(t3v.getX())
#    print "Y : "+str(t3v.getY())
#    print "Z : "+str(t3v.getZ())
#    print t3v

#    rotMat = pv.GetObjectRotationValue()
#    print rotMat

#    g4aff = G4AffineTransform()
#    g4aff = G4AffineTransform(pv.GetObjectTranslation(),
#                            pv.GetObjectTranslation())
#    print g4aff

#    p = obj.Placement

#    print p
#    print p.toMatrix()
#    pm = FreeCAD.Matrix()

def browsePhysicalVolume(pv):
    print("\nPhysical Volume  : "+str(pv.GetName()))
    lv = pv.GetLogicalVolume()
    num = lv.GetNoDaughters()
    if num == 0 :
       parseLogicalVolume(lv,pv)
    else :
       print("Num Daughters : "+str(num))
       for i in range(0,num,1) :
           pvd = lv.GetDaughter(i)
           browsePhysicalVolume(pvd)


def processGDML(filename):
    FreeCAD.Console.PrintMessage('Geant4 - Import GDML file : '+filename+'\n')
    if printverbose: print ('Geant4 - ImportGDML Version 0.1')
    
    gdml_parser = G4GDMLParser()
    gdml_parser.Read(G4String(str(filename))) 

#    Reader = gdml_parser.GetReader()

#    wv = gdml_parser.GetWorldVolume(G4String(str("Default")))
    wv = gdml_parser.GetWorldVolume()
    num = browsePhysicalVolume(wv)
    FreeCAD.Console.PrintMessage("Final Number : " + str(num)+'\n')

    doc.recompute()
    FreeCAD.Console.PrintMessage('End processing GDML file\n')
