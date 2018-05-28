#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

class Tranzitie
{
    char stanga;
    vector<string> dreapta;
public:
    string getstanga()const;
    bool seaflaindreapta(string s);
    friend istream &operator>>(istream&in,Tranzitie & obj);
    friend ostream &operator<<(ostream&out,Tranzitie const & obj);
};

string Tranzitie::getstanga() const {
    string aux=" ";
    aux[0]=stanga;
    return aux;
}

ostream &operator<<(ostream&out,Tranzitie const & obj)
{
    out<<obj.stanga<<"->";
    for(string s:obj.dreapta)
        out<<s<<"|";
    return out;
}

istream& operator>>(istream & in,Tranzitie & obj)
{
    in>>obj.stanga;
    int x;
    in>>x;
    string aux;
    while(x)
    {
        in>>aux;
        obj.dreapta.push_back(aux);
        x--;
    }
    return in;
}

bool Tranzitie::seaflaindreapta(string s) {
    for(string X:dreapta)
        if(X==s)
            return true;
    return false;
}

class Gramatica
{
    vector<Tranzitie> tranzitii;
public:
    friend istream &operator>>(istream & in,Gramatica & obj);
    friend ostream &operator<<(ostream & out,Gramatica const & obj);
    set<string> deundeseobtine(string s);
};

ostream& operator<<(ostream&out,Gramatica const&obj)
{
    for(Tranzitie X:obj.tranzitii)
        out<<X<<endl;
    return out;
}

set<string> Gramatica::deundeseobtine(string s) {
    set<string> raspuns;
    for(Tranzitie x:tranzitii)
    {
        if(x.seaflaindreapta(s))
            raspuns.insert(x.getstanga());
    }
    return raspuns;
}

vector<string> produscartezian(set<string>M1,set<string>M2)
{
    vector<string> raspuns;
    for(string X:M1)
        for (string Y:M2)
        {
            string aux=X+Y;
            raspuns.push_back(X + Y);
        }
    return raspuns;
}

istream& operator>>(istream&in,Gramatica&obj)
{
    int l;
    in>>l;
    while(l)
    {
        Tranzitie aux;
        in>>aux;
        obj.tranzitii.push_back(aux);
        l--;
    }
    return in;
}

int main() {
    string cuvant;
    cout<<"Cuvantul ";
    cin>>cuvant;
    int L=cuvant.size(),i,j,k;
    Gramatica G;
    ifstream fin("cyk.in");
    fin>>G;
    cout<<G<<endl;
    fin.close();
    set<string> Tabel[L][L];
    for(i=0;i<L;i++)
    {
        string aux=" ";aux[0]=cuvant[i];
        for(string X:G.deundeseobtine(aux))
            Tabel[0][i].insert(X);
    }
    for(i=1;i<L;i++)
        for(j=0;j<L-i;j++)
        {
            for(k=0;k<i;k++)
            {
                vector<string>produs=produscartezian(Tabel[i-k-1][j],Tabel[k][j+i-k]);
                for(string S:produs)
                    for (string X:G.deundeseobtine(S))
                        Tabel[i][j].insert(X);
            }
        }
    k=0;
    for(string S:Tabel[L-1][0])
        if(S[0]=='S')
            k=1;
    for(i=0;i<L;i++)
    {
        for(j=0;j<L-i;j++)
        {
            cout<<"{";
            for (string S:Tabel[i][j])
                cout << S << " ";
            cout<<"}\t\t";
        }
        cout<<endl;
    }
    if(k)
        cout<<"Apartine\n";
    else
        cout<<"Nu apartine\n";
    return 0;
}