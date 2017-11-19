#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Dibujos.h"

void DibujarParaMenu( ALLEGRO_BITMAP **MenuBack, ALLEGRO_BITMAP **Frog, ALLEGRO_FONT **FuenteTitulo, ALLEGRO_FONT **FuenteOpciones, ALLEGRO_FONT **FuenteAclaraciones, const char *TipoDeMenu, int Pos_x, int Pos_y ){
	// Dibujamos lo necesario para el menu especificado
	
	char *ActNombre, *ActPuntaje, *NombreAMostrar;
	FILE* fp;
	int Contador = 1;
	
	if( strcmp( TipoDeMenu, "Principal" ) == 0 ){
		al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
		al_draw_bitmap( *(MenuBack), 0, 0, 0 );
		al_draw_text( *(FuenteTitulo), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_TITULO, ALLEGRO_ALIGN_CENTRE, "- FROGGER -");
		al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_OPCIONES, ALLEGRO_ALIGN_CENTRE, "Jugar");
		al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_OPCIONES + ALTURA_LETRA_OPCIONES + SEPARACION_OPCIONES, ALLEGRO_ALIGN_CENTRE, "Ver Puntajes");
		al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_OPCIONES + 2 * (ALTURA_LETRA_OPCIONES + SEPARACION_OPCIONES), ALLEGRO_ALIGN_CENTRE, "Salir");
		al_draw_text( *(FuenteAclaraciones), al_map_rgb( 0, 205, 50 ), 0, Y_ACLARACIONES, ALLEGRO_ALIGN_LEFT, " Para SELECCIONAR presione [ENTER] ");
		al_draw_bitmap( *(Frog), Pos_x, Pos_y, 0 );
		al_flip_display();		
	}
	else if( strcmp( TipoDeMenu, "Jugar" ) == 0 ){
		al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
		al_draw_bitmap( *(MenuBack), 0, 0, 0 );
		al_draw_text( *(FuenteTitulo), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_TITULO, ALLEGRO_ALIGN_CENTRE, "- FROGGER -");
		al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_OPCIONES, ALLEGRO_ALIGN_CENTRE, "1 vs C");	
		al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_OPCIONES + ALTURA_LETRA_OPCIONES + SEPARACION_OPCIONES, ALLEGRO_ALIGN_CENTRE, "1 vs 1 (Offline)");
		al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), ( SCREEN_W / 2 ), Y_OPCIONES + 2 * (ALTURA_LETRA_OPCIONES + SEPARACION_OPCIONES), ALLEGRO_ALIGN_CENTRE, "1 vs 1 (Online)");		
		al_draw_text( *(FuenteAclaraciones), al_map_rgb( 0, 205, 50 ), 0, Y_ACLARACIONES, ALLEGRO_ALIGN_LEFT, " Para SELECCIONAR presione [ENTER] ");
		al_draw_text( *(FuenteAclaraciones), al_map_rgb( 0, 205, 50 ), SCREEN_W, Y_ACLARACIONES, ALLEGRO_ALIGN_RIGHT, " Para VOLVER presione [Q/q] ");
		al_draw_bitmap( *(Frog), Pos_x, Pos_y, 0 );
		al_flip_display();		
	}
	
	else if( strcmp( TipoDeMenu, "Ver Puntajes" ) == 0 ){
		
		fp = fopen( "Archivos/Puntajes.txt", "r" );
			if( fp == NULL ){
				fprintf(stdout, "\n\n ERROR al intentar abrir Archivos/Puntajes.txt \n\n");
				return;
			}
		al_draw_bitmap( *(MenuBack), 0, 0, 0 );
		al_draw_text( *(FuenteAclaraciones), al_map_rgb( 0, 205, 50 ), SCREEN_W, Y_ACLARACIONES, ALLEGRO_ALIGN_RIGHT, " Para VOLVER presione [Q/q] ");
		al_flip_display();
		
		ActNombre = (char *) malloc( 50 * sizeof(char) );
			if( ActNombre == NULL ) return;
		ActPuntaje = (char *) malloc( 10 * sizeof(char) );
			if( ActPuntaje == NULL ) return;
		NombreAMostrar = (char *) malloc( 52 * sizeof(char) );
			if( NombreAMostrar == NULL ) return;
		
		
		while( fscanf( fp, "%[^\t]\t%[^\n]\n", ActNombre, ActPuntaje ) != EOF && Contador <= 9){
			
			strcpy( NombreAMostrar, "" );
			strcat( NombreAMostrar, "  " );
			strcat( NombreAMostrar, ActNombre );
			strcat( ActPuntaje, "  " );
			
			al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), 0, Pos_y, ALLEGRO_ALIGN_LEFT, NombreAMostrar );
			al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), SCREEN_W, Pos_y, ALLEGRO_ALIGN_RIGHT, ActPuntaje );	
			al_draw_bitmap( *(Frog), ( ( SCREEN_W / 2 ) - ( FROG_SIZE / 2 ) ), ( Pos_y - 10 ), 0 );	
			
			Pos_y += ALTURA_LETRA_OPCIONES + SEPARACION_PUNTAJES;
			
			
			strcpy( NombreAMostrar, "" );
			Contador ++;
		}
		
		al_flip_display();
		fclose( fp );
		free( ActNombre ); 
		free( ActPuntaje );
		free( NombreAMostrar ); 
	}
}


