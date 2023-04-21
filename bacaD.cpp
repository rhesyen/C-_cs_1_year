//Aniela Fendrych
#include <iostream>
using namespace std;

void funkcja_kierunek ( int a, int l, int v, int p, int kierunek[] )
{
    int x = 1; int y = 1; int z = 1;
    // pierwsza cwiartka brak zmian
    if ( l >= a/2 )
    {
    y = -1;
    }
    if ( v >= a/2 )
    {
    x = -1;
    }
    if ( p >= a/2 )
    {
    z = -1;
    }

    kierunek[0] = y;
    kierunek[1] = x;
    kierunek[2] = z;
  
}

int main ()
{
    char operacja;
    char C; char T; char O; char D; char E;
    int kierunek[3] = {0, 0, 0};

    unsigned a;
    //cout << "Podaj dlugosc boku a:" << endl;
    cin >> a;
    //unsigned h = a; unsigned w = a; unsigned d = a;

    if ( a <= 32 && a%2 == 0 )
    {
        long long tab[a][a][a];

        for ( int i = 0; i < a; i++) // d
        { 
            for ( int j = 0; j < a; j++ ) // h
            {
                for ( int k = 0; k < a; k++ ) // w
                {
                    cin >> tab[j][k][i]; //to odblokowac jak skoncze
                    //cout << "i :" << i << " j: " << j << " k: " << k << endl;
                }
            }
        } // zapelnianie zaczynajace sie od "k"
        // to odblokowac
      
        do // blok operacji
        {
            //cout << "Podaj operacje (C, T, O, D, E) gdzie E konczy operacje" << endl;
            cin >> operacja;
            // **********************************************************************************
            if ( operacja == 'D') // wyznacznik
            { 
                char k; unsigned i = 0;
                cin >> k >> i;
                bool det_non_zero = true;
                int dim = a;
                long long vect[a][a];
                int sign = 1;

                if ( i < 32 && a != 0 )
                {
                    ////////////////////////////////////////////
                    if ( k == 'l')
                    {
                        for(int k=0; k<a; k++)
                        {
                            for(int j=0; j<a; j++)
                            {
                                vect[k][j] = tab[i][k][j]; // tutaj te x y  w tab moglam pomieszac w kolejnosci
                                //cout << "vect[" << e <<"][" << f << "] " << endl;
                            }
                        }
                    }// przepisane wartosci z szescianu danych do macierzy vect
                    ////////////////////////////////////////////
                    else if ( k == 'v')
                    {
                        for(int k=0; k<a; k++)
                        {
                            for(int j=0; j<a; j++)
                            {
                                vect[k][j] = tab[k][i][j]; // tutaj te x y  w tab moglam pomieszac w kolejnosci
                                //cout << "vect[" << e <<"][" << f << "] " << endl;
                            }
                        }
                    }// przepisane wartosci z szescianu danych do macierzy vect
                    ////////////////////////////////////////////
                    else if ( k == 'p')
                    {
                        for(int k=0; k<a; k++)
                        {
                            for(int j=0; j<a; j++)
                            {
                                vect[k][j] = tab[k][j][i]; // tutaj te x y  w tab moglam pomieszac w kolejnosci
                                //cout << "vect[" << e <<"][" << f << "] " << endl;
                            }
                        }
                    }// przepisane wartosci z szescianu danych do macierzy vect
                    ////////////////////////////////////////////
                    for (int k = 0; k < dim - 1; k++)
                    {
                        int m = 0;
                        //Pivot - row swap needed
                        if ( vect[k][k] == 0 ) 
                        {
                            for ( m = k + 1; m < dim; m++ ) 
                            {
                                if ( vect[m][k] != 0 )
                                {   
                                    // odpowiednik swap vect[m] z vect[k]
                                    int j = 0;
                                    while ( j <= dim - 1 )
                                    {
                                        int temp = vect[k][j];
                                        vect[k][j] = vect[m][j];
                                        vect[m][j] = temp;
                                        j++;
                                    } // END swap

                                    sign = -sign;
                                    break;
                                }
                            }
                            //wyznacznik
                            if ( m == dim )
                            {
                                det_non_zero = false;
                            }
                        }
                        //No entries != 0 found in column k -> det = 0
                        if ( det_non_zero ) 
                        {
                            //Apply formula
                            for (int i = k + 1; i < dim; i++) 
                            {
                                for (int j = k + 1; j < dim; j++) 
                                {
                                    vect[i][j] = vect[k][k] * vect[i][j] - vect[i][k] * vect[k][j];

                                    if(k != 0) 
                                    {
                                        vect[i][j] /= vect[k-1][k-1]; // vect[i][j] = vect[i][j] / vect[k-1][k-1]; 
                                    }
                                }
                            }
                        }
                    }
                } // koniec i < 32
                if ( det_non_zero && a != 0 )
                {
                    cout << (sign * vect[dim-1][dim-1]) << endl;
                }
                else
                {
                    cout << 0 << endl;
                }
            } // operacja D
            // **********************************************************************************
            if ( operacja == 'C') // prostopadloscian
            {
                unsigned l, v, p, h, w, d; //poziom, pion, panel, wysokosc, szerokosc, glebokosc/ funkcja
                cin >> l >> v >> p >> h >> w >> d;
                long long int suma = 0;
                funkcja_kierunek ( a, l, v, p, kierunek );

                    for ( int i = 0; i <= h; i++)
                    { 
                        for ( int j = 0; j <= w; j++ )
                        {
                            for ( int k = 0; k <= d; k++ )
                            {
                                //cout << " sprawdzenie " << endl;
                                if (   l + kierunek[0]*i >= 0 
                                    && l + kierunek[0]*i < a 
                                    && v + kierunek[1]*j >= 0 
                                    && v + kierunek[1]*j < a
                                    && p + kierunek[2]*k >= 0 
                                    && p + kierunek[2]*k < a )
                                {
                                //cout << " sumuje" << endl;
                                suma += tab[ l + kierunek[0]*i ][ v + kierunek[1]*j ][ p + kierunek[2]*k ];
                                }
                            }
                        }
                    }
                cout << suma << endl;
            } // operacja C
            // **********************************************************************************
            if ( operacja == 'O') 
            {
                unsigned l, v, p, r; //poziom, pion, panel, wysokosc, szerokosc, glebokosc/ funkcja
                cin >> l >> v >> p >> r;
                long long int suma = 0;
                funkcja_kierunek ( a, l, v, p, kierunek );

                    for ( int i = 0; i <= r; i++)
                    {
                        for ( int j = 0; j <= r; j++ )
                        {
                            for ( int k = 0; k <= r; k++ )
                            {
                                //cout << " sprawdzenie " << endl;
                                if (     l + kierunek[0]*i >= 0
                                      && l + kierunek[0]*i < a 
                                      && v + kierunek[1]*j >= 0
                                      && v + kierunek[1]*j < a
                                      && p + kierunek[2]*k >= 0
                                      && p + kierunek[2]*k < a )
                                {
                                    if ( ((i)*(i) + (j)*(j) + (k)*(k) <= r*r) )
                                    {
                                        // cout << " sumuje "<<( (i - l)*(i - l) + (j - v)*(j - v) + (k - p)*(k - p) <= r*r )<< " coordy: " << i << ',' << j << ',' << k<<endl;
                                        suma += tab[ l + kierunek[0]*i ][ v + kierunek[1]*j ][ p + kierunek[2]*k ];
                                    }
                                }
                            }
                        }
                    }

                cout << suma << endl;
            } // operacja O
            // **********************************************************************************
            if ( operacja == 'T') 
            {
                unsigned l, v, p, e; //poziom, pion, panel, wysokosc, szerokosc, glebokosc/ funkcja
                cin >> l >> v >> p >> e;
                long long int suma = 0;
                funkcja_kierunek ( a, l, v, p, kierunek );

                    for ( int i = 0; i <= e; i++)
                    { 
                        for ( int j = 0; j <= e; j++ )
                        {
                            for ( int k = 0; k <= e; k++ )
                            {
                                //cout << " sprawdzenie " << endl;
                                if (     l + kierunek[0]*i >= 0
                                      && l + kierunek[0]*i < a 
                                      && v + kierunek[1]*j >= 0
                                      && v + kierunek[1]*j < a
                                      && p + kierunek[2]*k >= 0
                                      && p + kierunek[2]*k < a )
                                {
                                    if ( ((i) + (j) + (k) <= e) )
                                    {
                                        // cout << " sumuje "<<( (i - l)*(i - l) + (j - v)*(j - v) + (k - p)*(k - p) <= r*r )<< " coordy: " << i << ',' << j << ',' << k<<endl;
                                        suma += tab[ l + kierunek[0]*i ][ v + kierunek[1]*j ][ p + kierunek[2]*k ];
                                    }
                                }
                            }
                        }
                    }
                cout << suma << endl;
            } // operacja T
            // **********************************************************************************
        } while ( operacja != 'E' );

    } //if duze odblokowac

    return 0;
} //main