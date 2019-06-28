#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define file1 "./med.txt"
#define arduino "./arduino/arduino.ino"


//ATUALIZAR LISTA

/****
 *  g_signal_connect(entry,"activate",G_CALLBACK(button_clicked),entry);  //press enter event
 *  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle),true);
 * *********/

// COMPILAR:

// g++ teste.cpp -o prog `pkg-config --libs --cflags  gtk+-3.0`

struct medicamento
{
    char nomemed[50];
    char nomecom[50];
    char tipo[30];
    int qtdd;
    //podem ser escolhidos varios horarios...
    //alocacao dinamica..
    int *hora;  // a medida que forem escolhidos horarios serao alocados mais espacos de memoria...
    int *min;
    int qh; //quantidade de horarios escolhidos
    int dia[8]; //booleana, 1-7 corresponde aos dias da semana dom-sab

};

char hrs[100];

int remqual;

int adicionar = 0;

struct medicamento med;  //variavel global

struct medicamento *adicionados;   //usada pela funcao Armazenar()

int Lista (GtkWidget *grid, GtkWidget *label);

void Adicionar(GtkWidget *button, gpointer window);

void ButtonClicked (GtkWidget *entry, GtkWidget *toggle);

void NomeMed (GtkWidget *toggle, GtkWidget *entry);

void NomeCom (GtkWidget *toggle, GtkWidget *entry);

void Tipo (GtkWidget *toggle, GtkWidget **radios);

void Quantidade (GtkWidget *toggle, GtkWidget *entry);

void Dia (GtkWidget *toggle, GtkWidget **checks);

void Horario (GtkWidget *toggle, GtkWidget *entry);

int Busca ();

void Salvar ();

void Remover(GtkWidget *button, gpointer window);

int ListaRemover (GtkWidget *grid, GtkWidget **radio, GtkWidget *space);

void RemoverQual(GtkWidget **radio, int num);

void Removendo(int num);

void Sair (GtkWidget *button, GtkWidget *window);

void Arduino();

void Tom(int *tom, int i);

void Cor(int *cor, int i);

int ArmazenarStruct();  

void UploadArduino();


int main(int argc, char *argv[])
{
    int i; 

    gtk_init(&argc,&argv); //initialize gtk

    GtkWidget *window, *image1, *image2, *grid, *label, *button1, *button2, *button3; //declare needed variables

    refazer:

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //create window

    //if exit button is clicked, exit from program
    g_signal_connect(window,"delete_event",G_CALLBACK(gtk_main_quit),window); 

    // PROGRAM STARTS HERE

    grid = gtk_grid_new();

    image1 = gtk_image_new_from_file("./images/titulo.png");
    image2 = gtk_image_new_from_file("./images/meds.png");

    gtk_grid_attach(GTK_GRID(grid),image1,0,0,1,1); // left, top, width, height
    gtk_grid_attach(GTK_GRID(grid),image2,0,1,1,1);

    i = Lista(grid,label);

    button1 = gtk_button_new_with_label("ADICIONAR NOVO MEDICAMENTO");
    button2 = gtk_button_new_with_label("REMOVER MEDICAMENTO");
    button3 = gtk_button_new_with_label("SALVAR E SAIR");

    gtk_grid_attach(GTK_GRID(grid),button1,0,i,1,1);
    g_signal_connect(button1,"clicked",G_CALLBACK(Adicionar),window);

    i++;
    gtk_grid_attach(GTK_GRID(grid),button2,0,i,1,1);
    g_signal_connect(button2,"clicked",G_CALLBACK(Remover),window);

    i++;
    gtk_grid_attach(GTK_GRID(grid),button3,0,i,1,1);  
    g_signal_connect(button3,"clicked",G_CALLBACK(Sair),window);

    
    gtk_container_add(GTK_CONTAINER(window),grid);

    //gtk_widget_set_size_request(window,480, 680);

    gtk_window_set_title(GTK_WINDOW(window),"DESPREOCUPE-SE");

    // PROGRAM ENDS HERE

    gtk_widget_show_all(window);  //show all widgets
    gtk_main();  //starts main loop

    if(adicionar == 1){
        //printf("aqui\n");
        gtk_widget_destroy(window);
        adicionar = 0;
        goto refazer;
    }

    return 0;
}