void MoverTodo( Objeto **p_Ini, Objeto **p_ObjetoFrog ){	// Mueve todos los objetos que deben moverse
	Objeto *Act, *Aux, *ObjetoFrog;
	int i;
		
	Act = *(p_Ini);
	ObjetoFrog = *p_ObjetoFrog;
	
	if( ObjetoFrog->Pos_y == 360 || ObjetoFrog->Pos_y == 660 || ObjetoFrog->Pos_y == 62 ) ObjetoFrog->Velocidad = 0;
	else if( ObjetoFrog->Pos_x >= ( SCREEN_W - FROG_SIZE ) && strstr( ObjetoFrog->DirMov, "Der" ) != NULL ) ObjetoFrog->Velocidad = 0;
	else if( ObjetoFrog->Pos_x <= 0 && strstr( ObjetoFrog->DirMov, "Izq" ) != NULL ) ObjetoFrog->Velocidad = 0;
	
	while( Act != NULL ){
		if( strstr( Act->DirMov, "Izq" ) != NULL ){
			if( Act->Pos_x <= - Act->Ancho ){
				if( Act->Numero == 1 ) {
					Aux = Act;
					i = 1;
					while( i != CANT_OBJ_POR_LINEA ){
						Aux = Aux->Sig;
						i++;
					}
					Act->Pos_x = Aux->Pos_x + Act->Dif_x;						
				}
				else Act->Pos_x = Act->Ant->Pos_x + Act->Dif_x;							//Para ciclo continuo
			}
			else Act->Pos_x -= Act->Velocidad;
		}
		else if( strstr( Act->DirMov, "Der" ) != NULL ){
			if( Act->Pos_x >= SCREEN_W ){
				if( Act->Numero == 1 ) {
					Aux = Act;
					i = 1;
					while( i != CANT_OBJ_POR_LINEA ){
						Aux = Aux->Sig;
						i++;
					}
					Act->Pos_x = Aux->Pos_x - Act->Dif_x;						
				}
				else Act->Pos_x = Act->Ant->Pos_x - Act->Dif_x;							//Para ciclo continuo
			}
			else Act->Pos_x += Act->Velocidad;
		}
		Act = Act->Sig;
	}	
}

