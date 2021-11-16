%{
    #include <stdbool.h>
    #include <string.h>
    #include "AST/Identifier.h"
    #include "AST/Expression.h"
    #include "AST/Instruction.h"
    #include "y.tab.h"
    #include <stdint.h>
%}

%s LINE
%%

<INITIAL>"\n"
<INITIAL>. {
   int i;
   /* Copy yytext because unput() trashes yytext */
   char *yycopy = strdup( yytext );
   for ( i = yyleng - 1; i >= 0; --i )
       unput( yycopy[i] );
   free( yycopy );
   BEGIN(LINE);
}


<LINE>"&&"     {return AND;}
<LINE>"||"     {return OR;}
<LINE>"=>"	{return IMPLIES;}
<LINE>"^^"	{return XOR;}
<LINE>"=="	{return EQUALS;}
<LINE>"!="	{return DISTINCT;}
<LINE>"!"	{return NOT;}
<LINE>"+"	{return PLUS;}
<LINE>"-"	{return MINUS;}
<LINE>"(" {return OPAREN;}
<LINE>")" {return CPAREN;}
<LINE>"[" {return OBRACKET;}
<LINE>"]" {return CBRACKET;}
<LINE>"{" {BEGIN(INITIAL); return OBRACE;}
<LINE>"}" {return CBRACE;}
<LINE>"," {return COMMA;}
<LINE>"->" {return ARROW;}
<LINE>"return" {return RETURN;}
<LINE>"INT" {
    yylval.valueType = "INT";
    return C_TYPE;
}
<LINE>"BOOL" {
    yylval.valueType = "BOOL";
    return C_TYPE;
}
<LINE>"REAL" {
    yylval.valueType = "REAL";
    return C_TYPE;
}
<LINE>"BITVEC" {
    return BITVEC;
}
<LINE>"false"   {
    VALUE value = newBooleanVALUE(false);
    yylval.value = value;
    return BOOL;
}
<LINE>"true"  {
    VALUE value = newBooleanVALUE(true);
    yylval.value = value;
    return BOOL;
}
<LINE>"="     {return ASSIGN;}
<LINE>"if"    {return IF;}
<LINE>"goto"  {return GOTO;}
<LINE>"LABEL" {return LAB;}
<LINE>"def"   {return DEFINE;}
<LINE>"endef" {return END_FUNC;}
<LINE>"struct" {return STRUCT;}
<LINE>"endstruct" {return ENDSTRUCT;}
<LINE>"bv2nat" {return BV2NAT;}
<LINE>"nat2bv" {return NAT2BV;}
<LINE>"bv_concat" {return BVCONCAT;}
<LINE>"bv_extract" {return BVEXTRACT;}
<LINE>"bv_not" {return BVNOT;}
<LINE>"bv_and" {return BVAND;}
<LINE>"bv_or" {return BVOR;}
<LINE>"bv_neg" {return BVNEG;}
<LINE>"bv_add" {return BVADD;}
<LINE>"bv_mul" {return BVMUL;}
<LINE>"bv_udiv" {return BVUDIV;}
<LINE>"bv_urem" {return BVUREM;}
<LINE>"bv_shl" {return BVSHL;}
<LINE>"bv_lshr" {return BVLSHR;}
<LINE>"bv_ult" {return BVULT;}
<LINE>"r_+" {return RADD;}
<LINE>"r_-" {return RMINUS;}
<LINE>"r_*" {return RMUL;}
<LINE>"r_/" {return RDIV;}
<LINE>"r_<=" {return RLEQ;}
<LINE>"r_<" {return RLE;}
<LINE>"r_>=" {return RGEQ;}
<LINE>"r_>" {return RGE;}
<LINE>"toreal" {return RITOREAL;}
<LINE>"toint" {return RITOINT;}
<LINE>"isint" {return RIISINT;}
<LINE>[a-zA-Z][a-zA-Z0-9]* {
    char *id = (char *) malloc(yyleng + 1);
    strcpy (id, yytext);
    yylval.id = newIDENTIFIER(id);
    return IDENTIFIER;
}
<LINE>(0|[1-9][0-9]*)"."(0|[1-9][0-9]*) {
    float f = atof(yytext);
    VALUE value = newRealVALUE(atof(yytext));
    yylval.value = value;
    return REAL;
}
<LINE>0|[1-9][0-9]* {
    VALUE value = newIntegerVALUE(atoi(yytext));
    yylval.value = value;
    return INTEGER;
}
<LINE>"#b"[0-1]+ {
    char *bitString = (char *) malloc(yyleng - 2 + 1);
    strcpy (bitString, yytext + 2);
    int numBits = (sizeof(unsigned long) * 8 < yyleng - 2) ? (sizeof(unsigned long) * 8) : (yyleng - 2);
    VALUE val = newBitVectorVALUE(strtol(bitString, NULL, 2), numBits);
    yylval.value = val;
    return BITVECTOR;
}
<LINE>"#x"[abcdef0-9]+ {
    char *bitString = (char *) malloc(yyleng - 2 + 1);
    strcpy (bitString, yytext + 2);
    int numBits = (sizeof(unsigned long) * 8 < ((yyleng - 2) * 4)) ? (sizeof(unsigned long) * 8) : ((yyleng - 2) * 4);
    VALUE val = newBitVectorVALUE(strtol(bitString, NULL, 16), numBits);
    yylval.value = val;
    return BITVECTOR;
}
<LINE>"?"	{return QMARK;}
<LINE>":"	{return COLON;}
<LINE>"." {return DOT;}
<LINE>"*" {return ASTERISK;}
<LINE>"$mem" {return MEMALLOC;}
<LINE>\n      {BEGIN(INITIAL);  return EOL;}
<LINE>[ \t]   {}
<LINE>.       {printf("unsupported");}
%%

int yywrap(){return 1;}
