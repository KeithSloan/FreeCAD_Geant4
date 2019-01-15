cmake_minimum_required(VERSION 3.0)
find_package(PythonLibs 2 REQUIRED)
#the version of libboost_python
#See https://gitlab.kitware.com/cmake/cmake/issues/16391
if(UNIX)
set(BOOST_PYTHONLIB python-py36)
else()
#set(BOOST_PYTHONLIB python3)
set(BOOST_PYTHONLIB python2)
endif()

find_package(Geant4 REQUIRED)
find_package(Boost COMPONENTS system python)

include_directories(/home/keith/geant4.10.05/source)

link_directories (${GEANT4_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

add_library(myg4py SHARED 
    myG4VSolid.cc
    myG4TessellatedSolid.cc
)

target_include_directories(myg4py PUBLIC
#   /home/keith/geant4.10.05/source/global/management/include 
#   /home/keith/geant4.10.05/source/geometry/management/include 
#   /home/keith/geant4.10.05/source/geometry/solids/specfic/include 
#   /home/keith/geant4.10.05/source/global/HEPGeometry/include 
   ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${Geant4_INCLUDE_DIRS} )

target_link_libraries(myg4py
   ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${Geant4_LIBRARIES})
#add_dependencies(myg4py boost)
#configure_file(__init__.py ${CMAKE_CURRENT_BINARY_DIR}/src/__init__.py COPYONLY)

set_target_properties(myg4py PROPERTIES PREFIX .so)
set_target_properties(myg4py PROPERTIES PREFIX "")

#install(TARGETS myg4py __init__.py DESTINATION "${PYTHON_INSTALL_PATH}")
#install(TARGETS myg4py DESTINATION "${PYTHON_INSTALL_PATH}")
install(TARGETS myg4py DESTINATION lib )
