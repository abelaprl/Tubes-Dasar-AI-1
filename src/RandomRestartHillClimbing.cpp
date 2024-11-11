#include <bits/stdc++.h>
#include "LocalSearch.hpp"

using namespace std;

void RandomRestartHillClimbing(CUBE initial, int maxRestart)
{

    CUBE current = initial;
    int currentValue = findValue(current, 0);

    vector<int> values; 
    vector<int> jmlIterations;

    int restart = 0; //banyak restart
    int iterationsperrestart = 0; //iterasi per restart

    ofstream outfile("objective_values.txt");

    while (restart < maxRestart)
    {
        CUBE next = highestSuccessor(current);
        int nextValue = findValue(next, 0);

        if (nextValue > currentValue)
        {
            current = next;
            currentValue = nextValue;
            iterationsperrestart++;
        }
        else
        {
            // Simpan data iterasi dan restart
            jmlIterations.push_back(iterationsperrestart);
            restart++;

            // Restart dengan state baru
            if (restart != maxRestart)
            {
                generateInitialState(&current);
                currentValue = findValue(current, 0);
                iterationsperrestart = 0;
            }
        }

        values.push_back(currentValue);
        outfile << currentValue << endl;

        if (currentValue == 0) // Tujuan tercapai
            break;
    }

    outfile.close(); 
    // Tampilkan hasil
    cout << "\nNilai Objective Function per Iterasi:" << endl;
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << "Iterasi " << i+1 << ": " << values[i] << endl;
    }

    cout << "\nGrafik Plot objective function terhadap banyak iterasi dapat dilihat dengan menjalankan file objectiveValue.py" << endl;

    // Tampilkan jumlah restart dan iterasi per restart
    cout << "\nJumlah restart yang dilakukan: " << restart << endl;
    for (size_t i = 0; i < jmlIterations.size(); i++)
    {
        cout << "Jumlah iterasi pada restart ke-" << i + 1 << ": " << jmlIterations[i] << endl;
    }

    // State awal dan akhir
    cout << "\nState Awal:" << endl;
    printState(initial);
    cout << "Nilai Objective Function Awal: " << findValue(initial, 0) << endl;

    cout << "\nState Akhir:" << endl;
    printState(current);
    cout << "Nilai Objective Function Akhir: " << currentValue << endl;

    cout << "\nTotal restart: " << restart << endl;
    cout << "\nTotal Iterasi: " << values.size() << endl;
}

int main()
{
    int maxRestart; // Menyimpan jumlah restart maksimal

    // Meminta input jumlah restart dari pengguna
    cout << "\nMasukkan jumlah restart maksimum: ";
    cin >> maxRestart;
    srand(static_cast<unsigned>(time(0)));
    auto start = chrono::high_resolution_clock::now();
    CUBE cube;
    generateInitialState(&cube);
    RandomRestartHillClimbing(cube, maxRestart);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nDurasi: " << duration.count() << " detik\n" << endl;
    return 0;
}