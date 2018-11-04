/* Integrantes:
Leonardo L. R. T. Brandao - 31633528
Felipe Estrela Cardoso - 31618375
Bryam Kim - 31637450
Gustavo Getulio - 31686508
*/
int linha = 1;
int tam = 0;
#define PROGRAM 1 
#define IF 2
#define ELSE 3 
#define VOID 4 
#define TRUE 5 
#define FALSE 6 
#define INT 7 
#define BOOL 8 
#define WHILE 9 
#define PRINT 30
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
#define MENOR 31
#define MENORIGUAL 32
#define ABRECHAVES 23
#define FECHACHAVES 24
#define PONTOVIRGULA 25
#define ABREPARENTESE 26
#define FECHAPARENTESE 27
#define DOISPONTOS 28
#define VARIAVEL 29
#define NUMERO 33
#define ESPACO 34
#define ERROR -1

/* Nome do arquivo com o codigo a ser analisado: codigo.txt
   Nome do arquivo produzido contendo os tokens: tokens.txt */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct token
{
    int linha;
    int codigo;
} token_t;

typedef struct node
{
    token_t *token;
    struct node *next;
} node_t;

void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("Codigo: %d, Linha: %d\n", current->token->codigo, current->token->linha);
        current = current->next;
    }
}

void push_end(node_t * head, token_t * val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->token = val;
    current->next->next = NULL;
}

void push_start(node_t ** head, token_t *val) {
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->token = val;
    new_node->next = *head;
    *head = new_node;
}

int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->token->codigo;
    free(*head);
    *head = next_node;

    return retval;
}

int remove_last(node_t * head) {
    int retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->token->codigo;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->token->codigo;
    free(current->next);
    current->next = NULL;
    return retval;

}

