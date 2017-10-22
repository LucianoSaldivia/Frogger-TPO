#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#define FPS 60
#define FRAME_RATE 1.0/FPS
#define SCREEN_W 719
#define SCREEN_H 701
#define FROG_SIZE 50
#define MAX_BOUNCE_X 11.0
#define MAX_BOUNCE_Y 13.0
#define FROG_RESTING_TIME 0.35
#define UPPER_OFFSET 0
#define TIEMPO_SPRITE 0.020
#define CANT_SPRITES 25

#define BOUNCE_Y (SCREEN_H / (MAX_BOUNCE_Y+1))
#define BOUNCE_X (SCREEN_H / (MAX_BOUNCE_X+1))

#define Cant_Objetos 10

typedef struct Objeto{
	char *Nombre;
	int Numero;
	char *DirImagen;
	char *DirMov;
	float Velocidad;
	float Alto;
	float Ancho;
	float Pos_x;
	float Pos_y;
	ALLEGRO_BITMAP *Imagen;
	struct Objeto *Sig;
}Objeto;
