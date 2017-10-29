#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYJUMPS {
	JUMP_UP, JUMP_DOWN, JUMP_LEFT, JUMP_RIGHT
};

#define FPS 60
#define FRAME_RATE 1.0/FPS
#define SCREEN_W 720
#define SCREEN_H 730
#define FROG_SIZE 50
#define MAX_BOUNCE_X 11.0
#define MAX_BOUNCE_Y 13.0
#define FROG_RESTING_TIME 0.35
#define UPPER_OFFSET 56
#define LOWER_OFFSET 20
#define CANT_SPRITES 5
#define TIEMPO_SPRITE 0.01
#define TIEMPO_ENTRE_SPRITES (TIEMPO_SPRITE/CANT_SPRITES)

#define Y_INI_FROG ( SCREEN_H - LOWER_OFFSET - FROG_SIZE )
#define X_INI_FROG ( ( SCREEN_W / 2.0 )  - ( FROG_SIZE / 2.0 ) )

#define BOUNCE_Y 50 //51
#define BOUNCE_X ( SCREEN_W / ( MAX_BOUNCE_X + 1 ) ) //casi 51

#define LIM_SALTO_ARRIBA ( BOUNCE_Y + UPPER_OFFSET )
#define LIM_SALTO_ABAJO ( SCREEN_H - FROG_SIZE - BOUNCE_Y )
#define LIM_SALTO_IZQUIERDA ( BOUNCE_X )
#define LIM_SALTO_DERECHA ( SCREEN_W - FROG_SIZE - BOUNCE_X )

#define CANT_OBJ_POR_LINEA 6	//Multiplo de 3!
#define CANTIDAD_DE_CARRILES 10
#define VELOCIDAD_MAXIMA 4
#define VELOCIDAD_MINIMA 1

typedef struct Objeto{
	char *Nombre;
	int Numero;
	char *DirImagen;
	char *DirMov;
	float Velocidad;
	float Alto;
	float Ancho;
	float Dif_x;
	float Pos_x;
	float Pos_y;
	ALLEGRO_BITMAP *Imagen;
	struct Objeto *Ant, *Sig;
}Objeto;
