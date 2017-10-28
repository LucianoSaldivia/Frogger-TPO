#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/SaltosFrogLib.h"
#include "../inc/Teclas.h"
#include "../inc/AlTodo.h"

void TeclaPresionadaJugador1(ALLEGRO_EVENT *pev, bool **pkey, Objeto **pIni, Objeto **pObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(pObjetoFrog);

	switch(pev->keyboard.keycode){
		case ALLEGRO_KEY_UP:
			if( ObjetoFrog->Pos_y >= LIM_SALTO_ARRIBA ){
				RanaSaltaArriba(pIni, pObjetoFrog, VecFrog );	
				(*pkey)[KEY_UP] = true;
				//al_start_timer(resting_timer);
			}
			break;
		case ALLEGRO_KEY_DOWN:
			if( ObjetoFrog->Pos_y <= LIM_SALTO_ABAJO ) {
				RanaSaltaAbajo( pIni, pObjetoFrog, VecFrog );			
				(*pkey)[KEY_DOWN] = true;
				//al_start_timer(resting_timer);
			}
			break;
		case ALLEGRO_KEY_LEFT:
			if( ObjetoFrog->Pos_x >= LIM_SALTO_IZQUIERDA ) {
				RanaSaltaIzquierda( pIni, pObjetoFrog, VecFrog );			
				(*pkey)[KEY_LEFT] = true;
				//al_start_timer(resting_timer);

			}
			break;
		case ALLEGRO_KEY_RIGHT:
			if( ObjetoFrog->Pos_x <= LIM_SALTO_DERECHA ) {
				RanaSaltaDerecha( pIni, pObjetoFrog, VecFrog );
				(*pkey)[KEY_RIGHT] = true;
				//al_start_timer(resting_timer);
			}
		/*default:
			if( ObjetoFrog->Pos_y <= LIM_SALTO_ABAJO ) {
				RanaSaltaAbajo( pIni, pObjetoFrog, VecFrog );			
				(*pkey)[KEY_DOWN] = true;	
				//al_start_timer(resting_timer);
			}*/	
	}
}

