CFLAGS = -Wall -g
CC = gcc
LIBS += $(shell pkg-config --libs allegro-5.0)
CFLAGS += $(shell pkg-config --cflags allegro-5.0)
LIBS += $(shell pkg-config --libs allegro_image-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_image-5.0)
LIBS += $(shell pkg-config --libs allegro_dialog-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_dialog-5.0)
LIBS += $(shell pkg-config --libs allegro_audio-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_audio-5.0)
LIBS += $(shell pkg-config --libs allegro_color-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_color-5.0)
LIBS += $(shell pkg-config --libs allegro_font-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_font-5.0)
LIBS += $(shell pkg-config --libs allegro_main-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_main-5.0)
LIBS += $(shell pkg-config --libs allegro_ttf-5.0)
CFLAGS += $(shell pkg-config --cflags allegro_ttf-5.0)


all:
	$(CC)  -o Jugador2 Jugador2.c Jugador2Lib.c $(CFLAGS) $(LIBS)

clean:
	@rm -rf Jugador2
