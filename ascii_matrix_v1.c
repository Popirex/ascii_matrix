#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DIM_ALFABETO 26
#define DIM_SPAZI 8
#define DIM_TEMPO_MS 20

void dormi_ms(int millisecondi){
    usleep(millisecondi * 1000);
}

char alfabeto[DIM_ALFABETO];

char alfabeto[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 

char *spazi[] = {
    " ",      
    "  ",     
    "   ",    
    "    ",
    "     ",     
    "      ", 
    "       ",     
    "        "
};

long int random(void);

int main( int argc, char *argv[]){

    srand(time(NULL));
    int i = 0;


    while(1){
        
        if ( i == 0){
            i++;
            continue;
        }

        int numero_alfabeto = rand() % (DIM_ALFABETO);
        int numero_spazi = rand() % (DIM_SPAZI);
        int numero_timer = rand() % (DIM_TEMPO_MS);

        printf("%c%s", alfabeto[numero_alfabeto], spazi[numero_spazi]);

        if( (i % 10) == 0 ){
            int numero_spazio_singolo = rand() % (DIM_SPAZI);
            printf("\n%s", spazi[numero_spazio_singolo]);
        }
        i++;

        dormi_ms(numero_timer);

    }

    
    

    return 0;
} 