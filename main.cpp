#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
ifstream f("in.txt");
ofstream g("out.txt");
class NumarComplex                                //clasa numar complex
{
	float real;
	float imag;
public:
	float ModulNrComplex();
	friend ostream& operator<<(ostream&, const NumarComplex&);                   //supraincarcare operatorului <<
	friend istream& operator>>(istream&, NumarComplex&);
	NumarComplex Suma(NumarComplex &a, const NumarComplex& b);
	NumarComplex Produs(NumarComplex &a, const NumarComplex &b);
	NumarComplex operator+(const NumarComplex& b);                             //supraincarcare operatorului + pentru a aduna nr complexe
	NumarComplex operator*(const NumarComplex& a);
	NumarComplex& operator=(const NumarComplex& a);
	NumarComplex(const NumarComplex &z);
	NumarComplex(float re = 0, float im = 0);
	~NumarComplex();
};
NumarComplex::NumarComplex(const NumarComplex& z)
{
	real = z.real;
	imag = z.imag;
}
NumarComplex& NumarComplex:: operator=(const NumarComplex& a)
{
	if (this != &a)
	{
		real = a.real;
		imag = a.imag;
	}
	return *this;
}
NumarComplex::NumarComplex(float re, float im)
{
	real = re;
	imag = im;
}
NumarComplex::~NumarComplex() {}
NumarComplex NumarComplex:: operator+(const NumarComplex& b)                                //supraincarcare operatorului + pentru a aduna nr complexe
{
	NumarComplex h;
	h.real = real + b.real;
	h.imag = imag + b.imag;
	return  h;
}
NumarComplex NumarComplex:: operator*(const NumarComplex& a)                               //supraincarcarea operatorului * pentru a inmulti nr complexe
{
	NumarComplex nr;
	nr.real = (real*a.real) - (imag * a.imag);
	nr.imag = (real*a.imag) + (imag * a.real);
	return nr;
}
NumarComplex NumarComplex::Suma(NumarComplex &a, const NumarComplex& b)                        //functie ce calculeaza suma dintre doua numere complexe
{
	NumarComplex sum;
	sum = a + b;
	return sum;
}

NumarComplex NumarComplex::Produs(NumarComplex& a, const NumarComplex& b)                      //functie ce calculeaza produsul dintre doua numere complexe
{
	NumarComplex c;
	c = a * b;
	return c;
}
float NumarComplex::ModulNrComplex()                      //supraincarcare operatorului >>
{
	float modul;
	modul = sqrt(real * real + imag * imag);
	return modul;
}

istream& operator>>(istream& in, NumarComplex& num)                             //supraincarcare operatorului >>  pentru a citi un nr complex
{
	in >> num.real;
	in >> num.imag;
	return in;
}
ostream& operator<<(ostream& out, const NumarComplex& num)                     //supraincarcare operatorului << pentru a afisa un nr complex
{
	if (num.imag > 0)
	{
		out << num.real << "+" << num.imag << "i";
	}
	else if (num.imag == 0)
	{
		out << num.real;
	}
	else if (num.imag < 0)
	{
		out << num.real << num.imag << "i";
	}
	return out;
}


class VectoriDeComplecsi                                                 // clasa pentru vectori de nr complexe
{
protected:
	NumarComplex *h;
	int n;
public:
	friend class NumarComplex;
	friend  istream& operator>>(istream&, VectoriDeComplecsi&);            //supraincarcare operatorului >>
	friend  ostream& operator<<(ostream&, VectoriDeComplecsi&);            //supraincarcare operatorului <<
	VectoriDeComplecsi(int nr = 0);                                       //constructor cu parametru nr de elemente
	~VectoriDeComplecsi();                                                //destructor
	VectoriDeComplecsi(const VectoriDeComplecsi &v);                      //constructor de copiere
	void CalculModuleVector(int k);                                            //calculul modulelor unui vector de nr complexe
	void SumaElemVector(int k);                                                //suma elementelor unui vector de nr complexe
	void SortareVector(int k);                                                 //sortarea unui vector de numere complexe dupa modulele elementelor
	NumarComplex operator *(VectoriDeComplecsi& b);                       //supraincarcarea operatorului *
	VectoriDeComplecsi operator =(VectoriDeComplecsi& c);
	int SetN();
};

