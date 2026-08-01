
CFLAGS = -c -o 

Test.out: Test.o PPHP.o
	@g++ -o $@ Test.o PPHP.o -lgtest -lgtest_main -pthread

Test.o: Test.cpp
	@g++ -I /usr/include $(CFLAGS) $@ $<

PPHP.o: ../PPHP.c
	@gcc -c -o PPHP.o ../PPHP.c

.PHONY: clean
clean:
	@rm -f *.o Test.out
