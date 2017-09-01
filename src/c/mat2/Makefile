# Makefile
# wGui /docs/tutorial/Calc/Makefile
# Copyright (c) 2002 - Rob Wiskow
# rob-dev@boxedchaos.com
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

INCLUDES = -I/usr/include/freetype2 -I../../../includes
LIBS = -L../../../src -lwguid -lfreetype `sdl-config --libs`
CPPFLAGS = -Wall -O0 -g -DDEBUG `sdl-config --cflags`

CALC_OBJS = calc_tutorial.o

.SUFFIXES:
.SUFFIXES: .cpp .o

.cpp.o:; g++ $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

all: CalcApp

CalcApp: $(CALC_OBJS)
	g++ $(CPPFLAGS) $(INCLUDES) -o CalcTutorial $(CALC_OBJS) $(LIBS)

clean:
	rm -rf *~ *.o CalcTutorial
