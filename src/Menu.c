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
	char Flag = ERROR;
	
	while ( Flag != OvsC && Flag != OvsO_OFFLINE && Flag != OvsO_ONLINE ){
		Flag = MenuPrincipal( p_event_queue );							// Devuelve SALIR, JUGAR, VER_PUNTAJES
		if( Flag == JUGAR ){
			Flag = MenuJugar( p_event_queue );							// Devuelve SALIR, VOLVER, OvsC, OvsO_OFFLINE, OvsO_ONLINE 
			if( Flag == SALIR ) break;
		}
		else if( Flag == VER_PUNTAJES ){
			Flag = MenuPuntajes( p_event_queue );						// Devuelve SALIR o VOLVER
			if( Flag == SALIR ) break;
		}
		else if( Flag == SALIR ) break;
	}
	return Flag;
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
			switch( ev.keyboard.keycode ) {					
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
	
	MenuPausa = al_load_bitmap( "Imagenes/MenuPausa1.png" );
	
	Eventos_Pausa = al_create_event_queue(); 		//creamos cola de eventos
	if( ! Eventos_Pausa ) {
		fprintf(stderr, "failed to create event_queue!\n");
		return SALIR;
	}
	
	al_register_event_source( Eventos_Pausa, al_get_display_event_source( *(p_display) ) ); //conectamos eventos de la pantalla 
	al_register_event_source( Eventos_Pausa, al_get_keyboard_event_source() );
	
	al_draw_bitmap( MenuPausa, 0, 0, 0 );
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

char MenuNuevoPuntaje( Objeto **p_Ini, ALLEGRO_DISPLAY **p_display, int *p_Puntos, const char *Titulo ){	
	ALLEGRO_EVENT_QUEUE *Eventos_Nuevo_Puntaje;
	ALLEGRO_FONT *Fuente = NULL;
	ALLEGRO_BITMAP *MenuFinJuego = NULL;
	int Contador = 0;
	bool Mayus = false;
	char *Aux1, *Aux2, *Nombre, Retornar = -10;	
	
	Aux1 = ( char *) malloc( 100 * sizeof( char ) );
		if( Aux1 == NULL ) Retornar = ERROR;
	Aux2 = ( char *) malloc( 100 * sizeof( char ) );
		if( Aux2 == NULL ){
			free( Aux1 );
			return ERROR;
		}
	Nombre = ( char *) malloc( 100 * sizeof( char ) );
		if( Nombre == NULL ){
			free( Aux1 );
			free( Aux2 );
			return ERROR;
		}
	Eventos_Nuevo_Puntaje = al_create_event_queue(); 		//creamos cola de eventos
		if( ! Eventos_Nuevo_Puntaje ) {
			free( Aux1 );
			free( Aux2 );
			free( Nombre );
			return ERROR;
		}
	memset( Nombre, '\0', 100 * sizeof( char ) );
	
	al_register_event_source( Eventos_Nuevo_Puntaje, al_get_display_event_source( *(p_display) ) ); //conectamos eventos de la pantalla 
	al_register_event_source( Eventos_Nuevo_Puntaje, al_get_keyboard_event_source() );
	
	RedibujarDesde( p_Ini );
	MenuFinJuego = al_load_bitmap( "Imagenes/MenuFinJuego_ConNombre.png" );
		if( ! MenuFinJuego ) {
			free( Aux1 );
			free( Aux2 );
			free( Nombre );
			al_destroy_event_queue( Eventos_Nuevo_Puntaje );
			return ERROR;
		}
	al_draw_bitmap( MenuFinJuego, 0, 0, 0 );
		
	Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES, 0 );
	al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), 295, ALLEGRO_ALIGN_CENTRE, Titulo );
	
	Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_PUNTOS, 0 );
	sprintf( Aux1, "%d", ( *p_Puntos ) );
	strcpy( Aux2, " Tu puntaje final: " );
	strcat( Aux2, Aux1 );
	al_draw_text( Fuente, al_map_rgb( 0, 0, 0 ), ( SCREEN_W / 2 ), 0, ALLEGRO_ALIGN_CENTRE, Aux2 );
	
	al_flip_display();
	
	while( Retornar != CONTINUAR && Retornar != SALIR ){
		ALLEGRO_EVENT ev;
		al_wait_for_event( Eventos_Nuevo_Puntaje, &ev);
		
		if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
			Retornar = SALIR;
		}
		
		else if( ev.type == ALLEGRO_EVENT_KEY_DOWN ){
			switch ( ev.keyboard.keycode ){
				case ALLEGRO_KEY_A:
					if( Mayus == true )Nombre[Contador] = 'A';
					else if( Mayus == false ) Nombre[Contador] = 'a';
					Contador ++;
					break;
				case ALLEGRO_KEY_B:
					if( Mayus == true )Nombre[Contador] = 'B';
					else if( Mayus == false ) Nombre[Contador] = 'b';
					Contador ++;
					break;
				case ALLEGRO_KEY_C:
					if( Mayus == true )Nombre[Contador] = 'C';
					else if( Mayus == false ) Nombre[Contador] = 'c';
					Contador ++;
					break;
				case ALLEGRO_KEY_D:
					if( Mayus == true )Nombre[Contador] = 'D';
					else if( Mayus == false ) Nombre[Contador] = 'd';
					Contador ++;
					break;
				case ALLEGRO_KEY_E:
					if( Mayus == true )Nombre[Contador] = 'E';
					else if( Mayus == false ) Nombre[Contador] = 'e';
					Contador ++;
					break;
				case ALLEGRO_KEY_F:
					if( Mayus == true )Nombre[Contador] = 'F';
					else if( Mayus == false ) Nombre[Contador] = 'f';
					Contador ++;
					break;
				case ALLEGRO_KEY_G:
					if( Mayus == true )Nombre[Contador] = 'G';
					else if( Mayus == false ) Nombre[Contador] = 'g';
					Contador ++;
					break;
				case ALLEGRO_KEY_H:
					if( Mayus == true )Nombre[Contador] = 'H';
					else if( Mayus == false ) Nombre[Contador] = 'h';
					Contador ++;
					break;
				case ALLEGRO_KEY_I:
					if( Mayus == true )Nombre[Contador] = 'I';
					else if( Mayus == false ) Nombre[Contador] = 'i';
					Contador ++;
					break;
				case ALLEGRO_KEY_J:
					if( Mayus == true )Nombre[Contador] = 'J';
					else if( Mayus == false ) Nombre[Contador] = 'j';
					Contador ++;
					break;
				case ALLEGRO_KEY_K:
					if( Mayus == true )Nombre[Contador] = 'K';
					else if( Mayus == false ) Nombre[Contador] = 'k';
					Contador ++;
					break;
				case ALLEGRO_KEY_L:
					if( Mayus == true )Nombre[Contador] = 'L';
					else if( Mayus == false ) Nombre[Contador] = 'l';
					Contador ++;
					break;
				case ALLEGRO_KEY_M:
					if( Mayus == true )Nombre[Contador] = 'M';
					else if( Mayus == false ) Nombre[Contador] = 'm';
					Contador ++;
					break;
				case ALLEGRO_KEY_N:
					if( Mayus == true )Nombre[Contador] = 'N';
					else if( Mayus == false ) Nombre[Contador] = 'n';
					Contador ++;
					break;
				case ALLEGRO_KEY_O:
					if( Mayus == true )Nombre[Contador] = 'O';
					else if( Mayus == false ) Nombre[Contador] = 'o';
					Contador ++;
					break;
				case ALLEGRO_KEY_P:
					if( Mayus == true )Nombre[Contador] = 'P';
					else if( Mayus == false ) Nombre[Contador] = 'p';
					Contador ++;
					break;
				case ALLEGRO_KEY_Q:
					if( Mayus == true )Nombre[Contador] = 'Q';
					else if( Mayus == false ) Nombre[Contador] = 'q';
					Contador ++;
					break;
				case ALLEGRO_KEY_R:
					if( Mayus == true )Nombre[Contador] = 'R';
					else if( Mayus == false ) Nombre[Contador] = 'r';
					Contador ++;
					break;
				case ALLEGRO_KEY_S:
					if( Mayus == true )Nombre[Contador] = 'S';
					else if( Mayus == false ) Nombre[Contador] = 's';
					Contador ++;
					break;
				case ALLEGRO_KEY_T:
					if( Mayus == true )Nombre[Contador] = 'T';
					else if( Mayus == false ) Nombre[Contador] = 't';
					Contador ++;
					break;
				case ALLEGRO_KEY_U:
					if( Mayus == true )Nombre[Contador] = 'U';
					else if( Mayus == false ) Nombre[Contador] = 'u';
					Contador ++;
					break;
				case ALLEGRO_KEY_V:
					if( Mayus == true )Nombre[Contador] = 'V';
					else if( Mayus == false ) Nombre[Contador] = 'v';
					Contador ++;
					break;
				case ALLEGRO_KEY_W:
					if( Mayus == true )Nombre[Contador] = 'W';
					else if( Mayus == false ) Nombre[Contador] = 'w';
					Contador ++;
					break;
				case ALLEGRO_KEY_X:
					if( Mayus == true )Nombre[Contador] = 'X';
					else if( Mayus == false ) Nombre[Contador] = 'x';
					Contador ++;
					break;
				case ALLEGRO_KEY_Y:
					if( Mayus == true )Nombre[Contador] = 'Y';
					else if( Mayus == false ) Nombre[Contador] = 'y';
					Contador ++;
					break;
				case ALLEGRO_KEY_Z:
					if( Mayus == true )Nombre[Contador] = 'Z';
					else if( Mayus == false ) Nombre[Contador] = 'z';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_0:
				case ALLEGRO_KEY_0:
					Nombre[Contador] = '0';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_1:
				case ALLEGRO_KEY_1:
					Nombre[Contador] = '1';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_2:
				case ALLEGRO_KEY_2:
					Nombre[Contador] = '2';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_3:
				case ALLEGRO_KEY_3:
					Nombre[Contador] = '3';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_4:
				case ALLEGRO_KEY_4:
					Nombre[Contador] = '4';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_5:
				case ALLEGRO_KEY_5:
					Nombre[Contador] = '5';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_6:
				case ALLEGRO_KEY_6:
					Nombre[Contador] = '6';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_7:
				case ALLEGRO_KEY_7:
					Nombre[Contador] = '7';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_8:
				case ALLEGRO_KEY_8:
					Nombre[Contador] = '8';
					Contador ++;
					break;
				case ALLEGRO_KEY_PAD_9:
				case ALLEGRO_KEY_9:
					Nombre[Contador] = '9';
					Contador ++;
					break;
				case ALLEGRO_KEY_SPACE:
					Nombre[Contador] = ' ';
					Contador ++;
					break;
				case ALLEGRO_KEY_ENTER:
					Retornar = CONTINUAR;
					break;
				case ALLEGRO_KEY_BACKSPACE:
					if( Contador >= 2 ){
						Contador --;
						Nombre[Contador] = '\0';
					}
					else{
						Contador = 0;
						Nombre[Contador] = '\0';
					}
					break;
				case ALLEGRO_KEY_ESCAPE:
					Retornar = SALIR;
					break;	
				case ALLEGRO_KEY_LSHIFT:
					Mayus = true;
					break;
				case ALLEGRO_KEY_RSHIFT:
					Mayus = true;
					break;	
			}
		}
		else if( ev.type == ALLEGRO_EVENT_KEY_UP ){
			switch( ev.keyboard.keycode ){
				case ALLEGRO_KEY_CAPSLOCK:
					if( Mayus == true ) Mayus = false;
					else if( Mayus == false ) Mayus = true;
					break;
				case ALLEGRO_KEY_LSHIFT:
				case ALLEGRO_KEY_RSHIFT:
					Mayus = false;
					break;
			}
		}
		RedibujarDesde( p_Ini );
		al_draw_bitmap( MenuFinJuego, 0, 0, 0 );
		
		Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_OPCIONES, 0 );
		al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), 295, ALLEGRO_ALIGN_CENTRE, Titulo );
		
		Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_PUNTOS, 0 );
		al_draw_text( Fuente, al_map_rgb( 0, 0, 0 ), ( SCREEN_W / 2 ), 0, ALLEGRO_ALIGN_CENTRE, Aux2 );
		
		Fuente = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ( ALTURA_LETRA_OPCIONES / 2 ) , 0 );
		al_draw_text( Fuente, al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), ( 350 + ALTURA_LETRA_OPCIONES ) , ALLEGRO_ALIGN_CENTRE, Nombre );
		
		al_flip_display();
	}
	
	if( GuardarOrdenadoEnArchivo( Nombre, p_Puntos, "Archivos/Puntajes.txt" ) == ERROR ) Retornar = ERROR;
	
	free( Aux1 );
	free( Aux2 );
	free( Nombre );
	al_destroy_event_queue( Eventos_Nuevo_Puntaje );
	al_destroy_bitmap( MenuFinJuego );
	al_destroy_font( Fuente );
	return Retornar;
}

