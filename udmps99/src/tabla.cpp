/*
tabla.cpp - tabla de símbolos
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

// $JK200910 cambio linea
//#include <string.h>
#include <cstring>
#include "tabla.h"


EntradaTabla::EntradaTabla( const char *ident, byte tipo, int offset )
{
	sgte = NULL;
	this->tipo = tipo;
	this->offset = offset;
	this->ident = new char[ strlen( ident ) + 1 ];
	strcpy( this->ident, ident );
}

EntradaTabla::EntradaTabla()
{
	sgte = NULL;
	tipo = 0;
	ident = NULL;
}

EntradaTabla::~EntradaTabla()
{
	delete( ident );
}

byte EntradaTabla::Tipo( void )
{
	return( tipo );
}

void EntradaTabla::ActualizarTipo( byte tipo )
{
	this->tipo = tipo;
}

int EntradaTabla::OffSet( void )
{
	return( offset );
}

void EntradaTabla::ActualizarOffSet( int offset )
{
	this->offset = offset;
}

const char* EntradaTabla::Ident( void )
{
	return( ident );
}

Etiqueta::Etiqueta( const char *ident, byte tipo, Instr *pinstr ) :
		EntradaTabla( ident, tipo )
{
	this->pinstr = pinstr;
}

Etiqueta::~Etiqueta()
{
}

Instr* Etiqueta::PtrInstr( void )
{
	return( pinstr );
}

Tabla::Tabla()
{
	lista_entradas = NULL;
	ult_entrada = NULL;
}

Tabla::~Tabla()
{
	EntradaTabla *entrada;

	entrada = lista_entradas;
	while( entrada != NULL )
	{
		lista_entradas = entrada->sgte;
		delete( entrada );
		entrada = lista_entradas;
	}
}

void Tabla::InsertarEntrada( EntradaTabla *entrada )
{
	if( entrada != NULL )
	{
		entrada->sgte = lista_entradas;
		lista_entradas = entrada;
	}
}

EntradaTabla * Tabla::InsertarVariable( const char *ident, byte tipo, word offset )
{
    EntradaTabla *var = new EntradaTabla ( ident, tipo, offset );
	InsertarEntrada( var );
	return( var );
}

Etiqueta* Tabla::InsertarEtiqueta( const char *ident, byte tipo, Instr *pinstr )
{
	Etiqueta *etiq;

	etiq = new Etiqueta( ident, tipo, pinstr );
	InsertarEntrada( etiq );
	return( etiq );
}

EntradaTabla* Tabla::BuscarIdent( const char *ident )
{
/*
    EntradaTabla *entrada;
	int encontrado = 0;

	entrada = lista_entradas;
	if( entrada != NULL )
		encontrado = strcmpi( ident, entrada->ident ) == 0;
    while( entrada != NULL && !encontrado )
	{
		entrada = entrada->sgte;
		encontrado = strcmpi( ident, entrada->ident ) == 0;
	}
	return( entrada );
*/
    // SAG: optimizaci¢n de c¢digo
    EntradaTabla *entrada = lista_entradas;
    while ( entrada )
    {
// $JK200910 cambio linea
//      if ( !strcmpi( ident, entrada->ident ) )
        if ( !strcmp( ident, entrada->ident ) )
            return entrada;
        entrada = entrada->sgte;
    }
    return NULL;
}

// $JK201103 hay que manejar bien la lista ligada...
/*
void Tabla::BorrarDeclLocales( void )
{
	EntradaTabla *entr, *ant;

	ant = NULL;
	entr = lista_entradas;
	while( entr != NULL )
	{
		if( entr->tipo & LOCAL )
		{
|*
            ant->sgte = entr->sgte;
			if( entr == lista_entradas )
				lista_entradas = entr->sgte;
*|
            // SAG: soluci¢n de una posible asignaci¢n de puntero nulo...
			if( entr == lista_entradas )
				lista_entradas = entr->sgte;
            else
                // si no es la primera entrada (si ant != NULL...)
                ant->sgte = entr->sgte;

            delete( entr );
		}
		else
			ant = entr;
		entr = ant->sgte;
	}
}
*/
void Tabla::BorrarDeclLocales( void )
{
	EntradaTabla *entr, **ant;

	ant = &lista_entradas;
	entr = lista_entradas;
	while( entr != NULL )
	{
		if( entr->tipo & LOCAL )
		{
			if( entr == lista_entradas )
				lista_entradas = entr->sgte; //JK: ant sigue apuntando a lista_entradas
			else
				*ant = entr->sgte;
			delete( entr );
		}
		else
			ant = &(entr->sgte);
		entr = *ant;
	}
}
