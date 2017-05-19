#include <iostream>
/*17.03.2017
PROJEKT 1: Obrotnica Kolejowa
ALGORYTMY I STRUKTURY DANYCH
Autor: Bartosz Łuczak
Wszelkie prawa zastrzeżone*/
using namespace std;

class Railway {
	int last_waggon;
	int *waggons;
	int howmany;
public:
	Railway()
	{
		this->howmany = 10000;
		waggons = new int[10000];
		last_waggon = -1;
	}
	Railway(int how_many)
	{
		waggons = new int[how_many];
		this->howmany = how_many;
		last_waggon = -1;
	}

	void AddWaggon(int id)
	{
		last_waggon++;
		waggons[last_waggon] = id;
	}
	void PushWaggon(int id)
	{
			int temp = waggons[0];
			int temp2;
			for (int i = 0; i < last_waggon + 1; i++)
			{
				temp2 = waggons[i + 1];
				waggons[i + 1] = temp;
				temp = temp2;
			}
			last_waggon++;
			waggons[0] = id;
	}
	void DeleteWaggon()
	{
		for (int i = 1; i <= last_waggon; i++)
		{
			waggons[i - 1] = waggons[i];
		}
		last_waggon--;
		if (last_waggon == -2) last_waggon = -1;
	}
	void GetWaggons()
	{
		cout << last_waggon + 1 << " ";
		for (int i = 0; i <=last_waggon ; i++)
		{
			cout << waggons[i] << " ";
		}
		cout << endl;
	}
	void OnTurntable(Railway &ttable)
	{
		if (this->last_waggon != -1 && ttable.last_waggon<ttable.howmany-1)
		{
			ttable.PushWaggon(this->waggons[0]);
			this->DeleteWaggon();
		}
	}

};

int Przesun(int oile, int wyjscie, int t)
{
	int flaga = 1;
	if (oile < 0)
	{
		flaga = 0;
		oile *= -1;
	}
	for (int i = 0; i < oile; i++)
	{
		if (flaga == 1)
		{
			wyjscie++;
			if (wyjscie == t) wyjscie = 0;
		}
		else if(flaga==0)
		{
			wyjscie--;
			if (wyjscie == -1) wyjscie = t - 1;
		}
	}
	return wyjscie;
}

int main()
{
		int t, n, id, instr, liczba;
		char  znak;
		int wyjscie = 0;
		cin >> t;

		Railway **tor = new Railway*[t];
		for (int i = 0; i < t; i++)
		{
			tor[i] = new Railway();
		}
		Railway obrotnica(10);
		for (int i = 0; i < t; i++)
		{
			cin >> n;
			for (int j = 0; j < n; j++)
			{
				cin >> id;
				tor[i]->AddWaggon(id);
			}
		}

		cin >> instr;
		for (int i = 0; i < instr; i++)
		{
			cin >> znak;
			switch (znak) {
			case 'z':
				cin >> liczba;
				wyjscie = Przesun(liczba, wyjscie, t);
				break;
			case 'o':
				cin >> liczba;
				wyjscie = Przesun(-liczba, wyjscie, t);
				break;
			case 'w':
				cin >> liczba;
				for (int i = 0; i < liczba; i++)
				{
					tor[wyjscie]->OnTurntable(obrotnica);
				}
				break;
			case 'j':
				cin >> liczba;
				for (int i = 0; i < liczba; i++)
				{
					obrotnica.OnTurntable(*tor[wyjscie]);
				}
				break;
			}

			cout << endl;
		}

		obrotnica.GetWaggons();
		int j=wyjscie;
		for (int i = 0; i < t ; i++)
		{
			tor[j]->GetWaggons();
			j++;
			if (j == t) j = 0;
		}
	
    return 0;
}

