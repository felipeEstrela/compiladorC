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
    int tipo;
    int escopo;
} token_t;

typedef struct node
{
    token_t *token;
    struct node *next;
} node_t;

void adicionaTabelaSimbolos(node_t *head, int tipo);
int atribuicao(node_t *head);
int bloco(node_t *head);
int boolean(node_t *head);
int chamadaDeProcedimento(node_t *head);
int comando(node_t *head);
int comandoPrint(node_t *head);
int comandoRepetitivo(node_t *head);
int comandoComposto(node_t *head);
int comandoCondicional(node_t *head);
int declaracaoFuncao(node_t *head);
int declaracaoVariavel(node_t *head);
int expressao(node_t *head);
int expressaoSimples(node_t *head);
int fator(node_t *head);
int listaIdentificadores(node_t *head, int tipo);
int listaDeParametros(node_t *head);
int match(node_t *head, int palavra);
int parametroFormal(node_t *head);
int parametrosFormais(node_t *head);
int parteDeclaracaoFuncao(node_t *head);
int program(node_t *head);
int relacao(node_t *head);
int termo(node_t *head);

node_t *tabelaSimbolos;
int linha = 1;
int tam = 0;
int escopo = 1;
int fileLenght = 0;
int tipoVal = 0;

void print_list(node_t *head)
{
    node_t *current = head->next;

    while (current != NULL)
    {
        if (current->token->codigo && current->token->linha)
        {
            printf("\nToken: %s Tipo: %d Escopo: %d Linha: %d", current->token->str, current->token->tipo, current->token->escopo, current->token->linha);
        }
        current = current->next;
    }
}

void push_end(node_t *head, token_t *val)
{
    node_t *current = malloc(sizeof(node_t));

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

void adicionaTabelaSimbolos(node_t *tabela, int tipo)
{
    token_t *token = tabela->token;
    token->tipo = tipo;
    token->escopo = escopo;
    push_end(tabelaSimbolos, token);
}

int procuraTabelaSimbolos(node_t *tabela, token_t *token)
{
    node_t *current = tabela->next;
    int achou = 0;
    int tipo = 0;
    int escopo = 0;

    while (current != NULL)
    {
        if (strcmp(token->str, current->token->str) == 0)
        {
            achou = 1;
            if (current->token->escopo > escopo)
            {
                tipo = current->token->tipo;
            }
        }
        current = current->next;
    }
    if (achou == 1)
    {
        return tipo;
    }
    else
    {
        return ERROR;
    }
}

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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
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
        return ERROR;
    }
}

int match(node_t *head, int palavra)
{
    if (head != NULL)
    {
        if (head->token->codigo == palavra)
        {
            if (head->token->codigo == ABRECHAVES)
                escopo++;
            if (head->token->codigo == FECHACHAVES)
                escopo--;
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
    if (tipoVal == head->token->tipo)
    {
        if (variavel(head) || match(head, NUMERO) || match(head, TRUE) || match(head, FALSE) || expressaoSimples(head))
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
        char tipoValStr[5];
        char tiporValStr[5];
        if (head->token->tipo == INT)
        {
            strcpy(tipoValStr, "bool");
            strcpy(tiporValStr, "int");
        }
        else
        {
            strcpy(tipoValStr, "int");
            strcpy(tiporValStr, "bool");
        }
        printf("Erro Semantico - Tentando atribuir um valor %s a uma variavel %s", tiporValStr, tipoValStr);
    }
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
    if ((tipoVal = procuraTabelaSimbolos(tabelaSimbolos, head->token)) != ERROR)
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
    else
    {
        printf("ERRO SEMANTICO - Tentativa de atribuir para a variavel nao existente [ %s ]", head->token->str);
        return FALSE;
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
            printf("\nTabela de simbolos\n");
            print_list(tabelaSimbolos);
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
        comandoPrint(head) ||
        atribuicao(head) ||
        chamadaDeProcedimento(head) ||
        comandoCondicional(head) ||
        comandoRepetitivo(head))
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
    int tipo;
    if (head->token->codigo == INT)
    {
        head->token->tipo = INT;
        tipo = INT;
    }
    if (head->token->codigo == BOOL)
    {
        head->token->tipo = BOOL;
        tipo = BOOL;
    }
    if ((match(head, INT) || match(head, BOOL)))
    {
        adicionaTabelaSimbolos(head, tipo);
        if (match(head, VARIAVEL))
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
    int tipo;
    if (head->token->codigo == VOID)
    {
        head->token->tipo = VOID;
        tipo = VOID;
    }
    if (match(head, VOID))
    {
        adicionaTabelaSimbolos(head, tipo);
        if (
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

int listaIdentificadores(node_t *head, int tipo)
{
    if (head->token->codigo == VARIAVEL)
    {
        adicionaTabelaSimbolos(head, tipo);
        match(head, VARIAVEL);
        if (head->token->codigo == VIRGULA)
        {
            match(head, VIRGULA);
            return listaIdentificadores(head, tipo);
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
    int tipo;
    if (head->token->codigo == BOOL)
    {
        head->token->tipo = BOOL;
        tipo = BOOL;
    }
    if (head->token->codigo == INT)
    {
        head->token->tipo = INT;
        tipo = INT;
    }
    if (
        (match(head, BOOL) || match(head, INT)) &&
        listaIdentificadores(head, tipo) &&
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
    int tipo;
    if (head->token->codigo == PROGRAM)
    {
        head->token->tipo = PROGRAM;
        tipo = PROGRAM;
    }
    if (match(head, PROGRAM))
    {
        adicionaTabelaSimbolos(head, tipo);
        if (match(head, VARIAVEL) &&
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
    return FALSE;
}

int main()
{
    FILE *input, *arq_saida;

    node_t *listaTokens = NULL;
    listaTokens = malloc(sizeof(node_t));
    listaTokens->next = NULL;

    tabelaSimbolos = malloc(sizeof(node_t));
    tabelaSimbolos->next = NULL;

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
    if (listaTokens == NULL)
    {
        return 1;
    }

    while (tam < fileLenght)
    {
        token_t *t = malloc(sizeof(token_t));
        char token_str[TAMANHO_MAX_TOKEN] = {'\0'};
        int erro = 0;
        erro = scanner(input, arq_saida, token_str);

        t->linha = linha;

        int codigo = str_to_codigo(token_str);
        if (codigo == 1)
            t->tipo = BOOL;
        if (codigo == 0)
            t->tipo = BOOL;
        if (codigo == 33)
            t->tipo = INT;
        t->codigo = codigo;

        strcpy(t->str, token_str);

        push_end(listaTokens, t);

        printf("token %s\n", t->str);
        fprintf(arq_saida, "%s \n", token_str);

        if (erro == -1)
        {
            printf("\nERRO LEXICO no token %s - linha %d\n", t->str, linha);
            return 0;
        }
    }

    pop(&listaTokens);

    if (program(listaTokens))
    {
        printf("\nAnalise sintatica OK");
    }
    else
    {
        printf("\nERRO SINTATICO na linha %d", listaTokens->token->linha);
    };

erroSemantico:
    return 0;
}
