#include <iostream>
#include <fstream>
using namespace std;

int main()
{ 
//transkrypcja
    ofstream output("rna - out.txt"); // stworz plik tekstowy o nazwie out.txt
    ifstream fasta("muszka_owocowka_genom.fna"); //zamiast sciezki dostepu moze byc nazwa pliku, o ile jest w tym samym folderze
    while (true) {
        string line; //string dziala jak tablica char
        getline (fasta, line); //bardziej skomplikowana; wczytaj z "fasta" znaki do "line", czytaj plik az do konca linii (enter), pozniej do konca pliku
        if(!fasta.good()) break; //konczy program w momencie gdy osiagnie koniec pliku
        if (line[0] == '>') continue;
        //fasta >> line; prostsza wersja, czytaj plik az do bialego znaku, np spacja lub enter
        line.length();
        int i = 0;
        while (i < line.length() + 1) {
            //char T = 'T';
            if (line[i] == 'T') line[i] = 'U';
             if (line[i] == 't') line[i] = 'u';
            i++;
        }

        //cout << line << endl; // to samo co na dole, ale tu wypisanie na ekran
        output << line << endl; //wypisz wszystko z line za pomoca procedury output do out.txt
    }
    return 0;
}
