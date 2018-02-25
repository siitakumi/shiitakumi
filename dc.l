%%
[1-9][0-9]*	{
				yylval = atoi(yytext);
				return(KAZU);
			}
\(			{ return(HIDARIKAKKO); }
\)			{ return(MIGIKAKKO); }
\+			{ return(TASU); }
\-			{ return(HIKU); }
\*			{ return(KAKERU); }
\/			{ return(WARU); }
;			{ return(OWARI); }
mplus		{ return(MPLUS); }
mminus		{ return(MMINUS); }
mclear		{ return(MCLEAR); }
mprint		{ return(MPRINT); }

[ \t\n]+	{}
.			{}
%%