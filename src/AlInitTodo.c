#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/AlInitTodo.h"

int AlDrawTodo(Objeto **Ini, float EsperaIntermedia, float EsperaFinal){
	Objeto *Act;
	
	Act = *(Ini);
	while(Act != NULL){
	
		al_draw_bitmap(Act->Imagen, Act->Pos_x, Act->Pos_y, 0); //dibujamos todo 0 flags
		if(EsperaIntermedia != 0)al_rest(EsperaIntermedia); //esperamos EsperaIntermedia segundos
		Act = Act->Sig;
	}
	al_flip_display(); //mostramos
	
	if(EsperaFinal != 0)al_rest(EsperaFinal); //esperamos EsperaFinal segundos

	return 0;	
}

int AlInitTodo(ALLEGRO_TIMER **resting_timer, ALLEGRO_TIMER **refresh_timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, Objeto **Ini){
	FILE *fp;
	Objeto *Act, *Ant;
	char *Nombre, *Numero, *RutaImagen, *Velocidad, *Alto, *Ancho;
	float Pos_y;
	
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
	
	*(refresh_timer) = al_create_timer(TiempoEntreFraps);
	if(!(*(refresh_timer))) {
		fprintf(stderr, "failed to create timer!\n");
		al_destroy_timer(*(resting_timer));
		return -5;
	}
	
	if(!al_init_image_addon()) {
		al_show_native_message_box((*(display)), "Error", "Error", "Failed to initialize image addon!", 
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_timer(*(resting_timer));
		al_destroy_timer(*(refresh_timer));
		return -5;
	}
	
	*(display) = al_create_display(SCREEN_W, SCREEN_H);
	if(!(*(display))) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(*(resting_timer));
		al_destroy_timer(*(refresh_timer));
		return -5;
	}
		
	*(event_queue) = al_create_event_queue(); 		//creamos cola de eventos
	if(!(*(event_queue))) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(*(display));
		al_destroy_timer(*(resting_timer));
		al_destroy_timer(*(refresh_timer));
		return -5;
	}
	
	/* ---------------- Inicializamos todos los objetos ---------------- */
	Act = *Ini;
	
	Nombre = (char *) malloc(50*sizeof(char));
		if(Nombre == NULL) return -5;
	Numero = (char *) malloc(4*sizeof(char));
		if(Numero == NULL) return -5;
	RutaImagen = (char *) malloc(100*sizeof(char));
		if(RutaImagen == NULL) return -5;
	Velocidad = (char *) malloc(4*sizeof(char));
		if(Velocidad == NULL) return -5;
	Alto = (char *) malloc(4*sizeof(char));
		if(Alto == NULL) return -5;
	Ancho = (char *) malloc(4*sizeof(char));
		if(Ancho == NULL) return -5;
	
	fp = fopen("Archivos/Objetos.txt", "r");
	if(fp == NULL){
		fprintf(stderr, "\nNo se pudo abrir Objetos.txt");
		return -5;		
	}
	fscanf(fp, "%[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %f", Nombre, Numero, RutaImagen, Velocidad, Alto, Ancho, &Pos_y);
	while( ! strstr(Nombre, "FIN") ){
		if( Act == *(Ini) ){
			Act = (Objeto *) malloc(sizeof(Objeto));
				if(Act == NULL) return -5;
				*(Ini) = Act;
			/*aaaaa*/
			fprintf(stderr, "\n\t Sólo la primera \n");
			fprintf(stderr, "\n%s %s %s %s %s %s %f", Nombre, Numero, RutaImagen, Velocidad, Alto, Ancho, Pos_y );
			/*aaaaa*/
		}
		else{
			Ant->Sig = (Objeto *) malloc(sizeof(Objeto));
				if(Ant->Sig == NULL) return -5;
			Act = Ant->Sig;
			/*aaaaa*/
			fprintf(stderr, "\n\t Las demás \n");
			fprintf(stderr, "\n %s %s %s %s %s %s %f", Nombre, Numero, RutaImagen, Velocidad, Alto, Ancho, Pos_y );
			/*aaaaa*/
		}			
		Act->Nombre = (char *) malloc(50*sizeof(char));
			if(Act->Nombre == NULL) return -5;
		strcpy(Act->Nombre, Nombre);
		
		Act->Numero = atoi(Numero);
		
		Act->DirImagen = (char *) malloc(100*sizeof(char));
			if(Ancho == NULL) return -5;
		strcpy(Act->DirImagen, RutaImagen);
		
		if( strstr(Nombre, "Background") ){
			Act->Velocidad = 0;
			Act->Alto = 0;
			Act->Ancho = 0;
			Act->Pos_x = 0;
			Act->Pos_y = 0;
			/*aaaaa*/
			fprintf(stderr, "\n\t Entró en Background \n");
			/*aaaaa*/
		}
		else if( strstr(Nombre, "Frog") && Act->Numero == 1){
			Act->Velocidad = 0;
			Act->Alto = FROG_SIZE;
			Act->Ancho = FROG_SIZE;
			Act->Pos_x = SCREEN_W / 2.0 - FROG_SIZE / 2.0;;
			Act->Pos_y = SCREEN_H - (SCREEN_H+UPPER_OFFSET) / ((MAX_BOUNCE_Y*2.0) - 1) - FROG_SIZE / 2.0;;
			/*aaaaa*/
			fprintf(stderr, "\n\t Entró en Frog \n");
			/*aaaaa*/
		}
		else {
			Act->Velocidad = atof(Velocidad);
			Act->Alto = atof(Alto);
			Act->Ancho = atof(Ancho);
			Act->Pos_x = SCREEN_W - 350;
			Act->Pos_y = Pos_y;
			/*aaaaa*/
			fprintf(stderr, "\n\t Entró en Tronco \n");
			/*aaaaa*/
		}

		Act->Imagen = al_load_bitmap(RutaImagen);
		if(!Act->Imagen) {
			fprintf(stderr, "\n\n\tError al cargar la imagen %s, de %s.", RutaImagen, Nombre);
			al_show_native_message_box((*(display)), "Error", "Error", "Failed to load image! (Objeto)",
						NULL, ALLEGRO_MESSAGEBOX_ERROR);
			Act = (*Ini);
			while(Act != NULL){
				al_destroy_bitmap(Act->Imagen);
				Act = Act->Sig;
			}
			al_destroy_event_queue(*(event_queue));
			al_destroy_display(*(display));
			al_destroy_timer(*(resting_timer));
			al_destroy_timer(*(refresh_timer));
			return -5;
		}
		/*aaaaa*/
		fprintf(stderr, "\n\t Imagen Cargada \n");
		/*aaaaa*/
		Ant = Act;
		Act = NULL;
		fscanf(fp, "%[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %f", Nombre, Numero, RutaImagen, Velocidad, Alto, Ancho, &Pos_y);
	}
	Ant->Sig = NULL;
	
	fprintf(stderr, "\n\t Despues De cargar objetos \n");

	
	if ( AlDrawTodo(Ini, 0.2, 0.5) == -5) return -5; 
	
	al_register_event_source((*(event_queue)), al_get_display_event_source(*(display))); //conectamos eventos de la pantalla 
	al_register_event_source((*(event_queue)), al_get_keyboard_event_source());//entradas a dicha cola
	
	fclose(fp);
	
	return 0;	
}
