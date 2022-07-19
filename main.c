#include <stdio.h>
#include <stdlib.h>

/* Distributore automatico di carburante.
Si suppone di avere 3 tipi di carburante identificati da un nome, da un codice identificativo, dal numero
di litri presenti nella scorta e da un prezzo per litro.
Permettere all’utente di:
• Inserire dei soldi (5,10, 20, 50 euro)
• Scegliere il tipo carburante
• Controllare se è possibile soddisfare la richiesta
Nel caso è possibile soddisfare la richiesta rifornire di carburante(aggiornando la scorta)
• Periodicamente controllare i prodotti sotto scorta (minore di 10 litri)
• Dato un tipo di carburante visualizzare il giorno in cui si è avuto la massima vendita. */

/*Procedo quindi a creare la struttura del mio tipo che chiamo Carburante che è composto da 4 variabili
una stringa col nome del carburante, un char con un identificativo del carburante (per convenienza:
1 per la benzina
2 per il metano
3 per il gpl),
e due double, una per il numero di litri nella scorta ed una per il prezzo del carburante al litro*/
struct carburante{
    char nome_carburante[20];
    char id_carburante;
    double num_litri;
    double prezzo_litro;
};
typedef struct carburante Carburante;//assegno al tipo Carburante la struttura da me creata
typedef enum{lunedi,martedi,mercoledi,giovedi,venerdi,sabato,domenica} Giorno; //creo un tipo enumerato per i giorni della settimana

Giorno set_giorno(Giorno giorno);/*function che prende in ingresso un tipo Giorno e ritorna un tipo Giorno che utilizzo
per cambiare il giorno della settimana*/
void rifornimento(Carburante *carburante, int* conta_carburante, double* soldi);/*procedura che prende in ingresso la struttura
Carburante mediante puntatore, un puntatore ad un intero che conta il carburante in quel dato giorno della settimana ed
un puntatore alla variabile double per i soldi da rifornire col distributore*/
void controllo_scorta(Carburante *carburante);/*procedura che prende in input il puntatore alla struttura carburante
e controlla se il numero dei litri è inferiore a 10, se si, rifornisce la scorta di carburante.*/
void inserimento_soldi(double *soldi);/*procedura che inserisce i soldi nel distributore, accetta 5,10,20 o 50€
Prende in input il puntatore alla variabile soldi*/
int indice_max(int giorni[]);/*function che ritorna l'indice del giorno dove si e' venduto il massimo per lo specifico carburante
Prende input un vettore con all'interno i soldi di carburante venduti durante la settimana*/


