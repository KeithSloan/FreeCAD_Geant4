sudo rm -r build
mkdir build
cd build
cmake .. \
#-DPYTHON_INCLUDE_DIR=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")  \
#-DPYTHON_LIBRARY=$(python -c "import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR'))")
make -j4
#make configure
#make install
cp myG4VSolid.so ../lib