VectoriDeComplecsi::VectoriDeComplecsi(int nr)                          //constructor
{
	int i;
	n = nr;
	h = new NumarComplex[n];
	for (i = 0; i < n; i++)
	{
		h[i] = (0, 0);
	}
}

VectoriDeComplecsi::VectoriDeComplecsi(const VectoriDeComplecsi &v)                        //constructor
{
	int i;
	n = v.n;
	h = new NumarComplex[n];
	for (i = 0; i < n; i++)
	{
		h[i] = v.h[i];
	}
}
VectoriDeComplecsi::~VectoriDeComplecsi()                                                //destructorul
{
	n = 0;
	delete h;
}

void VectoriDeComplecsi::CalculModuleVector(int k)                               //calculul modulelor unui vector de nr complexe
{
	float p[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = h[i].ModulNrComplex();
	}
	for (int i = 0; i < n; i++)
	{
		if (k == 1)
		{
			cout << p[i] << " ";
		}
		else
		{
			g << p[i] << endl;
		}
	}
}
void VectoriDeComplecsi::SumaElemVector(int k)                                //suma elementelor unui vector de nr complexe
{
	NumarComplex sum = (0, 0);
	for (int i = 0; i < n; i++)
	{
		sum = sum + h[i];
	}
	if (k == 1)
	{
		cout << sum << endl;
	}
	else
	{
		g << sum << endl;
	}
}

void VectoriDeComplecsi::SortareVector(int k)                                                 //sortarea unui vector de numere complexe dupa modulele elementelor
{
	float p[n];
	NumarComplex *t;
	t = new NumarComplex[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = h[i].ModulNrComplex();
		t[i] = h[i];
	}
	NumarComplex aux;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[i] > p[j])
			{
				aux = t[i];
				t[i] = t[j];
				t[j] = aux;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (k == 1)
		{
			cout << t[i] << " ";
		}
		else
		{
			g << t[i] << endl;
		}
		t[i].~NumarComplex();
	}
	cout << endl;
}

NumarComplex VectoriDeComplecsi::operator *(VectoriDeComplecsi& b)
{
	NumarComplex c = (1, 1);
	for (int i = 0; i < n; i++)
	{
		c = c.Suma(c, c.Produs(b.h[i], h[i]));
	}
	return c;
}

VectoriDeComplecsi VectoriDeComplecsi::operator =(VectoriDeComplecsi& c)
{
	if (this != &c)
	{
		n = c.n;
		h = new NumarComplex[n];
		for (int i = 0; i < n; i++)
		{
			h[i] = c.h[i];
		}
	}
	return *this;
}

int VectoriDeComplecsi::SetN()
{
	return n;
}


istream& operator>>(istream& in, VectoriDeComplecsi& num)          //supraincarcare operatorului >> pentru a citi un vector de complecsi
{
	for (int i = 0; i < num.n; i++)
	{
		in >> num.h[i];
	}
	return  in;
}
ostream& operator<<(ostream& out, VectoriDeComplecsi& num)        //supraincarcare operatorului << pentru a afisa un vecotor de complecsi
{

	for (int i = 0; i < num.n; i++)
	{
		out << num.h[i] << endl;
	}
	return out;
}
class Stiva :public VectoriDeComplecsi
{
public:
	void Adaugare(const NumarComplex&);
	NumarComplex Stergere();
	Stiva operator =(Stiva&);

	Stiva(int nr = 0, int t = 0) :VectoriDeComplecsi(nr)                       //constructor de initializare
	{
		h = new NumarComplex[t];
	}