/*Il funzionamento del mio distributore e' così strutturato:
Si parte dal primo giorno della settimana SEMPRE (che è settato a Lunedì);
Ho creato 3 tipi di carburante: Benzina (id 1), Metano (id 2) e GPL (id 3).
Le scorte le pongo inizialmente alla capacità di 200.
Ciascun tipo di carburante ha un vettore di 7 elementi, inizialmente settati a 0, questo mi servirà per calcolare quanti euro
di carburante sono stati venduti in un dato giorno della settimana.
Sfrutto l'indice per regolarmi col giorno della settimana
Come nel tipo enumerato:
Allo 0 corrisponde Lunedi,
A 1 corrisponde Martedi,
A 2 corrisponde Mercoledi,
A 3 corrisponde Giovedi,
A 4 corrisponde Venerdi,
A 5 corrisponde Sabato,
A 6 corrisponde Domenica;
Un vettore di stringhe viene utilizzato per stampare a video, mediante l'indice del giorno, il giorno in cui ci troviamo;
L'utente si trova in un menu' innestato in un ciclo do-while, dove, a seconda del numero inserito, vengono effettuate
diverse operazioni:
Col numero 1 l'utente sceglie il tipo di carburante con cui vuole rifornirsi,
Col numero 2 l'utente inserisce i soldi nel distributore,
Col numero 3 l'utente rifornisce il veicolo, laddove la scorta lo consente, altrimenti il distributore dà indietro i soldi
all'utente.
Col numero 4 l'utente visualizza in quale giorno della settimana si è venduto più carburante.
Con qualsiasi altro numero l'utente esce dal distributore ed il programma termina.
Il do-while resta dentro fino a quando la variabile menu è compresa tra 1 e 4
Ogni 5 erogazioni di carburante andate a buon fine viene effettuato il controllo periodico sulle scorte di carburante
ed inoltre viene cambiato il giorno della settimana, che avanza di 1.*/
int main(){
    Carburante benzina ={"Benzina",'1',200,1.55};//generazione della variabile benzina col tipo Carburante
    Carburante metano ={"Metano",'2',200,1.00};//generazione della variabile metano col tipo Carburante
    Carburante gpl ={"GPL",'3',200,0.68};//generazione della variabile gpl col tipo Carburante
    int giorni_benzina[7] = {0,0,0,0,0,0,0};
    int giorni_metano[7] = {0,0,0,0,0,0,0};
    int giorni_gpl[7] = {0,0,0,0,0,0,0};
    double soldi = 0; //variabile per il conteggio dei soldi nel distributore
    char* nomi_giorni[] = {"lunedi","martedi","mercoledi","giovedi","venerdi","sabato","domenica"};
    Giorno giorno = 0;//variabile di tipo Giorno per gestire l'indice del giorno in cui ci troviamo.
    int indice_massimo; //variabile utilizzata per trovare il giorno della settimana in cui si e' venduto più carburante
    int menu;//variabile utilizzata per l'input dell'utente del menù
    int controllo_periodico = 0;//contatore del controllo periodico incrementato di 1 ogni volta che viene erogato carburante
    int tipo_carburante = 0;//variabile utilizzata per gestire il tipo di carburante, l'id corrisponde al tipo di carburante
    printf("Benvenuto nel nostro distributore automatico di carburante!\n");
    printf("Siamo in grado di fornire tre tipi di carburante diverso.\nBenzina, Metano e GPL.\n");
    printf("La benzina costa %-.2lf al litro\nIl metano costa %-.2lf al litro\nIL GPL costa %-.2lf al litro\n",
           benzina.prezzo_litro,metano.prezzo_litro,gpl.prezzo_litro);
    printf("\n");
    do{
            printf("Digita 1 per scegliere il tipo di carburante\n");
            printf("Digita 2 per inserire i soldi\n");
            printf("Digita 3 se vuoi rifornire il tuo veicolo\n");
            printf("Digita 4 se vuoi visualizzare in quale giorno della settimana si e' avuta la massima vendita di un carburante\n");
            printf("Digita qualsiasi altro numero per uscire dal distributore di carburante\n");
            printf("\n");
            printf("Ogni cinque rifornimenti viene effettuato un controllo periodico sulle scorte di carburante e\n");
            printf("cambia il giorno della settimana\n");
            printf("Oggi e' %s\n",nomi_giorni[giorno]);
            scanf("%d",&menu);//richiesta all'utente di quale operazione effettuare

            /*Se menù è 1 allora viene richiesto all'utente quale tipo di carburante vuole settare
            1 per la benzina, 2 per il metano e 3 per il gpl (in pratica gli id dei rispettivi carburanti)
            La richiesta viene ripetuta se l'utente non inserisce un numero compreso tra 1 e 3*/
            if(menu == 1){
                    do{
                        printf("Digita 1 per la benzina\n");
                        printf("Digita 2 per il metano\n");
                        printf("Digita 3 per il GPL\n");
                        printf("\n");
                        scanf("%d",&tipo_carburante);
                        if((tipo_carburante < 1)|| (tipo_carburante > 3))
                           printf("Il numero inserito non e' associato ad un tipo di carburante, si prega di riprovare\n");
                           printf("\n");
                    }while((tipo_carburante < 1)|| (tipo_carburante > 3));
                    if(tipo_carburante == 1)
                        printf("Hai selezionato la benzina\n");
                        printf("\n");
                    if(tipo_carburante == 2)
                        printf("Hai selezionato il metano\n");
                        printf("\n");
                    if(tipo_carburante == 3)
                        printf("Hai selezionato il GPL\n");
                        printf("\n");
            }
            if(menu == 2){
                inserimento_soldi(&soldi);//chiamo la procedura per l'inserimento dei soldi passando l'indirizzo di soldi
            }
            if(menu == 3){
                if(tipo_carburante == 1){
                    rifornimento(&benzina,&giorni_benzina[giorno],&soldi);/*Rifornisco benzina se tipo_carburante è 1
                    Passo l'indirizzo della struttura Carburante, l'indirizzo della variabile giorni_benzina con l'indice
                    giorno (che indica il giorno della settimana in cui ci troviamo) e l'indirizzo della variabile soldi*/
                    printf("\n");
                    controllo_periodico++;//incremento di 1 controllo periodico
                }
                if(tipo_carburante == 2){
                    rifornimento(&metano,&giorni_metano[giorno],&soldi);/*Rifornisco metano se tipo_carburante è 2
                    Passo l'indirizzo della struttura Carburante, l'indirizzo della variabile giorni_benzina con l'indice
                    giorno (che indica il giorno della settimana in cui ci troviamo) e l'indirizzo della variabile soldi*/
                    printf("\n");
                    controllo_periodico++;//incremento di 1 controllo periodico
                }
                if(tipo_carburante == 3){
                    rifornimento(&gpl,&giorni_gpl[giorno],&soldi);/*Rifornisco gpl se tipo_carburante è 3
                    Passo l'indirizzo della struttura Carburante, l'indirizzo della variabile giorni_benzina con l'indice
                    giorno (che indica il giorno della settimana in cui ci troviamo) e l'indirizzo della variabile soldi*/
                    printf("\n");
                    controllo_periodico++;//incremento di 1 controllo periodico
                }
                if(tipo_carburante == 0){
                    printf("Non hai inserito il tipo di carburante con cui vuoi rifornirti, riprova dopo averlo impostato\n");
                    printf("\n");
                    /*Se l'utente non ha ancora inserito il tipo di carburante, prima di rifornirsi, allora stampo un errore*/
                }
            }
            if(menu == 4){
                /*In base all'id del tipo del carburante richiamo la function indice_max assegnando il ritorno ad
                indice_massimo.
                Indice_max non è altro che una function che ritorna la posizione del valore più alto tra gli elementi
                del vettore giorni_benzina
                Anche in questo caso gioco con l'indice del vettore, che coincide esattamente con l'indice dei giorni settimanali
                Servendomi dell'indice stampo il giorno in cui si e' venduto di più ed il valore in euro del carburante erogato*/
                if(tipo_carburante == 1){
                    indice_massimo = indice_max(giorni_benzina);
                    printf("Nel giorno di %s, si e' avuta la vendita piu' alta di %s con %d euro spesi\n",
                           nomi_giorni[indice_massimo], benzina.nome_carburante,giorni_benzina[indice_massimo]);
                    printf("\n");
                }
                if(tipo_carburante == 2){
                    indice_massimo = indice_max(giorni_metano);
                    printf("Nel giorno di %s, si e' avuta la vendita piu' alta di %s con %d euro spesi\n",
                           nomi_giorni[indice_massimo], metano.nome_carburante,giorni_metano[indice_massimo]);
                    printf("\n");
                }
                if(tipo_carburante == 3){
                    indice_massimo = indice_max(giorni_gpl);
                    printf("Nel giorno di %s, si e' avuta la vendita piu' alta di %s con %d euro spesi\n",
                           nomi_giorni[indice_massimo], gpl.nome_carburante,giorni_gpl[indice_massimo]);
                    printf("\n");
                }
                if(tipo_carburante == 0){
                    printf("Non hai inserito il tipo di carburante, riprova dopo averlo impostato\n");
                    printf("\n");
                    /*Se l'utente non ha ancora inserito il tipo di carburante, prima di richiedere
                      in quale giorno si è venduto più carburante, allora stampo un errore*/
                }
            }

            /*Se controllo_periodico è 5 allora procedo a richiamare la procedura che controlla le scorte di carburante
            Per ciascun carburante viene chiamata la procedura, passando l'indirizzo della struttura di tipo Carburante
            Inoltre richiamo la function set_giorno passando il giorno, assegnando proprio al giorno il nuovo valore
            che ritornerà.
            Infine setto a 0 controllo_periodico per poter eseguire altre 5 erogazioni prima del nuovo controllo*/
            if((controllo_periodico) == 5){
                controllo_scorta(&benzina);
                controllo_scorta(&metano);
                controllo_scorta(&gpl);
                giorno = set_giorno(giorno);
                controllo_periodico = 0;
            }
    }while((menu >= 1) && (menu <= 4));
    printf("Grazie per aver utilizzato il nostro distributore automatico!\n");
    /*Esco dal programma se l'utente inserisce un numero non compreso tra 1 e 4*/
    return 0;
}

