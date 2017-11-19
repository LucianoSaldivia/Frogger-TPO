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
#include "../inc/Dibujos.h"
/*   Genericos   */
char InicioGenerico( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){	// Inicializa lo necesario para todos los juegos y menus
	
	if( ! al_init() ){
		fprintf(stderr, "failed to initialize allegro!\n");
		return ERROR;
	}
	
	if( ! al_install_keyboard() ){
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return ERROR;
	}
	
	if( ! al_init_image_addon() ){
		al_show_native_message_box( (*p_display), "Error", "Error", "Failed to initialize image addon!", 
					NULL, ALLEGRO_MESSAGEBOX_ERROR );
		return ERROR;
	}
	
	al_init_font_addon();
	al_init_ttf_addon();
	
	*(p_display) = al_create_display( SCREEN_W, SCREEN_H );
	if( ! (*p_display) ){
		fprintf(stderr, "failed to create display!\n");
		return ERROR;
	}
		
	*(p_event_queue) = al_create_event_queue();
	if( ! (*p_event_queue) ) {
		al_destroy_display( *(p_display) );
		fprintf(stderr, "failed to create event_queue!\n");
		return ERROR;
	}
	
	al_register_event_source( (*p_event_queue), al_get_display_event_source(*p_display) );
	al_register_event_source( (*p_event_queue), al_get_keyboard_event_source() );
	
	return 0;
}

void DestruirGenerico( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){	// Finaliza y destruye todo lo inicializado por InicioGenerico
	al_destroy_display( *(p_display) );
	al_destroy_event_queue( *(p_event_queue) );
}


void TerminarDeAcomodarLista( Objeto **p_Ini ){	// Ajusta las posiciones iniciales de los objetos
	Objeto *Act;
	
	Act = *p_Ini;
	
	while( Act != NULL ){
		if( strstr( Act->DirMov, "Izq" ) != NULL ){
			if( Act->Numero == 1 ) Act->Pos_x = SCREEN_W;
			else Act->Pos_x = Act->Ant->Pos_x + Act->Dif_x;
		}
		if( strstr( Act->DirMov, "Der" ) != NULL ){
			if( Act->Numero == 1 ) Act->Pos_x = 0 - Act->Ancho;
			else Act->Pos_x = Act->Ant->Pos_x - Act->Dif_x;
		}
		Act = Act->Sig;
	}
}

void LiberarMemoria( Objeto **p_Ini ){	// Elimina la lista de objetos, y todo lo que contienen sus nodos
	Objeto *Act, *Ant;
	
	Act = *(p_Ini);
	while(Act != NULL){
		Ant = Act;
		Act = Act->Sig;
		free(Ant->Nombre);
		free(Ant->DirImagen);
		free(Ant->DirMov);
		free(Ant);
	}
}

void InicializarTimers( ALLEGRO_TIMER **p_timer1, ALLEGRO_TIMER **p_timer2 ){	// Inicializa 2 timers
	al_start_timer(*p_timer1);		
	al_start_timer(*p_timer2);	
}

/*   1vsC   */

