/*
codinter.cpp - código intermedio
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

// $JK200910 cambio 5 lineas...
//#include <iostream.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include <stdio.h>
// $JK200910 ... por 5 lineas...
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdio>
// $JK200910 ... hasta aqui
// 201102 EGS+LRG+JK: corrigiendo warnings, línea nueva
#include <fstream>
// $JK200910 quito linea
//#include <conio.h>
// $JK200910 cambio 2 lineas...
//#include "codinter.h"
//#include "tokens.h"
// $JK200910 ... por 2 lineas...
#include "codinter.h"
#include "tokens.h"
// $JK200910 ... hasta aqui

// $JK200910 linea nueva
using namespace std;

const char *ErrProgFin = "ERROR FATAL: Programa finalizado incorrectamente.";

// SAG: Error de etiqueta no declarada (para no escribirla N veces)
void ErrEtiq( char *QueEtiq ) {
    cout << "ERROR: etiqueta <" << QueEtiq <<"> no declarada";
}

// 201102 EGS+LRG+JK: corrigiendo warnings
//char *token_names[] = {     // ver TOKENS.H
const char *token_names[] = {     // ver TOKENS.H
    "",                                             // 0x00
    "",                                             // 0x01
    "ident",                                        // 0x02
    "etiqueta",                                     // 0x03
    "num_ent",                                      // 0x04
    "num_real",                                     // 0x05
    "num_byte",                                     // 0x06     // SAG
    "string",                                       // 0x07
    "+",                                            // 0x08
    "-",                                            // 0x09
    "*",                                            // 0x0a
    "/",                                            // 0x0b
    "^",                                            // 0x0c
    "+r",                                           // 0x0d
    "-r",                                           // 0x0e
    "*r",                                           // 0x0f
    "/r",                                           // 0x10
    "^r",                                           // 0x11
    "+b",                                           // 0x12     // SAG
    "-b",                                           // 0x13     // SAG
    "neg",                                          // 0x14     // SAG
    "negr",                                         // 0x15     // SAG
    "negb",                                         // 0x16     // SAG
    "<",                                            // 0x17
    ">",                                            // 0x18
    "<=",                                           // 0x19
    ">=",                                           // 0x1a
    "==",                                           // 0x1b
    "!=",                                           // 0x1c
    "<r",                                           // 0x1d
    ">r",                                           // 0x1e
    "<=r",                                          // 0x1f
    ">=r",                                          // 0x20
    "==r",                                          // 0x21
    "!=r",                                          // 0x22
    "<b",                                           // 0x23     // SAG
    ">b",                                           // 0x24     // SAG
    "<=b",                                          // 0x25     // SAG
    ">=b",                                          // 0x26     // SAG
    "==b",                                          // 0x27     // SAG
    "!=b",                                          // 0x28     // SAG
    "and",                                          // 0x29
    "or",                                           // 0x2a
    "not",                                          // 0x2b     // SAG
    "intareal",                                     // 0x2c
    "intabyte",                                     // 0x2d
    "byteaint",                                     // 0x2e
    "sqrt",                                         // 0x2f
    "sin",                                          // 0x30
    "cos",                                          // 0x31
    "tan",                                          // 0x32
    "asin",                                         // 0x33
    "acos",                                         // 0x34
    "atan",                                         // 0x35
    "exp",                                          // 0x36
    "log",                                          // 0x37
    "ln",                                           // 0x38
    "round",                                        // 0x39
    "trunc",                                        // 0x3a
    "ins",                                          // 0x3b
    "desapilar",                                    // 0x3c
    "insi",                                         // 0x3d
    "desapilari",                                   // 0x3e
    "insr",                                         // 0x3f
    "desapilarr",                                   // 0x40
    "insb",                                         // 0x41
    "desapilarb",                                   // 0x42
    "copiari",                                      // 0x43
    "copiarr",                                      // 0x44
    "copiarb",                                      // 0x45
    "cambiarii",                                    // 0x46
    "cambiarir",                                    // 0x47
    "cambiarib",                                    // 0x48
    "cambiarri",                                    // 0x49
    "cambiarrr",                                    // 0x4a
    "cambiarrb",                                    // 0x4b
    "cambiarbi",                                    // 0x4c
    "cambiarbr",                                    // 0x4d
    "cambiarbb",                                    // 0x4e
    "si_cierto_ir_a",                               // 0x4f
    "si_falso_ir_a",                                // 0x50
    "ir_a",                                         // 0x51
    "etiq",                                         // 0x52
    "leeri",                                        // 0x53
    "leerr",                                        // 0x54
    "leerb",                                        // 0x55
    "escribiri",                                    // 0x56
    "escribirr",                                    // 0x57
    "escribirb",                                    // 0x58     // SAG
    "escribirln",                                   // 0x59
    "escribirs",                                    // 0x5a
    "inicio",                                       // 0x5b
    "fin",                                          // 0x5c
    "etiqv",                                        // 0x5d
    "etiqi",                                        // 0x5e
    "etiqr",                                        // 0x5f
    "etiqb",                                        // 0x60
    "globali",                                      // 0x61
    "globalr",                                      // 0x62
    "globalb",                                      // 0x63
    "locali",                                       // 0x64
    "localr",                                       // 0x65
    "localb",                                       // 0x66
    "parami",                                       // 0x67
    "paramr",                                       // 0x68
    "paramb",                                       // 0x69
    "valord",                                       // 0x6a
    "valori",                                       // 0x6b
    ":=",                                           // 0x6c
    ":=r",                                          // 0x6d
    ":=b",                                          // 0x6e
    "llamar",                                       // 0x6f
    "ret",                                          // 0x70
    "ponerbase",                                    // 0x71
    "cogerbase",                                    // 0x72
    "",     // 0x73 ...
    ""
};


Instr::Instr( int cod, integer val_int )
{
	this->cod = cod;
	flag = 0;
	atr.val_int = val_int;
	sgte = NULL;
	ident = NULL;
}

Instr::Instr( int cod, byte val_byte )
{
	this->cod = cod;
	flag = 0;
    atr.val_byte = val_byte;
	sgte = NULL;
	ident = NULL;
}


Instr::Instr( int cod, real val_real )
{
	this->cod = cod;
	flag = 0;
	atr.val_real = val_real;
	sgte = NULL;
	ident = NULL;
}

Instr::Instr( int cod, const char *ident )
{
	this->cod = cod;
	flag = 0x80;
	if( ident != NULL )
		atr.ident = strdup( ident );
	else
		atr.ident = NULL;
	this->ident = NULL;
	sgte = NULL;
}

Instr::Instr( int cod, int offset, byte flag, const char *ident )
{
	this->ident = strdup( ident );
	this->cod = cod;
	this->atr.val_int = offset;
	this->flag = flag;
	sgte = NULL;
}

Instr::~Instr()
{
    if ( (flag & 0x80) && (atr.ident != NULL) )
		delete( atr.ident );
	delete( ident );
	delete( sgte );
}

CodInter::CodInter( Tabla *tabla, char *fich, int debug )
// 201102 EGS+LRG+JK: f_log should be initialized to 0. Otherwise no way for the program to know whether its opened and valid or not
// 201102 EGS+LRG+JK: comentada la siguiente línea cuando f_log se ha convertido en un ofstream
//	: f_log(0)
{
/*
    char f[256];

    if( debug )
	{
        strcpy( f, fich );
		strcat( f, ".log" );
		f_log = fopen( f, "wt" );
	}
	strcpy( f, fich );
	strcat( f, ".mpn" );
	f_mpn = fopen( f, "wt" );
    strcpy( f, fich );
	strcat( f, ".out" );
	f_out = fopen( f, "wt" );

    lista_instr = ult_instr = instr_act = inicio = NULL;
	pila = new Pila( &instr_act );
	this->tabla = tabla;
	this->debug = debug;
*/
    // SAG: optimizaci¢n (omito la variable 'debug' de la clase)
