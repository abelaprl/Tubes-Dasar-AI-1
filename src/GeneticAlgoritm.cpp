#include <bits/stdc++.h> 
#include "LocalSearch.cpp"
using namespace std; 

CUBE population[200];
int POPULATION_SIZE;
int ITERATION_TOTAL;
int fitnessTotal;

void generatePopulation()
{
    cout<<"INITIAL STATE: "<<endl;
	for(int i=0; i<POPULATION_SIZE; i++) 
	{ 
        CUBE gnome;
		generateInitialState(&gnome); 
        population[i] = gnome;
        cout<<"INDIVIDUAL KE-"<<i+1<<endl;
        printState(population[i]);
        cout<<"OBJECTIVE VALUE: "<<findValue(population[i], 109)<<endl<<endl;
	} 
}

void selection()
{
    // percentage fitness of each state
    double percentageFitnessLevel[POPULATION_SIZE];
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        percentageFitnessLevel[i]=double(population[i].value)/double(fitnessTotal);
    }

    // sequence of fitness value's percentage
    double fitnessOrder[POPULATION_SIZE];
    int idxMax = 0;
    fitnessOrder[0] = double(percentageFitnessLevel[0])*100;

    for (int i=1; i<POPULATION_SIZE; i++)
    {
        fitnessOrder[i] = fitnessOrder[i-1] + double(percentageFitnessLevel[i])*100;
        if (fitnessOrder[i] > 0)
        {
            idxMax = i;
        }
    }
    fitnessOrder[idxMax] = 100;

    CUBE parent[POPULATION_SIZE];
    for (int i=0; i<POPULATION_SIZE; i++) {
        double randomNumber = (rand()%101);
        for (int j=0; j<POPULATION_SIZE; j++)
        {
            if ((fitnessOrder[j]) >= randomNumber && fitnessOrder[j] != 0)
            {
                parent[i] = population[j];
                break;
            }
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
	int generation = 0; 
    CUBE finalState;
    bool notNaN = false;
    fitnessTotal = 0;
    int bestValue, idxBestState = 0;

    while (!notNaN)
    {
        generatePopulation();

        // make sure at least there's one state that has value > 0
        for(int i=0; i<POPULATION_SIZE; i++)
        {
            fitnessTotal+=population[i].value;
        }
        if (fitnessTotal > 0) notNaN = true;
    }
    
    selection();
    for (int i=0; i<POPULATION_SIZE; i++) {
        cout<<"nilai parent ke-"<<i+1<<": "<<findValue(population[i], 109)<<endl;
    }
	while (!found && generation<ITERATION_TOTAL)
	{
        selection();
        // if the individual having 0 fitness score then we know that we have reached to the target so break the loop
        for(int i=0; i<POPULATION_SIZE; i++)
        {
            if(population[i].value == 109) 
            { 
                found = true; 
                idxBestState = i;
                break; 
            } 
        }

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

    for(int i=0; i<POPULATION_SIZE; i++)
    {
        if (findValue(population[i], 109) > bestValue)
        {
            bestValue = findValue(population[i], 109);
            idxBestState = i;
        }
    }

    finalState = population[idxBestState];
    cout<<"FINAL STATE: "<<endl;
    printState(finalState);
    cout<<"FINAL OBJECTIVE VALUE: "<<findValue(finalState, 109)<<endl<<endl;
}