char Inicializar1vsC( ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer, ALLEGRO_TIMER **p_died_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key, char **p_PosicionesFinales ){	
	// Inicializa lo necesario para 1vsC
	
	*(p_resting_timer) = al_create_timer(FROG_RESTING_TIME);
	if( ! (*p_resting_timer) ) {
		fprintf(stderr, "failed to create timer!\n");
		return ERROR;
	}
	
	*(p_frames_timer) = al_create_timer(FRAME_RATE);
	if( ! (*p_frames_timer) ) {
		al_destroy_timer( *(p_resting_timer) );
		fprintf(stderr, "failed to create timer!\n");
		return ERROR;
	}
	
	*(p_sprites_timer) = al_create_timer(TIEMPO_ENTRE_SPRITES);
	if( ! (*p_sprites_timer) ) {
		al_destroy_timer( *(p_resting_timer) );
		al_destroy_timer( *(p_frames_timer) );
		fprintf(stderr, "failed to create timer!\n");
		return ERROR;
	}
	
	*(p_died_timer) = al_create_timer(TIEMPO_PARA_REVIVIR);
	if( ! (*p_died_timer) ) {
		al_destroy_timer( *(p_resting_timer) );
		al_destroy_timer( *(p_frames_timer) );
		al_destroy_timer( *(p_sprites_timer) );
		fprintf(stderr, "failed to create timer!\n");
		return ERROR;
	}
	
	*(p_VecFrog) = ( ALLEGRO_BITMAP ** ) malloc( 9 * sizeof(ALLEGRO_BITMAP *) );
		if( (*p_VecFrog) == NULL ){
			al_destroy_timer( *(p_resting_timer) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer) );
			al_destroy_timer( *(p_died_timer) );
			fprintf(stderr, "No hay memoria para VecFrog!\n");
			return ERROR;
		}
	CargarSprites1vsC( p_VecFrog, "Imagenes/" );
	
	
	*(p_key) = ( bool * ) malloc( 4 * sizeof(bool) );
		if( (*p_key) == NULL ){
			al_destroy_timer( *(p_resting_timer) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer) );
			al_destroy_timer( *(p_died_timer) );
			free( *(p_VecFrog) );
			fprintf(stderr, "No hay memoria para Key!\n");
			return ERROR;
		}
	CargarKey1vsC( p_key );
	
	*(p_PosicionesFinales) = ( char * ) malloc( 5 * sizeof(char) );
		if( (*p_PosicionesFinales) == NULL ){
			al_destroy_timer( *(p_resting_timer) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer) );
			al_destroy_timer( *(p_died_timer) );
			free( *(p_VecFrog) );
			free( *(p_key) );
			fprintf(stderr, "No hay memoria para Posiciones Finales!\n");
			return ERROR;
		}
	CargarPosicionesFinales1vsC( p_PosicionesFinales );
	
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_resting_timer) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_frames_timer) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_sprites_timer) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_died_timer) );
	
	return CONTINUAR;
}

	void CargarSprites1vsC( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora ){	// Carga las imagenes de todas las posiciones la rana
	char RutaFinal[100];
	ALLEGRO_BITMAP **VecFrog = *(p_VecFrog);
	RutaFinal[0] = '\0';
	
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaArriba.png");
	VecFrog[0] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoArriba.png");
	VecFrog[1] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaAbajo.png");
	VecFrog[2] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoAbajo.png");
	VecFrog[3] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaIzquierda.png");
	VecFrog[4] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoIzquierda.png");
	VecFrog[5] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaDerecha.png");
	VecFrog[6] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoDerecha.png");
	VecFrog[7] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Muerte.png");
	VecFrog[8] = al_load_bitmap(RutaFinal);
}	

	void CargarKey1vsC( bool **p_key ){	// Inicializa los flags de las teclas
	bool *key = *(p_key);
	
	key[KEY_UP] = false;
	key[KEY_DOWN] = false;
	key[KEY_LEFT] = false;
	key[KEY_RIGHT] = false;	
}

	void CargarPosicionesFinales1vsC( char **p_PosicionesFinales ){	// Inicializamos flags para las Posiciones Finales 
	char *PosicionesFinales;
	PosicionesFinales = *(p_PosicionesFinales);
	
	PosicionesFinales[POS_1] = VACIA;
	PosicionesFinales[POS_2] = VACIA;
	PosicionesFinales[POS_3] = VACIA;
	PosicionesFinales[POS_4] = VACIA;
	PosicionesFinales[POS_5] = VACIA;
}

void Finalizar1vsC( ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer, ALLEGRO_TIMER **p_died_timer, ALLEGRO_BITMAP **VecFrog, bool **p_key, char **p_PosicionesFinales ){
	// Finaliza y destruye todo lo inicializado por Inicializar1vsC
	
	int Contador;
	al_destroy_timer( *(p_resting_timer) );
	al_destroy_timer( *(p_frames_timer) );
	al_destroy_timer( *(p_sprites_timer) );
	al_destroy_timer( *(p_died_timer) );
	for( Contador = 0 ; Contador <= 8 ; Contador ++ ){
		al_destroy_bitmap( VecFrog[Contador] );
	}
	free( VecFrog );
	free( *(p_key) );
	free( *(p_PosicionesFinales) );
}

