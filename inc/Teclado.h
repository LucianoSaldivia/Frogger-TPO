#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

//void TeclaPresionadaJugador1(ALLEGRO_EVENT *, Objeto **, Objeto **, ALLEGRO_BITMAP **);
void TeclaPresionadaJugador1(ALLEGRO_EVENT *, bool **, Objeto **, Objeto **, ALLEGRO_BITMAP **);
void TeclaSoltadaJugador1(ALLEGRO_EVENT *, bool **);



void RanaSaltaArriba( Objeto **, Objeto **, ALLEGRO_BITMAP ** );
void RanaSaltaAbajo( Objeto **, Objeto **, ALLEGRO_BITMAP ** );
void RanaSaltaIzquierda( Objeto **, Objeto **, ALLEGRO_BITMAP ** );
void RanaSaltaDerecha( Objeto **, Objeto **, ALLEGRO_BITMAP ** );

/*
void Jugador1ApretoFlecha(ALLEGRO_EVENT *, bool **, ALLEGRO_TIMER **, Objeto **, Objeto **, ALLEGRO_BITMAP **);
void Jugador1SoltoFlecha(ALLEGRO_EVENT *, bool **, bool *, ALLEGRO_TIMER **);	
void Jugador1SigueApretandoFlecha(bool *, Objeto **, Objeto **, ALLEGRO_BITMAP **);
*/
