objects = main.o entropy.o detection.o collector.o log.o utils.o 

main: $(objects)
	cc -o main $(objects) -lm
	-rm $(objects)
main.o:
entropy.o: entropy.h 
detection.o: detection.h collector.h log.h utils.h
log.o: log.h
utils.o: utils.h

.PHONY: clean
clean:
	-rm main
