#include <iostream>
#include<string.h>
#include <type_traits>
#include <cstdint>
#include<typeinfo>

using namespace std;
class locuinta{
protected:
      char *nume;
      char *prenume;
      float suputila;
      float discount;
public:
      locuinta(char *, char *, float, float);
      ~locuinta();
      locuinta(locuinta &);
      virtual float chirie(){return 0;};
      virtual void afisare(ostream &out);
      char * get_nume(){return nume;};
      locuinta & operator =(locuinta &);
      friend istream & operator >>(istream &, locuinta &);
      friend ostream & operator <<(ostream &, locuinta &);
};
void locuinta:: afisare(ostream &out)
{
    out<<"Numele persoanei care detine locuinta: ";
    out<<nume<<"\n";
    out<<"Prenumele persoanei care detine locuinta: ";
    out<<prenume<<"\n";
    out<<"Suprafata utila a locuintei: ";
    out<<suputila<<"\n";
    out<<"Discountul care se aplica acestei locuinte pe metru patrat: ";
    out<<discount<<"\n";
}
locuinta ::~locuinta()
{
    delete [] nume;
    delete [] prenume;
    cout<<"Destructor locuinta...\n";

}
locuinta::locuinta(char *n=(char *)"\0", char *p=(char *)"\0", float sup=0, float disc=0)
{
    try  { nume=new char[strlen(n)];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    try  {  prenume=new char[strlen(p)];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    strcpy(nume,n);
    strcpy(prenume,p);
    suputila=sup;
    discount=disc;
}
locuinta :: locuinta (locuinta &l)
{
    try  {nume=new char[strlen(l.nume)];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    try  { prenume=new char[strlen(l.prenume)];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    strcpy(nume,l.nume);
    strcpy(prenume,l.prenume);
    suputila=l.suputila;
    discount=l.discount;
}
locuinta & locuinta:: operator=(locuinta &l)
{
    try  {nume=new char[strlen(l.nume)];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    try  { prenume=new char[strlen(l.prenume)];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    strcpy(nume,l.nume);
    strcpy(prenume,l.prenume);
    suputila=l.suputila;
    discount=l.discount;
    return *this;
}
istream & operator>>(istream &in, locuinta &l)
{
    cout<<"Numele persoanei care detine locuinta:\n";
    in>>l.nume;
    cout<<"Prenumele persoanei care detine locuinta:\n";
    in>>l.prenume;
    cout<<"Suprafata utila a locuintei:\n";
    in>>l.suputila;
    cout<<"Discountul care se aplica acestei locuinte pe metru patrat:\n";
    in>>l.discount;
    return in;
}

class apartament:public locuinta{
      int etaj;
      float pretinterior;
  public:

      apartament(char *, char *, float, float, int, float);
      ~apartament();
      apartament(apartament &a);
      float chirie();
      void afisare(ostream &out);
      apartament & operator =(apartament &a);
      friend istream & operator >>(istream &,apartament &);
      friend ostream & operator <<(ostream &,apartament &);
};
apartament :: ~apartament()
{
   cout<<"Destructor apartament...\n";
}
apartament:: apartament(char *n=(char *)"\0", char *p=(char *)"\0", float sup=0, float disc=0,int et=0,float pret1=0):locuinta(n,p,sup,disc)
{
    etaj=et;
    pretinterior=pret1;
}
apartament::apartament(apartament &a):locuinta(a)
{
    etaj=a.etaj;
    pretinterior=a.pretinterior;
}
apartament & apartament:: operator=(apartament &a)
{
    locuinta::operator=(a);
    etaj=a.etaj;
    pretinterior=a.pretinterior;
    return *this;
}
istream &operator >>(istream &in, apartament &a)
{
    locuinta &l=a;
    in>>l;
    cout<<"La ce etaj se afla apartamentul?\n";
    in>>a.etaj;
    cout<<"Ce pret are (pe metru patrat util):\n";
    in>>a.pretinterior;
    return in;
}
ostream &operator <<(ostream &out, apartament &a)
{
    locuinta &l=a;
    out<<l;
    out<<"Etajul la care se afla apartamentul: ";
    out<<a.etaj<<"\n";
    out<<"Pretul pe care il are (pe metru patrat util): ";
    out<<a.pretinterior<<"\n";
    return out;
}
void apartament :: afisare(ostream &out)
{
    locuinta l=*this;
    l.afisare(out);
    out<<"Etajul la care se afla apartamentul: ";
    out<<etaj<<"\n";
    out<<"Pretul pe care il are (pe metru patrat util): ";
    out<<pretinterior<<"\n";
}
float apartament :: chirie()
{
    float a=pretinterior*suputila;
    return a-a*(discount/100);
}
class casa : public locuinta{
      float pretinterior;
      float pretexterior;
      float supcurte;
      int nretaje;
      float *suputilaetaj;
  public:

      casa(char *, char *, float , float ,float, float, float, int, float*);
      ~casa();
      casa (casa &);
      float chirie();
      casa & operator=(casa &);
      void afisare(ostream &);
      friend ostream &operator<<(ostream &, casa &);
      friend istream &operator >>(istream &,casa &);

};
void casa :: afisare(ostream &out)
{
    locuinta l=*this;
    l.afisare(out);
    out<<"pretul pe metru patrat interior: ";
    out<<pretinterior<<"\n";
    out<<"pretul pe metru patrat exterior: ";
    out<<pretexterior<<"\n";
    out<<"suprafata curtii: ";
    out<<supcurte<<"\n";
    out<<"Nr etaje casa: ";
    out<<nretaje<<"\n";
    out<<"Suprafata utila pe fiecare etaj: ";
    for(int i=0;i<nretaje;i++)
    {
        out<<"Etaj "<<i<<": ";
        out<<suputilaetaj[i]<<" ";
    }
    out<<"\n";
}
casa :: ~casa()
{
    delete [] suputilaetaj;
    cout<<"Destructor casa...\n";
}
casa::casa(char *n=(char *)"\0", char *p=(char *)"\0", float sup=0, float disc=0,float pret1=0, float pret2=0, float curte=0,int nr=0, float *v={0}):locuinta(n,p,sup,disc)
{
    pretinterior=pret1;
    pretexterior=pret2;
    supcurte=curte;
    nretaje=nr;
    try  {suputilaetaj=new float[nretaje];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    for(int i=0;i<nretaje;i++)
        suputilaetaj[i]=v[i];

}
casa :: casa (casa &c):locuinta (c)
{
    pretinterior=c.pretinterior;
    pretexterior=c.pretexterior;
    supcurte=c.supcurte;
    nretaje=c.nretaje;
    try  {suputilaetaj=new float[nretaje];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    for(int i=0;i<nretaje;i++)
        suputilaetaj[i]=c.suputilaetaj[i];
}
casa& casa :: operator =(casa &c)
{
    locuinta::operator=(c);
    pretinterior=c.pretinterior;
    pretexterior=c.pretexterior;
    supcurte=c.supcurte;
    nretaje=c.nretaje;
    try  {suputilaetaj=new float[nretaje];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    for(int i=0;i<nretaje;i++)
        suputilaetaj[i]=c.suputilaetaj[i];
    return *this;
}
istream &operator>>(istream &in,casa &c)
{
    locuinta &l=c;
    in>>l;
    cout<<"Care este pretul pe metru patrat interior?\n";
    in>>c.pretinterior;
    cout<<"Care este pretul pe metru patrat exterior?\n";
    in>>c.pretexterior;
    cout<<"Care este suprafata curtii?\n";
    in>>c.supcurte;
    cout<<"Cate etaje are casa?\n";
    in>>c.nretaje;
    cout<<"Suprafata utila pe fiecare etaj:\n";
    try  {c.suputilaetaj=new float[c.nretaje];}
    catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
    for(int i=0;i<c.nretaje;i++)
    {
        cout<<"Etaj "<<i<<":\n";
        in>>c.suputilaetaj[i];
    }
    return in;
}
ostream & operator <<(ostream &out, casa &c)
{
    locuinta &l=c;
    out<<l;
    out<<"pretul pe metru patrat interior: ";
    out<<c.pretinterior<<"\n";
    out<<"pretul pe metru patrat exterior: ";
    out<<c.pretexterior<<"\n";
    out<<"suprafata curtii: ";
    out<<c.supcurte<<"\n";
    out<<"Nr etaje casa: ";
    out<<c.nretaje<<"\n";
    out<<"Suprafata utila pe fiecare etaj: ";
    for(int i=0;i<c.nretaje;i++)
    {
        out<<"Etaj "<<i<<": ";
        out<<c.suputilaetaj[i]<<" ";
    }
    out<<"\n";
    return out;
}
float casa :: chirie()
{
    float a=pretinterior*suputila;
    a=a-a*(discount/100);
    return a+pretexterior*supcurte;
}
ostream & operator<<(ostream &out,locuinta &l)
{
    l.afisare(out);
    return out;

}
template <class type >class gestiune{
    int i;
    type *L[100];
    int nrlocuinte;
    float *chirie;

  public:
    gestiune(int n=0){ nrlocuinte=n;
                       i=0;
                       try
                        {chirie=new float[nrlocuinte];}
                       catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
                       for(int i=0;i<nrlocuinte;i++)
                            {try{ L[i]=new type;}
                             catch(exception &e) { cout<<"Standard exception: " << e.what() << endl;}
                              }
                                       };
    gestiune & operator +=(type &l);
    void afisare();



};
template <class type> gestiune<type> & gestiune <type>:: operator +=(type &l)
{

   L[i]=new type(l);
   chirie[i]=l.chirie();
   i++;
   nrlocuinte=i;
   return *this;
}
template <class type> void gestiune <type> ::afisare()
{
    cout<<"\n\nNR DE LOCUINTE: "<<nrlocuinte<<"\n";
    cout<<"Chiria pe fiecare:";
    for(int j=0;j<nrlocuinte;j++)
        cout<<chirie[j]<<" ";
    cout<<"\n\n\n";
    cout<<"Informatii locuinte:\n";
    for(int j=0;j<i;j++)
        {   cout<<"Locuinta "<<j<<"\n";
            L[j]->afisare(cout);
            cout<<"\n";}

}
template<> class gestiune<apartament>{
    int nrclienti;
    char *nume[100];
    int i;
    apartament *L[100];
  public:
    gestiune(int n=0) {nrclienti=n;
                       i=0;
                       for(int j=0;j<nrclienti;j++)
                            {try{ L[j]=new apartament;}
                             catch(exception &e) { cout<<"Standard exception: " << e.what() << endl;}
                              }
                                            }
    gestiune<apartament>& operator+=(apartament &);
    void afisare();



};
gestiune <apartament> & gestiune <apartament> :: operator +=(apartament &a)
{

   try{L[i]=new apartament(a);}
   catch(exception &e){cout<<"Standard exception: "<<e.what() <<endl;}
   try{nume[i]=new char [strlen(a.get_nume())];}
   catch (exception& e){cout << "Standard exception: " << e.what() << endl;}
   strcpy(nume[i],a.get_nume());
   i++;
   nrclienti=i;
   return *this;
}
void gestiune <apartament> ::afisare()
{
    cout<<"\n\nNR DE clienti: "<<nrclienti<<"\n";
    cout<<"Numele fiecaruia:\n";
    for(int j=0;j<nrclienti;j++)
        cout<<nume[j]<<"\n\n\n";
    cout<<"Informatii locuinte:\n";
    for(int j=0;j<i;j++)
        {   cout<<"Locuinta "<<j<<"\n";
            L[j]->afisare(cout);
            cout<<"\n";}

    cout<<"\n";

}

int main()
{ int p;
  while(1)
  {cout<<"MENIU\n\n";
   cout<<"0.Iesiti\n";
   cout<<"1.Creati o gestiune de apartamente si afisati-o\n";
   cout<<"2.Creati o gestiune de case si afisati-o\n";
   cin>>p;
   if(p==1)
   {
      gestiune <apartament> G;
      cout<<"Introduceti numarul de apartamente:\n";
      cin>>p;
      apartament A[p];
      for(int i=0;i<p;i++)
      {
          cout<<"Introduceti datele apartamentului "<<i<<"\n";
          cin>>A[i];
      }
      for(int i=0;i<p;i++)
      {
          G+=A[i];
      }
      G.afisare();
   }
   else if(p==2)
   {
      gestiune <casa> G;
      cout<<"Introduceti numarul de case:\n";
      cin>>p;
      casa C[p];
      for(int i=0;i<p;i++)
      {
          cout<<"introduceti datele casei "<<i<<"\n";
          cin>>C[i];
      }
      for(int i=0;i<p;i++)
      {
          G+=C[i];
      }
      G.afisare();
   }
   else if(p==0) return 0;
   else cout<<"Comanda invalida, reintroduceti\n";
  }

    return 0;
}
