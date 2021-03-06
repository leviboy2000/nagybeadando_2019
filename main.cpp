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
    string allomas;
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

void beolvas(vector<termek> &termekek, vector<kocsi> &kocsik, vector<vonat> &vonatok)
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

            getline(infile,kap,' ');
            k.kapacitas = stoi(kap);

            getline(infile,kezd);
            k.allomas = kezd;

            kocsik.push_back(k);

        }
        infile.close();
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

            getline(infile2,forr,' ');
            t.forrashely = forr;

            getline(infile2,cel,' ');
            t.celhely = cel;

            getline(infile2,mer);
            t.meret = stoi(mer);

            termekek.push_back(t);

        }
        infile2.close();
    }

    else
    {
        cout << "az arukat tartalmazo fajlt nem sikerult megnyitni";

    }

    string kapacitas,ido,allomas;
    int ido_szammal;
    map<string,int> all;

    ifstream infile3("menetrend.txt");
    if (infile3.is_open())
    {
        while(infile3.good())
        {
            getline(infile3,v.id, ' ');
            getline(infile3,kapacitas);
            v.kapacitas = stoi(kapacitas);
            while(getline(infile3,allomas, ' ')) ///addig olvassa egy vonat menetrendjét, amíg nincs üres sor (utána a következő jön)
            {
                getline(infile3, ido, ' ');
                ido_szammal = stoi(ido);
                v.allomasok[allomas]=ido_szammal;
            }
            vonatok.push_back(v);

        }
        infile3.close();
    }

    else
    {
        cout << "az arukat tartalmazo fajlt nem sikerult megnyitni";

    }
}


int main()
{
    vector<termek> termekek;
    vector<kocsi> kocsik;
    vector<vonat> vonatok;

    beolvas(termekek, kocsik, vonatok);

    int mennyiseg=0; ///mennyi cuccot akarunk bepakolni
    //pakol(k,t,mennyiseg); ///kell egy kocsi, egy termék és hogy mennyit rakjunk bele

    //kipakol(k,t,mennyiseg);

    //csatol(v, k);

    //lecsatol(v,k);

    return 0;
}
