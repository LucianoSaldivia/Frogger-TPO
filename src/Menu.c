#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Menu.h"
#include "../inc/Dibujos.h"

char Menu( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){
	char Opcion = -10, JuegoElegido = -30;	
		
	while ( Opcion != JuegoElegido ){
		Opcion = MenuPrincipal( p_event_queue );						// Devuelve SALIR, JUGAR, VER_PUNTAJES
		if( Opcion == VER_PUNTAJES ){
			if( MenuPuntajes( p_event_queue ) == SALIR ) Opcion = SALIR;// Devuelve SALIR o VOLVER
		}
		
		else if( Opcion == JUGAR ){
			JuegoElegido = MenuJugar( p_event_queue );					// Devuelve SALIR, VOLVER, OvsC, OvsO_OFFLINE, OvsO_ONLINE 
			if( JuegoElegido != VOLVER ){
				Opcion = JuegoElegido;
			}
		}
		
		if( Opcion == SALIR ) return Opcion;
	}		
	return JuegoElegido;
}

char MenuPrincipal( ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_BITMAP *MenuBack = NULL, *Frog = NULL;
	ALLEGRO_FONT *FuenteTitulo = NULL, *FuenteOpciones = NULL, *FuenteAclaraciones = NULL;
	static int Pos_x = 247, Pos_y = 326;
	char Retornar = -10;
	
	MenuBack = al_load_bitmap( "Imagenes/MenuBack.png" );
	Frog = al_load_bitmap( "Imagenes/RanaDerecha.png" );
	FuenteTitulo = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_TITULO, 0 );
	FuenteOpciones = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES, 0 );
	FuenteAclaraciones = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_CHICA, 0 );
	
	DibujarParaMenu( &MenuBack, &Frog, &FuenteTitulo, &FuenteOpciones, &FuenteAclaraciones, "Principal", Pos_x, Pos_y); 
	
	while( Retornar == -10 ){
		ALLEGRO_EVENT ev;
		al_wait_for_event( *(p_event_queue), &ev );
		
		if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
			Retornar = SALIR;
		}
		
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					if( Pos_y == 326 ) Retornar = JUGAR;
					if( Pos_y == 383 ) Retornar = VER_PUNTAJES;
					if( Pos_y == 440 ) Retornar = SALIR;
					break;
					
				case ALLEGRO_KEY_ESCAPE:
					Retornar = SALIR;
					break;
		
				case ALLEGRO_KEY_UP:
					if( Pos_y == 440 ){
						Pos_y = 383;
						Pos_x = 170;
					}
					else if( Pos_y == 383 ){
						Pos_y = 326;
						Pos_x = 247;
					}
					break;
 
				case ALLEGRO_KEY_DOWN:
					if( Pos_y == 326 ){
						Pos_y = 383;
						Pos_x = 170;
					}
					else if( Pos_y == 383 ){
						Pos_y = 440;
						Pos_x = 250;
					}
					break;
			}
			DibujarParaMenu( &MenuBack, &Frog, &FuenteTitulo, &FuenteOpciones, &FuenteAclaraciones, "Principal", Pos_x, Pos_y); 
		}
	}
	al_destroy_bitmap( MenuBack );
	al_destroy_bitmap( Frog );
	al_destroy_font( FuenteTitulo );
	al_destroy_font( FuenteOpciones );
	al_destroy_font( FuenteAclaraciones );
	
	return Retornar;
}

char MenuJugar( ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_BITMAP *MenuBack = NULL, *Frog = NULL;
	ALLEGRO_FONT *FuenteTitulo = NULL, *FuenteOpciones = NULL, *FuenteAclaraciones = NULL;
	int Pos_x = 239, Pos_y = 326;
	char Retornar = -10;
	bool EnterPresionado = false, FlagSalida = false;
	
	
	MenuBack = al_load_bitmap( "Imagenes/MenuBack.png" );
	Frog = al_load_bitmap( "Imagenes/RanaDerecha.png" );
	FuenteTitulo = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_TITULO , 0 );
	FuenteOpciones = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES , 0 );
	FuenteAclaraciones = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_CHICA , 0 );
	
	DibujarParaMenu( &MenuBack, &Frog, &FuenteTitulo, &FuenteOpciones, &FuenteAclaraciones, "Jugar", Pos_x, Pos_y); 
		
	while( EnterPresionado == false && FlagSalida == false){
		ALLEGRO_EVENT ev;
		al_wait_for_event( *(p_event_queue), &ev );
		
		if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
			FlagSalida = true;		
			Retornar = SALIR;
		}

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					FlagSalida = true;		
					Retornar = SALIR;
					break;
				
				case ALLEGRO_KEY_Q:
					FlagSalida = true;		
					Retornar = VOLVER;
					break;
					
				case ALLEGRO_KEY_ENTER:
					EnterPresionado = true;
					break;
							
				case ALLEGRO_KEY_UP:
					if( Pos_y == 440 ){
						Pos_y = 383;
						Pos_x = 147;
					}
					else if( Pos_y == 383 ){
						Pos_y = 326;
						Pos_x = 239;
					}
					break;
			
				case ALLEGRO_KEY_DOWN:
					if( Pos_y == 326 ){
						Pos_y = 383;
						Pos_x = 147;
					}
					else if( Pos_y == 383 ){
						Pos_y = 440;
						Pos_x = 147;
					}
					break;
			}
		}
		
		DibujarParaMenu( &MenuBack, &Frog, &FuenteTitulo, &FuenteOpciones, &FuenteAclaraciones, "Jugar", Pos_x, Pos_y);
	}
		
	if( EnterPresionado == true && Pos_y == 326 ) Retornar = OvsC;
	if( EnterPresionado == true && Pos_y == 383 ) Retornar = OvsO_OFFLINE;
	if( EnterPresionado == true && Pos_y == 440 ) Retornar = OvsO_ONLINE;
	
	al_destroy_bitmap( MenuBack );
	al_destroy_bitmap( Frog );
	al_destroy_font( FuenteTitulo );
	al_destroy_font( FuenteOpciones );
	al_destroy_font( FuenteAclaraciones );
	
	return Retornar;
}

