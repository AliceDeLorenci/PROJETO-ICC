#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/***********************************************************************************************
 * O QUE FOI FEITO
 * 
 * interface de interacao com o usuario pronta
 * 
 * remove medicamento
 * 
 * PESQUISAR: busca de palavras
 * https://www.codingunit.com/c-tutorial-searching-for-strings-in-a-text-file
 * https://linux.ime.usp.br/~lucasmmg/livecd/documentacao/documentos/mac122/strma.html
 * http://www-igm.univ-mlv.fr/%7Elecroq/string/node14.html#SECTION00140
 * https://www.ime.usp.br/~pf/algoritmos/aulas/strma.html
 * 
 * 
************************************************************************************************/

/* PESQUISAR */
// COMENTARIO   

#define file1 "med.txt"
#define arduino "./modelo/modelo.ino"

struct medicamento
{
    char nomemed[50];
    char nomecom[50];
    char tipo[30];
    float qtdd;
    float quanto;
    //podem ser escolhidos varios horarios...
    //alocacao dinamica..
    int *hora;  // a medida que forem esolhidos horarios serao alocados mais espacos de memoria...
    int *min;
    int dia[8]; //booleana, 1-7 corresponde aos dias da semana dom-sab

};

struct medicamento med;  //variavel global

char undd;  //tipo de dosagem

int s;  //size de med.hora e med.min

void GUI();

void Lista();

void GUIadicionar(bool *GUIad);

void GUIremover();

int ListaNumerada();

void Remover(int num);

void NomeMed(bool *GUIad);

void NomeCom (bool *GUIad);

void Quantidade (bool *GUIad);

void QuantoTem(bool *GUIad);

void Quando (bool *GUIad);

void Dia ();

void Horario ();

void Salvar(bool *GUIad);

void Sair (bool *GUIad);

int Busca();

void Arduino();

int main(){

    GUI();

    //PROBLEMA
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
  /*

 * gerar mensagem de erro para horarios invalidos!
  */

}

/* INTERFACE INICIAL */
void GUI(){
    char tecla;
    bool GUIad[]={0,0,0,0,0,0};  //a primeira posicao nao eh relevante, nem eh utilizada, precisa deixar como ZERO!
    undd = 0;  //resetar tipo de dosagem para novo medicamento

    int i;
    for(i=0; i<8; i++){ //zerar dias da semana
        med.dia[i] = 0;
    }



    printf("\n\n-----------------------DESPREOCUPE-SE-----------------------\n\n");
    printf("MEUS MEDICAMENTOS:\n");
    Lista();
    printf("\n");
    printf("ESCOLHA O QUE DESEJA FAZER:\n");
    printf("1 - Adicionar medicamento\n");
    printf("2 - Remover medicamento\n");
    //printf("3 - Editar medicamento\n");
    /* remover medicamentos 
        //#posteriores -> #n-1  */
    printf("0 - SALVAR E SAIR\n");

    scanf("\n%c",&tecla);

    if(tecla == '1'){
        GUIadicionar(GUIad);
    }
    else if(tecla == '2'){
        GUIremover();
    }
    /*
    else if(tecla == '3'){
        printf("\n\nFuncionalidade em desenvolvimento, obrigada pela compreensão :)\n");
        GUI();
    }*/
    else if(tecla == '0'){
        Arduino();
        exit(0);
    }
    else{
        printf("COMANDO INVALIDO\n\n");
        GUI();
    }

}

/* INTERFACE ADICIONAR */
void GUIadicionar (bool *GUIad){  

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
        printf("4 - Quanto do medicamento você tem\n");   /*completar quantidade antes de quanto!!!!*/
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
            GUIadicionar(GUIad); 
        }
        NomeMed(GUIad);
    }
    else if(tecla == '2'){
        if(GUIad[2] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad); 
        }
        NomeCom(GUIad);
    }
    else if(tecla == '3'){
        if(GUIad[3] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad); 
        }
        Quantidade(GUIad);   //a função quantidade chamara GUIadicionar passando o parametro undd
    }
    else if(tecla == '4'){
        if(GUIad[4] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad); 
        }
        QuantoTem(GUIad);   //aqui sera utilizado o parametro undd
    }
    else if(tecla == '5'){
        if(GUIad[5] == 1){
            printf("COMANDO INVALIDO\n\n");
            GUIadicionar(GUIad); 
        }
        Quando(GUIad);
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
       GUIadicionar(GUIad); 
    }

}

void NomeMed (bool *GUIad){

    printf("\n\nInforme o nome do medicamento:\n");
    scanf("\n");
    fgets(med.nomemed,50,stdin);

    GUIad[1] = 1;   //retornar informação que 1 já foi realizado

    GUIadicionar(GUIad);
}

void NomeCom (bool *GUIad){

    printf("\n\nInforme o nome comercial do medicamento:\n");
    scanf("\n");
    fgets(med.nomecom,50,stdin);

    GUIad[2] = 1;   //retornar informação que 2 já foi realizado

    GUIadicionar(GUIad);
}