int Lista (GtkWidget *grid, GtkWidget *label){

    char busca[50];
    char nome[50];
    char comercial[50];
    char ref = '#';
    long int snome; //size das strings
    int end = 0, i=3, j;
    char etiqueta[100];


    FILE *Arq;
    Arq = fopen(file1,"r");

    label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid),label,0,i,1,1);

    while(feof(Arq)==0){
        end++;
        strcpy(etiqueta,"");
        fscanf(Arq,"%s",busca);
        if(busca[0] == ref){
            i++;

            fscanf(Arq,"\n");
            fgets(nome,50,Arq);   // adiciona \n ao final da string
            snome = strlen(nome);
            nome[snome-1] = ' ';   //eliminando \n do gets
            for(j=0; j<snome; j++){
                nome[j] = toupper(nome[j]);
            }

            fscanf(Arq,"\n");
            fgets(comercial,50,Arq);  // adiciona \n ao final da string
            snome = strlen(comercial);
            comercial[snome-1] = ' ';   //eliminando \n do gets
            for(j=0; j<snome; j++){
                comercial[j] = toupper(comercial[j]);
            }

            //strcat(etiqueta,"• ");
            strcat(etiqueta,nome);
            strcat(etiqueta,"• ");
            strcat(etiqueta,comercial);
            label = gtk_label_new(etiqueta);
            //gtk_label_set_text(GTK_LABEL(label),etiqueta);
            gtk_grid_attach(GTK_GRID(grid),label,0,i,1,1); 
            i++;
            label = gtk_label_new("");
            gtk_grid_attach(GTK_GRID(grid),label,0,i,1,1);
        }
    }
    if(end == 1){
        label = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(grid),label,0,i,1,1);
        i++;
        label = gtk_label_new("Nenhum medicamento foi adicionado...");
        gtk_grid_attach(GTK_GRID(grid),label,0,i,1,1); 
        i++;
        label = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(grid),label,0,i,1,1);
    }

    i++;
    return i;

    fclose(Arq);
}

void ButtonClicked (GtkWidget *entry, GtkWidget *toggle){

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(toggle),true);

}

