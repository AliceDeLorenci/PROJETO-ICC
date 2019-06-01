/***********************************************************
 * O FOI FEITO?
 * solicita as informacoes do usuario
 * salva em arquivo assim que sao inseridas
***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* PESQUISAR */
// COMENTARIO   

#define file1 "med.txt"

void GUI();

void GUIadicionar(bool *GUIad, char undd);

void NomeMed(bool *GUIad);

void NomeCom (bool *GUIad);

void Quantidade (bool *GUIad);

void QuantoTem(bool *GUIad, char undd);

int main(){

    /* ver funcionamento do teclado / ASCII estendido / conio.h */
    /****
     *  busca em arquivos
     * ideia:  linha 1 - numero de remedios
     *         novo remedio  - scanf linha 1  &n
     *                         "w"  n++
    */

    /*se usuario quiser sair antes de terminar: aviso - mudancas serao perdidas
     funcao (struct) para armazenar as infos e so printar no arquivo quando terminar
     */

    GUI();
    


}

/* INTERFACE INICIAL */
void GUI(){
    char tecla;
    bool GUIad[]={0,0,0,0,0,1};  //a primeira posicao nao eh relevante

    printf("\n\n-----------------------DESPREOCUPE-SE-----------------------\n");
    printf("Escolha o que deseja fazer:\n");

    //lista de medicamentos

    printf("1 - Adicionar medicamento\n");
    //editar medicamentos
    //remover medicamentos 
        //#posteriores -> #n-1
    printf("0 - SALVAR E SAIR\n");

    scanf("\n%c",&tecla);

    if(tecla == '1'){
        FILE *Arq;
        Arq = fopen(file1,"a");
        fprintf(Arq,"#1\n");  //ID do novo med    /*usar busca para determinar numero do remedio*/
        fclose(Arq);

        GUIadicionar(GUIad,'0');
    }

    else if(tecla == '0'){
        return;
    }

}

/* INTERFACE ADICIONAR */
void GUIadicionar (bool *GUIad, char undd){
    char tecla;
    int i, done = 0;

    for(i=1; i<6; i++){   //avaliar se as opcoes ja foram concluidas
        if(GUIad[i]==1){
            done++;
        }
    }

    printf("\n\n-----------------------DESPREOCUPE-SE-----------------------\n");
    
    if(done != 5)
        printf("Informe:\n");

    if(GUIad[1] == 0)
        printf("1 - Nome do medicamento\n");
    if(GUIad[2] == 0)
        printf("2 - Nome comercial do medicamento\n");
    if(GUIad[3] == 0)
        printf("3 - Quantidade a ser tomada\n");
    if(GUIad[4] == 0)
        printf("4 - Quanto do medicamento você tem\n");
    if(GUIad[5] == 0)
        printf("5 - Quando tomar o medicamento\n");

    if(done == 5){
        printf("Medicamento incluido com sucesso!!!\n\n");
    }

    printf("V - VOLTAR PARA A TELA INICIAL\n");

    scanf("\n%c",&tecla);

    if(tecla == '1'){
        NomeMed(GUIad);
    }
    else if(tecla == '2'){
        NomeCom(GUIad);
    }
    else if(tecla == '3'){
        Quantidade(GUIad);   //a função quantidade chamara GUIadicionar passando o parametro undd
    }
    else if(tecla == '4'){
        QuantoTem(GUIad,undd);   //aqui sera utilizado o parametro undd
    }
    else if(tecla == '5'){
        printf("\n\nFuncionalidade em desenvolvimento, obrigada pela compreensão :)\n");
        GUIadicionar(GUIad,'0');
    }
    if(tecla == 'V' || tecla == 'v'){
        GUI();
    }

}

void NomeMed (bool *GUIad){

    FILE *Arq;
    Arq = fopen(file1,"a");

    char nomemed[50];
    printf("\n\nInforme o nome do medicamento:\n");
    scanf("\n");
    fgets(nomemed,50,stdin);

    fprintf(Arq,"%s",nomemed);  //a funcao fgets ja adiciona um \0 ao final, que eh convertido em \n

    fclose(Arq);

    GUIad[1] = 1;   //retornar informação que 1 já foi realizado

    GUIadicionar(GUIad,'0');
}

void NomeCom (bool *GUIad){

    FILE *Arq;
    Arq = fopen(file1,"a");

    char nomecom[50];
    printf("\n\nInforme o nome comercial do medicamento:\n");
    scanf("\n");
    fgets(nomecom,50,stdin);

    fprintf(Arq,"%s",nomecom);  //a funcao fgets ja adiciona um \0 ao final, que eh convertido em \n

    fclose(Arq);

    GUIad[2] = 1;   //retornar informação que 2 já foi realizado

    GUIadicionar(GUIad,'0');
}

void Quantidade (bool *GUIad){
    char tecla; //tecla armazenara o tipo de unidade

    float dose;

    FILE *Arq;
    Arq = fopen(file1,"a");

    printf("\n\nEscolha o tipo de dosagem do medicamento:\n");
    printf("1 - mL\n");
    printf("2 - comprimido(s)\n");
    printf("3 - spray(s)\n");

    scanf("\n%c",&tecla);  //essa informção será utilizada em seguida

    printf("\n\nInforme a dosagem do medicamento: ");   /* quero _____ml, como fazer a entrada ocorrer no ______ ?*/

    scanf("%f",&dose);

    if(tecla == '1')
        fprintf(Arq,"%f mL\n",dose);
    if(tecla == '2')
        fprintf(Arq,"%f comprimido(s)\n",dose);
    if(tecla == '3')
        fprintf(Arq,"%f spray(s)\n",dose);

    //se houver alguma modificacao nos tipos de dosagem, modificar tambem em QuantoTem()

    fclose(Arq);

    GUIad[3] = 1;

    GUIadicionar(GUIad,tecla);
}

void QuantoTem(bool *GUIad, char undd){
    FILE *Arq;
    Arq = fopen(file1,"a");

    char dosagem [20];
    float estoque;

    if(undd == '1')
        sprintf(dosagem,"mL");
    if(undd == '2')
        sprintf(dosagem,"comprimidos");
    if(undd == '3')
        sprintf(dosagem,"sprays");

    printf("\n\nInforme quantos %s do medicamento voce possui: ",dosagem);
    scanf(" %f",&estoque);

    fprintf(Arq,"%f\n",estoque);

    fclose(Arq);

    GUIad[4] = 1;

    GUIadicionar(GUIad,'0');

}