void MoverTodo1vs1( Objeto **p_Ini, Objeto **p_ObjetoFrog_1, Objeto **p_ObjetoFrog_2 ){	// Mueve todos los objetos que deben moverse para 1sv1
	Objeto *Act, *Aux, *ObjetoFrog_1, *ObjetoFrog_2;
	int i;
		
	Act = *(p_Ini);
	ObjetoFrog_1 = *p_ObjetoFrog_1;
	ObjetoFrog_2 = *p_ObjetoFrog_2;
	
	if( ObjetoFrog_1->Pos_y == 360 || ObjetoFrog_1->Pos_y == 660 || ObjetoFrog_1->Pos_y == 62 ) ObjetoFrog_1->Velocidad = 0;
	else if( ObjetoFrog_1->Pos_x >= ( SCREEN_W - FROG_SIZE ) && strstr( ObjetoFrog_1->DirMov, "Der" ) != NULL ) ObjetoFrog_1->Velocidad = 0;
	else if( ObjetoFrog_1->Pos_x <= 0 && strstr( ObjetoFrog_1->DirMov, "Izq" ) != NULL ) ObjetoFrog_1->Velocidad = 0;
	
	if( ObjetoFrog_2->Pos_y == 360 || ObjetoFrog_2->Pos_y == 660 || ObjetoFrog_2->Pos_y == 62 ) ObjetoFrog_2->Velocidad = 0;
	else if( ObjetoFrog_2->Pos_x >= ( SCREEN_W - FROG_SIZE ) && strstr( ObjetoFrog_2->DirMov, "Der" ) != NULL ) ObjetoFrog_2->Velocidad = 0;
	else if( ObjetoFrog_2->Pos_x <= 0 && strstr( ObjetoFrog_2->DirMov, "Izq" ) != NULL ) ObjetoFrog_2->Velocidad = 0;
	
	while( Act != NULL ){
		if( strstr( Act->DirMov, "Izq" ) != NULL ){
			if( Act->Pos_x <= - Act->Ancho ){
				if( Act->Numero == 1 ) {
					Aux = Act;
					i = 1;
					while( i != CANT_OBJ_POR_LINEA ){
						Aux = Aux->Sig;
						i++;
					}
					Act->Pos_x = Aux->Pos_x + Act->Dif_x;						
				}
				else Act->Pos_x = Act->Ant->Pos_x + Act->Dif_x;							//Para ciclo continuo
			}
			else Act->Pos_x -= Act->Velocidad;
		}
		else if( strstr( Act->DirMov, "Der" ) != NULL ){
			if( Act->Pos_x >= SCREEN_W ){
				if( Act->Numero == 1 ) {
					Aux = Act;
					i = 1;
					while( i != CANT_OBJ_POR_LINEA ){
						Aux = Aux->Sig;
						i++;
					}
					Act->Pos_x = Aux->Pos_x - Act->Dif_x;						
				}
				else Act->Pos_x = Act->Ant->Pos_x - Act->Dif_x;							//Para ciclo continuo
			}
			else Act->Pos_x += Act->Velocidad;
		}
		Act = Act->Sig;
	}	
}

void RedibujarDesde( Objeto **p_DesdeAca ){	// Redibujamos la lista empezando por el objeto indicado
	Objeto *Act;
	
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	
	Act = *(p_DesdeAca);
	while(Act != NULL){
		al_draw_bitmap( Act->Imagen, Act->Pos_x, Act->Pos_y, 0 );
		Act = Act->Sig;
	}
}

void RedibujarDesdeConTexto1vsC( Objeto **p_DesdeAca, ALLEGRO_FONT **FuentePuntos, int *p_Puntos ,int *p_Vidas ){
	// Redibujamos la lista empezando por el objeto indicado, y mostramos datos de 1vsC
	
	char Aux1[1000], Aux2[1000];
	Objeto *Act;
	
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	Act = *(p_DesdeAca);
	while(Act != NULL){
		al_draw_bitmap( Act->Imagen, Act->Pos_x, Act->Pos_y, 0 );
		Act = Act->Sig;
	}
	sprintf( Aux1, "%d", ( *p_Puntos ) );
	strcpy( Aux2, " Puntuacion: " );
	strcat( Aux2, Aux1 );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), 0, 0, ALLEGRO_ALIGN_LEFT, Aux2 );
	sprintf( Aux1, "%d", ( *p_Vidas ) );
	strcpy( Aux2, "Vidas: " );
	strcat( Aux2, Aux1 );
	strcat( Aux2, " " );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT, Aux2 );
	
	al_flip_display();
}

