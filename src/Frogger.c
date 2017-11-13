#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Juegos.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/Menu.h"	
	
int main(int argc, char *argv[]){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	char Flag = -10;
	
	if( InicioGenerico( &display, &event_queue ) == ERROR){
		DestruirGenerico( &display, &event_queue );
		return ERROR;		
	}
	
	while( Flag != SALIR && Flag != ERROR ){		
		Flag = Menu( &display, &event_queue );							// Devuelve OvsC, OvsO_OFFLINE, OvsO_ONLINE
		if( Flag == OvsC ){
			fprintf(stdout, "\n Estoy en OvsC \n");
			Flag = Juego1vsC( &display, &event_queue ); 				// Devuelve SALIR ,VOLVER o ERROR
		}
		else if( Flag == OvsO_OFFLINE ){
			fprintf(stdout, "\n Estoy en OvsO OFFLINE \n");
			//Flag = Juego1vs1_OFFLINE( &display, &event_queue ); 		// Devuelve SALIR ,VOLVER o ERROR
			//ModoDeJuego = -1;
		}
		else if( Flag == OvsO_ONLINE ){
			fprintf(stdout, "\n Estoy en OvsO ONLINE \n");
			//Flag = Juego1vs1_ONLINE( &display, &event_queue ); 		// Devuelve SALIR ,VOLVER o ERROR
			//ModoDeJuego = -1;
		}
	}
	DestruirGenerico( &display, &event_queue );
	fprintf(stderr, "\n\t Tira Violación de Segmento después de esto... Tiene sentido? \n");
	return 0;
}
