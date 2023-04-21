#include <iostream>
#include <stdlib.h>
using namespace std;

void win_rules (char tab[][49], int N)
{
    bool WIN = false;
    bool poziom = false;
    bool pion = false;
    bool skos = false;
    int x = 2;

    //************POZIOMY****************
    for (int i = 0; i < N; i++)
    {
        bool poziom_i = true;
        int j;
        for (j = 0; j < N; j++)
        {
            int k = j + 1;
            if (k == N)
            {
                break;
            }
            if (tab[i][j] != tab[i][k])
            {
                poziom_i = false;
                break;
            }
        }
        if (poziom_i == true)
        {
            if (tab[i][j] == 'X')
            {
                x = 1;
            }
            if (tab[i][j] == 'O')
            {
                x = 0;
            }
            if (x == 1)
            {
                poziom = true;
                WIN = true;
                cout << "WYGRYWA X!"<< endl;
                exit(0);
            }
            if (x == 0)
            {
                poziom = true;
                WIN = true;
                cout << "WYGRYWA O!"<< endl;
                exit(0);
            }
        }
    }
    //************PIONY******************
    if (poziom == false)
    {
        for (int i = 0; i < N; i++)
        {
            bool pion_i = true;
            int j;
            for (j = 0; j < N; j++)
            {
                int k = j + 1;
                if (k == N)
                {
                    break;
                }
                if (tab[j][i] != tab[k][i])
                {
                    pion_i = false;
                    break;
                }
            }
            if (pion_i == true)
            {
                if (tab[j][i] == 'X')
                {
                    x = 1;
                }
                if (tab[j][i] == 'O')
                {
                    x = 0;
                }
                if (x == 1)
                {
                    pion = true;
                    WIN = true;
                    cout << "WYGRYWA X! "<< endl;
                    exit(0);
                }
                if (x == 0)
                {
                    pion = true;
                    WIN = true;
                    cout << "WYGRYWA O!"<< endl;
                    exit(0);
                }
            }
        }
    }
    //************SKOSY******************
    if (poziom == false && pion == false)
    {
        //pierwszy skos
        bool skos_1 = true;
        int i;
        for (i = 0; i < N; i++)
        {
            int j = i + 1;
            if (j == N)
            {
                break;
            }
            if (tab[i][i] != tab[j][j])
            {
                skos_1 = false;
                break;
            }
        }
        if (skos_1 == true)
        {
            if (tab[i][i] == 'X')
            {
                x = 1;
            }
            if (tab[i][i] == 'O')
            {
                x = 0;
            }
            if (x == 1)
            {
                skos = true;
                WIN = true;
                cout << "WYGRYWA X!"<< endl;
                exit(0);
            }
            if (x == 0)
            {
                skos = true;
                WIN = true;
                cout << "WYGRYWA O!"<< endl;
                exit(0);
            }
        }
        //drugi skos
        if (skos_1 == false)
        {
            bool skos_2 = true;
            int i;
            int j = N - 1;
            for (i = 0; i < N; i++)
            {
                if (j < 0)
                {
                    break;
                }
                if (i != j)
                {
                    if (tab[i][j] != tab[j][i])
                    {
                        skos_2 = false;
                        break;
                    }
                }
                else
                {
                    int a = i + 1;
                    int b = j - 1;
                    int c = i - 1;
                    int d = j + 1;
                    if (tab[a][b] != tab[i][j])
                    {
                        skos_2 = false;
                        break;
                    }
                    if (tab[c][d] != tab[i][j])
                    {
                        skos_2 = false;
                        break;
                    }
                }
                j--;
            }
            i = 0;
            j = N - 1;
            if (skos_2 == true)
            {
                if (tab[i][j] == 'X')
                {
                    x = 1;
                }
                if (tab[i][j] == 'O')
                {
                    x = 0;
                }
                if (x == 1)
                {
                    skos = true;
                    WIN = true;
                    cout << "WYGRYWA X!"<< endl;
                    exit(0);
                }
                if (x == 0)
                {
                    skos = true;
                    WIN = true;
                    cout << "WYGRYWA O!"<< endl;
                    exit(0);
                }
            }
        }
    }
    //***********************************KONIEC WARUNKOW
    /*if (WIN != true)
    {
        cout << "jeszcze brak wygranej!" << endl;
    }*/
}

void view(char tab[][49], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << " " << endl;
    } // wyswietlenie
}

int main ()
{
    unsigned N; //wielkosc tablicy kolko krzyzyk
    int Q = N*N; //ilosc mozliwych podmian znakow
    char name;
    cout << "GRA KOLKO I KRYZYK \nPodaj wielkosc tablicy do gry:" << endl;
    cin >> N;
    if (N%2 == 0 || N == 1 || N > 49)
    {
        do 
        {
            cout << "Podaj liczbe nieparzysta, rozna od 1 i mniejsza niz 49" << endl;
            cin >> N;
        }
        while (N%2 == 0 || N == 1 || N > 49);
    }
    cout << "Gracze podaja pozycje swojego znaku poprzez podanie do niego wspolrzednych."<< endl;
    cout << "W pierwszej kolejnosci podany jest numer wiersza, nastepnie kolumny." << endl;
    cout << "Rozgrywke rozpoczyna dowolny z graczy." << endl;

    char tab[49][49]; //tablica

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tab[i][j] = '-';
        }
    } // pierwsze zapelnienie

    view(tab, N);
    cout << " " << endl;
    cout << "Wpisz znak gracza, nastepnie wspolrzedne znaku oddzielone spacja, zaczynajac od zera!" << endl;
    do
    {
        cout << ">";
        cin >> name;
        if (name == 'X')
        {
            int i;
            cin >> i;
            if (i >= N)
            {
                cout << "Wspolrzedne zaczynaja sie od zera, a koncza na " << N - 1 << ". Podaj nr jeszcze raz." << endl;
                cin >> i;
            }
            int j;
            cin >> j;
            if (j >= N)
            {
                cout << "Wspolrzedne zaczynaja sie od zera, a koncza na " << N - 1 << ". Podaj nr jeszcze raz." << endl;
                cin >> j;
            }
            if (tab[i][j] == '-')
            {
                tab[i][j] = 'X';
            }
            else
            {
                cout << "Podales zajete wspolrzedne, kanciarzom przepada kolejka!" << endl;
            }
        }
        if (name == 'O')
        {
            int i;
            cin >> i;
            if (i >= N)
            {
                cout << "Wspolrzedne zaczynaja sie od zera, a koncza na " << N - 1 << ". Podaj nr jeszcze raz." << endl;
                cin >> i;
            }
            int j;
            cin >> j;
            if (i >= N)
            {
                cout << "Wspolrzedne zaczynaja sie od zera, a koncza na " << N - 1 << ". Podaj nr jeszcze raz." << endl;
                cin >> i;
            }
            if (tab[i][j] == '-')
            {
                tab[i][j] = 'O';
            }
            else
            {
                cout << "Podales zajete wspolrzedne, kanciarzom przepada kolejka!" << endl;
            }
        }
        Q--;
        view(tab, N);
        win_rules(tab, N);
    }
    while (Q != 0);

    view(tab, N);
    win_rules(tab, N);
    cout << "WYNIK NIEROZSTRZYGNIETY, KONIEC PARTII!" << endl;
    return 0;
}