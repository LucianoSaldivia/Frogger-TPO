#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

enum MisEstadosFlag {
	SALIR, VER_PUNTAJES, JUGAR, VOLVER, OvsC, OvsO_OFFLINE, OvsO_ONLINE, PAUSA, CONTINUAR, FIN_GANO, FIN_PERDIO
};

enum MisDirecciones{
	ARRIBA, ABAJO, IZQUIERDA, DERECHA, NO_HAY_DIRECCION
};

enum EstadosFrog{
	VIVO, MUERTO
};

enum MisPosicionesFinales{
	POS_1, POS_2, POS_3, POS_4, POS_5, VACIA, OCUPADA
};

#define ERROR -5

#define FPS 60
#define FRAME_RATE 1.0/FPS
#define SCREEN_W 720
#define SCREEN_H 730
#define FROG_SIZE 50
#define MAX_BOUNCE_X 11.0
#define MAX_BOUNCE_Y 13.0
#define FROG_RESTING_TIME 0.35
#define UPPER_OFFSET 62
#define LOWER_OFFSET 20
#define SIDE_OFFSET 9
#define CANT_SPRITES 10
#define TIEMPO_SALTO 0.05
#define TIEMPO_ENTRE_SPRITES (TIEMPO_SALTO/CANT_SPRITES)
#define TIEMPO_PARA_REVIVIR 2

#define Y_INI_FROG ( SCREEN_H - LOWER_OFFSET - FROG_SIZE )
#define X_INI_FROG ( ( SCREEN_W / 2.0 )  - ( FROG_SIZE / 2.0 ) )
#define DIF_FROG_COSA 4
#define FROG_TRANSPARENCY_PIX 20
#define BOUNCE_Y 50
#define BOUNCE_X 50
#define X_POS_1 28
#define X_POS_2 182
#define X_POS_3 336
#define X_POS_4 490
#define X_POS_5 644
#define MARGEN_SALTO_FINAL 12

#define LIM_SALTO_ARRIBA ( UPPER_OFFSET )
#define LIM_SALTO_ABAJO 660
#define LIM_SALTO_IZQUIERDA 36
#define LIM_SALTO_DERECHA 634

#define CANT_OBJ_POR_LINEA 6	//Multiplo de 3!
#define CANT_VIDAS_INICIALES 3
#define PUNTOS_POR_SALTO 150
#define CANTIDAD_DE_CARRILES 10
#define VELOCIDAD_MAXIMA 4
#define VELOCIDAD_MINIMA 1

/* MENUS */
#define ALTURA_LETRA_TITULO 58
#define ALTURA_LETRA_OPCIONES 42
#define ALTURA_LETRA_PUNTOS 26
#define ALTURA_LETRA_CHICA 10
#define Y_TITULO 172
#define Y_OPCIONES 332
#define Y_ACLARACIONES (SCREEN_H - 15)
#define SEPARACION_PUNTAJES 20
#define SEPARACION_OPCIONES 15

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

typedef struct Puntaje{
	char *Nombre;
	int Puntos;
	struct Puntaje *Sig;
}Puntaje;

