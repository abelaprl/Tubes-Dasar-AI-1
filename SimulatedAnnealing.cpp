#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "LocalSearch.cpp"

using namespace std;

double calculateTemperature(double Temperature, int time) {
    return Temperature - 0.000000001*time; //Nilai temperature dikurang dengan 0.000000001*time agar turun secara perlahan
}

void simulatedAnnealing(CUBE &current) {
    double threshold = 0.55;
    int MAX_TIME = 100000;
    int time = 0;
    CUBE bestState = current;
    int bestValue = findValue(current,0);

    vector<double> probability_values;  
    int stuck_count = 0;                
    int unchanged_iterations = 0;     
    const int stuck_threshold = 10; 

    double temperature = 2;

    while (time <= MAX_TIME) {
        temperature=calculateTemperature(temperature,time);
        if(temperature<=0) {cout << "Total stuck count (local optima): " << stuck_count << endl; return;}
        CUBE neighbor = randomSuccessor(current);
        int neighborValue = findValue(neighbor,0);

        int deltaE = neighborValue - findValue(current,0);
        double probability;
        if(deltaE>0) probability=1;
        else probability = exp(double(deltaE) / temperature); // e^(deltaE / T)
        cout << "Iteration: " << time
                << ", Temperature: " << temperature
                << ", DeltaE: " << deltaE
                << ", Probability (e^(DeltaE/T)): " << probability
                << ", Threshold: " << threshold
                << ", Value: " << current.value << endl;

        if (deltaE > 0) {
            current = neighbor;
        } else {
            if((probability > threshold && ((double)rand() / RAND_MAX) < probability)) current=neighbor;
            stuck_count++;
        }
        time++;
    }
}

int main() {
    clock_t start, end;
    start = clock();
    srand(time(0));
    CUBE current;
    generateInitialState(&current);

    cout << "Initial State:" << endl;
    printState(current);
    cout << "Initial Value: " << current.value << endl;
    
    simulatedAnnealing(current);

    cout << "Final State after Simulated Annealing:" << endl;
    printState(current);
    cout << "Final Value: " << findValue(current,0) << endl;
     end = clock();
 
    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}