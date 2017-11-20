#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Saltos.h"
#include "../inc/Inicializacion.h"

void RanaSaltaArriba( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites, char *PosicionesFinales ){
	/**
	\fn void RanaSaltaArriba( Objeto **p_ObjetoFrog,
	 ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites,
	 *  char *PosicionesFinales )
	\brief Salto de la rana hacia arriba
	*/
	Objeto *ObjetoFrog = *(p_ObjetoFrog);
	char ContadorSprites = *(p_ContadorSprites);

	if( ObjetoFrog->Pos_y == ( UPPER_OFFSET + BOUNCE_Y - 2 ) ){			//CONDICION DEL SALTO DE LLEGADA
		if( ObjetoFrog->Pos_x > ( X_POS_1 - MARGEN_SALTO_FINAL ) && ObjetoFrog->Pos_x < ( X_POS_1 + MARGEN_SALTO_FINAL ) && PosicionesFinales[POS_1] == VACIA ) {
			ObjetoFrog->Pos_x = X_POS_1; 
			ObjetoFrog->Pos_y = UPPER_OFFSET;
			ObjetoFrog->Imagen = VecFrog[0];
		}
		if( ObjetoFrog->Pos_x > ( X_POS_2 - MARGEN_SALTO_FINAL ) && ObjetoFrog->Pos_x < ( X_POS_2 + MARGEN_SALTO_FINAL ) && PosicionesFinales[POS_2] == VACIA ) {
			ObjetoFrog->Pos_x = X_POS_2; 
			ObjetoFrog->Pos_y = UPPER_OFFSET;
			ObjetoFrog->Imagen = VecFrog[0];
		}
		if( ObjetoFrog->Pos_x > ( X_POS_3 - MARGEN_SALTO_FINAL ) && ObjetoFrog->Pos_x < ( X_POS_3 + MARGEN_SALTO_FINAL ) && PosicionesFinales[POS_3] == VACIA ) {
			ObjetoFrog->Pos_x = X_POS_3;
			ObjetoFrog->Pos_y = UPPER_OFFSET;
			ObjetoFrog->Imagen = VecFrog[0];
		}
		if( ObjetoFrog->Pos_x > ( X_POS_4 - MARGEN_SALTO_FINAL ) && ObjetoFrog->Pos_x < ( X_POS_4 + MARGEN_SALTO_FINAL ) && PosicionesFinales[POS_4] == VACIA ) {
			ObjetoFrog->Pos_x = X_POS_4;
			ObjetoFrog->Pos_y = UPPER_OFFSET;
			ObjetoFrog->Imagen = VecFrog[0];
		}
		if( ObjetoFrog->Pos_x > ( X_POS_5 - MARGEN_SALTO_FINAL ) && ObjetoFrog->Pos_x < ( X_POS_5 + MARGEN_SALTO_FINAL ) && PosicionesFinales[POS_5] == VACIA ) {
			ObjetoFrog->Pos_x = X_POS_5;
			ObjetoFrog->Pos_y = UPPER_OFFSET;
			ObjetoFrog->Imagen = VecFrog[0];
		}
		
		*(p_ContadorSprites) = CANT_SPRITES;
		return;
	}
	else {
		ObjetoFrog->Pos_y -= ( BOUNCE_Y / ( CANT_SPRITES ) ); 
		if( ContadorSprites == ( CANT_SPRITES - 1 ) ) ObjetoFrog->Pos_y = (int) ObjetoFrog->Pos_y;
	
		if( ContadorSprites > 2 ){
			ObjetoFrog->Imagen = VecFrog[0];
		}
		else if( ContadorSprites >= 2 && ContadorSprites < 8  ){
			ObjetoFrog->Imagen = VecFrog[1];
		}
		else if( ContadorSprites >= 8 ){
			ObjetoFrog->Imagen = VecFrog[0];
		}
		
		(*(p_ContadorSprites)) ++;
	}
}

void RanaSaltaAbajo( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites ){
	/**
	\fn void RanaSaltaAbajo( Objeto **p_ObjetoFrog,
	 ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites )
	\brief Salto de la rana hacia abajo
	*/
	Objeto *ObjetoFrog = *(p_ObjetoFrog);
	char ContadorSprites = *(p_ContadorSprites);

	ObjetoFrog->Pos_y += ( BOUNCE_Y / ( CANT_SPRITES ) ); 
	if( ContadorSprites == ( CANT_SPRITES - 1 ) ) ObjetoFrog->Pos_y = (int) ObjetoFrog->Pos_y;
	
	if( ContadorSprites > 2 ){
		ObjetoFrog->Imagen = VecFrog[2];
	}
	
	else if( ContadorSprites >= 2 && ContadorSprites < 8  ){
		ObjetoFrog->Imagen = VecFrog[3];
	}
	
	else if( ContadorSprites >= 8 ){
		ObjetoFrog->Imagen = VecFrog[2];
	}
	
	(*(p_ContadorSprites)) ++;
}

void RanaSaltaIzquierda( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites ){
	/**
	\fn void RanaSaltaIzquierda( Objeto **p_ObjetoFrog,
	 ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites )
	\brief Salto de la rana hacia la izquierda
	*/
	Objeto *ObjetoFrog = *(p_ObjetoFrog);
	char ContadorSprites = *(p_ContadorSprites);
	
	ObjetoFrog->Pos_x -= ( BOUNCE_X / ( CANT_SPRITES ) ); 
	if( ContadorSprites == ( CANT_SPRITES - 1 ) ) ObjetoFrog->Pos_x = (int) ObjetoFrog->Pos_x;
	
	if( ContadorSprites > 2 ){
		ObjetoFrog->Imagen = VecFrog[4];
	}
	
	else if( ContadorSprites >= 2 && ContadorSprites < 8  ){
		ObjetoFrog->Imagen = VecFrog[5];
	}
	
	else if( ContadorSprites >= 8 ){
		ObjetoFrog->Imagen = VecFrog[4];
	}
	
	(*(p_ContadorSprites)) ++;
}

void RanaSaltaDerecha( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites ){
	/**
	\fn void RanaSaltaDerecha( Objeto **p_ObjetoFrog,
	 ALLEGRO_BITMAP **VecFrog, char *p_ContadorSprites )
	\brief Salto de la rana hacia la derecha
	*/
	Objeto *ObjetoFrog = *(p_ObjetoFrog);
	char ContadorSprites = *(p_ContadorSprites);
	
	ObjetoFrog->Pos_x += ( BOUNCE_X / ( CANT_SPRITES ) ); 
	if( ContadorSprites == ( CANT_SPRITES - 1 ) ) ObjetoFrog->Pos_x = (int) ObjetoFrog->Pos_x;
	
	if( ContadorSprites > 2 ){
		ObjetoFrog->Imagen = VecFrog[6];
	}
	
	else if( ContadorSprites >= 2 && ContadorSprites < 8  ){
		ObjetoFrog->Imagen = VecFrog[7];
	}
	
	else if( ContadorSprites >= 8 ){
		ObjetoFrog->Imagen = VecFrog[6];
	}
	
	(*(p_ContadorSprites)) ++;
}