void Quantidade (bool *GUIad){
    char tecla; //tecla armazenara o tipo de unidade

    printf("\n\nEscolha o tipo de dosagem do medicamento:\n");
    printf("1 - mL\n");
    printf("2 - comprimido(s)\n");
    printf("3 - spray(s)\n");
    printf("4 - outra unidade\n");

    //se houver alguma modificacao nos tipos de dosagem, modificar tambem em QuantoTem()!!!

    scanf("\n%c",&tecla);  //essa informção será utilizada em seguida

    if(tecla == '1')
        sprintf(med.tipo,"mL");
    else if(tecla == '2')
        sprintf(med.tipo,"comprimido");
    else if(tecla == '3')
        sprintf(med.tipo,"spray");
    else if(tecla == '4')
        sprintf(med.tipo,"unidade");
    else{
        printf("COMANDO INVALIDO\n\n");
        Quantidade(GUIad); 
    }

    printf("\n\nInforme a dosagem do medicamento: ");   /* quero _____ml, como fazer a entrada ocorrer no ______ ?*/

    scanf("%f",&med.qtdd);

    GUIad[3] = 1;

    undd = tecla;

    GUIadicionar(GUIad);
}

void QuantoTem(bool *GUIad){

    char dosagem [20];

    if(undd == '1')
        sprintf(dosagem,"mL");
    if(undd == '2')
        sprintf(dosagem,"comprimidos");
    if(undd == '3')
        sprintf(dosagem,"\"sprays\"");
    if(undd == '4')
        sprintf(dosagem,"unidades");

    printf("\n\nInforme quantos %s do medicamento voce possui: ",dosagem);
    scanf(" %f",&med.quanto);

    GUIad[4] = 1;

    GUIadicionar(GUIad);  

}

void Quando (bool *GUIad){

    Dia();
    Horario();

    GUIad[5] = 1;

    GUIadicionar(GUIad);  
}

void Dia (){

    int tecla;
    int i;

    printf("\n\nInforme em quais dias da semana o medicamento deve ser consumido:\n");
    printf("1 - domingo\n");
    printf("2 - segunda\n");
    printf("3 - terca\n");
    printf("4 - quarta\n");
    printf("5 - quinta\n");
    printf("6 - sexta\n");
    printf("7 - sabado\n");
    printf("Apos escolher todos os dias necessarios, digite 0\n");

    for(i=0; i<8; i++){
        scanf("%d",&tecla);
        if(tecla == 0){
            break;
        }
        med.dia[tecla] = 1;
    }
}

void Horario (){

    int h, m;
    char ref;
    s = 0; //zerar tamanho para novo medicamento

    med.hora = (int*)calloc(0,sizeof(int));
    med.min = (int*)calloc(0,sizeof(int));

    printf("\n\nInsira os horarios em que o medicamento deve ser consumido\n");
    printf("Insira os horarios no formato .HH:MM\n");  //"." eh usado como referencia
    printf("S - Salvar\n");

    //getchar();

    while(1){    //precisa parar em algum momento...
        getchar();  //ignorar enter

        scanf("%c",&ref);
        if(ref != '.'){
            break;
        }
        scanf("%d",&h);/*
        if(h<0 || h>23){
            printf("HORARIO INVALIDO\n");
            Horario();
        }*/
        getchar(); // ":"
        scanf("%d",&m);/*
        if(m<0 || m>59){
            printf("HORARIO INVALIDO\n");
            Horario();
        }*/
        s++;
        med.hora = (int*)realloc(med.hora,s*sizeof(int));
        med.min = (int*)realloc(med.min,s*sizeof(int));
        med.hora[s-1] = h;
        med.min[s-1] = m;
    }


}

void Salvar (bool *GUIad){

    int n;
    n = Busca();

    int i;

    //resetando variavel que contabiliza o que foi feito
    for(i=0; i<6; i++){
        GUIad[i] = 0;
    }

    FILE *Arq;
    Arq = fopen(file1,"a+");
    if (Arq == NULL)  {  
        printf ("\n\nErro no arquivo!\n\n"); 
        printf ("\n\nAs informacoes serao perdidas!\n\n");
        exit(0); 
    }

    fprintf(Arq,"#%d\n",n);  //ID do novo med    /*usar busca para determinar numero do remedio*/
    fprintf(Arq,"%s",med.nomemed);  //como foi usado gets, o \0 eh convertido em \n
    fprintf(Arq,"%s",med.nomecom);
    fprintf(Arq,"%s\n",med.tipo);
    fprintf(Arq,"%f\n",med.qtdd);
    fprintf(Arq,"%f\n",med.quanto);

    for(i=1; i<8; i++){
        fprintf(Arq,"%d ",med.dia[i]);
    }
    fprintf(Arq,"\n");
    for(i=0; i<s; i++){
        fprintf(Arq,"%d:%d ",med.hora[i],med.min[i]);
    }
    fprintf(Arq,"\n");


    fclose(Arq);

}

