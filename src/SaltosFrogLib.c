#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/AlInitTodo.h"

int FrogSaltaArriba(Objeto **Ini){
	Objeto *Act, *ObjetoFrog;
	float Bounce_Y = BOUNCE_Y;
	float y_inicial;
		
	Act = *(Ini);
	while( Act != NULL ){
		if( (strstr(Act->Nombre, "Frog") != NULL) && Act->Numero == 1 ){
			ObjetoFrog = Act;
		}
		Act = Act->Sig;
	}
	y_inicial = ObjetoFrog->Pos_y;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaArriba.png"), al_load_bitmap("Imagenes/RanaSaltoArriba.png")};
	
	if( ObjetoFrog->Pos_y < 97) Bounce_Y = 60.0;

		while( ObjetoFrog->Pos_y >= y_inicial - Bounce_Y){
				if( ObjetoFrog->Pos_y >= y_inicial - (1*Bounce_Y / 7)){
					ObjetoFrog->Imagen = PosFrog[0];
				}
				else if( ObjetoFrog->Pos_y >= y_inicial - (6*Bounce_Y / 7)){
					ObjetoFrog->Imagen = PosFrog[1];
				}
				else{
					ObjetoFrog->Imagen = PosFrog[0];
				}
				if( ! ObjetoFrog->Imagen ) return -5;
		
			ObjetoFrog->Pos_y -= Bounce_Y / 7 + 0.01;
			
			AlDrawTodo(Ini, 0, TIEMPO_SPRITE/CANT_SPRITES);
			
			/*al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);*/
		}
	return 0;
}

int FrogSaltaIzquierda(Objeto **Ini){
	Objeto *Act, *ObjetoFrog;
	float Bounce_X = BOUNCE_X;
	float x_inicial;
	
	Act = *(Ini);
	while( Act != NULL ){
		if( (strstr(Act->Nombre, "Frog") != NULL) && Act->Numero == 1 ){
			ObjetoFrog = Act;
		}
		Act = Act->Sig;
	}
	x_inicial = ObjetoFrog->Pos_x;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaIzquierda.png"), al_load_bitmap("Imagenes/RanaSaltoIzquierda.png")};
	
		while(ObjetoFrog->Pos_x >= x_inicial - Bounce_X){
				if(ObjetoFrog->Pos_x >= x_inicial - (1*Bounce_X / 7)){
					ObjetoFrog->Imagen = PosFrog[0];
				}
				else if(ObjetoFrog->Pos_x >= x_inicial - (6*Bounce_X / 7)){
					ObjetoFrog->Imagen = PosFrog[1];
				}
				else{
					ObjetoFrog->Imagen = PosFrog[0];
				}
				if( ! ObjetoFrog->Imagen ) return -5;
		
			ObjetoFrog->Pos_x -= Bounce_X / 7 +0.01;
			AlDrawTodo(Ini, 0, TIEMPO_SPRITE/CANT_SPRITES);
			
			/*al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);*/
		}
	return 0;
}

int FrogSaltaAbajo(Objeto **Ini){
	Objeto *Act, *ObjetoFrog;
	float Bounce_Y = BOUNCE_Y;
	float y_inicial;
	
	Act = *(Ini);
	while( Act != NULL ){
		if( (strstr(Act->Nombre, "Frog") != NULL) && Act->Numero == 1 ){
			ObjetoFrog = Act;
		}
		Act = Act->Sig;
	}
	y_inicial = ObjetoFrog->Pos_y;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaAbajo.png"), al_load_bitmap("Imagenes/RanaSaltoAbajo.png")};
	
	if( ObjetoFrog->Pos_y < 50) Bounce_Y = 60.0;

		while(ObjetoFrog->Pos_y <= y_inicial + Bounce_Y){
				if(ObjetoFrog->Pos_y <= y_inicial + (1*Bounce_Y / 7)){
					ObjetoFrog->Imagen = PosFrog[0];
				}
				else if(ObjetoFrog->Pos_y <= y_inicial + (6*Bounce_Y / 7)){
					ObjetoFrog->Imagen = PosFrog[1];
				}
				else{
					ObjetoFrog->Imagen = PosFrog[0];
				}
				if( ! ObjetoFrog->Imagen ) return -5;
		
			ObjetoFrog->Pos_y += Bounce_Y / 7 +0.01;
			AlDrawTodo(Ini, 0, TIEMPO_SPRITE/CANT_SPRITES);
			
			/*al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);*/
		}
	return 0;
}

int FrogSaltaDerecha(Objeto **Ini){
	Objeto *Act, *ObjetoFrog;
	float Bounce_X = BOUNCE_X;
	float x_inicial;
	
	Act = *(Ini);
	while( Act != NULL ){
		if( (strstr(Act->Nombre, "Frog") != NULL) && Act->Numero == 1 ){
			ObjetoFrog = Act;
		}
		Act = Act->Sig;
	}	
	x_inicial = ObjetoFrog->Pos_x;
	
	ALLEGRO_BITMAP *PosFrog[2] = {al_load_bitmap("Imagenes/RanaDerecha.png"), al_load_bitmap("Imagenes/RanaSaltoDerecha.png")};
	
		while(ObjetoFrog->Pos_x <= x_inicial + Bounce_X){
				if(ObjetoFrog->Pos_x <= x_inicial + (1*Bounce_X / 7)){
					ObjetoFrog->Imagen = PosFrog[0];
				}
				else if(ObjetoFrog->Pos_x <= x_inicial + (6*Bounce_X / 7)){
					ObjetoFrog->Imagen = PosFrog[1];
				}
				else{
					ObjetoFrog->Imagen = PosFrog[0];
				}
				if( ! ObjetoFrog->Imagen ) return -5;
		
			ObjetoFrog->Pos_x += Bounce_X / 7 +0.01;
			AlDrawTodo(Ini, 0, TIEMPO_SPRITE/CANT_SPRITES);
			
			/*al_clear_to_color(al_map_rgb(0, 0, 0)); //borramos display, dejamos todo en 0
			al_draw_bitmap(*Background, 0, 0, 0); //dibujamos background en la misma posicion que antes
			al_draw_bitmap(*Frog, *frog_x, *frog_y, 0); //dibujamos frog en su nueva posicion
			al_flip_display(); //lo mostramos
			al_rest(TIEMPO_SPRITE/CANT_SPRITES);*/
		}
	return 0;
}

