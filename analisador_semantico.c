/* Integrantes:
Leonardo L. R. T. Brandao - 31633528
Felipe Estrela Cardoso - 31618375
Bryam Kim - 31637450
Gustavo Getulio - 31686508
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int linha = 1;
int tam = 0;
#define TAMANHO_MAX_TOKEN 30
#define PROGRAM 5
#define IF 6
#define ELSE 3
#define VOID 4
#define TRUE 1
#define FALSE 0
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
#define FIM 99
#define ERROR -1
int str_to_codigo(char str[TAMANHO_MAX_TOKEN])
{
    if (strcmp(str, "program") == 0)
        return 5;
    if (strcmp(str, "if") == 0)
        return 6;
    if (strcmp(str, "else") == 0)
        return 3;
    if (strcmp(str, "void") == 0)
        return 4;
    if (strcmp(str, "true") == 0)
        return 1;
    if (strcmp(str, "false") == 0)
        return 0;
    if (strcmp(str, "int") == 0)
        return 7;
    if (strcmp(str, "bool") == 0)
        return 8;
    if (strcmp(str, "while") == 0)
        return 9;
    if (strcmp(str, "print") == 0)
        return 30;
    if (strcmp(str, "var") == 0)
        return 10;
    if (strcmp(str, "for") == 0)
        return 11;
    if (strcmp(str, "+") == 0)
        return 12;
    if (strcmp(str, "-") == 0)
        return 13;
    if (strcmp(str, "/") == 0)
        return 14;
    if (strncmp(str, "/*", 2) == 0)
        return 15;
    if (strcmp(str, "*") == 0)
        return 16;
    if (strcmp(str, ",") == 0)
        return 17;
    if (strcmp(str, "!=") == 0)
        return 18;
    if (strcmp(str, "=") == 0)
        return 19;
    if (strcmp(str, "==") == 0)
        return 20;
    if (strcmp(str, ">") == 0)
        return 21;
    if (strcmp(str, ">=") == 0)
        return 22;
    if (strcmp(str, "<") == 0)
        return 31;
    if (strcmp(str, "<=") == 0)
        return 32;
    if (strcmp(str, "{") == 0)
        return 23;
    if (strcmp(str, "}") == 0)
        return 24;
    if (strcmp(str, ";") == 0)
        return 25;
    if (strcmp(str, "(") == 0)
        return 26;
    if (strcmp(str, ")") == 0)
        return 27;
    if (strcmp(str, ":") == 0)
        return 28;
    if (strncmp(str, "_", 1) == 0)
        return 29;
    if (atoi(str) != 0 || strcmp(str, "0") == 0)
        return 33;
}

typedef struct token
{
    int linha;
    int codigo;
    char str[TAMANHO_MAX_TOKEN];
} token_t;

typedef struct node
{
    token_t *token;
    struct node *next;
} node_t;

int match(node_t *head, int palavra);
int program(node_t *head);
int printar(node_t *head);
int comandoRepetitivo(node_t *head);
int relacao(node_t *head);
int expressaoSimples(node_t *head);
int fator(node_t *head);
int boolean(node_t *head);
int termo(node_t *head);
int expressao(node_t *head);
int comandoCondicional(node_t *head);
int listaDeParametros(node_t *head);
int chamadaDeProcedimento(node_t *head);
int atribuicao(node_t *head);
int comando(node_t *head);
int comandoComposto(node_t *head);
int parametroFormal(node_t *head);
int parametrosFormais(node_t *head);
int declaracaoFuncao(node_t *head);
int parteDeclaracaoFuncao(node_t *head);
int listaIdentificadores(node_t *head);
int declaracaoVariavel(node_t *head);
int bloco(node_t *head);

void print_list(node_t *head)
{
    node_t *current = head;

    while (current != NULL)
    {
        printf("Codigo: %d, Linha: %d\n", current->token->codigo, current->token->linha);
        current = current->next;
    }
}

void push_end(node_t *head, token_t *val)
{
    node_t *current = malloc(sizeof(node_t));
    ;
    current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->token = val;
    current->next->next = NULL;
}

void push_start(node_t **head, token_t *val)
{
    node_t *new_node;
    new_node = malloc(sizeof(node_t));

    new_node->token = val;
    new_node->next = *head;
    *head = new_node;
}

node_t *pop(node_t **head)
{
    node_t *retval;
    node_t *next_node = NULL;

    if (*head == NULL)
    {
        retval->next = NULL;
        retval->token = NULL;
        return retval;
    }

    next_node = (*head)->next;
    retval = *head;
    free(*head);
    *head = next_node;

    return retval;
}

int remove_last(node_t *head)
{
    int retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL)
    {
        retval = head->token->codigo;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    node_t *current = head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->token->codigo;
    free(current->next);
    current->next = NULL;
    return retval;
}

node_t *remove_by_index(node_t **head, int n)
{
    int i = 0;
    node_t *retval;
    node_t *current = *head;
    node_t *temp_node = NULL;

    if (n == 0)
    {
        return pop(head);
    }

    for (i = 0; i < n - 1; i++)
    {
        if (current->next == NULL)
        {
            return retval;
        }
        current = current->next;
    }

    temp_node = current->next;
    retval = temp_node;
    current->next = temp_node->next;
    free(temp_node);

    return retval;
}

int fileLenght = 0;

FILE *openFile(char *nomeArq)
{
    FILE *fp;
    fp = fopen(nomeArq, "r");

    if (fp == NULL)
    {
        printf("Arquivo nao encontrado\n");
        exit(0);
    }
    return fp;
}

char scanner(FILE *fp, FILE *tokens, char token_str[])
{
    /* 'lookahead' e o caractere lido a cada goto ate o fim do arquivo (EOF) */
    char token[TAMANHO_MAX_TOKEN] = {'\0'};
    int token_pos = 0;
    char lookahead;

