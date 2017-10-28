#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/AlTodo.h"

int AlDrawTodo( Objeto **Ini, float EsperaIntermedia, float EsperaFinal ){
	Objeto *Act;
	
	Act = *(Ini);
	while(Act != NULL){	
		al_draw_bitmap(Act->Imagen, Act->Pos_x, Act->Pos_y, 0); //dibujamos todo 0 flags
		if(EsperaIntermedia != 0)al_rest(EsperaIntermedia); //esperamos EsperaIntermedia segundos
		Act = Act->Sig;
	}
	al_flip_display(); //mostramos
	
	if(EsperaFinal != 0) al_rest(EsperaFinal); //esperamos EsperaFinal segundos

	return 0;	
}

void CargarSprites( ALLEGRO_BITMAP **VecFrog, const char *CarpetaContenedora ){
	char RutaFinal[50];
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
}

int AlInitTodo( ALLEGRO_TIMER **resting_timer, ALLEGRO_TIMER **frames_timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_BITMAP ***pVecFrog, bool **pkey ){
	
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -5;
	}
	
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -5;
	}
	
	*(resting_timer) = al_create_timer(FROG_RESTING_TIME);
	if(!(*(resting_timer))) {
		fprintf(stderr, "failed to create timer!\n");
		return -5;
	}
	
	*(frames_timer) = al_create_timer(FRAME_RATE);
	if(!(*(frames_timer))) {
		fprintf(stderr, "failed to create timer!\n");
		return -5;
	}
	
	if(!al_init_image_addon()) {
		al_show_native_message_box((*(display)), "Error", "Error", "Failed to initialize image addon!", 
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -5;
	}
	
	*(display) = al_create_display(SCREEN_W, SCREEN_H);
	if(!(*(display))) {
		fprintf(stderr, "failed to create display!\n");
		return -5;
	}
		
	*(event_queue) = al_create_event_queue(); 		//creamos cola de eventos
	if(!(*(event_queue))) {
		fprintf(stderr, "failed to create event_queue!\n");
		return -5;
	} 
	
	/*aaa*/
	fprintf(stderr, "\n Antes de pkey ");
	/*aaa*/
	
	(*pkey) = (bool *) malloc( 4 * sizeof(bool) );
		if( (*pkey) == NULL ) return -5;
	(*pkey)[KEY_UP] = false;
	(*pkey)[KEY_DOWN] = false;
	(*pkey)[KEY_LEFT] = false;
	(*pkey)[KEY_RIGHT] = false;
	
	/*aaa*/
	fprintf(stderr, "\n %d %d %d %d ", (*pkey)[0], (*pkey)[1], (*pkey)[2], (*pkey)[3]);
	/*aaa*/	
	
	/*aaa*/
	fprintf(stderr, "\n Despues de pkey ");
	/*aaa*/	
	
	/* --------------- Cargamos las imágenes de los Sprites para los Saltos de la Rana --------------- */
	
	(*pVecFrog) = (ALLEGRO_BITMAP **) malloc(sizeof( 8 * sizeof(ALLEGRO_BITMAP *) ));
		if( (*pVecFrog) == NULL ){
			fprintf(stderr, "\n No hay memoria para VecFrog ");
			return -5;
		}
	/*aaa*/
	fprintf(stderr, "\n Despues de malloc pVecFrog ");
	/*aaa*/
	
	/*aaa*/
	fprintf(stderr, "\n Vamos a CargarSprites ");
	/*aaa*/
	
	CargarSprites( *(pVecFrog), "Imagenes");

	/*(*pVecFrog)[0] = al_load_bitmap("Imagenes/RanaArriba.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 0 ");
	(*pVecFrog)[1] = al_load_bitmap("Imagenes/RanaSaltoArriba.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 1 ");
	(*pVecFrog)[2] = al_load_bitmap("Imagenes/RanaAbajo.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 2 ");
	(*pVecFrog)[3] = al_load_bitmap("Imagenes/RanaSaltoAbajo.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 3 ");
	(*pVecFrog)[4] = al_load_bitmap("Imagenes/RanaIzquierda.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 4 ");
	(*pVecFrog)[5] = al_load_bitmap("Imagenes/RanaSaltoIzquierda.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 5 ");
	(*pVecFrog)[6] = al_load_bitmap("Imagenes/RanaDerecha.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 6 ");
	(*pVecFrog)[7] = al_load_bitmap("Imagenes/RanaSaltoDerecha.png");
	al_rest(0.5);
	fprintf(stderr, "\n Despues de cargar 7 ");*/
	
	/*aaa*/
	fprintf(stderr, "\n Despues de CargarSprites ");
	/*aaa*/	
	
	al_register_event_source((*(event_queue)), al_get_display_event_source(*(display))); //conectamos eventos de la pantalla 
	al_register_event_source((*(event_queue)), al_get_keyboard_event_source());
	al_register_event_source((*(event_queue)), al_get_timer_event_source(*(resting_timer)));
	al_register_event_source(*(event_queue), al_get_timer_event_source(*(frames_timer)));
	return 0;	
}
				//ALLEGRO_TIMER **resting_timer, ALLEGRO_TIMER **frames_timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_BITMAP ***pVecFrog, bool **pkey
