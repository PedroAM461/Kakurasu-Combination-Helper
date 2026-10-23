#include <stdio.h>
#include <windows.h>

int S[512][10];  //Matriz global das combinacoes
//S[i][0] eh a soma da i-esima combinacao
//Se S[i][j] for 1, com j > 0, entao o numero j faz parte da combinacao i
int NUM;  //Soma desejada
char RES[10];  //Array das restricoes (vou usar string pq eh mais facil)


void fInicializar() {
    int pot = 1;  //pot. de 2
    for (int x = 1; x < 10; x++) {
        int a = 1;  //bit
        for (int y = 0; y < 512; y++) {
            if (y % pot == 0) a = !a;  //troca ciclica
            S[y][x] = a;
        }
        pot *= 2;  //proxima pot.
    }

    for (int i = 0; i < 512; i++) {
        int sum = 0;
        for (int j = 1; j < 10; j++) {
            if (S[i][j]) sum += j;  //conta os bits ligados
        }
        S[i][0] = sum;
    }
}

void fMostrar() {
    for (int i = 0; i < 512; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", S[i][j]);
        }
        printf("\n");
    }
}

int fMenu1() {
    int escolha;
    
    printf("Qual numero vc quer somar: ");
    scanf("%d", &escolha);
    getchar();

    return escolha;
}

int fChecaRestricao(int row) {
    for (int x = 1; x < 10; x++) {
        if(S[row][x] == 0 && (RES[x-1] != '?' && RES[x-1] != 'X')) return 0;
        
        if (S[row][x] == 1 && RES[x-1] == 'X') return 0;
    }
    return 1;
}

void fKakuro() {
    system("cls");

    int FREQ[9] = {0,0,0,0,0,0,0,0,0};
    int TOTAL = 0;

    //Calcula quantas combinacoes tem, e a frequencia de cada numero
    for (int i = 0; i < 512; i++) {
        if (S[i][0] == NUM) {
            if (fChecaRestricao(i)) {
                TOTAL++;
                for (int j = 1; j < 10; j++) {
                    if (S[i][j]) FREQ[j-1]++;
                }
            }
        }
    }

    printf("=== RESULTADOS COM BASE NA SUA RESTRICAO ===\n\n");
    printf(">>Os numeros obrigatorios sao:\n");
    for (int x = 0; x < 9; x++) {
        if (FREQ[x] == TOTAL) printf("[%d]", x+1);
    }

    printf("\n\n");

    printf(">>Os numeros proibidos sao:\n");
    for (int x = 0; x < 9; x++) {
        if (FREQ[x] == 0) printf("[%d]", x+1);
    }

    printf("\n\n");

    printf(">>Frequencias:\n");
    printf("    Num: ");
    for (int x = 0; x < 9; x++) {
        printf("[%2d]", x+1);
    }
    printf("\n");
    printf("Aparece: ");
    for (int x = 0; x < 9; x++) {
        printf("[%2d]", FREQ[x]);
    }
    printf("\n");
    printf(">>Total de combinacoes: %d\n", TOTAL);

    printf("\n");
    system("pause");
}

int main () {
    fInicializar();

    do {
        system("cls");

        printf("=== ASSISTENTE DE COMBINACOES DO KAKURASU 9x9 ===\n");  //dps adicionar outros nxn
        NUM = fMenu1();

        if (!NUM) {
            printf("\nflw\n"); system("pause");
        } else {
            if (NUM < 1 || NUM > 45) {  //Isso nao eh kakuro
                printf("\nbruh\n"); system("pause");
            } else {

                //n vou testar todos casos desta budega, apenas escreva corretamente nove simbolos
                printf("Insira a restricao atual (Ex. ?XX4X???9):\n");
                scanf("%s", RES);  //ACHO q ele coloca '\0'
                getchar();

                fKakuro();
            }
        }
    } while (NUM);



}

/* Lembra muito um somador, com carry out
1 troca a cada 2^0 (1) vezes [000000000] {%1}
2 troca a cada 2^1 (2) vezes [010101010] {%2}
3 troca a cada 2^2 (4) vezes [012301230] {%4}
4 troca a cada 2^3 (8) vezes ...
5 troca a cada 2^4 (16) vezes ..
6 troca a cada 2^5 (32) vezes .
7 troca a cada 2^6 (64) vezes
8 troca a cada 2^7 (128) vezes
9 troca a cada 2^8 (256) vezes
*/