char GuardarOrdenadoEnArchivo( char *NewNombre, int *p_Puntos, const char *RutaArchivo ){
	Puntaje *Ini = NULL, *Act = NULL, *Ant = NULL, *New = NULL;
	FILE *fp;
	char Retornar, *ActNombre, Aux[50];
	int ActPuntos, NewPuntos = ( *(p_Puntos) );
	
	ActNombre = ( char * ) malloc( 100 * sizeof( char ) ); 
		if( ActNombre == NULL ) {
			Retornar = ERROR;
		}
	New = ( Puntaje * ) malloc( sizeof( Puntaje ) );											/* Armamos Nuestro struct Puntaje NUEVO */
		if( New == NULL ) {
			Retornar = ERROR;
		}
	New->Nombre = ( char * ) malloc( 100 * sizeof( char ) );
		if( New->Nombre == NULL ) {
			Retornar = ERROR;
		}
	strcpy( New->Nombre, NewNombre );
	New->Puntos = NewPuntos;
	New->Sig = NULL;
	
	fp = fopen( RutaArchivo, "r" );
	
	while( fscanf( fp, "%[^\t]\t%[^\n]\n", ActNombre, Aux ) != EOF && Retornar != ERROR ){	/* Armamos de la lista de todos los puntajes guardados */
		ActPuntos = atoi( Aux );
		if( Ini == NULL ){
			Ini = ( Puntaje * ) malloc( sizeof( Puntaje ) );
				if( Ini == NULL ) {
					Retornar = ERROR;
					break;
				}
			Act = Ini;
			Act->Nombre = ( char * ) malloc( 100 * sizeof( char ) );
				if( New->Nombre == NULL ) {
					Retornar = ERROR;
				}
			strcpy( Act->Nombre, ActNombre );
			Act->Puntos = ActPuntos;
			Act->Sig = NULL;
		}
		else{
			Act->Sig = ( Puntaje * ) malloc( sizeof( Puntaje ) );
				if( Act == NULL ) {
					Retornar = ERROR;
					break;
				}
			Act = Act->Sig;
			Act->Nombre = ( char * ) malloc( 100 * sizeof( char ) );
				if( New->Nombre == NULL ) {
					Retornar = ERROR;
				}
			strcpy( Act->Nombre, ActNombre );
			Act->Puntos = ActPuntos;
			Act->Sig = NULL;
		}
	}
	fclose( fp );
	
	Act = Ini;																				/* Ponemos Nuestro Struct Puntaje NUEVO en la lista de forma ordenada */
	while( Act != NULL ){
		if( New->Puntos >= Ini->Puntos ){
			Ini = New;
			New->Sig = Act;
			break;
		}
		else if( New->Puntos >= Act->Puntos ){
			New->Sig = Act;
			Ant->Sig = New;
			break;
		}
		else if( Act->Sig == NULL ){
			Act->Sig = New;
			New->Sig = NULL;
		}
		Ant = Act;
		Act = Act->Sig;
	}
	
	fp = fopen( RutaArchivo, "w" );															/* Escribimos toda la lista completa en el archivo de nuevo */
	
	Act = Ini;
	while( Act != NULL ){
		fprintf( fp, "%s\t%d\n", Act->Nombre, Act->Puntos);
		Act = Act->Sig;
	}
	
	LiberarMemoriaDePuntos( Ini );
	fclose( fp );	
	return Retornar;
}

void LiberarMemoriaDePuntos( Puntaje *Ini ){
	Puntaje *Act, *Ant = NULL;
	
	Act = Ini;
	while( Act != NULL ){
		if( Ant != NULL ) free( Ant );
		free( Act->Nombre );
		Ant = Act;
		Act = Act->Sig;
	}
}

