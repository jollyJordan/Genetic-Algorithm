#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome{
public:
	Chromosome();
	Chromosome(int modulo);
	int* get();
	void set(int newData[]);
	int getFitness();
	void setFitness(int newFitness);
	
	
private:
	const static int DATA_SIZE = 16;
	int data[DATA_SIZE];
	int fitness;
};

#endif