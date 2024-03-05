#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;
const int X = 6;
const int Y = 6;
const int Z = X * Y;
const int linie = 24;
const int przesuniecie = 10;
const int ZET = 8;

struct gracz {
	string imie;
	char zeton;
};
struct rozgrywka {
	string ruch;
	char tab[X][Y];
};
void undo(char tab[][Y],rozgrywka tab1[], gracz gracz1, gracz gracz2,int &licznik) {
	int undo;
	int sprawdzenie;
	do {
		sprawdzenie = 0;
		cout << "Wybierz ilosc ruchow do cofniecia (od 1 do 4): " << endl;
		cin >> undo;
		if (undo < 1 || undo>4) {
			cout << "Bledna ilosc. Podaj ponownie: " << endl;
			sprawdzenie = 1;
		}
	} while (sprawdzenie == 1);
	undo += 1;
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			tab[i][j] = tab1[licznik-undo].tab[i][j];
	licznik -= undo;
}
void zapis1(char tab[][Y],rozgrywka tab1[],int &licznik){ //zapisywanie ruchow gracza 1
	for(int i=0;i<X;i++)
		for(int j=0;j<Y;j++)
			tab1[licznik].tab[i][j] = tab[i][j];
	tab1[licznik].ruch = "Ruch gracza 1";
	licznik++;
}
void zapis2(char tab[][Y], rozgrywka tab1[], int &licznik) { //zapisywanie ruchow gracza 2
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			tab1[licznik].tab[i][j] = tab[i][j];
	tab1[licznik - 1].ruch = "Ruch gracza 2";
	licznik++;
}
void pauza(){
	int sprawdzenie;
	char start;
	system("cls"); 
	cout << "Gra zatrzymana (pauza)" << endl;
	cout << "Nacisnij k aby kontynuowac.." << endl;
	do {
		sprawdzenie = 0;
		cin >> start;
		if (start != 'k') {
			cout << "Wprowadzono bledny znak. Nacisnij k aby kontynuowac.." << endl;
			sprawdzenie = 1;
		}
	} while (sprawdzenie == 1);
	system("cls");
}
void predefiniowana(char tab[][Y], gracz gracz1, gracz gracz2) {
	tab[0][4] = gracz1.zeton;
	tab[1][1] = gracz1.zeton;
	tab[1][0] = gracz1.zeton;
	tab[1][2] = gracz1.zeton;
	tab[1][3] = gracz1.zeton;
	tab[2][1] = gracz1.zeton;
	tab[3][0] = gracz1.zeton;
	tab[3][1] = gracz1.zeton;
	tab[4][2] = gracz1.zeton;
	tab[0][1] = gracz2.zeton;
	tab[1][2] = gracz2.zeton;
	tab[1][4] = gracz2.zeton;
	tab[4][0] = gracz2.zeton;
	tab[4][4] = gracz2.zeton;
	tab[5][1] = gracz2.zeton;
	tab[5][4] = gracz2.zeton;
	tab[5][5] = gracz2.zeton;
}
void obrotqz(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = 0; i < X / 2; i++) {
		for (int j = 0; j < Y / 2; j++) {    //przepisanie cwiartki do innej tablicy z zamiana wierszy z kolumnami
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = 0; i < X / 2; i++) {
		buf = tab2[i][0];
		tab2[i][0] = tab2[i][Y / 2 - 1];   // zamiana skrajnych kolumn w cwiartce
		tab2[i][Y / 2 - 1] = buf;
	}
	for (int i = 0; i < X / 2; i++) {
		for (int j = 0; j < Y / 2; j++) {  //przeisanie zmienionej cwiartki do oryginalnej tabeli
			tab[i][j] = tab2[i][j];
		}
		cout << endl;
	}
}
void obrotwz(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = 0; i < X / 2; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = X / 2; i < X; i++) {
		buf = tab2[i][0];
		tab2[i][0] = tab2[i][Y / 2 - 1];
		tab2[i][Y / 2 - 1] = buf;
	}
	for (int i = 0; i < X / 2; i++) {
		for (int j = Y / 2; j < Y; j++) {   
			tab[i][j] = tab2[i + 3][j - 3];
		}
		cout << endl;
	}
}
void obrotaz(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = X / 2; i < X; i++) {
		for (int j = 0; j < Y / 2; j++) {
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = 0; i < X / 2; i++) {
		buf = tab2[i][Y / 2];
		tab2[i][Y / 2] = tab2[i][Y - 1];
		tab2[i][Y - 1] = buf;
	}
	for (int i = X / 2; i < X; i++) {
		for (int j = 0; j < Y / 2; j++) {
			tab[i][j] = tab2[i - 3][j + 3];
		}
		cout << endl;
	}
}
void obrotsz(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = X / 2; i < X; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = X / 2; i < X; i++) {
		buf = tab2[i][0];
		tab2[i][0] = tab2[i][Y / 2 - 1];
		tab2[i][Y / 2 - 1] = buf;
	}
	for (int i = X / 2; i < X; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab[i][j] = tab2[i][j];
		}
		cout << endl;
	}
}
void obrotqx(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = 0; i < X / 2; i++) {
		for (int j = 0; j < Y / 2; j++) {    //przepisanie cwiartki do innej tablicy z zamiana wierszy z kolumnami
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = 0; i < X / 2; i++) {
		buf = tab2[0][i];                 // zamiana skrajnych wierszy w cwiartce
		tab2[0][i] = tab2[Y / 2 - 1][i];
		tab2[Y / 2 - 1][i] = buf;
	}
	for (int i = 0; i < X / 2; i++) {
		for (int j = 0; j < Y / 2; j++) {  //przeisanie zmienionej cwiartki do oryginalnej tabeli
			tab[i][j] = tab2[i][j];
		}
		cout << endl;
	}
}
void obrotwx(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = 0; i < X / 2; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = 0; i < Y/2 ; i++) {
		buf = tab2[X/2][i];
		tab2[X/2][i] = tab2[X - 1][i];
		tab2[X  - 1][i] = buf;
	}
	for (int i = 0; i < X / 2; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab[i][j] = tab2[i + 3][j - 3];
		}
		cout << endl;
	}
}
void obrotax(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = X / 2; i < X; i++) {
		for (int j = 0; j < Y / 2; j++) {
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = X / 2; i < X; i++) {
		buf = tab2[0][i];
		tab2[0][i] = tab2[Y / 2 - 1][i];
		tab2[Y / 2 - 1][i] = buf;
	}
	for (int i = X / 2; i < X; i++) {
		for (int j = 0; j < Y / 2; j++) {
			tab[i][j] = tab2[i - 3][j + 3];
		}
		cout << endl;
	}
}
void obrotsx(char tab[][Y]) {
	int buf;
	int tab2[X][Y];
	for (int i = X / 2; i < X; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab2[j][i] = tab[i][j];
		}
	}
	for (int i = X / 2; i < X; i++) {
		buf = tab2[0][i];
		tab2[0][i] = tab2[Y / 2 - 1][i];
		tab2[Y / 2 - 1][i] = buf;
	}
	for (int i = X / 2; i < X; i++) {
		for (int j = Y / 2; j < Y; j++) {
			tab[i][j] = tab2[i][j];
		}
		cout << endl;
	}
}
void postaw_pionek(char tab[][Y], gracz gracz) {
	char plansza;
	int pole;
	int buf;
	int sprawdzenie;
	do {
		sprawdzenie = 0;
		cout << "Wybierz plansze do wstawienia pionka: " << endl;
		cout << "q - plansza lewa gorna" << endl;
		cout << "w - plansza prawa gorna" << endl;
		cout << "a - plansza lewa dolna" << endl;
		cout << "s - plansza prawa dolna" << endl;
		cin >> plansza;
		cout << "Wybierz pole(od 1 do 9 - jak na klawiaturze numerycznej): " << endl;
		cin >> pole;
		if (pole == 0 ||pole>9|| isalpha((unsigned char)pole)) {
			cout << "Wprowadzono niewlasciwe pole. Wprowadz dane ponownie: " << endl;
			cin.clear();
			sprawdzenie = 1;
			continue;
		}
		pole -= 1;
		switch (plansza) {
		case 'q':
			for (int i = 0; i < X / 2; i++) {
				buf = tab[0][i];                  //zamiana wierszy
				tab[0][i] = tab[Y / 2 - 1][i];
				tab[Y / 2 - 1][i] = buf;        
			}
			if (tab[pole / 3][pole % 3] == ' ') {
				tab[pole / 3][pole % 3] = gracz.zeton;    //stawianie pionka jesli pole jest puste i zamiana wierszy z powrotem
				for (int i = 0; i < X / 2; i++) {
					buf = tab[0][i];
					tab[0][i] = tab[Y / 2 - 1][i];
					tab[Y / 2 - 1][i] = buf;
				}
			}
			else {
				for (int i = 0; i < X / 2; i++) {
					buf = tab[0][i];
					tab[0][i] = tab[Y / 2 - 1][i];      //zamiana wierszy z powrotem jesli pole bylo zajete
					tab[Y / 2 - 1][i] = buf;
				}
				cout << "Pole zajete. Podaj inne wspolrzedne: " << endl;
				sprawdzenie = 1;
			}
			break;
		case 'w':
			for (int i = 3; i < X; i++) {
				buf = tab[0][i];
				tab[0][i] = tab[Y / 2 - 1][i];
				tab[Y / 2 - 1][i] = buf;
			}
			if (tab[pole / 3][(pole % 3) + 3] == ' ') {
				tab[pole / 3][(pole % 3) + 3] = gracz.zeton;
				for (int i = 3; i < X; i++) {
					buf = tab[0][i];
					tab[0][i] = tab[Y / 2 - 1][i];
					tab[Y / 2 - 1][i] = buf;
				}
			}
			else {
				for (int i = 3; i < X; i++) {
					buf = tab[0][i];
					tab[0][i] = tab[Y / 2 - 1][i];
					tab[Y / 2 - 1][i] = buf;
				}
				cout << "Pole zajete. Podaj inne wspolrzedne: " << endl;
				sprawdzenie = 1;
			}
			break;
		case 'a':
			for (int i = 0; i < X / 2; i++) {
				buf = tab[Y / 2][i];
				tab[Y / 2][i] = tab[Y - 1][i];
				tab[Y - 1][i] = buf;
			}
			if (tab[(pole / 3) + 3][pole % 3] == ' ') {
				tab[(pole / 3) + 3][pole % 3] = gracz.zeton;
				for (int i = 0; i < X / 2; i++) {
					buf = tab[Y / 2][i];
					tab[Y / 2][i] = tab[Y - 1][i];
					tab[Y - 1][i] = buf;
				}
			}
			else {
				for (int i = 0; i < X / 2; i++) {
					buf = tab[Y / 2][i];
					tab[Y / 2][i] = tab[Y - 1][i];
					tab[Y - 1][i] = buf;
				}
				cout << "Pole zajete. Podaj inne wspolrzedne: " << endl;
				sprawdzenie = 1;
			}
			break;
		case 's':
			for (int i = X / 2; i < X; i++) {
				buf = tab[Y / 2][i];
				tab[Y / 2][i] = tab[Y - 1][i];
				tab[Y - 1][i] = buf;
			}
			if (tab[(pole / 3) + 3][(pole % 3) + 3] == ' ') {
				tab[(pole / 3) + 3][(pole % 3) + 3] = gracz.zeton;
				for (int i = X / 2; i < X; i++) {
					buf = tab[Y / 2][i];
					tab[Y / 2][i] = tab[Y - 1][i];
					tab[Y - 1][i] = buf;
				}
			}
			else {
				for (int i = X / 2; i < X; i++) {
					buf = tab[Y / 2][i];
					tab[Y / 2][i] = tab[Y - 1][i];
					tab[Y - 1][i] = buf;
				}
				cout << "Pole zajete. Podaj inne wspolrzedne: " << endl;
				sprawdzenie = 1;
			}
			break;
		default: cout << "Wprowadzono niewlasciwa plansze. Wprowadz dane ponownie" << endl;
			sprawdzenie = 1;
			break;
		}
	} while (sprawdzenie == 1);
}
void obrot(char tab[][Y]) {
	char plansza;
	char obrot;
	int sprawdzenie;
	do {
		sprawdzenie = 0;
		cout << "Wybierz plansze do obrocenia: " << endl;
		cout << "q - plansza lewa gorna" << endl;
		cout << "w - plansza prawa gorna" << endl;
		cout << "a - plansza lewa dolna" << endl;
		cout << "s - plansza prawa dolna" << endl;
		cin >> plansza;
		switch (plansza) {
		case 'q':
			cout << "Wybierz sposob obrotu planszy: " << endl;
			cout << "z - zgodnie z ruchem wskazowek zegara" << endl;
			cout << "x - odwrotnie do ruchu wskazowek zegara" << endl;
			cin >> obrot;
			switch (obrot) {
			case 'z': obrotqz(tab);
				break;
			case 'x': obrotqx(tab);
				break;
			default: cout << "Wprowadzono zly sposob obrotu planszy. Wprowadz ponownie: " << endl;
				sprawdzenie = 1;
				break;
			}
			break;
		case 'w':
			cout << "Wybierz sposob obrotu planszy: " << endl;
			cout << "z - zgodnie z ruchem wskazowek zegara" << endl;
			cout << "x - odwrotnie do ruchu wskazowek zegara" << endl;
			cin >> obrot;
			switch (obrot) {
			case 'z': obrotwz(tab);
				break;
			case 'x': obrotwx(tab);
				break;
			default: cout << "Wprowadzono zly sposob obrotu planszy. Wprowadz ponownie: " << endl;
				sprawdzenie = 1;
				break;
			}
			break;
		case 'a':
			cout << "Wybierz sposob obrotu planszy: " << endl;
			cout << "z - zgodnie z ruchem wskazowek zegara" << endl;
			cout << "x - odwrotnie do ruchu wskazowek zegara" << endl;
			cin >> obrot;
			switch (obrot) {
			case 'z': obrotaz(tab);
				break;
			case 'x': obrotax(tab);
				break;
			default: cout << "Wprowadzono zly sposob obrotu planszy. Wprowadz ponownie: " << endl;
				sprawdzenie = 1;
				break;
			}
			break;
		case 's':
			cout << "Wybierz sposob obrotu planszy: " << endl;
			cout << "z - zgodnie z ruchem wskazowek zegara" << endl;
			cout << "x - odwrotnie do ruchu wskazowek zegara" << endl;
			cin >> obrot;
			switch (obrot) {
			case 'z': obrotsz(tab);
				break;
			case 'x': obrotsx(tab);
				break;
			default: cout << "Wprowadzono zly sposob obrotu planszy. Wprowadz ponownie: " << endl;
				sprawdzenie = 1;
				break;
			}
			break;
		default: cout << "Wprowadzono niewlasciwa plansze. Wprowadz dane ponownie" << endl;
			sprawdzenie = 1;
			break;
		}
	} while (sprawdzenie == 1);
}
bool wygrana(char tab[][Y], gracz &gracz) {
	bool warunek;
	warunek = false;
	int licz = 0;
	int licz1 = 0;
	int licz2 = 0;
	int licz3 = 0;
	int licz4 = 0;
	int licz5 = 0;
	int licz6 = 0;
	int licz7 = 0;
	for (int i = 0; i < X; i++) //warunek dla wierszy
		warunek |= ((tab[i][0] == gracz.zeton) && (tab[i][1] == gracz.zeton) && (tab[i][2] == gracz.zeton) && (tab[i][3] == gracz.zeton) && (tab[i][4] == gracz.zeton) || (tab[i][1] == gracz.zeton) && (tab[i][2] == gracz.zeton) && (tab[i][3] == gracz.zeton) && (tab[i][4] == gracz.zeton) && (tab[i][5] == gracz.zeton));
	for (int i = 0; i < Y; i++) { //warunek dla kolumn
		warunek |= ((tab[0][i] == gracz.zeton) && (tab[1][i] == gracz.zeton) && (tab[2][i] == gracz.zeton) && (tab[3][i] == gracz.zeton) && (tab[4][i] == gracz.zeton) || (tab[1][i] == gracz.zeton) && (tab[2][i] == gracz.zeton) && (tab[3][i] == gracz.zeton) && (tab[4][i] == gracz.zeton) && (tab[5][i] == gracz.zeton));
	}
	for (int i = 0; i < X - 1; i++) 
		for (int j = 0; j < Y - 1; j++) 
			if (i==j && tab[i][j] == gracz.zeton) 
				licz++;
	for (int i = 1; i < X; i++)
		for (int j = 1; j < Y; j++)
			if (i == j && tab[i][j] == gracz.zeton) 
				licz1++;
	for (int i = 0; i < X-1; i++)
		for (int j = 1; j < Y; j++)
			if (i+1==j && tab[i][j] == gracz.zeton) 
				licz2++;
	for (int i = 1; i < X; i++)
		for (int j = 0; j < Y-1; j++)                   //warunki dla skosow (pierwsze 4 od lewa gora do dol prawo, drugie 4 od prawo gora do dol lewo)
			if (i==j+1 && tab[i][j] == gracz.zeton) 
				licz3++;
	for (int i = 0; i < X-1; i++)
		for (int j= Y-1; j > 0; j--)
			if (i + j == 5 && tab[i][j] == gracz.zeton) 
				licz4++;
	for (int i = 1; i < X; i++)
		for (int j = Y - 2; j >= 0; j--)
			if (i+j==5 && tab[i][j] == gracz.zeton) 
				licz5++;
	for (int i = 0; i < X - 1; i++)
		for (int j = Y - 2; j >= 0; j--)
			if (i + j == 4 && tab[i][j] == gracz.zeton) 
				licz6++;
	for (int i = 1; i < X; i++)
		for (int j = Y - 1; j > 0; j--)
			if (i + j == 6 && tab[i][j] == gracz.zeton) 
				licz7++;
	warunek |= (licz == 5 || licz1 == 5 || licz2 == 5 || licz3 == 5 || licz4 == 5 || licz5 == 5 || licz6 == 5 || licz7 == 5);
	if (warunek)
		return true;
	else
	    return false;
}
bool remis2(char tab[][Y], gracz gracz1, gracz gracz2) {
	bool warunek;
	warunek = false;
	warunek |= (wygrana(tab, gracz1) && wygrana(tab, gracz2));
	if (warunek)
		return true;
	else return false;
}
bool remis1(char tab[][Y]) {
	int licznik=0;
	bool warunek;
	warunek = false;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++)
			if (tab[i][j] != ' ')        //remis jesli 36 pol jest zajetych 
				licznik++;
	}
	warunek |= (licznik == 36);
	if (warunek)
		return true;
	else return false;
}
void zamiana(char tab[][Y],rozgrywka tab1[],gracz &gracz1, gracz &gracz2) {
	char buf;
	buf = gracz1.zeton;          //zamiana zetonow przypisanych do graczy
	gracz1.zeton = gracz2.zeton; 
	gracz2.zeton = buf;
	for (int i = 0; i < X; i++) {  //zamiana zetonow w glownej planszy
		for (int j = 0; j < Y; j++) {
			if (tab[i][j] == 'x')
				tab[i][j] = 'o';
			else if (tab[i][j] == 'o')
				tab[i][j] = 'x';
		}
	}
	for (int i = 0; i < Z; i++) {      //zamiana zetonow w planszy do undo i przegladania
		for (int j = 0; j < X; j++) {
			for (int k = 0; k < Y; k++) {
				if (tab1[i].tab[j][k] == 'x')
					tab1[i].tab[j][k] = 'o';              
				else if (tab1[i].tab[j][k] == 'o')
					tab1[i].tab[j][k] = 'x';
			}
		}
	}
	cout << "Zetony zostaly zamienione!" << endl << endl;
}
void nowa_plansza(char tab[][Y]) {
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++) 
			tab[i][j] = ' ';
}
void gorna_linia() {
	cout << char(201);  
	for (int k = 1; k < linie; k++)
		if (k != linie / 2) cout << char(205); //wylaczenie srodka
		else cout << char(203);   
	cout << char(187); 
}
void linie_poziome(int& i) {
	if (i > 0 && i != 3) {
		cout << char(186);
		for (int k = 1; k < linie; k++)
			if (k != linie / 2) cout << char(196); //poziome linie miedzy okienkami
			else cout << char(186); //srodkowa pozioma linia
		cout << char(186); 
	}
	else if (i > 0) {
		cout << char(204); 
		for (int k = 1; k < linie; k++)
			if (k != linie / 2) cout << char(205); //srodkowy wiersz
			else cout << char(206); //srodek planszy
		cout << char(185); 
	}
}
void dolna_linia() {
	cout << char(200); 
	for (int k = 1; k < linie; k++)
		if (k != linie / 2) cout << char(205); //dolna linia bez srodka
		else cout << char(202); //srodek dolnej linii
	cout << char(188); 
	cout << endl;
}
void plansza(char tab[][Y], gracz gracz1, gracz gracz2) {
	cout << setw(przesuniecie + 13) << "Gracz 1: " << gracz1.imie << ' ' << '|' << ' ' << gracz1.zeton << endl;
	cout << endl;
	cout << setw(przesuniecie+6) << 'q' << setw(przesuniecie+2) << 'w' << endl;
	cout << setw(przesuniecie);
	gorna_linia();
	int licznik = 0;
	for (int i = 0; i < X; i++) {
		cout << setw(przesuniecie);
		linie_poziome(i);
		cout << setw(przesuniecie);
		cout << endl;
		cout << char(186); 
		for (int j = 0; j < Y; j++) {
			if (j > 0 && j != 3) cout << char(179); //pionowe linie miedzy okienkami
			else if (j > 0) cout << char(186); //srodkowa pionowa linia
			cout << ' ' << tab[i][j] << ' '; 
		}
		cout << char(186); 
		cout << endl;
	}
	cout << setw(przesuniecie);
	dolna_linia();
	cout << setw(przesuniecie+6) << 'a' << setw(przesuniecie+2) << 's' << endl << endl;
	cout << setw(przesuniecie + 13) << "Gracz 2: " << gracz2.imie << ' ' << '|' << ' ' << gracz2.zeton << endl << endl;
}
void przegladanie(char tab[][Y], gracz gracz1, gracz gracz2, rozgrywka tab1[], int& licznik) {
	int ruch;
	int sprawdzenie = 0;;
	cout << "Rozgrywka miala " << licznik << " ruchow." << endl;
	do {
		cout << "Wybierz ktory ruch rozgrywki chcesz zobaczyc: " << endl;
		cin >> ruch;
		switch (ruch) {
		case 0: sprawdzenie = 1;
			break;
		default:
			if (ruch > 0 && ruch <= licznik) { //sprawdzenie czy ruch nie wykracza poza zakres
				cout << "Ruch numer " << ruch << endl;
				plansza(tab1[ruch-1].tab, gracz1, gracz2);
				cout << endl;
				cout << tab1[ruch-1].ruch << endl;
				cout << "Podaj nastepny ruch lub wybierz 0 aby zakonczyc przegladanie. ";
			}
			else cout << "Nie ma takiego ruchu. Podaj inny ruch: ";
		}
	} while (sprawdzenie == 0);
}
void opis_programu() {
	cout << "Program pozwala wybrac pomiedzy gra w Kolko i krzyzyk a gra w Pentago." << endl;
	cout << "Pentago jest gra dwuosobowa na planszy. Plansza sklada sie z 4 ruchomych czesci, ktore mozna obracac. Kazda czesc zawiera 9 miejsc na zetony." << endl;
	cout << "Gracze po kolei oddaja ruch skladajacy się z 2 czesci: " << endl;
	cout << "- dolozenia swojego zetonu na niezajete pole planszy" << endl;
	cout << "- obrot jednej z czesci planszy o 90 stopni w dowolnym kierunkuku" << endl;
	cout << "Nie mozna zrezygnowac z zadnej czesci ruchu" << endl;
	cout << "Wygrywa osoba, ktorej 5 zetonow, po pelnym ruchu, sa ulozone w rzedzie / kolumnie / po skosach" << endl << endl;
}
void menu1(char tab[][Y],rozgrywka tab1[], gracz &gracz1, gracz &gracz2,int &licznik) {
	char opcja;
	do{
		cout << "Opcje: " << endl;
		cout << "p - pauza " << endl;
		cout << "u - undo" << endl;
		cout << "h - opis programu" << endl;
		cout << "f - zmiana zetonu" << endl;
		cout << "t - wykonaj ruch" << endl;
		cin >> opcja;
		cout << endl;
		switch (opcja) {
		case 'u': undo(tab, tab1, gracz1, gracz2, licznik);
			break;
		case 'p': pauza();
			break;
		case 'f': zamiana(tab, tab1,gracz1, gracz2);
			break;
		case 'h': opis_programu();
			break;
		case 't': plansza(tab, gracz1, gracz2);
			postaw_pionek(tab, gracz1);
		default: cout << "Wybrano bledna opcje. Wybierz ponownie:" << endl;
			break;
		}
	} while (opcja != 't');
}
void menu2(char tab[][Y], rozgrywka tab1[], gracz &gracz1, gracz &gracz2, int& licznik) {
	char opcja;
	do {
		cout << "Opcje: " << endl;
		cout << "p - pauza " << endl;
		cout << "u - undo" << endl;
		cout << "h - opis programu" << endl;
		cout << "f - zmiana zetonu" << endl;
		cout << "t - wykonaj ruch" << endl;
		cin >> opcja;
		cout << endl;
		switch (opcja) {
		case 'u': undo(tab, tab1, gracz1, gracz2, licznik);
			break;
		case 'f': zamiana(tab, tab1,gracz1, gracz2);
			break;
		case 'h': opis_programu();
			break;
		case 't': plansza(tab, gracz1, gracz2);
			postaw_pionek(tab, gracz2);
		default: cout << "Wybrano bledna opcje. Wybierz ponownie:" << endl;
			break;
		}
	} while (opcja != 't');
}
void gracze(gracz& gracz1, gracz& gracz2) {
	char zetony[ZET] = { 'x','o', '@','+','*','#','?','$' };
	cout << "Podaj imie gracza 1: ";
	cin >> gracz1.imie;
	cout << "Podaj imie gracza 2: ";
	cin >> gracz2.imie;
	cout << "Wybierz zeton dla gracza 1: " << endl;
	cout << "Dostepne zetony: x, o" << endl;
	int pop = 0;
	while (pop == 0) {
		pop = 0;
		cin >> gracz1.zeton;
		if (gracz1.zeton == 'x' || gracz1.zeton == 'o')
			pop = 1;
		else cout << "Wprowadzono niewlasciwe dane. Wprowadz ponownie: " << endl;
	}
	cout << "Wybierz zeton dla gracza 2: " << endl;
	cout << "Dostepne zetony: x, o" << endl;
	pop = 0;
	while (pop == 0) {
		pop = 0;
		cin >> gracz2.zeton;
		if (gracz2.zeton == gracz1.zeton)
			cout << "Zeton wybrany przez innego gracza. Wprowadz inny zeton: " << endl;
		else if (gracz2.zeton == 'x' || gracz2.zeton == 'o')
			pop = 1;
		else cout << "Wprowadzono niewlasciwe dane. Wprowadz ponownie: " << endl;
	}
}
void tura1(char tab[][Y], rozgrywka tab1[], gracz &gracz1, gracz &gracz2, int& licznik) {
	char akcja;
	int sprawdzenie;
	cout << "RUCH GRACZA 1" << endl;
	do {
		sprawdzenie = 0;
		cout << "m - wejscie do menu" << endl;
		cout << "t - wykonaj ruch" << endl;
		cin >> akcja;
		switch (akcja) {
		case 'm': menu1(tab, tab1,gracz1, gracz2,licznik);
			break;
		case 't': postaw_pionek(tab, gracz1);
			break;
		default: cout << "Wybrano bledna opcje. Wybierz ponownie:" << endl;
			sprawdzenie = 1;
			break;
		}
	} while (sprawdzenie == 1);
}
void tura2(char tab[][Y], rozgrywka tab1[], gracz &gracz1, gracz &gracz2, int& licznik) {
	char akcja;
	int sprawdzenie;
	cout << "RUCH GRACZA 2" << endl;
	do {
		sprawdzenie = 0;
		cout << "m - wejscie do menu" << endl;
		cout << "t - wykonaj ruch" << endl;
		cin >> akcja;
		switch (akcja) {
		case 'm': menu2(tab, tab1, gracz1, gracz2, licznik);
			break;
		case 't': postaw_pionek(tab, gracz2);
			break;
		default: cout << "Wybrano bledna opcje. Wybierz ponownie:" << endl;
			sprawdzenie = 1;
			break;
		}
	} while (sprawdzenie == 1);
}
void kolko_krzyzyk(char tab[][Y],rozgrywka tab1[], gracz &gracz1, gracz &gracz2,int &licznik) {
	cout << "Witaj w grze kolko i krzyzyk :)" << endl;
	plansza(tab, gracz1, gracz2);
	cout << "Rozgrywke zaczyna gracz 1: " << endl;
	while ((wygrana(tab, gracz1) == false) && (wygrana(tab, gracz2) == false) && (remis1(tab) == false)) {
		cout << "Tura gracza 1: " << endl;
		tura1(tab, tab1, gracz1, gracz2, licznik);
		zapis1(tab, tab1, licznik);
		plansza(tab, gracz1, gracz2);
		wygrana(tab, gracz1);
		wygrana(tab, gracz2);
		remis1(tab);
		if (wygrana(tab, gracz1) || remis1(tab))
			break;
		cout << endl;
		cout << "Tura gracza 2: " << endl;
		tura2(tab, tab1, gracz1, gracz2, licznik);
		zapis2(tab, tab1, licznik);
		plansza(tab, gracz1, gracz2);
		wygrana(tab, gracz1);
		wygrana(tab, gracz2);
		remis1(tab);
		if (wygrana(tab, gracz1) || remis1(tab))
			break;
		cout << endl;
	}
	if (wygrana(tab, gracz1)) {
		cout << "Wygrywa gracz 1! Gratulacje!" << endl;
	}
	else if (remis1(tab)) {
		cout << "Remis!" << endl;
	}
	else if (wygrana(tab, gracz2)) {
		cout << "Wygrywa gracz 2! Gratulacje!" << endl;
	}
}
void pentago(char tab[][Y], gracz &gracz1, gracz &gracz2,rozgrywka tab1[],int &licznik) {
	cout << endl;
	cout << "Witaj w grze pentago :)" << endl << endl;
	plansza(tab, gracz1, gracz2);
	cout << "Rozgrywke zaczyna gracz 1: " << endl;
	while ((wygrana(tab, gracz1) == false) && (wygrana(tab, gracz2) == false) && (remis1(tab) == false)&&(remis2(tab,gracz1,gracz2)==false)) {
		tura1(tab, tab1,gracz1, gracz2,licznik);
		obrot(tab);
		zapis1(tab, tab1, licznik);
		plansza(tab, gracz1, gracz2);
		remis1(tab);
		remis2(tab, gracz1, gracz2);
		wygrana(tab, gracz1);
		wygrana(tab, gracz2);
		if (wygrana(tab, gracz1) || wygrana(tab,gracz2)||remis1(tab) || remis2(tab, gracz1, gracz2))
			break;
		cout << endl;
		tura2(tab,tab1, gracz1, gracz2,licznik);
		obrot(tab);
		zapis2(tab, tab1, licznik);
		plansza(tab, gracz1, gracz2);
		remis1(tab);
		remis2(tab, gracz1, gracz2);
		wygrana(tab, gracz1);
		wygrana(tab, gracz2);
		if (wygrana(tab, gracz1) || wygrana(tab, gracz2) || remis1(tab) || remis2(tab, gracz1, gracz2))
				break;
		cout << endl;
	}
	if (remis1(tab)) {
		cout << "Remis!" << endl;
	}
	else if (remis2(tab, gracz1, gracz2)) {
		cout << "Remis!" << endl;
	}
	else if (wygrana(tab, gracz1)) {
		cout << "Wygrywa gracz 1! Gratulacje!" << endl;
	}
	else if (wygrana(tab, gracz2)) {
		cout << "Wygrywa gracz 2! Gratulacje!" << endl;
	}
}
int main() {
	gracz gracz1;
	gracz gracz2;
	rozgrywka tab1[Z];
	char tab[X][Y];
	char opcja1;
	char opcja2;
	int sprawdzenie;
	int licznik = 0;
	gracze(gracz1, gracz2);
	cout << endl;
	do {
		sprawdzenie = 0;
		cout << "Wybierz: " << endl;
		cout << "p - Gra w pentago" << endl;
		cout << "k - Gra w kolko i krzyzyk" << endl;
		cout << "o - Wczytanie predefiniowanej planszy dla pentago" << endl;
		cout << "O - Wczytanie predefiniowanej planszy dla kolko i krzyzyk" << endl;
		cin >> opcja1;
		switch (opcja1) {
		case 'p':
			nowa_plansza(tab);
			pentago(tab, gracz1, gracz2,tab1,licznik);
			break;
		case 'k':
			nowa_plansza(tab);
			kolko_krzyzyk(tab, tab1,gracz1, gracz2,licznik);
			break;
		case 'o':
			nowa_plansza(tab);
			predefiniowana(tab, gracz1, gracz2);
			pentago(tab, gracz1, gracz2,tab1,licznik);
			break;
		case 'O':
			nowa_plansza(tab);
			predefiniowana(tab, gracz1, gracz2);
			kolko_krzyzyk(tab, tab1,gracz1, gracz2,licznik);
			break;
		default:
			cout << "Wybrano bledna opcje. Wybierz ponownie:" << endl;
			sprawdzenie = 1;
			break;
		}
	} while (sprawdzenie == 1);
	do {
		cout << "Koniec gry. Wybierz: " << endl;
		cout << "p - Przegladanie rozgrywki" << endl;
		cout << "e - wyjscie z programu" << endl;
		cin >> opcja2;
		switch (opcja2) {
		case 'p': przegladanie(tab, gracz1, gracz2, tab1, licznik);
			break;
		case 'e':;
		}
	} while (opcja2 != 'e');
}
