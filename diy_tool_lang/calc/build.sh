bison --yacc -dv calc.y
flex calc.l
gcc lex.yy.c y.tab.c
