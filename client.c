#include "bignumber.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
    BigNumber *res = NULL;
    int n = 0;

    for(;;) 
    {
        int erro = 0;
        BigNumber inp1 = scanBigNumber();
        if (inp1.ndigitos == 1 && inp1.digitos[0] == 1 && inp1.sinal == '-') {
            free(inp1.digitos);
            break;
        }
        BigNumber inp2 = scanBigNumber();
        char sinal;
        scanf(" %c", &sinal);

        for (int i = 0; i < inp1.ndigitos; i++)
            if (inp1.digitos[i] < 0 || inp1.digitos[i] > 9) {
                erro = 1;
                printf("Primeiro numero invalido -> caso de teste ignorado\n");
            }

        for (int i = 0; i < inp2.ndigitos; i++)
            if (inp2.digitos[i] < 0 || inp2.digitos[i] > 9) {
                erro = 1;
                printf("Segundo numero invalido -> caso de teste ignorado\n");
            }

        if (limparBuffer() == EOF) 
        {
            free(inp1.digitos);
            free(inp2.digitos);
            printf("Erro ao ler o sinal\n");
            break;
        }

        if (sinal != '+' && sinal != '-' && sinal != '*') {
            erro = 1;
            printf("Sinal invalido -> caso de teste ignorado\n");
        }
        
        if (!erro)
        {
            BigNumber *tmp = realloc(res, sizeof *res * (n + 1));
            if(tmp == NULL) {
                printf("Erro de alocacao");
                exit(1);
            }
            res = tmp;
            res[n] = operationHandler(&inp1, &inp2, sinal);
            n++;
        }

        free(inp1.digitos);
        free(inp2.digitos);
    }

    for (int i = 0; i < n; i++) 
    {
        if (res[i].sinal == '-')
            printf("-");
        printArray(res[i].digitos, res[i].ndigitos);
        printf("\n");
        free(res[i].digitos);
    }

    free(res);
    return 0;
}
