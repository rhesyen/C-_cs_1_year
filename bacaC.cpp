//Aniela Fendrych

void Add(int a, int tab[]);
void Complement(int tab_1[], int tab_2[]);
void Union(int tab_1[], int tab_2[], int suma[]);
void MinMax(int tab[], int min, int max);
void Intersection(int tab_1[],int tab_2[], int wspolna[]);
bool Equal(int tab_1[], int tab_2[]);
double Harmonic(int tab[]);
void Cardinality(int tab[], int *size);
double Arithmetic(int tab[]);
void Symmetric(int tab_1[], int tab_2[], int wynik[]);
void Create (int N, int tab[], int wynik[]);
void Properties();

void Swap(int *a, int *b) { // zamiana miejscami
  int zmn = *a;
  *a = *b;
  *b = zmn;
}

void Sortowanie(int tab[], int N){
  int mniejsze;
  
  for (int i = 0; i < N -1; i++){
    mniejsze = i;
    for (int j = i +1; j < N; j++){
      if (tab[mniejsze] > tab[j]) {
        mniejsze = j;
      }
      Swap(&tab[i], &tab[mniejsze]);
    }
  }
}

bool Empty(int tab[]) {return tab[0] == -1;}

bool Nonempty(int tab[]) {return tab[0] != -1;}

bool Element(int e, int tab[]) {
  for (int i = 0; tab[i] != -1; ++i) {
    if (tab[i] == e) return true;
  }
    return false;
}

void Difference(int tab_1[], int tab_2[], int wynik[]) {
  int indeks1 = 0;
  int indeks2 = 0;
  int wyn = 0;
  for (; tab_1[indeks1] != (-1); ++indeks1) {
    bool is = false; // czy to poprawny zapis??
    while (tab_2[indeks2] != (-1)) {
      if (tab_1[indeks1] == tab_2[indeks2]) {
        is = true; // jesli dwa argumenty zbiorow beda sobie rowne, to znaczy ze sie nie roznia
      }
      indeks2 = indeks2 + 1;
    }//while
    if (is == false) {
      wynik[wyn] = tab_1[indeks1];
      wyn = wyn + 1; // kolejny element do porownania
    }
  } //for
  Sortowanie(wynik, wyn); // sortuj
  wynik[wyn] = -1; // na ostatnie miejsce -1
}
