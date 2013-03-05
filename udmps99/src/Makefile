# udmps99 - intérprete de máquina de pila simbólica UDMPs99
#
# Copyright (C) 1997, 1998, 1999, 2007, 2008, 2009, 2011
# The UDMPs99 team (Universidad de Deusto)
#
# The UDMPs99 team: Andoni Eguíluz, JosuKa Díaz
# (Departamento de Ingeniería Informática, Facultad de Ingeniería)
# and Jesús Redrado, Jorge García, Ana Cabana, Sergio Argüello, David Vázquez,
# Igor Ruiz, David Ausín, Endika Gutiérrez, Luis Rodríguez
#
# v.1.0ß 19990419
# v.1.1ß 20110318
#
# This file is part of UDMPs99.
#
# UDMPs99 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# UDMPs99 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

#CXX = g++
#CXXFLAGS = -Wall -ggdb -I./include -DDEBUG -Os
CXXFLAGS = -Wall -I./include -DDEBUG -Os
LDFLAGS = -o udmps99

OBJS = codinter.o lexyy.o maqpila.o pila.o tabla.o udmps99.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

install:
	cp udmps99 ../test
	mv udmps99 ../bin/linux32