int Busca (){
    int n = 0; 
    char ref = '#';
    char busca[100];

    FILE *Arq;
    Arq = fopen(file1,"r");
    if(Arq == NULL){
        printf ("\n\nErro no arquivo!\n\n"); 
        exit(0);
    }

    while(feof(Arq)==0){  
        fscanf(Arq,"%s",busca);
        if(busca[0] == ref){
            n++;
        }
    }

    fclose(Arq);

    return n+1; //ja tem n medicamentos, n+1 numero do proximo medicamento (que eh o que vai ser salvo agora)
}

void Lista (){
    char busca[50];
    char nome[50];
    char comercial[50];
    char ref = '#';
    long int snome; //size das strings
    int end = 0;


    FILE *Arq;
    Arq = fopen(file1,"r");

    while(feof(Arq)==0){
        end++;
        fscanf(Arq,"%s",busca);
        if(busca[0] == ref){
            fscanf(Arq,"\n");
            fgets(nome,50,Arq);   // adiciona \n ao final da string
            snome = strlen(nome);
            nome[snome-1] = '\0';   //eliminando \n do gets
            fscanf(Arq,"\n");
            fgets(comercial,50,Arq);  // adiciona \n ao final da string
            printf("• %s - %s",nome,comercial); 
        }
    }
    if(end == 1){
        printf("Nenhum medicamento foi adicionado...\n");
    }

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
        GUIadicionar(GUIad);
    }
    else{
        printf("COMANDO INVALIDO\n\n");
        Sair(GUIad); 
    }
}

void Arduino(){

    FILE *Ard, *Arq;
    Arq = fopen(file1,"r");
    Ard = fopen(arduino,"w+");

    fprintf(Ard,"HELLO");
    //passar programa pro Arduino...

    fclose(Ard);
    fclose(Arq);

}

int ListaNumerada (){
    char busca[50];
    char nome[50];
    char comercial[50];
    char ref = '#';
    int count = 0;
    long int snome; //size das strings


    FILE *Arq;
    Arq = fopen(file1,"r");

    while(feof(Arq)==0){ //enquanto nao chegar no fim do arquivo
        fscanf(Arq,"%s",busca);
        if(busca[0] == ref){
            count++;
            fscanf(Arq,"\n");
            fgets(nome,50,Arq);   // adiciona \n ao final da string
            snome = strlen(nome);
            nome[snome-1] = '\0';   //eliminando \n do gets
            fscanf(Arq,"\n");
            fgets(comercial,50,Arq);  // adiciona \n ao final da string
            printf("%d - %s / %s",count,nome,comercial); 
        }
    }

    fclose(Arq);

    return count;
}

void GUIremover(){
    int tecla1, tecla2;  /*IDEIA: usar string e atoi() para mensagens de erro*/
    int n;

    printf("\n\n-----------------------DESPREOCUPE-SE-----------------------\n");
    printf("\nInforme qual medicamento voce deseja remover:\n");
    n = ListaNumerada();
    printf("0 - VOLTAR PARA A TELA INICIAL\n");

    scanf("\n%d",&tecla1);

    if(tecla1 == 0){
        GUI();
    }
    else if(0 < tecla1 && tecla1 <= n){
        printf("\nO medicamento %d será removido\n",tecla1);
        printf("1 - Remover\n");
        printf("2 - Cancelar\n");
        scanf("\n%d",&tecla2);
        if(tecla2 == 1){
            Remover(tecla1); 
        }
        else if(tecla2 == 2){
            GUIremover();
        }
        else{
            printf("\nCOMANDO INVALIDO\n");
            GUIremover();
        }
    }
    else{
        printf("\nCOMANDO INVALIDO\n");
        GUIremover();
    }

}

void Remover(int num){
    char buffer[100];
    int i, end=0;
    int count = 0;
    char ref = '#';
    char fullref[5];

    sprintf(fullref,"#%d\n",num);  //fgets adiciona \n ao final da string

    FILE *Arq;
    FILE *Temp;

    Arq = fopen(file1,"r");
    Temp = fopen("replace.temp","w+");

    while(fgets(buffer,100,Arq) != NULL){   /* usar feof? */
        if(buffer[0] == ref){
            if(strcmp(buffer,fullref)==0){ //se for o medicamento a ser deletado
                for(i=0; i<8; i++){   // 7 infos por medicamento (nao serao salvos em TEMP, linha 0 a 6) a linha 7 eh do proximo
                    if(fgets(buffer,100,Arq)==NULL){
                        end = 1;
                        break;
                    }
                }
            }
            if(end == 1){
                break;
            }
            count++;
            fprintf(Temp,"#%d\n",count);
            fgets(buffer,100,Arq);  
        }
        fputs(buffer,Temp);
    }

    fclose(Arq);
    fclose(Temp);

    remove(file1);

    rename("replace.temp",file1);

    printf("Medicamento removido com sucesso\n");

    GUIremover();

}