// $JK200910 NOOOOO se puede omitir la variable 'debug', ver siguiente cambio
    char *f = new char[strlen(fich)+4+1];

// $JK200910 linea nueva
    this->debug = debug;    if( debug )
	{
        sprintf( f, "%s.%s", fich, "log" );
// 201102 EGS+LRG+JK: corrigiendo warnings
//		f_log = fopen( f, "wt" );
		f_log.open( f );
	}
    sprintf( f, "%s.%s", fich, "mpn" );
// 201102 EGS+LRG+JK: corrigiendo warnings
//	f_mpn = fopen( f, "wt" );
	f_mpn.open( f );
    sprintf( f, "%s.%s", fich, "out" );
// 201102 EGS+LRG+JK: corrigiendo warnings
//	f_out = fopen( f, "wt" );
	f_out.open( f );
    delete f;

    lista_instr = ult_instr = instr_act = inicio = NULL;
	pila = new Pila( &instr_act );
	this->tabla = tabla;
}

CodInter::~CodInter()
{
//    if( debug ) fclose( f_log );
    // SAG: no hace falta realizar la comprobaci¢n...
//    fclose( f_log );
// $JK200910 SSSSÍÍÍÍÍÍ hace falta realizar la comprobación, cambio linea anterior a siguiente
// 201102 EGS+LRG+JK: corrigiendo warnings
//  if( debug ) fclose( f_log );
	if( debug ) f_log.close();

// 201102 EGS+LRG+JK: corrigiendo warnings
//	fclose( f_out );
    f_out.close();
// $JK200910 quito linea (la pongo más adelante: ver)
//    fclose( f_mpn );
	delete( lista_instr );
	delete( pila );
}

