#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

char Jugador1ApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer );
void Jugador1SoltoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer );

char JugadorApretoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2, ALLEGRO_TIMER **p_sprites_timer_1, ALLEGRO_TIMER **p_sprites_timer_2 );
void JugadorSoltoTecla( ALLEGRO_EVENT *p_ev, bool *key, ALLEGRO_TIMER **p_resting_timer_1, ALLEGRO_TIMER **p_resting_timer_2 );
