/*
maqpila.cpp - máquina de pila
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

// $JK200910 dos lineas nuevas
#include <iostream>
#include <cstdio>
// $JK200910 cambio linea
//#include <fstream.h>
#include <fstream>
// $JK200910 quito linea
//#include <io.h>
#include <fcntl.h>
// $JK200910 cambio 2 lineas...
//#include <string.h>
//#include <stdlib.h> 	// itoa()
// $JK200910 ... por 2 lineas...
#include <cstring>
#include <cstdlib> 	// itoa()
// $JK200910 ... hasta aqui
#include "maqpila.h"
#include "tokens.h"
#include "tabla.h"

// $JK200910 linea nueva
using namespace std;

// 201102 EGS+LRG+JK: corrigiendo warnings
//const char *ErrIdDup    = "Identificador duplicado.";
//const char *ErrNoVal    = "Instrucci¢n no valida.";
//const char *ErrSin      = "Error sint ctico.";
//const char *ErrByte     = "El n£mero debe estar comprendido entre 0 y 255";
//const char *ErrNoDecl   = "Identificador no declarado";
//const char *ErrVar      = "El identificador debe ser una variable";
//const char *ErrIdentDup = "Identificador duplicado.";
const char *ErrIdDup    = "identificador duplicado";
const char *ErrNoVal    = "instrucción no válida";
const char *ErrSin      = "error sintáctico";
const char *ErrByte     = "el número debe estar comprendido entre 0 y 255";
const char *ErrNoDecl   = "identificador no declarado";
const char *ErrVar      = "el identificador debe ser una variable";
const char *ErrIdentDup = "identificador duplicado";

extern char *linea;
// 201102 EGS+LRG+JK: corrigiendo warnings
//FILE *fich_err;
ofstream f_err;

UdLexica::UdLexica( byte token, const char *lexema )
{
	this->token = token;
	this->lexema = strdup( lexema );
}

UdLexica::~UdLexica()
{
	delete( lexema );
}

byte UdLexica::Token( void )
{
	return( token );
}

const char* UdLexica::Lexema( void )
{
	return( lexema );
}

// SAG: comprueba si un fichero existe (devuelve 1) o no (devuelve 0)
int fileexist( const char *file )
{
// 201102 EGS+LRG+JK: quitando obsolescencias
//// $JK200910 cambio linea
////	int handle = open( file, O_TEXT );
//	int handle = open( file, O_RDONLY );
//	if ( handle == -1 )
//		return 0;
//// $JK200910 quito 2 lineas, no compila en DJGPP/gpp4.2.3
////	else
////		close( handle );
//	return 1;
	ifstream fin(file); // intenta abrir el archivo
	return !fin.fail(); // devuelve true o false dependiendo del failbit
}

MaqPila::MaqPila( char *f, int log )
{
	// SAG: inicializaci¢n de variables din micas
    fich        = strdup( f );
    udlexact    = NULL;
	sgteudlex	= NULL;
	codinter	= NULL;
	tabla		= NULL;
	yylex		= NULL;
// $JK200910 cambio 2 lineas
//	fb			= NULL;
//	iostr		= NULL;
// $JK200910 ... por 2 lineas...
	isb		= NULL;
	istr		= NULL;
// $JK200910 ... hasta aqui
	error		= 0;

	// SAG: hay que asignar memoria a las variables din micas...
	char *fmpv = new char[strlen(f)+4+1];

	// SAG: si existe el fichero .MPV, ...
	sprintf( fmpv, "%s.%s", f, "mpv" );

	if ( fileexist( fmpv ) )
	{
		sprintf( fmpv, "%s.%s", f, "err" );
// 201102 EGS+LRG+JK: corrigiendo warnings
//		fich_err = fopen( fmpv, "w" );
		f_err.open( fmpv );

		offset_local = offset_global = 0;
		tabla = new Tabla();
		codinter = new CodInter( tabla, f, log );

		sprintf( fmpv, "%s.%s", f, "mpv" );
// $JK200910 cambio 4 lineas...
//		yyin = open( fmpv, O_TEXT );
//		fb = new filebuf( yyin );
//		iostr = new iostream( fb );
//		yylex = new yyFlexLexer( iostr );
// $JK200910 ... por 4 lineas...
		filestr.open( fmpv );
		isb = filestr.rdbuf();
		istr = new istream( isb );
		yylex = new yyFlexLexer( istr );
// $JK200910 ... hasta aqui
	}
	else
		error = 1;
	delete fmpv;
}

MaqPila::~MaqPila()
{
	delete( tabla );
	delete( codinter );
	delete( yylex );
// $JK200910 cambio
//	delete( fb );
//	delete( isb );	$JK200910 da SIGABRT, por lo que lo quito
// $JK200910 cambio
//	delete( iostr );
	delete( istr );
	delete( sgteudlex );
	delete( udlexact );
// 201102 EGS+LRG+JK: corrigiendo warnings
//	delete( linea );
	free( linea );
// $JK200910 cambio
//	close( yyin );
	filestr.close();
/* $JK200910 quito lineas...
// SAG: si el fichero de errores tiene tama¤o 0, no hay errores (borrarlo)
    if ( !filelength( fich_err->fd ) )
    {
        fclose (fich_err);
        char *cad = new char[strlen(fich)+4+1];
        sprintf( cad, "%s.%s", fich , "err");
        remove( cad );
        delete cad;
    }
    else
   $JK200910 ... hasta aqui */
