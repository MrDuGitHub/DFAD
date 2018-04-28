objects = entropy.o detection.o collector.o log.o utils.o 

entropy: $(objects)
	cc -o entropy $(objects) -lm
entropy.o: entropy.h 
detection.o: detection.h collector.h log.h utils.h
log.o: log.h
utils.o: utils.h

.PHONY: clean
clean:
	-rm entropy $(objects)	
