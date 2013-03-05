/*
pila.h - operaciones básicas de la máquina de pila
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

#ifndef _PILA_H_
#define _PILA_H_

#include "instr.h"

// 201102 EGS+LRG+JK: the type hell; corregimos:
//#define TAM_PTR     4   // sizeof( Instr* );
#define TAM_PTR     ( sizeof(Instr*) )
// 201102 EGS+LRG+JK: the type hell; pasamos lo siguiente a tipos.h
//#define TAM_DIR		4	// sizeof( unsigned long );
//#define TAM_INT		4	// sizeof( long );
//#define TAM_REAL    8   // sizeof( double );
//#define TAM_BYTE    1   // sizeof( byte );
#define MAX_BUFFER	4096

// 201102 EGS+LRG+JK: the type hell; ¿cual debe ser el tipo de componente de la pila? votamos por word
//typedef unsigned long t_pila;
typedef word t_pila;

class Pila
{

private:

	byte *buffer;
    t_pila sp, bp, tam;
	Instr **ip;

public:

    Pila( Instr **ip, t_pila tam = MAX_BUFFER );
	~Pila();

    t_pila BP( void );

    // Funciones de conversi¢n de tipos:
	void CambiarIntInt( void );
					// En la pila hay dos valores enteros. Esta
					// funcion intercambia ambos valores.
	void CambiarIntReal( void );
					// En la cima de la pila hay un real, y el
					// siguiente valor es un entero. Intercambia
					// ambos valores en la pila.
	void CambiarRealInt( void );
					// En la cima de la pila hay un entero, y el
					// siguiente valor es un real. Intercambia
					// ambos valores en la pila.
	void CambiarRealReal( void );
					// Intercambia los dos ultimos valores reales
					// en la pila.
    void CambiarByteByte( void );
                    // Intercambia los dos ultimos bytes
                    // en la pila.
    void CambiarByteInt( void );
                    // En la cima de la pila hay un byte, y el
                    // siguiente valor es un entero. Intercambia
                    // ambos valores en la pila.
    void CambiarByteReal( void );
                    // En la cima de la pila hay un byte, y el
                    // siguiente valor es un real. Intercambia
                    // ambos valores en la pila.
    void CambiarRealByte( void );
                    // En la cima de la pila hay un real, y el
                    // siguiente valor es un byte. Intercambia
                    // ambos valores en la pila.
    void CambiarIntByte( void );
                    // En la cima de la pila hay un entero, y el
                    // siguiente valor es un byte. Intercambia
                    // ambos valores en la pila.

    void IntAReal( void );  // Convierte el valor entero situado en la cima
                            // de la pila a un valor real.
	void RealAInt( void );	// Convierte el valor real situado en la cima
                            // de la pila a un valor entero.
    void ByteAInt( void );  // Convierte el valor byte situado en la cima
                            // de la pila a un valor entero.
    void IntAByte( void );  // Convierte el valor entero situado en la cima
                            // de la pila a un valor byte.

	// Funciones de manejo de la pila:
    void Ins( t_pila );     // Inserta n bytes en la cima de la pila.
	void InsInt( integer );	// Introduce un valor entero en la pila.
    void InsByte( byte );   // Introduce un byte en la pila.
	integer DesapilarInt( void );
					// Elimina un valor entero de la cima de la pila
    byte DesapilarByte( void );
                    // Elimina un byte de la cima de la pila

	void InsReal( real );	// Introduce un valor entero en la pila.
	real DesapilarReal( void );
					// Elimina un valor real de la cima de la pila.
    void Desapilar( t_pila );
					// Elimina n bytes de la cima de la pila
    void CopiarInt ( void );// Duplica el valor entero de la cima de la pila
	void CopiarReal( void );// Duplica el valor real de la cima de la pila
    void CopiarByte( void );// Duplica el valor byte  de la cima de la pila
    void AsigBase  ( void );// Pone BP al SP actual
    void PonerBase ( void );// Pone BP al SP actual e inserta el BP anterior
                            // en la pila
    void CogerBase ( void );// Toma el valor (direccion) de la cima de la pila
                            // y lo carga en el registro base.

    // Asignaciones:
    void ValorDInt( t_pila );
					// Introduce un valor entero en la pila.
    void ValorDByte( t_pila );
                    // Introduce un valor byte en la pila.

    void ValorDReal( t_pila );
					// Introduce un valor real en la pila.
    void ValorIInt( t_pila );
					// Introduce la direccion de la variable entera en la pila.
    void ValorIByte( t_pila );
                    // Introduce la direccion de la variable byte en la pila.
    void ValorIReal( t_pila );
					// Introduce la direccion de la variable real en la pila.
    void AsigInt( void );
                    // Toma dos valores de la pila. El primero es el valor
                    // entero que hay que asignar y el segundo es la
                    // direcci¢n de la variable a la que hay que asignar el
                    // valor.
    void AsigByte( void );  // Igual pero para variables de tipo byte.
	void AsigReal( void );	// Igual pero para variables de tipo real.
	void Ret( integer n );	// Toma el valor de la cima como direccion de
                            // retorno. Elimina ademas de la pila tantos
                            // bytes como indique n.
	void InsIP( void );
	void DesapilarIP( void );

private:

    // SAG: funciones a¤adidas para optimizaci¢n de c¢digo
    void apilar( void *, t_pila bytes );
                    // apilar algo en la pila
    void *desapilar( t_pila bytes );
                    // desapilar algo de la pila
    void valori( t_pila dir );
                    // introduce una direcci¢n de una variable en la pila
    void valord( t_pila dir, t_pila tam );
                    // introduce un valor en la pila
    void asig( void *valor, t_pila bytes );
                    // asignar un valor donde se indique en la pila
};

#endif
