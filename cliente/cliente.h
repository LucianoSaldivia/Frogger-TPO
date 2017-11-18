#define MY_EVENT_TYPE ALLEGRO_GET_EVENT_TYPE('S','O','C','K')

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_EXIT
};

typedef struct Teclas_2
{
    bool T_arriba,T_abajo, T_izquierda, T_derecha;
} Teclas_2;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}