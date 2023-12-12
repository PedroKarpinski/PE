#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bignumber.h"

BigNumber scanBigNumber() 
{
    BigNumber inp;
    int l = 1;
    char *s = malloc(sizeof(char));
    if (s == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }

    char aux;
    scanf("%c", &aux);
    if (aux == '-') {
        inp.sinal = aux;
        scanf("%c", &aux);
    } else
        inp.sinal = '+';

    while (aux != '\n') {
        l++;
        char *temp = realloc(s, l * sizeof(char));
        if (temp == NULL) {
            printf("Erro de alocacao");
            exit(1);
        }
        s = temp;
        s[l - 2] = aux;
        scanf("%c", &aux);
    }

    inp.digitos = malloc(sizeof(int) * (l - 1));
    if (inp.digitos == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }

    inp.ndigitos = l - 1;
    for (int i = 0; i < inp.ndigitos; i++)
        inp.digitos[i] = s[i] - '0';

    free(s);
    return inp;
}

void inverterArray(int *array, int tamanho)
{
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio < fim)
    {
        int temp = array[inicio];
        array[inicio] = array[fim];
        array[fim] = temp;
        inicio++;
        fim--;
    }
}

void addZeros(BigNumber *inp, int n) {
    if (n <= inp->ndigitos) return;

    int *novo = malloc(sizeof(int) * n);
    if (novo == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }

    int diff = n - inp->ndigitos;
    for (int i = 0; i < diff; i++)
        novo[i] = 0;
    for (int i = 0; i < inp->ndigitos; i++)
        novo[i + diff] = inp->digitos[i];

    free(inp->digitos);
    inp->digitos = novo;
    inp->ndigitos = n;
}

int tamanhoDoMaiorArray(BigNumber *inp1, BigNumber *inp2) 
{
    if (inp1->ndigitos > inp2->ndigitos)
        return inp1->ndigitos;

    if (inp1->ndigitos < inp2->ndigitos)
        return inp2->ndigitos;

    return inp1->ndigitos;
}

void printArray(int *v, int n)
{
    int isZero = 0, k = -1;
    for (int i = 0; i < n; i++)
        if (v[i] != 0)
        {
            isZero = 1;
            k = i;
            break;
        }

    if (k == -1)
    {
        printf("0");
        return;
    }

    if (!isZero)
        for (int i = 0; i < n; i++)
            printf("%d", v[i]);
    else
        for (int i = k; i < n; i++)
            printf("%d", v[i]);
}


// =================================================================
// OPERAÇÕES
// =================================================================

BigNumber soma(BigNumber *inp1, BigNumber *inp2)
{
    int n = tamanhoDoMaiorArray(inp1, inp2);
    BigNumber temp;
    temp.digitos = calloc(n, sizeof(int));
    if (temp.digitos == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }
    temp.ndigitos = n;

    if (inp1->ndigitos > inp2->ndigitos)
        addZeros(inp2, n);
    else if (inp1->ndigitos < inp2->ndigitos)
        addZeros(inp1, n);

    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int sum = 0;
        if (i < inp1->ndigitos)
            sum += inp1->digitos[i];
        if (i < inp2->ndigitos)
            sum += inp2->digitos[i];
        sum += carry;
        temp.digitos[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        addZeros(&temp, n + 1);
        temp.digitos[0] = carry;
    }

    return temp;
}

BigNumber subtract(BigNumber *inp1, BigNumber *inp2) 
{
    int n = tamanhoDoMaiorArray(inp1, inp2);
    BigNumber temp;
    temp.digitos = calloc(n, sizeof(int));
    if (temp.digitos == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }
    temp.ndigitos = n;

    if (inp1->ndigitos > inp2->ndigitos)
        addZeros(inp2, n);
    else if (inp1->ndigitos < inp2->ndigitos)
        addZeros(inp1, n);

    int borrow = 0;
    for (int i = n - 1; i >= 0; i--) {
        int dif = inp1->digitos[i] - inp2->digitos[i] - borrow;
        if (dif < 0) {
            dif += 10;
            borrow = 1;
        } else
            borrow = 0;
        temp.digitos[i] = dif;
    }

    return temp;
}

