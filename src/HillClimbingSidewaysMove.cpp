#include <bits/stdc++.h>
#include "LocalSearch.hpp"

using namespace std;

void HillClimbingSidewaysMove(CUBE initial, int maxsideways)
{

    CUBE current = initial;
    int currentValue = findValue(current,0);
    vector<int> values;

    int iterations = 0;
    int sideways = 0;

    ofstream outfile("objective_values.txt");

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
        outfile << currentValue << endl;
        iterations++;

        // Jika mencapai nilai objective function yang optimal
        if (currentValue == 0)
            break;
    }

    outfile.close(); 

    // Tampilkan hasil
    cout << "\nNilai Objective Function per Iterasi:" << endl;
    for (int i = 0; i < values.size(); i++)
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
    int maxsideways; // Menyimpan jumlah iterasi sideways maksimum

    // Meminta input jumlah iterasi sideways maksimum dari pengguna
    cout << "\nMasukkan jumlah sideways move maksimum: ";
    cin >> maxsideways;
    srand(time(0));
    auto start = chrono::high_resolution_clock::now();
    CUBE cube;
    generateInitialState(&cube);
    HillClimbingSidewaysMove(cube, maxsideways);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nDurasi: " << duration.count() << " detik" << endl;
    return 0;
}