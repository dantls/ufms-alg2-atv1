/* 
ALGORITMOS E PROGRAMAÇÃO II - 2020
ATIVIDADE PRÁTICA I - NOTAÇÃO INFIXA - POSFIXA
ALUNOS: DANILO GOMES DA SILVA e ELTON IGOR CUNHA PEREIRA
*/

/* IMPORTANDO AS LIB PERMITIDAS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* DEFININDO CONSTANTES UTILIZADAS NO PROGRAMA*/
#define MAX 100
#define CHAR_MIN '\0'
#define NUMBER_OF_STRING 100
#define MAX_STRING_SIZE 300


/* FUNÇÃO QUE REALIZA O CALCULO DA POTENCIA*/
int potencia(int base, int pot)
{
    int i = 0, result = 1;
    for (i = 0; i < pot; i++)
    {
        result *= base;
    }
    return result;
}


/* FUNÇÃO QUE REALIZA AS PRECEDENCIAS DOS OPERADORES*/
int precedencia(char op)
{
    switch (op)
    {

    case '(':
        return 0;
        break;

    case '+':
    case '-':
        return 1;
        break;

    case '*':
    case '/':
        return 2;
        break;

    case '^':
        return 3;
        break;
    }
}


/* FUNÇÃO QUE EMPILHA, UTILIZADA NA CONSTRUÇÃO DA POSFIXA*/
void empilha(int *t, char P[MAX], char y)
{
    if (*t != MAX - 1)
    {
        (*t)++;
        P[*t] = y;
    }
    else
        printf("Pilha cheia!\n");
}

/* FUNÇÃO QUE EMPILHA, UTILIZADA NA CONSTRUÇÃO DO CALCULO DA POSFIXA*/
void empilhaInt(int *t, int P[MAX], int y)
{
    if (*t != MAX - 1)
    {
        (*t)++;
        P[*t] = y;
    }
    else
        printf("Pilha cheia!\n");
}

/* FUNÇÃO QUE DESEMPILHA, UTILIZADA NA CONSTRUÇÃO DA POSFIXA*/
char desempilha(int *t, char P[MAX])
{
    char r;
    if (*t != -1)
    {
        r = P[*t];
        (*t)--;
    }
    else
    {
        r = CHAR_MIN;
        printf("Pilha vazia!\n");
    }
    return r;
}

/* FUNÇÃO QUE DESEMPILHA, UTILIZADA NA CONSTRUÇÃO DO CALCULO DA POSFIXA*/
int desempilhaInt(int *t, int P[MAX])
{
    int r;
    if (*t != -1)
    {
        r = P[*t];
        (*t)--;
    }
    else
    {
        r = CHAR_MIN;
        printf("Pilha vazia!\n");
    }
    return r;
}


