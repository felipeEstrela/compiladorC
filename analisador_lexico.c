/* Integrantes:
Leonardo L. R. T. Brandao - 31633528
Felipe Estrela Cardoso - 31618375
Bryam Kim - 31637450
Gustavo Getulio - 31686508
*/

#define PROGRAM 1 
#define IF 2
#define ELSE 3 
#define VOID 4 
#define TRUE 5 
#define FALSE 6 
#define INT 7 
#define BOOL 8 
#define WHILE 9 
#define PRINT 9
#define VAR 10
#define FOR 11
#define MAIS 12
#define MENOS 13
#define DIVISAO 14
#define COMENTARIO 15
#define MULTIPLICACAO 16
#define VIRGULA 17
#define DIFERENTE 18
#define IGUAL 19
#define COMPARACAO 20
#define MAIOR 21
#define MAIORIGUAL 22
#define MENOR 21
#define MENORIGUAL 22
#define ABRECHAVES 23
#define FECHACHAVES 24
#define PONTOVIRGULA 25
#define ABREPARENTESE 26
#define FECHAPARENTESE 27
#define DOISPONTOS 28
#define VARIAVEL 29
#define ERROR -1

/* Nome do arquivo com o codigo a ser analisado: codigo.txt
   Nome do arquivo produzido contendo os tokens: tokens.txt */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int fileLenght = 0;

FILE *openFile(char *nomeArq) {
    FILE *fp;
    fp = fopen(nomeArq, "r");

    if (fp == NULL) {
        printf("Arquivo nao encontrado\n");
        exit(0);
    }
    return fp;
}

void writeToFile(FILE *tokens, char* token) {
    fprintf(tokens, "%s", token);  

}