char AlistarObjetos1vsC( Objeto **p_Ini,  Objeto **p_ObjetoFrog, const char *RutaArchivo ){	// Leemos archivo de Objetos para 1vsC y armamos la lista de objetos
	FILE *fp;
	Objeto *New;
	char *Nombre, *Numero, *RutaImagen, *DirMov, *Velocidad, *Alto, *Ancho, *Dif_x;
	
	Nombre = (char *) malloc( 10 * sizeof(char) );
		if( Nombre == NULL ) return ERROR;
	Numero = (char *) malloc( 3 * sizeof(char) );
		if( Numero == NULL ){
			free( Nombre );
			return ERROR;
		}
	RutaImagen = (char *) malloc( 75 * sizeof(char) );
		if( RutaImagen == NULL ){
			free( Nombre );
			free( Numero );
			return ERROR;
		}
	DirMov = (char *) malloc( 4 * sizeof(char) );
		if( DirMov == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			return ERROR;
		}
	
	Velocidad = (char *) malloc( 4 * sizeof(char) );
		if( Velocidad == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			return ERROR;
		}
	Alto = (char *) malloc( 4 * sizeof(char) );
		if( Alto == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			return ERROR;
		}
	Ancho = (char *) malloc( 4 * sizeof(char) );
		if( Ancho == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			free( Alto );
			return ERROR;
		}
	Dif_x = (char *) malloc( 25 * sizeof(char) );
		if( Dif_x == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			free( Alto );
			free( Ancho );
			return ERROR;
		}
		
	fp = fopen( RutaArchivo, "r+" );
		if( fp == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			free( Alto );
			free( Ancho );
			free( Dif_x );
			fprintf( stdout, "\n\n\tERROR AL INTENTAR ABRIR ARCHIVO\n\n");
			return ERROR;
		}
		
	New = *p_Ini;
	fscanf( fp, "%[^\t]", Nombre );
		
	while( strstr(Nombre, "FIN") == NULL ){
		fscanf( fp, "\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", Numero, RutaImagen, DirMov, Velocidad, Alto, Ancho, Dif_x );		
		
		// Lista Vacía
		if( *(p_Ini) == NULL ){
			*(p_Ini) = (Objeto *) malloc( sizeof(Objeto)  );
				if( (*p_Ini) == NULL ){
					fclose( fp );
					free( Nombre );
					free( Numero );
					free( RutaImagen );
					free( DirMov );
					free( Velocidad );
					free( Alto );
					free( Ancho );
					free( Dif_x );
					fclose( fp );
					return ERROR;
				}
			New = *(p_Ini);
			New->Ant = NULL;
		}
		// Lista NO Vacía
		else {
			New->Sig = (Objeto *) malloc( sizeof(Objeto) );
				if( New->Sig == NULL ) {
					fclose( fp );
					free( Nombre );
					free( Numero );
					free( RutaImagen );
					free( DirMov );
					free( Velocidad );
					free( Alto );
					free( Ancho );
					free( Dif_x );
					fclose( fp );
					return ERROR;
				}
			New->Sig->Ant = New;
			New = New->Sig;
		}
		
		if( strstr( RutaArchivo, "1vsC" ) != NULL ){
			if( CargarDatosEnObjeto1vsC( New, Nombre, Numero, RutaImagen, DirMov, Velocidad, Alto, Ancho, Dif_x ) == ERROR ) return ERROR;
		}
		if( strstr(Nombre, "Frog") != NULL/* && atoi(Numero) == 1*/ ) *(p_ObjetoFrog) = New;
		
		fscanf( fp, "%[^\t]\t", Nombre );
	}
	New->Sig = NULL;
	
	TerminarDeAcomodarLista( p_Ini );

	RedibujarDesde( p_Ini );
	al_flip_display();
	fclose( fp );
	free( Nombre );
	free( Numero );
	free( RutaImagen );
	free( DirMov );
	free( Velocidad );
	free( Alto );
	free( Ancho );
	free( Dif_x );
	
	return CONTINUAR;	
}

	char CargarDatosEnObjeto1vsC( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x ){
	// Carga los datos de cada objeto en su correspondiente nodo de la lista de 1vsC
	
	New->Nombre = (char *) malloc( 10 * sizeof(char) );
		if( New->Nombre == NULL ) return ERROR;
	New->DirImagen = (char *) malloc( 75 * sizeof(char) );
		if( New->DirImagen == NULL ){
			free( New->Nombre );
			return ERROR;
		}
	New->DirMov = (char *) malloc( 4 * sizeof(char) );
		if( New->DirMov == NULL ){
			free( New->Nombre );
			free( New->DirImagen );
			return ERROR;
		}
	
	strcpy( New->Nombre, Nombre );
	New->Numero = atoi( Numero );
	strcpy( New->DirImagen, RutaImagen );
	strcpy( New->DirMov, DirMov );
	New->Imagen = al_load_bitmap( New->DirImagen );
		if( New->Imagen == NULL ){
			fprintf(stderr, "\n\n\tError al cargar la imagen %s, de %s.", RutaImagen, Nombre);
			return ERROR;
		}

	if( strstr(New->Nombre, "Frog") != NULL && atoi(Numero) == 1 ){
		New->Velocidad = 0;
		New->Alto = FROG_SIZE;
		New->Ancho = FROG_SIZE;
		New->Dif_x = 0;	
		New->Pos_x = X_INI_FROG;
		New->Pos_y = Y_INI_FROG;
	}
	else if( strstr(New->Nombre, "Back") != NULL ){
		New->Velocidad = 0;
		New->Alto = 0;
		New->Ancho = 0;
		New->Dif_x = 0;
		New->Pos_x = 0;
		New->Pos_y = 0;
	}
	else{
		New->Velocidad = atof( Velocidad );
		New->Alto = atof( Alto );
		New->Ancho = atof( Ancho );
		New->Dif_x = atof( Dif_x );	
		if( strstr( New->Nombre, "Tronco2" ) != NULL ) New->Pos_y = UPPER_OFFSET + BOUNCE_Y + 2;
		if( strstr( New->Nombre, "Tortuga2" ) != NULL ) New->Pos_y = UPPER_OFFSET + 2 * BOUNCE_Y + 2;
		if( strstr( New->Nombre, "Tronco3" ) != NULL ) New->Pos_y = UPPER_OFFSET + 3 * BOUNCE_Y + 2;
		if( strstr( New->Nombre, "Tronco1" ) != NULL ) New->Pos_y = UPPER_OFFSET + 4 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Tortuga3" ) != NULL ) New->Pos_y = UPPER_OFFSET + 5 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto1" ) != NULL ) New->Pos_y = UPPER_OFFSET + 7 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto2" ) != NULL ) New->Pos_y = UPPER_OFFSET + 8 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto3" ) != NULL ) New->Pos_y = UPPER_OFFSET + 9 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto4" ) != NULL ) New->Pos_y = UPPER_OFFSET + 10 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto5" ) != NULL ) New->Pos_y = UPPER_OFFSET + 11 * BOUNCE_Y + 2;
	}
	return CONTINUAR;
}

