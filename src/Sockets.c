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



int CrearSocket(int puerto){

	const int uno=1;
    struct sockaddr_in serverAddress;
    int sockfd;
    int clientfd;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd==-1) return ERROR;

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&uno, 
		(socklen_t)(sizeof(uno)))) return ERROR;

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

void LeerDelSocket(int sockfd, bool *key) {
    Teclas_2 tmp;
    recv(sockfd, tmp, sizeof(tmp), MSG_DONTWAIT);
    key[KEY_2_UP] = tmp.T_arriba;
    key[KEY_2_DOWN] = tmp.T_abajo;
    key[KEY_2_LEFT] = tmp.T_izquierda;
    key[KEY_2_RIGHT] = tmp.T_derecha;
}