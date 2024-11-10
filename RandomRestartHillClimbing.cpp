#include <bits/stdc++.h>
#include "LocalSearch.hpp"

using namespace std;

void randomRestartHillClimbing(CUBE initial)
{
    int maxRestart; // Menyimpan jumlah restart maksimal

    // Meminta input jumlah restart dari pengguna
    cout << "Masukkan jumlah restart maksimum: ";
    cin >> maxRestart;

    auto start = chrono::high_resolution_clock::now();
    CUBE current = initial;
    int currentValue = findValue(current, 0);

    vector<int> values;
    vector<int> jmlRestart;
    vector<int> jmlIterations;

    values.push_back(currentValue);
    int restart = 0;
    int iterations = 0;

    while (restart < maxRestart)
    {
        CUBE next = highestSuccessor(current);
        int nextValue = findValue(next, 0);

        if (nextValue > currentValue)
        {
            current = next;
            currentValue = nextValue;
            iterations++;
        }
        else
        {
            // Simpan data iterasi dan restart
            jmlRestart.push_back(restart);
            jmlIterations.push_back(iterations);
            restart++;

            // Restart dengan state baru
            if (restart != maxRestart)
            {
                generateInitialState(&current);
                currentValue = findValue(current, 0);
                iterations = 0;
            }
        }

        values.push_back(currentValue);

        if (currentValue == 0) // Tujuan tercapai
            break;
    }

    // Tampilkan hasil
    cout << "\nPlot Nilai Objective Function per Iterasi:" << endl;
    for (size_t i = 0; i < values.size() - 1; i++)
    {
        cout << "Iterasi " << i + 1 << ": " << values[i] << endl;
    }

    // Tampilkan jumlah restart dan iterasi per restart
    cout << "\nJumlah restart yang dilakukan: " << jmlRestart.size() << endl;
    for (size_t i = 0; i < jmlIterations.size(); i++)
    {
        cout << "Jumlah iterasi pada restart ke-" << i + 1 << ": " << jmlIterations[i] << endl;
    }

    // State awal dan akhir
    cout << "\nState Awal:" << endl;
    printState(initial);
    cout << "Nilai Objective Function Awal: " << findValue(initial, 0) << endl;

    cout << "\nState Terbaik yang Ditemukan:" << endl;
    printState(current);
    cout << "Nilai Objective Function Akhir: " << currentValue << endl;

    cout << "Total restart: " << restart << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Durasi: " << duration.count() << " detik" << endl;
}

int main()
{
    srand(static_cast<unsigned>(time(0)));
    CUBE cube;
    generateInitialState(&cube);
    randomRestartHillClimbing(cube);
    return 0;
}
