gen:Chromosome.h Chromosome.cpp main.cpp 
	g++ -g -o gen Chromosome.h Chromosome.cpp main.cpp
clean:
	rm -f *~ gen