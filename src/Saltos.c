#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Saltos.h"
#include "../inc/Inicializacion.h"
#include "../inc/MovimientoAmbiente.h"


void RanaSaltaArriba(Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(p_ObjetoFrog);
	float Bounce_Y = BOUNCE_Y;
	float y_inicial = ObjetoFrog->Pos_y;
	bool Esperar = false;
	
	if( ObjetoFrog->Pos_y == ( UPPER_OFFSET + BOUNCE_Y ) ){
		ObjetoFrog->Pos_y = UPPER_OFFSET;
		RedibujarDesde( p_ObjetoFrog );
	}

	while( ObjetoFrog->Pos_y > y_inicial - Bounce_Y ){
		if( Esperar ) al_rest(TIEMPO_ENTRE_SPRITES);
		if( ObjetoFrog->Pos_y >= y_inicial - (Bounce_Y * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[0];
		}
		else if( ObjetoFrog->Pos_y > y_inicial - Bounce_Y * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[1];
		}
		else ObjetoFrog->Imagen = VecFrog[0];
		
		ObjetoFrog->Pos_y -= Bounce_Y / CANT_SPRITES;
		MoverCosas( p_Ini );
		RedibujarDesde( p_Ini );
		Esperar = true;
	}
}

void RanaSaltaAbajo(Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(p_ObjetoFrog);
	float Bounce_Y = BOUNCE_Y;
	float y_inicial = ObjetoFrog->Pos_y;
	bool Esperar = false;
	
	if( ObjetoFrog->Pos_y < 37) Bounce_Y = 60.0;
	
	while( ObjetoFrog->Pos_y < y_inicial + Bounce_Y ){
		if( Esperar ) al_rest(TIEMPO_ENTRE_SPRITES);
		if( ObjetoFrog->Pos_y < y_inicial + (Bounce_Y * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[2];
		}
		else if( ObjetoFrog->Pos_y < y_inicial + Bounce_Y * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[3];
		}
		else ObjetoFrog->Imagen = VecFrog[2];
		
		ObjetoFrog->Pos_y += Bounce_Y / CANT_SPRITES;
		MoverCosas( p_Ini );
		RedibujarDesde( p_Ini );
		Esperar = true;
	}	
}

void RanaSaltaIzquierda(Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(p_ObjetoFrog);	float Bounce_X = BOUNCE_X;
	float x_inicial = ObjetoFrog->Pos_x;
	bool Esperar = false;
	
	while( ObjetoFrog->Pos_x >= x_inicial - BOUNCE_X ){
		if( Esperar ) al_rest(TIEMPO_ENTRE_SPRITES);
		if( ObjetoFrog->Pos_x > x_inicial - (BOUNCE_X * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[4];
		}
		else if( ObjetoFrog->Pos_x > x_inicial - BOUNCE_X * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[5];
		}
		else ObjetoFrog->Imagen = VecFrog[4];
		
		ObjetoFrog->Pos_x -= Bounce_X / CANT_SPRITES;
		MoverCosas( p_Ini );
		RedibujarDesde( p_Ini );
		Esperar = true;
	}	
}

void RanaSaltaDerecha(Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(p_ObjetoFrog);	float Bounce_X = BOUNCE_X;
	float x_inicial = ObjetoFrog->Pos_x;
	bool Esperar = false;
	
	while( ObjetoFrog->Pos_x <= x_inicial + BOUNCE_X ){
		if( Esperar ) al_rest(TIEMPO_ENTRE_SPRITES);
		if( ObjetoFrog->Pos_x < x_inicial + (BOUNCE_X * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[6];
		}
		else if( ObjetoFrog->Pos_x < x_inicial + BOUNCE_X * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[7];
		}
		else ObjetoFrog->Imagen = VecFrog[6];
		
		ObjetoFrog->Pos_x += Bounce_X / CANT_SPRITES;
		MoverCosas( p_Ini );
		RedibujarDesde( p_Ini );
		Esperar = true;	
	}	
}
