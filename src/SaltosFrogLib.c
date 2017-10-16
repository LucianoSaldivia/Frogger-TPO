#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/SaltosFrogLib.h"

const int FPS;					
const int SCREEN_W;				//Ancho de la ventana
const int SCREEN_H;				//Alto de la ventana
const int FROG_SIZE; 			//Tamaño de frog DEBE ser menor a BOUNCE_Y
const float MAX_BOUNCE_X;		//Máxima cantidad de saltos en X
const float MAX_BOUNCE_Y;		//Máxima cantidad de saltos en Y
const float UPPER_OFFSET;		//Corrimiento superior, por el borde de la imagen
const float TIEMPO_SPRITE = 0.025;
const float CANT_SPRITES = 25;

int FrogSaltaArriba(ALLEGRO_BITMAP **Background, ALLEGRO_BITMAP ** Frog, float *frog_x, float *frog_y ){
	float y_inicial = *frog_y;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaArriba.png"), al_load_bitmap("Imagenes/RanaSaltoArriba.png")};
	
	float BOUNCE_Y = SCREEN_H / (MAX_BOUNCE_Y+1);
	if(*frog_y < 97) BOUNCE_Y = 60.0;

		while(*frog_y >= y_inicial - BOUNCE_Y){
				if(*frog_y >= y_inicial - (1*BOUNCE_Y / 7)){
					*Frog = PosFrog[0];
				}
				else if(*frog_y >= y_inicial - (6*BOUNCE_Y / 7)){
					*Frog = PosFrog[1];
				}
				else{
					*Frog = PosFrog[0];
				}
				if( ! (*Frog)) return -1;
		
			*frog_y -= BOUNCE_Y / 7 +0.01;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);
			
			
		}
	return 0;
}

int FrogSaltaIzquierda(ALLEGRO_BITMAP **Background, ALLEGRO_BITMAP ** Frog, float *frog_x, float *frog_y ){
	float x_inicial = *frog_x;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaIzquierda.png"), al_load_bitmap("Imagenes/RanaSaltoIzquierda.png")};
	
	float BOUNCE_X = SCREEN_H / (MAX_BOUNCE_X+1);

		while(*frog_x >= x_inicial - BOUNCE_X){
				if(*frog_x >= x_inicial - (1*BOUNCE_X / 7)){
					*Frog = PosFrog[0];
				}
				else if(*frog_x >= x_inicial - (6*BOUNCE_X / 7)){
					*Frog = PosFrog[1];
				}
				else{
					*Frog = PosFrog[0];
				}
				if( ! (*Frog)) return -1;
		
			*frog_x -= BOUNCE_X / 7 +0.01;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);
		}
	return 0;
}

int FrogSaltaAbajo(ALLEGRO_BITMAP **Background, ALLEGRO_BITMAP ** Frog, float *frog_x, float *frog_y ){
	float y_inicial = *frog_y;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaAbajo.png"), al_load_bitmap("Imagenes/RanaSaltoAbajo.png")};
	
	float BOUNCE_Y = SCREEN_H / (MAX_BOUNCE_Y+1);
	if(*frog_y < 50) BOUNCE_Y = 60.0;


		while(*frog_y <= y_inicial + BOUNCE_Y){
				if(*frog_y <= y_inicial + (1*BOUNCE_Y / 7)){
					*Frog = PosFrog[0];
				}
				else if(*frog_y <= y_inicial + (6*BOUNCE_Y / 7)){
					*Frog = PosFrog[1];
				}
				else{
					*Frog = PosFrog[0];
				}
				if( ! (*Frog)) return -1;
		
			*frog_y += BOUNCE_Y / 7 +0.01;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);
		}
	return 0;
}

int FrogSaltaDerecha(ALLEGRO_BITMAP **Background, ALLEGRO_BITMAP ** Frog, float *frog_x, float *frog_y ){
	float x_inicial = *frog_x;

	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaDerecha.png"), al_load_bitmap("Imagenes/RanaSaltoDerecha.png")};
	
	float BOUNCE_X = SCREEN_H / (MAX_BOUNCE_X+1);

		while(*frog_x <= x_inicial + BOUNCE_X){
				if(*frog_x <= x_inicial + (1*BOUNCE_X / 7)){
					*Frog = PosFrog[0];
				}
				else if(*frog_x <= x_inicial + (6*BOUNCE_X / 7)){
					*Frog = PosFrog[1];
				}
				else{
					*Frog = PosFrog[0];
				}
				if( ! (*Frog)) return -1;
		
			*frog_x += BOUNCE_X / 7 +0.01;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);
		}
	return 0;
}

