/*
instr.h - estructura de datos de instrucciones
Copyright (C) 1997, 1998, 1999, 2007, 2008, 2009, 2011
The UDMPs99 team (Universidad de Deusto)

The UDMPs99 team: Andoni Eguíluz, JosuKa Díaz
(Departamento de Ingeniería Informática, Facultad de Ingeniería)
and Jesús Redrado, Jorge García, Ana Cabana, Sergio Argüello, David Vázquez,
Igor Ruiz, David Ausín, Endika Gutiérrez, Luis Rodríguez

v.1.0ß 19990419
v.1.1ß 20110318

This file is part of UDMPs99.

UDMPs99 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

UDMPs99 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _INSTR_H_
#define _INSTR_H_

#include "tipos.h"


union Atr {
	char *ident;
    integer val_int;    // SAG: mejor llamarlos por lo que son...
    real val_real;
    byte val_byte;
    struct {
		int offset;
        byte flag;
	};
};


class Instr {
    friend class CodInter;

    Instr *sgte;

	int cod;
	Atr atr;
	char *ident;
	byte flag;		// diferenciar entre variables globales y
                    // locales ( o parametros ), y para saber
                    // el tipo de la variable ( int o real )

public:
    Instr( int cod, const char *atr = 0 );
    Instr( int cod, integer val_int );
    Instr( int cod, byte val_byte );
    Instr( int cod, real val_real );
	Instr( int cod, int offset, byte flag, const char *ident );
	~Instr();
};

#endif
