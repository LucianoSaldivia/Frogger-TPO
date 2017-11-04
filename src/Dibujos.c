#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Dibujos.h"

void DibujarParaMenu( ALLEGRO_BITMAP **MenuBack, ALLEGRO_BITMAP **Frog, ALLEGRO_FONT **FuenteTitulo, ALLEGRO_FONT **FuenteOpciones, ALLEGRO_FONT **FuenteAclaraciones, const char *TipoDeMenu, int Pos_x, int Pos_y ){
	char *Nombre, *Puntaje, *NombreAMostrar;
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
		
		Nombre = (char *) malloc( 50 * sizeof(char) );
			if( Nombre == NULL ) return;
		Puntaje = (char *) malloc( 10 * sizeof(char) );
			if( Puntaje == NULL ) return;
		NombreAMostrar = (char *) malloc( 52 * sizeof(char) );
			if( NombreAMostrar == NULL ) return;
		
		fscanf( fp, "%[^\t]\t%[^\n]\n", Nombre, Puntaje );
		while( strstr( Nombre, "FIN" ) == NULL && Contador <= 9){
			
			strcpy( NombreAMostrar, "" );
			strcat( NombreAMostrar, "  " );
			strcat( NombreAMostrar, Nombre );
			strcat( Puntaje, "  " );
			
			al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), 0, Pos_y, ALLEGRO_ALIGN_LEFT, NombreAMostrar );
			al_draw_text( *(FuenteOpciones), al_map_rgb( 0, 205, 50 ), SCREEN_W, Pos_y, ALLEGRO_ALIGN_RIGHT, Puntaje );	
			al_draw_bitmap( *(Frog), ( ( SCREEN_W / 2 ) - ( FROG_SIZE / 2 ) ), ( Pos_y - 10 ), 0 );	
			
			Pos_y += ALTURA_LETRA_OPCIONES + SEPARACION_PUNTAJES;
			Contador ++;
			
			strcpy( NombreAMostrar, "" );
			fscanf( fp, "%[^\t]\t%[^\n]\n", Nombre, Puntaje );
		}
		
		al_flip_display();
		fclose( fp );
		free( Nombre ); 
		free( Puntaje );
		free( NombreAMostrar ); 
	}
}

void RedibujarDesde( Objeto **p_DesdeAca ){
	Objeto *Act;
	
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	
	Act = *(p_DesdeAca);
	while(Act != NULL){
		al_draw_bitmap( Act->Imagen, Act->Pos_x, Act->Pos_y, 0 ); //dibujamos todo con 0 flags
		Act = Act->Sig;
	}
	al_flip_display(); //mostramos
}
void RedibujarDesdeConTexto( Objeto **p_DesdeAca, ALLEGRO_FONT **FuentePuntos, int *p_Puntos ,int *p_Vidas ){
	char Aux1[1000], Aux2[1000];
	Objeto *Act;
	
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
	Act = *(p_DesdeAca);
	while(Act != NULL){
		al_draw_bitmap( Act->Imagen, Act->Pos_x, Act->Pos_y, 0 ); //dibujamos todo con 0 flags
		Act = Act->Sig;
	}
	sprintf( Aux1, "%d", ( *p_Puntos ) );
	strcpy( Aux2, " Score: " );
	strcat( Aux2, Aux1 );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), 0, 0, ALLEGRO_ALIGN_LEFT, Aux2 );
	sprintf( Aux1, "%d", ( *p_Vidas ) );
	strcpy( Aux2, "Vidas: " );
	strcat( Aux2, Aux1 );
	strcat( Aux2, " " );
	al_draw_text( *(FuentePuntos), al_map_rgb( 0, 0, 0 ), SCREEN_W, 0, ALLEGRO_ALIGN_RIGHT, Aux2 );
	
	al_flip_display();
}

