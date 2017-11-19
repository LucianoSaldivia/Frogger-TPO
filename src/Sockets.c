#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../inc/VariablesFrogger.h"
#include "../inc/Inicializacion.h"
#include "../inc/Teclado.h"
#include "../inc/Saltos.h"
#include "../inc/Dibujos.h"
#include "../inc/Menu.h"
#include "../inc/Sockets.h"

int CrearSocket( int puerto ){	// Creamos el socket

	const int uno=1;
	struct sockaddr_in serverAddress;
	int sockfd;
	int clientfd;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd==-1) return ERROR;

	if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&uno, (socklen_t)( sizeof(uno) )) ) return ERROR;

	// cargamos parametros del socket
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(puerto);
    memset((&serverAddress.sin_zero), 0, 8);

	// bindeamos el puerto y escuchamos
    if(bind (sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress) ) < 0)
    	return ERROR;
    if(listen(sockfd, 5))
    	return ERROR;
    clientfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddressLen);
    if(clientfd < 0) return ERROR;
    return clientfd;
}

void dumpteclas( Teclas_2 NodoTeclas ) {	// Funcion para probar la llegada de las teclas
    if(NodoTeclas.T_arriba) {
        fprintf(stderr, "T_arriba = true\n");
    }else {
        fprintf(stderr, "T_arriba = false\n");
    }
    if(NodoTeclas.T_abajo) {
        fprintf(stderr, "T_abajo = true\n");
    }else {
        fprintf(stderr, "T_abajo = false\n");
    }
    if(NodoTeclas.T_izquierda) {
        fprintf(stderr, "T_izquierda = true\n");
    }else {
        fprintf(stderr, "T_izquierda = false\n");
    }
    if(NodoTeclas.T_derecha) {
        fprintf(stderr, "T_derecha = true\n");
    }else {
        fprintf(stderr, "T_derecha = false\n");
    }
}

int LeerDelSocket( int sockfd, bool *key, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer ) {
	int Salida = 0;
	Teclas_2 NodoTeclas;
	bool key_ant[4] = {0};
    
    NodoTeclas.T_arriba = false;
	NodoTeclas.T_abajo = false;
	NodoTeclas.T_izquierda = false;
	NodoTeclas.T_derecha = false;
	NodoTeclas.T_pausa = false;
	
	key_ant[KEY_UP] = key[KEY_2_UP];
	key_ant[KEY_DOWN] = key[KEY_2_DOWN];
	key_ant[KEY_LEFT] = key[KEY_2_LEFT];
	key_ant[KEY_RIGHT] = key[KEY_2_RIGHT];
    
	if( (Salida = recv(sockfd, &NodoTeclas, sizeof(NodoTeclas), MSG_DONTWAIT) ) > 0 ){
		// dumpteclas(NodoTeclas);
		key[KEY_2_UP] = NodoTeclas.T_arriba;
		key[KEY_2_DOWN] = NodoTeclas.T_abajo;
		key[KEY_2_LEFT] = NodoTeclas.T_izquierda;
		key[KEY_2_RIGHT] = NodoTeclas.T_derecha;
		
		if( NodoTeclas.T_pausa ) return 100;
		
		if( key[KEY_2_UP] && ! key_ant[KEY_UP] ) InicializarTimers( p_resting_timer, p_sprites_timer );
		if( key[KEY_2_DOWN] && ! key_ant[KEY_DOWN] ) InicializarTimers( p_resting_timer, p_sprites_timer );
		if( key[KEY_2_LEFT] && ! key_ant[KEY_LEFT] ) InicializarTimers( p_resting_timer, p_sprites_timer );
		if( key[KEY_2_RIGHT] && ! key_ant[KEY_RIGHT] ) InicializarTimers( p_resting_timer, p_sprites_timer );
		
		if( ! key[KEY_2_UP] && key_ant[KEY_UP] ) al_stop_timer( *(p_resting_timer) );
		if( ! key[KEY_2_DOWN] && key_ant[KEY_DOWN] ) al_stop_timer( *(p_resting_timer) );
		if( ! key[KEY_2_LEFT] && key_ant[KEY_LEFT] ) al_stop_timer( *(p_resting_timer) );
		if( ! key[KEY_2_RIGHT] && key_ant[KEY_RIGHT] ) al_stop_timer( *(p_resting_timer) );
	}
	
	return Salida;
}