char MenuPuntajes( ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_BITMAP *MenuBack = NULL, *Frog = NULL;
	ALLEGRO_FONT *FuenteTitulo = NULL, *FuenteOpciones = NULL, *FuenteAclaraciones = NULL;
	bool Volver = false;
	int Pos_y = UPPER_OFFSET + FROG_SIZE + SEPARACION_PUNTAJES - 8;
	char Retornar = -10;
	
	MenuBack = al_load_bitmap( "Imagenes/MenuBack.png" );
	Frog = al_load_bitmap( "Imagenes/RanaArriba.png" );
	FuenteTitulo = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_TITULO , 0 );
	FuenteOpciones = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES , 0 );
	FuenteAclaraciones = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_CHICA , 0 );
	
	DibujarParaMenu( &MenuBack, &Frog, &FuenteTitulo, &FuenteOpciones, &FuenteAclaraciones, "Ver Puntajes", 0, Pos_y);
	
	while( Volver == false ){ 
		ALLEGRO_EVENT ev;
		al_wait_for_event( *(p_event_queue), &ev );
		
		if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
			Retornar = SALIR;
			Volver = true;
		}
		
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {					
				case ALLEGRO_KEY_ESCAPE:
					Volver = true;
					Retornar = SALIR;
					break;		
		
				case ALLEGRO_KEY_Q:
					Volver = true;
					Retornar = VOLVER;
					break;
			}
		}
	}
	al_destroy_bitmap( MenuBack );
	al_destroy_bitmap( Frog );
	al_destroy_font( FuenteTitulo );
	al_destroy_font( FuenteOpciones );
	al_destroy_font( FuenteAclaraciones );
	return Retornar;
}

char MenuPausa( ALLEGRO_DISPLAY **p_display ){
	ALLEGRO_EVENT_QUEUE *Eventos_Pausa = NULL;
	ALLEGRO_BITMAP *MenuPausa = NULL;
	char Retornar = -10;
	
	MenuPausa = al_load_bitmap( "Imagenes/MenuPausa.png" );
	
	Eventos_Pausa = al_create_event_queue(); 		//creamos cola de eventos
	if( ! Eventos_Pausa ) {
		fprintf(stderr, "failed to create event_queue!\n");
		return SALIR;
	}
	
	al_register_event_source( Eventos_Pausa, al_get_display_event_source( *(p_display) ) ); //conectamos eventos de la pantalla 
	al_register_event_source( Eventos_Pausa, al_get_keyboard_event_source() );
	
	al_draw_bitmap( MenuPausa, 0, 00, 0 );
	al_flip_display();		
			
	while( Retornar == -10 ){
		ALLEGRO_EVENT Ev;
		al_wait_for_event( Eventos_Pausa, &Ev );
		
		if( Ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
			Retornar = SALIR;
		}
		
		else if(Ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if( Ev.keyboard.keycode == ALLEGRO_KEY_X ) Retornar = SALIR;																							//SALIR del juego
			else if( Ev.keyboard.keycode == ALLEGRO_KEY_ENTER || Ev.keyboard.keycode == ALLEGRO_KEY_P ) Retornar = CONTINUAR;										//CONTINUAR con el juego		
			else if( Ev.keyboard.keycode == ALLEGRO_KEY_S || Ev.keyboard.keycode == ALLEGRO_KEY_Q || Ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) Retornar = VOLVER;	//VOLVER al menu principal
		}
	}
		
	al_destroy_event_queue( Eventos_Pausa );
	al_destroy_bitmap( MenuPausa );	
	return Retornar;	
}
