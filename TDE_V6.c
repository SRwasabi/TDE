#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//"evolucao_do_salario_minimo_teste3.csv"
#define NOME_ARQ "evolucao_do_salario_minimo_teste3.csv"

void print_dado(char[], char [], char[], float, char[]);


int main(){
    /*Var de Entrada*/
    char data[3];
    int ret;
    printf("Escolha uma data entre 1940 a 2015 pela sua dezena e unidade: ");
    scanf("%s", &data);


    FILE *arquivo;

    /*Dados dos Arquivos*/
    char legis[164][25];
    char DOU[164][10];
    char vigenD[164][10];
    char vigenM[164][10];
    char vigenAno[164][3];
    char moeda[164][10];
    float salario[164];


    arquivo = fopen(NOME_ARQ, "r");

    if(arquivo == NULL){
        printf("Erro! Não consegui abrir o arquivo de leitura");
        return 1;
    }
    char linha[100];
    fgets(linha, 100, arquivo);
    char *token;
    int i=0;

    while(fgets(linha, 100, arquivo) != NULL){
        token = strtok(linha, ";");
        strcpy(legis[i], token);
        token = strtok(NULL, ";");
        strcpy(DOU[i], token);
        token = strtok(NULL, ".");
        strcpy(vigenD[i], token);
        token = strtok(NULL, ".");
        strcpy(vigenM[i], token);
        token = strtok(NULL, ";");
        strcpy(vigenAno[i], token);
        token = strtok(NULL, ";");
        strcpy(moeda[i], token);
        token = strtok(NULL, ";");


        //Salario vem com '.'
        //Professor Guilherme ajudou
        ///==========================================
        int j, p = 0;
        for(j = 0; token[j] != '\0'; j++){
            token[p] = token[j];

            if(token[j] != '.'){
                if(token[p] == ','){
                    token[p] = '.';
                }
                p++;
            }

        }
        ///==========================================

        salario[i] = strtof(token, NULL);
        //printf("%s", linha);
       // token = strtok(linha, ","); //Teste Para ler o data inteiro

        if(strcmp(data, vigenAno[i]) == 0){
            print_dado(legis[i], DOU[i], moeda[i], salario[i], vigenAno[i]);
            //printf("%s\n", vigenAno[i]);
        }
        i++;
    }

    fclose(arquivo);
    return 0;
}


void print_dado(char legis[], char DOU[], char moeda[], float salario, char vigenAno[]){
    printf("\n");
    printf("-------------------------------------------\n");
    printf("> Legislacao: %s\n", legis);
    printf("\tDOU: %s\n", DOU);
    printf("\tSalario: %s %.2f\n", moeda, salario);
    int Ano;
    Ano = strtof(vigenAno, NULL);
    if(Ano == 40){
        printf("\tConversao: %.15f\n", salario/(pow(1000, 4)*2750));
    }
    else if(43 <= Ano <= 66){
        printf("\tConversao: %.15f\n", salario/(pow(1000, 4)*2750));
    }
    else
}
