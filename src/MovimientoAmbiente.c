#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/AlTodo.h"
#include "../inc/MovimientoAmbiente.h"

void MoverAlgo(Objeto **Ini){
	int aux;
	Objeto *Act;
	
	Act = *(Ini);
	for(aux = 1; aux < 4; aux++){
		Act = Act->Sig;
	}
	Act->Pos_x += Act->Velocidad;
	AlDrawTodo(Ini, 0, 0);
}

void MoverCosas(Objeto **Ini){
	Objeto *Act;
	
	Act = *(Ini);
	while(Act != NULL){
		/*aaaaa*/
		fprintf(stderr, "\n\t Entró al while \n");
		/*aaaaa*/
		if( strstr(Act->Nombre, "Background") == NULL && strstr(Act->Nombre, "Frog") == NULL){
			if( Act->Numero % 2 != 0 ){  															// SE PONEN LOS IMPARES PARA PROBAR MOVER 1,3y5 <---  y 2y4 --->
				/*aaaaa*/
				fprintf(stderr, "\n\t Hizo Algo \n");
				/*aaaaa*/
				if(Act->Pos_x <= - Act->Ancho){
					Act->Pos_x = SCREEN_W + 1;
				}
					Act->Pos_x -= Act->Velocidad;
			}
			else{
				/*aaaaa*/
				fprintf(stderr, "\n\t Hizo Algo \n");
				/*aaaaa*/

				if(Act->Pos_x >= SCREEN_W + Act->Ancho){
					Act->Pos_x = - Act->Ancho;
				}
				Act->Pos_x += Act->Velocidad;
			}
			
		}		
		Act = Act->Sig;
	}
	AlDrawTodo(Ini, 0, 0);
}
