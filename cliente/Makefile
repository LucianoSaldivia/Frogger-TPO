CFLAGS = -Wall -g
CC = gcc
LIBS += $(shell pkg-config --libs allegro-5)
CFLAGS += $(shell pkg-config --cflags allegro-5)
LIBS += $(shell pkg-config --libs allegro_image-5)
CFLAGS += $(shell pkg-config --cflags allegro_image-5)
LIBS += $(shell pkg-config --libs allegro_dialog-5)
CFLAGS += $(shell pkg-config --cflags allegro_dialog-5)
LIBS += $(shell pkg-config --libs allegro_audio-5)
CFLAGS += $(shell pkg-config --cflags allegro_audio-5)
LIBS += $(shell pkg-config --libs allegro_color-5)
CFLAGS += $(shell pkg-config --cflags allegro_color-5)
LIBS += $(shell pkg-config --libs allegro_font-5)
CFLAGS += $(shell pkg-config --cflags allegro_font-5)
LIBS += $(shell pkg-config --libs allegro_main-5)
CFLAGS += $(shell pkg-config --cflags allegro_main-5)
LIBS += $(shell pkg-config --libs allegro_ttf-5)
CFLAGS += $(shell pkg-config --cflags allegro_ttf-5)


all:
	$(CC) cliente.c -o cliente $(CFLAGS) $(LIBS)
clean:
	rm cliente