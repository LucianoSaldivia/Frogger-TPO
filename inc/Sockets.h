int CrearSocket( int puerto );
int Sockets( ALLEGRO_DISPLAY **p_display, ALLEGRO_EVENT_QUEUE **p_event_queue, int *p_sockfd );
int LeerDelSocket( int sockfd, bool *key, ALLEGRO_TIMER **p_resting_timer, ALLEGRO_TIMER **p_sprites_timer );