/* FUNÇÃO QUE REALIZA A CONVERSÃO DA EXPRESSÃO INFIXA LIDA DO ARQUIVO PARA POSFIXA*/
/* RECEBE UMA CADEIA DE CHAR QUE DEPOIS RETORNA OUTRA CADEIA COM A EXPRESSÃO POSFIXA*/
char *posfixa(char *expression)
{
    /* TODO EMPILHAMENTO NESTA FUNÇÃO É SEGUIDO DE UM ESPAÇO*/
    char posfixa[MAX] = {}, pilhaAux[MAX] = {}, aux;

    int topoPosfixa, topoAux, i;

    topoPosfixa = -1;
    topoAux = -1;
    /* LAÇO QUE ITERA A STRING DE ENTRADA DO ARQUIVO E TRANSFORMA EM POSFIXA COM AS FUNÇÕES DE EMPILHA E DESEMPILHA*/
    for (i = 0; expression[i] != '\0'; i++)
    {
        /* VERIFICA SE É DIGITO, SENDO OCORRE O EMPILHAMENTO DO MESMO*/
        if (isdigit(expression[i]))
        {
            empilha(&topoPosfixa, posfixa, expression[i]);
        }
        /* SE NÃO FOR DIGITO VERIFICA QUAL É O OPERADOR OU PARENTESES E REALIZA O EMPILHAMENTO JUNTO A UM ESPAÇO */
        else
        {
            empilha(&topoPosfixa, posfixa, ' ');
            switch (expression[i])
            {
            case '(':
                empilha(&topoAux, pilhaAux, expression[i]);
                empilha(&topoPosfixa, posfixa, ' ');
                break;
            case ')':
                do
                {
                    aux = desempilha(&topoAux, pilhaAux);
                    if (aux != '(')
                    {
                        empilha(&topoPosfixa, posfixa, aux);
                        empilha(&topoPosfixa, posfixa, ' ');
                    }
                } while (aux != '(');
                break;
            default:
                while (topoAux != -1 && precedencia(expression[i]) <= precedencia(pilhaAux[topoAux]))
                {
                    /* DESEMPILHA PARA VERIFICAR A PRECEDENCIA E EMPILHA NOVAMENTE*/
                    aux = desempilha(&topoAux, pilhaAux);
                    empilha(&topoPosfixa, posfixa, aux);
                    empilha(&topoPosfixa, posfixa, ' ');
                };

                empilha(&topoAux, pilhaAux, expression[i]);
                break;
            }
        }
    }
    while (topoAux != -1)
    {
        empilha(&topoPosfixa, posfixa, ' ');
        empilha(&topoPosfixa, posfixa, desempilha(&topoAux, pilhaAux));
        empilha(&topoPosfixa, posfixa, ' ');
    }
    strcpy(expression, posfixa);

    return expression;
}

/* FUNÇÃO QUE REALIZA O CALCULO DA POSFIXA E RETORNA O RESULTADO DA EXPRESSÃO*/
/* RECEBE UMA CADEIA DE CHAR QUE DEPOIS RETORNA APENAS O RESULTADO DA EXPRESSÃO*/
int calculaPosfixa(char expression[][MAX_STRING_SIZE])
{

    int vetor[MAX] = {};
    char *sub;
    char texto[MAX] = {};
    /* RECEBE A POSFIXA E RETIRA OS ESPAÇO PARA AUXILIAR NO EMPILHAMENTO E NA ENTRADA DO VETOR DE INTEIRO*/
    sub = strtok(expression, " ");
    int contador = 0;
    /* WHILE QUE SPLIT PELO ESPAÇO */
    while (sub != NULL)
    {
        if (isdigit(*sub))
        {
            vetor[contador] = atoi(sub);
            contador++;
        }
        strcat(texto, sub);
        strcat(texto, " ");
        sub = strtok(NULL, " ");
    }
    /* COPIA O TEXTO PARA EXPRESSÃO ONDE É UTILIZADA ABAIXO NO CALCULADORA DO POSFIXA*/
    strcpy(expression, texto);

    int var1, var2, i, result;

    int pilhaAuxInt[MAX] = {};

    int topoAuxInt;

    topoAuxInt = -1;
    var1 = 0;
    var2 = 0;
    result = 0;
    int contaIteracao = 0;
    int tamanhoString = strlen(expression);

    int k = 0;
    int cont = 0;
    /* LAÇO QUE PERCORRE A EXPRESSÃO E VAI REALIZANDO O DESEMPILHAMENTO E EMPILHAMENTO, ALÉM DE REALIZAR OS CALCULOS CONFORME OS SINAIS */
    for (i = 0; strcmp(expression[i], "\0") != 0; i++)
    {
        for (k = 0; k < tamanhoString; k++)
        {
            if (expression[i][k] == '*' && expression[i][k + 1] == ' ')
            {
                var1 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                var2 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                result = var1 * var2;
                empilhaInt(&topoAuxInt, pilhaAuxInt, result);
                contaIteracao++;
            }
            else if (expression[i][k] == '^' && expression[i][k + 1] == ' ')
            {
                var1 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                var2 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                result = potencia(var2, var1);
                empilhaInt(&topoAuxInt, pilhaAuxInt, result);
                contaIteracao++;
            }
            else if (expression[i][k] == '-' && expression[i][k + 1] == ' ')
            {
                var1 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                var2 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                result = var2 - var1;
                empilhaInt(&topoAuxInt, pilhaAuxInt, result);
                contaIteracao++;
            }
            else if (expression[i][k] == '+' && expression[i][k + 1] == ' ')
            {
                var1 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                var2 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                result = var2 + var1;
                empilhaInt(&topoAuxInt, pilhaAuxInt, result);
                contaIteracao++;
            }
            else if (expression[i][k] == '/' && expression[i][k + 1] == ' ')
            {
                var1 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                var2 = desempilhaInt(&topoAuxInt, pilhaAuxInt);
                result = var2 / var1;
                empilhaInt(&topoAuxInt, pilhaAuxInt, result);
                contaIteracao++;
            }
            else if (isdigit(expression[i][k]) && cont < contador && expression[i][k + 1] == ' ')
            {
                empilhaInt(&topoAuxInt, pilhaAuxInt, vetor[cont]);
                cont++;
            }
        }
    }
    return desempilhaInt(&topoAuxInt, pilhaAuxInt);
}