void Adicionar(GtkWidget *button, gpointer window){

    int argc;
    char **argv;

    GtkWidget *dialog, *content_area, *grid, *image;
    GtkWidget *entry[4], *radio[4], *label, *but[7], *space, *toggle;

    dialog = gtk_dialog_new_with_buttons("NOVO MEDICAMENTO",GTK_WINDOW(window),GTK_DIALOG_MODAL,("_CONCLUIR"),GTK_RESPONSE_ACCEPT,("_CANCELAR"),GTK_RESPONSE_REJECT,NULL); 
                                                  // dialog parent                                                      //as many buttons as you need
    
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();

    image = gtk_image_new_from_file("./images/novomeds.png");
    gtk_grid_attach(GTK_GRID(grid),image,0,0,8,1);

    entry[0] = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry[0]),"Nome popular do medicamento");
    gtk_grid_attach(GTK_GRID(grid),entry[0],0,1,7,1);
    
    toggle = gtk_toggle_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid),toggle,7,1,1,1);
    g_signal_connect(toggle,"toggled",G_CALLBACK(NomeMed),entry[0]);
    g_signal_connect(entry[0],"activate",G_CALLBACK(ButtonClicked),toggle);  //press enter event
    
    entry[1] = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry[1]),"Nome comercial do medicamento");
    gtk_grid_attach(GTK_GRID(grid),entry[1],0,2,7,1);

    toggle = gtk_toggle_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid),toggle,7,2,1,1);
    g_signal_connect(toggle,"toggled",G_CALLBACK(NomeCom),entry[1]);
    g_signal_connect(entry[1],"activate",G_CALLBACK(ButtonClicked),toggle);  //press enter event

    label = gtk_label_new("TIPO DE DOSAGEM:");
    gtk_grid_attach(GTK_GRID(grid),label,0,3,7,1);

    radio[0] = gtk_radio_button_new_with_label(NULL,"mL");  //NULL -> no group, this is the first radio
    gtk_grid_attach(GTK_GRID(grid),radio[0],0,4,7,1);

    radio[1] = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio[0])), "comprimidos");
    gtk_grid_attach(GTK_GRID(grid),radio[1],0,5,7,1);

    radio[2] = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio[0])), "sprays");
    gtk_grid_attach(GTK_GRID(grid),radio[2],0,6,7,1);

    radio[3] = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio[0])), "outra unidade");
    gtk_grid_attach(GTK_GRID(grid),radio[3],0,7,7,1);

    toggle = gtk_toggle_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid),toggle,7,7,1,1);
    g_signal_connect(toggle,"toggled",G_CALLBACK(Tipo),radio);

    entry[2] = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry[2]),"Dosagem");
    gtk_grid_attach(GTK_GRID(grid),entry[2],0,8,7,1);

    toggle = gtk_toggle_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid),toggle,7,8,1,1);
    g_signal_connect(toggle,"toggled",G_CALLBACK(Quantidade),entry[2]);
    g_signal_connect(entry[2],"activate",G_CALLBACK(ButtonClicked),toggle);  //press enter event

    space = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid),space,0,9,7,1);

    label = gtk_label_new("SELECIONE OS DIAS EM QUE O MEDICAMENTO DEVE SER UTILIZADO:");
    gtk_grid_attach(GTK_GRID(grid),label,0,10,7,1);

    space = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid),space,0,11,7,1);

    but[0] = gtk_check_button_new_with_label("domingo");
    gtk_grid_attach(GTK_GRID(grid),but[0],0,12,1,1);

    but[1] = gtk_check_button_new_with_label("segunda");
    gtk_grid_attach(GTK_GRID(grid),but[1],1,12,1,1);

    but[2] = gtk_check_button_new_with_label("terca");
    gtk_grid_attach(GTK_GRID(grid),but[2],2,12,1,1);

    but[3] = gtk_check_button_new_with_label("quarta");
    gtk_grid_attach(GTK_GRID(grid),but[3],3,12,1,1);

    but[4] = gtk_check_button_new_with_label("quinta");
    gtk_grid_attach(GTK_GRID(grid),but[4],4,12,1,1);

    but[5] = gtk_check_button_new_with_label("sexta");
    gtk_grid_attach(GTK_GRID(grid),but[5],5,12,1,1);

    but[6] = gtk_check_button_new_with_label("sabado");
    gtk_grid_attach(GTK_GRID(grid),but[6],6,12,1,1);

    toggle = gtk_toggle_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid),toggle,7,12,1,1);
    g_signal_connect(toggle,"toggled",G_CALLBACK(Dia),but);

    space = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid),space,0,13,7,1);

    entry[3] = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry[3]),"Horarios - FORMATO HH:MM");
    gtk_grid_attach(GTK_GRID(grid),entry[3],0,14,7,1);

    toggle = gtk_toggle_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid),toggle,7,14,1,1);
    g_signal_connect(toggle,"toggled",G_CALLBACK(Horario),entry[3]);
    g_signal_connect(entry[3],"activate",G_CALLBACK(ButtonClicked),toggle);  //press enter event

    gtk_container_add(GTK_CONTAINER(content_area),grid);
    

    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if(response == GTK_RESPONSE_ACCEPT){
        adicionar = 1;
        //printf("%d",adicionar);
        Salvar ();
        //gtk_widget_destroy(dialog);
        gtk_main_quit();
        //main(argc,argv);
        //g_print("OK\n");
    }
    //else
    //    g_print("Cancel\n");

    gtk_widget_destroy(dialog);
}

void NomeMed (GtkWidget *toggle, GtkWidget *entry){

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle)))
    {
        //printf("Toogle button activated\n");
        strcpy(med.nomemed,gtk_entry_get_text(GTK_ENTRY(entry)));
        strcat(med.nomemed,"\n");
        //printf("%s %s\n",gtk_entry_get_text(GTK_ENTRY(entry)),med.nomemed);
    }

}

void NomeCom (GtkWidget *toggle, GtkWidget *entry){

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle)))
    {
        //printf("Toogle button activated\n");
        strcpy(med.nomecom,gtk_entry_get_text(GTK_ENTRY(entry)));
        strcat(med.nomecom,"\n");
        //printf("%s %s\n",gtk_entry_get_text(GTK_ENTRY(entry)),med.nomecom);
    }

}

void Tipo (GtkWidget *toggle, GtkWidget **radios){

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[0]))){ 
            //printf("The 1 button is active\n");
            sprintf(med.tipo,"mL");
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[1]))){ 
            //printf("The 2 button is active\n");
            sprintf(med.tipo,"comprimido");
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[2]))){ 
            //printf("The 3 button is active\n");
            sprintf(med.tipo,"spray");
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radios[3]))){ 
            //printf("The 4 button is active\n");
            sprintf(med.tipo,"unidade");
    }

}