// 201102 EGS+LRG+JK: corrigiendo warnings
// 201102 EGS+LRG+JK: quitando warnings
//  if( fich_err )
//        fclose (fich_err);
	if( !error ) f_err.close();
// 201102 EGS+LRG+JK: quitando warnings
//    delete fich;
    free( fich );
}

//void MaqPila::Error( char *err  )
void MaqPila::Error( const char *err  )
{
// SAG
//	  char l[3];
// 201102 EGS+LRG+JK: corrigiendo warnings
//	cout << "\n" << linea;
//	cout << "\nERROR #" << yylex->lineno() << ": " << err;
	cout << linea << endl;
	cout << "Línea #" << yylex->lineno() << ": ERROR : " << err << endl;

//	  fprintf (fich_err,"\n");
//	  fprintf(fich_err, linea);
//	  fprintf(fich_err,"\nERROR #");
// 201102 EGS+LRG+JK: corrigiendo warnings
//	fprintf( fich_err, "\n"
//					   "%s\n"
//					   "ERROR #", linea );
	f_err << linea << endl;
	f_err << "Línea #" << yylex->lineno() << ": ERROR : " << err << endl;
//	  itoa( yylex->lineno(), l, 10 );
//	  fprintf(fich_err,l);
//	  fprintf(fich_err,": ");
//	  fprintf(fich_err,err);
// 201102 EGS+LRG+JK: corrigiendo warnings, esto sobra porque el anterior fprintf no hacia nada
//	fprintf( fich_err, "%i: %s", yylex->lineno(), err );

//	  delete( this );
	exit( EXIT_FAILURE );
}

void MaqPila::Ejecutar( int check_only )
{
	// SAG: sobra esta variable
//	  char linea[256];

	// Realizamos el analisis sintactico
	SgteUdLexica();
	Programa();
	codinter->EscribirCodigo();
	// Ejecutamos el codigo intermedio
	if ( !check_only )
		codinter->EjecutarCodigo();
}

void MaqPila::DeclLocales( void )
{
    EntradaTabla *ident;
// 201102 EGS+LRG+JK: the type hell; creemos que debe ser de tipo word
//	long total_bytes = 0, num_bytes;
	word total_bytes = 0, num_bytes;
	byte tipo, token;

	offset_local = 0;
	Parear( EOLN );
	while( sgteudlex->Token() == EOLN ) Avanzar();
	token = sgteudlex->Token();
	while( token == LOCALI || token == LOCALR || token == LOCALB)
	{
		switch( token )
		{
			case LOCALI:
				tipo = INT | LOCAL | ID_VAR;
				num_bytes = TAM_INT;
				break;
			case LOCALR:
				tipo = REAL | LOCAL | ID_VAR;
				num_bytes = TAM_REAL;
				break;
			case LOCALB:
				tipo = BYTE | LOCAL | ID_VAR;
				num_bytes = TAM_BYTE;
				break;
        }
		Avanzar();
		Parear( IDENT );
		ident = tabla->BuscarIdent( udlexact->Lexema() );
        if ( ident != NULL && (( ident->Tipo() & AMBITO ) != GLOBAL ) )
//            Error( "Identificador duplicado" );
            Error( ErrIdDup );
		else
		{
			tabla->InsertarVariable( udlexact->Lexema(), tipo, offset_local );
			offset_local += num_bytes;
			total_bytes += num_bytes;
		}
		Parear( EOLN );
		while( sgteudlex->Token() == EOLN ) Avanzar();
		token = sgteudlex->Token();
	}
	if( total_bytes != 0 )
// 201102 EGS+LRG+JK: the type hell; no hay previsto InsertarInstr para tipo word, así que forzamos a integer (obviamente no es muy correcto)
//		codinter->InsertarInstr( INS, total_bytes );
		codinter->InsertarInstr( INS, (integer)total_bytes );
}

