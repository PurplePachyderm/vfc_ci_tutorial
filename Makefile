CC=verificarlo-c

all:
	$(CC) -lvfc_probes main.c -o dotprod

clean:
	rm -f *.vfcrun.h5 *.vfcraw.h5 dotprod *.o
