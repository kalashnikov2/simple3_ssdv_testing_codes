EXEC=GEOLOC
export TARGET=MOBILE# ANCHOR or MOBILE
export ANCHOR_ID=2# Define the anchor id
export IS_MASTER=0# Define if this anchor is master or not
export CC=gcc -g -D TARGET=$(TARGET) -D ANCHOR_ID=$(ANCHOR_ID) -D IS_MASTER=$(IS_MASTER) -Ilib -lm -pthread
export LDFLAGS=-lwiringPi

all:$(EXEC)

$(EXEC): main.o lib/dragino.o lib/config.o lib/fskconfig.o app/app.o lib/gps.o
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

main.o: main.c
	$(CC) -c $< -o $@

lib/dragino.o: lib/dragino.c
	$(CC) -c $^ -o $@

lib/config.o: lib/config.c
	$(CC) -c $^ -o $@

lib/fskconfig.o: lib/fskconfig.c
	$(CC) -c $^ -o $@

lib/gps.o: lib/gps.c
	$(CC) -c $^ -o $@

app/app.o:
	$(MAKE) -C ./app

clean:
	-$(MAKE) -C ./app clean
	-find ./ -name "*.o" -delete
	-rm $(EXEC)
