#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

	/*aaa*/
	/*fprintf(stderr, "\n Antes de saltar ");*/
	/*aaa*/

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYJUMPS {
	JUMP_UP, JUMP_DOWN, JUMP_LEFT, JUMP_RIGHT
};

#define FPS 60
#define FRAME_RATE 1.0/FPS
#define SCREEN_W 719
#define SCREEN_H 701
#define FROG_SIZE 50
#define MAX_BOUNCE_X 11.0
#define MAX_BOUNCE_Y 14.0
#define FROG_RESTING_TIME 0.35
#define UPPER_OFFSET 0
#define CANT_SPRITES 5
#define TIEMPO_SPRITE 0.01
#define TIEMPO_ENTRE_SPRITES ((TIEMPO_SPRITE/CANT_SPRITES)-0.001)

#define BOUNCE_Y ( (SCREEN_H+0) / (MAX_BOUNCE_X+1)) 
#define BOUNCE_X ( (SCREEN_H+0) / (MAX_BOUNCE_X+1))

#define LIM_SALTO_ARRIBA ( BOUNCE_Y + UPPER_OFFSET )
#define LIM_SALTO_ABAJO ( SCREEN_H - FROG_SIZE - BOUNCE_Y )
#define LIM_SALTO_IZQUIERDA ( BOUNCE_X )
#define LIM_SALTO_DERECHA ( SCREEN_W - FROG_SIZE - BOUNCE_X )



typedef struct Objeto{
	char *Nombre;
	int Numero;
	char *DirImagen;
	char *DirMov;
	float Velocidad;
	float Alto;
	float Ancho;
	float Pos_x;
	float Dif_x;
	float Pos_y;
	ALLEGRO_BITMAP *Imagen;
	struct Objeto *Sig;
}Objeto;