void Quantidade (GtkWidget *toggle, GtkWidget *entry){

    int qtdd;

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle)))
    {
        //printf("Toogle button activated\n");
        sscanf(gtk_entry_get_text(GTK_ENTRY(entry)),"%d",&qtdd);
        med.qtdd = qtdd;
        //printf("%d\n",med.qtdd);
    }

}

void Dia (GtkWidget *toggle, GtkWidget **checks){

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[0]))){ 
            //printf("dom\n");
            med.dia[1] = 1;
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[1]))){ 
            //printf("seg\n");
            med.dia[2] = 1;
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[2]))){ 
            //printf("ter\n");
            med.dia[3] = 1;
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[3]))){ 
            //printf("quar\n");
            med.dia[4] = 1;
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[4]))){ 
            //printf("quin\n");
            med.dia[5] = 1;
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[5]))){ 
            //printf("sex\n");
            med.dia[6] = 1;
    }
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checks[6]))){ 
            //printf("sab\n");
            med.dia[7] = 1;
    }

    //printf("%d\n",med.dia[1]);

}

void Horario (GtkWidget *toggle, GtkWidget *entry){

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle)))
    {
        //printf("Toogle button activated\n");
        strcpy(hrs,gtk_entry_get_text(GTK_ENTRY(entry)));
        strcat(hrs,"@");
        //printf("%s %s\n",gtk_entry_get_text(GTK_ENTRY(entry)),hrs);
    }

}

void Salvar (){

    int n;
    n = Busca();

    int i;


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
    fprintf(Arq,"%d\n",med.qtdd);
    //fprintf(Arq,"%f\n",med.quanto);

    for(i=1; i<8; i++){
        fprintf(Arq,"%d ",med.dia[i]);
    }
    fprintf(Arq,"\n");
    fprintf(Arq,"%s",hrs);
    /*
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
    }*/
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

void Remover(GtkWidget *button, gpointer window){

    int num; //numero de meds que tem

    GtkWidget *dialog, *content_area, *grid, *image;
    GtkWidget *radio[50], *space;

    dialog = gtk_dialog_new_with_buttons("REMOVER MEDICAMENTO",GTK_WINDOW(window),GTK_DIALOG_MODAL,("_REMOVER"),GTK_RESPONSE_ACCEPT,("_CANCELAR"),GTK_RESPONSE_REJECT,NULL); 
                                                  // dialog parent                                                      //as many buttons as you need
    
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();

    image = gtk_image_new_from_file("./remmeds.png");
    gtk_grid_attach(GTK_GRID(grid),image,0,0,8,1);

    num = ListaRemover(grid,radio,space);

    //printf("%d\n",num);

    gtk_container_add(GTK_CONTAINER(content_area),grid);
    

    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if(response == GTK_RESPONSE_ACCEPT){
        RemoverQual(radio,num);
        adicionar = 1;
        gtk_main_quit();
        //g_print("OK\n");
    }
    //else
        //g_print("Cancel\n");

    gtk_widget_destroy(dialog);
}

int ListaRemover (GtkWidget *grid, GtkWidget **radio, GtkWidget *space){

    char busca[50];
    char nome[50];
    char comercial[50];
    char ref = '#';
    long int snome; //size das strings
    int end = 0, i=1, j, num = 0;
    char etiqueta[100];


    FILE *Arq;
    Arq = fopen(file1,"r");

    space = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid),space,0,i,1,1);

    while(feof(Arq)==0){
        end++;
        strcpy(etiqueta,"");
        fscanf(Arq,"%s",busca);
        if(busca[0] == ref){
            num++;
            i++;

            fscanf(Arq,"\n");
            fgets(nome,50,Arq);   // adiciona \n ao final da string
            snome = strlen(nome);
            nome[snome-1] = ' ';   //eliminando \n do gets
            for(j=0; j<snome; j++){
                nome[j] = toupper(nome[j]);
            }

            fscanf(Arq,"\n");
            fgets(comercial,50,Arq);  // adiciona \n ao final da string
            snome = strlen(comercial);
            comercial[snome-1] = ' ';   //eliminando \n do gets
            for(j=0; j<snome; j++){
                comercial[j] = toupper(comercial[j]);
            }

            strcat(etiqueta,nome);
            strcat(etiqueta,"- ");
            strcat(etiqueta,comercial);
            if(end == 1){
                radio[1] = gtk_radio_button_new_with_label(NULL,etiqueta);
                gtk_grid_attach(GTK_GRID(grid),radio[1],0,i,1,1); 
            }
            else{
                radio[num] = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio[1])),etiqueta);
                gtk_grid_attach(GTK_GRID(grid),radio[num],0,i,1,1); 
            }
            i++;
            space = gtk_label_new("");
            gtk_grid_attach(GTK_GRID(grid),space,0,i,1,1);
        }
    }
    if(end == 1){
        space = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(grid),space,0,i,1,1);
        i++;
        space = gtk_label_new("Ainda não há medicamentos...");
        gtk_grid_attach(GTK_GRID(grid),space,0,i,1,1); 
    }

    //i++;
    //printf("%d\n",num);
    return num;

    fclose(Arq);
}

