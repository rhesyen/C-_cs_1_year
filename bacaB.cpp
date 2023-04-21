// Aniela Fendrych

void insertionSort(int arr[], int n);
bool Element(int x, int array[]);
void Add(int x, int array[]);
void Complement(int array1[], int array2[]);
void Union(int array1[], int array2[], int suma[]);
bool Nonempty(int array[]);
void Intersection(int array1[], int array2[], int wsp[]);
bool Equal(int array1[], int array2[]);
void Cardinality(int array[], int *size);
bool Subset(int array1[], int array2[]);
double Arithmetic(int array[]);
bool Empty(int array[]);
void Symmetric(int array1[], int array2[], int result[]);
void MinMax(int array[], int *min, int &max);
void Create(int n, int array[], int result[]);
void Difference(int array1[], int array2[], int result[]);
double Harmonic(int array[]);
void Properties(int array[], char action[], double &arithmentic, double *harmonic, int &min, int *max, int &size);

bool Element(int x, int array[])
{
    int i = 0;
    while( array[i] != -1 ) {
        if( array[i] == x ) return true;
        i += 1;
    }

    return false;
}

void Add(int x, int array[])
{
    int i = 0;
    while( array[i] != (-1) ){i += 1;}

    // dodanie elementu 
    if( x > 0 && x < 4096 )
    {
        if( !Element(x, array) )
        {
            array[i] = x;
            array[i+1] = -1;  
        }
    }

    // ile elementow 
    int size = 0;
    while( array[size] != (-1) )
    {
        size += 1;
    }
    
    // sortowanie
    insertionSort(array, size);
}  

void Union(int array1[], int array2[], int suma[])
{
    int i_array1=0;
    int i_array2=0;
    int i_suma=0;

    // przepisanie 1. zbioru
    while( array1[i_array1] != (-1) )
    {
        suma[i_suma] = array1[i_array1];

        i_suma += 1; //kończy z indeksem wartości -1 
        i_array1 += 1; //kończy z indeksem wartości -1
    }
    
    // dodanie elementow z 2. zbioru
    while( array2[i_array2] != -1 )
    {
        bool is = false;
        i_array1=0;
        while( array1[i_array1] != -1 )
        {
            if( array1[i_array1] == array2[i_array2]) 
            {
                is = true;
            }
            i_array1++; //kończy z indeksem wartości -1
        }
        if( !is )
        {
            suma[i_suma] = array2[i_array2];
            i_suma += 1;
        }
        i_array2++;
    }

    // sortowanie
    insertionSort(suma, i_suma);

    // dodanie wartości -1
    suma[i_suma] = -1;
}

bool Empty(int array[])
{
    if( array[0] == -1 ) return true;
    else return false;
}

bool Nonempty(int array[])
{
    if( !Empty(array) ) return true;
    else return false;
}

void Intersection(int array1[], int array2[], int wsp[])
{
    int i_array1=0;
    int i_array2=0;
    int i_wsp=0;
    
    while( array1[i_array1] != -1 )
    {
        bool is = false;
        i_array2=0;
        while( array2[i_array2] != -1 )
        {
            if( array1[i_array1] == array2[i_array2]) 
            {
                is = true;
            }
            i_array2++;
        }
        if( is )
        {
            wsp[i_wsp] = array1[i_array1];
            i_wsp++;
        }
        i_array1 += 1;
    }

    // sortowanie
    insertionSort(wsp, i_wsp);

    wsp[i_wsp] = -1;
}

void Complement(int array1[], int array2[])
{   
    int i_array = 0;
    for(int i=1; i<4096; i++)
    {
        if( !Element(i, array1) )
        {
            array2[i_array] = i;
            i_array++;
        }
    }

    insertionSort(array2, i_array);

    array2[i_array] = -1;
}

bool Equal(int array1[], int array2[])
{
    int i_array1=0;
    int i_array2=0;

    int size_1 = 0;
    while( array1[i_array1] != (-1) )
    {
        size_1 += 1;
        i_array1 += 1;
    }

    int size_2 = 0;
    while( array2[i_array2] != (-1) )
    {
        size_2 += 1;
        i_array2 += 1;
    }

    bool the_same = true;
    if( Empty(array1) && Empty(array2) ) the_same = true;
    else if( size_1 != size_2 ) the_same = false;
    else
    {
        for(int i=0; i<size_1; i++)
        {
            if( !Element(array1[i], array2) ) the_same = false;           
        }
    }

    return the_same;
}

