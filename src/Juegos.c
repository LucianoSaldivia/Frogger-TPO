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
	Objeto *Ini = NULL, *ObjetoFrog = NULL;
	bool *key = NULL, EstadoFrog = VIVO;
	char Flag = CONTINUAR, Direccion = NO_HAY_DIRECCION, ContadorSprites = 0, *PosicionesFinales = NULL;
	int Vidas = CANT_VIDAS_INICIALES, Puntos = 0;
	
	if( Inicializar1vsC( p_event_queue, &resting_timer, &frames_timer, &sprites_timer, &died_timer, &VecFrog, &key, &PosicionesFinales ) == ERROR ) return ERROR;
	
	if( AlistarObjetos1vsC( &Ini, &ObjetoFrog, "Archivos/Objetos1vsC.txt" ) == ERROR ){
		Finalizar1vsC( &resting_timer, &frames_timer, &sprites_timer, &died_timer, VecFrog, &key, &PosicionesFinales );
		LiberarMemoria( &Ini );
		return ERROR;
	}
	
	FuentePuntos = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_PUNTOS, 0 );
	al_start_timer( frames_timer );
		
	while( Flag != SALIR && Flag != VOLVER ){							// VOLVER = VOLVER AL MENU PRINCIPAL
		while( Flag != ERROR && Flag != PAUSA && Flag != FIN_PERDIO && Flag != FIN_GANO ){											//Juego
			ALLEGRO_EVENT ev;
			al_wait_for_event( *(p_event_queue), &ev);
			
			if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
				Flag = SALIR;
				break;
			}
			
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
					RedibujarDesdeConTexto1vsC( &Ini, &FuentePuntos, &Puntos, &Vidas );
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
								if( ( ContadorSprites == 0 && ObjetoFrog->Pos_y > LIM_SALTO_ARRIBA ) || ContadorSprites != 0 ) RanaSaltaArriba( &ObjetoFrog, VecFrog, &ContadorSprites, PosicionesFinales );
								else Direccion = NO_HAY_DIRECCION;
								break;
							case ABAJO:
								if( ( ContadorSprites == 0 && ObjetoFrog->Pos_y < LIM_SALTO_ABAJO ) || ContadorSprites != 0 ) RanaSaltaAbajo( &ObjetoFrog, VecFrog, &ContadorSprites );
								else Direccion = NO_HAY_DIRECCION;
								break;
							case IZQUIERDA:
								if( ( ContadorSprites == 0 && ObjetoFrog->Pos_x > LIM_SALTO_IZQUIERDA ) || ContadorSprites != 0 ) RanaSaltaIzquierda( &ObjetoFrog, VecFrog, &ContadorSprites );
								else Direccion = NO_HAY_DIRECCION;
								break;
							case DERECHA:
								if( ( ContadorSprites == 0 && ObjetoFrog->Pos_x < LIM_SALTO_DERECHA )  || ContadorSprites != 0 ) RanaSaltaDerecha( &ObjetoFrog, VecFrog, &ContadorSprites );
								else Direccion = NO_HAY_DIRECCION;
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
	if( Flag == FIN_GANO ) Flag = MenuNuevoPuntaje( &Ini, p_display, Puntos, "Ganaste !" );
	else if( Flag == FIN_PERDIO ) Flag = MenuNuevoPuntaje( &Ini, p_display, Puntos, "Perdiste..." );
	
	//if( Flag != SALIR && Flag != ERROR && Flag != VOLVER ) Flag = MenuPuntajes( p_event_queue );
	
	al_destroy_font( FuentePuntos );
	LiberarMemoria( &Ini );
	Finalizar1vsC( &resting_timer, &frames_timer, &sprites_timer, &died_timer, VecFrog, &key, &PosicionesFinales );
	
	return Flag;
}

