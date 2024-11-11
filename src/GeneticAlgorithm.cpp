#include <bits/stdc++.h> 
#include "LocalSearch.hpp"
using namespace std; 

CUBE population[10000];
int POPULATION_SIZE;
int ITERATION_TOTAL;

void tournamentSelection()
{
    CUBE selected[POPULATION_SIZE];
    int maxVal=-1;
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        CUBE candidates[POPULATION_SIZE/4];
        for(int j=0; j<POPULATION_SIZE/4; j++)
        {
            candidates[j]=population[(rand()%POPULATION_SIZE)];
            if(findValue(candidates[j],109)>maxVal) {maxVal=candidates[j].value; selected[i]=candidates[j];}
        }
        maxVal=-1;
    }
    for(int i=0; i<POPULATION_SIZE; i++) population[i]=selected[i];
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
    struct GeneticAlgoritm
    {
        int i; 
        int j;
        int k;
    };
    vector<GeneticAlgoritm> A,B;
    for(int i=1; i<=5; i+=4)
    {
        for(int j=1; j<=5; j++)
        {
            for(int k=1; k<=5; k++)
            {
                if(isDouble(x,population[x].state[i][j][k]))
                {
                    GeneticAlgoritm a;
                    a.i=i; a.j=j; a.k=k;
                    A.push_back(a);
                }
                if(isDouble(y,population[y].state[i][j][k]))
                {
                    GeneticAlgoritm a;
                    a.i=i; a.j=j; a.k=k;
                    B.push_back(a);
                }
            }
        }
    }
    for(int i=0; i<A.size(); i++)
    {
        swap(population[x].state[A[i].i][A[i].j][A[i].k],population[y].state[B[i].i][B[i].j][B[i].k]);
    }
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        population[x].value=findValue(population[x],109);
        population[y].value=findValue(population[y],109);
    }
}

int main() {
    clock_t start, end;
    start = clock();
    srand(time(0));
    cin>>POPULATION_SIZE>>ITERATION_TOTAL;
    bool found = false; 
	int generation = 0; 
    CUBE finalState;
    int bestValue, idxBestState = 0;

    ofstream bestfile("best_objective_values.txt");
    ofstream avgfile("avg_objective_values.txt");

    //generate inisial population
    for(int i=0; i<POPULATION_SIZE; i++)
    {
        generateInitialState(&population[i]);
        population[i].value=findValue(population[i],109);
    }

    // print best initial state
    cout<<"INITIAL STATE: "<<endl;
    CUBE bestInitialState = population[0];
    int bestInitialValue = findValue(bestInitialState, 109);
    int sumInitialValue = findValue(bestInitialState, 109);

    for (int i=1; i<POPULATION_SIZE; i++)
    {
        sumInitialValue += findValue(population[i], 109);
        if (findValue(population[i], 109) > bestInitialValue) {
            bestInitialState = population[i];
            bestInitialValue = findValue(bestInitialState, 109);
        }
    }
    printState(bestInitialState);
    cout<<"INITIAL OBJECTIVE VALUE: "<<bestInitialValue<<endl<<endl;
    bestfile << bestInitialValue << endl;
    avgfile << double(sumInitialValue)/double(POPULATION_SIZE)<<endl;


	while (!found && generation<ITERATION_TOTAL)
	{
        tournamentSelection();
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

        for(int i=0; i<POPULATION_SIZE/2; i+=2)
        {
            crossover(i,i+1);   
        }

        //mutation
        for (int i=0; i<POPULATION_SIZE; i++) {
            population[i]=randomSuccessor(population[i]);
        }

        int bestGenValue = 0;
        int sumGenValue = 0;
        for (int i=0; i<POPULATION_SIZE; i++) {
            sumGenValue += findValue(population[i], 109);
            if (findValue(population[i], 109) > bestGenValue) {
                bestGenValue = findValue(population[i], 109);
            }
        }
        bestfile << bestGenValue << endl;
        avgfile << double(sumGenValue)/double(POPULATION_SIZE)<<endl;
        
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
    bestfile << findValue(finalState, 109) << endl;
    end = clock();
    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}