void TeclaSoltadaJugador1(ALLEGRO_EVENT *pev, bool **pkey){
	switch(pev->keyboard.keycode){
		case ALLEGRO_KEY_UP:
			(*pkey)[KEY_UP] = true;			
			break;
		case ALLEGRO_KEY_DOWN:
			(*pkey)[KEY_DOWN] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			(*pkey)[KEY_LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			(*pkey)[KEY_RIGHT] = true;
			break;	
	}
}


void RanaSaltaArriba(Objeto **pIni, Objeto **pObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(pObjetoFrog);
	float Bounce_Y = BOUNCE_Y;
	float y_inicial = ObjetoFrog->Pos_y;
	
	if( ObjetoFrog->Pos_y < 110) Bounce_Y = 60.0;
	/*aaa*/
	fprintf(stderr, "\n\twhile( %f >= %f )", ObjetoFrog->Pos_y, (y_inicial - Bounce_Y) );
	/*aaa*/
	while( ObjetoFrog->Pos_y >= y_inicial - Bounce_Y ){
		/*aaa*/
		fprintf(stderr, "\n\twhile( %f >= %f )", ObjetoFrog->Pos_y, (y_inicial - Bounce_Y) );
		/*aaa*/
		/*aaa*/
		fprintf(stderr, "\n\tif( %f >= %f )", ObjetoFrog->Pos_y, (y_inicial - (Bounce_Y * (1 / CANT_SPRITES )) ) );
		/*aaa*/
		if( ObjetoFrog->Pos_y >= y_inicial - (Bounce_Y * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[0];
		}
		else if( ObjetoFrog->Pos_y > y_inicial - Bounce_Y * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[1];
		}
		else ObjetoFrog->Imagen = VecFrog[0];
		
		ObjetoFrog->Pos_y -= Bounce_Y / CANT_SPRITES;
		AlDrawTodo( pIni, 0, TIEMPO_ENTRE_SPRITES);
	}	
}

void RanaSaltaAbajo(Objeto **pIni, Objeto **pObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(pObjetoFrog);
	float Bounce_Y = BOUNCE_Y;
	float y_inicial = ObjetoFrog->Pos_y;
	
	if( ObjetoFrog->Pos_y < 50) Bounce_Y = 60.0;
	
	while( ObjetoFrog->Pos_y <= y_inicial + Bounce_Y ){
		if( ObjetoFrog->Pos_y < y_inicial + (Bounce_Y * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[2];
		}
		else if( ObjetoFrog->Pos_y < y_inicial + Bounce_Y * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[3];
		}
		else ObjetoFrog->Imagen = VecFrog[2];
		
		ObjetoFrog->Pos_y += Bounce_Y / CANT_SPRITES;
		AlDrawTodo( pIni, 0, TIEMPO_ENTRE_SPRITES);
	}	
}

void RanaSaltaIzquierda(Objeto **pIni, Objeto **pObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(pObjetoFrog);	float Bounce_X = BOUNCE_X;
	float x_inicial = ObjetoFrog->Pos_x;
	
	while( ObjetoFrog->Pos_x >= x_inicial - BOUNCE_X ){
		if( ObjetoFrog->Pos_x > x_inicial - (BOUNCE_X * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[4];
		}
		else if( ObjetoFrog->Pos_x > x_inicial - BOUNCE_X * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[5];
		}
		else ObjetoFrog->Imagen = VecFrog[4];
		
		ObjetoFrog->Pos_x -= Bounce_X / CANT_SPRITES;
		AlDrawTodo( pIni, 0, TIEMPO_ENTRE_SPRITES);
	}	
}

void RanaSaltaDerecha(Objeto **pIni, Objeto **pObjetoFrog, ALLEGRO_BITMAP **VecFrog){
	Objeto *ObjetoFrog = *(pObjetoFrog);	float Bounce_X = BOUNCE_X;
	float x_inicial = ObjetoFrog->Pos_x;
	
	while( ObjetoFrog->Pos_x <= x_inicial + BOUNCE_X ){
		if( ObjetoFrog->Pos_x < x_inicial + (BOUNCE_X * (1 / CANT_SPRITES )) ){
			ObjetoFrog->Imagen = VecFrog[6];
		}
		else if( ObjetoFrog->Pos_x < x_inicial + BOUNCE_X * (CANT_SPRITES-1) / CANT_SPRITES ){
			ObjetoFrog->Imagen = VecFrog[7];
		}
		else ObjetoFrog->Imagen = VecFrog[6];
		
		ObjetoFrog->Pos_x += Bounce_X / CANT_SPRITES;
		AlDrawTodo( pIni, 0, TIEMPO_ENTRE_SPRITES);
	}	
}


/*void RedibujarRana( Objeto **pObjetoFrog ){
	al_draw_bitmap( (*pObjetoFrog)->Imagen, (*pObjetoFrog)->Pos_x, (*pObjetoFrog)->Pos_y, 0); //dibujamos todo 0 flags
	al_flip_display();
	al_rest();
}*/

/*void Jugador1ApretoFlecha(ALLEGRO_EVENT *ev, bool **key, ALLEGRO_TIMER **resting_timer, Objeto **DirObjetoFrog, Objeto **Ini, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;
	
	ObjetoFrog = *(DirObjetoFrog);
	
	switch(ev->keyboard.keycode) {
		case ALLEGRO_KEY_UP: //si es tecla arriba
			
			(*key)[KEY_UP] = true; //en nuestro set de teclas, arriba es true
			if( ObjetoFrog->Pos_y >= (BOUNCE_Y+UPPER_OFFSET)) { //si se puede mover, habilitamos el movimiento
				FrogSaltaArriba( DirObjetoFrog, Ini, PosFrog);
				
			}	
			break;
		case ALLEGRO_KEY_DOWN://si es tecla abajo
			(*key)[KEY_DOWN] = true;  //en nuestro set de teclas, abajo es true
			if( ObjetoFrog->Pos_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {//si se puede mover, le cambiamos la posicion
				FrogSaltaAbajo( DirObjetoFrog, Ini, PosFrog);
			}
			break;
		case ALLEGRO_KEY_LEFT: //igual que KEY_UP, pero para la izquierda
			(*key)[KEY_LEFT] = true;
			if( ObjetoFrog->Pos_x >= BOUNCE_X) {
				FrogSaltaIzquierda( DirObjetoFrog, Ini, PosFrog);
			}
			break;
		case ALLEGRO_KEY_RIGHT: //igual que  KEY_DOWN, pero para la derecha
			(*key)[KEY_RIGHT] = true;
			if( ObjetoFrog->Pos_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
				FrogSaltaDerecha( DirObjetoFrog, Ini, PosFrog);
			}  
			break;
	}	
	al_start_timer(*(resting_timer));
}*/



/*void Jugador1SigueApretandoFlecha(bool *key, Objeto **DirObjetoFrog, Objeto **Ini, ALLEGRO_BITMAP **PosFrog){
	Objeto *ObjetoFrog;

	ObjetoFrog = *(DirObjetoFrog);
	
	if(key[KEY_UP] && ObjetoFrog->Pos_y >= BOUNCE_Y) { //si UP estaba presionada y se puede mover
		FrogSaltaArriba( DirObjetoFrog, Ini, PosFrog);
	}
	if(key[KEY_DOWN] && ObjetoFrog->Pos_y <= SCREEN_H - FROG_SIZE - BOUNCE_Y) {
		FrogSaltaAbajo( DirObjetoFrog, Ini, PosFrog);
	}
	if(key[KEY_LEFT] && ObjetoFrog->Pos_x >= BOUNCE_X) {
		FrogSaltaIzquierda( DirObjetoFrog, Ini, PosFrog);
	}
	if(key[KEY_RIGHT] && ObjetoFrog->Pos_x <= SCREEN_W - FROG_SIZE - BOUNCE_X) {
		FrogSaltaDerecha( DirObjetoFrog, Ini, PosFrog);
	}
}*/

/*void Jugador1SoltoFlecha(ALLEGRO_EVENT *ev, bool **key, bool *doexit, ALLEGRO_TIMER **resting_timer){	
	switch(ev->keyboard.keycode) { //detectamos la tecla y en nuestro set de teclas, queda como false
		case ALLEGRO_KEY_UP:
			(*key)[KEY_UP] = false;
			break;	
		case ALLEGRO_KEY_DOWN:
			(*key)[KEY_DOWN] = false;
			break;	
		case ALLEGRO_KEY_LEFT: 
			(*key)[KEY_LEFT] = false;
			break;
			
		case ALLEGRO_KEY_RIGHT:
			(*key)[KEY_RIGHT] = false;
			break;  
		case ALLEGRO_KEY_ESCAPE:
			*(doexit) = true;
			break;
	}
	al_stop_timer(*(resting_timer));	
}*/


