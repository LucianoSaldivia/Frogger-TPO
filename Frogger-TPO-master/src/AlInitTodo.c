#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/AlInitTodo.h"

const int FPS;					
const int SCREEN_W;				//Ancho de la ventana
const int SCREEN_H;				//Alto de la ventana
const int FROG_SIZE; 			//Tamaño de frog DEBE ser menor a BOUNCE_Y
const float MAX_BOUNCE_X;		//Máxima cantidad de saltos en X
const float MAX_BOUNCE_Y;		//Máxima cantidad de saltos en Y
const float FROG_RESTING_TIME;//Tiempo entre salto y salto
const float UPPER_OFFSET;		//Corrimiento superior, por el borde de la imagen


int AlInitTodo(ALLEGRO_TIMER **resting_timer, ALLEGRO_TIMER **refresh_timer, ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **Background, ALLEGRO_BITMAP **Frog, ALLEGRO_EVENT_QUEUE **event_queue){
	
	float frog_x = SCREEN_W / 2.0 - FROG_SIZE / 2.0;		//Posicion inicial en x
	float frog_y = SCREEN_H - (SCREEN_H+UPPER_OFFSET) / ((MAX_BOUNCE_Y*2.0) - 1) - FROG_SIZE / 2.0; //Posicion inicial en y
	
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
	
	*(refresh_timer) = al_create_timer(FPS);
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
	
	*(Background) = al_load_bitmap("Imagenes/Background.png");
	if(!(*(Background))) {
		al_show_native_message_box((*(display)), "Error", "Error", "Failed to load image! (BACKGROUND)",
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(*(display));
		al_destroy_timer(*(resting_timer));
		al_destroy_timer(*(refresh_timer));
		return -5;
	}
	
	*(Frog) = al_load_bitmap("Imagenes/Muerte.png");
	if(!(*(Frog))) {
		al_show_native_message_box((*(display)), "Error", "Error", "Failed to load image! (Frog)",
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_bitmap(*(Background));
		al_destroy_display(*(display));
		al_destroy_timer(*(resting_timer));
		al_destroy_timer(*(refresh_timer));
		return -5;
	}
	
	al_draw_bitmap(*(Background), 0, 0, 0); //dibujamos la imagen en el 0,0, con 0 flags(el último siempre en 0)
	al_flip_display(); //mostramos
	al_rest(1); //esperamos un segundo
	al_draw_bitmap(*(Frog), frog_x, frog_y, 0); //dibujamos el frog en su posición inicial 
	al_flip_display(); //mostramos
	
	*(event_queue) = al_create_event_queue(); //creamos cola de eventos
	if(!(*(event_queue))) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(*(Frog));
		al_destroy_bitmap(*(Background));
		al_destroy_display(*(display));
		al_destroy_timer(*(resting_timer));
		al_destroy_timer(*(refresh_timer));
		return -5;
	}
	
	al_register_event_source((*(event_queue)), al_get_display_event_source(*(display))); //conectamos eventos de la pantalla 
	al_register_event_source((*(event_queue)), al_get_keyboard_event_source());//entradas a dicha cola
	
	return 0;	
}