/*set_giorno prende in input una variabile di tipo giorno e ritorna un tipo giorno
Creo un vettore di stringhe per i nomi dei giorni come nel main
Incremento di 1 la variabile giorno
Poi assegno a giorno quello che ottengo dal resto di giorno/7
Questo lo faccio per impedire che giorno superi l'indice massimo che in questo caso è 6, altrimenti mi troverei
fuori il vettore.
Infine stampo il nuovo giorno della settimana a video e ritorno il nuovo valore di giorno*/
Giorno set_giorno(Giorno giorno){
    char* nomi_giorni[] = {"lunedi","martedi","mercoledi","giovedi","venerdi","sabato","domenica"};
    giorno++;
    giorno = (giorno%7);
    printf("E' cambiato il giorno della settimana, siamo a: %s\n", nomi_giorni[giorno]);
    printf("\n");
    return giorno;
}

/*La procedura rifornimento che prende in input ha i puntatori a carburante, a conta_carburante ed a soldi
Controlla innanzitutto che ci siano soldi nel distributore.
Se il puntatore di soldi è 0, allora stampa errore e ritorna al menù principale, altrimenti:
Rifornisce il veicolo se i soldi moltiplicati il prezzo per litro sono minori del numero dei litri di quel carburante
In pratica verifica che ci sia carburante nella scorta a sufficienza.
Se entra nell'if, allora viene soddisfatta la richiesta e quindi vengono aggiornati i litri della scorta
Viene incrementato il puntatore a conta_carburante (che ricordo, nel main è un vettore di 7 elementi, nella procedura,
siccome conosco a priori in quale giorno della settimana siamo, vado a passare il preciso elemento, evitando il passaggio
dell'intero array) aggiungendo i soldi (che vengono castati in int, siccome soldi è una variabile double) ed azzerando i soldi.
Altrimenti, nel caso la scorta fosse minore della richiesta, stampo a video che non è possibile soddisfare l'utente ed
il distributore ritorna indietro i soldi (per convenienza azzero soldi restituendo all'utente tutto ciò che ha inserito)
*/
void rifornimento(Carburante *carburante, int* conta_carburante, double* soldi){
    if(*soldi == 0){
        printf("Devi inserire prima i soldi!\n");
        printf("\n");
    }else{
        printf("Hai scelto di rifornire di %s il tuo veicolo\n",carburante ->nome_carburante);
        if((*soldi * carburante->prezzo_litro)< carburante->num_litri){
            printf("\n");
            printf("E' possibile soddisfare la richiesta, procedo ad erogare %s\n", carburante->nome_carburante);
            carburante->num_litri = (carburante->num_litri - (*soldi * carburante->prezzo_litro));
            printf("\n");
            *conta_carburante = *conta_carburante+ (int)*soldi;
            *soldi = 0;
        }else{
            printf("%s non sufficiente a soddisfare la richiesta, restituisco i %-.lf euro\n",
                    carburante->nome_carburante,*soldi);
            printf("\n");
            *soldi = 0;
        }
    }
}

