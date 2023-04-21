// Aniela Fendrych
#include <iostream>
using namespace std;

long long suma;
const int N = 128; // do testow wpisywac N=10 ma byc 128, N TO ILOSC OBIEKTOW (polek, magazynow itd)

bool equal(char operacja[], char name[])
{
    int i = 0;
    do
    {
        if (operacja[i] == name[i])
        {
        }
        else
        {
            return false;
        }
        i++;
    }
    while (operacja[i] != '\0' );

    int j = 0;
    do
    {
        if (operacja[j] == name[j])
        {
        }
        else
        {
            return false;
        }
        j++;
    }
    while (name[j] != '\0' );

    return true;
}

struct Place //miejsce na towar
{
    char label[2]; //etykieta
    unsigned short count; //ilosc towaru 65535
    Place() //konstruktor
    {
        label[0] = '-';
        label[1] = '-'; //etykieta pusta
        count = 0; //ustawienie ilosci na zero
    }
    void clear () //zerowanie
    {
        label[0] = '-';
        label[1] = '-'; //etykieta pusta
        count = 0; //ustawienie ilosci na zero
    }
    void cout_label()
    {
        cout << label[0] << label[1] << endl;
    }
    void setLab(char d1, char d2)
    {
        //czy moze byc etykieta zerowa? 00, czy zrobic obsluge bledow gdy d > 9?
        label[0] = d1;
        label[1] = d2;
    }
    void put(int a)
    {
        if  (a + count <= 65535)
        {
            count += a;
            suma += a;
        }
        else
        {
            suma += 65535 - count;
            count = 65535;
        }
    }
    void pop(int a)
    {
        if (count < a)
        {
            suma -= count;
            count = 0;
        }
        else
        {
            suma -= a;
            count -= a;
        }
    }
};

struct Shelf
{
    Place place[N]; //tablica o dlugosci N, ktorej skladowe maja wlasciwosci Place
    short length;
    Shelf()
    {
        length = 0;
    }
    void set(int p)
    {
        for (int i = p; i < length; ++i)
        {
            suma -= place[i].count;
            place[i].clear();
        }
        for (int i = length; i < p; ++i) //czy bedzie ok?
        {
            suma -= place[i].count;
            place[i].clear();
        }
        length = p;
    }

    long long get_count()
    {
        long long sum = 0;
        for (int i = 0; i < length; i++)
        {
            sum += place[i].count;
        }
        return sum;
    }
};

struct Rack
{
    Shelf shelf[N]; //tablica o dlugosci N skladajaca sie z obiektow typu Shelf
    short length;
    Rack()
    {
        length = 0;
    }
    void set(int shelfs, int places)
    {
        for (int i = 0; i < shelfs; i++) //zwiekszanie tu bylo length
        {
            shelf[i].set(places);
        }
        for (int i = shelfs; i < length; i++) //zmniejszanie
        {
            shelf[i].set(0);
        }
        length = shelfs;
    }
    long long get_count()
    {
        long long sum = 0;
        for (int i = 0; i < length; i++)
        {
            sum += shelf[i].get_count();
        }
        return sum;
    }
};

struct Warehouse
{
    Rack rack[N];
    Shelf handy_shelf;
    short length;
    Warehouse()
    {
        length = 0;
    }
    void set(int racks, int shelfs, int places)
    {
        for (int i = 0; i < racks; i++) //zwiekszenie
        {
            rack[i].set(shelfs,places);
        }
        for (int i = racks; i < length; i++) //zmniejszenie
        {
            rack[i].set(0,0);
        }
        length = racks;
    }

    long long get_count()
    {
        long long sum = 0;
        for (int i = 0; i < length; i++) //suma we wszystkich regalach
        {
            sum += rack[i].get_count();
        }
        sum += handy_shelf.get_count(); //+suma polki podreczne
        return sum;
    }

    void mov(); // DO ZROBIENIA
};

