#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../inc/VariablesFrogger.h"
#include <allegro5/allegro.h>

int CrearArchivo( int Preguntas ){
	FILE *fp;
	char Cambiar = 'a', *DirMov, *StringAux;
	int Aux, Aux2, Alto = 40, Ancho;
	float FactorDistancia = 1.416666, Distancia, Velocidad, FactorDistancia2 = 2;
	
	DirMov = ( char * ) malloc( 10 * sizeof(char) );
		if( DirMov == NULL ) return -5;
 	StringAux = ( char * ) malloc ( 10 * sizeof(char) );
		if( StringAux == NULL ) return -5;
	
	fp = fopen("Archivos/ObjetosCreados.txt", "w");
	
	Cambiar = 'a';
	
	if( Preguntas >= 1 ){
		fprintf( stdout, "S o N \n\t Factor de distancia entre objetos en linea ( default > 1 ) = %f, Desea cambiar ?:", FactorDistancia );
		fscanf( stdin, " %c", &Cambiar );
		if( tolower( Cambiar ) == 's' ){
			fprintf( stdout, "\n\t Ingrese el factor distancia que quiere entre objetos:");
			fscanf( stdin, "%s", StringAux );
			FactorDistancia = atof( StringAux );
		}
	}
	
	Cambiar = 'a';
	
	if( Preguntas >= 2 ){
			fprintf( stdout, "S o N \n\t Factor de distancia entre objetos SEPARADOS en linea ( default > 1 ) = %f, Desea cambiar ?:", FactorDistancia2 );
		fscanf( stdin, " %c", &Cambiar );
		if( tolower( Cambiar ) == 's' ){
			fprintf( stdout, "\n\t Ingrese el factor distancia que quiere entre objetos:");
			fscanf( stdin, "%s", StringAux );
			FactorDistancia2 = atof( StringAux );
		}
	}
	
	fprintf(stderr, "\n\t No lo puedo creer \n");
		
	fprintf(fp, "Back\t1\tImagenes/Background.png\t0\t0\t0\t0\t0\n" );
	
	fprintf(stderr, "\n\t Antes de los fors \n");
	
	for( Aux = 1; Aux <= CANTIDAD_DE_CARRILES ; Aux++ ){
		al_rest( ( rand() % ( 1000 * 2 ) + 1000 * 0 ) / 1000 );
		Velocidad = ( rand() % ( 1000 * VELOCIDAD_MAXIMA ) + 1000 * VELOCIDAD_MINIMA ) / 1000;
		
		for( Aux2 = 1; Aux2 <= CANT_OBJ_POR_LINEA ; Aux2++ ){
			switch( Aux ){
				case 1:	//Tronco2
					strcpy( DirMov, "Der" );
					Ancho = 186;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia;
					else Distancia = Ancho * FactorDistancia;
					
					fprintf(fp, "Tronco2\t%d\tImagenes/Tronco2.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 2:	//Tortuga2
					strcpy( DirMov, "Izq" );
					Ancho = 104;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia;
					else Distancia = Ancho * FactorDistancia;					
					
					fprintf(fp, "Tortuga2\t%d\tImagenes/Tortuga2.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 3:	//Tronco3
					strcpy( DirMov, "Der" );
					Ancho = 284;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia;
					else Distancia = Ancho * FactorDistancia;
										
					fprintf(fp, "Tronco3\t%d\tImagenes/Tronco3.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 4:	//Tronco1
					strcpy( DirMov, "Der" );
					Ancho = 136;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia;
					else Distancia = Ancho * FactorDistancia;
										
					fprintf(fp, "Tronco1\t%d\tImagenes/Tronco1.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 5:	//Tortuga3
					strcpy( DirMov, "Izq" );
					Ancho = 156;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia;
					else Distancia = Ancho * FactorDistancia;
											
					fprintf(fp, "Tortuga3\t%d\tImagenes/Tortuga3.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 6:	//Auto1
					strcpy( DirMov, "Izq" );
					Ancho = 98;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia * 2;
					else Distancia = Ancho * FactorDistancia * 2;
											
					fprintf(fp, "Auto1\t%d\tImagenes/Auto1.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 7:	//Auto2
					strcpy( DirMov, "Der" );
					Ancho = 50;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia * 2;
					else Distancia = Ancho * FactorDistancia * 2;
											
					fprintf(fp, "Auto2\t%d\tImagenes/Auto2.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 8:	//Auto3
					strcpy( DirMov, "Izq" );
					Ancho = 58;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia * 2;
					else Distancia = Ancho * FactorDistancia * 2;
											
					fprintf(fp, "Auto3\t%d\tImagenes/Auto3.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 9:	//Auto4
					strcpy( DirMov, "Der" );
					Ancho = 50;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia * 2;
					else Distancia = Ancho * FactorDistancia * 2;
											
					fprintf(fp, "Auto4\t%d\tImagenes/Auto4.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;
				case 10://Auto5
					strcpy( DirMov, "Izq" );
					Ancho = 44;
					if( ( Aux2 % 3 ) == 1 ) Distancia = Ancho * FactorDistancia2 * FactorDistancia * 2;
					else Distancia = Ancho * FactorDistancia * 2;
											
					fprintf(fp, "Auto5\t%d\tImagenes/Auto5.png\t%s\t%f\t%d\t%d\t%f\n", Aux2, DirMov, Velocidad, Alto, Ancho, Distancia );
					break;	
			}	
		}	
	}
	fprintf(stderr, "\n\t Después los fors \n");
	
	fprintf(fp, "Frog\t1\tImagenes/RanaArriba.png\t0\t0\t0\t0\t0\n" );
	//fprintf(fp, "Frog\t2\tImagenes/Rana2Arriba.png\t0\t0\t0\t0\t0\n" );
	
	
	fprintf(fp, "FIN\t\n" );		/*ESTO ES CLAVE*/	
	
	fclose( fp );
	free( DirMov );
	free( StringAux );
	
	return 0;
}


