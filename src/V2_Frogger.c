#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/SaltosFrogLib.h"

const int FPS = 60;					
const int SCREEN_W = 719;			//Ancho de la ventana
const int SCREEN_H = 701;			//Alto de la ventana
const int FROG_SIZE = 50; 			// A L E R T A ! ! !  Tamaño de frog DEBE ser menor a BOUNCE_Y
const float MAX_BOUNCE_X = 11.0;	//Máxima cantidad de saltos en X
const float MAX_BOUNCE_Y = 13.0;	//Máxima cantidad de saltos en Y
const float FROG_RESTING_TIME = 0.35;//Tiempo entre salto y salto
const float UPPER_OFFSET = 0;		//Corrimiento superior, por el borde de la imagen
//(arriba la imagen tiene más borde "inutil" que abajo, en lugar de recortarla puse el offset, porque
//después ahí tenemos que agregar puntajes, vidas y cosas así)

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYJUMPS {
	JUMP_UP, JUMP_DOWN, JUMP_LEFT, JUMP_RIGHT
};
 
int main(int argc, char **argv)
{


	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *resting_timer = NULL, *refresh_timer = NULL;
	ALLEGRO_BITMAP *Background = NULL, *Frog = NULL;
   
	const float BOUNCE_X = SCREEN_W / (MAX_BOUNCE_X+1);
	const float BOUNCE_Y = SCREEN_H / (MAX_BOUNCE_Y+1);

	float frog_x = SCREEN_W / 2.0 - FROG_SIZE / 2.0;		//Posicion inicial en x
	float frog_y = SCREEN_H - (SCREEN_H+UPPER_OFFSET) / ((MAX_BOUNCE_Y*2.0) - 1) - FROG_SIZE / 2.0; //Posicion inicial en y
   
   
	bool key[4] = { false, false, false, false };
	bool redraw = false; //Identifica si hay que redibujar o no
	bool jump[4] = { false, false, false, false };
	bool doexit = false; //Identifica si hay que salir o no
   
	int aux = 1;

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}
   
	resting_timer = al_create_timer(FROG_RESTING_TIME);
	if(!resting_timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	
	refresh_timer = al_create_timer(FPS);
	if(!refresh_timer) {
		fprintf(stderr, "failed to create timer!\n");
		al_destroy_timer(resting_timer);
		return -1;
	}
 
	if(!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_timer(resting_timer);
		al_destroy_timer(refresh_timer);
		return 0;
	}
   
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(resting_timer);
		return -1;
	}

    Background = al_load_bitmap("Imagenes/Background.png");

	if(!Background) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image! (BACKGROUND)",
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(resting_timer);
		al_destroy_timer(refresh_timer);
		return 0;
	}
   
   
	Frog = al_create_bitmap(FROG_SIZE, FROG_SIZE); //Esto después habría que cambiarlo por imagen del frog
	if(!Frog) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_bitmap(Background);
		al_destroy_display(display);
		al_destroy_timer(resting_timer);
		al_destroy_timer(refresh_timer);
		return -1;
	}
	
	Frog = al_load_bitmap("Imagenes/Muerte.png");

	if(!Background) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image! (BACKGROUND)",
					NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(resting_timer);
		al_destroy_timer(refresh_timer);
		return 0;
	}

	al_draw_bitmap(Background, 0, 0, 0); //dibujamos la imagen en el 0,0, con 0 flags(el último siempre en 0)

	al_flip_display(); //mostramos
	al_rest(1); //esperamos un segundo
	al_draw_bitmap(Frog, frog_x, frog_y, 0); //dibujamos el frog en su posición inicial 
	al_flip_display(); //mostramos

	event_queue = al_create_event_queue(); //creamos cola de eventos
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(Frog);
		al_destroy_bitmap(Background);
		al_destroy_display(display);
		al_destroy_timer(resting_timer);
		al_destroy_timer(refresh_timer);
		return -1;
	}
	
	al_register_event_source(event_queue, al_get_display_event_source(display)); //conectamos todas las 
	al_register_event_source(event_queue, al_get_keyboard_event_source());//entradas a dicha cola
 
	while(!doexit){ //Loop del juego
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //si recibe esto, cierra la ventana
			break;
		}	
		
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //sino, y recibe evento de tecla presionada
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP: //si es tecla arriba
					key[KEY_UP] = true; //en nuestro set de teclas, arriba es true
					if(frog_y >= (BOUNCE_Y+UPPER_OFFSET)) { //si se puede mover, le cambiamos la posicion
						jump[JUMP_UP] = true;
					}	
					break;
	 
				case ALLEGRO_KEY_DOWN://si es tecla abajo
					key[KEY_DOWN] = true;  //en nuestro set de teclas, abajo es true
					if(key[KEY_DOWN] && frog_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {//si se puede mover, le cambiamos la posicion
						jump[JUMP_DOWN] = true;
					}
					break;
				case ALLEGRO_KEY_LEFT: //igual que KEY_UP, pero para la izquierda
					key[KEY_LEFT] = true;
					if(key[KEY_LEFT] && frog_x >= BOUNCE_X) {
						jump[JUMP_LEFT] = true;
					}
					break;
	 
					case ALLEGRO_KEY_RIGHT: //igual que  KEY_DOWN, pero para la derecha
					key[KEY_RIGHT] = true;
					if(key[KEY_RIGHT] && frog_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
						jump[JUMP_RIGHT] = true;
					}  
					break;
			}
			 
			redraw = true; //HAY que redibujar
			 
			al_start_timer(resting_timer); //iniciamos timer de descanso
		}
		  
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //evento de tecla soltada
			switch(ev.keyboard.keycode) { //detectamos la tecla y en nuestro set de teclas, queda como false
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;
					
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;
					
				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = false;
					break;
					
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;
				   
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
			}
			al_stop_timer(resting_timer);
		}
		  
		else if(ev.timer.source == resting_timer) { //evento de timer de descanso
			if(key[KEY_UP] && frog_y >= BOUNCE_Y) { //si UP estaba presionada y se puede mover
				jump[JUMP_UP] = true;
			}
			
			if(key[KEY_DOWN] && frog_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {
				jump[JUMP_DOWN] = true;
			}
			
			if(key[KEY_LEFT] && frog_x >= BOUNCE_X) {
				jump[JUMP_LEFT] = true;
			}
	 
			if(key[KEY_RIGHT] && frog_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
				jump[JUMP_RIGHT] = true;
			}
		
			redraw = true; //HAY que redibujar
		}  
		
		if(redraw) { //si al llegar acá, hay que redibujar
			redraw = false; //dejamos redraw en false, para que no entre infinitas veces					  
					  
			if(jump[JUMP_UP]){
				aux = (FrogSaltaArriba(&Background, &Frog, &frog_x, &frog_y));			   
				jump[JUMP_UP] = false;
			}
			 
			if(jump[JUMP_DOWN]){
				aux = (FrogSaltaAbajo(&Background, &Frog, &frog_x, &frog_y));
				jump[JUMP_DOWN] = false;
			}
			if(jump[JUMP_LEFT]){
				aux = (FrogSaltaIzquierda(&Background, &Frog, &frog_x, &frog_y));
				jump[JUMP_LEFT] = false;
			}
			if(jump[JUMP_RIGHT]){
				aux = (FrogSaltaDerecha(&Background, &Frog, &frog_x, &frog_y));
				jump[JUMP_RIGHT] = false;
			}
			
			if(aux == -1){
					al_show_native_message_box(display, "Error", "Error", "Failed to load image! (ranaSaltoArriba)",
								NULL, ALLEGRO_MESSAGEBOX_ERROR);
					al_destroy_bitmap(Background); //destruimos todo lo creado
					al_destroy_bitmap(Frog);
					al_destroy_timer(resting_timer);
					al_destroy_timer(refresh_timer);
					al_destroy_display(display);
					al_destroy_event_queue(event_queue);
					return 0;
			}
			 
		  }
	   } 
	   al_destroy_bitmap(Background); //destruimos todo lo creado
	   al_destroy_bitmap(Frog);
	   al_destroy_timer(resting_timer);
	   al_destroy_timer(refresh_timer);
	   al_destroy_display(display);
	   al_destroy_event_queue(event_queue);
	 
	   return 0;
}
