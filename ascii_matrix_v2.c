#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

#define DIM_ALFABETO 26
#define MAX_VEL 2


void ottieni_dimensioni_terminale(int *righe, int *colonne){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *righe = w.ws_row;
    *colonne = w.ws_col;
}

typedef struct{
    int x;
    int y;
    char carattere;
    int velocita;
} Goccia;

char alfabeto[DIM_ALFABETO];
char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 


void dormi_ms(int millisecondi){
    usleep(millisecondi * 1000);
}

void nascondi_cursore() {
    printf("\033[?25l");
}

void mostra_cursore() {
    printf("\033[?25h");
}

void pulisci_schermo() {
    printf("\033[2J");
    printf("\033[H");
}

void vai_a(int riga, int colonna) {
    printf("\033[%d;%dH", riga, colonna);
}


void handler_interruzione(int signum){
    pulisci_schermo();
    mostra_cursore();
    dormi_ms(500);
    printf("\nMADE BY POPIREX\n");
    dormi_ms(500);
    printf("\nThank you for using my program!\n");
    dormi_ms(500);
    exit(0);
}

int main(int argc, char *argv[]){

    signal(SIGINT, handler_interruzione);
    int altezza, larghezza, numero_gocce;

    ottieni_dimensioni_terminale(&altezza, &larghezza);

    numero_gocce = larghezza;

    srand(time(NULL));
    Goccia gocce[numero_gocce];

    for(int i = 0; i < numero_gocce; i++){
        gocce[i].x = rand() % (larghezza - 1);
        gocce[i].y = rand() % altezza;
        gocce[i].velocita = 1 +  (rand() % MAX_VEL);
        gocce[i].carattere = alfabeto[rand() % DIM_ALFABETO];
    }

    nascondi_cursore();
    pulisci_schermo();

    printf("altezza: %d \n larghezza: %d \n", altezza, larghezza);
    dormi_ms(2000);
    pulisci_schermo();

    while(1){

        for(int i = 0; i < numero_gocce; i++){


            // cancello la vecchia goccia

            vai_a(gocce[i].y, gocce[i].x);
            printf(" ");

            // ne aggiorno la posizione ( con la velocità )

            gocce[i].y += gocce[i].velocita;

            // mi assicuro che sia ancora all'interno del terminale -> se no creo una nuova goccia
            if(gocce[i].y > altezza){
                gocce[i].y = 1;
                gocce[i].x = rand() % (larghezza - 1);
                gocce[i].carattere = alfabeto[rand() % DIM_ALFABETO];
            }


            // disegno la goccia nuova ( posiziono il cursore e poi stampo il carattere )

            vai_a(gocce[i].y, gocce[i].x);
            printf("%c", gocce[i].carattere);
            
        }

        fflush(stdout);
        dormi_ms(50);
    }

    mostra_cursore();

    return 0;
}