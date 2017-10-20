#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>


#define TiempoEntreFraps 0.02				
#define SCREEN_W 719						//Ancho de la ventana
#define SCREEN_H 701						//Alto de la ventana
#define FROG_SIZE 50 						// A L E R T A ! ! !  Tamaño de frog DEBE ser menor a BOUNCE_Y
#define MAX_BOUNCE_X 11.0				//Máxima cantidad de saltos en X
#define MAX_BOUNCE_Y 13.0				//Máxima cantidad de saltos en Y
#define FROG_RESTING_TIME 0.35			//Tiempo entre salto y salto
#define UPPER_OFFSET 0					//Corrimiento superior, por el borde de la imagen
#define TIEMPO_SPRITE 0.025
#define CANT_SPRITES 25
#define A_COSAS 60

#define BOUNCE_Y (SCREEN_H / (MAX_BOUNCE_Y+1))
#define BOUNCE_X (SCREEN_H / (MAX_BOUNCE_X+1))

#define Cant_Objetos 10

typedef struct objeto{
	ALLEGRO_BITMAP *Imagen;
	float Velocidad;
	float Ancho;
	float Pos_x;
	float Pos_y;
	struct objeto *Sig;
}objeto;


//(arriba la imagen tiene más borde "inutil" que abajo, en lugar de recortarla puse el offset, porque
//después ahí tenemos que agregar puntajes, vidas y cosas así)