struct Wholesaler
{
    Shelf handy_shelf;
    Rack handy_rack;
    Warehouse warehouse[N];
    short length;
    Wholesaler()
    {
        length = 0;
    }
    void set(int warehouses, int racks, int shelfs, int places)
    {
        for (int i = 0; i < warehouses; i++) //zwiekszanie
        {
            warehouse[i].set(racks, shelfs, places);
            warehouse[i].handy_shelf.set(places); //ustawienie handy
        }
        for (int i = warehouses; i < length; i++) //zmniejszanie
        {
            warehouse[i].set(0, 0, 0);
            warehouse[i].handy_shelf.set(0); //ustawienie handy na zero
        }
        length = warehouses;
    }

    void fill(int warehouses, int racks, int shelfs, int places, int a)
    {
        set(0, 0, 0, 0); //????????????????????????????? czy dobrze
        handy_rack.set(0, 0);
        handy_shelf.set(0);
        length = 0;
        suma = 0; //koniec wyzerowania

        set(warehouses, racks, shelfs, places); //nowe wypelnienie
        if (a > 65535)
        {
            a = 65535;
        }
        for (int w = 0; w < warehouses; w++)
        {
            for (int r = 0; r < racks; r++)
            {
                for (int s = 0; s < shelfs; s++)
                {
                    for (int p = 0; p < places; p++)
                    {
                            warehouse[w].rack[r].shelf[s].place[p].count = a;
                            suma += a;
                    }
                }
            }
            warehouse[w].handy_shelf.set(places);
            for (int p2 = 0; p2 < places; p2++)
            {
            warehouse[w].handy_shelf.place[p2].count = a;
            suma += a;
            }
        }

        handy_rack.set(shelfs,places);
        for (int s2 = 0; s2 < shelfs; s2++)
        {
            for (int p3 = 0; p3 < places; p3++)
            {
                handy_rack.shelf[s2].place[p3].count = a;
                suma += a;
            }
        }

        handy_shelf.set(places);
        for (int p4 = 0; p4 < places; p4++)
        {
            handy_shelf.place[p4].count = a;
            suma += a;
        }
    }
};

    Wholesaler wholesaler;
