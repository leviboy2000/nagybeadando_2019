#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <list>


using namespace std;



struct termek
{
    string id;
    string forrashely;
    string celhely;
    int meret;
};

struct kocsi ///vonathoz csatlakoztatható kocsi
{
    string azonosito;
    int kapacitas = 0;
    string kezdo_allomas;
    list<termek> tartalma; ///mi van belepakolva
};


struct vonat ///vonat hova megy
{
    string id;
    int kapacitas;
    map<string,int> allomasok; /// allomas neve es hogy mikor van ott
    list<kocsi> csatlakoztatott_kocsik;
};




void pakol(kocsi &k, termek &t, int &m)
{
    if(m<=(k.kapacitas-k.tartalma.size()))
    {
        for(int i=0; i<m; i++)
        {
            k.tartalma.push_back(t);
        }
    }
    else
    {
        cout << "Nincs eleg hely a bepakolashoz! :(" << endl;
    }
}

void kipakol(kocsi &k, termek &t, int &m)
{
    int kipakoltak_szama =0;
    list<termek>::iterator it = k.tartalma.begin();
    while(it!=k.tartalma.end() && kipakoltak_szama <m)
    {
        if(it->id == t.id)
        {
            k.tartalma.erase(it);
            kipakoltak_szama++;
        }
        else
        {
            it++;
        }
    }

}

void csatol(vonat &v, kocsi &k)
{
    if (v.csatlakoztatott_kocsik.size() < v.kapacitas)
    {
        v.csatlakoztatott_kocsik.push_back(k);
    }
    else
    {
        cout << "Nem lehet tobb kocsit csatlakoztatni! :(" << endl;
    }
}

void lecsatol(vonat &v, kocsi &k)
{
    list<kocsi>::iterator it = v.csatlakoztatott_kocsik.begin();
    while(it != v.csatlakoztatott_kocsik.end())
    {
        if(it->azonosito == k.azonosito)
        {
            v.csatlakoztatott_kocsik.erase(it);
            break;
        }
    }
}


int main()
{
    kocsi k;
    vonat v;
    termek t;


    string azon, kezd, kap;

    ifstream infile("kocsik.txt");
    if (infile.is_open())
    {
        while(infile.good())
        {
            getline(infile,azon,' ');
            k.azonosito = azon;
            cout << azon << '\t';

            getline(infile,kap,' ');
            k.kapacitas = stoi(kap);
            cout << k.kapacitas << '\t';

            getline(infile,kezd);
            k.kezdo_allomas = kezd;
            cout << kezd << endl;

        }
        infile.close();
        cout << endl;
    }

    else
    {
        cout << "a kocsikat tartalmazo fajlt nem sikerult megnyitni";

    }








    string i, forr, cel, mer;

    ifstream infile2("aruk.txt");
    if (infile2.is_open())
    {
        while(infile2.good())
        {
            getline(infile2,i,' ');
            t.id = i;
            cout << i << '\t';

            getline(infile2,forr,' ');
            t.forrashely = forr;
            cout << forr << '\t';

            getline(infile2,cel,' ');
            t.celhely = cel;
            cout << cel << '\t';

            getline(infile2,mer);
            t.meret = stoi(mer);
            cout << t.meret << endl;

        }
        infile.close();
        cout << endl;
    }

    else
    {
        cout << "az arukat tartalmazo fajlt nem sikerult megnyitni";

    }

    int mennyiseg=0; ///mennyi cuccot akarunk bepakolni
    pakol(k,t,mennyiseg); ///kell egy kocsi, egy termék és hogy mennyit rakjunk bele

    kipakol(k,t,mennyiseg);

    csatol(v, k);

    lecsatol(v,k);

    return 0;
}
