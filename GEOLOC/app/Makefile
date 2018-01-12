
all: app.o

app.o:
ifeq ($(TARGET),ANCHOR)
	$(MAKE) -C ./anchor
	cp anchor/app.o ./
else
	$(CC) -c ./mobile/app.c -o ./app.o
endif
	$(CC) -c frame.c -o frame.o
	ld -r app.o frame.o -o app_tmp.o
	mv app_tmp.o $@

.PHONY: clean

clean:
	-rm ./app.o ./frame.o
