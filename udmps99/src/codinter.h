/*
codinter.h - código intermedio
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

#ifndef _CODINTER_H_
#define _CODINTER_H_

// $JK200910 linea nueva
#include <cstdio>
// 201102 EGS+LRG+JK: corrigiendo warnings, línea nueva
#include <iostream>
#include <fstream>
#include "tabla.h"
#include "instr.h"
#include "pila.h"
#include "tipos.h"

// 201102 EGS+LRG+JK: corrigiendo warnings, línea nueva
using namespace std;

class CodInter
{
private:

	Instr *lista_instr;
	Instr *inicio, *instr_act, *ult_instr;
	Pila *pila;
	Tabla *tabla;
// 201102 EGS+LRG+JK: corrigiendo warnings
//	FILE *f_log, *f_out, *f_mpn;
	ofstream f_out;
	ofstream f_mpn;
	ofstream f_log;
// SAG: esta variable sobra...
//    int debug;
// $JK200910 esta variable NOOOOOO sobra, cambio linea anterior a siguiente
	int debug;

	void EjecutarInstr( void );
	void EscribirInstr( void );

    // SAG: es mejor que devuelva la instrucci¢n que se a¤ada...
//    void InsertarInstr( Instr* instr );
    Instr *InsertarInstr( Instr* instr );

public:

	CodInter( Tabla *tabla, char *fich, int debug = 0 );
	~CodInter();

    Instr* InsInstrInicio( int cod, integer n );
	Instr* InsertarInstr( int cod, const char *atr = 0 );
    Instr* InsertarInstr( int cod, integer val_int );
    Instr* InsertarInstr( int cod, byte val_byte );
    Instr* InsertarInstr( int cod, real val_real );
	Instr* InsertarInstr( int cod, int offset, byte flag, const char *ident );
	void EjecutarCodigo( void );
	void EscribirCodigo( void );

};

#endif