Instr *CodInter::InsertarInstr( Instr* instr )
{
	if( ult_instr != NULL )
		ult_instr->sgte = instr;
	else
		lista_instr = instr;
	ult_instr = instr;
	if( instr->cod == INICIO )
		inicio = instr;
    return instr;
}

Instr* CodInter::InsInstrInicio( int cod, integer n )
{
	Instr *instr = NULL;

	if( inicio != NULL )
	{
		instr = new Instr( cod, n );
		instr->sgte = inicio->sgte;
		inicio->sgte = instr;
		if( inicio == ult_instr )
			ult_instr = instr;
	}
	return( instr );
}

Instr* CodInter::InsertarInstr( int cod, integer val_int )
{
// SAG
/*
    Instr *instr = new Instr( cod, val_int );
	InsertarInstr( instr );
	return( instr );
*/
    return InsertarInstr( new Instr( cod, val_int ) );
}

Instr* CodInter::InsertarInstr( int cod, byte val_byte )
{
// SAG
/*
    Instr *instr = new Instr( cod, val_byte );
	InsertarInstr( instr );
	return( instr );
*/
    return InsertarInstr( new Instr( cod, val_byte ) );
}

Instr* CodInter::InsertarInstr( int cod, real val_real )
{
// SAG
/*
    Instr *instr = new Instr( cod, val_real );
	InsertarInstr( instr );
	return( instr );
*/
    return InsertarInstr( new Instr( cod, val_real ) );
}

Instr* CodInter::InsertarInstr( int cod, int offset, unsigned char flag,
                                const char *ident )
{
// SAG
/*
    Instr *instr = new Instr( cod, offset, flag, ident );
	InsertarInstr( instr );
	return( instr );
*/
    return InsertarInstr( new Instr( cod, offset, flag, ident ) );
}

Instr* CodInter::InsertarInstr( int cod, const char *atr )
{
// SAG
/*
    Instr *instr = new Instr( cod, atr );
	InsertarInstr( instr );
	return( instr );
*/
    return InsertarInstr( new Instr( cod, atr ) );
}

void CodInter::EjecutarCodigo( void )
{
    instr_act = inicio;
	while( instr_act != NULL )
	{
//        if (debug) EscribirInstr();
        // SAG: ya no existe la variable 'debug'...
        // si el fichero '.log' se ha creado, escribir las instrucciones en ‚l
// 201102 EGS+LRG+JK: una vez más, el rollo incorrecto de creer que no existe la variable debug sigue dando problemas
//        if ( f_log ) EscribirInstr();
        if ( debug ) EscribirInstr();
		EjecutarInstr();
	}
}

