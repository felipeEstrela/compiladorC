#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

/* Participantes
* Lucas Vargas      - 31637213
* Patrick Andrade   - 31527914
* Pedro Mangino     - 31617980
*/

// DEFINIÇÃO DOS TOKENS
#define TRUE 1
#define FALSE 0
#define ERRO 999

#define PROGRAM 10
#define PRINT 11
#define ID 12
#define ABRE_PARENTESES 13
#define FECHA_PARENTESES 14
#define VIRGULA 15
#define PONTO_VIRGULA 16
#define ABRE_CHAVES 17
#define FECHA_CHAVES 18
#define INTEIRO 19
#define BOOLEAN 20
#define VOID 21
#define IF 22
#define IGUAL 23
#define MENOR 24
#define MAIOR 25
#define NUMERO 26 
#define SOMA 27
#define SUBTRACAO 28
#define MULTIPLICACAO 29
#define DIVISAO 30
#define WHILE 31
#define ELSE 32
#define MAIOR_IGUAL 33
#define MENOR_IGUAL 34
#define IGUALDADE 35
#define DIFERENCA 36
#define ESPACO 37
#define COMENTARIO 38


char lookahead;
FILE *entrada, *saida;
int tamanhoArquivo=0, posicao = 0, posicaoInicial = 0,posicaoFinal = 0, posicaoSintaticaIni = 0, posicaoSintaticaFin = 0, lookaheadTOKEN = -1, linha = 1;


int scanner(char programaFonte[]);
FILE *abrirArquivo(char *nome, char *flags);
void escreverUltimoToken(char *programaFonte,int erro);
int match(int token, char programaFonte[]);
int program(char programaFonte[]);
int printar(char programaFonte[]);
int comandoRepetitivo(char programaFonte[]);
int relacao(char programaFonte[]);
int expressaoSimples(char programaFonte[]);
int fator(char programaFonte[]);
int boolean(char programaFonte[]);
int termo(char programaFonte[]);
int expressao(char programaFonte[]);
int comandoCondicional(char programaFonte[]);
int listaParametros(char programaFonte []);
int chamadaProcedimento(char programaFonte []);
int atribuicao(char programaFonte []);
int comando(char programaFonte [] );
int comandoComposto(char programaFonte [] );
int parametroFormal(char programaFonte [] );
int parametrosFormais(char programaFonte [] );
int declaracaoFuncao(char programaFonte [] );
int parteDeclaracaoFuncao(char programaFonte [] );
int listaIdentificadores(char programaFonte [] );
int declaracaoVariavel(char programaFonte []);
int bloco(char programaFonte []);
void trataErro(char *programaFonte);

int main() {    

    entrada = abrirArquivo("entrada.txt","r");
    saida   = abrirArquivo("saida.txt","w");
    // Conta quantos caracteres existem no arquivo
    char ch;
    while("loop_infinito" == "loop_infinito"){
        ch = fgetc(entrada);
        if (ch == EOF)
            break;        

        tamanhoArquivo++;
    }
    
    // Move o ponteiro novamente para o começo do arquivo
    fseek(entrada, 0, SEEK_SET);
    char programaFonte[tamanhoArquivo];

    //passando o arquivo de entrada para um vetor
    int i;
    for(i = 0; i < tamanhoArquivo; i++){
        programaFonte[i] = fgetc(entrada);        
    }

     
    // chamando a analise
    if(program(programaFonte)){
        printf("Programa válido\n");
    }
    else
    {   
        posicaoSintaticaFin = posicao;        
        trataErro(programaFonte);
    }

    // antiga analise léxica (manter no código para possível uso futuro)
    /* while(posicao < tamanhoArquivo){
        // CASO SEJA UM TOKEN VALIDO
        if ( scanner(programaFonte ) != ERRO ){
            escreverUltimoToken(programaFonte,0);
        }
        else
        {
            escreverUltimoToken(programaFonte,1);
            fclose(entrada);
            fclose(saida);
            return 1;
        }
    } */

    fclose(entrada);
    fclose(saida);
}