q0:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'p')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q1;
    }
    else if (lookahead == 'i')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q13;
    }
    else if (lookahead == 't')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q19;
    }
    else if (lookahead == 'b')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q24;
    }
    else if (lookahead == 'f')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q29;
    }
    else if (lookahead == 'e')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q35;
    }
    else if (lookahead == 'v')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q46;
    }
    else if (lookahead == 'w')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q40;
    }
    else if (lookahead == '+')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q51;
    }
    else if (lookahead == '-')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q52;
    }
    else if (lookahead == '/')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q53;
    }
    else if (lookahead == '*')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q54;
    }
    else if (lookahead == ',')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q103;
    }
    else if (lookahead == '!')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q55;
    }
    else if (lookahead == '=')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q57;
    }
    else if (lookahead == '>')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q66;
    }
    else if (lookahead == '<')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q67;
    }
    else if (lookahead == '(')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q75;
    }
    else if (lookahead == ')')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q74;
    }
    else if (lookahead == '{')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q77;
    }
    else if (lookahead == '}')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q76;
    }
    else if (lookahead == ';')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q78;
    }
    else if (lookahead == '_')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q89;
    }
    else if (lookahead >= '0' && lookahead <= '9')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q105;
    }
    else if (lookahead == ' ')
    {
        goto q0;
    }
    else if (lookahead == '\0')
    {
        return *token;
    }

q1:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'r')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q2;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q2:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'o')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q3;
    }
    else if (lookahead == 'i')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q9;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q3:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'g')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q4;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q4:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'r')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q5;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q5:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'a')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q6;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q6:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'm')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q7;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q7:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q9:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'n')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q10;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q10:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 't')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q11;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q11:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q13:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'f')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q17;
    }
    else if (lookahead == 'n')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q14;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q14:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 't')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q15;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q15:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q17:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q19:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'r')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q20;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q20:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'u')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q21;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q21:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'e')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q22;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q22:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q24:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'o')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q25;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q25:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'o')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q26;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q26:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'l')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q27;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q27:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }

