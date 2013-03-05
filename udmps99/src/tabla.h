/*
tabla.h - tabla de símbolos
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

#ifndef _TABLA_H_
#define _TABLA_H_

#include "instr.h"
#include "tipos.h"

class EntradaTabla {
    friend class Tabla;

    EntradaTabla *sgte;
	int offset;
	byte tipo;
	char *ident;

public:

    EntradaTabla( const char *ident, byte tipo, int offset = 0 );
	EntradaTabla();
	~EntradaTabla();

	byte Tipo( void );
	void ActualizarTipo( byte );
	int OffSet( void );
	void ActualizarOffSet( int );
	const char* Ident( void );

};

class Etiqueta: public EntradaTabla {

	Instr *pinstr;

public:

	Etiqueta( const char *ident, byte tipo, Instr *pinstr );
	~Etiqueta();

	Instr * PtrInstr( void );

};

class Tabla {

    EntradaTabla *lista_entradas;
	EntradaTabla *ult_entrada;

	void InsertarEntrada( EntradaTabla *entrada );

public:

	Tabla();
	~Tabla();

	EntradaTabla* InsertarVariable( const char *ident, byte tipo, word offset = 0 );
	Etiqueta* InsertarEtiqueta( const char *ident, byte tipo, Instr *pinstr );
	void BorrarDeclLocales( void );

	EntradaTabla* BuscarIdent( const char *ident );

};

#endif
