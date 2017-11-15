#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/* Generales */	
char InicioGenerico( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );
void DestruirGenerico( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );

void TerminarDeAcomodarLista( Objeto **p_Ini );
void LiberarMemoria( Objeto **p_Ini );
void InicializarTimers( ALLEGRO_TIMER **p_timer1, ALLEGRO_TIMER **p_timer2 );


/* Especificas */
char Inicializar1vsC( ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer, ALLEGRO_TIMER **p_died_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key, char **p_PosicionesFinales );
	void CargarSprites1vsC( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora );
	void CargarKey1vsC( bool **p_key );
	void CargarPosicionesFinales1vsC( char **p_PosicionesFinales );
void Finalizar1vsC( ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer, ALLEGRO_TIMER **p_died_timer, ALLEGRO_BITMAP **VecFrog, bool **p_key, char **p_PosicionesFinales );
char AlistarObjetos1vsC( Objeto **p_Ini,  Objeto **p_ObjetoFrog, const char *RutaArchivo );
	char CargarDatosEnObjeto1vsC( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x );



char Inicializar1vs1( ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer_1, ALLEGRO_TIMER **p_sprites_timer_2, ALLEGRO_TIMER **p_died_timer_1, ALLEGRO_TIMER **p_died_timer_2, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key, char **p_PosicionesFinales );
	void CargarSprites1vs1( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora );
	void CargarKey1vs1( bool **p_key );
	void CargarPosicionesFinales1vs1( char **p_PosicionesFinales );
void Finalizar1vs1( ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer_1, ALLEGRO_TIMER **p_sprites_timer_2, ALLEGRO_TIMER **p_died_timer_1, ALLEGRO_TIMER **p_died_timer_2, ALLEGRO_BITMAP **VecFrog, bool **p_key, char **p_PosicionesFinales );
char AlistarObjetos1vs1( Objeto **p_Ini,  Objeto **p_ObjetoFrog_1, Objeto **p_ObjetoFrog_2, const char *RutaArchivo );
	char CargarDatosEnObjeto1vs1( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x );