char Juego1vs1_OFFLINE( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue ){
	ALLEGRO_TIMER *resting_timer_1 = NULL, *resting_timer_2 = NULL, *frames_timer = NULL, *sprites_timer_1 = NULL, *sprites_timer_2 = NULL, *died_timer_1 = NULL, *died_timer_2 = NULL;
	ALLEGRO_BITMAP **VecFrog = NULL;
	ALLEGRO_FONT *FuentePuntos = NULL;
	Objeto *Ini = NULL, *ObjetoFrog_1 = NULL, *ObjetoFrog_2 = NULL;
	bool *key = NULL, EstadoFrog_1 = VIVO, EstadoFrog_2 = VIVO;
	char Flag = CONTINUAR, Direccion_1 = NO_HAY_DIRECCION, Direccion_2 = NO_HAY_DIRECCION, ContadorSprites_1 = 0, ContadorSprites_2 = 0, *PosicionesFinales = NULL, PosicionesOcupadas_1 = 0, PosicionesOcupadas_2 = 0;
	int Vidas_1 = CANT_VIDAS_INICIALES, Vidas_2 = CANT_VIDAS_INICIALES, Puntos_1 = 0, Puntos_2 = 0;
	
	if( Inicializar1vs1( p_event_queue, &resting_timer_1, &resting_timer_2, &frames_timer, &sprites_timer_1, &sprites_timer_2, &died_timer_1, &died_timer_2, &VecFrog, &key, &PosicionesFinales ) == ERROR ) return ERROR;
	
	if( AlistarObjetos1vs1( &Ini, &ObjetoFrog_1, &ObjetoFrog_2, "Archivos/Objetos1vs1.txt" ) == ERROR ){
		Finalizar1vs1( &resting_timer_1, &resting_timer_2, &frames_timer, &sprites_timer_1, &sprites_timer_2, &died_timer_1, &died_timer_2, VecFrog, &key, &PosicionesFinales );
		LiberarMemoria( &Ini );
		return ERROR;
	}
	
	FuentePuntos = al_load_ttf_font( "Fuente/KeeponTruckin.ttf", ALTURA_LETRA_PUNTOS, 0 );
	al_start_timer( frames_timer );
		
	while( Flag != SALIR && Flag != VOLVER ){							// VOLVER = VOLVER AL MENU PRINCIPAL
		while( Flag != ERROR && Flag != PAUSA && Flag != FIN_PERDIO && Flag != FIN_GANO ){											//Juego
			ALLEGRO_EVENT ev;
			al_wait_for_event( *(p_event_queue), &ev);
			
			if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
				Flag = SALIR;
				break;
			}
			
			else if( ev.type == ALLEGRO_EVENT_KEY_DOWN ){
				Flag = JugadorApretoTecla( &ev, key, &resting_timer_1, &resting_timer_2, &sprites_timer_1, &sprites_timer_2 );
				if( Direccion_1 == NO_HAY_DIRECCION ){
					if( EstadoFrog_1 == VIVO ){
						if( key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion_1 = ARRIBA;
						if( key[KEY_DOWN] && ! key[KEY_UP] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion_1 = ABAJO;
						if( key[KEY_LEFT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_RIGHT] ) Direccion_1 = IZQUIERDA;
						if( key[KEY_RIGHT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] ) Direccion_1 = DERECHA;
					}
				}
				if( Direccion_2 == NO_HAY_DIRECCION ){
					if( EstadoFrog_2 == VIVO ){
						if( key[KEY_2_UP] && ! key[KEY_2_DOWN] && ! key[KEY_2_LEFT] && ! key[KEY_2_RIGHT] ) Direccion_2 = ARRIBA;
						if( key[KEY_2_DOWN] && ! key[KEY_2_UP] && ! key[KEY_2_LEFT] && ! key[KEY_2_RIGHT] ) Direccion_2 = ABAJO;
						if( key[KEY_2_LEFT] && ! key[KEY_2_UP] && ! key[KEY_2_DOWN] && ! key[KEY_2_RIGHT] ) Direccion_2 = IZQUIERDA;
						if( key[KEY_2_RIGHT] && ! key[KEY_2_UP] && ! key[KEY_2_DOWN] && ! key[KEY_2_LEFT] ) Direccion_2 = DERECHA;
					}
				}
			}
			
			else if( ev.type == ALLEGRO_EVENT_KEY_UP ){
				JugadorSoltoTecla( &ev, key, &resting_timer_1, &resting_timer_2 );
			}
			
			else if( ev.type == ALLEGRO_EVENT_TIMER ){
				if( ev.timer.source == frames_timer ){
					if( Vidas_1 == 0 ) Flag = FIN_PERDIO;
					else if( Vidas_2 == 0 ) Flag = FIN_GANO;
					MoverTodo1vs1( &Ini, &ObjetoFrog_1, &ObjetoFrog_2 );
					if( EstadoFrog_1 == VIVO ) DetectarColision( &Ini, &ObjetoFrog_1, VecFrog, &died_timer_1, &Vidas_1, &EstadoFrog_1, ContadorSprites_1 );
					if( EstadoFrog_2 == VIVO ) DetectarColision( &Ini, &ObjetoFrog_2, VecFrog, &died_timer_2, &Vidas_2, &EstadoFrog_2, ContadorSprites_2 );
					if( ObjetoFrog_1->Pos_y == UPPER_OFFSET || ObjetoFrog_2->Pos_y == UPPER_OFFSET ) Flag = LeerPosFinal1vs1( &ObjetoFrog_1, &ObjetoFrog_2, PosicionesFinales, &PosicionesOcupadas_1, &PosicionesOcupadas_2 );
					RedibujarDesdeConTexto1vs1( &Ini, &FuentePuntos, &Puntos_1, &Vidas_1, &Puntos_2, &Vidas_2 );
				}
				else if( ev.timer.source == died_timer_1 ){
					RevivirFrog1( &ObjetoFrog_1, VecFrog, &died_timer_1, &EstadoFrog_1 );
				}
				else if( ev.timer.source == died_timer_2 ){
					RevivirFrog1( &ObjetoFrog_2, ( VecFrog + 9 ), &died_timer_2, &EstadoFrog_2 );
				}
				else if( ev.timer.source == resting_timer_1 ){
					al_start_timer( sprites_timer_1 );
					if( key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion_1 = ARRIBA;
					if( key[KEY_DOWN] && ! key[KEY_UP] && ! key[KEY_LEFT] && ! key[KEY_RIGHT] ) Direccion_1 = ABAJO;
					if( key[KEY_LEFT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_RIGHT] ) Direccion_1 = IZQUIERDA;
					if( key[KEY_RIGHT] && ! key[KEY_UP] && ! key[KEY_DOWN] && ! key[KEY_LEFT] ) Direccion_1 = DERECHA;
				}
				else if( ev.timer.source == resting_timer_2 ){
					al_start_timer( sprites_timer_2 );
					if( key[KEY_2_UP] && ! key[KEY_2_DOWN] && ! key[KEY_2_LEFT] && ! key[KEY_2_RIGHT] ) Direccion_2 = ARRIBA;
					if( key[KEY_2_DOWN] && ! key[KEY_2_UP] && ! key[KEY_2_LEFT] && ! key[KEY_2_RIGHT] ) Direccion_2 = ABAJO;
					if( key[KEY_2_LEFT] && ! key[KEY_2_UP] && ! key[KEY_2_DOWN] && ! key[KEY_2_RIGHT] ) Direccion_2 = IZQUIERDA;
					if( key[KEY_2_RIGHT] && ! key[KEY_2_UP] && ! key[KEY_2_DOWN] && ! key[KEY_2_LEFT] ) Direccion_2 = DERECHA;
				}
				
				else if( ev.timer.source == sprites_timer_1 && Direccion_1 != NO_HAY_DIRECCION ){
					if( ContadorSprites_1 < CANT_SPRITES && EstadoFrog_1 == VIVO ){
						switch( Direccion_1 ){
							case ARRIBA:
								if( ( ContadorSprites_1 == 0 && ObjetoFrog_1->Pos_y > LIM_SALTO_ARRIBA ) || ContadorSprites_1 != 0 ) RanaSaltaArriba( &ObjetoFrog_1, VecFrog, &ContadorSprites_1, PosicionesFinales );
								else Direccion_1 = NO_HAY_DIRECCION;
								break;
							case ABAJO:
								if( ( ContadorSprites_1 == 0 && ObjetoFrog_1->Pos_y < LIM_SALTO_ABAJO ) || ContadorSprites_1 != 0 ) RanaSaltaAbajo( &ObjetoFrog_1, VecFrog, &ContadorSprites_1 );
								else Direccion_1 = NO_HAY_DIRECCION;
								break;
							case IZQUIERDA:
								if( ( ContadorSprites_1 == 0 && ObjetoFrog_1->Pos_x > LIM_SALTO_IZQUIERDA ) || ContadorSprites_1 != 0 ) RanaSaltaIzquierda( &ObjetoFrog_1, VecFrog, &ContadorSprites_1 );
								else Direccion_1 = NO_HAY_DIRECCION;
								break;
							case DERECHA:
								if( ( ContadorSprites_1 == 0 && ObjetoFrog_1->Pos_x < LIM_SALTO_DERECHA )  || ContadorSprites_1 != 0 ) RanaSaltaDerecha( &ObjetoFrog_1, VecFrog, &ContadorSprites_1 );
								else Direccion_1 = NO_HAY_DIRECCION;
								break;
						}
						if( ContadorSprites_1 == CANT_SPRITES ) {
							al_stop_timer( sprites_timer_1 );
							ContadorSprites_1 = 0;
							if( Direccion_1 == ARRIBA ) Puntos_1 += PUNTOS_POR_SALTO;
							Direccion_1 = NO_HAY_DIRECCION;
						}
					}
				}
				else if( ev.timer.source == sprites_timer_2 && Direccion_2 != NO_HAY_DIRECCION ){
					if( ContadorSprites_2 < CANT_SPRITES && EstadoFrog_2 == VIVO ){
						switch( Direccion_2 ){
							case ARRIBA:
								if( ( ContadorSprites_2 == 0 && ObjetoFrog_2->Pos_y > LIM_SALTO_ARRIBA ) || ContadorSprites_2 != 0 ) RanaSaltaArriba( &ObjetoFrog_2, ( VecFrog + 9), &ContadorSprites_2, PosicionesFinales );
								else Direccion_2 = NO_HAY_DIRECCION;
								break;
							case ABAJO:
								if( ( ContadorSprites_2 == 0 && ObjetoFrog_2->Pos_y < LIM_SALTO_ABAJO ) || ContadorSprites_2 != 0 ) RanaSaltaAbajo( &ObjetoFrog_2, ( VecFrog + 9), &ContadorSprites_2 );
								else Direccion_2 = NO_HAY_DIRECCION;
								break;
							case IZQUIERDA:
								if( ( ContadorSprites_2 == 0 && ObjetoFrog_2->Pos_x > LIM_SALTO_IZQUIERDA ) || ContadorSprites_2 != 0 ) RanaSaltaIzquierda( &ObjetoFrog_2, ( VecFrog + 9), &ContadorSprites_2 );
								else Direccion_2 = NO_HAY_DIRECCION;
								break;
							case DERECHA:
								if( ( ContadorSprites_2 == 0 && ObjetoFrog_2->Pos_x < LIM_SALTO_DERECHA )  || ContadorSprites_2 != 0 ) RanaSaltaDerecha( &ObjetoFrog_2, ( VecFrog + 9), &ContadorSprites_2 );
								else Direccion_2 = NO_HAY_DIRECCION;
								break;
						}
						if( ContadorSprites_2 == CANT_SPRITES ) {
							al_stop_timer( sprites_timer_2 );
							ContadorSprites_2 = 0;
							if( Direccion_2 == ARRIBA ) Puntos_2 += PUNTOS_POR_SALTO;
							Direccion_2 = NO_HAY_DIRECCION;
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
	if( Flag == FIN_GANO ){
		Flag = MenuNuevoPuntaje( &Ini, p_display, Puntos_1, "Jugador 1 GANO !" );
		if( Flag != SALIR && Flag != ERROR && Flag != VOLVER ) Flag = MenuPuntajes( p_event_queue );
	}
	else if( Flag == FIN_PERDIO ){
		Flag = MenuNuevoPuntaje( &Ini, p_display, Puntos_2, "Jugador 2 GANO !" );
		if( Flag != SALIR && Flag != ERROR && Flag != VOLVER ) Flag = MenuPuntajes( p_event_queue );
	}
	
	al_destroy_font( FuentePuntos );
	LiberarMemoria( &Ini );
	Finalizar1vs1( &resting_timer_1, &resting_timer_2, &frames_timer, &sprites_timer_1, &sprites_timer_2, &died_timer_1, &died_timer_2, VecFrog, &key, &PosicionesFinales );	

	return Flag;
}

