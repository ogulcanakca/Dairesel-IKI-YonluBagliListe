#include <iostream>
#include <iomanip>
using namespace std;


class Dugum {
public:
	Dugum(int veri)
	{
		this->veri = veri;
		onceki = sonraki = 0;
	}
	int veri;
	Dugum* onceki;
	Dugum* sonraki;
};
class DaireselListe {
public:
	DaireselListe()
	{
		ilk = 0;
		dugumSayisi = 0;
	}
	~DaireselListe() {

	}
	void ekle(int veri) {
		Dugum* yeni = new Dugum(veri);

		if (ilk == 0) {
			ilk = yeni;
			ilk->onceki = ilk;
			ilk->sonraki = ilk;
		}
		else {
			Dugum* gec = ilk;
			while (gec->sonraki != ilk) {
				gec = gec->sonraki;
			}
			gec->sonraki = yeni;
			yeni->onceki = gec;
			yeni->sonraki = ilk;
			ilk->onceki = yeni;

		}
		dugumSayisi++;
	}
	void cikar(int sira) {
		Dugum* gec = dugumGetir(sira);
		if (gec) {
			Dugum* oncekiDugum = gec->onceki;
			Dugum* sonrakiDugum = gec->sonraki;

			oncekiDugum->sonraki = sonrakiDugum;
			sonrakiDugum->onceki = oncekiDugum;
			if (ilk->onceki == ilk) {
				ilk = 0;
			}
			if (gec == ilk) {
				ilk = sonrakiDugum;
			}
			

			delete gec;
			 

			dugumSayisi--;
		}
	}
	void cikar() {
		if (ilk == 0) {
			return;

		}
		if (ilk->sonraki == ilk) {
			delete ilk;
			ilk = 0;
		}
		else
		{
			Dugum* gec = dugumGetir(dugumSayisi - 2);

			delete gec->sonraki;

			gec->sonraki = ilk;
			ilk->onceki = gec;
			
		}
		dugumSayisi--;
	}
	friend ostream& operator<<(ostream& os, DaireselListe& liste) {
		os << setw(15) << "dugum adresi" << setw(15) << "veri" << setw(15) << "onceki" << setw(15) << "sonraki" << endl;

		Dugum* gec = liste.ilk;
		for (int i = 0; i < liste.dugumSayisi; i++) {
			os << setw(15) << gec << setw(15) << gec->veri << setw(15) << gec->onceki << setw(15) << gec->sonraki << endl;

			gec = gec->sonraki;
		}
		os << "--------------------------------------" << endl;
		return os;
	}
	Dugum* dugumGetir(int sira) {
		if (sira < 0 || sira >= dugumSayisi) {
			return 0;

		}

		Dugum* gec = ilk;
		for (int i = 0; i < sira; i++) {
			gec = gec->sonraki;

		}
		return gec;
	}
	void onuneEkle(int sira, int veri) {
		Dugum* gec = dugumGetir(sira);
		
		if (gec) {
			
			Dugum* oncekiDugum = gec->onceki;
			Dugum* yeniDugum = new Dugum(veri);
			if (gec == ilk) {
				ilk = yeniDugum;
				
			}
			oncekiDugum->sonraki = yeniDugum;
			yeniDugum->onceki = oncekiDugum;
			yeniDugum->sonraki = gec;
			gec->onceki = yeniDugum;
			dugumSayisi++;
		}
	}
private:
	Dugum* ilk;
	int dugumSayisi;
};

int main()
{
	DaireselListe liste;

	for (int i = 0; i < 5; i++) {
		liste.ekle((i + 1) * 11);
	}
	cout << liste;
	for (int i = 0; i < 5; i++) {
		liste.cikar(0);
		cout << liste;
	}
	liste.ekle(77);
	cout << liste;

	liste.onuneEkle(0, 88);
	cout << liste;
}