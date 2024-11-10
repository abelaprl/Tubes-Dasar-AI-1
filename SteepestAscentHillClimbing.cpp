#include <bits/stdc++.h>
#include "LocalSearch.hpp"

using namespace std;

void steepestascentHillClimbing(CUBE initial)
{
    auto start = chrono::high_resolution_clock::now();
    CUBE current = initial;
    int currentValue = findValue(current,0);
    vector<int> values;
    values.push_back(currentValue);
    int iterations = 0;

    while (true) // Limit iterasi maksimum
    {
        CUBE next = highestSuccessor(current);
        int nextValue = findValue(next,0);

        if (nextValue > currentValue)
        {
            current = next;
            currentValue = nextValue;
        }
        else{
            break;
        }

        values.push_back(currentValue);
        iterations++;

        if (currentValue == 0) // Tujuan tercapai
            break;
    }

    // Tampilkan hasil
    
    // Plot nilai objective function
    cout << "\nPlot Nilai Objective Function per Iterasi:" << endl;
    for (int i = 0; i < (values.size()-1); i++) //values.size() - 1 itu supaya tidak memasukkan yang state awal
    {
        cout << "Iterasi " << i + 1 << ": " << values[i] << endl;
    }

    cout << "State Awal:" << endl;
    printState(initial);
    cout << "Nilai Objective Function Awal: " << findValue(initial,0) << endl;

    cout << "\nState Akhir:" << endl;
    printState(current);
    cout << "Nilai Objective Function Akhir: " << currentValue << endl;

    cout << "Total Iterasi: " << iterations << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Durasi: " << duration.count() << " detik" << endl;
}

int main()
{
    srand(time(0));
    CUBE cube;
    generateInitialState(&cube);
    steepestascentHillClimbing(cube);
    return 0;
}
