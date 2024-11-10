#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "LocalSearch.cpp"

using namespace std;

double calculateTemperature(double initialTemperature, double coolingRate, int time) {
    return initialTemperature * pow(coolingRate, time);
}

/*
double calculateTemperature(double initialTemperature, int time) {
    return initialTemperature / log(time + 1);
}
*/

void simulatedAnnealing(CUBE &current, double initialTemperature, double coolingRate, double threshold, int MAX_TIME) {
    int time = 1;
    CUBE bestState = current;
    int bestValue = findValue(current);

    vector<double> probability_values;  
    int stuck_count = 0;                
    int unchanged_iterations = 0;     
    const int stuck_threshold = 10; 

    //double temperature = calculateTemperature(initialTemperature, time);
    double temperature = calculateTemperature(initialTemperature, coolingRate, time);

    while (time <= MAX_TIME) {
        CUBE neighbor = randomSuccessor(current);
        int neighborValue = findValue(neighbor);

        int deltaE = neighborValue - findValue(current);
        double probability = exp(deltaE / temperature); // e^(deltaE / T)

        // probability_values.push_back(probability); buat visualisasi tp kayanya gajadi

        cout << "Temperature: " << temperature
             << ", DeltaE: " << deltaE
             << ", Probability (e^(DeltaE/T)): " << probability
             << ", Threshold: " << threshold << endl;

        if (deltaE > 0 || (probability > threshold && ((double)rand() / RAND_MAX) < threshold)) {
            current = neighbor;
            if (neighborValue > bestValue) {
                bestState = neighbor;
                bestValue = neighborValue;
            }
            unchanged_iterations = 0;
        } else {
            unchanged_iterations++;
        }

        if (unchanged_iterations >= stuck_threshold) {
            stuck_count++;
            unchanged_iterations = 0;
        }

        time++;
        //temperature = calculateTemperature(initialTemperature, time);
        temperature = calculateTemperature(initialTemperature, coolingRate, time);
    }

    current = bestState;

    cout << "Total stuck count (local optima): " << stuck_count << endl;

    
    /*
    // ini kayanya gajadi 
    FILE *file = fopen("probability_values.txt", "w");
    for (double prob : probability_values) {
        fprintf(file, "%f\n", prob);
    }
    fclose(file);
    */
}

int main() {
    srand(time(0));
    CUBE current;
    generateInitialState(&current);

    cout << "Initial State:" << endl;
    printState(current);
    cout << "Initial Value: " << findValue(current) << endl;

    double initialTemperature = 2.0;
    double threshold = 0.55;
    int MAX_TIME = 25000; 
    double coolingRate = 0.99; 
    
    simulatedAnnealing(current, initialTemperature, coolingRate, threshold, MAX_TIME);

    cout << "Final State after Simulated Annealing:" << endl;
    printState(current);
    cout << "Final Value: " << findValue(current) << endl;

    return 0;
}