bool Subset(int array1[], int array2[])
{

    int i_array1 = 0;
    int i_array2 = 0;

    // jezeli pusta
    if( Empty(array2) && Nonempty(array1) ) return false;
    else if( Empty(array2) && Empty(array1) ) return true;
    else if ( Empty(array1) && Nonempty(array2) ) return true;
    
    else 
    {
        
        while( array1[i_array1] != -1 )
        {
            bool zawiera = false;
            i_array2 = 0;
            while( array2[i_array2] != -1 )
            {
                if( array1[i_array1] == array2[i_array2] )
                {
                    zawiera = true;
                }
                i_array2 += 1;
            }
            
            if( zawiera == false ) return false;

            i_array1 += 1;
        }

        return true;
    }
}

double Arithmetic(int array[])
{
    int i = 0;
    int size = 0;
    while( array[i] != (-1) )
    {
        size += 1;
        i += 1;
    }

    if( size == 0 ) return 0;

    double sum = 0;
    i = 0;

    
    while( array[i] != (-1) )
    {
        sum += array[i];
        i = i + 1;
    }

    return sum/size;
}

double Harmonic(int array[])
{

    int size = 0;
    int i = 0;
    while( array[i] != (-1) )
    {
        i++;
        size += 1;
    }

    if( size == 0 ) return 1;

    i = 0;
    double mian = 0;

    while( array[i] != (-1) )
    {
        mian += (1/(double)array[i]);
        i += 1;
    }
    return size/mian;
}

void MinMax(int array[], int *min, int &max)
{

    int size = 0;
    int i = 0;
    while( array[i++] != (-1) )
    {
        size += 1;
    }

    if( size != 0 )
    {
        if( size == 1 )
        {
            max = array[0];
            *min = array[0];
        }
        else
        {
            max = array[0];
            *min = array[0];
            // min
            int i=1;
            while( array[i] != (-1) )
            {
                if( !(array[i] > *min)) *min = array[i];
                i += 1;
            }

            // max
            i = 0;
            while( array[i] != (-1) )
            {
                if( !(array[i] < max)) max = array[i];
                i += 1;
            }
        }     
    }
    
}

void Create(int n, int array[], int result[])
{
    result[0] = -1;
    for(int i=0; i<n; i++) {
        int elem = array[i];
        Add(elem, result);
    }
        

    // size
    int size = 0;
    int j = 0;
    while( result[j] != (-1) )
    {
        size += 1;
        j += 1;
    }

    // sortowanie
    insertionSort(result, size);
}

void Cardinality(int array[], int *size)
{
    *size = 0;
    int tmp = 0;
    int i = 0;
    while( array[i] != (-1) )
    {
        tmp += 1;
        i += 1;
    }
    *size = tmp;
}

void Difference(int array1[], int array2[], int result[])
{
    int i_array1 = 0;
    int i_array2 = 0;
    int i_result = 0;

    while( array1[i_array1] != -1 )
    {
        bool is = false;
        i_array2 = 0;
        while( array2[i_array2] != -1 )
        { 
            if( !(array1[i_array1] != array2[i_array2]) )
            {
                is = true;
            }
            i_array2 += 1;
        }

        if( !is )
        {
            result[i_result] = array1[i_array1];
            i_result += 1;
        }

        i_array1 += 1;
    }
    insertionSort(result, i_result);

    result[i_result] = -1;
}

void Properties(int array[], char action[], double &arithmentic, double *harmonic, int &min, int *max, int &size)
{
    int index = 0;
    while( action[index] != 0 )
    {
        char comm = action[index++];
        switch (comm)
        {
        case 'a':
            arithmentic = Arithmetic(array);
            break;
        
        case 'h':
            *harmonic = Harmonic(array);
            break;

        case 'm':
            MinMax(array, &min, *max);
            break;

        case 'c':
            Cardinality(array, &size);
            break;
        }
    }
}

void Symmetric(int array1[], int array2[], int result[])
{
    // result = A/B
    Difference(array1,array2,result);

    // size result
    int i = 0;
    int tmp_ind = 0;
    while( result[i] != (-1) )
    {
        tmp_ind++;
        i++; // last index
    }

    int i_array1 = 0;
    int i_array2 = 0;
    int i_result = tmp_ind;

    while( array2[i_array2] != -1 )
    {
        bool is = false;
        i_array1 = 0;
        while( array1[i_array1] != -1 ) { 
            if( array2[i_array2] == array1[i_array1] ) {
                is = true;
            }
            i_array1 += 1;
        }

        if( !is ) {
            result[i_result] = array2[i_array2];
            i_result += 1;
        }

        i_array2 += 1;
    }
    
    insertionSort(result, i_result);

    result[i_result] = -1;
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int tmp = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > tmp) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = tmp;
    }
}


