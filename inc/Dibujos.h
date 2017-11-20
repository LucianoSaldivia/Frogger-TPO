#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void DibujarParaMenu( ALLEGRO_BITMAP **MenuBack, ALLEGRO_BITMAP **Frog, ALLEGRO_FONT **FuenteTitulo, ALLEGRO_FONT **FuenteOpciones, ALLEGRO_FONT **FuenteAclaraciones, const char *TipoDeMenu, int Pos_x, int Pos_y );

void MoverTodo( Objeto **p_Ini, Objeto **p_ObjetoFrog );
void MoverTodo1vs1( Objeto **p_Ini, Objeto **p_ObjetoFrog_1, Objeto **p_ObjetoFrog_2 );


void RedibujarDesde( Objeto **p_DesdeAca );
void RedibujarDesdeConTexto1vsC( Objeto **p_DesdeAca, ALLEGRO_FONT **FuentePuntos, int *p_Puntos, int *p_Vidas );
void RedibujarDesdeConTexto1vs1( Objeto **p_DesdeAca, ALLEGRO_FONT **FuentePuntos, int *p_Puntos_1, int *p_Vidas_1, int *p_Puntos_2 ,int *p_Vidas_2 );

void DetectarColision( Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **p_died_timer, int *Vidas, bool *EstadoFrog, char ContadorSprites );

void FrogSeMurio( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, int *Vidas, bool *EstadoFrog );
void RevivirFrog1( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, bool *EstadoFrog );

char LeerPosFinal( Objeto **p_ObjetoFrog, char *PosicionesFinales );
char LeerPosFinal1vs1( Objeto **p_ObjetoFrog_1, Objeto **p_ObjetoFrog_2, char *PosicionesFinales, char *PosicionesOcupadas_1, char *PosicionesOcupadas_2 );

	char DameUnNuevoFrog( Objeto **p_ObjetoFrog, Objeto **p_NewFrog );
	void PonemeNewFrogEnLista( Objeto **p_ObjetoFrog, Objeto **p_NewFrog );

