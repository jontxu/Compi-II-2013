/*
tokens.h - tokens de UDMPs99
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

#ifndef _TOKENS_H_
#define _TOKENS_H_

#define ERROR                   0xFF

// SAG & DVR: los hemos ordenado, ya que est n un 'poco' mezclados...
// Nota: el orden en CODINTER.CPP tiene que coincidir.

// Fin de fichero, fin de l¡nea
#define EOFL                    0x00
#define EOLN                    0x01

// Tipos
#define IDENT                   0x02
#define ETIQUETA                0x03
#define NUM_ENT                 0x04
#define NUM_REAL                0x05
#define NUM_BYTE                0x06        // SAG & DVR
#define STRING                  0x07

// Operadores aritm‚ticos
#define OP_ENT_SUMA             0x08
#define OP_ENT_RESTA            0x09
#define OP_ENT_MULT             0x0a
#define OP_ENT_DIV              0x0b
#define OP_ENT_EXP              0x0c

#define OP_REAL_SUMA            0x0d
#define OP_REAL_RESTA           0x0e
#define OP_REAL_MULT            0x0f
#define OP_REAL_DIV             0x10
#define OP_REAL_EXP             0x11

#define OP_BYTE_SUMA            0x12        // SAG & DVR
#define OP_BYTE_RESTA           0x13        // SAG & DVR

#define OP_UNA_ENT              0x14
#define OP_UNA_REAL             0x15
#define OP_UNA_BYTE             0x16        // SAG & DVR

// Operadores relacionales
#define OP_ENT_MENOR            0x17
#define OP_ENT_MAYOR            0x18
#define OP_ENT_MENORIGUAL       0x19
#define OP_ENT_MAYORIGUAL       0x1a
#define OP_ENT_IGUAL            0x1b
#define OP_ENT_DISTINTO         0x1c

#define OP_REAL_MENOR           0x1d
#define OP_REAL_MAYOR           0x1e
#define OP_REAL_MENORIGUAL      0x1f
#define OP_REAL_MAYORIGUAL      0x20
#define OP_REAL_IGUAL           0x21
#define OP_REAL_DISTINTO        0x22

#define OP_BYTE_MENOR           0x23        // SAG & DVR
#define OP_BYTE_MAYOR           0x24        // SAG & DVR
#define OP_BYTE_MENORIGUAL      0x25        // SAG & DVR
#define OP_BYTE_MAYORIGUAL      0x26        // SAG & DVR
#define OP_BYTE_IGUAL           0x27        // SAG & DVR
#define OP_BYTE_DISTINTO        0x28        // SAG & DVR

// Operadores l¢gicos
#define OP_LOG_AND              0x29
#define OP_LOG_OR               0x2a
//#define OP_LOG_NEG        	0x21
#define OP_LOG_NOT              0x2b        // SAG: este nombre es m s propio

// Conversi¢n de tipos
#define INTAREAL                0x2c
#define INTABYTE                0x2d
#define BYTEAINT                0x2e

// Primitivas de c lculo
#define SQRT                    0x2f
#define SIN                     0x30
#define COS                     0x31
#define TAN                     0x32
#define ASIN                    0x33
#define ACOS                    0x34
#define ATAN                    0x35
#define EXP                     0x36
#define LOG                     0x37
#define LN                      0x38
#define ROUND                   0x39
#define TRUNC                   0x3a

// Manejo de la pila
#define INS                     0x3b
#define DESAPILAR               0x3c
#define INSI                    0x3d
#define DESAPILARI              0x3e
#define INSR                    0x3f
#define DESAPILARR              0x40
#define INSB                    0x41
#define DESAPILARB              0x42
#define COPIARI                 0x43
#define COPIARR                 0x44
#define COPIARB                 0x45
#define CAMBIARII               0x46
#define CAMBIARIR               0x47
#define CAMBIARIB               0x48
#define CAMBIARRI               0x49
#define CAMBIARRR               0x4a
#define CAMBIARRB               0x4b
#define CAMBIARBI               0x4c
#define CAMBIARBR               0x4d
#define CAMBIARBB               0x4e

// Control de flujo
#define SI_CIERTO_IR_A          0x4f
#define SI_FALSO_IR_A           0x50
#define IR_A                    0x51
#define ETIQ                    0x52

// Primitivas de E/S
#define LEERI                   0x53
#define LEERR                   0x54
#define LEERB                   0x55
#define ESCRIBIRI               0x56
#define ESCRIBIRR               0x57
#define ESCRIBIRB               0x58        // SAG & DVR
#define ESCRIBIRLN              0x59
#define ESCRIBIRS               0x5a

// Estructura del programa y subprogramas
#define INICIO                  0x5b
#define FIN                     0x5c
#define ETIQV                   0x5d
#define ETIQI                   0x5e
#define ETIQR                   0x5f
#define ETIQB                   0x60

// Declaraci¢n de variables
#define GLOBALI                 0x61
#define GLOBALR                 0x62
#define GLOBALB                 0x63

#define LOCALI                  0x64
#define LOCALR                  0x65
#define LOCALB                  0x66

#define PARAMI                  0x67
#define PARAMR                  0x68
#define PARAMB                  0x69

// Acceso a las variables y asignaciones
#define VALORD                  0x6a
#define VALORI                  0x6b
#define ASIG_ENT                0x6c
#define ASIG_REAL               0x6d
#define ASIG_BYTE               0x6e

// Subprogramas: llamada y retorno
#define LLAMAR                  0x6f
#define RET                     0x70
#define PONERBASE               0x71
#define COGERBASE               0x72

#endif