BigNumber multiply(BigNumber *num1, BigNumber *num2)
{
    BigNumber temp;
    temp.digitos = calloc(num1->ndigitos + num2->ndigitos, sizeof(int));
    if (temp.digitos == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }
    temp.ndigitos = num1->ndigitos + num2->ndigitos;

    int i, j, carry;
    for (i = 0; i < num1->ndigitos; i++) 
    {
        carry = 0;
        int digit1 = num1->digitos[num1->ndigitos - 1 - i];

        for (j = 0; j < num2->ndigitos; j++)
        {
            int digit2 = num2->digitos[num2->ndigitos - 1 - j];
            int sum = digit1 * digit2 + temp.digitos[i + j] + carry;
            carry = sum / 10;
            temp.digitos[i + j] = sum % 10;
        }

        if (carry > 0)
            temp.digitos[i + num2->ndigitos] += carry;
    }

    inverterArray(temp.digitos, temp.ndigitos);
    return temp;
}

int limparBuffer() 
{
    for(;;) {
        int c = getchar();
        if(c == EOF || c == '\n')
            return c;
    }
}

int comparaModulo(BigNumber *inp1, BigNumber *inp2) 
{
    if (inp1->ndigitos > inp2->ndigitos)
        return 1;

    if (inp1->ndigitos < inp2->ndigitos)
        return 2;

    for (int i = 0; i < inp1->ndigitos; i++) 
    {
        if (inp1->digitos[i] > inp2->digitos[i])
            return 1;

        if (inp1->digitos[i] < inp2->digitos[i])
            return 2;
    }

    return 1;
}

BigNumber operationHandler(BigNumber *inp1, BigNumber *inp2, char signal) 
{
    BigNumber inpRes;
    int maiorNum = comparaModulo(inp1, inp2);

    // SOMA
    if (signal == '+') 
    {
        // a + b
        if (inp1->sinal == '+' && inp2->sinal == '+')
        {
            inpRes = soma(inp1, inp2);
            inpRes.sinal = '+';
        }

        // a + (-b)
        else if (inp1->sinal == '+' && inp2->sinal == '-')
        {
            // |a| > |b|
            if (maiorNum == 1)
            {
                inpRes = subtract(inp1, inp2);
                inpRes.sinal = '+';
            }

            // |a| < |b|
            else if (maiorNum == 2)
            {
                inpRes = subtract(inp2, inp1);
                inpRes.sinal = '-';
            }
        }

        // (-a) + b
        else if (inp1->sinal == '-' && inp2->sinal == '+')
        {
            // |a| > |b|
            if (maiorNum == 1)
            {
                inpRes = subtract(inp1, inp2);
                inpRes.sinal = '-';
            }

            // |a| < |b|
            else if (maiorNum == 2)
            {
                inpRes = subtract(inp2, inp1);
                inpRes.sinal = '+';
            }
        }

        // (-a) + (-b)
        else if (inp1->sinal == '-' && inp2->sinal == '-')
        {
            inpRes = soma(inp1, inp2);
            inpRes.sinal = '-';
        }
    }

    // SUBTRAÇÃO
    else if (signal == '-')
    {
        // a - b
        if (inp1->sinal == '+' && inp2->sinal == '+')
        {
            // |a| > |b|
            if (maiorNum == 1)
            {
                inpRes = subtract(inp1, inp2);
                inpRes.sinal = '+';
            }

            // |a| < |b|
            else if (maiorNum == 2)
            {
                inpRes = subtract(inp2, inp1);
                inpRes.sinal = '-';
            }
        }

        // a - (-b)
        else if (inp1->sinal == '+' && inp2->sinal == '-')
        {
            inpRes = soma(inp1, inp2);
            inpRes.sinal = '+';
        }

        // (-a) - b
        else if (inp1->sinal == '-' && inp2->sinal == '+')
        {
            inpRes = soma(inp2, inp1);
            inpRes.sinal = '-';
        }

        // (-a) - (-b)
        else if (inp1->sinal == '-' && inp2->sinal == '-')
        {
            // |a| > |b|
            if (maiorNum == 1)
            {
                inpRes = subtract(inp1, inp2);
                inpRes.sinal = '-';
            }

            // |a| < |b|
            else if (maiorNum == 2)
            {
                inpRes = subtract(inp2, inp1);
                inpRes.sinal = '+';
            }
        }
    }

    // MULTIPLICAÇÃO
    else if (signal == '*')
    {
        inpRes = multiply(inp1, inp2);

        // a * (-b) ou (-a) * b
        if ((inp1->sinal == '+' && inp2->sinal == '-') || (inp1->sinal == '-' && inp2->sinal == '+'))
            inpRes.sinal = '-';
        
        // a * b ou (-a) * (-b)
        else
            inpRes.sinal = '+';
    }

    return inpRes;
}