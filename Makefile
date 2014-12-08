GRAPH = gnuplot

CC = clang
CFLAGS = -Wall -O0 -g 
LFLAGS = -O0 -g
LIBS = -lgsl  -lgslcblas -lm

pendulum: part_two.o pendulum_ode.o 
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)


pendulum_unstable: pendulum
	./pendulum 110.0 > pendulum_unstable_data

pendulum_stable: pendulum
	./pendulum 150 > pendulum_stable_data

pendulum.png:  pendulum_stable pendulum_unstable
	$(GRAPH) pendulum_stable.gpl
	$(GRAPH) pendulum_unstable.gpl

clean : 
	rm -f *~
	rm -f *.o
	rm -f pendulum

veryclean : clean
	rm -f pendulum_data pendulum.png