void CodInter::EjecutarInstr( void )
{
    int sgte_instr = 1;
// SAG: es un tipo apuntador a pila
//    unsigned int bp;
    t_pila bp;
	Etiqueta *etiqueta;
	integer i1, i2;
	real r1, r2;
    byte b1, b2;

	switch( instr_act->cod )
	{
		case INS: pila->Ins( instr_act->atr.val_int ); break;
		case INSI: pila->InsInt( instr_act->atr.val_int ); break;
		case INSR: pila->InsReal( instr_act->atr.val_real ); break;
        case INSB: pila->InsByte(instr_act->atr.val_byte);break;
        case VALORD:
// SAG
/*
            if( instr_act->flag & GLOBAL )
				bp = 0;
            else
                bp = pila->BP();
*/
            bp = (instr_act->flag & GLOBAL) ? 0 : pila->BP();
            if ( (instr_act->flag & TIPO) == INT )
				pila->ValorDInt( bp+instr_act->atr.val_int );
            else if ( (instr_act->flag & TIPO) == REAL )
                pila->ValorDReal( bp+instr_act->atr.val_int );
            else
                pila->ValorDByte( bp+instr_act->atr.val_int );
			break;
		case VALORI:
// SAG
/*
            if( instr_act->flag & GLOBAL )
				bp = 0;
            else
                bp = pila->BP();
*/
            bp = (instr_act->flag & GLOBAL) ? 0 : pila->BP();
            if ( (instr_act->flag & TIPO) == INT )
				pila->ValorIInt( bp+instr_act->atr.val_int );
            else if ( (instr_act->flag & TIPO) == REAL )
                pila->ValorIReal( bp+instr_act->atr.val_int  );
            else
                pila->ValorIByte( bp+instr_act->atr.val_int  );
			break;
		case LEERI:
			cin >> i1;
			pila->InsInt( i1 );
// SAG: leer un entero LARGO
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%ld\n", i1 );
			f_out << i1 << endl;
			break;
		case LEERR:
			cin >> r1;
			pila->InsReal( r1 );
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%g\n", r1 );
			f_out << r1 << endl;
			break;
        case LEERB:
            cin >> b1;
            pila->InsByte( b1 );
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%c\n", b1 );
			f_out << b1 << endl;
			break;
		case ESCRIBIRR:
            r1 = pila->DesapilarReal();
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%g", r1 );
			f_out << r1;
            cout << r1;
//            printf( "%g", r1 );
            break;
		case ESCRIBIRI:
            i1 = pila->DesapilarInt();
// SAG: escribir un entero LARGO
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%ld", i1 );
			f_out << i1;
            cout << i1;
//            printf( "%ld", i1 );
            break;
        case ESCRIBIRB:                                 // SAG: nuevo
            b1 = pila->DesapilarByte();
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%c", b1 );
            f_out << b1;
            cout << b1;
            break;
        case ESCRIBIRS:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "%s", instr_act->atr.ident );
            f_out << instr_act->atr.ident;
            cout << instr_act->atr.ident;
            break;
		case ESCRIBIRLN:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_out, "\n" );
            f_out << "\n" ;
            cout << "\n" ;
            break;
		case DESAPILARI: pila->DesapilarInt(); break;
		case DESAPILARR: pila->DesapilarReal(); break;
        case DESAPILARB: pila->DesapilarByte(); break;
        case DESAPILAR: pila->Desapilar( instr_act->atr.val_int ); break;
		case COPIARI: pila->CopiarInt(); break;
		case COPIARR: pila->CopiarReal(); break;
        case COPIARB: pila->CopiarByte(); break;
		case INICIO: break;
		case PONERBASE: pila->PonerBase(); break;
		case COGERBASE: pila->CogerBase(); break;
		case FIN:
