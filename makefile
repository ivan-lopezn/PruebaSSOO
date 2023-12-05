.PHONY: clean

LDFLAGS:=-lpthread

all: hilos hilos_mutex

hilos: hilos.c

hilos_mutex: hilos_mutex.c

clean:
	rm -rf hilos hilos_mutex
