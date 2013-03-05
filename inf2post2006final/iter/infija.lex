%{
/* infija.lex (versión final ANT)
   Traductor de expresiones en notación infija a notación postfija
   Analizador léxico
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include <string.h>
#include "infija.h"

void yyerror( char *msg )
{
	printf( "\nError en linea %d con '%s': %s", yylineno, yytext, msg );
}

%}

%option noyywrap
%option yylineno
%option never-interactive

/* Definiciones Regulares */

digito		[0-9]
constante	{digito}+
sep		[ \t\n]

%%

";"		{ atribANT.TCodigo = 0; return( P_COMA ); }

"+"		{ atribANT.TCodigo = 1; return( OP_ADIT ); }
"-"		{ atribANT.TCodigo = 2; return( OP_ADIT ); }

"*"		{ atribANT.TCodigo = 1; return( OP_MULT ); }
"/"		{ atribANT.TCodigo = 2; return( OP_MULT ); }
"%"		{ atribANT.TCodigo = 3; return( OP_MULT ); }

"("		{ atribANT.TCodigo = 0; return( PAR_ABR ); }
")"		{ atribANT.TCodigo = 0; return( PAR_CER ); }

{constante}	{ atribANT.TCadena = strdup( yytext ); return( NUM ); }

{sep}		{ }

.		{ yyerror( "lexical error: caracter desconocido" ); }

%%
