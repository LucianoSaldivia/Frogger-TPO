#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/Dibujos.h"
#include "../inc/Menu.h"

char Juego1vsC( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_TIMER *resting_timer = NULL, *frames_timer = NULL, *sprites_timer = NULL, *died_timer = NULL;
	ALLEGRO_BITMAP **VecFrog = NULL;
	ALLEGRO_FONT *FuentePuntos = NULL;
	Objeto *Ini = NULL, *ObjetoFrog = NULL, /*aaaaaaa*/*Act = NULL;
	bool *key = NULL, EstadoFrog = VIVO;
	char Flag = CONTINUAR, Direccion = NO_HAY_DIRECCION, ContadorSprites = 0, *PosicionesFinales = NULL;
	int Vidas = CANT_VIDAS_INICIALES, Puntos = 0;
	
	if( Inicializar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales ) == ERROR ) return ERROR;
	
	if( AlistarObjetos1vsC( &Ini, &ObjetoFrog, "Archivos/Objetos1vsC.txt" ) == ERROR ){
		Finalizar1vsC( &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales );
		LiberarMemoria( &Ini );
		return ERROR;
	}
	
	/*aaaaaaaaaaaaaaaaaaaaaaaa*/
	Act = Ini;
	while( Act != NULL){
		fprintf( stderr, "\n%s %d %s %f %f", Act->Nombre, Act->Numero, Act->DirImagen, Act->Pos_y, Act->Dif_x );
		Act = Act->Sig;
	}
	/*aaaaaaaaaaaaaaaaaaaaaaaa*/
	
	FuentePuntos = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_PUNTOS, 0 );
	al_start_timer( frames_timer );
		
	while( Flag != SALIR && Flag != VOLVER ){							// VOLVER = VOLVER AL MENU PRINCIPAL
		while( Flag != ERROR && Flag != PAUSA && Flag != FIN_PERDIO && Flag != FIN_GANO ){											//Juego
			ALLEGRO_EVENT ev;
			al_wait_for_event( *(p_event_queue), &ev);
			
			if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) return SALIR;
			
			else if( ev.type == ALLEGRO_EVENT_KEY_DOWN && EstadoFrog == VIVO ){
				Flag = Jugador1ApretoTecla( &ev, key, &resting_timer, &sprites_timer );
				if( Direccion == NO_HAY_DIRECCION ){
					if( key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion = ARRIBA;
					if( key[KEY_DOWN] && ! key[KEY_UP] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion = ABAJO;
					if( key[KEY_LEFT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_RIGHT] ) Direccion = IZQUIERDA;
					if( key[KEY_RIGHT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] ) Direccion = DERECHA;
				}
			}
			
			else if( ev.type == ALLEGRO_EVENT_KEY_UP ){
				Jugador1SoltoTecla( &ev, key, &resting_timer );
			}
			
			else if( ev.type == ALLEGRO_EVENT_TIMER ){
				if( ev.timer.source == frames_timer ){
					if( Vidas == 0 ) Flag = FIN_PERDIO;
					MoverTodo( &Ini, &ObjetoFrog );
					if( EstadoFrog == VIVO ) DetectarColision( &Ini, &ObjetoFrog, VecFrog, &died_timer, &Vidas, &EstadoFrog, ContadorSprites );
					if( ObjetoFrog->Pos_y == UPPER_OFFSET ) Flag = LeerPosFinal( &ObjetoFrog, PosicionesFinales );
					RedibujarDesdeConTexto( &Ini, &FuentePuntos, &Puntos, &Vidas );
				}
				else if( ev.timer.source == died_timer ){
					RevivirFrog1( &ObjetoFrog, VecFrog, &died_timer, &EstadoFrog );
				}
				else if( ev.timer.source == resting_timer ){
					al_start_timer( sprites_timer );
					if( key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion = ARRIBA;
					if( key[KEY_DOWN] && ! key[KEY_UP] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion = ABAJO;
					if( key[KEY_LEFT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_RIGHT] ) Direccion = IZQUIERDA;
					if( key[KEY_RIGHT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] ) Direccion = DERECHA;
				}
				else if( ev.timer.source == sprites_timer && Direccion != NO_HAY_DIRECCION ){
					if( ContadorSprites < CANT_SPRITES && EstadoFrog == VIVO ){
						switch( Direccion ){
							case ARRIBA:
								if( ObjetoFrog->Pos_y > LIM_SALTO_ARRIBA ) RanaSaltaArriba( &ObjetoFrog, VecFrog, &ContadorSprites, PosicionesFinales );
								break;
							case ABAJO:
								if( ObjetoFrog->Pos_y < LIM_SALTO_ABAJO ) RanaSaltaAbajo( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
							case IZQUIERDA:
								if( ObjetoFrog->Pos_x > LIM_SALTO_IZQUIERDA ) RanaSaltaIzquierda( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
							case DERECHA:
								if( ObjetoFrog->Pos_x < LIM_SALTO_DERECHA ) RanaSaltaDerecha( &ObjetoFrog, VecFrog, &ContadorSprites );
								break;
						}
						if( ContadorSprites == CANT_SPRITES ) {
							al_stop_timer( sprites_timer );
							ContadorSprites = 0;
							if( Direccion == ARRIBA ) Puntos += PUNTOS_POR_SALTO;
							Direccion = NO_HAY_DIRECCION;
						}
					}
				}
			}
		}
		if( Flag == ERROR ) break;
		else if( Flag == PAUSA ) Flag = MenuPausa( p_display );											// Devuelve CONTINUAR, VOLVER o SALIR
		else if( Flag == FIN_GANO || Flag == FIN_PERDIO ) break;
		al_flush_event_queue( *(p_event_queue) );
	}
	if( Flag == FIN_GANO ) Flag = MenuNuevoPuntaje( &Ini, p_display, &Puntos, "Ganaste !" );
	else if( Flag == FIN_PERDIO ) Flag = MenuNuevoPuntaje( &Ini, p_display, &Puntos, "Perdiste..." );
	
	if( Flag != SALIR && Flag != ERROR && Flag != VOLVER ) Flag = MenuPuntajes( p_event_queue );
	
	al_destroy_font( FuentePuntos );
	LiberarMemoria( &Ini );
	Finalizar1vsC( &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales );
	
	return Flag;
}
