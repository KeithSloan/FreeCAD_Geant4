cmake_minimum_required(VERSION 3.0)
find_package(PythonLibs 3 REQUIRED)
#To prevent attempts to link to python2 libraries, specify
#the version of libboost_python
#See https://gitlab.kitware.com/cmake/cmake/issues/16391
if(UNIX)
set(BOOST_PYTHONLIB python-py36)
else()
set(BOOST_PYTHONLIB python3)
endif()
#add_executable(myG4VSolid myG4VSolid.cc)
find_package(Boost COMPONENTS ${BOOST_PYTHONLIB})
python_add_module(myG4VSolid myG4VSolid.cc)
#target_include_directories(${GEANT4_SOURCE}/geometry/managment/include PUBLIC 
target_include_directories(myG4VSolid PUBLIC
   /home/keith/geant4.10.05/source/global/management/include 
   /home/keith/geant4.10.05/source/geometry/management/include 
   /home/keith/geant4.10.05/source/global/HEPGeometry/include 
   ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(myG4VSolid
   ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