int scanner(FILE *fp, FILE *tokens) {
    /* 'lookahead' e o caractere lido a cada goto ate o fim do arquivo (EOF) */
    char* token;
    char lookahead;
    
    q0: lookahead = fgetc(fp);
    if (lookahead == 'p') {
        goto q1;
    } else if (lookahead == 'i'){
        goto q13;
    } else if (lookahead == 't'){
        goto q19;
    } else if (lookahead == 'b'){
        goto q24;
    } else if (lookahead == 'f'){
        goto q29;
    } else if (lookahead == 'v'){
        goto q46;
    } else if (lookahead == 'w'){
        goto q40;
    } else if (lookahead == '+'){
        goto q51;
    } else if (lookahead == '-'){
        goto q52;
    } else if (lookahead == '/'){
        goto q53;
    } else if (lookahead == '*'){
        goto q54;
    } else if (lookahead == ','){
        goto q103;
    } else if (lookahead == '!'){
        goto q55;
    } else if (lookahead == '='){
        goto q57;
    } else if (lookahead == '>'){
        goto q66;
    } else if (lookahead == '<'){
        goto q67;
    } else if (lookahead == '('){
        goto q75;
    } else if (lookahead == ')'){
        goto q74;
    } else if (lookahead == '{'){
        goto q77;
    } else if (lookahead == '}'){
        goto q76;
    } else if (lookahead == ';'){
        goto q78;
    } else if (lookahead == '_'){
        goto q89;
    } else {
        return ERROR;
    }

    q1: lookahead = fgetc(fp);
    if (lookahead == 'r') {
        goto q2;
    } else {
        return ERROR;
    }

    q2: lookahead = fgetc(fp);
    if (lookahead == 'o') {
        goto q3;
    } else if(lookahead == 'i'){
        goto q9;
    } else {
        return ERROR;
    }

    q3: lookahead = fgetc(fp);
    if (lookahead == 'g') {
        goto q4;
    } else {
        return ERROR;
    }

    q4: lookahead = fgetc(fp);
    if (lookahead == 'r') {
        goto q5;
    } else {
        return ERROR;
    }

    q5: lookahead = fgetc(fp);
    if (lookahead == 'a') {
        goto q6;
    } else {
        return ERROR;
    }

    q6: lookahead = fgetc(fp);
    if (lookahead == 'm') {
        goto q7;
    } else {
        return ERROR;
    }

    q7: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("PROGRAM \n");
        return PROGRAM;
    } else {
        return ERROR;
    }

    q9: lookahead = fgetc(fp);
    if (lookahead == 'n') {
        goto q10;
    } else {
        return ERROR;
    }
   
    q10: lookahead = fgetc(fp);
    if (lookahead == 't') {
        goto q11;
    } else {
        return ERROR;
    }
    
    q11: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("PRINT \n");
        return PRINT;
    } else {
        return ERROR;
    }

    q13: lookahead = fgetc(fp);
    if (lookahead == 'f') {
        goto q17;
    } else if (lookahead == 'n'){
        goto q14;
    } else {
        return ERROR;
    }

    q14: lookahead = fgetc(fp);
    if (lookahead == 't') {
        goto q15;
    } else {
        return ERROR;
    }

    q15: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("INT \n");
        return INT;
    } else {
        return ERROR;
    }

    q17: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("IF \n");
        return IF;
    } else {
        return ERROR;
    }

    q19: lookahead = fgetc(fp);
    if (lookahead == 'r') {
        goto q20;
    } else {
        return ERROR;
    }
    
    q20: lookahead = fgetc(fp);
    if (lookahead == 'u') {
        goto q21;
    } else {
        return ERROR;
    }
    
    q21: lookahead = fgetc(fp);
    if (lookahead == 'e') {
        goto q22;
    } else {
        return ERROR;
    }

    q22: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("true \n");
        return TRUE;
    } else {
        return ERROR;
    }

    q24: lookahead = fgetc(fp);
    if (lookahead == 'o') {
        goto q25;
    } else {
        return ERROR;
    }
  
    q25: lookahead = fgetc(fp);
    if (lookahead == 'o') {
        goto q26;
    } else {
        return ERROR;
    }
   
    q26: lookahead = fgetc(fp);
    if (lookahead == 'l') {
        goto q27;
    } else {
        return ERROR;
    }

    q27: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("bool \n");
        return BOOL;
    }

    q29: lookahead = fgetc(fp);
    if (lookahead == 'o') {
        goto q100;
    } else if(lookahead == 'a'){
        goto q30;
    } else {
        return ERROR;
    }
    
    q30: lookahead = fgetc(fp);
    if (lookahead == 'l') {
        goto q31;
    } else {
        return ERROR;
    }
    
    q31: lookahead = fgetc(fp);
    if (lookahead == 's') {
        goto q32;
    } else {
        return ERROR;
    }
   
    q32: lookahead = fgetc(fp);
    if (lookahead == 'e') {
        goto q33;
    } else {
        return ERROR;
    }

    q33: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("false \n");
        return FALSE;
    } else {
        return ERROR;
    }

    q100: lookahead = fgetc(fp);
    if (lookahead == 'r') {
        goto q101;
    } else {
        return ERROR;
    }
    
    q101: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("for \n");
        return FOR;
    } else {
        return ERROR;
    }

    q46: lookahead = fgetc(fp);
    if (lookahead == 'o') {
        goto q47;
    } else {
        return ERROR;
    }
    
    q47: lookahead = fgetc(fp);
    if (lookahead == 'i') {
        goto q48;
    } else {
        return ERROR;
    }
    
    q48: lookahead = fgetc(fp);
    if (lookahead == 'd') {
        goto q49;
    } else {
        return ERROR;
    }
    
    q49: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("void \n");
        return VOID;
    } else {
        return ERROR;
    }
    
    q40: lookahead = fgetc(fp);
    if (lookahead == 'h') {
        goto q41;
    } else {
        return ERROR;
    }
    
    q41: lookahead = fgetc(fp);
    if (lookahead == 'i') {
        goto q42;
    } else {
        return ERROR;
    }
    
    q42: lookahead = fgetc(fp);
    if (lookahead == 'l') {
        goto q43;
    } else {
        return ERROR;
    }
    
    q43: lookahead = fgetc(fp);
    if (lookahead == 'e') {
        goto q44;
    } else {
        return ERROR;
    }

    q44: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("while \n");
        return WHILE;
    } else {
        return ERROR;
    }
    
    q51: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("+ \n");
        return MAIS;
    } else {
        return ERROR;
    }
    
    q52: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("- \n");
        return MENOS;
    } else {
        return ERROR;
    }

    q53: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("/ \n");
        return DIVISAO;
    } else if (lookahead == '*') {
        goto q86;
    } else {
        return ERROR;
    }

    q86: lookahead = fgetc(fp);
    if (lookahead == '0' || lookahead == '1' || lookahead == '2' || lookahead == '3' || lookahead == '4' || lookahead == '5' || 
            lookahead == '6' || lookahead == '7' || lookahead == '8' || lookahead == '9' || lookahead == 'a' ||
            lookahead == 'a' || lookahead == 'A' || lookahead == 'b' || lookahead == 'B' || lookahead == 'c' ||
            lookahead == 'C' || lookahead == 'd' || lookahead == 'D' || lookahead == 'e' || lookahead == 'E' ||
            lookahead == 'f' || lookahead == 'F' || lookahead == 'g' || lookahead == 'G' || lookahead == 'h' ||
            lookahead == 'H' || lookahead == 'i' || lookahead == 'I' || lookahead == 'J' || lookahead == 'j' ||
            lookahead == 'K' || lookahead == 'k' || lookahead == 'm' || lookahead == 'M' || lookahead == 'n' ||
            lookahead == 'N' || lookahead == 'l' || lookahead == 'L' || lookahead == 'o' || lookahead == 'O' ||
            lookahead == 'p' || lookahead == 'P' || lookahead == 'q' || lookahead == 'Q' || lookahead == 'r' ||
            lookahead == 'R' || lookahead == 's' || lookahead == 'S' || lookahead == 't' || lookahead == 'T' ||
            lookahead == 'U' || lookahead == 'u' || lookahead == 'v' || lookahead == 'V' || lookahead == 'x' ||
            lookahead == 'X' || lookahead == 'w' || lookahead == 'W' || lookahead == 'y' || lookahead == 'Y' || 
            lookahead == 'z' || lookahead == 'Z') {
        goto q87;
    } else {
        return ERROR;
    }

    q87: lookahead = fgetc(fp);
    if (lookahead == '0' || lookahead == '1' || lookahead == '2' || lookahead == '3' || lookahead == '4' || lookahead == '5' || 
            lookahead == '6' || lookahead == '7' || lookahead == '8' || lookahead == '9' || lookahead == 'a' ||
            lookahead == 'a' || lookahead == 'A' || lookahead == 'b' || lookahead == 'B' || lookahead == 'c' ||
            lookahead == 'C' || lookahead == 'd' || lookahead == 'D' || lookahead == 'e' || lookahead == 'E' ||
            lookahead == 'f' || lookahead == 'F' || lookahead == 'g' || lookahead == 'G' || lookahead == 'h' ||
            lookahead == 'H' || lookahead == 'i' || lookahead == 'I' || lookahead == 'J' || lookahead == 'j' ||
            lookahead == 'K' || lookahead == 'k' || lookahead == 'm' || lookahead == 'M' || lookahead == 'n' ||
            lookahead == 'N' || lookahead == 'l' || lookahead == 'L' || lookahead == 'o' || lookahead == 'O' ||
            lookahead == 'p' || lookahead == 'P' || lookahead == 'q' || lookahead == 'Q' || lookahead == 'r' ||
            lookahead == 'R' || lookahead == 's' || lookahead == 'S' || lookahead == 't' || lookahead == 'T' ||
            lookahead == 'U' || lookahead == 'u' || lookahead == 'v' || lookahead == 'V' || lookahead == 'x' ||
            lookahead == 'X' || lookahead == 'w' || lookahead == 'W' || lookahead == 'y' || lookahead == 'Y' || 
            lookahead == 'z' || lookahead == 'Z') {
        goto q87;
    } else if (lookahead == '*') {
        goto q88;
    } else {
        return ERROR;
    }

    q88: lookahead = fgetc(fp);
    if (lookahead == '/') {
        goto q91;
    } else {
        return ERROR;
    }

    q91: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("COMENTARIO \n");
        return COMENTARIO;
    } else {
        return ERROR;
    }

    q54: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("* \n");
        return MULTIPLICACAO;
    } else {
        return ERROR;
    }

    q103: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf(", \n");
        return VIRGULA;
    } else {
        return ERROR;
    }

    q55: lookahead = fgetc(fp);
    if (lookahead == '=') {
        goto q56;
    } else {
        return ERROR;
    }

    q56: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("DIFERENTE \n");
        return DIFERENTE;
    } else {
        return ERROR;
    }

    q57: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("= \n");
        return IGUAL;
    } else if (lookahead == '=') {
        goto q58;
    } else {
        return ERROR;
    }

    q58: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("== \n");
        return COMPARACAO;
    } else {
        return ERROR;
    }

    q66: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("> \n");
        return MAIOR;
    } else if (lookahead == '=') {
        goto q68;
    } else {
        return ERROR;
    }

    q68: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf(">= \n");
        return MAIORIGUAL;
    } else {
        return ERROR;
    }

    q67: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("< \n");
        return MENOR;
    } else if (lookahead == '=') {
        goto q69;
    } else {
        return ERROR;
    }

    q69: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("<= \n");
        return MENORIGUAL;
    } else {
        return ERROR;
    }

    q75: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("( \n");
        return ABREPARENTESE;
    } else {
        return ERROR;
    }
    
    q74: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf(") \n");
        return FECHAPARENTESE;
    } else {
        return ERROR;
    }

    q77: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("{ \n");
        return ABRECHAVES;
    } else {
        return ERROR;
    }
    
    q76: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("} \n");
        return FECHACHAVES;
    } else {
        return ERROR;
    }

    q78: lookahead = fgetc(fp);
    if (lookahead == ' ') {
        printf("; \n");
        return PONTOVIRGULA;
    } else {
        return ERROR;
    }

    q89: lookahead = fgetc(fp);
    if (    lookahead == 'a' || lookahead == 'a' || lookahead == 'A' || lookahead == 'b' || lookahead == 'B' || 
            lookahead == 'C' || lookahead == 'd' || lookahead == 'D' || lookahead == 'e' || lookahead == 'E' ||
            lookahead == 'f' || lookahead == 'F' || lookahead == 'g' || lookahead == 'G' || lookahead == 'h' ||
            lookahead == 'H' || lookahead == 'i' || lookahead == 'I' || lookahead == 'J' || lookahead == 'j' ||
            lookahead == 'K' || lookahead == 'k' || lookahead == 'm' || lookahead == 'M' || lookahead == 'n' ||
            lookahead == 'N' || lookahead == 'l' || lookahead == 'L' || lookahead == 'o' || lookahead == 'O' ||
            lookahead == 'p' || lookahead == 'P' || lookahead == 'q' || lookahead == 'Q' || lookahead == 'r' ||
            lookahead == 'R' || lookahead == 's' || lookahead == 'S' || lookahead == 't' || lookahead == 'T' ||
            lookahead == 'U' || lookahead == 'u' || lookahead == 'v' || lookahead == 'V' || lookahead == 'x' ||
            lookahead == 'X' || lookahead == 'w' || lookahead == 'W' || lookahead == 'y' || lookahead == 'Y' || 
            lookahead == 'z' || lookahead == 'Z' || lookahead == 'c' ) {
        goto q90;
    } else {
        return ERROR;
    }

    q90: lookahead = fgetc(fp);
    if (    lookahead == 'a' || lookahead == 'a' || lookahead == 'A' || lookahead == 'b' || lookahead == 'B' || 
            lookahead == 'C' || lookahead == 'd' || lookahead == 'D' || lookahead == 'e' || lookahead == 'E' ||
            lookahead == 'f' || lookahead == 'F' || lookahead == 'g' || lookahead == 'G' || lookahead == 'h' ||
            lookahead == 'H' || lookahead == 'i' || lookahead == 'I' || lookahead == 'J' || lookahead == 'j' ||
            lookahead == 'K' || lookahead == 'k' || lookahead == 'm' || lookahead == 'M' || lookahead == 'n' ||
            lookahead == 'N' || lookahead == 'l' || lookahead == 'L' || lookahead == 'o' || lookahead == 'O' ||
            lookahead == 'p' || lookahead == 'P' || lookahead == 'q' || lookahead == 'Q' || lookahead == 'r' ||
            lookahead == 'R' || lookahead == 's' || lookahead == 'S' || lookahead == 't' || lookahead == 'T' ||
            lookahead == 'U' || lookahead == 'u' || lookahead == 'v' || lookahead == 'V' || lookahead == 'x' ||
            lookahead == 'X' || lookahead == 'w' || lookahead == 'W' || lookahead == 'y' || lookahead == 'Y' || 
            lookahead == 'z' || lookahead == 'Z' || lookahead == 'c' ) {
        goto q90;
    } else if (lookahead == ' ') {
        printf("VARIAVEL \n");
        return VARIAVEL;
    } else {
        return ERROR;
    }

}

int main()
{
    FILE *input, *arq_saida;

    /* Arquivo do codigo AlgC que deve ser analisado */
    input = openFile("codigo.txt");

    /* Arquivo gerado apos analise contendo os tokens */
    arq_saida = fopen("tokens.txt", "w");

    int tam = 0;

    /*ENCONTRANDO O TAMANHO DO ARQUIVO*/
    while(fgetc(input) != EOF){
        fileLenght = fileLenght + 1;
    }

    /*RETORNA PARA O COMEÇO DO ARQUIVO*/
    fseek(input, 0, SEEK_SET);

    while(tam < fileLenght){
       scanner(input, arq_saida);
       tam++;
    }
  
   return 0;
}
