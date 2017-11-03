#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/CreadorDeArchivos.h"
#include "../inc/Juegos.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/MovimientoAmbiente.h"
#include "../inc/Menu.h"
	
/* AL SALIR DEL MENU DE PAUSA; DESTRUIR TODO LO QUE SE ESTABA USANDO EXCEPTO LO GENERICO */
	
	
int main(int argc, char *argv[]){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	char Flag = -10, ModoDeJuego = -10;
	/*ALLEGRO_TIMER *resting_timer = NULL, *frames_timer;
	ALLEGRO_BITMAP **VecFrog = NULL;
	Objeto *Ini = NULL, *ObjetoFrog = NULL;
	bool *key, doexit = false; //Flags de teclas apretadas y de salida*/
	
	
	/*aaaaa
	Objeto *Act;
	aaaaa*/
	
	if( InicioGenerico( &display, &event_queue ) == ERROR){
		DestruirGenerico( &display, &event_queue );
		return ERROR;		
	}
	
	ModoDeJuego = Menu( &display, &event_queue );
	
	while( ModoDeJuego != SALIR ){
		if( ModoDeJuego == SALIR ) break;
		
		if( ModoDeJuego == OvsC ){
			fprintf(stdout, "\n Estoy en OvsC \n");
			Flag = Juego1vsC( &display, &event_queue ); // Devuelve SALIR o VOLVER
			
		}
		else if( ModoDeJuego == OvsO_OFFLINE ){
			fprintf(stdout, "\n Estoy en OvsO OFFLINE \n");
			//Flag = Juego1vs1_OFFLINE( &display, &event_queue ); //if( pausa->salir ) => return		
			//ModoDeJuego = -1;
		}
		else if( ModoDeJuego == OvsO_ONLINE ){
			fprintf(stdout, "\n Estoy en OvsO ONLINE \n");
			//Flag = Juego1vs1_ONLINE( &display, &event_queue ); //if( pausa->salir ) => return
			//ModoDeJuego = -1;
		}
		
		if( Flag == SALIR || Flag == ERROR ) break;		/*		Antes de return SALIR, destruir lo especifico del juego		*/
		
		ModoDeJuego = Menu( &display, &event_queue );
	}
	
	DestruirGenerico( &display, &event_queue );
	return 0;
}
