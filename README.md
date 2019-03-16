# FreeCAD_Geant4

**Geant4 must be built using the same version of QT as FreeCAD is using.**

## Building Geant4

Set variable for where Geant4 will be installed.
export GEANT4_INSTALL=/usr/local/Geant4

change directory to where Geant4 has been downloaded.

cd ....../Geant4.10.0.5
mkdir build
cd build
cmake .. -DGEANT4_USE_GDML=ON -DGEANT4_USE_QT=ON -DCMAKE_INSTALL_PREFIX=/usr/local/Geant4

make -j4
make install

## Build Geant4Py

change directory to Geant4Py

cd ....../Geant4.10.0.5/environment/g4py
mkdir build
cd build
cmake ..
make -j4
make install

## Install Boost
sudo apt-get install libboost-all-dev

## Symbolic links to relevant python libraries
ln -s ~/geant4.10.05/environments/g4py/lib/Geant4 ~/.local/lib/python2.7/site-packages/Geant4

ln -s ~/FreeCAD_Geant4/MyG4py/lib ~/.local/lib/python2.7/site-packages/MyG4py

## ToDo
Add sym links to python libraries to softLink script - make location neutral

## Acknowledgements

Thanks to

* Wouter Deconnick

and the following FreeCAD forum members

* wmayer
* Joel_graff
* chrisb

## Feedback

To contact the Author email keith[at]sloan-home.co.uk

~                 

