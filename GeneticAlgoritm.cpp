#include <bits/stdc++.h> 
#include "LocalSearch.hpp"
using namespace std; 

CUBE population[100];
int POPULATION_SIZE;
int ITERATION_TOTAL;

void selection()
{
    int fitnessTotal=0;
    double percentageFitnessLevel[POPULATION_SIZE];
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        fitnessTotal+=population[i].value;
    }
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        percentageFitnessLevel[i]=double(population[i].value)/double(fitnessTotal);
    }

    double fitnessOrder[POPULATION_SIZE];
    fitnessOrder[0] = 0;
    for(int i=1; i<POPULATION_SIZE; i++)
    {
        fitnessOrder[i] = fitnessOrder[i-1] + double(population[i].value);
    }
    double maxNumber = fitnessOrder[POPULATION_SIZE-1];
    fitnessOrder[POPULATION_SIZE-1] = 100;
    
    CUBE parent[POPULATION_SIZE];
    for (int i=0; i<POPULATION_SIZE; i++) {
        double randomNumber = (rand()%101);
        for (int j=0; j<POPULATION_SIZE; j++) {
            if ((fitnessOrder[j]) > randomNumber) parent[i] = population[j];
        }
    }    
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        population[i]=parent[i];
    }
}

void swapPair(int x, int y, int num, int l, int m, int n)
{
    for(int i=2; i<=4; i++)
    {
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                if(population[x].state[i][j][k]==num)
                {
                    num=population[y].state[i][j][k];
                    i=2; j=1; k=1;
                }      
            }
        }
    }
    for(int i=1; i<=5; i++)
    {
        if(i>=2 && i<=4) continue;
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                if(population[y].state[i][j][k]==num)
                {
                    swap(population[x].state[l][m][n],population[y].state[i][j][k]);
                }
            }
        }
    }
}

bool isDouble(int x, int num)
{
    for(int i=2; i<=4; i++)
    {
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                if(population[x].state[i][j][k]==num) return true;        
            }
        }
    }
    return false;
}
void crossover(int x, int y)
{
    for(int i=2; i<=4; i++)
    {
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                swap(population[x].state[i][j][k],population[y].state[i][j][k]);        
            }
        }
    }
    for(int i=1; i<=5; i++)
    {
        if(i>=2 && i<=4) continue;
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                if(isDouble(x,population[x].state[i][j][k]))
                {
                    swapPair(x,y,population[x].state[i][j][k],i,j,k);
                }
            }
        }
    }

}

int main() {
    srand(time(0));
    cin>>POPULATION_SIZE>>ITERATION_TOTAL;
    bool found = false; 

    // current generation 
	int generation = 0; 
    // generate population
	for(int i=0; i<POPULATION_SIZE; i++) 
	{ 
        CUBE gnome;
		generateInitialState(&gnome); 
        population[i] = gnome;
        printState(population[i]);
	} 
    
	while (!found && generation<ITERATION_TOTAL)
	{ 
		// sort the population in increasing order of fitness score 
		//sort(population,population+POPULATION_SIZE); 

		// if the individual having 0 fitness score then we know that we have reached to the target 
		// so break the loop 
        for(int i=0; i<POPULATION_SIZE; i++)
        {
            if(population[POPULATION_SIZE-1].value == 109) 
            { 
                found = true; 
                break; 
            } 
        }
        selection();
        for(int i=0; i<POPULATION_SIZE/2; i++)
        {
            crossover(i,i+1);
        }
        //mutation
        for (int i=0; i<POPULATION_SIZE; i++) {
            population[i]=randomSuccessor(population[i]);
        }
        generation++;
    }
    cout<<"FINAL STATE:"<<endl;
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        printState(population[i]);
    }
}