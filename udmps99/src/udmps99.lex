%{
/*
udmps99.lex - analizador léxico en lex
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

// $JK200910 cambio 2 lineas...
//#include <stdio.h>
//#include <string.h>
// $JK200910 ... por 2 lineas...
#include <cstdio>
#include <cstring>
// $JK200910 ... hasta aqui
#include "tokens.h"

char *linea = NULL;

const char *ErrLex[] =
{
    "",
    "el numero debe estar comprendido entre 0 y 255"    // 0x01
};

void yyerror( const char *s ) { }


%}
 /* %option case-insensitive */
%option outfile = "lexyy.cpp"

  //JK:en este fichero hay que modificar
  //<Flexlexer.h> por "Flexlexe.h"
  // SAG: esto no hace falta con el Watcom C++
  //quitar include <unistd.h>
  //cambiar "yyconst char msg[]" por "const char *msg" 

%option c++
%option noyywrap
%option yylineno
/* %option never-interactive */

/* Definiciones Regulares */

letra                   [A-Za-z]
digito                  [0-9]
digitopos               [1-9]
digitoo                 [0-7]
digitox                 {digito}|[A-Fa-f]
idesp                   [#\-_]
idneg                   "-"
ident                   {letra}({letra}|{digito}|{idesp})*
etiqueta                #{ident}
numbytec                \'[^'\t\n\\]\'|"''''"
numbyted                \'\\{digito}+\'
numbytex                \'\\x{digitox}+\'
numbyte                 {numbytec}|{numbyted}|{numbytex}
numentdpos              {digitopos}{digito}*|0
numentd                 {numentdpos}|{idneg}{numentdpos}
numento                 0{digitoo}+
numentx                 0x{digitox}+
nument                  {numentd}|{numento}|{numentx}
basereal                {digito}*\.{digito}+|{digito}+\.{digito}*
exponente               [eE]{numentd}
numrealpos              {basereal}|{basereal}{exponente}|{numentdpos}{exponente}
numreal                 {numrealpos}|{idneg}{numrealpos}
espbl                   [ \t]+
string                  \"([^"\t\n])*\"

%%

	// 201102 EGS+LRG+JK: corrigiendo warnings
	//^.*                     {       delete( linea );
^.*                     {       free( linea );
                                linea = strdup( yytext );
                                yyless( 0 ); }
;.*                     {}
{espbl}                 {}
	/* $JK200910 cambio...
\n+                     { return EOLN; } */
(\n|\r|\f)+             { return EOLN; }

"+"                     { return OP_ENT_SUMA; }
"-"                     { return OP_ENT_RESTA; }
"*"                     { return OP_ENT_MULT; }
"/"                     { return OP_ENT_DIV; }
"^"                     { return OP_ENT_EXP; }

"+"[rR]                 { return OP_REAL_SUMA; }
"-"[rR]                 { return OP_REAL_RESTA; }
"*"[rR]                 { return OP_REAL_MULT; }
"/"[rR]                 { return OP_REAL_DIV; }
"^"[rR]                 { return OP_REAL_EXP; }

"+"[bB]                 { return OP_BYTE_SUMA; }
"-"[bB]                 { return OP_BYTE_RESTA; }

[nN][eE][gG]            { return OP_UNA_ENT; }
[nN][eE][gG][rR]        { return OP_UNA_REAL; }
[nN][eE][gG][bB]        { return OP_UNA_BYTE; }

"<"                     { return OP_ENT_MENOR; }
">"                     { return OP_ENT_MAYOR; }
"<="                    { return OP_ENT_MENORIGUAL; }
">="                    { return OP_ENT_MAYORIGUAL; }
"=="                    { return OP_ENT_IGUAL; }
"!="                    { return OP_ENT_DISTINTO; }

"<"[rR]                 { return OP_REAL_MENOR; }
">"[rR]                 { return OP_REAL_MAYOR; }
"<="[rR]                { return OP_REAL_MENORIGUAL; }
">="[rR]                { return OP_REAL_MAYORIGUAL; }
"=="[rR]                { return OP_REAL_IGUAL; }
"!="[rR]                { return OP_REAL_DISTINTO; }

"<"[bB]                 { return OP_BYTE_MENOR; }
">"[bB]                 { return OP_BYTE_MAYOR; }
"<="[bB]                { return OP_BYTE_MENORIGUAL; }
">="[bB]                { return OP_BYTE_MAYORIGUAL; }
"=="[bB]                { return OP_BYTE_IGUAL; }
"!="[bB]                { return OP_BYTE_DISTINTO; }

[aA][nN][dD]            { return OP_LOG_AND; }
[oO][rR]                { return OP_LOG_OR; }
[nN][oO][tT]            { return OP_LOG_NOT; }

[iI][nN][tT][aA][rR][eE][aA][lL]   { return INTAREAL; }
[iI][nN][tT][aA][bB][yY][tT][eE]   { return INTABYTE; }
[bB][yY][tT][eE][aA][iI][nN][tT]   { return BYTEAINT; }

[iI][nN][sS][iI]                           { return INSI; }
[dD][eE][sS][aA][pP][iI][lL][aA][rR][iI]   { return DESAPILARI; }
[iI][nN][sS][rR]                           { return INSR; }
[dD][eE][sS][aA][pP][iI][lL][aA][rR][rR]   { return DESAPILARR; }
[iI][nN][sS][bB]                           { return INSB; }
[dD][eE][sS][aA][pP][iI][lL][aA][rR][bB]   { return DESAPILARB; }
[dD][eE][sS][aA][pP][iI][lL][aA][rR]       { return DESAPILAR; }
[cC][oO][pP][iI][aA][rR][iI]               { return COPIARI; }
[cC][oO][pP][iI][aA][rR][rR]               { return COPIARR; }
[cC][oO][pP][iI][aA][rR][bB]               { return COPIARB; }

[cC][aA][mM][bB][iI][aA][rR][iI][iI]   { return CAMBIARII; }
[cC][aA][mM][bB][iI][aA][rR][iI][rR]   { return CAMBIARIR; }
[cC][aA][mM][bB][iI][aA][rR][rR][iI]   { return CAMBIARRI; }
[cC][aA][mM][bB][iI][aA][rR][rR][rR]   { return CAMBIARRR; }
[cC][aA][mM][bB][iI][aA][rR][bB][bB]   { return CAMBIARBB; }
[cC][aA][mM][bB][iI][aA][rR][bB][iI]   { return CAMBIARBI; }
[cC][aA][mM][bB][iI][aA][rR][bB][rR]   { return CAMBIARBR; }
[cC][aA][mM][bB][iI][aA][rR][rR][bB]   { return CAMBIARRB; }
[cC][aA][mM][bB][iI][aA][rR][iI][bB]   { return CAMBIARIB; }

[sS][iI][_-][cC][iI][eE][rR][tT][oO][_-][iI][rR][_-][aA]   { return SI_CIERTO_IR_A; }
[sS][iI][_-][fF][aA][lL][sS][oO][_-][iI][rR][_-][aA]       { return SI_FALSO_IR_A; }
[iI][rR][_-][aA]                                           { return IR_A; }
[eE][tT][iI][qQ]                                           { return ETIQ; }

[lL][eE][eE][rR][iI]    { return LEERI; }
[lL][eE][eE][rR][rR]    { return LEERR; }
[lL][eE][eE][rR][bB]    { return LEERB; }

[eE][sS][cC][rR][iI][bB][iI][rR][iI]       { return ESCRIBIRI;  }
[eE][sS][cC][rR][iI][bB][iI][rR][rR]       { return ESCRIBIRR;  }
[eE][sS][cC][rR][iI][bB][iI][rR][bB]       { return ESCRIBIRB;  }
[eE][sS][cC][rR][iI][bB][iI][rR][lL][nN]   { return ESCRIBIRLN; }
[eE][sS][cC][rR][iI][bB][iI][rR][sS]       { return ESCRIBIRS;  }

[iI][nN][iI][cC][iI][oO]   { return INICIO; }
[fF][iI][nN]               { return FIN; }
[eE][tT][iI][qQ][vV]       { return ETIQV; }
[eE][tT][iI][qQ][iI]       { return ETIQI; }
[eE][tT][iI][qQ][rR]       { return ETIQR; }
[eE][tT][iI][qQ][bB]       { return ETIQB; }

[gG][lL][oO][bB][aA][lL][iI]   { return GLOBALI; }
[gG][lL][oO][bB][aA][lL][rR]   { return GLOBALR; }
[gG][lL][oO][bB][aA][lL][bB]   { return GLOBALB; }

[pP][aA][rR][aA][mM][iI]       { return PARAMI; }
[pP][aA][rR][aA][mM][rR]       { return PARAMR; }
[pP][aA][rR][aA][mM][bB]       { return PARAMB; }

[lL][oO][cC][aA][lL][iI]       { return LOCALI; }
[lL][oO][cC][aA][lL][rR]       { return LOCALR; }
[lL][oO][cC][aA][lL][bB]       { return LOCALB; }

[vV][aA][lL][oO][rR][dD]   { return VALORD; }
[vV][aA][lL][oO][rR][iI]   { return VALORI; }
":="                       { return ASIG_ENT; }
":="[rR]                   { return ASIG_REAL; }
":="[bB]                   { return ASIG_BYTE; }

[lL][lL][aA][mM][aA][rR]   { return LLAMAR; }
[rR][eE][tT]               { return RET; }

[pP][oO][nN][eE][rR][bB][aA][sS][eE]   { return PONERBASE; }
[cC][oO][gG][eE][rR][bB][aA][sS][eE]   { return COGERBASE; }

	/* $JK200910 lineas nuevas... */
[rR][oO][uU][nN][dD]           { return ROUND; }
[tT][rR][uU][nN][cC]           { return TRUNC; }

[sS][qQ][rR][tT]               { return SQRT; }
[sS][iI][nN]                   { return SIN; }
[cC][oO][sS]                   { return COS; }
[tT][aA][nN]                   { return TAN; }
[aA][sS][iI][nN]               { return ASIN; }
[aA][cC][oO][sS]               { return ACOS; }
[aA][tT][aA][nN]               { return ATAN; }
[eE][xX][pP]                   { return EXP; }
[lL][oO][gG]                   { return LOG; }
[lL][nN]                       { return LN; }
	/* $JK200910 ... hasta aqui */

{etiqueta}              { return ETIQUETA; }

{ident}                 { return IDENT; }

{numbyte}               {
                            // quitarle la primera y la £ltima comilla
                            yytext++;
// $JK200910 cambio linea
//                          yytext[strlen(yytext)-1] = NULL;
                            yytext[strlen(yytext)-1] = '\0';
                            if ( yytext[0] == '\\' )      // es un n£mero
                            {
                                yytext++;
                                long numero;
                                if ( yytext[0] == 'x' )   // hexadecimal
                                    numero = strtol( ++yytext, NULL, 16 );
                                else                    // decimal
                                    numero = strtol( yytext, NULL, 10 );
                                if ( (numero < 0) || (numero > 255) )
                                    yyerror( ErrLex[1] );
// 201102 EGS+LRG+JK: corrigiendo warnings
//                              sprintf( yytext, "%d", numero );
                                sprintf( yytext, "%ld", numero );
                            }
                            else { //JK: es un caracter
                                long numero;
                                numero = (int)*yytext;
// 201102 EGS+LRG+JK: corrigiendo warnings
//                              sprintf( yytext, "%d", numero );
                                sprintf( yytext, "%ld", numero );
                            }
                            return NUM_BYTE;
                        }

{nument}                {
                            if ( (yytext[0] == '0') && (yytext[1] != '\0') )
                            {
                                if ( yytext[1] == 'x' )     // hexadecimal
// 201102 EGS+LRG+JK: corrigiendo warnings
//                                  sprintf( yytext, "%d",
                                    sprintf( yytext, "%ld",
                                        strtol( yytext+2, NULL, 16 ) );
                                else                        // octal
// 201102 EGS+LRG+JK: corrigiendo warnings
//                                  sprintf( yytext, "%d",
                                    sprintf( yytext, "%ld",
                                        strtol( yytext+1, NULL, 8 ) );
                            }
                            // else;                        // decimal positivo
                            return NUM_ENT;
                        }

{numreal}               { return NUM_REAL; }

{string}                { return STRING; }

.                       { return ERROR; }
                  
%%

/*
[rR][oO][uU][nN][dD]           { return ROUND; }
[tT][rR][uU][nN][cC]           { return TRUNC; }

[sS][qQ][rR][tT]               { return SQRT; }
[sS][iI][nN]                   { return SIN; }
[cC][oO][sS]                   { return COS; }
[tT][aA][nN]                   { return TAN; }
[aA][sS][iI][nN]               { return ASIN; }
[aA][cC][oO][sS]               { return ACOS; }
[aA][tT][aA][nN]               { return ATAN; }
[eE][xX][pP]                   { return EXP; }
[lL][oO][gG]                   { return LOG; }
[lL][nN]                       { return LN; }
*/
