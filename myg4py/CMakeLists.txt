cmake_minimum_required(VERSION 3.0)

#set(CMAKE_CXX_STANDARD 14)
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

#include_directories(/home/keith/geant4.10.05/source)
include_directories(${Geant4_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories (${GEANT4_LIBRARY_DIR} ${Boost_LIBRARY_DIRS})

#add_library(MyFC_G4 SHARED 
#    MyFC_G4.cpp
#)

add_library(MyG4py SHARED 
    MyG4py.cpp
)

target_include_directories(MyG4py PUBLIC
   ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} ${Geant4_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include )

target_link_libraries(MyG4py
   ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${Geant4_LIBRARIES})
#add_dependencies(MyG4py boost)
#configure_file(__init__.py ${CMAKE_CURRENT_BINARY_DIR}/src/__init__.py COPYONLY)

set_target_properties(MyG4py PROPERTIES PREFIX .so)
set_target_properties(MyG4py PROPERTIES PREFIX "")

#install(TARGETS MyG4py __init__.py DESTINATION "${PYTHON_INSTALL_PATH}")
#install(TARGETS MyG4py DESTINATION "${PYTHON_INSTALL_PATH}")
install(TARGETS MyG4py DESTINATION lib )
