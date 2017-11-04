#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void DibujarParaMenu( ALLEGRO_BITMAP **MenuBack, ALLEGRO_BITMAP **Frog, ALLEGRO_FONT **FuenteTitulo, ALLEGRO_FONT **FuenteOpciones, ALLEGRO_FONT **FuenteAclaraciones, const char *TipoDeMenu, int Pos_x, int Pos_y );
void RedibujarDesde( Objeto **p_DesdeAca );
void MostrarPuntos( ALLEGRO_FONT **FuentePuntos, int *p_Puntos );
void MostrarTodo( ALLEGRO_FONT **FuentePuntos, int *p_Puntos, Objeto **p_DesdeAca );


void DetectarColision( Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, int *Vidas, bool *EstadoFrog );

void FrogSeMurio( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, int *Vidas, bool *EstadoFrog );
void RevivirFrog1( Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **VecFrog, ALLEGRO_TIMER **died_timer, bool *EstadoFrog );
char LeerPosFinal( Objeto **p_ObjetoFrog, char *PosicionesFinales );
char DameUnNuevoFrog( Objeto **p_ObjetoFrog, Objeto **p_NewFrog );
void PonemeNewFrogEnLista( Objeto **p_ObjetoFrog, Objeto **p_NewFrog );

int ModuloDeInt( int Valor);
float ModuloDeFloat( float Valor);