/*   1vs1   */

char Inicializar1vs1( ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer_1, ALLEGRO_TIMER **p_sprites_timer_2, ALLEGRO_TIMER **p_died_timer_1, ALLEGRO_TIMER **p_died_timer_2, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key, char **p_PosicionesFinales ){	
	// Inicializa lo necesario para 1vs1 ONLINE y OFFLINE
	
	*(p_resting_timer_1) = al_create_timer(FROG_RESTING_TIME);
		if( ! (*p_resting_timer_1) ) {
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_resting_timer_2) = al_create_timer(FROG_RESTING_TIME);
		if( ! (*p_resting_timer_2) ) {
			al_destroy_timer( *(p_resting_timer_1) );
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_frames_timer) = al_create_timer(FRAME_RATE);
		if( ! (*p_frames_timer) ) {
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_sprites_timer_1) = al_create_timer(TIEMPO_ENTRE_SPRITES);
		if( ! (*p_sprites_timer_1) ) {
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_sprites_timer_2) = al_create_timer(TIEMPO_ENTRE_SPRITES);
		if( ! (*p_sprites_timer_2) ) {
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer_1) );
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_died_timer_1) = al_create_timer(TIEMPO_PARA_REVIVIR);
		if( ! (*p_died_timer_1) ) {
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer_1) );
			al_destroy_timer( *(p_sprites_timer_2) );
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_died_timer_2) = al_create_timer(TIEMPO_PARA_REVIVIR);
		if( ! (*p_died_timer_2) ) {
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer_1) );
			al_destroy_timer( *(p_sprites_timer_2) );
			al_destroy_timer( *(p_died_timer_1) );
			fprintf(stderr, "failed to create timer!\n");
			return ERROR;
		}
	
	*(p_VecFrog) = ( ALLEGRO_BITMAP ** ) malloc( 17 * sizeof(ALLEGRO_BITMAP *) );
		if( (*p_VecFrog) == NULL ){
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer_1) );
			al_destroy_timer( *(p_sprites_timer_2) );
			al_destroy_timer( *(p_died_timer_1) );
			al_destroy_timer( *(p_died_timer_2) );
			fprintf(stderr, "No hay memoria para VecFrog!\n");
			return ERROR;
		}
	CargarSprites1vs1( p_VecFrog, "Imagenes/" );
	
	*(p_key) = ( bool * ) malloc( 8 * sizeof(bool) );
		if( (*p_key) == NULL ){
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer_1) );
			al_destroy_timer( *(p_sprites_timer_2) );
			al_destroy_timer( *(p_died_timer_1) );
			al_destroy_timer( *(p_died_timer_2) );
			free( *(p_VecFrog) );
			fprintf(stderr, "No hay memoria para Key!\n");
			return ERROR;
		}
	CargarKey1vs1( p_key );
	
	*(p_PosicionesFinales) = ( char * ) malloc( 5 * sizeof(char) );
		if( (*p_PosicionesFinales) == NULL ){
			al_destroy_timer( *(p_resting_timer_1) );
			al_destroy_timer( *(p_resting_timer_2) );
			al_destroy_timer( *(p_frames_timer) );
			al_destroy_timer( *(p_sprites_timer_1) );
			al_destroy_timer( *(p_sprites_timer_2) );
			al_destroy_timer( *(p_died_timer_1) );
			al_destroy_timer( *(p_died_timer_2) );
			free( *(p_VecFrog) );
			free( *(p_key) );
			fprintf(stderr, "No hay memoria para Posiciones Finales!\n");
			return ERROR;
		}
	CargarPosicionesFinales1vs1( p_PosicionesFinales );
	
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_resting_timer_1) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_resting_timer_2) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_frames_timer) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_sprites_timer_1) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_sprites_timer_2) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_died_timer_1) );
	al_register_event_source( (*p_event_queue), al_get_timer_event_source(*p_died_timer_2) );
	
	return CONTINUAR;
}

	void CargarSprites1vs1( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora ){	// Carga las imagenes de todas las posiciones las 2 ranas
	char RutaFinal[100];
	ALLEGRO_BITMAP **VecFrog = *(p_VecFrog);
	RutaFinal[0] = '\0';
	
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaArriba.png");
	VecFrog[0] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoArriba.png");
	VecFrog[1] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaAbajo.png");
	VecFrog[2] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoAbajo.png");
	VecFrog[3] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaIzquierda.png");
	VecFrog[4] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoIzquierda.png");
	VecFrog[5] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaDerecha.png");
	VecFrog[6] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/RanaSaltoDerecha.png");
	VecFrog[7] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Muerte.png");
	VecFrog[8] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2Arriba.png");
	VecFrog[9] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2SaltoArriba.png");
	VecFrog[10] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2Abajo.png");
	VecFrog[11] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2SaltoAbajo.png");
	VecFrog[12] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2Izquierda.png");
	VecFrog[13] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2SaltoIzquierda.png");
	VecFrog[14] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2Derecha.png");
	VecFrog[15] = al_load_bitmap(RutaFinal);
	strcpy(RutaFinal, CarpetaContenedora);
	strcat(RutaFinal, "/Rana2SaltoDerecha.png");
	VecFrog[16] = al_load_bitmap(RutaFinal);
}	

	void CargarKey1vs1( bool **p_key ){	// Inicializa los flags de las teclas
	bool *key = *(p_key);
	
	key[KEY_UP] = false;
	key[KEY_DOWN] = false;
	key[KEY_LEFT] = false;
	key[KEY_RIGHT] = false;	
	key[KEY_2_UP] = false;
	key[KEY_2_DOWN] = false;
	key[KEY_2_LEFT] = false;
	key[KEY_2_RIGHT] = false;
}

	void CargarPosicionesFinales1vs1( char **p_PosicionesFinales ){
	char *PosicionesFinales;
	PosicionesFinales = *(p_PosicionesFinales);
	
	PosicionesFinales[POS_1] = VACIA;
	PosicionesFinales[POS_2] = VACIA;
	PosicionesFinales[POS_3] = VACIA;
	PosicionesFinales[POS_4] = VACIA;
	PosicionesFinales[POS_5] = VACIA;
}