// SAG: optimizaci¢n de c¢digo
//            if( strcmp( instr_act->atr.ident, "" ) != 0 )
            if( instr_act->atr.ident[0] != '\0' )
            {
// 201102 EGS+LRG+JK: corrigiendo warnings
//              fprintf( f_out, ErrProgFin );
                f_out << ErrProgFin;
                cout << ErrProgFin;
            }
            sgte_instr = 0;
			instr_act = NULL;
			break;
		case ASIG_ENT: pila->AsigInt(); break;
		case ASIG_REAL: pila->AsigReal(); break;
        case ASIG_BYTE: pila->AsigByte(); break;
		case CAMBIARII: pila->CambiarIntInt(); break;
        case CAMBIARIR: pila->CambiarIntReal(); break;
		case CAMBIARRI: pila->CambiarRealInt(); break;
		case CAMBIARRR: pila->CambiarRealReal(); break;
        case CAMBIARBB: pila->CambiarByteByte(); break;
        case CAMBIARBI: pila->CambiarByteInt(); break;
        case CAMBIARBR: pila->CambiarByteReal(); break;
		case CAMBIARRB: pila->CambiarRealByte(); break;
        case CAMBIARIB: pila->CambiarIntReal(); break;
		case INTAREAL: pila->IntAReal(); break;
//        case REALAINT: pila->RealAInt(); break;
        case BYTEAINT: pila->ByteAInt(); break;
        case INTABYTE: pila->IntAByte(); break;
        case ROUND: pila->InsInt( integer( pila->DesapilarReal()+0.5 )); break;
		case TRUNC: pila->RealAInt(); break;
		case SQRT: pila->InsReal( sqrt( pila->DesapilarReal() )); break;
		case SIN: pila->InsReal( sin( pila->DesapilarReal() )); break;
		case COS: pila->InsReal( cos( pila->DesapilarReal() )); break;
		case TAN: pila->InsReal( tan( pila->DesapilarReal() )); break;
		case ASIN: pila->InsReal( asin( pila->DesapilarReal() )); break;
		case ACOS: pila->InsReal( acos( pila->DesapilarReal() )); break;
		case ATAN: pila->InsReal( atan( pila->DesapilarReal() )); break;
		case EXP: pila->InsReal( exp( pila->DesapilarReal() )); break;
		case LOG: pila->InsReal( log10( pila->DesapilarReal() )); break;
		case LN: pila->InsReal( log( pila->DesapilarReal() )); break;

/*
  Modificado por JosuKa 20 de enero de 1999
		case OP_LOG_AND: pila->InsInt( pila->DesapilarInt() &&
							pila->DesapilarInt() ); break;
		case OP_LOG_OR: pila->InsInt( pila->DesapilarInt() ||
							pila->DesapilarInt() ); break;
*/
		case OP_LOG_AND:
// SAG: Los operadores l¢gicos deben de ser bytes (octetos)
/*
            i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
			pila->InsInt( i1 && i2 );
*/
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 && b2 );
            break;
		case OP_LOG_OR:
/*
            i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
			pila->InsInt( i1 || i2 );
*/
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 || b2 );
            break;

        case OP_LOG_NOT:
/*
            i1 = pila->DesapilarInt();
            pila->InsInt( !i1 );
*/
            b1 = pila->DesapilarByte();
            pila->InsByte( !b1 );
            break;
		case OP_ENT_SUMA:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
            pila->InsInt( i1 + i2 );
            break;
		case OP_ENT_RESTA:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();                        
            pila->InsInt( i1 - i2 );
            break;
        case OP_ENT_MULT:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();                        
            pila->InsInt( i1 * i2 );
            break;
		case OP_ENT_DIV:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
			pila->InsInt( i1 / i2 );
			break;
        case OP_ENT_EXP:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();                        
