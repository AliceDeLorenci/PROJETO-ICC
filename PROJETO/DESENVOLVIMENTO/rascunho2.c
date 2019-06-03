/********************************************************************************
 * O QUE FOI FEITO?
 * todas as informacoes sao armazenadas antes de serem passadas para o arquivo
 * 
 ********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* PESQUISAR */
// COMENTARIO   

#define file1 "med.txt"

struct medicamento
{
    char nomemed[50];
    char nomecom[50];
    char tipo[30];
    float qtdd;
    float quanto;

};

struct medicamento med;  //varaivel global

void GUI();

void GUIadicionar(bool *GUIad, char undd);

void NomeMed(bool *GUIad);

void NomeCom (bool *GUIad);

void Quantidade (bool *GUIad);

void QuantoTem(bool *GUIad, char undd);

void Salvar(bool *GUIad);

void Sair (bool *GUIad);

int main(){

    GUI();

    //PROBLEMA
    /*ver como undd esta sendo passado entre funcoes
    se trocar a ordem de execucao, esta perdendo a info??
    */
   /*
   verificar problemas decorrentes da troca de ordem, por exemplo, quanto antes de quantidade
   */

    /* ver funcionamento do teclado / ASCII estendido / conio.h */
    /****
     *  busca em arquivos
     * ideia:  linha 1 - numero de remedios
     *         novo remedio  - scanf linha 1  &n
     *                         "w"  n++
    */

   /*
    como editar texto em um ponto especifico?

   */

    /*se usuario quiser sair antes de terminar: aviso - mudancas serao perdidas
     funcao (struct) para armazenar as infos e so printar no arquivo quando terminar
     */
}

/* INTERFACE INICIAL */
void GUI(){
    char tecla;
    bool GUIad[]={0,0,0,0,0,1};  //a primeira posicao nao eh relevante, nem eh utilizada, precisa deixar como ZERO!

    printf("\n\n-----------------------DESPREOCUPE-SE-----------------------\n");
    printf("Escolha o que deseja fazer:\n");

    //lista de medicamentos

    printf("1 - Adicionar medicamento\n");
    printf("2 - Editar medicamento\n");
    printf("3 - Remover medicamento\n");
    /* remover medicamentos 
        //#posteriores -> #n-1  */
    printf("0 - SALVAR E SAIR\n");

    scanf("\n%c",&tecla);

    if(tecla == '1'){
        GUIadicionar(GUIad,'0');
    }
    else if(tecla == '2'){
        printf("\n\nFuncionalidade em desenvolvimento, obrigada pela compreensão :)\n");
        GUI();
    }
    else if(tecla == '3'){
        printf("\n\nFuncionalidade em desenvolvimento, obrigada pela compreensão :)\n");
        GUI();
    }
    else if(tecla == '0'){
        exit(0);
    }
    else{
        printf("COMANDO INVALIDO\n\n");
        GUI();
    }

}

/* INTERFACE ADICIONAR */
void GUIadicionar (bool *GUIad, char undd){  //o parametro unidade sera utilizado para passar de uma funcao para outra o tipo de dosagem do medicamento
    /*ver como undd esta sendo passado entre funcoes
    se trocar a ordem de execucao, esta perdendo a info??
    */

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
        Salvar(GUIad);
    }

    printf("V - VOLTAR PARA A TELA INICIAL\n");

    scanf("\n%c",&tecla);

    if(tecla == '1'){
        if(GUIad[1] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad,undd); 
        }
        NomeMed(GUIad);
    }
    else if(tecla == '2'){
        if(GUIad[2] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad,undd); 
        }
        NomeCom(GUIad);
    }
    else if(tecla == '3'){
        if(GUIad[3] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad,undd); 
        }
        Quantidade(GUIad);   //a função quantidade chamara GUIadicionar passando o parametro undd
    }
    else if(tecla == '4'){
        if(GUIad[4] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad,undd); 
        }
        QuantoTem(GUIad,undd);   //aqui sera utilizado o parametro undd
    }
    else if(tecla == '5'){
        if(GUIad[5] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad,undd); 
        }
        printf("\n\nFuncionalidade em desenvolvimento, obrigada pela compreensão :)\n");
        GUIadicionar(GUIad,undd);
    }
    else if((tecla == 'V' || tecla == 'v') && (done == 5)){  //se quiser sair e o medicamento ja foi salvo...
        GUI();
        //observe que a funcao GUI ja reseta a variavel booleana
        //nao ha necessidade de sesetar o structs, pois quando um novo med for adicionado,
        //o structs vai ser simplesmente substituido
        //o struct ja foi salvo no arquivo
    }
    else if((tecla == 'V' || tecla == 'v') && (done != 5)){  //se quiser sair e o medicamento ja nao foi salvo...
        Sair(GUIad);
    }
    else{
       printf("COMANDO INVALIDO\n\n");
       GUIadicionar(GUIad,'0'); 
    }

}