q29:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'o')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q100;
    }
    else if (lookahead == 'a')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q30;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q30:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'l')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q31;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q31:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 's')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q32;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q32:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'e')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q33;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q33:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q100:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'r')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q101;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q101:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q46:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'o')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q47;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q47:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'i')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q48;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q48:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'd')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q49;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q49:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q40:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'h')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q41;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q41:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'i')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q42;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q42:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'l')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q43;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q43:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'e')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q44;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q44:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q51:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q52:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q53:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else if (lookahead == '*')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q86;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q86:
    lookahead = fgetc(fp);
    tam++;
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
        lookahead == 'z' || lookahead == 'Z')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q87;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q87:
    lookahead = fgetc(fp);
    tam++;
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
        lookahead == 'z' || lookahead == 'Z')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q87;
    }
    else if (lookahead == '*')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q88;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q88:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == '/')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q91;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q91:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q54:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q103:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q55:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == '=')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q56;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q56:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q57:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else if (lookahead == '=')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q58;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q58:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q66:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else if (lookahead == '=')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q68;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q68:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q67:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else if (lookahead == '=')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q69;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q69:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q75:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q74:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q77:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q76:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q78:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q89:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'a' || lookahead == 'a' || lookahead == 'A' || lookahead == 'b' || lookahead == 'B' ||
        lookahead == 'C' || lookahead == 'd' || lookahead == 'D' || lookahead == 'e' || lookahead == 'E' ||
        lookahead == 'f' || lookahead == 'F' || lookahead == 'g' || lookahead == 'G' || lookahead == 'h' ||
        lookahead == 'H' || lookahead == 'i' || lookahead == 'I' || lookahead == 'J' || lookahead == 'j' ||
        lookahead == 'K' || lookahead == 'k' || lookahead == 'm' || lookahead == 'M' || lookahead == 'n' ||
        lookahead == 'N' || lookahead == 'l' || lookahead == 'L' || lookahead == 'o' || lookahead == 'O' ||
        lookahead == 'p' || lookahead == 'P' || lookahead == 'q' || lookahead == 'Q' || lookahead == 'r' ||
        lookahead == 'R' || lookahead == 's' || lookahead == 'S' || lookahead == 't' || lookahead == 'T' ||
        lookahead == 'U' || lookahead == 'u' || lookahead == 'v' || lookahead == 'V' || lookahead == 'x' ||
        lookahead == 'X' || lookahead == 'w' || lookahead == 'W' || lookahead == 'y' || lookahead == 'Y' ||
        lookahead == 'z' || lookahead == 'Z' || lookahead == 'c')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q90;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q90:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'a' || lookahead == 'a' || lookahead == 'A' || lookahead == 'b' || lookahead == 'B' ||
        lookahead == 'C' || lookahead == 'd' || lookahead == 'D' || lookahead == 'e' || lookahead == 'E' ||
        lookahead == 'f' || lookahead == 'F' || lookahead == 'g' || lookahead == 'G' || lookahead == 'h' ||
        lookahead == 'H' || lookahead == 'i' || lookahead == 'I' || lookahead == 'J' || lookahead == 'j' ||
        lookahead == 'K' || lookahead == 'k' || lookahead == 'm' || lookahead == 'M' || lookahead == 'n' ||
        lookahead == 'N' || lookahead == 'l' || lookahead == 'L' || lookahead == 'o' || lookahead == 'O' ||
        lookahead == 'p' || lookahead == 'P' || lookahead == 'q' || lookahead == 'Q' || lookahead == 'r' ||
        lookahead == 'R' || lookahead == 's' || lookahead == 'S' || lookahead == 't' || lookahead == 'T' ||
        lookahead == 'U' || lookahead == 'u' || lookahead == 'v' || lookahead == 'V' || lookahead == 'x' ||
        lookahead == 'X' || lookahead == 'w' || lookahead == 'W' || lookahead == 'y' || lookahead == 'Y' ||
        lookahead == 'z' || lookahead == 'Z' || lookahead == 'c')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q90;
    }
    else if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q105:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead >= '0' && lookahead <= '9')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q105;
    }
    else if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q35:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'l')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q36;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q36:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 's')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q37;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q37:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == 'e')
    {
        token_str[token_pos] = lookahead;
        token_pos++;
        goto q38;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }

q38:
    lookahead = fgetc(fp);
    tam++;
    if (lookahead == ' ' || lookahead == '\n' || lookahead == '\0')
    {
        if (lookahead == '\n' || lookahead == '\0')
            linha++;
        return *token;
    }
    else
    {
        strcpy(token, "ERRO");
        return *token;
    }
}

