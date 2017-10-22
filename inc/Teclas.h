#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int HayQueRedibujar(bool *, bool *, ALLEGRO_TIMER **, ALLEGRO_TIMER **, ALLEGRO_DISPLAY **, ALLEGRO_EVENT_QUEUE **, Objeto **);
void Jugador1ApretoFlecha(ALLEGRO_EVENT *, bool *, bool *, bool *, ALLEGRO_TIMER **, Objeto **);
void Jugador1SoltoFlecha(ALLEGRO_EVENT *, bool *, bool *, ALLEGRO_TIMER **);	
void Jugador1SigueApretandoFlecha(ALLEGRO_EVENT *, bool *, bool *, bool *, Objeto **);

