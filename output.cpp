#include <iostream>
#include <iomanip>
#include<fstream>

int main () {

    std::ifstream fin("table.txt");
    std::ofstream fout1("new_table.csv");
    int m, n;
    double a;
    unsigned int dd, mm, yyyy;
    dd = 25; mm = 9; yyyy = 2021;
    if (fout1.good()) fout1 << std::setw(2) << std::setfill('0') << dd << '_' << std::setw(2) << std::setfill('0') << mm << '_' << yyyy << '\n';
    fout1.close();
    std::ofstream fout("new_table.csv", std::ios::app);
    if (fin.good()) fin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (fin.good()) fin >> a;
            if (fout.good()) fout << a << ',';
        }
        if (fin.good()) fin >> a;
        if (fout.good()) fout << a << '\n';
    }
    fin.close();
    fout.close();
return 0;}
