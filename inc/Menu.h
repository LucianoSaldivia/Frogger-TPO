#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

char Menu( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPrincipal( ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuJugar( ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPuntajes( ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPausa( ALLEGRO_DISPLAY **p_display );

char MenuNuevoPuntaje( Objeto **p_Ini, ALLEGRO_DISPLAY **p_display, int Puntos, const char *Titulo );
	char GuardarOrdenadoEnArchivo( char *NewNombre, int Puntos, const char *RutaArchivo );
	void LiberarMemoriaDePuntos( Puntaje *Ini );
	
char MenuPedirPuerto( ALLEGRO_DISPLAY **p_display, int *NPuerto );
int MenuEsperarJugador2( int *p_socketfd, int puerto );
char MenuPausaONLINE( ALLEGRO_DISPLAY **p_display, int socketfd, bool *key, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_sprites_timer_2 );
