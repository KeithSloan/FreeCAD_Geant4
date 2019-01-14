cmake_minimum_required(VERSION 3.0)
find_package(PythonLibs 2 REQUIRED)
#find_package(PythonLibs 3 REQUIRED)
#To prevent attempts to link to python2 libraries, specify
#the version of libboost_python
#See https://gitlab.kitware.com/cmake/cmake/issues/16391
if(UNIX)
set(BOOST_PYTHONLIB python-py36)
else()
#set(BOOST_PYTHONLIB python3)
set(BOOST_PYTHONLIB python2)
endif()
#add_executable(myG4VSolid myG4VSolid.cc)
#find_package(Boost COMPONENTS ${BOOST_PYTHONLIB})
find_package(Geant4 REQUIRED)
find_package(Boost COMPONENTS system python)

include_directories(/home/keith/geant4.10.05/source)

#python_add_module(myG4VSolid myG4VSolid.cc)

link_directories (${GEANT4_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

add_library(myG4VSolid SHARED myG4VSolid.cc)

#target_include_directories(${GEANT4_SOURCE}/geometry/managment/include PUBLIC 
target_include_directories(myG4VSolid PUBLIC
   /home/keith/geant4.10.05/source/global/management/include 
   /home/keith/geant4.10.05/source/geometry/management/include 
   /home/keith/geant4.10.05/source/global/HEPGeometry/include 
   ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(myG4VSolid
   ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${Geant4_LIBRARIES})
#add_dependencies(myG4VSolid boost)
#configure_file(__init__.py ${CMAKE_CURRENT_BINARY_DIR}/src/__init__.py COPYONLY)

set_target_properties(myG4VSolid PROPERTIES PREFIX .so)
set_target_properties(myG4VSolid PROPERTIES PREFIX "")

#install(TARGETS myG4VSolid __init__.py DESTINATION "${PYTHON_INSTALL_PATH}")
#install(TARGETS myG4VSolid DESTINATION "${PYTHON_INSTALL_PATH}")
install(TARGETS myG4VSolid DESTINATION lib )
