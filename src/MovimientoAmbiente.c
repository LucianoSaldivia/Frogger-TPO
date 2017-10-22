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
		if( strstr(Act->DirMov, "Izq") ){
			if(Act->Pos_x <= - Act->Ancho){
				Act->Pos_x = SCREEN_W;
			}
				Act->Pos_x -= Act->Velocidad;
		}
		else if( strstr(Act->DirMov, "Der") ){
			if(Act->Pos_x >= SCREEN_W + Act->Ancho){
				Act->Pos_x = - Act->Ancho;
			}
			Act->Pos_x += Act->Velocidad;
		}			
		Act = Act->Sig;
	}
	AlDrawTodo(Ini, 0, 0);
}
