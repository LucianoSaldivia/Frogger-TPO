#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int AlDrawTodo(Objeto **, float, float);
int AlInitTodo(ALLEGRO_TIMER **, ALLEGRO_TIMER **, ALLEGRO_DISPLAY **, ALLEGRO_EVENT_QUEUE **, Objeto **);
void AlDestroyTodo(ALLEGRO_TIMER **, ALLEGRO_TIMER **, ALLEGRO_DISPLAY **, ALLEGRO_EVENT_QUEUE **, Objeto **);
void LiberarTodo(Objeto **);

