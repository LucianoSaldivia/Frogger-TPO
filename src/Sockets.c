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



int CrearSocket( int puerto ){

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

void dumpteclas( Teclas_2 tmp ) {
    if(tmp.T_arriba) {
        fprintf(stderr, "T_arriba = true\n");
    }else {
        fprintf(stderr, "T_arriba = false\n");
    }
    if(tmp.T_abajo) {
        fprintf(stderr, "T_abajo = true\n");
    }else {
        fprintf(stderr, "T_abajo = false\n");
    }
    if(tmp.T_izquierda) {
        fprintf(stderr, "T_izquierda = true\n");
    }else {
        fprintf(stderr, "T_izquierda = false\n");
    }
    if(tmp.T_derecha) {
        fprintf(stderr, "T_derecha = true\n");
    }else {
        fprintf(stderr, "T_derecha = false\n");
    }
}

int LeerDelSocket( int sockfd, bool *key, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer ) {
	int Salida = 0;
	Teclas_2 tmp;
	bool key_ant[4] = {0};
    
    tmp.T_arriba = false;
	tmp.T_abajo = false;
	tmp.T_izquierda = false;
	tmp.T_derecha = false;
	tmp.T_pausa = false;
	
	key_ant[KEY_UP] = key[KEY_2_UP];
	key_ant[KEY_DOWN] = key[KEY_2_DOWN];
	key_ant[KEY_LEFT] = key[KEY_2_LEFT];
	key_ant[KEY_RIGHT] = key[KEY_2_RIGHT];
    
	if( (Salida = recv(sockfd, &tmp, sizeof(tmp), MSG_DONTWAIT) ) > 0 ){
		dumpteclas(tmp);
		key[KEY_2_UP] = tmp.T_arriba;
		key[KEY_2_DOWN] = tmp.T_abajo;
		key[KEY_2_LEFT] = tmp.T_izquierda;
		key[KEY_2_RIGHT] = tmp.T_derecha;
		
		if( tmp.T_pausa ) return 100;
		
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