void NomeMed (bool *GUIad){

    printf("\n\nInforme o nome do medicamento:\n");
    scanf("\n");
    fgets(med.nomemed,50,stdin);

    GUIad[1] = 1;   //retornar informação que 1 já foi realizado

    GUIadicionar(GUIad,'0');
}

void NomeCom (bool *GUIad){

    printf("\n\nInforme o nome comercial do medicamento:\n");
    scanf("\n");
    fgets(med.nomecom,50,stdin);

    GUIad[2] = 1;   //retornar informação que 2 já foi realizado

    GUIadicionar(GUIad,'0');
}

void Quantidade (bool *GUIad){
    char tecla; //tecla armazenara o tipo de unidade

    printf("\n\nEscolha o tipo de dosagem do medicamento:\n");
    printf("1 - mL\n");
    printf("2 - comprimido(s)\n");
    printf("3 - spray(s)\n");

    //se houver alguma modificacao nos tipos de dosagem, modificar tambem em QuantoTem()!!!

    scanf("\n%c",&tecla);  //essa informção será utilizada em seguida

    if(tecla == '1')
        sprintf(med.tipo,"mL");
    else if(tecla == '2')
        sprintf(med.tipo,"comprimido");
    else if(tecla == '3')
        sprintf(med.tipo,"spray");
    else{
        printf("COMANDO INVALIDO\n\n");
        Quantidade(GUIad); 
    }

    printf("\n\nInforme a dosagem do medicamento: ");   /* quero _____ml, como fazer a entrada ocorrer no ______ ?*/

    scanf("%f",&med.qtdd);

    GUIad[3] = 1;

    GUIadicionar(GUIad,tecla);
}

void QuantoTem(bool *GUIad, char undd){

    char dosagem [20];

    if(undd == '1')
        sprintf(dosagem,"mL");
    if(undd == '2')
        sprintf(dosagem,"comprimidos");
    if(undd == '3')
        sprintf(dosagem,"\"sprays\"");

    printf("\n\nInforme quantos %s do medicamento voce possui: ",dosagem);
    scanf(" %f",&med.quanto);

    GUIad[4] = 1;

    GUIadicionar(GUIad,'0');  //depois de utilizado o tipo de dosagem ZERAR para deixar pronto para o proximo med 

}

void Salvar (bool *GUIad){
    int i;

    //resetando variavel que contabiliza o que foi feito
    for(i=0; i<6; i++){
        GUIad[i] = 0;
    }
    GUIad[5] = 1;

    FILE *Arq;
    Arq = fopen(file1,"a+");
    if (Arq == NULL)  {  
        printf ("\n\nErro no arquivo!\n\n"); 
        printf ("\n\nAs informacoes serao perdidas!\n\n");
        exit(0); 
    }

    fprintf(Arq,"#1\n");  //ID do novo med    /*usar busca para determinar numero do remedio*/
    fprintf(Arq,"%s",med.nomemed);  //como foi usado gets, o \0 eh convertido em \n
    fprintf(Arq,"%s",med.nomecom);
    fprintf(Arq,"%s\n",med.tipo);
    fprintf(Arq,"%f\n",med.qtdd);
    fprintf(Arq,"%f\n",med.quanto);


    fclose(Arq);

}

void Sair (bool *GUIad){
    printf("\n\nSe voce sair agora o novo medicamento nao sera salvo!!\n\n");
    printf("1 - Voltar para a tela inicial\n");
    printf("2 - Continuar\n");
    char tecla2;
    scanf("\n%c",&tecla2);
    if(tecla2 == '1'){
        GUI();
    }
    else if(tecla2 == '2'){
        GUIadicionar(GUIad,'0');
    }
    else{
        printf("COMANDO INVALIDO\n\n");
        Sair(GUIad); 
    }
}