void RedibujarDesdeConTexto1vs1( Objeto **p_DesdeAca, ALLEGRO_FONT **FuentePuntos, int *p_Puntos_1 ,int *p_Vidas_1, int *p_Puntos_2 ,int *p_Vidas_2 ){
	// Redibujamos la lista empezando por el objeto indicado, y mostramos datos de 1vs1
	
	int AlturaFuente = al_get_font_line_height( *(FuentePuntos) );
	char Aux1[1000], Aux2[1000];
	Objeto *Act;
	
	
	
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	Act = *(p_DesdeAca);
	while(Act != NULL){
		al_draw_bitmap( Act->Imagen, Act->Pos_x, Act->Pos_y, 0 );
		Act = Act->Sig;
	}
	
	strcpy( Aux2, "Puntuacion" );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), ( SCREEN_W / 2 ), 0, ALLEGRO_ALIGN_CENTRE, Aux2 );
	strcpy( Aux2, "Vidas" );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), ( SCREEN_W / 2 ), AlturaFuente, ALLEGRO_ALIGN_CENTRE, Aux2 );
	
	sprintf( Aux1, "%d", ( *p_Puntos_1 ) );
	strcpy( Aux2, "  " );
	strcat( Aux2, Aux1 );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), 0, 0, ALLEGRO_ALIGN_LEFT, Aux2 );
	sprintf( Aux1, "%d", ( *p_Vidas_1 ) );
	strcpy( Aux2, "  " );
	strcat( Aux2, Aux1 );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ),  0, AlturaFuente, ALLEGRO_ALIGN_LEFT, Aux2 );
	
	sprintf( Aux1, "%d", ( *p_Puntos_2 ) );
	strcpy( Aux2, Aux1 );
	strcat( Aux2, "  " );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT, Aux2 );
	sprintf( Aux1, "%d", ( *p_Vidas_2 ) );
	strcpy( Aux2, Aux1 );
	strcat( Aux2, "  " );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), SCREEN_W, AlturaFuente, ALLEGRO_ALIGN_RIGHT, Aux2 );
	
	al_flip_display();
}

void DetectarColision( Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **p_died_timer, int *Vidas, bool *EstadoFrog, char ContadorSprites ){
	// Detectamos choques con autos, y caidas al agua
	
	Objeto *Ini, *ObjetoFrog, *Act, *Aux = NULL;
	Ini = (*p_Ini)->Sig;
	ObjetoFrog = *p_ObjetoFrog;
	char CantidadDeNoColisiones = 0;
	
	/*		FILTRAMOS SOLO LAS POSICIONES NECESARIAS PARA ANALIZAR COLISIONES		*/	
	if( ObjetoFrog->Pos_y == UPPER_OFFSET || ObjetoFrog->Pos_y == 360 || ObjetoFrog->Pos_y == Y_INI_FROG ) return;
	
	Act = Ini;
	while( strstr( Act->Nombre, "Frog" ) == NULL ){
		if( Act->Pos_y == ObjetoFrog->Pos_y + DIF_FROG_COSA && Aux == NULL ) Aux = Act;		// Encontramos al primero que pasa por la linea donde está frog
		Act = Act->Sig;
	}
	Act = Aux;		
	if( Act != NULL ){
		do{
			//	Una vez encontrados los objetos de la linea, vemos si hay alguna colision
			// Nombre Numero RutaImgInicial DirecciónMovimiento Velocidad Alto Ancho Dif_x
			if( ( ObjetoFrog->Pos_x + FROG_SIZE - FROG_TRANSPARENCY_PIX ) >= Act->Pos_x  &&  ( ObjetoFrog->Pos_x + FROG_TRANSPARENCY_PIX ) <= ( Act->Pos_x + Act->Ancho )  ){		/* HAY COLISION */
				if( Act->Pos_y >= 400 ){ /* Colision con un auto */
					FrogSeMurio( &ObjetoFrog, VecFrog, p_died_timer, Vidas, EstadoFrog );
					return;
				}
				if( Act->Pos_y < 400 ){ /*Colision en agua*/
					ObjetoFrog->Velocidad = Act->Velocidad;
					strcpy( ObjetoFrog->DirMov, Act->DirMov );
					/*TODO BIEN EN EL AGUA*/
				}
			}
			else CantidadDeNoColisiones ++;	
			
			Act = Act->Sig;
		} while( Act->Numero > Act->Ant->Numero );
	}
	Act = Aux;
	
	if( CantidadDeNoColisiones == CANT_OBJ_POR_LINEA ){				/* No hubo colision */
		if( Act->Pos_y < 400 && ContadorSprites == 0 ){
			FrogSeMurio( &ObjetoFrog, VecFrog, p_died_timer, Vidas, EstadoFrog );
			return;
		}
	}
}


void FrogSeMurio( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, int *Vidas, bool *EstadoFrog ){
	// Mata la rana, le saca una vida, muestra su imagen muerta y le da un tiempo hasta revivir
	al_start_timer( *( died_timer ) );
	( *(p_ObjetoFrog) )->Imagen =  VecFrog[8];
	( *(p_ObjetoFrog) )->Velocidad = 0;
	( *(Vidas) ) --;
	( *(EstadoFrog) ) = MUERTO;
}

