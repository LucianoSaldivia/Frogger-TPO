#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

char Jugador1ApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, char *Direccion, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer );
void Jugador1SoltoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer );








//void TeclaPresionadaJugador1(ALLEGRO_EVENT *, Objeto **, Objeto **, ALLEGRO_BITMAP **);
void TeclaPresionadaJugador1(ALLEGRO_EVENT *, bool **, Objeto **, Objeto **, ALLEGRO_BITMAP **);
void TeclaSoltadaJugador1(ALLEGRO_EVENT *, bool **);



/*
void Jugador1ApretoFlecha(ALLEGRO_EVENT *, bool **, ALLEGRO_TIMER **, Objeto **, Objeto **, ALLEGRO_BITMAP **);
void Jugador1SoltoFlecha(ALLEGRO_EVENT *, bool **, bool *, ALLEGRO_TIMER **);	
void Jugador1SigueApretandoFlecha(bool *, Objeto **, Objeto **, ALLEGRO_BITMAP **);
*/
