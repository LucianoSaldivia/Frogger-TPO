/*
 * Basic Keyboard Example
 * https://wiki.allegro.cc/index.php?title=Basic_Keyboard_Example
 *         Para correrlo:
 *             al08_keyboard_client <IP>
 */

#include <string.h>
#include <stdio.h>
#include <allegro5/allegro.h>
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "cliente.h"

int main(int argc, char **argv)
{
    /*************************
     * Variables de Allegro
     */

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   bool HuboEventos = false;
 
    /*************************
     * Variables de Server TCP
     */

    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    Teclas_2 tmp = {0};
    int puerto;

    /*************************
     * Inicializacion Server TCP
     */

    if (argc < 2) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    memset((void *) &serv_addr, '\0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    puerto = atoi(argv[2]);
    serv_addr.sin_port = htons(puerto);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    /*************************
     * Inicialiación y configuración Allegro
     */

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_set_target_bitmap(bouncer);
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
   al_flip_display();
   al_start_timer(timer);
 
    /*************************
     * Listos para empezar el juego!
     */

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      HuboEventos = false;

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_UP] && bouncer_y >= 4.0) {
            bouncer_y -= 4.0;
         }
 
         if(key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
            bouncer_y += 4.0;
         }
 
         if(key[KEY_LEFT] && bouncer_x >= 4.0) {
            bouncer_x -= 4.0;
         }
 
         if(key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
            bouncer_x += 4.0;
         }
 
         redraw = true;
      } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      } else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               HuboEventos = true;
               break; 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               HuboEventos = true;
               break; 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               HuboEventos = true;
               break;
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               HuboEventos = true;
               break;
         }
      } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               HuboEventos = true;
               break; 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               HuboEventos = true;
               break; 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               HuboEventos = true;
               break;
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               HuboEventos = true;
               break;
         }
      }
      if( HuboEventos ){
        tmp.T_arriba = key[KEY_UP];
        tmp.T_abajo = key[KEY_DOWN];
        tmp.T_izquierda = key[KEY_LEFT];
        tmp.T_derecha = key[KEY_RIGHT];
        send(sockfd, &tmp, sizeof(tmp), MSG_DONTWAIT);
      }
  
      // if(redraw && al_is_event_queue_empty(event_queue)) {
      //    redraw = false;

      //    al_clear_to_color(al_map_rgb(0,0,0));
      //    al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
      //    al_flip_display();
      // }
   }
 
   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   close(sockfd);
 
   return 0;
}