void AlDestroyTodo(ALLEGRO_TIMER **resting_timer, ALLEGRO_TIMER **frames_timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_BITMAP ***pVecFrog, /*PosFrog*/ bool **pkey){
	int aux = 0;
	ALLEGRO_BITMAP **VecFrog = *(pVecFrog);
	
	al_stop_timer(*resting_timer);
	al_stop_timer(*frames_timer);
	
	/*aaa*/
	fprintf(stderr, "\n Claramente hay Seg.Fault acá ");
	/*aaa*/
	if( *VecFrog != NULL ){
		while( aux <= 7 ){
			if (*(VecFrog+aux) == NULL) break;
			al_destroy_bitmap( *(VecFrog+aux) );	
			aux ++;	
			/*aaa*/
			fprintf(stderr, "\n Seg.Fault después del ciclo %d ", aux);
			/*aaa*/
		}	
		free(VecFrog);
	}
	/*aaa*/
	fprintf(stderr, "\n No hay Seg.Fault Hasta al_destroy_timer ");
	/*aaa*/
	al_destroy_timer( *(resting_timer) );
	al_destroy_timer( *(frames_timer) );
	al_destroy_display( *(display) );
	al_destroy_event_queue( *(event_queue) );
	/*aaa*/
	fprintf(stderr, "\n No hay Seg.Fault en AlDestroyTodo ");
	/*aaa*/
}