void MaqPila::DeclParametros( void )
{
	EntradaTabla *ident;
	word num_bytes;
	byte tipo, token;

	Parear( EOLN );
    while ( sgteudlex->Token() == EOLN ) Avanzar();
	token = sgteudlex->Token();
	if( token == PARAMI || token == PARAMR || token == PARAMB )
	{
		switch( token )
		{
			case PARAMI:
				tipo = INT | LOCAL | ID_VAR;
				num_bytes = TAM_INT;
				break;
			case PARAMR:
				tipo = REAL | LOCAL | ID_VAR;
				num_bytes = TAM_REAL;
				break;
			case PARAMB:
				tipo = BYTE | LOCAL | ID_VAR;
				num_bytes = TAM_BYTE;
				break;
        }
		Avanzar();
		Parear( IDENT );
		ident = tabla->BuscarIdent( udlexact->Lexema() );
		if( ident != NULL && (( ident->Tipo() & AMBITO ) != GLOBAL ))
//            Error( "Identificador duplicado" );
            Error( ErrIdDup );
		else
		{
			ident = tabla->InsertarVariable( udlexact->Lexema(), tipo, offset_local );
			offset_local += num_bytes;
			DeclParametros();
			ident->ActualizarOffSet( ident->OffSet()-offset_local-TAM_DIR-TAM_PTR );
		}
	}
}

void MaqPila::Programa( void )
{
	while( sgteudlex->Token() != INICIO )
		Declaracion();
	Avanzar();
	codinter->InsertarInstr( INICIO );
//JK: en la nueva concepción de máquina de pila UDMPs99
//    no tienen sentido las variables locales (solo para
//    subprogramas)
//        codinter->InsertarInstr( PONERBASE );
//	DeclLocales();
//FinJK.
	while( sgteudlex->Token() != EOFL )
		Instruccion();
	Parear( EOFL );
	if( offset_global != 0 )
	{
// 201103 EGS+LRG+JK: esta instruccion no existe en el mpv, pero tampoco hace falta imprimirla en la variable linea; lo quitamos
//		sprintf( linea, "\tins %d", offset_global );
		codinter->InsInstrInicio( INS, offset_global );
	}
}

void MaqPila::DeclFuncion( void )
{
	byte token;
// 201102 EGS+LRG+JK: corrigiendo warnings
//	int num_bytes;
	int num_bytes = 0;
	Etiqueta *etiqueta;

	token = sgteudlex->Token();
	if( token == ETIQV || token == ETIQB || token == ETIQI || token == ETIQR )
	{
		Avanzar();
		Parear( IDENT );
		etiqueta = ( Etiqueta* )tabla->BuscarIdent( udlexact->Lexema() );
		if( etiqueta != NULL )
//            Error( "Identificador duplicado" );
            Error( ErrIdDup );
		else
		{
			switch( token )
			{
				case ETIQV:
					num_bytes = 0;
					etiqueta = tabla->InsertarEtiqueta( udlexact->Lexema(),
							ID_ETIQ | GLOBAL, codinter->InsertarInstr( ETIQV, udlexact->Lexema() ));
					break;
				case ETIQR:
					num_bytes = TAM_REAL;
					etiqueta = tabla->InsertarEtiqueta( udlexact->Lexema(),
							ID_VAR | REAL , codinter->InsertarInstr( ETIQR,	udlexact->Lexema() ));
					break;
				case ETIQI:
					num_bytes = TAM_INT;
					etiqueta = tabla->InsertarEtiqueta( udlexact->Lexema(),
							ID_VAR | INT , codinter->InsertarInstr( ETIQI, udlexact->Lexema() ));
					break;
				case ETIQB:
					num_bytes = TAM_BYTE;
					etiqueta = tabla->InsertarEtiqueta( udlexact->Lexema(),
							ID_VAR | BYTE , codinter->InsertarInstr( ETIQB, udlexact->Lexema() ));
					break;

			}
			offset_local = 0;
			DeclParametros();
			etiqueta->ActualizarOffSet( -offset_local-num_bytes-TAM_DIR-TAM_PTR );
			while( sgteudlex && sgteudlex->Token() != FIN )
				Instruccion();
			etiqueta->ActualizarTipo( ( etiqueta->Tipo() & 0x3F ) | ID_ETIQ );
			tabla->BorrarDeclLocales();
			Avanzar();
			Parear( IDENT );
//			if( strcmpi( etiqueta->Ident(), udlexact->Lexema() ) != 0 )	$JK200910 cambio
			if( strcmp( etiqueta->Ident(), udlexact->Lexema() ) != 0 )
//                Error( "Identificador no valido" );
                Error( ErrNoVal );
			codinter->InsertarInstr( FIN, udlexact->Lexema() );
			Parear( EOLN );
		}
	}
}

