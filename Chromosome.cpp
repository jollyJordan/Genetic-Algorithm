#include <time.h>
#include <stdlib.h> 
#include "Chromosome.h"

Chromosome::Chromosome(){
	fitness = 0;
	for(int i=0; i<DATA_SIZE; i++)
		data[i] = 0;
}

Chromosome::Chromosome(int modulo){
	for(int i=0; i<DATA_SIZE; i++)
		data[i] = rand() % modulo;
}

int* Chromosome::get(){
	return data;
}

void Chromosome::set(int newData[]){
	for(int i=0; i<DATA_SIZE; i++)
		data[i] = newData[i];
}
int Chromosome::getFitness(){
	return fitness;
}

void Chromosome::setFitness(int newFitness){
	fitness = newFitness;
}