//napisac funkcje zewnetrzne ktore obbsluguja : set, put, pop, get
int main()
{
    bool comends = true;
    char operacja[15]; // dlugosc nazwy operacji do cin
    //rodzaje komend:
    //*************************************************
    char setap[] = "SET-AP";
    char setas[] = "SET-AS";
    char setar[] = "SET-AR";
    char setaw[] = "SET-AW";
    char sethw[] = "SET-HW";
    char seths[] = "SET-HS";
    char sethr[] = "SET-HR";
    char setlw[] = "SET-LW";
    char setlh[] = "SET-LH";
    char setlr[] = "SET-LR";
    char setls[] = "SET-LS";
    //*************************************************
    char putw[] = "PUT-W";
    char puth[] = "PUT-H";
    char putr[] = "PUT-R";
    char puts[] = "PUT-S";
    //*************************************************
    char fill[] = "FILL";
    //*************************************************
    char popw[] = "POP-W";
    char poph[] = "POP-H";
    char popr[] = "POP-R";
    char pops[] = "POP-S";
    //*************************************************
    char movw[] = "MOV-W";
    char movh[] = "MOV-H";
    char movr[] = "MOV-R";
    char movs[] = "MOV-S";
    //*************************************************
    char gets[] = "GET-S";
    char getls[] = "GET-LS";
    char gete[] = "GET-E";
    char getw[] = "GET-W";
    char getrw[] = "GET-RW";
    char getrh[] = "GET-RH";
    char getsw[] = "GET-SW";
    char getsh[] = "GET-SH";
    char getsr[] = "GET-SR";
    char getlw[] = "GET-LW";
    char getlh[] = "GET-LH";
    char getlr[] = "GET-LR";
    //
    char end[] = "END";
    while (comends)
    {
        cin >> operacja;
        if ( equal(operacja, setap) )
        {
            int w, r, s, p;
            cin >> w >> r >> s >> p;
            if (w >= N || r >= N || s >= N || p > N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].rack[r].shelf[s].set(p);
            }
        }
        if ( equal(operacja, setas) )
        {
            int w, r, s, p;
            cin >> w >> r >> s >> p;
            if (w >= N || r >= N || s > N || p > N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].rack[r].set(s, p);
            }
        }
        if ( equal(operacja, setar) )
        {
            int w, r, s, p;
            cin >> w >> r >> s >> p;
            if (w >= N || r > N || s > N || p > N || wholesaler.length <= w)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].set(r, s, p);
            }
        }
        if ( equal(operacja, setaw) )
        {
            int w, r, s, p;
            cin >> w >> r >> s >> p;
            if (w > N || r > N || s > N || p > N)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.set(w, r, s, p);
            }
        }
        if ( equal(operacja, sethw) )
        {
            int w, p;
            cin >> w >> p;
            if (w >= N || p > N || wholesaler.length <= w)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].handy_shelf.set(p);
            }
        }
        if ( equal(operacja, seths) ) //polka
        {
            int p;
            cin >> p;
            if (p >= N)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_shelf.set(p);
            }
        }
        if ( equal(operacja, sethr) ) //regal
        {
            int s, p;
            cin >> s >> p;
            if (s >= N || p >= N)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_rack.set(s, p);
            }
        }
        //LABEL
        if ( equal(operacja, setlw) )
        {
            int w, r, s, p;
            char dd[2];
            cin >> w >> r >> s >> p >> dd[0] >> dd[1];
            if (w >= N || r >= N || s >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s || wholesaler.warehouse[w].rack[r].shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].rack[r].shelf[s].place[p].setLab(dd[0], dd[1]);
                //cout << wholesaler.warehouse[w].rack[r].shelf[s].place[p].label[0] << wholesaler.warehouse[w].rack[r].shelf[s].place[p].label[1] << endl;
            }
        }
        if ( equal(operacja, setlh) )
        {
            int w, p;
            char dd[2];
            cin >> w >> p >> dd[0] >> dd[1];
            if (w >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].handy_shelf.place[p].setLab(dd[0], dd[1]);
                //cout << wholesaler.warehouse[w].handy_shelf.place[p].label[0] << wholesaler.warehouse[w].handy_shelf.place[p].label[1] << endl;
            }
        }
        if ( equal(operacja, setlr) )
        {
            int s, p;
            char dd[2];
            cin >> s >> p >> dd[0] >> dd[1];
            if (s >= N || p >= N || wholesaler.handy_rack.length <= s || wholesaler.handy_rack.shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_rack.shelf[s].place[p].setLab(dd[0], dd[1]);
                //cout << wholesaler.handy_rack.shelf[s].place[p].label[0] << wholesaler.handy_rack.shelf[s].place[p].label[1] << endl;
            }
        }
        if ( equal(operacja, setls) )
        {
            int p;
            char dd[2];
            cin >> p >> dd[0] >> dd[1];
            if (p >= N || wholesaler.handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_shelf.place[p].setLab(dd[0], dd[1]);
                //cout << wholesaler.handy_shelf.place[p].label[0] << wholesaler.handy_shelf.place[p].label[1] << endl;
            }
        }
        //PUT*
        if ( equal(operacja, putw) )
        {
            int w, r, s, p, a;
            cin >> w >> r >> s >> p >> a;
            if (w >= N || r >= N || s >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s || wholesaler.warehouse[w].rack[r].shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].rack[r].shelf[s].place[p].put(a);
            }
        }
        if ( equal(operacja, puth) )
        {
            int w, p, a;
            cin >> w >> p >> a;
            if (w >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].handy_shelf.place[p].put(a);
            }
        }
        if ( equal(operacja, putr) ) //regal
        {
            int s, p, a;
            cin >> s >> p >> a;
            if (s >= N || p >= N || wholesaler.handy_rack.length <= s || wholesaler.handy_rack.shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_rack.shelf[s].place[p].put(a);
            }
        }
        if ( equal(operacja, puts) ) //polka
        {
            int p, a;
            cin >> p >> a;
            if (p >= N || wholesaler.handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_shelf.place[p].put(a);
            }
        }
        //FILL
        if ( equal(operacja, fill) )
        {
            int w, r, s, p, a;
            cin >> w >> r >> s >> p >> a;
            if (w > N || r > N || s > N || p > N )
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.fill(w, r, s, p, a);
            }
        }
        //POP*
        if ( equal(operacja, popw) )
        {
            int w, r, s, p, a;
            cin >> w >> r >> s >> p >> a;
            if (w >= N || r >= N || s >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s || wholesaler.warehouse[w].rack[r].shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].rack[r].shelf[s].place[p].pop(a);
            }
        }
        if ( equal(operacja, poph) )
        {
            int w, p, a;
            cin >> w >> p >> a;
            if (w >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.warehouse[w].handy_shelf.place[p].pop(a);
            }
        }
        if ( equal(operacja, popr) )
        {
            int s, p, a;
            cin >> s >> p >> a;
            if (s >= N || p >= N || wholesaler.handy_rack.length <= s || wholesaler.handy_rack.shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_rack.shelf[s].place[p].pop(a);
            }
        }
        if ( equal(operacja, pops) )
        {
            int p, a;
            cin >> p >> a;
            if (p >= N || wholesaler.handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                wholesaler.handy_shelf.place[p].pop(a);
            }
        }
        //MOV*
        if ( equal(operacja, movw) )
        {
            int w1, r1, s1, w2, r2, s2, p, a;
            cin >> w1 >> r1 >> s1 >> w2 >> r2 >> s2 >> p >> a;
            if (w1 >= N || w2 >= N || r1 >= N || r2 >= N || s1 >= N || s2 >= N || p >= N 
            || wholesaler.length <= w1 || wholesaler.length <= w2 || wholesaler.warehouse[w1].length <= r1
            || wholesaler.warehouse[w2].length <= r2 || wholesaler.warehouse[w1].rack[r1].length <= s1 ||
            wholesaler.warehouse[w2].rack[r2].length <= s2 || wholesaler.warehouse[w1].rack[r1].shelf[s1].length <= p || wholesaler.warehouse[w2].rack[r2].shelf[s2].length <= p)
            {
                cout << "error" << endl; 
            }
            else
            {
                if (a > wholesaler.warehouse[w1].rack[r1].shelf[s1].place[p].count)
                {
                    a = wholesaler.warehouse[w1].rack[r1].shelf[s1].place[p].count;
                }
                if (a + wholesaler.warehouse[w2].rack[r2].shelf[s2].place[p].count > 65535)
                {
                    a = 65535 - wholesaler.warehouse[w2].rack[r2].shelf[s2].place[p].count;
                }
                if (a <= wholesaler.warehouse[w1].rack[r1].shelf[s1].place[p].count && (a + wholesaler.warehouse[w2].rack[r2].shelf[s2].place[p].count) <= 65535)
                {
                    wholesaler.warehouse[w1].rack[r1].shelf[s1].place[p].count -= a;
                    wholesaler.warehouse[w2].rack[r2].shelf[s2].place[p].count += a;
                }
            }
        }
        if ( equal(operacja, movh) )
        {
            int w, r, s, p, a;
            cin >> w >> r >> s >> p >> a;
            if (w >= N || r >= N || s >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s 
            || wholesaler.warehouse[w].rack[r].shelf[s].length <= p || wholesaler.warehouse[w].handy_shelf.length <= p)
            {
                cout << "error" << endl; 
            }
            else
            {
                if (a > wholesaler.warehouse[w].rack[r].shelf[s].place[p].count)
                {
                    a = wholesaler.warehouse[w].rack[r].shelf[s].place[p].count;
                }
                if (a + wholesaler.warehouse[w].handy_shelf.place[p].count > 65535)
                {
                    a = 65535 - wholesaler.warehouse[w].handy_shelf.place[p].count;
                }
                wholesaler.warehouse[w].rack[r].shelf[s].place[p].count -= a;
                wholesaler.warehouse[w].handy_shelf.place[p].count += a;

            }
        }
        if ( equal(operacja, movr) ) //pomiedzy magazynem a podrecznym regalem skladu
        {
            int w, r, s1, s2, p, a;
            cin >> w >> r >> s1 >> s2 >> p >> a;
            if (w >= N || r >= N || s1 >= N || s2 >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s1 
            || wholesaler.warehouse[w].rack[r].shelf[s1].length <= p || wholesaler.handy_rack.length <= s2 || wholesaler.handy_rack.shelf[s2].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                if (a > wholesaler.warehouse[w].rack[r].shelf[s1].place[p].count)
                {
                    a = wholesaler.warehouse[w].rack[r].shelf[s1].place[p].count;
                }
                if (a + wholesaler.handy_rack.shelf[s2].place[p].count > 65535)
                {
                    a = 65535 - wholesaler.handy_rack.shelf[s2].place[p].count;
                }
                wholesaler.warehouse[w].rack[r].shelf[s1].place[p].count -= a;
                wholesaler.handy_rack.shelf[s2].place[p].count += a;
            }
        }
        if ( equal(operacja, movs) ) //z podrecznego regalu skladu do podrecznej polki skladu
        {
            int s, p, a;
            cin >> s >> p >> a;
            if (s >= N || p >= N || wholesaler.handy_shelf.length <= p || wholesaler.handy_rack.length <= s || wholesaler.handy_rack.shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                if (a > wholesaler.handy_rack.shelf[s].place[p].count)
                {
                    a = wholesaler.handy_rack.shelf[s].place[p].count;
                }
                if (a + wholesaler.handy_shelf.place[p].count > 65535)
                {
                    a = 65535 - wholesaler.handy_shelf.place[p].count;
                }
                wholesaler.handy_rack.shelf[s].place[p].count -= a;
                wholesaler.handy_shelf.place[p].count += a;
            }
        }
        //GET**
        if ( equal(operacja, gets) )
        {
            cout << wholesaler.handy_shelf.get_count() << endl;
        }
        if ( equal(operacja, gete) )
        {
            cout << suma << endl;
        }
        if ( equal(operacja, getw) )
        {
            int w;
            cin >> w;
            if (w >= N || wholesaler.length <= w )
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.warehouse[w].get_count() << endl;
            }
        }
        if ( equal(operacja, getrw) )
        {
            int w, r;
            cin >> w >> r;
            if (w >= N || r >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r )
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.warehouse[w].rack[r].get_count() << endl;
            }
        }
        if ( equal(operacja, getrh) )
        {
            cout << wholesaler.handy_rack.get_count() << endl;
        }
        if ( equal(operacja, getsw) )
        {
            int w, r, s;
            cin >> w >> r >> s;
            if (w >= N || r >= N || s >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.warehouse[w].rack[r].shelf[s].get_count() << endl;
            }
        }
        if ( equal(operacja, getsh) )
        {
            int w;
            cin >> w;
            if (w >= N || wholesaler.length <= w)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.warehouse[w].handy_shelf.get_count() << endl;
            }
        }
        if ( equal(operacja, getsr) )
        {
            int s;
            cin >> s;
            if (s >= N || wholesaler.handy_rack.length <= s)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.handy_rack.shelf[s].get_count() << endl;
            }
        }

        if ( equal(operacja, getlw) )
        {
            int w, r, s, p;
            cin >> w >> r >> s >> p;
            if (w >= N || r >= N || s >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].length <= r || wholesaler.warehouse[w].rack[r].length <= s
            || wholesaler.warehouse[w].rack[r].shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.warehouse[w].rack[r].shelf[s].place[p].label[0] << wholesaler.warehouse[w].rack[r].shelf[s].place[p].label[1] << endl;
            }
        }
        if ( equal(operacja, getlh) )
        {
            int w, p;
            cin >> w >> p;
            if (w >= N || p >= N || wholesaler.length <= w || wholesaler.warehouse[w].handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.warehouse[w].handy_shelf.place[p].label[0] << wholesaler.warehouse[w].handy_shelf.place[p].label[0] << endl;
            }
        }
        if ( equal(operacja, getls) )
        {
            int p;
            cin >> p;
            if (p >= N || wholesaler.handy_shelf.length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.handy_shelf.place[p].label[0] << wholesaler.handy_shelf.place[p].label[1] << endl;
            }
        }
        if ( equal(operacja, getlr) )
        {
            int s, p;
            cin >> s >> p;
            if (s >= N || p >= N || wholesaler.handy_rack.length <= s || wholesaler.handy_rack.shelf[s].length <= p)
            {
                cout << "error" << endl;
            }
            else
            {
                cout << wholesaler.handy_rack.shelf[s].place[p].label[0] << wholesaler.handy_rack.shelf[s].place[p].label[1] << endl;
            }
        }
        // END
        if ( equal(operacja, end) )
        {
            comends = false;
            break;
        }
    }
    return 0;
}