	~Stiva()                                                               //destructor
	{
		n = 0;
		delete[]h;
	}

	Stiva(const Stiva &v)                                                  //constructor de copiere
	{
		int i;
		n = v.n;
		h = new NumarComplex[n];
		for (i = 0; i < n; i++)
		{
			h[i] = v.h[i];
		}
	}

};

NumarComplex Stiva::Stergere()
{
	NumarComplex p;
	p = h[n - 1];
	h[n - 1].~NumarComplex();
	n--;
	return p;
}

void Stiva::Adaugare(const NumarComplex &c)
{
	NumarComplex *j;
	j = new NumarComplex[n];
	for (int i = 0; i < n; i++)
	{
		j[i] = h[i];
		h[i].~NumarComplex();
	}
	n++;
	h = new NumarComplex[n];
	for (int i = 0; i < n - 1; i++)
	{
		h[i] = j[i];
		j[i].~NumarComplex();
	}
	h[n - 1] = c;
}

Stiva Stiva::operator =(Stiva& c)
{
	if (this != &c)
	{
		this->n = c.n;
		this->h = new NumarComplex[this->n];
		for (int i = 0; i < n; i++)
		{
			this->h[i] = c.h[i];
		}
	}
	return *this;
}

class Coada :public VectoriDeComplecsi
{
public:
	friend istream& operator>>(istream&, VectoriDeComplecsi&);
	friend ostream& operator<<(ostream&, VectoriDeComplecsi&);
	void Adaugare(const NumarComplex&);
	NumarComplex Stergere();
	Coada operator =(Coada&);

	Coada(int nr = 0, int t = 0) :VectoriDeComplecsi(nr)
	{
		h = new NumarComplex[t];
	}

	~Coada()
	{
		n = 0;
		delete[]h;
	}

	Coada(const Coada &v)
	{
		int i;
		n = v.n;
		h = new NumarComplex[n];
		for (i = 0; i < n; i++)
		{
			h[i] = v.h[i];
		}
	}
};

NumarComplex Coada::Stergere()
{
	NumarComplex t;
	t = h[0];
	for (int i = 0; i < n; i++)
	{
		h[i] = h[i + 1];
	}
	h[n].~NumarComplex();
	n--;
	return t;
}

void Coada::Adaugare(const NumarComplex &c)
{
	NumarComplex *j;
	j = new NumarComplex[n];
	for (int i = 0; i < n; i++)
	{
		j[i] = h[i];
		h[i].~NumarComplex();
	}
	n++;
	h = new NumarComplex[n];
	for (int i = 0; i < n - 1; i++)
	{
		h[i] = j[i];
		j[i].~NumarComplex();
	}
	h[n - 1] = c;
}

Coada Coada::operator =(Coada& c)
{
	if (this != &c)
	{
		n = c.n;
		h = new NumarComplex[n];
		for (int i = 0; i < n; i++)
		{
			h[i] = c.h[i];
		}
	}
	return *this;
}


