#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/AlTodo.h"

int SaltoJugador1(bool *redraw, bool *jump, Objeto **Ini,  ALLEGRO_BITMAP **PosFrog){
	int aux;
	
	*(redraw) = false; //dejamos redraw en false, para que no entre infinitas veces					  
			  
	if(jump[JUMP_UP]){
		aux = (FrogSaltaArriba(&Ini, &PosFrog[0]));			   
		jump[JUMP_UP] = false;
	}
	if(jump[JUMP_DOWN]){
		aux = (FrogSaltaAbajo(&Ini, &PosFrog[2]));
		jump[JUMP_DOWN] = false;
	}
	if(jump[JUMP_LEFT]){
		aux = (FrogSaltaIzquierda(&Ini, &PosFrog[4]));
		jump[JUMP_LEFT] = false;
	}
	if(jump[JUMP_RIGHT]){
		aux = (FrogSaltaDerecha(&Ini, &PosFrog[6]));
		jump[JUMP_RIGHT] = false;
	}	
	
	return aux;
}

int FrogSaltaArriba(Objeto ***Ini, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_Y = BOUNCE_Y;
	float y_inicial;
	
	ObjetoFrog = *( *(Ini) );
	while( ! (strstr(ObjetoFrog->Nombre, "Frog")) && ObjetoFrog->Numero == 1 ){
		ObjetoFrog = ObjetoFrog->Sig;
	}
		
	y_inicial = ObjetoFrog->Pos_y;
	
	if( ObjetoFrog->Pos_y < 97) Bounce_Y = 60.0;

	while( ObjetoFrog->Pos_y >= y_inicial - Bounce_Y){
			if( ObjetoFrog->Pos_y >= y_inicial - (1*Bounce_Y / 7)){
				ObjetoFrog->Imagen = *(PosFrog);
			}
			else if( ObjetoFrog->Pos_y >= y_inicial - (6*Bounce_Y / 7)){
				ObjetoFrog->Imagen = *(PosFrog + 1);
			}
			else{
				ObjetoFrog->Imagen = *(PosFrog);
			}
			if( ! ObjetoFrog->Imagen ) return -5;
	
		ObjetoFrog->Pos_y -= Bounce_Y / 7 + 0.01;
		
		AlDrawTodo( (*(Ini)), 0, TIEMPO_ENTRE_SPRITES);
	}
	return 0;
}

int FrogSaltaIzquierda(Objeto ***Ini, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_X = BOUNCE_X;
	float x_inicial;
	
	ObjetoFrog = *( *(Ini) );
	while( ! (strstr(ObjetoFrog->Nombre, "Frog")) && ObjetoFrog->Numero == 1 ){
		ObjetoFrog = ObjetoFrog->Sig;
	}
	
	x_inicial = ObjetoFrog->Pos_x;
	
	while(ObjetoFrog->Pos_x >= x_inicial - Bounce_X){
		if(ObjetoFrog->Pos_x >= x_inicial - (1*Bounce_X / 7)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if(ObjetoFrog->Pos_x >= x_inicial - (6*Bounce_X / 7)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}
		if( ! ObjetoFrog->Imagen ) return -5;
	ObjetoFrog->Pos_x -= Bounce_X / 7 +0.01;
	AlDrawTodo(*(Ini), 0, TIEMPO_ENTRE_SPRITES);
	}
	return 0;
}

int FrogSaltaAbajo(Objeto ***Ini, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_Y = BOUNCE_Y;
	float y_inicial;
	
	ObjetoFrog = *( *(Ini) );
	while( ! (strstr(ObjetoFrog->Nombre, "Frog")) && ObjetoFrog->Numero == 1 ){
		ObjetoFrog = ObjetoFrog->Sig;
	}
	
	y_inicial = ObjetoFrog->Pos_y;
		
	if( ObjetoFrog->Pos_y < 50) Bounce_Y = 60.0;
	while(ObjetoFrog->Pos_y <= y_inicial + Bounce_Y){
		if(ObjetoFrog->Pos_y <= y_inicial + (1*Bounce_Y / 7)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if(ObjetoFrog->Pos_y <= y_inicial + (6*Bounce_Y / 7)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}
		if( ! ObjetoFrog->Imagen ) return -5;
	ObjetoFrog->Pos_y += Bounce_Y / 7 +0.01;
	AlDrawTodo(*(Ini), 0, TIEMPO_ENTRE_SPRITES);
	}
	return 0;
}

int FrogSaltaDerecha(Objeto ***Ini, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_X = BOUNCE_X;
	float x_inicial;
	
	ObjetoFrog = *( *(Ini) );
	while( ! (strstr(ObjetoFrog->Nombre, "Frog")) && ObjetoFrog->Numero == 1 ){
		ObjetoFrog = ObjetoFrog->Sig;
	}
		
	x_inicial = ObjetoFrog->Pos_x;
		
	while(ObjetoFrog->Pos_x <= x_inicial + Bounce_X){
		if(ObjetoFrog->Pos_x <= x_inicial + (1*Bounce_X / 7)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if(ObjetoFrog->Pos_x <= x_inicial + (6*Bounce_X / 7)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}
		if( ! ObjetoFrog->Imagen ) return -5;
	ObjetoFrog->Pos_x += Bounce_X / 7 +0.01;
	AlDrawTodo(*(Ini), 0, TIEMPO_ENTRE_SPRITES);
	}
	return 0;
}
