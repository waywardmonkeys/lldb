#! /bin/sh

/opt/swig/bin/swig -c++ -javascript -node -I../../include -I. -o lldb_wrap.cxx ../lldb.swig
node-gyp rebuild
