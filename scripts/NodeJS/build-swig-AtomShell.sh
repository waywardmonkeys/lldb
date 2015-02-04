#! /bin/sh

/opt/swig/bin/swig -c++ -javascript -node -DV8_VERSION=0x032435 -I../../include -I. -o lldb_wrap.cxx ../lldb.swig
HOME=~/.atom-shell-gyp node-gyp rebuild --target=0.18.0 --dist-url=https://gh-contractor-zcbenz.s3.amazonaws.com/atom-shell/dist