void RevivirFrog1( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, bool *EstadoFrog ){
	// Nos da una rana nueva
	
	al_stop_timer( *( died_timer ) );
	( *(p_ObjetoFrog) )->Imagen = VecFrog[0];
	( *(EstadoFrog) ) = VIVO;
	( *(p_ObjetoFrog) )->Velocidad = 0;
	if( strstr( (*p_ObjetoFrog)->Nombre, "Frog_1" ) != NULL ) ( *(p_ObjetoFrog) )->Pos_x = X_INI_FROG_1;
	else if( strstr( (*p_ObjetoFrog)->Nombre, "Frog_2" ) != NULL ) ( *(p_ObjetoFrog) )->Pos_x = X_INI_FROG_2;
	else ( *(p_ObjetoFrog) )->Pos_x = X_INI_FROG;
	( *(p_ObjetoFrog) )->Pos_y = Y_INI_FROG;
}


char LeerPosFinal( Objeto **p_ObjetoFrog, char *PosicionesFinales ){	// Busca posiciones finales ocupadas para 1vsC
	Objeto *NewFrog = NULL;
	bool FlagCambio = false;
	
	if( (*p_ObjetoFrog)->Pos_x == X_POS_1 ){
		PosicionesFinales[POS_1] = OCUPADA;
		FlagCambio = true;
	}
	else if( (*p_ObjetoFrog)->Pos_x == X_POS_2 ){
		PosicionesFinales[POS_2] = OCUPADA;
		FlagCambio = true;
	}
	else if( (*p_ObjetoFrog)->Pos_x == X_POS_3 ){
		PosicionesFinales[POS_3] = OCUPADA;
		FlagCambio = true;
	}
	else if( (*p_ObjetoFrog)->Pos_x == X_POS_4 ){
		PosicionesFinales[POS_4] = OCUPADA;
		FlagCambio = true;
	}
	else if( (*p_ObjetoFrog)->Pos_x == X_POS_5 ){
		PosicionesFinales[POS_5] = OCUPADA;
		FlagCambio = true;
	}
	
	if( PosicionesFinales[POS_1] == OCUPADA && PosicionesFinales[POS_2] == OCUPADA && PosicionesFinales[POS_3] == OCUPADA && PosicionesFinales[POS_4] == OCUPADA && PosicionesFinales[POS_5] == OCUPADA) return FIN_GANO;
	
	if( FlagCambio == true ){
		
		NewFrog = ( Objeto * ) malloc( sizeof( Objeto ) );
			if( NewFrog == NULL ){
				fprintf( stdout, "\n No hay memoria para NewFrog!\n" );
				return ERROR;
			}
		if( DameUnNuevoFrog( p_ObjetoFrog, &NewFrog ) == SALIR ) return SALIR;
		PonemeNewFrogEnLista( p_ObjetoFrog, &NewFrog );	
		( *(p_ObjetoFrog) ) = NewFrog;
	}
	return CONTINUAR;
 }

