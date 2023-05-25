#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*"evolucao_do_salario_minimo_teste3.csv"*/
#define NOME_ARQ "evolucao_do_salario_minimo_teste3.csv"

void print_dado(char[], char [], char[], double, char[]);


int main(){
    /*Var de Entrada*/
    int opcao;
    char data[3];
    int ret;

    do{
            printf("\n\t================MENU================\n");
            printf("\tDigite uma das opcoes [1-3]\n");
            printf("\t1 - Exibir todas as linhas\n");
            printf("\t2 - Exibir somente o menor valor e a sua posicao\n");
            printf("\t3 - Sair\n");

            scanf("%i", &opcao);

            switch(opcao){

            case 1:

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
                double salario[164];


                arquivo = fopen(NOME_ARQ, "r");

                if(arquivo == NULL){
                    printf("Erro! N�o consegui abrir o arquivo de leitura");
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


                    /*Salario vem com '.'
                    Professor Guilherme ajudou*/
                    /*///==========================================*/
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
                    /*///==========================================*/

                    salario[i] = strtof(token, NULL);
                    /*printf("%s", linha);
                   // token = strtok(linha, ","); //Teste Para ler o data inteiro*/

                    if(strcmp(data, vigenAno[i]) == 0){
                        print_dado(legis[i], DOU[i], moeda[i], salario[i], vigenAno[i]);
                        /*printf("%s\n", vigenAno[i]);*/
                    }

                    i++;
                }

                fclose(arquivo);
                break;

            case 2:
                printf("Oi");
                break;

            case 3:
                printf("\tAdeus\n");
                break;

            default:
                printf("\t Nao existe essa opcao!!\n");
                break;
        }
    } while(opcao != 3);

    return 0;
}


void print_dado(char legis[], char DOU[], char moeda[], double salario, char vigenAno[]){
    printf("\n");
    printf("-------------------------------------------\n");
    printf("> Legislacao: %s\n", legis);
    printf("\tDOU: %s\n", DOU);
    printf("\tSalario: %s %.2lf\n", moeda, salario);
    int Ano;
    Ano = strtof(vigenAno, NULL);
    char cruzado[4] = {'C', 'z', '$', '\0'};
    char cruzeiro[4] = {'C', 'r', '$', '\0'};
    char cruzeiroREAL[4] = {'C', 'R', '$', '\0'};

    if(Ano >= 93){
           if(strcmp(moeda, cruzeiroREAL) == 0){
                printf("\tConversao: %.1lf\n", salario/2750);
           }
           else if(strcmp(moeda, cruzeiro) == 0){
                printf("\tConversao: %.2lf\n", salario/(1000*2750));
           }
           else{
                printf("\tConversao: %.3lf\n", salario);
           }
    }

    else if(Ano >= 86){
           if(strcmp(moeda, cruzado) == 0){
                printf("\tConversao: %.4lf\n", salario/(pow(1000, 2)*2750));
           }
           else{
                printf("\tConversao: %.5lf\n", salario/(1000*2750));
           }
    }

    else if(Ano >= 67){
        printf("\tConversao: %.6lf\n", salario/(pow(1000, 3)*2750));
    }

    else if(Ano >= 40){
        printf("\tConversao: %.7lf\n", salario/(pow(1000, 4)*2750));
    }

    else if(Ano >= 15){
        printf("\tConversao: %.8lf\n", salario);
    }


    }


