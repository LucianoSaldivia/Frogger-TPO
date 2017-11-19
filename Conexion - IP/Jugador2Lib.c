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

char InicializarJugador2( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return ERROR;
	}
	 
	if( ! al_install_keyboard() ) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return ERROR;
	}
	
	*p_display = al_create_display( SCREEN_W, SCREEN_H );
	if( ! *p_display ) {
		fprintf(stderr, "failed to create display!\n");
		return ERROR;
	}
	
	( *p_event_queue ) = al_create_event_queue();
	if( ! *p_event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display( *p_display );
		return ERROR;
	}
	al_register_event_source( *p_event_queue, al_get_display_event_source( *p_display ) );
	al_register_event_source( *p_event_queue, al_get_keyboard_event_source() );
	
	return CONTINUAR;
}

void error(const char *msg){
    perror(msg);
    exit(0);
}

char MenuPedir( ALLEGRO_DISPLAY **p_display, char *Output, const char *Titulo ){
	ALLEGRO_EVENT_QUEUE *Eventos;
	ALLEGRO_FONT *Fuente = NULL;
	ALLEGRO_BITMAP *MenuFinJuego = NULL;
	int Contador = 0;
	char Retornar = -10;
	
	if( ! al_init_image_addon() ){
		al_show_native_message_box( (*p_display), "Error", "Error", "Failed to initialize image addon!", 
					NULL, ALLEGRO_MESSAGEBOX_ERROR );
		return ERROR;
	}
	al_init_font_addon();
	al_init_ttf_addon();
	
	Eventos = al_create_event_queue(); 		//creamos cola de eventos
		if( ! Eventos ) return ERROR;
	memset( Output, '\0', strlen( Output ) * sizeof( char ) );
	MenuFinJuego = al_load_bitmap( "Imagenes/MenuBack.png" );
		if( ! MenuFinJuego ) {
			al_destroy_event_queue( Eventos );
			return ERROR;
		}
	
	al_register_event_source( Eventos, al_get_display_event_source( *(p_display) ) ); //conectamos eventos de la pantalla 
	al_register_event_source( Eventos, al_get_keyboard_event_source() );
	
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	al_draw_bitmap( MenuFinJuego, 0, 0, 0 );
		
	Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES, 0 );
	al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), 295, ALLEGRO_ALIGN_CENTRE, Titulo );
	
	Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ( ALTURA_LETRA_OPCIONES / 2 ) , 0 );
	al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), ( 350 + ALTURA_LETRA_OPCIONES ) , ALLEGRO_ALIGN_CENTRE, Output );
	
	al_flip_display();
	
	while( Retornar != CONTINUAR && Retornar != SALIR ){
		ALLEGRO_EVENT ev;
		al_wait_for_event( Eventos, &ev );
		
		if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
			Retornar = SALIR;
			break;
		}
		
		else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
			Retornar = SALIR;
			break;
		}
		
		else if( ev.type == ALLEGRO_EVENT_KEY_DOWN ){
			switch ( ev.keyboard.keycode ){
				case ALLEGRO_KEY_FULLSTOP:
					Output[Contador] = '.';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_0:
				case ALLEGRO_KEY_0:
					Output[Contador] = '0';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_1:
				case ALLEGRO_KEY_1:
					Output[Contador] = '1';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_2:
				case ALLEGRO_KEY_2:
					Output[Contador] = '2';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_3:
				case ALLEGRO_KEY_3:
					Output[Contador] = '3';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_4:
				case ALLEGRO_KEY_4:
					Output[Contador] = '4';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_5:
				case ALLEGRO_KEY_5:
					Output[Contador] = '5';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_6:
				case ALLEGRO_KEY_6:
					Output[Contador] = '6';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_7:
				case ALLEGRO_KEY_7:
					Output[Contador] = '7';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_8:
				case ALLEGRO_KEY_8:
					Output[Contador] = '8';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_9:
				case ALLEGRO_KEY_9:
					Output[Contador] = '9';
					Output[Contador + 1] = '\0';
					Contador ++;
					break;
				case ALLEGRO_KEY_ENTER:
					Retornar = CONTINUAR;
					break;
				case ALLEGRO_KEY_BACKSPACE:
					if( Contador >= 2 ){
						Contador --;
						Output[Contador] = '\0';
					}
					else{
						Contador = 0;
						Output[Contador] = '\0';
					}
					break;
			}
		}
		
		if( Retornar != CONTINUAR && Retornar != SALIR ){
			al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
			al_draw_bitmap( MenuFinJuego, 0, 0, 0 );
			
			Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES, 0 );
			al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), 295, ALLEGRO_ALIGN_CENTRE, Titulo );
			
			Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ( ALTURA_LETRA_OPCIONES / 2 ) , 0 );
			al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), ( 350 + ALTURA_LETRA_OPCIONES ) , ALLEGRO_ALIGN_CENTRE, Output );
			
			al_flip_display();
		}
	}
	
	al_destroy_event_queue( Eventos );
	al_destroy_bitmap( MenuFinJuego );
	al_destroy_font( Fuente );
	return Retornar;
}