char LeerPosFinal1vs1( Objeto **p_ObjetoFrog_1, Objeto **p_ObjetoFrog_2, char *PosicionesFinales, char *PosicionesOcupadas_1, char *PosicionesOcupadas_2 ){	// Busca posiciones finales ocupadas para 1vs1
	Objeto *NewFrog = NULL, *ObjetoFrog_1, *ObjetoFrog_2;
	bool FlagCambio = false;
	
	ObjetoFrog_1 = *(p_ObjetoFrog_1);
	ObjetoFrog_2 = *(p_ObjetoFrog_2);
	
	if( ObjetoFrog_1->Pos_y == UPPER_OFFSET ){
		if( (*p_ObjetoFrog_1)->Pos_x == X_POS_1 ){
			PosicionesFinales[POS_1] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_1)->Pos_x == X_POS_2 ){
			PosicionesFinales[POS_2] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_1)->Pos_x == X_POS_3 ){
			PosicionesFinales[POS_3] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_1)->Pos_x == X_POS_4 ){
			PosicionesFinales[POS_4] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_1)->Pos_x == X_POS_5 ){
			PosicionesFinales[POS_5] = OCUPADA;
			FlagCambio = true;
		}
		
		if( FlagCambio == true ){
			
			NewFrog = ( Objeto * ) malloc( sizeof( Objeto ) );
				if( NewFrog == NULL ){
					fprintf( stdout, "\n No hay memoria para NewFrog!\n" );
					return ERROR;
				}
			if( DameUnNuevoFrog( p_ObjetoFrog_1, &NewFrog ) == SALIR ) return SALIR;
			PonemeNewFrogEnLista( p_ObjetoFrog_1, &NewFrog );	
			( *(p_ObjetoFrog_1) ) = NewFrog;
			
			(*(PosicionesOcupadas_1)) ++;
		}
		
		if( *(PosicionesOcupadas_1) == 3 ) return FIN_GANO;
	}
	
	else if( ObjetoFrog_2->Pos_y == UPPER_OFFSET ){
		if( (*p_ObjetoFrog_2)->Pos_x == X_POS_1 ){
			PosicionesFinales[POS_1] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_2)->Pos_x == X_POS_2 ){
			PosicionesFinales[POS_2] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_2)->Pos_x == X_POS_3 ){
			PosicionesFinales[POS_3] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_2)->Pos_x == X_POS_4 ){
			PosicionesFinales[POS_4] = OCUPADA;
			FlagCambio = true;
		}
		else if( (*p_ObjetoFrog_2)->Pos_x == X_POS_5 ){
			PosicionesFinales[POS_5] = OCUPADA;
			FlagCambio = true;
		}
				
		if( FlagCambio == true ){
			
			NewFrog = ( Objeto * ) malloc( sizeof( Objeto ) );
				if( NewFrog == NULL ){
					fprintf( stdout, "\n No hay memoria para NewFrog!\n" );
					return ERROR;
				}
			if( DameUnNuevoFrog( p_ObjetoFrog_2, &NewFrog ) == SALIR ) return SALIR;
			PonemeNewFrogEnLista( p_ObjetoFrog_2, &NewFrog );	
			( *(p_ObjetoFrog_2) ) = NewFrog;
			
			(*(PosicionesOcupadas_2)) ++;
		}

		if( *(PosicionesOcupadas_2) == 3 ) return FIN_PERDIO;

	}
	
	return CONTINUAR;
}

	char DameUnNuevoFrog( Objeto **p_ObjetoFrog, Objeto **p_NewFrog ){	// Pedimos un nuevo frog, ya que el anterior quedo en la posicion final
	Objeto *NewFrog = *(p_NewFrog);
	
	NewFrog->Nombre = (char *) malloc( 10 * sizeof(char) );
		if( NewFrog->Nombre == NULL ) return SALIR;
	NewFrog->DirImagen = (char *) malloc( 75 * sizeof(char) );
		if( NewFrog->DirImagen == NULL ) return SALIR;
	NewFrog->DirMov = (char *) malloc( 4 * sizeof(char) );
		if( NewFrog->DirMov == NULL ) return SALIR;
	
	strcpy( NewFrog->Nombre, (*p_ObjetoFrog)->Nombre );
	NewFrog->Numero = ( (*p_ObjetoFrog)->Numero + 1 );
	strcpy( NewFrog->DirImagen, (*p_ObjetoFrog)->DirImagen );
	strcpy( NewFrog->DirMov, "0" );
	NewFrog->Imagen = (*p_ObjetoFrog)->Imagen;
	NewFrog->Velocidad = 0;
	NewFrog->Alto = FROG_SIZE;
	NewFrog->Ancho = FROG_SIZE;
	NewFrog->Dif_x = 0;
	if( strstr( (*p_ObjetoFrog)->Nombre, "Frog_1" ) != NULL ) NewFrog->Pos_x = X_INI_FROG_1;
	else if( strstr( (*p_ObjetoFrog)->Nombre, "Frog_2" ) != NULL ) NewFrog->Pos_x = X_INI_FROG_2;
	else NewFrog->Pos_x = X_INI_FROG;
	NewFrog->Pos_y = Y_INI_FROG;
	NewFrog->Ant = NULL;
	NewFrog->Sig = NULL;
	
	return CONTINUAR;
}

	void PonemeNewFrogEnLista( Objeto **p_ObjetoFrog, Objeto **p_NewFrog ){	// Pone al frog nuevo en su lugar en la lista
	(*p_NewFrog)->Sig = (*p_ObjetoFrog)->Sig;
	(*p_ObjetoFrog)->Sig = (*p_NewFrog);
	(*p_NewFrog)->Ant = (*p_ObjetoFrog);
	if( (*p_NewFrog)->Sig != NULL ) (*p_NewFrog)->Sig->Ant = (*p_NewFrog);
}