// função que faz a analise léxica e retorna o código do token lido ou erro caso não seja reconhecido o token
int scanner(char programaFonte[]){        
    
    

    // (?) Estado inicial, nenhum caractere for lido ainda
    q0: posicaoInicial = posicao;
        lookahead = programaFonte[posicao++];        
            
        //lookahead = programaFonte[posicao++];
            if (lookahead == 'p'){
                goto q1;
            }
            else if (lookahead == '_')
            {                    
                goto q92;
            }
            else if (lookahead == '=')
            {                    
                goto q62;
            }
            else if (lookahead == '{')                
            {
                goto q13;
            }
            else if (lookahead == '}')                
            {
                goto q18;
            }
            else if (lookahead == 'i')
            {
                goto q15;
            }
            else if (lookahead == 'e')
            {
                goto q21;
            }
            else if (lookahead == 'b')
            {
                goto q26;
            }
            else if (lookahead == 'v')
            {
                goto q33;
            }
            else if (lookahead == 't')
            {
                goto q38;
            }
            else if (lookahead == 'f')
            {
                goto q43;
            }
            else if (lookahead == 'w')
            {
                goto q82;
            }                
            else if (lookahead == '<')
            {
                goto q57;
            }
            else if (lookahead == '>')
            {
                goto q58;
            }
            else if (lookahead == '!')
            {
                goto q59;
            }
            else if (lookahead == '(')
            {
                goto q71;
            }
            else if (lookahead == ')')
            {
                goto q72;
            }
            else if (lookahead == ',')
            {
                goto q73;
            }
            else if (lookahead == ';')
            {
                goto q74;
            }
            else if (lookahead == '+')
            {
                goto q49;
            }
            else if (lookahead == '-')
            {
                goto q51;
            }
            else if (lookahead == '*')
            {
                goto q55;
            }
            else if (lookahead == '/')
            {
                goto q53;
            }
            else if (lookahead >= '0' && lookahead <= '9'  )
            {
                goto q100;
            }
            else if (lookahead == ' '   || lookahead == '\0')
            {
                goto q0;
                /* posicaoFinal = posicao;
                return ESPACO; */
            }            
            else if (lookahead = '\n')
            {
                linha++;
                goto q0;
            }
            else{
                posicaoFinal = posicao;
                return ERRO;
            }

    // p(r)
    q1:lookahead = programaFonte[posicao++];        
        if (lookahead == 'r') {
            goto q2;
        }

        posicaoFinal = posicao;
        return ERRO;
    
    // pr(o || i) 
    q2:lookahead = programaFonte[posicao++];         
        if (lookahead == 'o') {
            goto q3;            
        }
        else if (lookahead == 'i')
        {
            goto q9;
        }        
        
        posicaoFinal = posicao;
        return ERRO;
    
    // pro(g)
    q3:lookahead = programaFonte[posicao++];        
        if (lookahead == 'g') {
            goto q4;
        }

        posicaoFinal = posicao;
        return ERRO;
    
    // prog(r)
    q4:lookahead = programaFonte[posicao++];        
        if (lookahead == 'r') {
            goto q5;
        }

        posicaoFinal = posicao;
        return ERRO;

    // progr(a)
    q5:lookahead = programaFonte[posicao++];        
        if (lookahead == 'a') {
            goto q6;
        }

        posicaoFinal = posicao;
        return ERRO;
    
    //progra(m)
    q6: lookahead = programaFonte[posicao++];        
          if (lookahead == 'm') {
            goto q7;
        }

        posicaoFinal = posicao;
        return ERRO;

    // program(blank_space)
    q7:lookahead = programaFonte[posicao++]; 
        if(lookahead == '\n') linha++;

        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0') {            
            goto q8;
        }

        posicaoFinal = posicao;
        return ERRO;

    // estado final PROGRAM
    q8:posicaoFinal = posicao;
        return PROGRAM;
    
    // pri(n)
    q9: lookahead = programaFonte[posicao++];        
        if (lookahead == 'n') {
            goto q10;
        }

        posicaoFinal = posicao;
        return ERRO;
    
    // prin(t)
    q10: lookahead = programaFonte[posicao++];        
        if (lookahead == 't') {
            goto q11;
        }

        posicaoFinal = posicao;
        return ERRO;
    // print(blank_space)
    q11: lookahead = programaFonte[posicao++];      
        if(lookahead == '\n') linha++;  
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0') {            
            goto q12;
        }

        posicaoFinal = posicao;
        return ERRO;

    // ESTADO FINAL print
    q12:posicaoFinal = posicao;
        return PRINT;

    // { ( blank_space )
    q13:lookahead = programaFonte[posicao++];        
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q14;
        }
        posicaoFinal = posicao;
        return ERRO;

    // ESTADO FINAL ( { )
    q14:posicaoFinal = posicao;
        return ABRE_CHAVES;

    // i( f || n)
    q15:lookahead = programaFonte[posicao++];    
    if (lookahead == 'n') {
            goto q16;
    }
    else if (lookahead = 'f')
    {
        goto q19;
    }
    else{
        posicaoFinal = posicao;
        return ERRO;
    }

    // in(t)
    q16:lookahead = programaFonte[posicao++];
    
    if (lookahead == 't') {
        goto q17;
    }
    else
    {
       posicaoFinal = posicao;
        return ERRO;
    }

    //int (blank_space)
    q17:lookahead = programaFonte[posicao++];    
        if(lookahead == '\n') linha++;    
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q25;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        } 
    

    
     // } ( blank_space )
    q18:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0') {            
            goto q20;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // if (blank_space)
    q19:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q30;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }        


    // ESTADO FINAL ( } )
    q20:posicaoFinal = posicao;
        return FECHA_CHAVES;

    // e (l)
    q21:lookahead = programaFonte[posicao++];
        if (lookahead == 'l') {
            goto q22;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }   
    // el(s)
    q22:lookahead = programaFonte[posicao++];
        if (lookahead == 's') {
            goto q23;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // els(e)
    q23:lookahead = programaFonte[posicao++];
        if (lookahead == 'e') {
            goto q24;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // else (blank_space)
    q24:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;        
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q31;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }  

    // ESTADO FINAL  int
    q25:posicaoFinal = posicao;        
        return INTEIRO;

    // b (o)
    q26:lookahead = programaFonte[posicao++];
        if (lookahead == 'o') {            
            goto q27;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // bo (o)
    q27:lookahead = programaFonte[posicao++];
        if (lookahead == 'o') {            
            goto q28;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // boo(l)
    q28:lookahead = programaFonte[posicao++];
        if (lookahead == 'l') {            
            goto q29;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // bool (BLANK_SPACE)
     q29:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q32;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // ESTADO FINAL  if
    q30:posicaoFinal = posicao;
        return IF;
    
    // ESTADO FINAL  else
    q31:posicaoFinal = posicao;
        return ELSE;
    
     // ESTADO FINAL  bool
    q32:posicaoFinal = posicao;
        return BOOLEAN;

    // v(o)
    q33:lookahead = programaFonte[posicao++];
        if (lookahead == 'o') {            
            goto q34;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // vo(i)
    q34:lookahead = programaFonte[posicao++];
        if (lookahead == 'i') {            
            goto q35;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // voi(d)
    q35:lookahead = programaFonte[posicao++];
        if (lookahead == 'd') {            
            goto q36;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // void (BLANK_SPACE)
    q36:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q52;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // ESTADO FINAL true
    q37:posicaoFinal = posicao;        
        return TRUE;

    // t(r)
    q38:lookahead = programaFonte[posicao++];
        if (lookahead == 'r') {            
            goto q39;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // tr(u)
    q39:lookahead = programaFonte[posicao++];
        if (lookahead == 'u') {            
            goto q40;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // tru(e)
    q40:lookahead = programaFonte[posicao++];
        if (lookahead == 'e') {            
            goto q41;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // true (BLANK_SPACE)
    q41:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q37;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
    // ESTADO FINAL false 
    q42:posicaoFinal = posicao;
        return FALSE;
    
    // f(a)
    q43:lookahead = programaFonte[posicao++];
        if (lookahead == 'a') {
            goto q44;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // fa(l)
    q44:lookahead = programaFonte[posicao++];
        if (lookahead == 'l') {
            goto q45;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // fal(s)
    q45:lookahead = programaFonte[posicao++];
        if (lookahead == 's') {
            goto q46;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // fals(e)
    q46:lookahead = programaFonte[posicao++];
        if (lookahead == 'e') {
            goto q47;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
     // false (BLANK_SPACE)
    q47:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q42;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // ESTADO FINAL + 
    q48:posicaoFinal = posicao;
        return SOMA;

    // + (BLANK_SPACE)
    q49:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q48;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // ESTADO FINAL -
    q50:posicaoFinal = posicao;
        return SUBTRACAO;

    // - (BLANK_SPACE)
    q51:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q50;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

     // ESTADO FINAL  void
    q52:posicaoFinal = posicao;
        return VOID;

    // / (BLANK_SPACE)
    q53:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q54;
        }
        else if (lookahead == '*')
        {
            goto q88;
        }        
        else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
    // ESTADO FINAL /
    q54:posicaoFinal = posicao;
        return DIVISAO;

    // * (BLANK_SPACE)
    q55:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q56;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
     // ESTADO FINAL *
    q56:posicaoFinal = posicao;
        return MULTIPLICACAO;

    // < (BLANK_SPACE || = )
    q57:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q63;
        }
        else if (lookahead == '=')
        {
            goto q75;
        }
        
        else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // > (BLANK_SPACE || = )
    q58:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q64;
        }
        else if (lookahead == '=')
        {
            goto q76;
        }
        
        else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // ! (=)
    q59:lookahead = programaFonte[posicao++];
        if (lookahead == '=')
        {
            goto q66;
        }        
        else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
    // = (ESPACO || = )
    q62:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++; 
        if (lookahead == '=') {
            goto q68;
        }
        else if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' )
        {
            goto q69;
        }
        else
        {
            posicaoFinal = posicao;
            return ERRO;
        }

    // ESTADO FINAL <
    q63:posicaoFinal = posicao;
        return MENOR;

    // ESTADO FINAL >
    q64:posicaoFinal = posicao;
        return MAIOR;

     // ESTADO FINAL !=
    q65:posicaoFinal = posicao;
        return DIFERENCA;

    // != (BLANKSPACE)
    q66:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {
            goto q65;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // ESTADO FINAL <=
    q67:posicaoFinal = posicao;
        return MENOR_IGUAL;

    // == (BLANKSPACE)
    q68:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {
            goto q70;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // ESTADO FINAL  igual
    q69:posicaoFinal = posicao;
        return IGUAL;

    // ESTADO FINAL  == 
    q70:posicaoFinal = posicao;
        return IGUALDADE;

    // "(" (BLANKSPACE)
    q71:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q78;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // ")" (BLANKSPACE)
    q72:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q79;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    // , (BLANKSPACE)
    q73:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {            
            goto q80;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // ; (BLANK_SPACE)
    q74:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {
            goto q81;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }

    //  <= (BLANK_SPACE)
    q75:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {
            goto q67;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    //  >= (BLANK_SPACE)
    q76:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {
            goto q77;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // ESTADO FINAL  >=
    q77:posicaoFinal = posicao;
        return MAIOR_IGUAL;

    // ESTADO FINAL  ABRE PARENTESES
    q78:posicaoFinal = posicao;
        return ABRE_PARENTESES;

    // ESTADO FINAL  FECHA PARENTESES
    q79:posicaoFinal = posicao;
        return FECHA_PARENTESES;

    // ESTADO FINAL  Virgula
    q80:posicaoFinal = posicao;
        return VIRGULA;

    // ESTADO FINAL  ponto e Virgula
    q81:posicaoFinal = posicao;
        return PONTO_VIRGULA;

    // w (h)
    q82:lookahead = programaFonte[posicao++];
        if (lookahead == 'h'  ) {
            goto q83;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // wh(i)
    q83:lookahead = programaFonte[posicao++];
        if (lookahead == 'i'  ) {
            goto q84;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // whi(l)
    q84:lookahead = programaFonte[posicao++];
        if (lookahead == 'l'  ) {
            goto q85;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    // whil(e)
    q85:lookahead = programaFonte[posicao++];
        if (lookahead == 'e'  ) {
            goto q86;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
    // while (BLANK_SPACE)
    q86:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ) {
            goto q87;
        }else{
            posicaoFinal = posicao;
            return ERRO;
        }
    
    // ESTADO FINAL WHILE
    q87: posicaoFinal = posicao;
        return WHILE;

    // COMENTÁRIOS
    q88:lookahead = programaFonte[posicao++];
        if(lookahead == '*'){
            goto q89;
        }else{
            goto q88;
        }

    // COMENTÁRIOS
    q89:lookahead = programaFonte[posicao++];
        if(lookahead == '*'){
            goto q89;
        }
        else if (lookahead == '/')
        {
            goto q90;
        }        
        else{
            goto q88;
        }        

    // COMENTÁRIOS /
    q90:lookahead = programaFonte[posicao++];
        if(lookahead == '\n') linha++;
        if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' ){
            goto q91;
        }
        else
        {
            posicaoFinal = posicao;
            return ERRO;
        }
    
    // ESTADO FINAL COMENTARIO
    q91:posicaoFinal = posicao;
        return COMENTARIO;

    // _(<letras>)
    q92:lookahead = programaFonte[posicao++];        
        if(lookahead == '\n') linha++;
        if (isalpha(lookahead ) ) {            
            goto q92;
        }
        else if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0' )
        {
            goto q93;
        }
        else
        {
            posicaoFinal = posicao;
            return ERRO;
        }  
      
    // ESTADO FINAL DE UM IDENTIFICADOR
    q93: posicaoFinal = posicao;
        return ID;

    // Verificando se é um numero
    q100:lookahead = programaFonte[posicao++];        
        if(lookahead == '\n') linha++;
        if (lookahead >= '0' && lookahead <= '9' ) {
            goto q100;
        }
        else if (lookahead == ' '  || lookahead == '\n' || lookahead == '\0')
        {
            goto q101;
        }
        else
        {
            posicaoFinal = posicao;
            return ERRO;
        }
        
    // ESTADO FINAL DE UM NUMERO
    q101: posicaoFinal = posicao;
        return NUMERO;
    
        


} 


FILE *abrirArquivo(char *nome, char *flags){

    FILE *f;
     f = fopen(nome, flags);

    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo \"%s\"\n",nome);        
        exit(0);
    }

    return f;

}

void escreverUltimoToken(char *programaFonte,int erro){
        // não escreve nada caso o token seja vazio
        if (programaFonte[posicaoInicial] == ' ' ||  programaFonte[posicaoInicial] == '\n' || programaFonte[posicaoInicial] == '\0') return;

        if (erro == 1){
           fprintf(saida,"%s","ERRO LÉXICO: ");          
        }
        
        int i;
        
        // caractere inválido
        if(posicaoInicial == posicaoFinal ){
            fprintf(saida,"%c",programaFonte[posicaoFinal]);
        }

        for(i = posicaoInicial; i < posicaoFinal; i++)
        {
            // se for o final da palavra, n deve concatenar na string
            if ( programaFonte[i] == ' '  ||  programaFonte[i] == '\n' || programaFonte[i] == '\0' ){                
                continue;
            }

            fprintf(saida,"%c",programaFonte[i]);            
        }
        fprintf(saida,"\n");
}

int match(int token, char programaFonte[]){        
	if (lookaheadTOKEN == token){        
        lookaheadTOKEN = scanner(programaFonte);
        // caso tenha um erro léxico
        if(lookaheadTOKEN == ERRO ){
            escreverUltimoToken(programaFonte,1);
            return FALSE;
        }else{
            escreverUltimoToken(programaFonte,0);
            return(TRUE);
        }		
	}
    else
    {
        // volta para a posição inicial da palavra, caso não tenha dado match
        // posicao = posicaoInicial;
	    return(FALSE);
    }
}

int program( char programaFonte[]){
    lookaheadTOKEN = scanner(programaFonte);

    if(lookaheadTOKEN == ERRO ) escreverUltimoToken(programaFonte,1);
    posicaoSintaticaIni = posicaoInicial;

	if ( match(PROGRAM,programaFonte) &&
         match(ID,programaFonte) &&
         match(ABRE_CHAVES,programaFonte) &&
         bloco(programaFonte) &&
         match(FECHA_CHAVES,programaFonte)
    ){
		return(TRUE);
	}
	return(FALSE);  
}

int printar(char programaFonte[]){
    posicaoSintaticaIni = posicaoInicial;
	if ( match(PRINT,programaFonte) &&
         match(ABRE_PARENTESES,programaFonte) &&
         match(ID,programaFonte) &&
         match(FECHA_PARENTESES,programaFonte)  ){
		return(TRUE);
	}
	return(FALSE);  
}

int comandoRepetitivo(char programaFonte[]){
    posicaoSintaticaIni = posicaoInicial;
    if(
        match(WHILE,programaFonte) &&
        match(ABRE_PARENTESES,programaFonte) &&
        expressao(programaFonte) &&
        match(FECHA_PARENTESES,programaFonte) &&
        match(ABRE_CHAVES,programaFonte)  &&
        comandoComposto(programaFonte) &&
        match(FECHA_CHAVES,programaFonte) 
        
    ){
        return TRUE;
    }
    else{
        return FALSE;
    }
    
}

int relacao(char programaFonte[]){
    // <relação> ::=  == | != | < | <= | >= | >
    
    if (
        match(IGUALDADE,programaFonte) ||
        match(DIFERENCA, programaFonte) ||
        match(MENOR, programaFonte) ||
        match(MENOR_IGUAL, programaFonte) ||
        match(MAIOR, programaFonte) ||
        match(MAIOR_IGUAL, programaFonte)
    ) {
        return TRUE;
    }
    else
    {
        return FALSE;
    }    
}


int expressao(char programaFonte[]){
    // <expressão> ::= <expressão simples> [ <relação>  <expressão simples> ]
    posicaoSintaticaIni = posicaoInicial;
    if(expressaoSimples(programaFonte)){
        if(lookaheadTOKEN == IGUALDADE || lookaheadTOKEN == DIFERENCA || lookaheadTOKEN == MENOR || lookaheadTOKEN == MENOR_IGUAL || lookaheadTOKEN == MAIOR || lookaheadTOKEN == MAIOR_IGUAL){
            if( relacao(programaFonte) && expressaoSimples(programaFonte) ){
                return TRUE;
            }else{
                return FALSE;
            }
        }else{
            return TRUE;
        }
    }else{
        return FALSE;
    }
}

int expressaoSimples(char programaFonte[]){
    // <expressão simples> ::=  [ + | - ] <termo> { [ + | - ] <termo> }    
    if(lookaheadTOKEN == SOMA || lookaheadTOKEN == SUBTRACAO){
        if(match(SOMA, programaFonte ) || match(SUBTRACAO, programaFonte )){
            if(termo(programaFonte)){
                if(lookaheadTOKEN == SOMA || lookaheadTOKEN == SUBTRACAO){
                    return expressaoSimples(programaFonte);
                }else{
                    return TRUE;
                }
            }else{
                return FALSE;
            }
        }else{
            return FALSE;
        }
    }else if (lookaheadTOKEN = ID){
        if(termo(programaFonte)){
            if(lookaheadTOKEN == SOMA || lookaheadTOKEN == SUBTRACAO){
                return expressaoSimples(programaFonte);
            }else{
                return TRUE;
            }
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    }
}

int fator(char programaFonte[]){
    if (   
        match(ID, programaFonte) ||
        match(NUMERO, programaFonte) ||     
        boolean(programaFonte)||
        expressaoSimples(programaFonte)
     ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}


int termo(char programaFonte[]){
    if(fator(programaFonte)){
        if(lookaheadTOKEN == MULTIPLICACAO || lookaheadTOKEN == DIVISAO){
            if( (match(MULTIPLICACAO, programaFonte ) || match(DIVISAO, programaFonte ) ) && termo(programaFonte) ){
                return TRUE;
            }else{
                return FALSE;
            }
        }else{
            return TRUE;
        }
    }else{
        return FALSE;
    }    
}


int boolean(char programaFonte[]){    
    if (
        match(TRUE, programaFonte ) ||
        match(FALSE, programaFonte )
    ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
    
}

int comandoCondicional(char programaFonte []){
    //    if ( <expressão> ) { <comando composto> } [ else { <comando composto> } ]

    posicaoSintaticaIni = posicaoInicial; 
    if(
        match(IF, programaFonte) &&
        match(ABRE_PARENTESES, programaFonte) &&
        expressao(programaFonte) &&
        match(FECHA_PARENTESES, programaFonte) &&
        match(ABRE_CHAVES, programaFonte) &&
        comandoComposto(programaFonte) &&
        match(FECHA_CHAVES, programaFonte)
    ){
        if(lookaheadTOKEN == ELSE){
            if( match(ELSE, programaFonte) &&
                match(ABRE_CHAVES, programaFonte) &&
                comandoComposto(programaFonte) &&
                match(FECHA_CHAVES, programaFonte)){
                    return TRUE;
            }else{
                return FALSE;
            }
        }else{
            return TRUE;
        }
    }else{
        return FALSE;
    }
}
 
int listaParametros(char programaFonte [] ) {
    /* <lista de parâmetros> ::=( <identificador> | <número> | <bool> )
			[ , <lista de parâmetros>  ] */

    posicaoSintaticaIni = posicaoInicial; 

    if(lookaheadTOKEN == ID || lookaheadTOKEN == NUMERO || boolean(programaFonte)){
        if( match(ID,programaFonte ) ||match(NUMERO,programaFonte ) || boolean(programaFonte ) ) {
            if(lookaheadTOKEN == VIRGULA){
                match(VIRGULA, programaFonte);
                return listaParametros(programaFonte);
            }else{
                return TRUE;
            }
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    }
}

int chamadaProcedimento(char programaFonte [] ) {    
    // <chamada de procedimento> ::= <identificador>  ( [ <lista de parâmetros> ] ) ;  
    posicaoSintaticaIni = posicaoInicial;   
    
    if( match(ID, programaFonte ) && match(ABRE_PARENTESES, programaFonte ) ){
        if (lookaheadTOKEN == ID || lookaheadTOKEN == NUMERO || boolean(programaFonte) ){
            if(listaParametros(programaFonte) && 
                match(FECHA_PARENTESES, programaFonte) && 
                match(PONTO_VIRGULA, programaFonte )){
                return TRUE;
            }else{
                return FALSE;
            }
        }
        else if (lookaheadTOKEN == FECHA_PARENTESES)
        {
            if( match(FECHA_PARENTESES, programaFonte) &&
                match(PONTO_VIRGULA, programaFonte )){
                    return TRUE;
            }else{
                return FALSE;
            }
        }
    }else{
        return FALSE;
    }
}

int atribuicao(char programaFonte [] ) {
    // <atribuição> ::=  <identificador> = <expressão> ; 
    posicaoSintaticaIni = posicaoInicial; 
    if (
        match(ID,programaFonte) &&
        match(IGUAL, programaFonte) &&
        expressao(programaFonte) &&
        match(PONTO_VIRGULA, programaFonte)
    ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int comando(char programaFonte [] ) {    
/*    <comando> ::=	<atribuição>
                | <chamada de procedimento>
                | <comando condicional>
                | <comando repetitivo>
                | print ( <identificador> ) ;
 */
    posicaoSintaticaIni = posicaoInicial; 

    if (     
        atribuicao(programaFonte ) ||
        chamadaProcedimento(programaFonte ) ||
        comandoCondicional(programaFonte ) ||
        comandoRepetitivo(programaFonte ) ||
        ( printar(programaFonte ) && match(PONTO_VIRGULA, programaFonte ) )
    ) {
        return TRUE;
    }
    else {
        return FALSE;
    }    
}

int comandoComposto(char programaFonte [] ){    
    // <comando composto> ::=  <comando>  { [ <comando> ] }    
    posicaoSintaticaIni = posicaoInicial;    

    if (lookaheadTOKEN == ID || lookaheadTOKEN == IF || lookaheadTOKEN == WHILE || lookaheadTOKEN == PRINT ){
        if(comando(programaFonte)){
            if (lookaheadTOKEN == ID || lookaheadTOKEN == IF || lookaheadTOKEN == WHILE || lookaheadTOKEN == PRINT ){
                return comandoComposto(programaFonte);
            }else{
                return TRUE;
            }
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    }

  
}

int parametroFormal(char programaFonte [] ){   
    // <parâmetro formal> ::= ( int | bool ) <identificador>
    posicaoSintaticaIni = posicaoInicial; 
    if (
        ( match(INTEIRO, programaFonte) || match(BOOLEAN, programaFonte) ) &&
        match(ID, programaFonte)
    ) {
        return TRUE;
    }
    else {
        return FALSE;
    }
    
}

int parametrosFormais(char programaFonte [] ){   
    // <parâmetros formais> ::=  <parâmetro formal>  { , <parâmetro formal> }
    posicaoSintaticaIni = posicaoInicial; 
    if( lookaheadTOKEN == INTEIRO || lookaheadTOKEN == BOOLEAN){
        if(parametroFormal(programaFonte)){
            if( lookaheadTOKEN == INTEIRO || lookaheadTOKEN == BOOLEAN){
                return parametrosFormais(programaFonte);
            }else{
                return TRUE;
            }  
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    } 
}

int declaracaoFuncao(char programaFonte [] ){
   /*   <declaração de função> ::=
        void <identificador> ( [ <parâmetros formais> ] ) {  <bloco>  } 
    */      
    if (
        match(VOID, programaFonte)  &&
        match(ID, programaFonte) &&
        match(ABRE_PARENTESES, programaFonte) &&
        ( parametrosFormais(programaFonte) || 1==1 ) &&
        match(FECHA_PARENTESES, programaFonte) &&
        match(ABRE_CHAVES, programaFonte) &&
        bloco(programaFonte) &&
        match(FECHA_CHAVES, programaFonte) 
    ) {        
        return TRUE;
    }
    else {        
        return FALSE;
    }    
}


int parteDeclaracaoFuncao(char programaFonte [] ){
    // <parte declarações de funções> ::= { <declaração de função> }    
    if(lookaheadTOKEN == VOID){
        if(declaracaoFuncao(programaFonte)){
            if(lookaheadTOKEN == VOID){
                return parteDeclaracaoFuncao(programaFonte);
            }else{
                return TRUE;
            }            
        }else{
            return FALSE;
        }
    }else{
        return FALSE;
    }
}
int listaIdentificadores(char programaFonte [] ) {    
    // <lista de identificadores> ::=  <identificador> [ , <listaIdentificadores> ]    
    if( lookaheadTOKEN == ID ){
        match(ID,programaFonte);
        if( lookaheadTOKEN == VIRGULA){
            match(VIRGULA, programaFonte );
            return listaIdentificadores(programaFonte );
        }else{
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }     
}

int declaracaoVariavel(char programaFonte [] ) {
    // declaração de variáveis::=  ( int | bool )  lista de identificadores ;    
    if (        
        ( match(BOOLEAN, programaFonte) || match(INTEIRO, programaFonte) ) &&
        listaIdentificadores(programaFonte) &&
        match(PONTO_VIRGULA, programaFonte)
    ) {
        return TRUE;
    }
    else {
        return FALSE;
    }    
}

int parteDeclaracaoVariavel(char programaFonte [] ){    
    // <parte declarações de variáveis> ::= <declaração de variáveis> { <declaração de variáveis> }
    // printf("lookahead %i",lookaheadTOKEN);    
    if( lookaheadTOKEN == BOOLEAN || lookaheadTOKEN == INTEIRO  ){
        if (declaracaoVariavel(programaFonte)){
            if( lookaheadTOKEN == BOOLEAN || lookaheadTOKEN == INTEIRO  ){
              return parteDeclaracaoVariavel(programaFonte);  
            }
            else
            {
                return TRUE;
            }
            
        }else {
            return FALSE;
        }
    }  
}

int bloco(char programaFonte [] ){  
   /*  
    <bloco> ::=  [ <parte  declarações de variáveis> ]
    [ <parte declarações de funções> ]
    <comando composto> 
   */    
    
    if(lookaheadTOKEN == BOOLEAN || lookaheadTOKEN == INTEIRO ){        
        if (parteDeclaracaoVariavel(programaFonte))
        {
            if(lookaheadTOKEN == VOID){
                if(parteDeclaracaoFuncao(programaFonte)){                    
                    return comandoComposto(programaFonte);
                }else{
                    return FALSE;
                }
            }
            else{                
                return comandoComposto(programaFonte);
            }            
        }else{
            return FALSE;
        }
    }
    else if (lookaheadTOKEN == VOID)
    {
       if(parteDeclaracaoFuncao(programaFonte)){                    
            return comandoComposto(programaFonte);
        }else{
            return FALSE;
        }
    }    
    else if (lookaheadTOKEN == ID || lookaheadTOKEN == IF || lookaheadTOKEN == WHILE || lookaheadTOKEN == PRINT  )
    {
        return comandoComposto(programaFonte);
    }
    else {
        return FALSE;
    }    
}

void trataErro(char *programaFonte){
	printf("\nERRO DE SINTAXE\n");	
    
    fprintf(saida,"%s %i:  ","ERRO DE SINTAXE NA LINHA Nro.",linha);
    
    int i;

    // caractere inválido
    if(posicaoSintaticaIni == posicaoSintaticaFin ){
        fprintf(saida,"%c",programaFonte[posicaoSintaticaFin]);
    }

    for(i = posicaoSintaticaIni; i < posicaoSintaticaFin; i++)
    {
        // se for o final da palavra, n deve concatenar na string
        if ( programaFonte[i] == ' '  ||  programaFonte[i] == '\n' || programaFonte[i] == '\0' ){                
            continue;
        }

        fprintf(saida,"%c",programaFonte[i]);            
    }
    fprintf(saida,"\n");

}