//          pila->InsInt( pow( i2, i1 ));	$JK200910 cambio (notese cambio orden argumentos, ¿bien?)
            pila->InsInt( (int)pow( (double)i1, (double)i2 ));
			break;
		case OP_REAL_SUMA:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
            pila->InsReal( r1 + r2 );
            break;
		case OP_REAL_RESTA:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
            pila->InsReal( r1 - r2 );
            break;
        case OP_REAL_MULT:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();                        
            pila->InsReal( r1 * r2 );
            break;
		case OP_REAL_DIV:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
			pila->InsReal( r1 / r2 );
			break;
        case OP_REAL_EXP:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();                        
            pila->InsReal( pow( r2, r1 ) );
			break;
        case OP_BYTE_SUMA:                          // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 + b2 );
            break;
        case OP_BYTE_RESTA:                         // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 - b2 );
            break;
		case OP_ENT_MENOR:
            i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
// SAG: Los operadores relacionales dejan en la pila un byte (un octeto)
//            pila->InsInt( i1 < i2 );
            pila->InsByte( i1 < i2 );
			break;
		case OP_ENT_MAYOR:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
//            pila->InsInt( i1 > i2 );
            pila->InsByte( i1 > i2 );
			break;
		case OP_ENT_MENORIGUAL:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
//            pila->InsInt( i1 <= i2 );
            pila->InsByte( i1 <= i2 );
			break;
		case OP_ENT_MAYORIGUAL:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
//            pila->InsInt( i1 >= i2 );
            pila->InsByte( i1 >= i2 );
			break;
/*
  Modificado por JosuKa 20 de enero de 1999

            case OP_ENT_IGUAL: pila->InsInt( pila->DesapilarInt() ==
							pila->DesapilarInt() ); break;
		case OP_ENT_DISTINTO: pila->InsInt( pila->DesapilarInt() !=
							pila->DesapilarInt() ); break;
*/

		case OP_ENT_IGUAL:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
//            pila->InsInt( i1 == i2 );
            pila->InsByte( i1 == i2 );
			break;
		case OP_ENT_DISTINTO:
			i2 = pila->DesapilarInt();
			i1 = pila->DesapilarInt();
//            pila->InsInt( i1 != i2 );
            pila->InsByte( i1 != i2 );
			break;

		case OP_REAL_MENOR:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
//            pila->InsInt( r1 < r2 );
            pila->InsByte( r1 < r2 );
			break;
		case OP_REAL_MAYOR:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
//            pila->InsInt( r1 > r2 );
            pila->InsByte( r1 > r2 );
			break;
		case OP_REAL_MENORIGUAL:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
//            pila->InsInt( r1 <= r2 );
            pila->InsByte( r1 <= r2 );
			break;
		case OP_REAL_MAYORIGUAL:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();
//            pila->InsInt( r1 >= r2 );
            pila->InsByte( r1 >= r2 );
			break;
        case OP_REAL_IGUAL:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();                        
//            pila->InsInt( r1 == r2 );
            pila->InsByte( r1 == r2 );
            break;
		case OP_REAL_DISTINTO:
			r2 = pila->DesapilarReal();
			r1 = pila->DesapilarReal();                        
