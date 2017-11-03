#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void DibujarParaMenu( ALLEGRO_BITMAP **MenuBack, ALLEGRO_BITMAP **Frog, ALLEGRO_FONT **FuenteTitulo, ALLEGRO_FONT **FuenteOpciones, ALLEGRO_FONT **FuenteAclaraciones, const char *TipoDeMenu, int Pos_x, int Pos_y );
void RedibujarDesde( Objeto **p_DesdeAca );

void DetectarColision( Objeto **p_Ini, Objeto **p_ObjetoFrog, ALLEGRO_BITMAP **Vec_Frog );

int ModuloDe( int Valor);
float ModuloDeFloat( float Valor);
