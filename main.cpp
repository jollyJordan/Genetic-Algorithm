#include <algorithm>
#include <iostream>
#include <ctime>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>
#include "Chromosome.h"

const int DATA_SIZE = 10;
const int POP_SIZE = 25;
const int DATA_MOD = 3;
const int MAX_GENERATIONS = 100000;
Chromosome population[POP_SIZE];
std::clock_t start;
float accProbability[POP_SIZE];
int target[DATA_SIZE] = {0,1,2,1,0,0,1,2,1,0};

int binarySearch(float key, int l, int r){
	int i;
	
	if (l>=r)
		i = l;
	else if(l>=POP_SIZE)
		i = POP_SIZE-1;
	else
	{
		int pivot = (l+r)/2;
		if (key==accProbability[pivot])
			i = pivot;
		else if(key<accProbability[pivot])
			i = binarySearch(key, l, pivot-1);
		else
			i = binarySearch(key, pivot+1, r);
	}
	
	return i;
 }
 
 void printData(int a[]){
	for(int i=0; i<DATA_SIZE; i++)
			std::cout<<a[i]<<" ";
}
 
void printPopulation(){
	for(int i=0; i<POP_SIZE; i++)
	{
		printData(population[i].get());
		std::cout<<"\t"<<population[i].getFitness()/(float)DATA_SIZE<<"\t"<<accProbability[i]<<"\n";
	}
}

void calcFitness(){
	int fitness;
	int* data;
	
	for(int i=0; i<POP_SIZE; i++)
	{
		fitness = 0;
		data = population[i].get();
		
		for(int j=0; j<DATA_SIZE; j++)
			if(data[j]==target[j])
				fitness++;
		
		population[i].setFitness(fitness);
		
		// A solution has been found
		if(fitness/DATA_SIZE==1)
		{
			std::cout<<"Solution Found:\t";
			printData(population[i].get());
			std::cout << "\nTime: "<<(std::clock()-start) / (double)(CLOCKS_PER_SEC/1000)<<" ms\n";
			exit(1);
		}
	}
}

void calcPrDist(){
	float popFitness= 0;
	
	for(int i=0; i<POP_SIZE; i++)
		popFitness += population[i].getFitness();
	
	accProbability[0] = population[0].getFitness()/popFitness;
	
	for(int i=1; i<POP_SIZE; i++)
			accProbability[i] = (population[i].getFitness()/popFitness) + accProbability[i-1];
}

void combine(int leftParent, int rightParent, int newPopData[][DATA_SIZE], int insertIndex){
	int* rightData = population[rightParent].get();
	int* leftData = population[leftParent].get();
	
	for(int i=0; i<DATA_SIZE/2; i++)
		newPopData[insertIndex][i] = leftData[i];
	for(int i=DATA_SIZE/2; i<DATA_SIZE; i++)
		newPopData[insertIndex][i] = rightData[i];
}

void findParents(){
	int leftParent, rightParent;
	int newPopData[POP_SIZE][DATA_SIZE];
	
	for(int i=0; i<POP_SIZE; i++)
	{
		leftParent = binarySearch((rand()%100+1) / (float)100, 0, POP_SIZE-1);
		rightParent =  binarySearch((rand()%100+1) / (float)100, 0, POP_SIZE-1);
		
		combine(leftParent, rightParent, newPopData, i);
	}
	
	for(int i=0; i<POP_SIZE; i++)
		population[i].set(newPopData[i]);
}

void mutate(){
	srand(time(NULL));
	int chr, dataBit, bitsToMutate = rand()%DATA_SIZE+1;
	int* data = population[chr].get();
	
	for(int i=0; i<bitsToMutate; i++)
	{
		chr = rand()%POP_SIZE;
		dataBit = rand()%DATA_SIZE;
		data[dataBit] = rand()%DATA_MOD;
		population[chr].set(data);
	}
}

bool sortOrder(Chromosome i, Chromosome j) {
	return i.getFitness() > j.getFitness();
}

void calcPopMetrics(){
	calcFitness();
	std::sort(population, population+POP_SIZE, sortOrder);
	calcPrDist();
}

int run(int maxGenerations){
	calcPopMetrics();
	
	for(int i=0; i<maxGenerations; i++)
	{
		findParents();
		mutate();
		calcPopMetrics();
		// Uncomment to see every generation printed
		// printPopulation();
		// std::cout<<"\n";
	}
}

int main(int argc, char *argv[]){
	for(int i=0; i<POP_SIZE; i++)
		population[i] = Chromosome(DATA_MOD);
	
	calcFitness();
	std::sort(population, population+POP_SIZE, sortOrder);
	printPopulation();
	std::cout<<"------------------------------------\n";
	
	std::clock_t end;
   start = std::clock();
	run(MAX_GENERATIONS);
   end = std::clock();
	
	std::cout<<"------------------------------------\n";
	std::cout << "\nTarget:  ";
	printData(target);
	std::cout<<"\nClosest: ";
	printData(population[0].get());
   std::cout << "\nTime: "<<(end-start) / (double)(CLOCKS_PER_SEC/1000)<<" ms\n";
	
	return 1;
}