void DetectarColision( Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **p_died_timer, int *Vidas, bool *EstadoFrog ){
	Objeto *Ini, *ObjetoFrog, *Act, *Aux = NULL;
	Ini = (*p_Ini)->Sig;
	ObjetoFrog = *p_ObjetoFrog;
	char CantidadDeNoColisiones = 0;
	
	/*		FILTRAMOS SOLO LAS POSICIONES NECESARIAS PARA ANALIZAR COLISIONES		*/	
	if( ObjetoFrog->Pos_y != 610 && ObjetoFrog->Pos_y != 560 && ObjetoFrog->Pos_y != 510 && ObjetoFrog->Pos_y != 460 && ObjetoFrog->Pos_y != 410 && ObjetoFrog->Pos_y != 310 && ObjetoFrog->Pos_y != 260 && ObjetoFrog->Pos_y != 210 && ObjetoFrog->Pos_y != 160 && ObjetoFrog->Pos_y != 110 ) return;
	
	Act = Ini;
	while( strstr( Act->Nombre, "Frog" ) == NULL ){
		if( Act->Pos_y == ObjetoFrog->Pos_y + DIF_FROG_COSA && Aux == NULL ) Aux = Act;		// Encontramos al primero que pasa por la linea donde está frog
		Act = Act->Sig;
	}
	Act = Aux;		
	
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
	Act = Aux;
	
	if( CantidadDeNoColisiones == CANT_OBJ_POR_LINEA ){				/* Si no hubo colision */
		/*if( Act->Pos_y >= 400 ){
				TODO BIEN EN EL ASFALTO;
			}*/
			if( Act->Pos_y < 400 ){
				FrogSeMurio( &ObjetoFrog, VecFrog, p_died_timer, Vidas, EstadoFrog );
				return;
			}
		}	
	
	
			
}

void FrogSeMurio( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, int *Vidas, bool *EstadoFrog ){
	al_start_timer( *( died_timer ) );
	( *(p_ObjetoFrog) )->Imagen =  VecFrog[8];
	( *(p_ObjetoFrog) )->Velocidad = 0;
	( *(Vidas) ) --;
	( *(EstadoFrog) ) = MUERTO;
}

void RevivirFrog1( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, bool *EstadoFrog ){
	al_stop_timer( *( died_timer ) );
	( *(p_ObjetoFrog) )->Imagen = VecFrog[0];
	( *(EstadoFrog) ) = VIVO;
	( *(p_ObjetoFrog) )->Velocidad = 0;
	( *(p_ObjetoFrog) )->Pos_x = X_INI_FROG;
	( *(p_ObjetoFrog) )->Pos_y = Y_INI_FROG;
}

char LeerPosFinal( Objeto **p_ObjetoFrog, char *PosicionesFinales ){
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
	
	if( PosicionesFinales[POS_1] == OCUPADA && PosicionesFinales[POS_2] == OCUPADA && PosicionesFinales[POS_3] == OCUPADA && PosicionesFinales[POS_4] == OCUPADA && PosicionesFinales[POS_5] == OCUPADA) return FIN;
	
	if( FlagCambio == true ){
		
		NewFrog = ( Objeto * ) malloc( sizeof( Objeto ) );
			if( NewFrog == NULL ){
				fprintf( stdout, "\n No hay memoria para NewFrog!\n" );
				return SALIR;
			}
		
		if( DameUnNuevoFrog( p_ObjetoFrog, &NewFrog ) == SALIR ) return SALIR;
		PonemeNewFrogEnLista( p_ObjetoFrog, &NewFrog );
		
		( *(p_ObjetoFrog) ) = NewFrog;
		
	}
	
	return CONTINUAR;
 }

	char DameUnNuevoFrog( Objeto **p_ObjetoFrog, Objeto **p_NewFrog ){
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
	NewFrog->Pos_x = X_INI_FROG;
	NewFrog->Pos_y = Y_INI_FROG;
	NewFrog->Ant = NULL;
	NewFrog->Sig = NULL;
	
	return CONTINUAR;
}

	void PonemeNewFrogEnLista( Objeto **p_ObjetoFrog, Objeto **p_NewFrog ){
	(*p_NewFrog)->Sig = (*p_ObjetoFrog)->Sig;
	(*p_ObjetoFrog)->Sig = (*p_NewFrog);
	(*p_NewFrog)->Ant = (*p_ObjetoFrog);
	if( (*p_NewFrog)->Sig != NULL ) (*p_NewFrog)->Sig->Ant = (*p_NewFrog);
}




int ModuloDeInt( int Valor){
	if( Valor < 0 ) Valor = Valor * ( - 1 );
return Valor;
}

float ModuloDeFloat( float Valor){
	if( Valor < 0 ) Valor = Valor * ( - 1 );
return Valor;
}

