/*
pila.cpp - operaciones básicas de la máquina de pila
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

// C¢digo modificado por SAG & DVR, Mi‚rcoles 3/3/99

// $JK200910 cambio 2 lineas...
//#include <stdlib.h>
//#include <iostream.h>
// $JK200910 ... por 5 lineas...
#include <cstdlib>
#include <cstring>
#include <iostream>
// $JK200910 ... hasta aqui
// $JK200910 quito linea
//#include <mem.h>
#include "pila.h"

// $JK200910 linea nueva
using namespace std;

Pila::Pila( Instr **ip, t_pila tam )
{
	this->ip = ip;
	this->tam = tam;
	buffer = new byte[tam];
	bp = sp = 0;
}

Pila::~Pila()
{
	delete( buffer );
}

t_pila Pila::BP( void )
{
	return( bp );
}

void Pila::CambiarIntInt( void )
{
    integer i1 = DesapilarInt();
    integer i2 = DesapilarInt();
	InsInt( i1 );
	InsInt( i2 );
}

void Pila::CambiarIntReal( void )
{
    real r = DesapilarReal();
    integer i = DesapilarInt();
	InsReal( r );
	InsInt( i );
}

void Pila::CambiarRealInt( void )
{
    integer i = DesapilarInt();
    real r = DesapilarReal();
	InsInt( i );
	InsReal( r );
}

void Pila::CambiarRealReal( void )
{
    real r1 = DesapilarReal();
    real r2 = DesapilarReal();
	InsReal( r1 );
	InsReal( r2 );
}

void Pila::CambiarByteByte( void )
{
    byte b1 = DesapilarByte();
    byte b2 = DesapilarByte();
    InsByte( b1 );
    InsByte( b2 );
}

void Pila::CambiarByteInt( void )
{
    integer i = DesapilarInt();
    byte b = DesapilarByte();
    InsInt( i );
    InsByte( b );
}

void Pila::CambiarByteReal( void )
{
    real r = DesapilarReal();
    byte b = DesapilarByte();
    InsReal( r );
    InsByte( b );
}

void Pila::CambiarRealByte( void )
{
    byte b = DesapilarByte();
    real r = DesapilarReal();
    InsByte( b );
    InsReal( r );
}

void Pila::CambiarIntByte( void )
{
    byte b = DesapilarByte();
    integer i = DesapilarInt();
    InsByte( b );
    InsInt( i );
}

void Pila::IntAReal( void ) { InsReal( (real)DesapilarInt() ); }
void Pila::ByteAInt( void ) { InsInt ( (integer)DesapilarByte() ); }
void Pila::IntAByte( void ) { InsByte( (byte)DesapilarInt() ); }
void Pila::RealAInt( void ) { InsInt ( (integer)DesapilarReal() ); }

void Pila::Ins( t_pila n )      { apilar( NULL, n ); }
void Pila::InsInt( integer i )  { apilar( &i, TAM_INT ); }
void Pila::InsByte( byte c )    { apilar( &c, TAM_BYTE ); }
void Pila::InsReal( real r )    { apilar( &r, TAM_REAL ); }

void Pila::Desapilar( t_pila n )    { desapilar( n ); }
integer Pila::DesapilarInt( void )  { return *(integer *)desapilar( TAM_INT ); }
byte Pila::DesapilarByte( void )    { return *(byte *)desapilar( TAM_BYTE ); }
real Pila::DesapilarReal( void )    { return *(real *)desapilar( TAM_REAL ); }

void Pila::CopiarInt( void )
{
    integer i = DesapilarInt();
	InsInt( i );
	InsInt( i );
}

void Pila::CopiarReal( void )
{
    real r = DesapilarReal();
    InsReal( r );
	InsReal( r );
}

void Pila::CopiarByte( void )
{
    byte b = DesapilarByte();
    InsByte( b );
    InsByte( b );
}

void Pila::AsigBase( void )
{
      bp = sp;
}

void Pila::PonerBase( void )
{
    apilar( &bp, TAM_DIR );
    AsigBase();
}

void Pila::CogerBase( void )
{
    memcpy( &bp, desapilar( TAM_DIR ), TAM_DIR );
}

void Pila::ValorDInt ( t_pila dir ) { valord( dir, TAM_INT  ); }
void Pila::ValorDByte( t_pila dir ) { valord( dir, TAM_BYTE ); }
void Pila::ValorDReal( t_pila dir ) { valord( dir, TAM_REAL ); }

void Pila::ValorIInt ( t_pila dir ) { valori( dir ); }
void Pila::ValorIByte( t_pila dir ) { valori( dir ); }
void Pila::ValorIReal( t_pila dir ) { valori( dir ); }

void Pila::AsigInt( void )
{
    integer i = DesapilarInt();
    asig( &i, TAM_INT );
}

void Pila::AsigByte( void )
{
    byte b = DesapilarByte();
    asig( &b, TAM_BYTE );
}


void Pila::AsigReal( void )
{
    real r = DesapilarReal();
    asig( &r, TAM_REAL );
}

void Pila::Ret( integer n )
{
	DesapilarIP();
    desapilar( n );
}

void Pila::InsIP( void )        { apilar( ip, TAM_PTR ); }
void Pila::DesapilarIP( void )  { memcpy( ip, desapilar( TAM_PTR ), TAM_PTR ); }


/*-----------------------------------------------------------------------------
    Funciones Privadas
-----------------------------------------------------------------------------*/

// SAG: apilar algo en la pila que ocupe 'bytes' octetos
void Pila::apilar( void *Que, t_pila bytes )
{
    if ( sp+bytes < tam )
    {
        if ( Que ) memcpy( &buffer[sp], Que, bytes );
        sp += bytes;
    }
    else
    {
		cout << "\nERROR: Desbordamiento de pila.";
//        *ip = NULL;
        exit ( EXIT_FAILURE );
    }
}

// SAG: desapilar 'bytes' octetos de la pila
void *Pila::desapilar( t_pila bytes )
{
    if( bytes > sp )
	{
		cout << "\nERROR: Pila vacia.";
//        *ip = NULL;
        exit ( EXIT_FAILURE );
	}
	else
	{
        sp -= bytes;
        return &buffer[sp];
	}
    return NULL;
}

void Pila::valori( t_pila dir )
{
    apilar( &dir, TAM_DIR );
}

void Pila::valord( t_pila dir, t_pila tam )
{
    apilar( &buffer[dir], tam );
}

void Pila::asig( void *valor, t_pila bytes )
{
    t_pila dir = *(t_pila *)desapilar( TAM_DIR );
    memcpy( &buffer[dir], valor, bytes );
}

