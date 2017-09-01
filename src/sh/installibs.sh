#!/bin/sh

cd $HOME/Downloads/giflib-4.1.6
./configure
make
make install
cd $HOME/Downloads/jpeg-7
./configure
make
make install
cd $HOME/Downloads/libpng-1.2.41beta13
./configure
make
make install
cd $HOME/Downloads/tiff-3.8.2
#cp libjpeg.la /usr/local/lib/libjpeg.la                                                                                                                                           
#cp -R .libs /usr/local/lib/.libs                                                                                                                                                  
./configure --with-ns
make
make install