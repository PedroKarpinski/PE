#ifndef BIG_H
#define BIG_H
typedef struct
{
    int *digitos;
    int ndigitos;
    char sinal;
} BigNumber;

BigNumber scanBigNumber();
void addZeros(BigNumber *, int);
int tamanhoDoMaiorArray(BigNumber *, BigNumber *);
void printArray(int *, int);
void inverterArray(int *, int);
BigNumber soma(BigNumber *, BigNumber *);
BigNumber subtract(BigNumber *, BigNumber *);
BigNumber multiply(BigNumber *, BigNumber *);
int limparBuffer();
int comparaModulo(BigNumber*, BigNumber*);
BigNumber operationHandler(BigNumber*,BigNumber*,char);

#endif