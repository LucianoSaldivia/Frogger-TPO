#define MY_EVENT_TYPE ALLEGRO_GET_EVENT_TYPE('S','O','C','K')
#define PAUSA_AUX 4
#define ERROR -5
#define ALTURA_LETRA_TITULO 58
#define ALTURA_LETRA_OPCIONES 42
#define ALTURA_LETRA_PUNTOS 24
#define ALTURA_LETRA_CHICA 10

#define SCREEN_W 720
#define SCREEN_H 730

char InicializarJugador2( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue );
char MenuPedir( ALLEGRO_DISPLAY **p_display, char *Output, const char *Titulo );
void error(const char *msg);

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_EXIT
};

enum MisEstadosFlag {
	SALIR, VER_PUNTAJES, JUGAR, VOLVER, OvsC, OvsO_OFFLINE, OvsO_ONLINE, PAUSA, CONTINUAR, FIN_GANO, FIN_PERDIO
};

typedef struct Teclas_2{
	bool T_arriba,T_abajo, T_izquierda, T_derecha, T_pausa;
} Teclas_2;