/*La procedura controllo_scorta che prende in input il puntatore al tipo Carburante controlla quanti litri restano nella scorta
Se sono inferiori a 10 litri, allora il distributore viene rifornito e portato a 200 litri, per convenienza.
Altrimenti stampa semplicemente che non ci sarà un rifornimento, dato che la scorta è maggiore o uguale a 10*/
void controllo_scorta(Carburante *carburante){
    printf("Controllo periodico della scorta di %s restante\n",carburante->nome_carburante);
    printf("Restano %-.lf litri di %s\n",carburante->num_litri,carburante->nome_carburante);
    if(carburante->num_litri < 10){
        printf("Scorta inferiore a 10 litri, procedo a rifornire il distributore\n");
        printf("\n");
        carburante->num_litri = 200;
        printf("Operazione effettuata!");
        printf("I litri nel distributore di %s sono adesso: %-.lf\n",carburante->nome_carburante,carburante->num_litri);
        printf("\n");
    }else{
        printf("Scorta di %s superiore ai 10 litri, non verra' rifornita\n",carburante->nome_carburante);
        printf("\n");
    }
}

/*La procedura inserimento_soldi prende in input il puntatore a soldi
Chiede all'utente di inserire 5,10,20 o 50 euro.
Quindi con un do-while chiedo all'utente di inserire 5,10, 20 o 50, fin quando non inserisce uno di questi 4 valori
Dopo incremento il puntatore a soldi, con i soldi che ha inserito l'utente.
Stampo poi a video quanti soldi ci sono nel distributore, siccome prevedo la possibilità di accumulare più banconote*/
void inserimento_soldi(double* soldi){
    double soldi_inseriti;
    printf("Hai scelto di inserire soldi nel distributore\n");
    printf("\n");
    printf("Inserisci 5,10,20 o 50 euro\n");
    do{
        scanf("%lf",&soldi_inseriti);
    if((soldi_inseriti != 5)&& (soldi_inseriti != 10) && (soldi_inseriti != 20) && (soldi_inseriti != 50))
        printf("Non puoi inserire una banconota da %-.lf euro\n",soldi_inseriti);
        printf("\n");
    }while((soldi_inseriti != 5)&& (soldi_inseriti != 10) && (soldi_inseriti != 20) && (soldi_inseriti != 50));
    printf("Hai inserito %-.lf euro nel distributore\n",soldi_inseriti);
    printf("\n");
    *soldi = *soldi + soldi_inseriti;
    printf("Nel distributore ci sono %-.lf euro\n",*soldi);
}

/*Con indice_max che prende in input un vettore di interi, cerco nel vettore l'indice dell'elemento col valore più alto
Inizialmente settato al primo elemento sia il valore che l'indice.
Faccio scorrere un ciclo for che parte da 1 fino all'indice-1, ogni volta che il la variabile massimo è minore
dell'elemento del vettore, procedo ad assegnare a massimo il nuovo valore, ed ad indice massimo il nuovo indice.
Infine ritorno l'intero indice_massimo*/

int indice_max(int giorni[]){
    int massimo = giorni[0];
    int indice_massimo = 0;
    for(int i=1; i<7;i++){
        if (massimo < giorni [i]){
            massimo = giorni [i];
            indice_massimo = i;
        }
    }
    return indice_massimo;
}