int IniciarLista( Objeto **pIni, Objeto **pObjetoFrog ){
	FILE *fp;
	Objeto *Act, *Ant;
	char *Nombre, *Numero, *RutaImagen, *DirMov, *Velocidad, *Alto, *Ancho, *Dif_x, *Pos_y;
	
	Nombre = (char *) malloc(10*sizeof(char));
		if(Nombre == NULL) return -5;
	Numero = (char *) malloc(4*sizeof(char));
		if(Numero == NULL) return -5;
	RutaImagen = (char *) malloc(25*sizeof(char));
		if(RutaImagen == NULL) return -5;
	DirMov = (char *) malloc(5*sizeof(char));
		if(DirMov == NULL) return -5;
	Velocidad = (char *) malloc(4*sizeof(char));
		if(Velocidad == NULL) return -5;
	Alto = (char *) malloc(4*sizeof(char));
		if(Alto == NULL) return -5;
	Ancho = (char *) malloc(4*sizeof(char));
		if(Ancho == NULL) return -5;
	Dif_x = (char *) malloc(15*sizeof(char));
		if(Dif_x == NULL) return -5;
	Pos_y = (char *) malloc(15*sizeof(char));
		if(Pos_y == NULL) return -5;
	
	fp = fopen("Archivos/Objetos.txt", "r");
		if(fp == NULL){
			fprintf(stderr, "\n\n\t No se pudo abrir Objetos.txt");
			return -5;		
		}
	
	Act = *pIni;
	fscanf(fp, "%[^\t]", Nombre);
	while( ! strstr(Nombre, "FIN") ){	
		fscanf(fp, "\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", Numero, RutaImagen, DirMov, Velocidad, Alto, Ancho, Dif_x, Pos_y);	
		
		if( Act == *(pIni) ){
			Act = (Objeto *) malloc(sizeof(Objeto));
				if(Act == NULL) return -5;
			*(pIni) = Act;
		}
		else{
			Act = (Objeto *) malloc(sizeof(Objeto));
				if(Act == NULL) return -5;
			Ant->Sig = Act;
		}			
					//Cargamos TODO en Act
		Act->Nombre = (char *) malloc(10*sizeof(char));
			if(Act->Nombre == NULL) return -5;
		strcpy(Act->Nombre, Nombre);
		
		Act->DirMov = (char *) malloc(5*sizeof(char));
			if(Act->Nombre == NULL) return -5;
		strcpy(Act->DirMov, DirMov);
		
		Act->Numero = atoi(Numero);
		
		Act->DirImagen = (char *) malloc(25*sizeof(char));
			if(Ancho == NULL) return -5;
		strcpy(Act->DirImagen, RutaImagen);
		
		if( strstr(Nombre, "Back") ){
			Act->Velocidad = 0;
			Act->Alto = 0;
			Act->Ancho = 0;
			Act->Dif_x = 0;
			Act->Pos_x = 0;
			Act->Pos_y = 0;
		}
		else if( strstr(Nombre, "Frog") && Act->Numero == 1){
			Act->Velocidad = 0;
			Act->Alto = FROG_SIZE;
			Act->Ancho = FROG_SIZE;
			Act->Dif_x = 0;
			Act->Pos_x = SCREEN_W / 2.0 - FROG_SIZE / 2.0;;
			Act->Pos_y = SCREEN_H - (SCREEN_H+UPPER_OFFSET) / ((MAX_BOUNCE_Y*2.0) - 1) - FROG_SIZE / 2.0;;
			
			*(pObjetoFrog) = Act;
		}
		else {
			Act->Velocidad = atof(Velocidad);
			Act->Alto = atof(Alto);
			Act->Ancho = atof(Ancho);
			Act->Pos_y = atof(Pos_y);
			Act->Dif_x = atof(Dif_x);
			if( strstr(DirMov, "Izq") ){
				Act->Pos_x = SCREEN_W + Act->Dif_x;
			}
			if( strstr(DirMov, "Der") ){
				Act->Pos_x = - Act->Ancho - Act->Dif_x;
			}
		}

		Act->Imagen = al_load_bitmap(RutaImagen);
		if(!Act->Imagen) {
			fprintf(stderr, "\n\n\tError al cargar la imagen %s, de %s %s.", RutaImagen, Nombre, Numero);
			return -5;
		}	
					//Paso
		
		Ant = Act;
		Act = NULL;
		fscanf(fp, "%[^\t]", Nombre);
	}
	Ant->Sig = NULL;	
	
	/*aaa*/
	fprintf(stderr, "\n ERROR AL LIBERAR LOS CHAR * de AlTodo.c ?? ");
	/*aaa*/	
	free(Nombre);
	free(Numero);
	free(RutaImagen);
	free(DirMov);
	free(Velocidad);
	free(Alto);
	free(Ancho);
	free(Dif_x);
	free(Pos_y);
	/*aaa*/
	fprintf(stderr, "\t NO ! \n");
	/*aaa*/	
	
	fclose(fp);
	return 0;
}

void LiberarTodo( Objeto **pIni ){
	Objeto *Act, *Ant;
	Act = *(pIni);
	while(Act != NULL){
		al_destroy_bitmap(Act->Imagen);
		Act = Act->Sig;
	}
	Act = *(pIni);
	while(Act != NULL){
		Ant = Act;
		if( Act->Sig != NULL ) Act = Act->Sig;
		
		if( Ant->Nombre != NULL ) free(Ant->Nombre);
		if( Ant->DirImagen != NULL ) free(Ant->DirImagen);
		if( Ant->DirMov != NULL ) free(Ant->DirMov);
		free(Ant);
	}
}