//            pila->InsInt( r1 != r2 );
            pila->InsByte( r1 != r2 );
            break;
        case OP_BYTE_MENOR:                         // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 < b2 );
            break;
        case OP_BYTE_MAYOR:                         // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 > b2 );
            break;
        case OP_BYTE_MENORIGUAL:                    // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 <= b2 );
            break;
        case OP_BYTE_MAYORIGUAL:                    // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 >= b2 );
            break;
        case OP_BYTE_IGUAL:                         // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 == b2  );
            break;
        case OP_BYTE_DISTINTO:                      // SAG: nuevo
            b2 = pila->DesapilarByte();
            b1 = pila->DesapilarByte();
            pila->InsByte( b1 != b2);
            break;
		case OP_UNA_ENT:
            i1 = pila->DesapilarInt();
            pila->InsInt( -i1 );
            break;
		case OP_UNA_REAL:                
			r1 = pila->DesapilarReal();
            pila->InsReal( -r1 );
            break;
        case OP_UNA_BYTE:                           // SAG: nuevo
            b1 = pila->DesapilarByte();
            pila->InsByte( -b1 );
            break;
		case IR_A:
            etiqueta = ( Etiqueta * )tabla->BuscarIdent( instr_act->atr.ident );
			if( etiqueta != NULL )
			{
				sgte_instr = 0;
				instr_act = etiqueta->PtrInstr();
			}
			else
			{
                ErrEtiq( instr_act->atr.ident );
				instr_act = NULL;
			}
			break;
		case SI_CIERTO_IR_A:
			etiqueta = ( Etiqueta * ) tabla->BuscarIdent( instr_act->atr.ident );
			if( etiqueta != NULL )
			{
// SAG: En el control de flujo se realiza una comparaci¢n a nivel de byte
//                if( pila->DesapilarInt() != 0 )
                if( pila->DesapilarByte() != 0 )
				{
					sgte_instr = 0;
					instr_act = etiqueta->PtrInstr();
				}
			}
			else
			{
                ErrEtiq( instr_act->atr.ident );
				instr_act = NULL;
			}
			break;
		case SI_FALSO_IR_A:
            etiqueta = ( Etiqueta * )tabla->BuscarIdent( instr_act->atr.ident );
			if( etiqueta != NULL )
			{
//                if( pila->DesapilarInt() == 0 )
                if( pila->DesapilarByte() == 0 )
				{
					sgte_instr = 0;
					instr_act = etiqueta->PtrInstr();
				}
			}
			else
			{
                ErrEtiq( instr_act->atr.ident );
				instr_act = NULL;
			}
			break;
		case LLAMAR:
			etiqueta = ( Etiqueta * ) tabla->BuscarIdent( instr_act->atr.ident );
			if( etiqueta != NULL )
			{
				pila->InsIP();
				instr_act = etiqueta->PtrInstr();
			}
			else
			{
                ErrEtiq( instr_act->atr.ident );
				instr_act = NULL;
			}
			break;
		case ETIQ:
		case ETIQV:
		case ETIQR:
        case ETIQB:
        case ETIQI: break;
		case RET:
			pila->Ret( instr_act->atr.val_int );
			break;
	}
	if( instr_act != NULL && sgte_instr )
		instr_act = instr_act->sgte;
}

void CodInter::EscribirCodigo( void )
{
	Instr *instr;

	instr = lista_instr;
    while( instr != NULL )
	{
		switch( instr->cod )
		{
			case RET:
			case INS:
			case INSI:                        
			case DESAPILAR:
// SAG: INSI (entero largo)
// 201102 EGS+LRG+JK: corrigiendo warnings
//              fprintf( f_mpn, "%-20s%ld\n", token_names[instr->cod], instr->atr.val_int );
				f_mpn.width(20);
				f_mpn << left << token_names[instr->cod];
				f_mpn << instr->atr.val_int << endl;
				break;
			case INSR:
// 201102 EGS+LRG+JK: corrigiendo warnings
//				fprintf( f_mpn, "%-20s%f\n", token_names[instr->cod], instr->atr.val_real );
				f_mpn.width(20);
				f_mpn << left << token_names[instr->cod];
				f_mpn << instr->atr.val_real << endl;
				break;
			case INSB:
// 201102 EGS+LRG+JK: corrigiendo warnings
//				fprintf( f_mpn, "%-20s%c\n", token_names[instr->cod], instr->atr.val_byte );
				f_mpn.width(20);
				f_mpn << left << token_names[instr->cod];
				f_mpn << instr->atr.val_byte << endl;
				break;
            case ESCRIBIRS:
// 201102 EGS+LRG+JK: corrigiendo warnings
//              fprintf( f_mpn, "%-20s\"%s\"\n", token_names[instr->cod], instr->atr.ident );
				f_mpn.width(20);
				f_mpn << left << token_names[instr->cod];
				f_mpn << "\"" << instr->atr.ident << "\"" << endl;
                break;
			case IR_A:
			case SI_CIERTO_IR_A:
			case SI_FALSO_IR_A:
			case LLAMAR:
			case ETIQ:
			case ETIQR:
			case ETIQI:
			case ETIQV:
            case ETIQB:
			case FIN:
// 201102 EGS+LRG+JK: corrigiendo warnings
//				fprintf( f_mpn, "%-20s%s\n", token_names[instr->cod], instr->atr.ident );
				f_mpn.width(20);
				f_mpn << left << token_names[instr->cod];
				f_mpn << instr->atr.ident << endl;
				break;
			case VALORD:
			case VALORI:
// SAG
//                char cad[256];
// 201102 EGS+LRG+JK: corrigiendo warnings
//#define MAXLONGNUM  15
//                char cad[MAXLONGNUM+3+1];

// 201102 EGS+LRG+JK: corrigiendo warnings: añadido
				f_mpn.width(20);
				f_mpn << left << token_names[instr->cod];
				f_mpn << "[";
                if(( instr->flag & AMBITO ) == GLOBAL )
// 201102 EGS+LRG+JK: corrigiendo warnings: hasta aquí
// 201102 EGS+LRG+JK: corrigiendo warnings
//                  sprintf( cad, "%ld", instr->atr.val_int );
					f_mpn << instr->atr.val_int;
				else
// 201102 EGS+LRG+JK: corrigiendo warnings
//                  sprintf( cad, "%ld+BP", instr->atr.val_int );
					f_mpn << instr->atr.val_int << "+BP";
// 201102 EGS+LRG+JK: corrigiendo warnings
//              fprintf( f_mpn, "%-20s[%s]\n", token_names[instr->cod], cad );
				f_mpn << "]" << endl;
				break;
            default:
// 201102 EGS+LRG+JK: corrigiendo warnings
//              fprintf( f_mpn, "%s\n", token_names[instr->cod] );
				f_mpn << token_names[instr->cod] << endl;
		}
		instr = instr->sgte;
	}
// $JK200910 linea nueva (quitada de un lugar anterior: ver; objetivo: que el .MPN se cierre cuanto antes)
// 201102 EGS+LRG+JK: corrigiendo warnings
//  fclose( f_mpn );
    f_mpn.close();
}