void MaqPila::Declaracion( void )
{
	EntradaTabla *ident;
	byte token;

	token = sgteudlex->Token();
	switch( token )
	{
		case EOLN:	while( sgteudlex->Token() == EOLN ) Avanzar(); break;
		case GLOBALI:
			Avanzar();
			Parear( IDENT );
			ident = tabla->BuscarIdent( udlexact->Lexema() );
            if( ident != NULL )
//                Error( "Identificador duplicado" );
                Error( ErrIdDup );
			else
			{
				tabla->InsertarVariable( udlexact->Lexema(),
						ID_VAR | INT | GLOBAL, offset_global );
				offset_global += TAM_INT;
			}
			Parear( EOLN );
			break;
		case GLOBALR:
			Avanzar();
			Parear( IDENT );
			ident = tabla->BuscarIdent( udlexact->Lexema() );
			if( ident != NULL )
//                Error( "Identificador duplicado" );
                Error( ErrIdDup );
			else
			{
				tabla->InsertarVariable( udlexact->Lexema(),
						ID_VAR | REAL | GLOBAL, offset_global );
				offset_global += TAM_REAL;
			}
			Parear( EOLN );
			break;
		case GLOBALB:
			Avanzar();
			Parear( IDENT );
			ident = tabla->BuscarIdent( udlexact->Lexema() );
			if( ident != NULL )
//                Error( "Identificador duplicado" );
                Error( ErrIdDup );
			else
			{
				tabla->InsertarVariable( udlexact->Lexema(),
							ID_VAR | BYTE | GLOBAL, offset_global );
								offset_global += TAM_BYTE;
			}
			Parear( EOLN );
			break;
		case ETIQB:
		case ETIQV:
		case ETIQR:
		case ETIQI: DeclFuncion(); break;
		default:
//            Error( "Instruccion no valida" );
            Error( ErrNoVal );
	}
}

