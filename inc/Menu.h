#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

char Menu( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPrincipal( ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuJugar( ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPuntajes( ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPausa( ALLEGRO_DISPLAY **p_display );
