#include <bits/stdc++.h>
#include "DummyLocalSearch.h"

using namespace std;

void stochasticHillClimbing(CUBE initial)
{
    CUBE current = initial;
    int currentValue = findValue(current);
    vector<int> values;
    values.push_back(currentValue);
    int iterations = 0;
    auto start = chrono::high_resolution_clock::now();

    while (iterations < 100) // Limit iterasi maksimum
    {
        CUBE next = randomSuccessor(current);
        int nextValue = findValue(next);

        if (nextValue > currentValue)
        {
            current = next;
            currentValue = nextValue;
        }

        values.push_back(currentValue);
        iterations++;

        if (currentValue == 0) // Tujuan tercapai
            break;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    // Tampilkan hasil
    
    // Plot nilai objective function
    cout << "\nPlot Nilai Objective Function per Iterasi:" << endl;
    for (int i = 0; i < (values.size()-1); i++) //values.size() - 1 itu supaya tidak memasukkan yang state awal
    {
        cout << "Iterasi " << i + 1 << ": " << values[i] << endl;
    }

    cout << "State Awal:" << endl;
    printState(initial);
    cout << "Nilai Objective Function Awal: " << findValue(initial) << endl;

    cout << "\nState Akhir:" << endl;
    printState(current);
    cout << "Nilai Objective Function Akhir: " << currentValue << endl;
    cout << "Durasi: " << duration.count() << " detik" << endl;
    cout << "Total Iterasi: " << iterations << endl;
}

int main()
{
    srand(time(0));
    CUBE cube;
    generateInitialState(&cube);
    stochasticHillClimbing(cube);
    return 0;
}
