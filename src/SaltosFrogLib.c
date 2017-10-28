#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/AlTodo.h"

void FrogSaltaArriba(Objeto **Ini, Objeto **DirObjetoFrog, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_Y = BOUNCE_Y;
	float y_inicial;
	
	ObjetoFrog = *(DirObjetoFrog);
	
	/*aaa*/
	fprintf(stderr, "\n\t\t Encontré al puto %s! ", ObjetoFrog->Nombre);
	/*aaa*/
		
	y_inicial = ObjetoFrog->Pos_y;
	
	if( ObjetoFrog->Pos_y < 97) Bounce_Y = 60.0;

	while( ObjetoFrog->Pos_y >= y_inicial - Bounce_Y){
		if( ObjetoFrog->Pos_y >= y_inicial - (1*Bounce_Y / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if( ObjetoFrog->Pos_y >= y_inicial - (4*Bounce_Y / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}	
	ObjetoFrog->Pos_y -= Bounce_Y / CANT_SPRITES + 0.01;
	AlDrawTodo( Ini, 0, TIEMPO_ENTRE_SPRITES);
	}
}

void FrogSaltaIzquierda(Objeto **Ini, Objeto **DirObjetoFrog, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_X = BOUNCE_X;
	float x_inicial;
	
	ObjetoFrog = *(DirObjetoFrog);
	
	x_inicial = ObjetoFrog->Pos_x;
	
	while(ObjetoFrog->Pos_x >= x_inicial - Bounce_X){
		if(ObjetoFrog->Pos_x >= x_inicial - (1*Bounce_X / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if(ObjetoFrog->Pos_x >= x_inicial - (4*Bounce_X / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}
	ObjetoFrog->Pos_x -= Bounce_X / CANT_SPRITES + 0.01;
	AlDrawTodo( Ini, 0, TIEMPO_ENTRE_SPRITES);
	}
}

void FrogSaltaAbajo(Objeto **Ini, Objeto **DirObjetoFrog, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_Y = BOUNCE_Y;
	float y_inicial;
	
	ObjetoFrog = *(DirObjetoFrog);
	
	y_inicial = ObjetoFrog->Pos_y;
		
	if( ObjetoFrog->Pos_y < 50) Bounce_Y = 60.0;
	while(ObjetoFrog->Pos_y <= y_inicial + Bounce_Y){
		if(ObjetoFrog->Pos_y <= y_inicial + (1*Bounce_Y / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if(ObjetoFrog->Pos_y <= y_inicial + (4*Bounce_Y / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}
	ObjetoFrog->Pos_y += Bounce_Y / CANT_SPRITES + 0.01;
	AlDrawTodo( Ini, 0, TIEMPO_ENTRE_SPRITES);
	}
}

void FrogSaltaDerecha(Objeto **Ini, Objeto **DirObjetoFrog, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	float Bounce_X = BOUNCE_X;
	float x_inicial;
	
	ObjetoFrog = *(DirObjetoFrog);
	
	x_inicial = ObjetoFrog->Pos_x;
		
	while(ObjetoFrog->Pos_x <= x_inicial + Bounce_X){
		if(ObjetoFrog->Pos_x <= x_inicial + (1*Bounce_X / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog);
		}
		else if(ObjetoFrog->Pos_x <= x_inicial + (4*Bounce_X / CANT_SPRITES)){
			ObjetoFrog->Imagen = *(PosFrog + 1);
		}
		else{
			ObjetoFrog->Imagen = *(PosFrog);
		}
	ObjetoFrog->Pos_x += Bounce_X / CANT_SPRITES + 0.01;
	AlDrawTodo( Ini, 0, TIEMPO_ENTRE_SPRITES);
	}
}
