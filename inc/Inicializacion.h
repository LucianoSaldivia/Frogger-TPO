#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

/* Generales */	
char InicioGenerico( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );
void DestruirGenerico( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );

void TerminarDeAcomodarLista( Objeto **p_Ini );
void LiberarMemoria( Objeto **p_Ini );
void InicializarTimers( ALLEGRO_TIMER **p_timer1, ALLEGRO_TIMER **p_timer2 );


/* Especificas */
char Inicializar1vsC( ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key );
	void CargarSprites1vsC( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora );
	void CargarKey1vsC( bool **p_key );
void Finalizar1vsC( ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_TIMER **p_sprites_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key );

char AlistarObjetos( Objeto **p_Ini,  Objeto **p_ObjetoFrog, const char *RutaArchivo );
	char CargarDatosEnObjeto1vsC( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x );
	/*char CargarDatosEnObjeto1vs1*/
	










int InicializarALLEGRO( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key );

void CargarSprites( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora );
void CargarKey( bool **p_key );

int EnlistarObjetos( Objeto **p_Ini,  Objeto **p_ObjetoFrog );
int CargarDatosEnObjeto( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x );

void FinalizarALLEGRO( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key );