int remove_by_index(node_t ** head, int n) {
    int i = 0;
    int retval = -1;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    retval = temp_node->token->codigo;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

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
    tam ++;
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
    } else if (lookahead == 'e'){
        goto q35;
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
    } else if (lookahead >= '0' && lookahead <= '9'){
        goto q105;
    } else if (lookahead == '\0') {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ESPACO;
    }

    q1: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'r') {
        goto q2;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q2: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'o') {
        goto q3;
    } else if(lookahead == 'i'){
        goto q9;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q3: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'g') {
        goto q4;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q4: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'r') {
        goto q5;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q5: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'a') {
        goto q6;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q6: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'm') {
        goto q7;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q7: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("PROGRAM  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", PROGRAM);
        return PROGRAM;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q9: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'n') {
        goto q10;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
   
    q10: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 't') {
        goto q11;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q11: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("PRINT  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", PRINT);
        return PRINT;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q13: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'f') {
        goto q17;
    } else if (lookahead == 'n'){
        goto q14;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q14: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 't') {
        goto q15;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q15: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("INT  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", INT);
        return INT;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q17: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("IF  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", IF);
        return IF;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q19: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'r') {
        goto q20;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q20: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'u') {
        goto q21;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q21: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'e') {
        goto q22;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q22: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("true  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", TRUE);
        return TRUE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q24: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'o') {
        goto q25;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
  
    q25: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'o') {
        goto q26;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
   
    q26: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'l') {
        goto q27;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q27: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("bool  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", BOOL);
        return BOOL;
    }

    q29: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'o') {
        goto q100;
    } else if(lookahead == 'a'){
        goto q30;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q30: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'l') {
        goto q31;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q31: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 's') {
        goto q32;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
   
    q32: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'e') {
        goto q33;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q33: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("false  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", FALSE);
        return FALSE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q100: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'r') {
        goto q101;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q101: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("for  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", FOR);
        return FOR;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q46: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'o') {
        goto q47;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q47: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'i') {
        goto q48;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q48: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'd') {
        goto q49;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q49: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("void  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", VOID);
        return VOID;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q40: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'h') {
        goto q41;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q41: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'i') {
        goto q42;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q42: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'l') {
        goto q43;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q43: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'e') {
        goto q44;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q44: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("while  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", WHILE);
        return WHILE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q51: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("+  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MAIS);
        return MAIS;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q52: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("-  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MENOS);
        return MENOS;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q53: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("/  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", DIVISAO);
        return DIVISAO;
    } else if (lookahead == '*') {
        goto q86;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q86: lookahead = fgetc(fp);
    tam ++;
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
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q87: lookahead = fgetc(fp);
    tam ++;
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
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q88: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == '/') {
        goto q91;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q91: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("COMENTARIO  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", COMENTARIO);
        return COMENTARIO;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q54: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("*  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MULTIPLICACAO);
        return MULTIPLICACAO;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q103: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf(",  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", VIRGULA);
        return VIRGULA;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q55: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == '=') {
        goto q56;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q56: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("DIFERENTE  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", DIFERENTE);
        return DIFERENTE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q57: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("=  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", IGUAL);
        return IGUAL;
    } else if (lookahead == '=') {
        goto q58;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q58: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("==  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", COMPARACAO);
        return COMPARACAO;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q66: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf(">  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MAIOR);
        return MAIOR;
    } else if (lookahead == '=') {
        goto q68;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q68: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf(">=  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MAIORIGUAL);
        return MAIORIGUAL;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q67: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("<  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MENOR);
        return MENOR;
    } else if (lookahead == '=') {
        goto q69;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q69: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("<=  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", MENORIGUAL);
        return MENORIGUAL;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q75: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("(  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", ABREPARENTESE);
        return ABREPARENTESE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q74: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf(")  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", FECHAPARENTESE);
        return FECHAPARENTESE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q77: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("{  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", ABRECHAVES);
        return ABRECHAVES;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
    
    q76: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("}  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", FECHACHAVES);
        return FECHACHAVES;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q78: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf(";  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", PONTOVIRGULA);
        return PONTOVIRGULA;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q89: lookahead = fgetc(fp);
    tam ++;
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
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q90: lookahead = fgetc(fp);
    tam ++;
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
    } else if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("VARIAVEL  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", VARIAVEL);
        return VARIAVEL;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q105: lookahead = fgetc(fp);
    tam ++;
    if (lookahead >= '0' && lookahead <= '9') {
        goto q105;
    } else if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("NUMERO  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", NUMERO); 
        return NUMERO;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q35: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'l') {
        goto q36;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q36: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 's') {
        goto q37;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q37: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == 'e') {
        goto q38;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }

    q38: lookahead = fgetc(fp);
    tam ++;
    if (lookahead == ' ' || lookahead == '\n'  ||  lookahead == '\0') {
        printf("ELSE  - Linha: %d\n", linha);
        if(lookahead == '\n' || lookahead == '\0') linha++;
        fprintf(tokens, "TOKEN %d \n", ELSE);
        return ELSE;
    } else {
        fprintf(tokens, "ERRO LEXICO LINHA %d \n", linha);
        return ERROR;
    }
}

int main()
{
    FILE *input, *arq_saida;

    node_t *head = NULL;
    head = malloc(sizeof(node_t));

    /* Arquivo do codigo AlgC que deve ser analisado */
    input = openFile("codigo.txt");

    /* Arquivo gerado apos analise contendo os tokens */
    arq_saida = fopen("tokens.txt", "w");

    tam = 0;

    /*ENCONTRANDO O TAMANHO DO ARQUIVO*/
    while(fgetc(input) != EOF){
        fileLenght = fileLenght + 1;
    }

    printf("TAMANHO DO ARQUIVO %d \n", fileLenght);

    /*RETORNA PARA O COMEÇO DO ARQUIVO*/
    fseek(input, 0, SEEK_SET);

    while(tam < fileLenght){
       scanner(input, arq_saida);
    }
  
   return 0;
}
