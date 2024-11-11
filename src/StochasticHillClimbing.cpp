#include <bits/stdc++.h>
#include "LocalSearch.hpp"

using namespace std;

void StochasticHillClimbing(CUBE initial, int maxIterations)
{

    CUBE current = initial;
    int currentValue = findValue(current,0);
    vector<int> values;
    int iterations = 0;

    ofstream outfile("objective_values.txt");

    while (iterations < maxIterations) // Limit iterasi maksimum
    {
        CUBE next = randomSuccessor(current);
        int nextValue = findValue(next,0);

        if (nextValue > currentValue)
        {
            current = next;
            currentValue = nextValue;
        }

        values.push_back(currentValue);
        outfile << currentValue << endl;
        iterations++;

        if (currentValue == 0) // Tujuan tercapai
            break;
    }

    outfile.close(); 
    // Tampilkan hasil
    cout << "\nNilai Objective Function per Iterasi:" << endl;
    for (int i = 0; i < values.size(); i++) //values.size() - 1 itu supaya tidak memasukkan yang state awal
    {
        cout << "Iterasi " << i + 1 << ": " << values[i] << endl;
    }
    cout << "\nGrafik Plot objective function terhadap banyak iterasi dapat dilihat dengan menjalankan file objectiveValue.py" << endl;
    cout << "\nState Awal:" << endl;
    printState(initial);
    cout << "Nilai Objective Function Awal: " << findValue(initial,0) << endl;

    cout << "\nState Akhir:" << endl;
    printState(current);
    cout << "Nilai Objective Function Akhir: " << currentValue << endl;

    cout << "\nTotal Iterasi: " << iterations << endl;
}

int main()
{
    int maxIterations; // Menyimpan jumlah iterasi maksimal

    // Meminta input jumlah iterasi dari pengguna
    cout << "\nMasukkan jumlah iterasi maksimum: ";
    cin >> maxIterations;
    srand(time(0));
    auto start = chrono::high_resolution_clock::now();
    CUBE cube;
    generateInitialState(&cube);
    StochasticHillClimbing(cube,maxIterations);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nDurasi: " << duration.count() << " detik\n" << endl;
    return 0;
}