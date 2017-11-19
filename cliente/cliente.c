#include <string.h>
#include <stdio.h>
#include <allegro5/allegro.h>
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "cliente.h"

int main(int argc, char **argv)
{
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
	struct sockaddr_in serv_addr;
	struct hostent *server;
	Teclas_2 tmp;
	int puerto;
	
	
	tmp.T_arriba = false;
	tmp.T_abajo = false;
	tmp.T_izquierda = false;
	tmp.T_derecha = false;
	/*************************
	* Inicializacion Server TCP
	*/
	if (argc < 2) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
		error("ERROR opening socket");
		server = gethostbyname(argv[1]);
		if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	memset((void *) &serv_addr, '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
	puerto = atoi(argv[2]);
	serv_addr.sin_port = htons(puerto);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	error("ERROR connecting");
	/*************************
	* Inicialiación y configuración Allegro
	*/
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
	
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
	 
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	 
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();	 
	/************************
	* Listos para empezar el juego!
	*/

	while(!doexit){
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
	 
		HuboEventos = false;

		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			 break;
		} 
		
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
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
		
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
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
			send(sockfd, &tmp, sizeof(tmp), MSG_DONTWAIT);
		}			
	}
	
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	close(sockfd);
	
	return 0;
}
