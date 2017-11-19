#include <string.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Jugador2Lib.h"

int main(int argc, char **argv){
    /*************************
     * Variables de Allegro
     */

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	bool key[5] = { false, false, false, false, false };
	bool doexit = false;
	bool HuboEventos = false;
	
	/*************************
	* Variables de Server TCP
	*/
	int sockfd;
	char IPServer[20], StringPuerto[6];
	struct sockaddr_in serv_addr;
	struct hostent *server;
	Teclas_2 tmp;
	int puerto;
	
	/*************************
	* Inicialiación y configuración Allegro
	*/
	
	if ( InicializarJugador2( &display, &event_queue ) == ERROR ) return ERROR;
	MenuPedir( &display, IPServer, "IP Jugador 1:" );
	MenuPedir( &display, StringPuerto, "Puerto:" );
	
	/*************************
	* Inicializacion Server TCP
	*/
	
	sockfd = socket( AF_INET, SOCK_STREAM, 0 );
		if ( sockfd < 0 ) error("ERROR Abriendo socket");
	server = gethostbyname( IPServer );
		if ( server == NULL ) {
		fprintf( stderr,"ERROR, el ServerIP ingresado no existe\n" );
		exit( 0 );
		}
	memset( (void *) &serv_addr, '\0', sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	puerto = atoi( StringPuerto );
	serv_addr.sin_port = htons( puerto );
	if ( connect( sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr) ) < 0 ) error( "ERROR Conectando" );
	
	/************************
	* Listos para empezar el juego!
	*/

	tmp.T_arriba = false;
	tmp.T_abajo = false;
	tmp.T_izquierda = false;
	tmp.T_derecha = false;
	
	while(!doexit){
		
		ALLEGRO_EVENT ev;
		al_wait_for_event( event_queue, &ev );
	 
		HuboEventos = false;

		if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
			 break;
		} 
		
		else if( ev.type == ALLEGRO_EVENT_KEY_DOWN ) {
			switch( ev.keyboard.keycode ) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					HuboEventos = true;
					break; 
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					HuboEventos = true;
					break; 
				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = true;
					HuboEventos = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					HuboEventos = true;
					break;
				case ALLEGRO_KEY_P:
					key[PAUSA_AUX] = true;
					HuboEventos = true;
					break; 
			}
		}
		
		else if( ev.type == ALLEGRO_EVENT_KEY_UP ) {
			switch( ev.keyboard.keycode ) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					HuboEventos = true;
					break; 
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					HuboEventos = true;
					break; 
				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = false;
					HuboEventos = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					HuboEventos = true;
					break;
				case ALLEGRO_KEY_P:
					key[PAUSA_AUX] = false;
					HuboEventos = true;
					break; 
			}
		}
		
		if( HuboEventos ){
			tmp.T_arriba = key[KEY_UP];
			tmp.T_abajo = key[KEY_DOWN];
			tmp.T_izquierda = key[KEY_LEFT];
			tmp.T_derecha = key[KEY_RIGHT];
			tmp.T_pausa = key[PAUSA_AUX];
			send( sockfd, &tmp, sizeof( tmp ), MSG_DONTWAIT );
		}			
	}
	
	al_destroy_display( display );
	al_destroy_event_queue( event_queue );
	
	close( sockfd );
	
	return 0;
}