int match(node_t *head, int palavra)
{
    if (head != NULL)
    {
        if (head->token->codigo == palavra)
        {
            if (head->next != NULL)
                *head = *head->next;
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

int relacao(node_t *head)
{
    if (
        match(head, COMPARACAO) || match(head, DIFERENTE) || match(head, MENOR) ||
        match(head, MAIOR) || match(head, MENORIGUAL) || match(head, MAIORIGUAL))
    {
        return TRUE;
    }
    return FALSE;
}

int variavel(node_t *head)
{
    if (match(head, VARIAVEL))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int fator(node_t *head)
{
    if (variavel(head) || match(head, NUMERO) || match(head, TRUE) || match(head, FALSE) || expressaoSimples(head))
    {
        return TRUE;
    }
    return FALSE;
}

int termo(node_t *head)
{
    if (fator(head))
    {
        if (head->token->codigo == MULTIPLICACAO || head->token->codigo == DIVISAO)
        {
            if ((match(head, MULTIPLICACAO) || match(head, DIVISAO)) && termo(head))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

int expressaoSimples(node_t *head)
{
    if (head->token->codigo == MAIS || head->token->codigo == MENOS)
    {
        if ((match(head, MAIS) || match(head, MENOS)) && termo(head))
        {
            if (head->token->codigo == MAIS || head->token->codigo == MENOS)
            {
                return expressaoSimples(head);
            }
            else
            {
                return TRUE;
            }
            return FALSE;
        }
        return FALSE;
    }
    else if (termo(head))
    {
        if (head->token->codigo == MAIS || head->token->codigo == MENOS)
        {
            return expressaoSimples(head);
        }
        else
        {
            return TRUE;
        }
        return FALSE;
    }
    else
    {
        return FALSE;
    }
}

int expressao(node_t *head)
{
    if (expressaoSimples(head))
    {
        if (relacao(head))
        {
            expressao(head);
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}

int atribuicao(node_t *head)
{
    if (variavel(head))
    {
        if (head->token->codigo == IGUAL)
        {
            if (match(head, IGUAL))
            {
                if (expressao(head) && match(head, PONTOVIRGULA))
                {
                    return TRUE;
                };
            }
        }
    }
}

int listaDeParametros(node_t *head)
{
    if (head->token->codigo == VARIAVEL || head->token->codigo == NUMERO || head->token->codigo == TRUE || head->token->codigo == FALSE)
    {
        if (variavel(head) || match(head, NUMERO) || match(head, TRUE) || match(head, FALSE))
        {
            if (head->token->codigo == VIRGULA)
            {
                if (match(head, VIRGULA))
                {
                    listaDeParametros(head);
                }
            }
            else
            {
                return TRUE;
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int chamadaDeProcedimento(node_t *head)
{
    if (variavel(head))
    {
        if (head->token->codigo == ABREPARENTESE)
        {
            if (match(head, ABREPARENTESE))
            {
                if (listaDeParametros(head))
                {
                    if (head->token->codigo == FECHAPARENTESE)
                    {
                        if (match(head, FECHAPARENTESE))
                        {
                            return TRUE;
                        }
                    }
                }
            }
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    return FALSE;
}

int comandoCondicional(node_t *head)
{
    if (
        match(head, IF) &&
        match(head, ABREPARENTESE) &&
        expressao(head) &&
        match(head, FECHAPARENTESE) &&
        match(head, ABRECHAVES) &&
        comandoComposto(head) &&
        match(head, FECHACHAVES))
    {
        if (head->token->codigo == ELSE)
        {
            if (match(head, ELSE) &&
                match(head, ABRECHAVES) &&
                comandoComposto(head) &&
                match(head, FECHACHAVES))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}

int comandoRepetitivo(node_t *head)
{
    if (
        match(head, WHILE) &&
        match(head, ABREPARENTESE) &&
        expressao(head) &&
        match(head, FECHAPARENTESE) &&
        match(head, ABRECHAVES) &&
        comandoComposto(head) &&
        match(head, FECHACHAVES))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int comandoPrint(node_t *head)
{
    if (head->token->codigo == PRINT)
    {
        if (
            match(head, PRINT) &&
            match(head, ABREPARENTESE) &&
            variavel(head) &&
            match(head, FECHAPARENTESE) &&
            match(head, PONTOVIRGULA))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int comando(node_t *head)
{
    if (
        atribuicao(head) ||
        chamadaDeProcedimento(head) ||
        comandoCondicional(head) ||
        comandoRepetitivo(head) ||
        comandoPrint(head))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int comandoComposto(node_t *head)
{
    if (head->token->codigo == VARIAVEL || head->token->codigo == IF || head->token->codigo == WHILE || head->token->codigo == PRINT)
    {
        if (comando(head))
        {
            if (head->token->codigo == VARIAVEL || head->token->codigo == IF || head->token->codigo == WHILE || head->token->codigo == PRINT)
            {
                return comandoComposto(head);
            }
            else
            {
                return TRUE;
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int parametroFormal(node_t *head)
{
    if (
        (match(head, INT) || match(head, BOOL)) &&
        match(head, VARIAVEL))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int parametrosFormais(node_t *head)
{
    if (head->token->codigo == INT || head->token->codigo == BOOL)
    {
        if (parametroFormal(head))
        {
            if (head->token->codigo == INT || head->token->codigo == BOOL)
            {
                return parametrosFormais(head);
            }
            else
            {
                return TRUE;
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int declaracaoFuncao(node_t *head)
{
    if (
        match(head, VOID) &&
        match(head, VARIAVEL) &&
        match(head, ABREPARENTESE) &&
        (parametrosFormais(head) || 1 == 1) &&
        match(head, FECHAPARENTESE) &&
        match(head, ABRECHAVES) &&
        bloco(head) &&
        match(head, FECHACHAVES))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int parteDeclaracaoFuncao(node_t *head)
{
    if (head->token->codigo == VOID)
    {
        if (declaracaoFuncao(head))
        {
            if (head->token->codigo == VOID)
            {
                return parteDeclaracaoFuncao(head);
            }
            else
            {
                return TRUE;
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}
int listaIdentificadores(node_t *head)
{
    if (head->token->codigo == VARIAVEL)
    {
        match(head, VARIAVEL);
        if (head->token->codigo == VIRGULA)
        {
            match(head, VIRGULA);
            return listaIdentificadores(head);
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}

int declaracaoVariavel(node_t *head)
{
    if (
        (match(head, BOOL) || match(head, INT)) &&
        listaIdentificadores(head) &&
        match(head, PONTOVIRGULA))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int parteDeclaracaoVariavel(node_t *head)
{
    if (head->token->codigo == BOOL || head->token->codigo == INT)
    {
        if (declaracaoVariavel(head))
        {
            if (head->token->codigo == BOOL || head->token->codigo == INT)
            {
                return parteDeclaracaoVariavel(head);
            }
            else
            {
                return TRUE;
            }
        }
        else
        {
            return FALSE;
        }
    }
}

int bloco(node_t *head)
{
    if (head->token->codigo == BOOL || head->token->codigo == INT)
    {
        if (parteDeclaracaoVariavel(head))
        {
            if (head->token->codigo == VOID)
            {
                if (parteDeclaracaoFuncao(head))
                {
                    return comandoComposto(head);
                }
                else
                {
                    return FALSE;
                }
            }
            else
            {

                return comandoComposto(head);
            }
        }
        else
        {
            return FALSE;
        }
    }
    else if (head->token->codigo == VOID)
    {
        if (parteDeclaracaoFuncao(head))
        {
            return comandoComposto(head);
        }
        else
        {
            return FALSE;
        }
    }
    else if (head->token->codigo == VARIAVEL || head->token->codigo == IF || head->token->codigo == WHILE || head->token->codigo == PRINT)
    {
        return comandoComposto(head);
    }
    else
    {
        return FALSE;
    }
}
int program(node_t *head)
{
    if (match(head, PROGRAM) &&
        match(head, VARIAVEL) &&
        match(head, ABRECHAVES) &&
        bloco(head) &&
        match(head, FECHACHAVES))
    {
        return (TRUE);
    }
    return (FALSE);
}

int main()
{
    FILE *input, *arq_saida;

    node_t *head = NULL;
    head = malloc(sizeof(node_t));
    head->next = NULL;

    /* Arquivo do codigo AlgC que deve ser analisado */
    input = openFile("codigo.txt");

    /* Arquivo gerado apos analise contendo os tokens */
    arq_saida = fopen("tokens.txt", "w");

    tam = 0;

    /*ENCONTRANDO O TAMANHO DO ARQUIVO*/
    while (fgetc(input) != EOF)
    {
        fileLenght = fileLenght + 1;
    }

    /*RETORNA PARA O COMEÇO DO ARQUIVO*/
    fseek(input, 0, SEEK_SET);
    if (head == NULL)
    {
        return 1;
    }

    while (tam < fileLenght)
    {
        token_t *t = malloc(sizeof(token_t));
        char token_str[TAMANHO_MAX_TOKEN] = {'\0'};
        scanner(input, arq_saida, token_str);
        t->linha = linha;
        int codigo;
        codigo = str_to_codigo(token_str);
        t->codigo = codigo;
        strcpy(t->str, token_str);
        fprintf(arq_saida, "%s \n", token_str);
        push_end(head, t);
        printf("token %s\n", t->str);
        if (token_str == "ERRO")
        {
            printf("ERRO LEXICO na linha %d\n", linha);
            break;
        }
    }
    pop(&head);

    if (program(head))
    {
        printf("Analise sintatica OK");
    }
    else
    {
        printf("ERRO SINTATICO na linha %d", head->token->linha);
    };
    return 0;
}
