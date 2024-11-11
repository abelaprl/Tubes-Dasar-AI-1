#include <bits/stdc++.h>
#include "LocalSearch.hpp"

using namespace std;

void HillClimbingSidewaysMove(CUBE initial)
{
    int maxsideways; // Menyimpan jumlah iterasi sideways maksimum

    // Meminta input jumlah iterasi sideways maksimum dari pengguna
    cout << "Masukkan jumlah sideways move maksimum: ";
    cin >> maxsideways;

    auto start = chrono::high_resolution_clock::now();
    CUBE current = initial;
    int currentValue = findValue(current,0);
    vector<int> values;
    values.push_back(currentValue);

    int iterations = 0;
    int sideways = 0;

    while (true)
    {
        CUBE next = highestSuccessor(current);
        int nextValue = findValue(next,0);

        if (nextValue > currentValue)
        {
            // Jika nilai meningkat, terima keadaan baru
            current = next;
            currentValue = nextValue;
            sideways = 0; // Reset sideways move counter
        }
        else if (nextValue == currentValue && sideways < maxsideways)
        {
            // Jika nilai sama, lakukan sideways move
            current = next;
            currentValue = nextValue;
            sideways++;
        }
        else
        {
            // Tidak ada peningkatan, hentikan pencarian
            break;
        }

        values.push_back(currentValue);
        iterations++;

        // Jika mencapai nilai objective function yang optimal
        if (currentValue == 0)
            break;
    }

    // Tampilkan hasil
    cout << "\nPlot Nilai Objective Function per Iterasi:" << endl;
    for (int i = 0; i < values.size(); i++)
    {
        cout << "Iterasi " << i + 1 << ": " << values[i] << endl;
    }

    cout << "\nState Awal:" << endl;
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
    HillClimbingSidewaysMove(cube);
    return 0;
}