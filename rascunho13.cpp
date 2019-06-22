#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


/***********************************************************************************************
 * 
 * Compila programa para Arduino automaticamente
 * 
 * Alarme com cor/som diferente para cada medicamento
 * 
 * Uso do botao para parar alarme
 * 
 * OBS: as funcoes relacionadas ao Arduino estao comentadas para evitar erros de compilacao
 *
************************************************************************************************/
 

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
    int *hora;  // a medida que forem escolhidos horarios serao alocados mais espacos de memoria...
    int *min;
    int qh; //quantidade de horarios escolhidos
    int dia[8]; //booleana, 1-7 corresponde aos dias da semana dom-sab

};

struct medicamento med;  //variavel global

struct medicamento *adicionados;   //usada pela funcao Armazenar()

char undd;  //tipo de dosagem

int s;  //size de med.hora e med.min do remedio adicionado agora

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

//void Arduino();

//void Tom(int *tom, int i);

//void Cor(int *cor, int i);

//int ArmazenarStruct();  

//void GUIUpload();

//void UploadArduino();

int main(){

    GUI();

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
        GUIUpload();
        exit(0);
    }
    else{
        printf("COMANDO INVALIDO\n\n");
        GUI();
    }

}

void GUIUpload(){

    char tecla;

    printf("\n\n-----------------------DESPREOCUPE-SE-----------------------\n\n");
    printf("Se voce deseja atualizar as informacoes no seu organizador:\n");
    printf("• Conecte o cabo USB do organizador ao seu computador\n\n");
    printf("1 - Salvar e atualizar organizador\n");
    printf("2 - Salvar e NAO atualizar organizador\n");

    scanf("\n%c",&tecla);

    if(tecla == '1'){
        UploadArduino();
    }
    else if(tecla == '2'){
        return;
    }
    else{
        printf("COMANDO INVALIDO\n\n");
        GUIUpload();
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
    printf("MAXIMO DE 16 CARACTERES\n");
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
        scanf("%1d",&tecla);
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
        if(i == s-1){
            if(med.hora[i] < 10 && med.min[i] >= 10)
                fprintf(Arq,"0%d:%d@",med.hora[i],med.min[i]);
            if(med.hora[i] >= 10 && med.min[i] < 10)
                fprintf(Arq,"%d:0%d@",med.hora[i],med.min[i]);
            if(med.hora[i] < 10 && med.min[i] < 10)
                fprintf(Arq,"0%d:0%d@",med.hora[i],med.min[i]);
            if(med.hora[i] >= 10 && med.min[i] >= 10)
                fprintf(Arq,"%d:%d@",med.hora[i],med.min[i]);
        }
        else{
            if(med.hora[i] < 10 && med.min[i] >= 10)
                fprintf(Arq,"0%d:%d ",med.hora[i],med.min[i]);
            if(med.hora[i] >= 10 && med.min[i] < 10)
                fprintf(Arq,"%d:0%d ",med.hora[i],med.min[i]);
            if(med.hora[i] < 10 && med.min[i] < 10)
                fprintf(Arq,"0%d:0%d ",med.hora[i],med.min[i]);
            if(med.hora[i] >= 10 && med.min[i] >= 10)
                fprintf(Arq,"%d:%d ",med.hora[i],med.min[i]);
        }
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

void Arduino(){
    
    int count;

    FILE *Ard;
    Ard = fopen(arduino,"w+");

    /****************** bibliotecas e variaveis ******************/

    fprintf(Ard,"#include \"Wire.h\"\n");
    fprintf(Ard,"#define DS1307_ADDRESS 0x68\n");
    fprintf(Ard,"byte zero = 0x00;\n"); 
    fprintf(Ard,"\n");
    fprintf(Ard,"#include <LiquidCrystal.h>\n");
    fprintf(Ard,"int rs = 12, e = 11, d4 = 8, d5 = 7, d6 = 4, d7 = 2;\n");
    fprintf(Ard,"LiquidCrystal lcd(rs, e, d4, d5, d6, d7);\n");
    fprintf(Ard,"\n");
    fprintf(Ard,"#define red 10\n");
    fprintf(Ard,"#define green 9\n");
    fprintf(Ard,"#define blue 6\n");
    fprintf(Ard,"\n");
    fprintf(Ard,"#define BUT 5\n");
    fprintf(Ard,"#define BUZ 3\n");
    fprintf(Ard,"\n");
    fprintf(Ard,"byte segundos, minutos, horas, diadasemana, diadomes, mes, ano;\n");
    fprintf(Ard,"\n");

    /******************* funcao que pega horario *******************/
    fprintf(Ard,"byte ConverteParaBCD(byte val)\n");
    fprintf(Ard,"{\n");
    fprintf(Ard," return ( (val/10*16) + (val%%10) );\n");
    fprintf(Ard,"}\n");
    fprintf(Ard,"\n ");
    fprintf(Ard,"byte ConverteparaDecimal(byte val) \n");
    fprintf(Ard,"{ \n");
    fprintf(Ard," return ( (val/16*10) + (val%%16) );\n");
    fprintf(Ard,"}\n");
    fprintf(Ard,"\n");
    fprintf(Ard,"void Relogio()\n");
    fprintf(Ard,"{\n");
    fprintf(Ard," Wire.beginTransmission(DS1307_ADDRESS);\n");
    fprintf(Ard," Wire.write(zero);\n");
    fprintf(Ard," Wire.endTransmission();\n");
    fprintf(Ard," Wire.requestFrom(DS1307_ADDRESS, 7);\n");
    fprintf(Ard," segundos = ConverteparaDecimal(Wire.read());\n");
    fprintf(Ard," minutos = ConverteparaDecimal(Wire.read());\n");
    fprintf(Ard," horas = ConverteparaDecimal(Wire.read() & 0b111111);\n"); 
    fprintf(Ard," diadasemana = ConverteparaDecimal(Wire.read());\n"); 
    fprintf(Ard," diadomes = ConverteparaDecimal(Wire.read());\n");
    fprintf(Ard," mes = ConverteparaDecimal(Wire.read());\n");
    fprintf(Ard," ano = ConverteparaDecimal(Wire.read());\n");
    fprintf(Ard,"}\n");
    fprintf(Ard,"\n");

    /******************* funcao que define cor do RGB *******************/
    fprintf(Ard,"void color(int red_light_value, int green_light_value, int blue_light_value)\n");
    fprintf(Ard,"{\n");
    fprintf(Ard,"  analogWrite(red, red_light_value);\n");
    fprintf(Ard,"  analogWrite(green, green_light_value);\n");
    fprintf(Ard,"  analogWrite(blue, blue_light_value);\n");
    fprintf(Ard,"}\n");
    fprintf(Ard,"\n");

    /************************ void setup ************************/

    fprintf(Ard,"void setup()\n");
    fprintf(Ard,"{\n");
    fprintf(Ard," lcd.begin(16, 2);\n");
    fprintf(Ard," Wire.begin();\n");
    fprintf(Ard," Serial.begin(9600);\n");
    fprintf(Ard,"\n");
    fprintf(Ard," pinMode(red,OUTPUT);\n");
    fprintf(Ard," pinMode(green,OUTPUT);\n");
    fprintf(Ard," pinMode(blue,OUTPUT);\n");
    fprintf(Ard," pinMode(BUT,INPUT);\n");
    fprintf(Ard," pinMode(BUZ,OUTPUT);\n");
    fprintf(Ard,"}\n");
    fprintf(Ard,"\n");

    
    count = ArmazenarStruct();  //quantos medicamentos tem

    

    /************************* void loop *************************/

    //medicamentos verificados de 10 em 10 minutos

    //FUNCAO PARA COR DOS LEDS APARTIR DO NOME
    //FUNCAO PARA TOM DO BUZZER

    fprintf(Ard,"void loop()\n");
    fprintf(Ard,"{\n");
        fprintf(Ard," Relogio();\n");
        fprintf(Ard," if(minutos%%10 == 0){\n");

        int i,j,d,h,tempd;
        char nome[50];
        char tipo[50];

        #define button fprintf(Ard,"     if(digitalRead(BUT)==1){\n");fprintf(Ard,"      color(0,0,0);\n");fprintf(Ard,"      analogWrite(BUZ,0);\n");fprintf(Ard,"      lcd.clear();\n");fprintf(Ard,"      break;\n");fprintf(Ard,"     }\n");

        for(i=0; i<count; i++){  //PARA CADA REMEDIO

            fprintf(Ard,"  if("); //DIA DA SEMANA
                tempd = 0;
                for(d=1; d<=7; d++){
                    if(tempd == 0 && adicionados[i].dia[d] == 1){
                        fprintf(Ard,"diadasemana == %d",d);
                        tempd++;
                    }
                    else if(adicionados[i].dia[d] == 1){
                        fprintf(Ard," || diadasemana == %d",d);
                        tempd++;
                    }
                }
            fprintf(Ard,"){\n");

            fprintf(Ard,"   if("); //HORA E MINUTOS
                for(h=0; h < adicionados[i].qh; h++){
                    if(h==0){
                        fprintf(Ard,"(horas == %d && %d >= minutos && %d < minutos+10)",adicionados[i].hora[h],adicionados[i].min[h],adicionados[i].min[h]);
                    }
                    else{
                        fprintf(Ard," || (horas == %d && %d >= minutos && %d < minutos+10)",adicionados[i].hora[h],adicionados[i].min[h],adicionados[i].min[h]);
                    }
                }
            fprintf(Ard,"){\n");

            //se esse eh o dia e horario do medicamento, ALARME
            fprintf(Ard,"    int i;\n");
            fprintf(Ard,"    for(i=0 ; i<5 ; i++){\n");
            button;
            fprintf(Ard,"     lcd.setCursor(0,0);\n");

            for(j=0; j<50; j++){
                nome[j] = '\0';
            }
            for(j=0; adicionados[i].nomemed[j]!='\n'; j++){
                nome[j] = toupper(adicionados[i].nomemed[j]);
            }
            fprintf(Ard,"     lcd.print(\"%s\");\n",nome);
            fprintf(Ard,"     lcd.setCursor(0,1);\n");

            for(j=0; j<50; j++){
                tipo[j] = '\0';
            }
            for(j=0; adicionados[i].tipo[j]!='\n'; j++){
                tipo[j] = toupper(adicionados[i].tipo[j]);
            }
            if(adicionados[i].qtdd == 1){
                fprintf(Ard,"     lcd.print(\"%.0f %s\");\n",adicionados[i].qtdd, tipo);
            }
            else{
                fprintf(Ard,"     lcd.print(\"%.0f %sS\");\n",adicionados[i].qtdd, tipo);
            }
            int cor[3];
            Cor(cor,i);
            fprintf(Ard,"     color(%d,%d,%d);\n",cor[0],cor[1],cor[2]);
            int tom[4];
            Tom(tom,i);
            fprintf(Ard,"     analogWrite(BUZ,%d);\n",tom[0]);
            button;
            fprintf(Ard,"     delay(500);\n");
            fprintf(Ard,"     analogWrite(BUZ,%d);\n",tom[1]);
            button;
            fprintf(Ard,"     delay(500);\n");
            fprintf(Ard,"     analogWrite(BUZ,%d);\n",tom[2]);
            button;
            fprintf(Ard,"     delay(500);\n");
            fprintf(Ard,"     analogWrite(BUZ,%d);\n",tom[3]);
            button;
            fprintf(Ard,"     delay(500);\n");
            fprintf(Ard,"     analogWrite(BUZ,0);\n");
            button;
            fprintf(Ard,"     delay(2000);\n");
            fprintf(Ard,"     lcd.clear();\n");
            button;
            fprintf(Ard,"     delay(1000);\n");
            fprintf(Ard,"    }\n"); //END FOR alarme
            fprintf(Ard,"    color(0,0,0);\n");
            fprintf(Ard,"    delay(3000);\n"); //garantir que a pessoa ja soltou o botao
            fprintf(Ard,"\n");

            fprintf(Ard,"   }\n");  //END IF hora e minutos
            fprintf(Ard,"  }\n");  //END IF diadasemana
            fprintf(Ard,"  \n");

        }
        fprintf(Ard," delay(60000);\n"); //delay de 1 min

        fprintf(Ard," }\n"); //END if(minutos%%10 == 0)
    fprintf(Ard,"}\n"); //END void loop
    fprintf(Ard,"\n");


    fclose(Ard);

}

void Tom(int *tom, int i){  //i eh o numero do remedio em questao

    int l0,l1,l2,l3;

    l0 = (int)toupper(adicionados[i].nomecom[0]);
    l1 = (int)toupper(adicionados[i].nomecom[1]);
    l2 = (int)toupper(adicionados[i].nomecom[2]);
    l3 = (int)toupper(adicionados[i].nomecom[3]);

    int j;
    j = l0+l1;

    switch(j % 4){
        case 0:
            tom[0] = l0+l1+l2+l3;
            tom[1] = (l0+l1+l2+l3)*10+(l1*100);
            tom[2] = (l0*l1*l2)/1000;
            tom[3] = l3*100;
            break;
        case 1:
            tom[0] = l3*100;
            tom[1] = l0+l1+l2+l3;
            tom[2] = (l0+l1+l2+l3)*10+(l1*100);
            tom[3] = (l0*l1*l2)/1000;
            break;
        case 2:
            tom[0] = (l0*l1*l2)/1000;
            tom[1] = l3*100;
            tom[2] = l0+l1+l2+l3;
            tom[3] = (l0+l1+l2+l3)*10+(l1*100);
            break;
        case 3:
            tom[0] = (l0+l1+l2+l3)*10+(l1*100);
            tom[1] = (l0*l1*l2)/1000;
            tom[2] = l3*100;
            tom[3] = l0+l1+l2+l3;
            break;
    }
}

void Cor(int *cor, int n){ //0 = red, 1 = green, 2 = blue
    int l0,l1,l2;
    int i,f,q;
    int r,g,b;
    l0 = (int)toupper(adicionados[n].nomecom[0]);
    l1 = (int)toupper(adicionados[n].nomecom[1]);
    l2 = (int)toupper(adicionados[n].nomecom[2]);
    
    i = l0 + l1 + l2;
    f = (l0 + l1)/200;
    q = 1-f;

    switch(i % 6){
			case 0: 
                r = 1; g = f; b = 0; break;
			case 1: 
                r = q; g = 1; b = 0; break;
			case 2: 
                r = 0; g = 1; b = f; break;
			case 3: 
                r = 0; g = q; b = 1; break;
			case 4: 
                r = f; g = 0; b = 1; break;
			case 5: 
                r = 1; g = 0; b = q; break;
	}
    cor[0] = r*255;
    cor[1] = g*255;
    cor[2] = b*255;

}

int ArmazenarStruct(){

    char busca[50];
    //char temp[100];
    char ref = '#';
    int count = 0;
    //int s; //size das strings

    adicionados = (medicamento*)malloc(0*sizeof(medicamento));

    FILE *Arq;
    Arq = fopen(file1,"r");

    while(feof(Arq)==0){ //enquanto nao chegar no fim do arquivo
        fscanf(Arq,"%s",busca);
        if(busca[0] == ref){
            count++;
            adicionados = (medicamento*)realloc(adicionados,count*sizeof(medicamento));
            
            adicionados[count-1].hora = (int*)malloc(0*sizeof(int));
            adicionados[count-1].min = (int*)malloc(0*sizeof(int));
            

            fscanf(Arq,"\n");
            fgets(adicionados[count-1].nomemed,50,Arq);   // adiciona \n ao final da string
            /*s = strlen(adicionados[count-1].nomemed);
            adicionados[count-1].nomemed[s-1] = ' '; */

            fscanf(Arq,"\n");
            fgets(adicionados[count-1].nomecom,50,Arq);  
            /*s = strlen(adicionados[count-1].nomemed);
            adicionados[count-1].nomecom[s-1] = ' ';*/   //eliminando \n do gets

            fscanf(Arq,"\n");
            fgets(adicionados[count-1].tipo,50,Arq);  
            /*s = strlen(adicionados[count-1].tipo);
            adicionados[count-1].tipo[s-1] = ' ';*/  

            fscanf(Arq,"\n");
            fscanf(Arq,"%f",&adicionados[count-1].qtdd);

            fscanf(Arq,"\n");
            fscanf(Arq,"%f",&adicionados[count-1].quanto);   

            /****** dias da semana ******/
            int d;
            fscanf(Arq,"\n");
            for(d=1; d<=7; d++){
                fscanf(Arq,"%1d",&adicionados[count-1].dia[d]);
            }

            /********* horarios *********/

            fscanf(Arq,"\n");
            char temp = 'a';
            int q=0;
            adicionados[count-1].qh = 0;
            while(temp != '@'){
                adicionados[count-1].qh ++;
                q = adicionados[count-1].qh;
                adicionados[count-1].hora = (int*)realloc(adicionados[count-1].hora,q*sizeof(int));
                adicionados[count-1].min = (int*)realloc(adicionados[count-1].min,q*sizeof(int));
                fscanf(Arq,"%2d",&adicionados[count-1].hora[q-1]);
                fscanf(Arq,"%c",&temp);  // :
                fscanf(Arq,"%2d",&adicionados[count-1].min[q-1]);
                fscanf(Arq,"%c",&temp);  // espaço ou '@'
            }
            /** TESTE **
            printf("\nremedio %s %d: %d",adicionados[count-1].nomemed,count,q);
            printf("\n%d:%d",adicionados[count-1].hora[q-1],adicionados[count-1].min[q-1]);
            ***********/

            fscanf(Arq," ");  //se não colocar o programa nao roda...
            
            
        }
    }
    

    fclose(Arq);

    return count;
}

void UploadArduino(){

    system("cd ~/Desktop/'Projeto ICC'/DESENVOLVIMENTO/modelo && make && make upload");

}
