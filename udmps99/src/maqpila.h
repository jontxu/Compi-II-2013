/*
maqpila.h - máquina de pila
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

#ifndef _MAQPILA_H_
#define _MAQPILA_H_

// $JK200910 cambio linea
//#include <stdio.h>
#include <cstdio>
// $JK200910 linea nueva
#include <iostream>
// $JK200910 cambio linea
//#include <fstream.h>
#include <fstream>
// $JK200910 cambio linea
//#include "flexlexe.h"
#include <FlexLexer.h>
#include "codinter.h"
#include "tabla.h"

// $JK200910 linea nueva
using namespace std;

// 201102 EGS+LRG+JK: the type hell; sobra (ya declarado en "tipos.h")
//typedef unsigned char byte;

class UdLexica
{

private:

	byte token;
	char *lexema;

public:

	UdLexica( byte token, const char *lexema );
	~UdLexica();

	byte Token( void );
	const char* Lexema( void );

};

class MaqPila
{
// SAG: para saber el nombre de los ficheros...
    char *fich;
    UdLexica *udlexact, *sgteudlex;
// 201102 EGS+LRG+JK: the type hell; creemos que debe ser de tipo word, pero considerar volver a original (int)
//	int offset_local, offset_global;
	word offset_local, offset_global;


	CodInter *codinter;
	Tabla *tabla;
	yyFlexLexer *yylex;
// $JK200910 cambio 3 lineas...
//	int yyin;
//	filebuf *fb;
//	iostream *iostr;
// $JK200910 ... por las 3 siguientes...
	istream *istr;
	streambuf *isb;
	ifstream filestr;
// $JK200910 ... hasta aqui

//    void Error( char* );
    void Error( const char* );

	void Programa( void );
	void DeclFuncion( void );
	void DeclLocales( void );
	void DeclParametros( void );
	void Declaracion( void );
	void Instruccion( void );
	void Parear( byte token );
	void Avanzar( void );
	void SgteUdLexica( void );

public:

	int error;

	MaqPila( char*, int );
	~MaqPila();

	void Ejecutar( int );
};

#endif
