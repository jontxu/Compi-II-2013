%{
/* jkl.lex
   Analizador léxico del lenguaje JKL
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include <string.h>
#include "jkl.h"

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
letra		[a-zA-Z]
id		{letra}({letra}|{digito})*
char		[^\"\t\n]
str		\"{char}*\"
sep		[ \t\n]

%%

";"		{ atribANT.TCodigo = 0; return( P_COMA ); }

"."		{ atribANT.TCodigo = 0; return( PUNTO ); }

"<"		{ atribANT.TCodigo = 1; return( OP_REL ); }
"<="		{ atribANT.TCodigo = 2; return( OP_REL ); }
">"		{ atribANT.TCodigo = 3; return( OP_REL ); }
">="		{ atribANT.TCodigo = 4; return( OP_REL ); }
"="		{ atribANT.TCodigo = 5; return( OP_REL ); }
"<>"		{ atribANT.TCodigo = 6; return( OP_REL ); }

"+"		{ atribANT.TCodigo = 1; return( OP_ADIT ); }
"-"		{ atribANT.TCodigo = 2; return( OP_ADIT ); }

"*"		{ atribANT.TCodigo = 1; return( OP_MULT ); }
"/"		{ atribANT.TCodigo = 2; return( OP_MULT ); }
"%"		{ atribANT.TCodigo = 3; return( OP_MULT ); }

"("		{ atribANT.TCodigo = 0; return( PAR_ABR ); }
")"		{ atribANT.TCodigo = 0; return( PAR_CER ); }

":="		{ atribANT.TCodigo = 0; return( ASIGN ); }

{constante}	{ atribANT.TCadena = strdup( yytext ); return( NUM ); }

{str}		{ atribANT.TCadena = strdup( yytext ); return( CAD ); }

or		{ atribANT.TCodigo = 0; return( OP_OR ); }
and		{ atribANT.TCodigo = 0; return( OP_AND ); }
not		{ atribANT.TCodigo = 0; return( OP_NOT ); }

begin		{ atribANT.TCodigo = 0; return( PBEGIN ); }
end		{ atribANT.TCodigo = 0; return( PEND ); }
program		{ atribANT.TCodigo = 0; return( PPROG ); }
var		{ atribANT.TCodigo = 0; return( PVAR ); }
read		{ atribANT.TCodigo = 0; return( PREAD ); }
write		{ atribANT.TCodigo = 0; return( PWRITE ); }
writec		{ atribANT.TCodigo = 0; return( PWRITC ); }
writeln		{ atribANT.TCodigo = 0; return( PWRITL ); }
if		{ atribANT.TCodigo = 0; return( PIF ); }
then		{ atribANT.TCodigo = 0; return( PTHEN ); }
else		{ atribANT.TCodigo = 0; return( PELSE ); }
while		{ atribANT.TCodigo = 0; return( PWHILE ); }
do		{ atribANT.TCodigo = 0; return( PDO ); }
for		{ atribANT.TCodigo = 0; return( PFOR ); }
to		{ atribANT.TCodigo = 1; return( PTODO ); }
downto		{ atribANT.TCodigo = 2; return( PTODO ); }

{id}		{ atribANT.TCadena = strdup( yytext ); return( ID ); }

{sep}		{ }

"//".*		{ }

.		{ yyerror( "lexical error: caracter desconocido" ); }

%%