/* FUNÇÃO MAIN ONDE É FEITO A LEITURA E GRAVAÇÃO DOS ARQUIVO. 
ALÉM DISSO, SÃO CHAMADA AS FUNÇÕES PRINCIPAIS
CONVERSÃO DA INFIXA PARA POSFIXA E DO CALCULO DA POSFIXA */

int main()
{
    FILE *ptArq, *arqSaida;
    ptArq = fopen("arquivo.in", "r");

    int quantity, cont = 0;

    char expressaoPosfixa[300];

    fscanf(ptArq, "%d", &quantity);
    char expressions[quantity][MAX_STRING_SIZE];

    if (ptArq == NULL)
    {
        printf("Ocorreu um problema ao abrir o arquivo.\n");
        return 0;
    }
    else
    {
        int t, j = 0;
        char linha[300];
        while (fgets(linha, 300, ptArq) != NULL)
        {
            if (j == 0)
            {
            }
            else
            {
                linha[strcspn(linha, "\n")] = 0;
                t = j - 1;
                strcpy(expressions[t], linha);
                char *sub;
                char texto[MAX] = {};
                /* WHILE QUE É FEITO PARA SPLIT SE HOUVER MUITOS ESPAÇOS NA ENTRADA DA LINHA LIDA DO ARQUIVO */
                sub = strtok(linha, " ");
                
                while(sub != NULL){
                    strcat(texto, sub);
                    sub = strtok(NULL, " ");
                }
                strcpy(linha, texto);
                /* É CHAMADA A POSFIXA PARA REALIZAR A CONVERSÃO DE INFIXA PARA POSFIXA */
                strcpy(expressaoPosfixa, posfixa(linha));
                /* LOGO DEPOIS DE REALIZAR A POSFIXA, PASSAMOS PARA O CALCULO DA POSFIXA E POSTERIORMENTE GRAVAMOS NO ARQUIVO DE SAIDA*/
                int resultado = calculaPosfixa(linha);
                /* GRAVANDO O ARQUIVO DE SAIDA, ONDE TAMBÉM UTILIZAMOS O INTEIRO LIDO NO ARQUIVO DE ENTRADA*/
                if (arqSaida != NULL)
                {
                    arqSaida = fopen("arquivoSaida.out", "aw");
                    if (cont == 0)
                    {
                        fprintf(arqSaida, "%d\n", quantity);
                        cont++;
                    }
                    /* GRAVANDO NO ARQUIVO DE SAIDA JUNTO COM O ";" CONFORME O PADRÃO PEDIDO*/
                    fprintf(arqSaida, "%s; %d\n", linha, resultado);
                    fclose(arqSaida);
                }
            }
            j++;
        }
        fclose(ptArq);
    }

    return 0;
}
