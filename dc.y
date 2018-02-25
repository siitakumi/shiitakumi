%{
	#include <stdio.h>
	int memori = 0;
	int memori_rsl = 0;
%}
%token KAZU
%token MPLUS MMINUS MPRINT MCLEAR
%token OWARI
%left MIGIKAKKO
%left TASU HIKU
%left WARU KAKERU
%left VTOKEN
%left HIDARIKAKKO

%%
source: /* empty */
		| source bun
		;
		
bun:	shiki OWARI { printf("%d\n", $1); }
		|memori OWARI
		;
		
shiki:	KAZU{ $$ = $1; }
		| tasu
		| hiku
		| waru
		| kakeru
		| HIKU shiki %prec VTOKEN { $$ = -$2; }
		;
		
tasu:   HIDARIKAKKO shiki TASU shiki MIGIKAKKO { $$ = $2 + $4; memori = $$;}
		| shiki TASU shiki { $$ = $1 + $3; memori = $$; } 
		;
		
hiku:   HIDARIKAKKO shiki HIKU shiki MIGIKAKKO { $$ = $2 - $4; memori = $$;}
		| shiki HIKU shiki { $$ = $1 - $3; memori = $$; }
		;
		
waru:	HIDARIKAKKO shiki WARU shiki MIGIKAKKO { $$ = $2 / $4; }
		| shiki WARU shiki { memori = $$; }
		;
		
kakeru: HIDARIKAKKO shiki KAKERU shiki MIGIKAKKO { $$ = $2 * $4; memori = $$;}
		| shiki KAKERU shiki { $$ = $1 * $3; }
		;

memori: MPLUS { memori_rsl += memori; }
		| MMINUS { memori_rsl -= memori; }
		| MPRINT { printf("memori_rsl = %d\n",memori_rsl); }
		| MCLEAR { memori = memori_rsl = 0; }
		;

%%
#include "lex.yy.c"

int yyerror(const char *str)
{
	fprintf(stderr, "error: %s\n", str);
}

int yywrap(void)
{
	return(1);
}

int main(int argc, char *argv[])
{
	if(argc != 2){ return(1); }
	yyin = fopen(argv[1], "r");
	yyparse();
}