void RemoverQual(GtkWidget **radio, int num){
    int i, qual;
    for(i=1; i <= num; i++){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio[i]))){
                //printf("The %d button is active\n",i);
                qual = i;
        }
    }
    Removendo(qual);
}

void Removendo(int num){
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
                for(i=0; i<7; i++){   // 6 (RETIREI QUANTO) infos por medicamento (nao serao salvos em TEMP, linha 0 a 5) a linha 6 eh do proximo
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

    //printf("Medicamento removido com sucesso\n");

}

void Sair (GtkWidget *button, GtkWidget *window){
    
    Arduino();
/**********************************************************/

    GtkWidget *dialog, *content_area, *grid, *label;

    dialog = gtk_dialog_new_with_buttons("SAIR",GTK_WINDOW(window),GTK_DIALOG_MODAL,("_ATUALIZAR"),GTK_RESPONSE_ACCEPT,("_NÃO ATUALIZAR"),GTK_RESPONSE_REJECT,NULL); 
                                                  // dialog parent                                                      //as many buttons as you need
    
    
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    grid = gtk_grid_new();

    label = gtk_label_new("Se voce deseja atualizar o seu organizador");
    gtk_grid_attach(GTK_GRID(grid),label,0,0,1,1);

    label = gtk_label_new("conecte o cabo USB do organizador ao computador.");
    gtk_grid_attach(GTK_GRID(grid),label,0,1,1,1);

    label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid),label,0,2,1,1);

    gtk_container_set_border_width(GTK_CONTAINER(content_area),50);
    gtk_container_add(GTK_CONTAINER(content_area),grid);
    

    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if(response == GTK_RESPONSE_ACCEPT){
       UploadArduino();
    }

    gtk_widget_destroy(dialog);

/****************************************************/
    gtk_main_quit();
}

void UploadArduino(){

    system("cd ~/Desktop/DESPREOCUPE-SE/arduino && make && make upload");

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


    fprintf(Ard,"void loop()\n");
    fprintf(Ard,"{\n");
        fprintf(Ard," Relogio();\n");
        fprintf(Ard," if(minutos%%10 == 0){\n");

        int i,j,d,h,tempd;
        char nome[50];
        char tipo[50];

        #define button fprintf(Ard,"     if(digitalRead(BUT)==1){\n");fprintf(Ard,"      color(0,0,0);\n");fprintf(Ard,"      analogWrite(BUZ,0);\n");fprintf(Ard,"      lcd.clear();\n");fprintf(Ard,"      delay(5000);\n");fprintf(Ard,"      break;\n");fprintf(Ard,"     }\n");
        //no button tem um delay de 5 segundos pra nao interromper outro remedio

        for(i=0; i<count; i++){  //PARA CADA REMEDIO

            fprintf(Ard,"  if("); //DIA DA SEMANA
                tempd = 0;
                for(d=1; d<=7; d++){
                    if(tempd == 0 && adicionados[i].dia[d] == 1){
                        fprintf(Ard,"diadasemana == %d",d-1);
                        tempd++;
                    }
                    else if(adicionados[i].dia[d] == 1){
                        fprintf(Ard," || diadasemana == %d",d-1);
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
                fprintf(Ard,"     lcd.print(\"%d %s\");\n",adicionados[i].qtdd, tipo);
            }
            else{
                fprintf(Ard,"     lcd.print(\"%d %sS\");\n",adicionados[i].qtdd, tipo);
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
            fscanf(Arq,"%d",&adicionados[count-1].qtdd);

            //RETIREI QUANTO TEM
            //fscanf(Arq,"\n");
            //fscanf(Arq,"%f",&adicionados[count-1].quanto);   

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
                fscanf(Arq,"%d",&adicionados[count-1].hora[q-1]);
                fscanf(Arq,"%c",&temp);  // :
                fscanf(Arq,"%d",&adicionados[count-1].min[q-1]);
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