void Finalizar1vs1( ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer_1, ALLEGRO_TIMER **p_sprites_timer_2, ALLEGRO_TIMER **p_died_timer_1, ALLEGRO_TIMER **p_died_timer_2, ALLEGRO_BITMAP **VecFrog, bool **p_key, char **p_PosicionesFinales ){
	// Finaliza y destruye todo lo inicializado por Inicializar1vs1
	
	int Contador;
	al_destroy_timer( *(p_resting_timer_1) );
	al_destroy_timer( *(p_resting_timer_2) );
	al_destroy_timer( *(p_frames_timer) );
	al_destroy_timer( *(p_sprites_timer_1) );
	al_destroy_timer( *(p_sprites_timer_2) );
	al_destroy_timer( *(p_died_timer_1) );
	al_destroy_timer( *(p_died_timer_2) );
	for( Contador = 0 ; Contador <= 16 ; Contador ++ ){
		al_destroy_bitmap( VecFrog[Contador] );
	}
	free( VecFrog );
	free( *(p_key) );
	free( *(p_PosicionesFinales) );
}

char AlistarObjetos1vs1( Objeto **p_Ini,  Objeto **p_ObjetoFrog_1, Objeto **p_ObjetoFrog_2, const char *RutaArchivo ){ // Leemos archivo de Objetos para 1vs1 y armamos la lista de objetos
	FILE *fp;
	Objeto *New;
	char *Nombre, *Numero, *RutaImagen, *DirMov, *Velocidad, *Alto, *Ancho, *Dif_x;
	
	Nombre = (char *) malloc( 10 * sizeof(char) );
		if( Nombre == NULL ) return ERROR;
	Numero = (char *) malloc( 3 * sizeof(char) );
		if( Numero == NULL ){
			free( Nombre );
			return ERROR;
		}
	RutaImagen = (char *) malloc( 75 * sizeof(char) );
		if( RutaImagen == NULL ){
			free( Nombre );
			free( Numero );
			return ERROR;
		}
	DirMov = (char *) malloc( 4 * sizeof(char) );
		if( DirMov == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			return ERROR;
		}
	
	Velocidad = (char *) malloc( 4 * sizeof(char) );
		if( Velocidad == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			return ERROR;
		}
	Alto = (char *) malloc( 4 * sizeof(char) );
		if( Alto == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			return ERROR;
		}
	Ancho = (char *) malloc( 4 * sizeof(char) );
		if( Ancho == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			free( Alto );
			return ERROR;
		}
	Dif_x = (char *) malloc( 25 * sizeof(char) );
		if( Dif_x == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			free( Alto );
			free( Ancho );
			return ERROR;
		}
		
	fp = fopen( RutaArchivo, "r+" );
		if( fp == NULL ){
			free( Nombre );
			free( Numero );
			free( RutaImagen );
			free( DirMov );
			free( Velocidad );
			free( Alto );
			free( Ancho );
			free( Dif_x );
			fprintf( stdout, "\n\n\tERROR AL INTENTAR ABRIR ARCHIVO\n\n");
			return ERROR;
		}
		
	New = *p_Ini;
	fscanf( fp, "%[^\t]", Nombre );
		
	while( strstr(Nombre, "FIN") == NULL ){
		fscanf( fp, "\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", Numero, RutaImagen, DirMov, Velocidad, Alto, Ancho, Dif_x );		
		
		// Lista Vacía
		if( *(p_Ini) == NULL ){
			*(p_Ini) = (Objeto *) malloc( sizeof(Objeto)  );
				if( (*p_Ini) == NULL ){
					fclose( fp );
					free( Nombre );
					free( Numero );
					free( RutaImagen );
					free( DirMov );
					free( Velocidad );
					free( Alto );
					free( Ancho );
					free( Dif_x );
					fclose( fp );
					return ERROR;
				}
			New = *(p_Ini);
			New->Ant = NULL;
		}
		// Lista NO Vacía
		else {
			New->Sig = (Objeto *) malloc( sizeof(Objeto) );
				if( New->Sig == NULL ) {
					fclose( fp );
					free( Nombre );
					free( Numero );
					free( RutaImagen );
					free( DirMov );
					free( Velocidad );
					free( Alto );
					free( Ancho );
					free( Dif_x );
					fclose( fp );
					return ERROR;
				}
			New->Sig->Ant = New;
			New = New->Sig;
		}
		
		if( strstr( RutaArchivo, "1vs1" ) != NULL ){
			if( CargarDatosEnObjeto1vs1( New, Nombre, Numero, RutaImagen, DirMov, Velocidad, Alto, Ancho, Dif_x ) == ERROR ){
				fclose( fp );
				free( Nombre );
				free( Numero );
				free( RutaImagen );
				free( DirMov );
				free( Velocidad );
				free( Alto );
				free( Ancho );
				free( Dif_x );
				fclose( fp );
				return ERROR;
			}
		}
		if( strstr(Nombre, "Frog_1") != NULL ) *(p_ObjetoFrog_1) = New;
		else if( strstr(Nombre, "Frog_2") != NULL ) *(p_ObjetoFrog_2) = New;
		
		fscanf( fp, "%[^\t]\t", Nombre );
	}
	New->Sig = NULL;
	
	TerminarDeAcomodarLista( p_Ini );

	RedibujarDesde( p_Ini );
	al_flip_display();
	fclose( fp );
	free( Nombre );
	free( Numero );
	free( RutaImagen );
	free( DirMov );
	free( Velocidad );
	free( Alto );
	free( Ancho );
	free( Dif_x );
	
	return CONTINUAR;	
}

	char CargarDatosEnObjeto1vs1( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x ){
	// Carga los datos de cada objeto en su correspondiente nodo de la lista de 1vs1
	
	New->Nombre = (char *) malloc( 10 * sizeof(char) );
		if( New->Nombre == NULL ) return ERROR;
	New->DirImagen = (char *) malloc( 75 * sizeof(char) );
		if( New->DirImagen == NULL ){
			free( New->Nombre );
			return ERROR;
		}
	New->DirMov = (char *) malloc( 4 * sizeof(char) );
		if( New->DirMov == NULL ){
			free( New->Nombre );
			free( New->DirImagen );
			return ERROR;
		}
	
	strcpy( New->Nombre, Nombre );
	New->Numero = atoi( Numero );
	strcpy( New->DirImagen, RutaImagen );
	strcpy( New->DirMov, DirMov );
	New->Imagen = al_load_bitmap( New->DirImagen );
		if( New->Imagen == NULL ){
			fprintf(stderr, "\n\n\tError al cargar la imagen %s, de %s.", RutaImagen, Nombre);
			return ERROR;
		}

	if( strstr(New->Nombre, "Frog") != NULL && atoi(Numero) == 1 ){
		New->Velocidad = 0;
		New->Alto = FROG_SIZE;
		New->Ancho = FROG_SIZE;
		New->Dif_x = 0;
		if( strstr(New->Nombre, "Frog_1") != NULL ) New->Pos_x = X_INI_FROG_1;
		else if( strstr(New->Nombre, "Frog_2") != NULL ) New->Pos_x = X_INI_FROG_2;
		New->Pos_y = Y_INI_FROG;
	}
	else if( strstr(New->Nombre, "Back") != NULL ){
		New->Velocidad = 0;
		New->Alto = 0;
		New->Ancho = 0;
		New->Dif_x = 0;
		New->Pos_x = 0;
		New->Pos_y = 0;
	}
	else{
		New->Velocidad = atof( Velocidad );
		New->Alto = atof( Alto );
		New->Ancho = atof( Ancho );
		New->Dif_x = atof( Dif_x );	
		if( strstr( New->Nombre, "Tronco2" ) != NULL ) New->Pos_y = UPPER_OFFSET + BOUNCE_Y + 2;
		if( strstr( New->Nombre, "Tortuga2" ) != NULL ) New->Pos_y = UPPER_OFFSET + 2 * BOUNCE_Y + 2;
		if( strstr( New->Nombre, "Tronco3" ) != NULL ) New->Pos_y = UPPER_OFFSET + 3 * BOUNCE_Y + 2;
		if( strstr( New->Nombre, "Tronco1" ) != NULL ) New->Pos_y = UPPER_OFFSET + 4 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Tortuga3" ) != NULL ) New->Pos_y = UPPER_OFFSET + 5 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto1" ) != NULL ) New->Pos_y = UPPER_OFFSET + 7 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto2" ) != NULL ) New->Pos_y = UPPER_OFFSET + 8 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto3" ) != NULL ) New->Pos_y = UPPER_OFFSET + 9 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto4" ) != NULL ) New->Pos_y = UPPER_OFFSET + 10 * BOUNCE_Y + 2;
		if( strstr( New->Nombre,"Auto5" ) != NULL ) New->Pos_y = UPPER_OFFSET + 11 * BOUNCE_Y + 2;
	}
	return CONTINUAR;
}



