/*
tipos.h - constantes y tipos básicos de UDMPs99
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

#ifndef _TIPOS_H_
#define _TIPOS_H

#define AMBITO  0x03
#define TIPO 	0x30
#define ENTRA	0xC0

#define GLOBAL	0x01
#define LOCAL	0x02
#define INT		0x10
#define REAL	0x20
#define BYTE    0x30  

#define ID_ETIQ	0x80
#define ID_VAR	0x40

// SAG: tipos de datos: INTEGER (4 bytes), REAL (8 bytes) y BYTE (1 byte)
//typedef long integer;
//typedef unsigned int word;
// 201102 EGS+LRG+JK: the type hell; UDMPs99 no está pensada para 64 bits (o al menos, los programas compilados a .mpv no lo están)
// 201102 EGS+LRG+JK: the type hell; con lo que los tamaños deben ser fijos independientemente de la arquitectura
// 201102 EGS+LRG+JK: the type hell; para conseguir lo anterior todavía no podemos usar stdint.h porque es C99, pero "missing" en GCC y otros
#include <limits.h>
#if INT_MAX == 2147483647L
typedef int integer;
typedef unsigned int word;
#elif LONG_MAX == 2147483647L
typedef long integer;
typedef unsigned long word;
#else
	#error "Incapaz de determinar el tamaño de integer en tu sistema. Build aborted\n"
#endif

typedef double real;
typedef unsigned char byte;

// 201102 EGS+LRG+JK: the type hell; dejamos los tipos originales (arriba), pero traemos aquí desde pila.h lo siguiente
//#define TAM_DIR		4	// sizeof( unsigned long );
//#define TAM_INT		4	// sizeof( long );
//#define TAM_REAL    8   // sizeof( double );
//#define TAM_BYTE    1   // sizeof( byte );
// 201102 EGS+LRG+JK: the type hell; antes de tener claro que UDMPs99 es de 32 bits obligatoriamente
//#define TAM_INT		( sizeof(integer) )
//#define TAM_REAL    ( sizeof(real) )
//#define TAM_BYTE    ( sizeof(byte) )
//#define TAM_DIR		( sizeof(word) )
#define TAM_INT		4	// == sizeof( integer ) == s32
#define TAM_REAL    8   // == sizeof( real ) == f64
#define TAM_BYTE    1   // == sizeof( byte ) == u8
#define TAM_DIR		4	// == sizeof( word ) == u32

#endif
