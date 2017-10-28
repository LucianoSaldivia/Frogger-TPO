#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int AlDrawTodo(Objeto **, float, float);
void CargarSprites( ALLEGRO_BITMAP **, const char *);

int AlInitTodo(ALLEGRO_TIMER **, ALLEGRO_TIMER **, ALLEGRO_DISPLAY **, ALLEGRO_EVENT_QUEUE **, ALLEGRO_BITMAP ***, bool **);
void AlDestroyTodo(ALLEGRO_TIMER **, ALLEGRO_TIMER **, ALLEGRO_DISPLAY **, ALLEGRO_EVENT_QUEUE **, ALLEGRO_BITMAP ***, bool **);

int IniciarLista(Objeto **, Objeto **);
void LiberarTodo(Objeto **);