void meniu()                                                    //meniul
{
	int k = 0;
	int r = 11, n, m;
	NumarComplex c, d, sum, prod;
	VectoriDeComplecsi l;
	while (1)
	{
		if (k == 0)
		{
			cout << "Alegeti metoda prin care se citesc informatiile : " << endl;               //citire fisier/consola
			cout << "1.Citire si afisare in consola" << endl;
			cout << "2.Citire si afisare din fisier" << endl;
			cin >> k;
		}
		else if (k == 1)
		{
			switch (r)
			{
			case 0:
				cout << "Alegeti o alta varinata din cele de mai sus" << endl;
				cin >> r;
				break;
			case 1:
				cout << "Dati doua numere complexe:" << endl;
				cin >> c;
				cin >> d;
				cout << "Suma dintre numarul " << c << " si numarul " << d << " este " << sum.Suma(c, d) << endl;
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
				cout << endl;
				break;
			case 2:
				cout << "Dati doua numere complexe:" << endl;
				cin >> c;
				cin >> d;
				cout << "Produsul dintre numarul " << c << " si numarul " << d << " este " << prod.Produs(c, d) << endl;
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
				cout << endl;
				break;
			case 3:
				cout << "Dati un numar complex :" << endl;
				cin >> c;
				cout << "Modulul numarului " << c << " este " << c.ModulNrComplex() << endl;
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
				cout << endl;
				break;
			case 4:
			{
				cout << "Dati un numar de elemente pentru vector : ";
				cin >> n;
				VectoriDeComplecsi l(n);
				cout << "Dati elementele vectorului(perechi de cate 2): " << endl;
				cin >> l;
				cout << "Se afiseaza elementele vecoturului : " << endl;
				cout << l;
				cout << "Se afiseaza vectorul de module : " << endl;
				l.CalculModuleVector(k);
				l.~VectoriDeComplecsi();
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
			}
			break;
			case 5:
			{
				cout << "Dati numarul de elemente pentru un vector de numere complexe" << endl;
				cin >> n;
				VectoriDeComplecsi t(n);
				cout << "Dati elementele vectorului(perechi de cate 2): " << endl;
				cin >> t;
				cout << "Se afiseaza elementele vecoturului : " << endl;
				cout << t;
				cout << "Se afiseaza vectorul de module : " << endl;
				t.CalculModuleVector(k);
				cout << "Se afiseaza vectorul sortat in functie de modul : " << endl;
				t.SortareVector(k);
				t.~VectoriDeComplecsi();
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
			}
			break;
			case 6:
			{
				cout << "Dati numarul de elemente pentru un vector de numere complexe" << endl;
				cin >> n;
				VectoriDeComplecsi q(n);
				cout << "Dati elementele vectorului(perechi de cate 2): " << endl;
				cin >> q;
				cout << "Se afiseaza elementele vecoturului : " << endl;
				cout << q;
				cout << "Suma elementelor din vector este : ";
				q.SumaElemVector(k);
				q.~VectoriDeComplecsi();
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
			}
			break;
			case 7:
			{
				cout << "Dati numarul de elemente pentru primul vector de numere complexe" << endl;
				cin >> n;
				VectoriDeComplecsi l(n);
				cout << "Dati elementele vectorului 1 (perechi de cate 2): " << endl;
				cin >> l;
				cout << "Dati numarul de elemente pentru al doilea  vector de numere complexe" << endl;
				cin >> m;
				VectoriDeComplecsi q(m);
				cout << "Dati elementele vectorului 2 (perechi de cate 2): " << endl;
				cin >> q;
				if (m == n)
				{
					cout << "Produsul scalar intre cei doi vectori este : " << l * q << endl;
				}
				else
				{
					cout << "Produsul scalar nu se poate calcula dearece vectorii au lungimi diferite.";
				}
				l.~VectoriDeComplecsi();
				q.~VectoriDeComplecsi();
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
			}
			break;
			case 8:
			{
				Stiva a(0);
				cout << "Dati numarul de elemente ce vreti sa fie introduse in stiva:" << endl;
				cin >> m;
				for (int i = 0; i < m; i++)
				{
					cout << "Dati un element ce trebuie introdus in stiva : " << endl;
					cin >> c;
					a.Adaugare(c);
					cout << "Stiva:" << endl;
					cout << a;
				}
				for (int i = 0; i < m; i++)
				{
					cout << "Scot elementul: " << endl;
					d = a.Stergere();
					cout << d << endl;
					cout << "Stiva:" << endl;
					cout << a;
				}
				a.~Stiva();
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
			}
			break;
			case 9:
			{
				Coada b(0);
				cout << "Dati numarul de elemente ce vreti sa fie introduse in coada:" << endl;
				cin >> m;
				for (int i = 0; i < m; i++)
				{
					cout << "Dati un element ce trebuie introdus in coada : " << endl;
					cin >> c;
					b.Adaugare(c);
					cout << "Coada:" << endl;
					cout << b;
				}
				for (int i = 0; i < m; i++)
				{
					cout << "Scot elementul: " << endl;
					d = b.Stergere();
					cout << d << endl;
					cout << "Coada:" << endl;
					cout << b;
				}
				b.~Coada();
				cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
				cin >> r;
			}
			break;
			case 10:
				k = 0;
				break;
			case 11:
				cout << "Alegeti una dintre variantele urmatoare : " << endl;
				cout << "1.Suma dintre doua numere complexe. " << endl;
				cout << "2.Produsul dintre doua numere complexe. " << endl;
				cout << "3.Aflarea modulului unui numar complex. " << endl;
				cout << "4.Aflarea vectorului de module. " << endl;                                 //meniu secundar consola
				cout << "5.Sortarea unui vector in functie de vectorul de module. " << endl;
				cout << "6.Suma elementelor unui vector de numere complexe. " << endl;
				cout << "7.Produsul scalar dintre doi vectori de numere complexe. " << endl;
				cout << "8.Verificare functii stiva" << endl;
				cout << "9.Verificare functii coada" << endl;
				cout << "10.Revenire la meniul principal. " << endl;
				cin >> r;
				break;
			default:
				cout << "Numarul nu se afla printre variante.Apasati un numar de la 1 la 8" << endl;
				cin >> r;
				break;;
			}

		}
		else if (k == 2)
		{
			f >> c >> d;
			g << "Suma dintre numarul " << c << " si numarul " << d << " este " << sum.Suma(c, d) << endl;
			g << "Produsul dintre numarul " << c << " si numarul " << d << " este " << prod.Produs(c, d) << endl;
			g << "Modulul numarului " << c << " este " << c.ModulNrComplex() << endl;
			g << "Modulul numarului " << d << " este " << d.ModulNrComplex() << endl;
			f >> n;
			VectoriDeComplecsi l(n);
			f >> l;
			g << "Se afiseaza elementele vecoturului 1 : " << endl;                                                //afisare in fisier
			g << l;
			g << "Se afiseaza vectorul de module : " << endl;
			l.CalculModuleVector(k);
			g << "Se afiseaza vectorul sortat in functie de modul : " << endl;
			l.SortareVector(k);
			g << "Suma elementelor din vector este : ";
			l.SumaElemVector(k);
			f >> m;
			VectoriDeComplecsi o(m);
			f >> o;
			g << "Se afiseaza elementele vecoturului 2 : " << endl;
			g << o;
			if (m == n)
			{
				g << "Produsul scalar intre cei doi vectori este : ";
				g << l * o << endl;
			}
			else
				g << "Produsul scalar nu se poate calcula deoarece vectorii au lungimi diferite." << endl;
			l.~VectoriDeComplecsi();
			o.~VectoriDeComplecsi();

			Coada w(0);
			f >> m;
			for (int i = 0; i < m; i++)
			{

				f >> c;
				w.Adaugare(c);
				g << "Coada:" << endl;
				g << w;
			}
			for (int i = 0; i < m; i++)
			{
				g << "Scot elementul: " << endl;
				d = w.Stergere();
				g << d << endl;
				g << "Coada:" << endl;
				g << w;
			}
			w.~Coada();

			Stiva a(0);
			f >> m;
			for (int i = 0; i < m; i++)
			{

				f >> c;
				a.Adaugare(c);
				g << "Stiva:" << endl;
				g << a;
			}
			for (int i = 0; i < m; i++)
			{
				g << "Scot elementul: " << endl;
				d = a.Stergere();
				g << d << endl;
				g << "Stiva:" << endl;
				g << a;
			}
			a.~Stiva();
			cout << "Pentru a reveni la meniul anterior apasati 0." << endl;
			cin >> k;
		}
	}
}

int main()
{
	meniu();
	return 0;
	f.close();
	g.close();
}