void MaqPila::Instruccion( void )
{
	EntradaTabla *ident;
	Etiqueta *etiqueta;
	byte token;

	token = sgteudlex->Token();
	switch( token )
	{
		case EOLN:	while( sgteudlex->Token() == EOLN ) Avanzar(); break;
		case RET:
		case INSI:
			Avanzar();
			if( sgteudlex->Token() == NUM_ENT )
			{
				Avanzar();
// 201102 EGS+LRG+JK: the type hell
//				codinter->InsertarInstr( token, atol( udlexact->Lexema() ));
				codinter->InsertarInstr( token, (integer)atol( udlexact->Lexema() ));
			}
			else
// 201102 EGS+LRG+JK: the type hell: la instruccion INSI debería reservar solamente (valor "basura") pero parece no ser tan facil...
//			codinter->InsertarInstr( token, atol( 0 ));
			codinter->InsertarInstr( token, (integer)0 );
			Parear( EOLN );
			break;
		case INSR:
			Avanzar();
			if( sgteudlex->Token() == NUM_REAL )
			{
				Avanzar();
// 201102 EGS+LRG+JK: the type hell
//				codinter->InsertarInstr( token, atof( udlexact->Lexema() ));
				codinter->InsertarInstr( token, (real)atof( udlexact->Lexema() ));
			}
			else
// 201102 EGS+LRG+JK: the type hell: la instruccion INSR debería reservar solamente (valor "basura") pero parece no ser tan facil...
//				codinter->InsertarInstr( token, 0.0 );
				codinter->InsertarInstr( token, (real)0.0 );
			Parear( EOLN );
			break;
		case INSB:
			Avanzar();
// SAG
//			  if( sgteudlex->Token() == NUM_ENT )
            // admite byte o n£mero entero (entre 0 y 255)
            if( (sgteudlex->Token() == NUM_ENT) || (sgteudlex->Token() == NUM_BYTE) )
			{
				Avanzar();
                long numero = strtol( udlexact->Lexema(), NULL, 10 );
                if ( (numero < 0) || (numero > 255) )
//                    Error("Error: el n£mero debe estar comprendido entre 0 y 255");
                    Error( ErrByte );
				else
                    codinter->InsertarInstr( token, (byte)numero );
            }
			else
				codinter->InsertarInstr( token, (byte)0 );
			Parear( EOLN );
			break;
		case VALORD:
		case VALORI:
			Avanzar();
			Parear( IDENT );
			ident = tabla->BuscarIdent( udlexact->Lexema() );
			if( ident == NULL )
                Error( ErrNoDecl );
			else if(( ident->Tipo() & ENTRA ) != ID_VAR )
                Error( ErrVar );
			else
				codinter->InsertarInstr( token, ident->OffSet(), ident->Tipo(), ident->Ident() );
			Parear( EOLN );
			break;
		case LEERI:
		case LEERR:
		case LEERB:
		case ESCRIBIRR:
		case ESCRIBIRI:
        case ESCRIBIRB:
		case ESCRIBIRLN:
		case DESAPILARI:
		case DESAPILARR:
		case DESAPILARB:
		case COPIARI:
		case COPIARR:
		case COPIARB:
		case COGERBASE:
		case ASIG_ENT:
		case ASIG_REAL:
		case ASIG_BYTE:
		case CAMBIARII:
		case CAMBIARIR:
		case CAMBIARRI:
		case CAMBIARRR:
		case CAMBIARBI:
		case CAMBIARBR:
		case CAMBIARRB:
		case CAMBIARIB:
		case CAMBIARBB:
		case INTAREAL:
		case BYTEAINT:
		case INTABYTE:
		//case REALAINT:
		case OP_LOG_AND:
		case OP_LOG_OR:
        case OP_LOG_NOT:
		case OP_ENT_SUMA:
		case OP_ENT_RESTA:
		case OP_ENT_MULT:
		case OP_ENT_DIV:
		case OP_ENT_EXP:
		case OP_REAL_SUMA:
		case OP_REAL_RESTA:
		case OP_REAL_MULT:
		case OP_REAL_DIV:
		case OP_REAL_EXP:
		case OP_BYTE_SUMA:			// SAG
		case OP_BYTE_RESTA: 		// SAG
		case OP_ENT_MENOR:
		case OP_ENT_MAYOR:
		case OP_ENT_IGUAL:
		case OP_ENT_DISTINTO:
		case OP_ENT_MENORIGUAL:
		case OP_ENT_MAYORIGUAL:
		case OP_REAL_MENOR:
		case OP_REAL_MAYOR:
		case OP_REAL_IGUAL:
		case OP_REAL_DISTINTO:
		case OP_REAL_MENORIGUAL:
		case OP_REAL_MAYORIGUAL:
		case OP_BYTE_MENOR: 		// SAG
		case OP_BYTE_MAYOR: 		// SAG
		case OP_BYTE_IGUAL: 		// SAG
		case OP_BYTE_DISTINTO:		// SAG
		case OP_BYTE_MENORIGUAL:	// SAG
		case OP_BYTE_MAYORIGUAL:	// SAG
		case OP_UNA_ENT:
		case OP_UNA_REAL:
		case OP_UNA_BYTE:			// SAG
// $JK200910 nuevas lineas...
		case SQRT:
		case SIN:
		case COS:
		case TAN:
		case ASIN:
		case ACOS:
		case ATAN:
		case EXP:
		case LOG:
		case LN:
		case ROUND:
		case TRUNC:
// $JK200910 ... hasta aqui
			Avanzar();
			codinter->InsertarInstr( udlexact->Token() );
			Parear( EOLN );
			break;
		case ESCRIBIRS:
            char *string;
			Avanzar();
			Parear( STRING );
            string = (char *)udlexact->Lexema();
            string[ strlen( string ) - 1 ] = '\0';
			codinter->InsertarInstr( token, &string[1] );
			Parear( EOLN );
			break;
		case IR_A:
		case SI_CIERTO_IR_A:
		case SI_FALSO_IR_A:
			Avanzar();
			Parear( ETIQUETA );
			codinter->InsertarInstr( token, udlexact->Lexema() );
			Parear( EOLN );
			break;
		case LLAMAR:
			Avanzar();
			Parear( IDENT );
			codinter->InsertarInstr( token, udlexact->Lexema() );
			Parear( EOLN );
			break;
		case ETIQ:
			Avanzar();
			Parear( ETIQUETA );
			etiqueta = ( Etiqueta* )tabla->BuscarIdent( udlexact->Lexema() );
			if( etiqueta != NULL )
//                Error( "Identificador duplicado" );
                Error( ErrIdentDup );
			else
			{
				tabla->InsertarEtiqueta( udlexact->Lexema(), ID_ETIQ,
						codinter->InsertarInstr( ETIQ, udlexact->Lexema() ) );
				Parear( EOLN );
			}
			break;
		case PONERBASE:
			Avanzar();
			codinter->InsertarInstr( PONERBASE );
			offset_local = 0;
			DeclLocales();
			break;
		case DESAPILAR:
			Avanzar();
			Parear( NUM_ENT );
// 201102 EGS+LRG+JK: the type hell: el tipo es word, pero como no hay InsertarInstr para word... (ver nota anterior)
//			codinter->InsertarInstr( token, atol( udlexact->Lexema() ));
			codinter->InsertarInstr( token, (integer)atol( udlexact->Lexema() ));
			Parear( EOLN );
			break;
		case FIN:
			Avanzar();
			codinter->InsertarInstr( FIN, "" );
			if( sgteudlex->Token() != EOFL ) Parear( EOLN );
			break;
		case IDENT:
            Avanzar();
			ident = tabla->BuscarIdent( udlexact->Lexema() );
			if( ident != NULL )
//                Error( "Instruccion no valida" );
                Error( ErrNoVal );
/* $JK200910 lineas quitadas...
			else if( strcmpi( udlexact->Lexema(), "TRUNC" ) == 0 )
				codinter->InsertarInstr( TRUNC );
			else if( strcmpi( udlexact->Lexema(), "ROUND" ) == 0 )
				codinter->InsertarInstr( ROUND );
			else if( strcmpi( udlexact->Lexema(), "SQRT" ) == 0 )
				codinter->InsertarInstr( SQRT );
			else if( strcmpi( udlexact->Lexema(), "SIN" ) == 0 )
				codinter->InsertarInstr( SIN );
			else if( strcmpi( udlexact->Lexema(), "COS" ) == 0 )
				codinter->InsertarInstr( COS );
			else if( strcmpi( udlexact->Lexema(), "TAN" ) == 0 )
				codinter->InsertarInstr( TAN );
			else if( strcmpi( udlexact->Lexema(), "ASIN" ) == 0 )
				codinter->InsertarInstr( ASIN );
			else if( strcmpi( udlexact->Lexema(), "ACOS" ) == 0 )
				codinter->InsertarInstr( ACOS );
			else if( strcmpi( udlexact->Lexema(), "ATAN" ) == 0 )
				codinter->InsertarInstr( ATAN );
			else if( strcmpi( udlexact->Lexema(), "EXP" ) == 0 )
				codinter->InsertarInstr( EXP );
			else if( strcmpi( udlexact->Lexema(), "LOG" ) == 0 )
				codinter->InsertarInstr( LOG );
			else if( strcmpi( udlexact->Lexema(), "LN" ) == 0 )
				codinter->InsertarInstr( LN );
   $jk200910 ... hasta aqui */
//            else Error( "Instruccion no valida" );
            else Error( ErrNoVal );
			Parear( EOLN );
			break;
		default:
//            Error( "Instruccion no valida." );
            Error( ErrNoVal );
	}
}

void MaqPila::Parear( byte token )
{
	if( sgteudlex->Token() == token )
		Avanzar();
	else
//        Error( "Error sintactico" );
        Error( ErrSin );
}

void MaqPila::Avanzar( void )
{
	delete( udlexact );
	udlexact = sgteudlex;
	SgteUdLexica();
}

void MaqPila::SgteUdLexica( void )
{
	byte token = yylex->yylex();
	sgteudlex = new UdLexica( token, yylex->YYText() );
}