void CodInter::EscribirInstr( void )
{
	switch( instr_act->cod )
	{
		case RET:
		case INS:
		case INSI:
		case DESAPILAR:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%-20s%ld\n", token_names[instr_act->cod], instr_act->atr.val_int );
			f_log.width(20);
			f_log << left << token_names[instr_act->cod];
			f_log << instr_act->atr.val_int << endl;
			break;
		case INSR:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%-20s%f\n", token_names[instr_act->cod], instr_act->atr.val_real );
			f_log.width(20);
			f_log << left << token_names[instr_act->cod];
			f_log << instr_act->atr.val_real << endl;
			break;
		case INSB:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%-20s%c\n", token_names[instr_act->cod], instr_act->atr.val_byte );
			f_log.width(20);
			f_log << left << token_names[instr_act->cod];
			f_log << instr_act->atr.val_byte << endl;
            break;
		case IR_A:
		case SI_CIERTO_IR_A:
		case SI_FALSO_IR_A:
		case LLAMAR:
		case ETIQ:
		case ETIQR:
		case ETIQI:
        case ETIQB:
		case ETIQV:
		case FIN:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%-20s%s\n", token_names[instr_act->cod], instr_act->atr.ident );
			f_log.width(20);
			f_log << left << token_names[instr_act->cod];
			f_log << instr_act->atr.ident << endl;
			break;
		case VALORD:
		case VALORI:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%-20s%s\n", token_names[instr_act->cod], instr_act->ident );
			f_log.width(20);
			f_log << left << token_names[instr_act->cod];
			f_log << instr_act->ident << endl;
			break;
        case ESCRIBIRS:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%-20s\"%s\"\n", token_names[instr_act->cod], instr_act->atr.ident );
			f_log.width(20);
			f_log << left << token_names[instr_act->cod];
			f_log << "\"" << instr_act->atr.ident << "\"" << endl;
            break;
        default:
// 201102 EGS+LRG+JK: corrigiendo warnings
//          fprintf( f_log, "%s\n", token_names[instr_act->cod] );
			f_log << token_names[instr_act->cod] << endl;
	}
}
