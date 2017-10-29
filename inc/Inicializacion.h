#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

void RedibujarDesde( Objeto **p_DesdeAca );
int InicializarALLEGRO( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key );

void CargarSprites( ALLEGRO_BITMAP ***p_VecFrog, const char *CarpetaContenedora );
void CargarKey( bool **p_key );

int EnlistarObjetos( Objeto **p_Ini,  Objeto **p_ObjetoFrog );
int CargarDatosEnObjeto( Objeto *New, char *Nombre, char *Numero, char *RutaImagen, char *DirMov, char *Velocidad, char *Alto, char *Ancho, char *Dif_x );
void TerminarDeAcomodarLista( Objeto **p_Ini );

void FinalizarALLEGRO( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_frames_timer, ALLEGRO_BITMAP ***p_VecFrog, bool **p_key );
void LiberarMemoria( Objeto **p_Ini );

void InicializarTimers( ALLEGRO_TIMER **Timer1, ALLEGRO_TIMER **Timer2 );

