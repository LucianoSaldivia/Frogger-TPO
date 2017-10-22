#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/AlTodo.h"
#include "../inc/MovimientoAmbiente.h"

void MoverCosas(Objeto **Ini){			//Agregar un Objeto *Ant, para poder poner bien la posicion nueva una vez que un objeto pasa el rango visible
	Objeto *Act, *Ant;
	
	Act = *(Ini);
	while(Act != NULL){
		if( strstr(Act->DirMov, "Izq") ){
			if(Act->Pos_x <= - Act->Ancho){
				if( Act->Numero == 1 ){//Ver que pasa
					Act->Pos_x = Act->Sig->Pos_x + Act->Sig->Dif_x;
				}
				if( Act->Numero == 2 ){
					Act->Pos_x = Ant->Pos_x + Act->Dif_x;					
				}
			}
			else Act->Pos_x -= Act->Velocidad;
		}
		else if( strstr(Act->DirMov, "Der") ){
			if(Act->Pos_x >= SCREEN_W){
				if( Act->Numero == 1 ){//Ver que pasa
					Act->Pos_x = Act->Sig->Pos_x - Act->Sig->Dif_x;
				}
				if( Act->Numero == 2 ){
					Act->Pos_x = Ant->Pos_x - Act->Dif_x;
				}
			}
			else Act->Pos_x += Act->Velocidad;
		}			
		Ant = Act;
		Act = Act->Sig;
	}
	AlDrawTodo(Ini, 0, 0);
}
