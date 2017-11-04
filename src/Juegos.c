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
#include "../inc/MovimientoAmbiente.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/Dibujos.h"
#include "../inc/Menu.h"

char Juego1vsC( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_TIMER *resting_timer = NULL, *frames_timer = NULL, *sprites_timer = NULL, *died_timer = NULL;
	ALLEGRO_BITMAP **VecFrog = NULL;
	//ALLEGRO_FONT *FuentePuntos = NULL;
	Objeto *Ini = NULL, *ObjetoFrog = NULL, /*aaaaaaa*/*Act = NULL;
	bool *key = NULL, EstadoFrog = VIVO;
	char Flag = CONTINUAR, Direccion = NO_HAY_DIRECCION, ContadorSprites = 0, *PosicionesFinales = NULL;
	int Vidas = CANT_VIDAS_INICIALES;
	int Puntos = 0;
	
	if( Inicializar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales ) == ERROR ){
		Finalizar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales );
		return ERROR;		
	}
	
	if( AlistarObjetos( &Ini, &ObjetoFrog, "Archivos/Objetos1vsC.txt" ) == ERROR ){
		Finalizar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales );
		LiberarMemoria( &Ini );
		return ERROR;
	}
	
	/*aaaaaaaaaaaaaaaaaaaaaaaa*/
	Act = Ini;
	while( Act != NULL){
		fprintf(stderr, "\n%s %d %s %f %f", Act->Nombre, Act->Numero, Act->DirImagen, Act->Pos_y, Act->Dif_x);
		Act = Act->Sig;
	}
	/*aaaaaaaaaaaaaaaaaaaaaaaa*/
	
	//FuentePuntos = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_PUNTOS, 0 );
	al_start_timer( frames_timer );
		
	while( Flag != SALIR && Flag != VOLVER ){							// VOLVER = VOLVER AL MENU PRINCIPAL
		while( Flag != PAUSA && Flag != FIN ){											//Juego
			ALLEGRO_EVENT ev;
			al_wait_for_event( *(p_event_queue), &ev);
			
			if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) return SALIR;
			
			else if( ev.type == ALLEGRO_EVENT_KEY_DOWN && EstadoFrog == VIVO ){
				Flag = Jugador1ApretoTecla( &ev, key, &Direccion, &resting_timer, &sprites_timer );
			}
			
			else if( ev.type == ALLEGRO_EVENT_KEY_UP ){
				Jugador1SoltoTecla( &ev, key, &resting_timer );
			}
			
			else if( ev.type == ALLEGRO_EVENT_TIMER ){
				if( ev.timer.source == frames_timer ){
					if( EstadoFrog == VIVO ) DetectarColision( &Ini, &ObjetoFrog, VecFrog, &died_timer, &Vidas, &EstadoFrog );
					if( Vidas == 0 ) Flag = FIN;
					MoverTodo( &Ini, &ObjetoFrog );
					if( ObjetoFrog->Pos_y == UPPER_OFFSET ) Flag = LeerPosFinal( &ObjetoFrog, PosicionesFinales );
					RedibujarDesde( &Ini );
					//MostrarPuntos( &FuentePuntos, &Puntos );
					//MostrarTodo( &FuentePuntos, &Puntos, &Ini );
				}
				else if( ev.timer.source == died_timer ){
					RevivirFrog1( &ObjetoFrog, VecFrog, &died_timer, &EstadoFrog );
				}
				else if( ev.timer.source == resting_timer ){
					al_start_timer( sprites_timer );
					if( key[KEY_UP] == true ) Direccion = ARRIBA;
					if( key[KEY_DOWN] == true ) Direccion = ABAJO;
					if( key[KEY_LEFT] == true ) Direccion = IZQUIERDA;
					if( key[KEY_RIGHT] == true ) Direccion = DERECHA;
				}
				else if( ev.timer.source == sprites_timer && Direccion != NO_HAY_DIRECCION ){
					if( ContadorSprites < CANT_SPRITES && EstadoFrog == VIVO ){
						switch( Direccion ){
							case ARRIBA:
								if( ObjetoFrog->Pos_y > LIM_SALTO_ARRIBA ) RanaSaltaArriba( &ObjetoFrog, VecFrog, &ContadorSprites );
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
					}
					else{
						al_stop_timer( sprites_timer );
						ContadorSprites = 0;
						if( Direccion == ARRIBA ) Puntos += 150;
						Direccion = NO_HAY_DIRECCION;
					}
				}
			}
		}
		fprintf(stdout, "\n Hiciste un total de %d puntos, SOS GENIALIDAD PURA VOS! \n", Puntos);
		if( Flag == PAUSA ) Flag = MenuPausa( p_display );											// Devuelve CONTINUAR, VOLVER o SALIR	LIMPIAR EVENT QUEUE ANTES DE SALIR DE PAUSA
		else if( Flag == FIN ) break;
		al_flush_event_queue( *(p_event_queue) );
	}
	//if( Flag == FIN ) Flag = MenuNuevoPuntaje( &event_queue );
	MenuPuntajes( p_event_queue );
	
	Finalizar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales );
	//al_destroy_font( FuentePuntos );
	LiberarMemoria( &Ini );
	
	return Flag;
}

