#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>

using namespace std;

void menu();
bool nuskaitymas(int& n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]);
bool saugojimas(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]);
double kategorijosSuma(int n, string kategorija[], double kaina[], int kiekis[], string parinktis);
double nuolaidos(double kaina, int kiekis);
double galutineSuma(double sumaBeNuolaidos, double nuolaida);
double sumaBeNuolaidos(double kaina, int kiekis);
void kategorijosIsvestis(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[], string pasirinktaKategorija);

int main() {


    bool arVeikia = true;
    int n, kiekis[100], pasirinkimas;
    string kategorija[100], pavadinimas[100];
    double kaina[100];

    if(!nuskaitymas(n, kategorija, pavadinimas, kaina, kiekis)) {
        return 1;
    }
    while(arVeikia) {
        menu();
        cin >> pasirinkimas;
        switch(pasirinkimas) {
            case 1:{
                cout << "Visos prekes:" << endl;
                for(int i = 0; i < n; i++){
                    cout << left << setw(15) << kategorija[i]
                        << setw(50) << pavadinimas[i]
                        << right << fixed << setprecision(2)
                        << setw(15) << kaina[i]
                        << setw(10) << kiekis[i] << endl;
                }
                break;
            }
            case 2:{
                int x;
                cout << "Pasirinkite kategorija: " << endl;
                cout << "1. Dviraciai" << endl;
                cout << "2. Dalys" << endl;
                cout << "3. Aksesuarai" << endl;
                cin >> x;
                switch (x) {
                    case 1: {
                        kategorijosIsvestis(n, kategorija, pavadinimas, kaina, kiekis, "Dviraciai");
                        break;
                    }
                    case 2: {
                        kategorijosIsvestis(n, kategorija, pavadinimas, kaina, kiekis, "Dalys");
                        break;
                    }
                    case 3: {
                        kategorijosIsvestis(n, kategorija, pavadinimas, kaina, kiekis, "Aksesuarai");
                        break;
                    }
                    default: {
                        cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
                        break;
                    }
                }
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                if(!saugojimas(n, kategorija, pavadinimas, kaina, kiekis)){
                    return 1;
                }
                break;
            }
            case 7: {
                cout << "Programa baigiama." << endl;
                arVeikia = false;
                break;
            }
            default:
                cout << "Tokio pasirinkimo nera." << endl;
        }
    }
    return 0;
}

void menu() {
    cout << "Prasome pasirinkti:" << endl;
    cout << "1. Perziureti visas uzsakymo prekes." << endl;
    cout << "2. Perziureti pasirinktos kategorijos prekes." << endl;
    cout << "3. Perziureti viso uzsakymo sumas." << endl;
    cout << "4. Perziureti sumas pagal kategorijas." << endl;
    cout << "5. Parodyti visa uzsakymo ataskaita." << endl;
    cout << "6. Issaugoti visa ataskaita i faila." << endl;
    cout << "7. Iseiti." << endl;
}

bool nuskaitymas(int& n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]){
    ifstream fin("uzsakymas.txt");
    if(!fin.is_open()) {
        cout << "Nepavyko atidaryti duomenu failo." << endl;
        return false;
    }

    if(n > 100) {
        cout << "Per daug irasu, maksimaliai galima ivesti 100." << endl;
        fin.close();
        return false;
    }

    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> ws;
        getline(fin, kategorija[i], ';');
        getline(fin, pavadinimas[i], ';');
        fin >> kaina[i];
        fin.ignore(1);
        fin >> kiekis[i];
    }
    fin.close();
    return true;
}

bool saugojimas(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]){
    ofstream fout("ataskaita.txt");
    if(!fout.is_open()) {
        cout << "Nepavyko atidaryti rezultatu failo." << endl;
        return false;
    }
    fout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Vieneto kaina" << setw(10) << "Kiekis" << setw(15) << "Suma" << setw(15) << "Nuolaida" << setw(15) << "Galutine suma" << endl;
    for(int i = 0; i < n; i++){
        fout << left << setw(15) << kategorija[i]
            << setw(50) << pavadinimas[i]
            << right << fixed << setprecision(2)
            << setw(15) << kaina[i]
            << setw(10) << kiekis[i]
            << setw(15) << sumaBeNuolaidos(kaina[i], kiekis[i])
            << setw(15) << nuolaidos(kaina[i], kiekis[i])
            << setw(15) << galutineSuma(sumaBeNuolaidos(kaina[i], kiekis[i]), nuolaidos(kaina[i], kiekis[i])) << endl;
    }
    fout.close();
    return true;
}

double kategorijosSuma(int n, string kategorija[], double kaina[], int kiekis[], string parinktis) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        if(kategorija[i] == parinktis) {
            sum += (kaina[i] * kiekis[i]);
        }
    }
    return sum;
}

double nuolaidos(double kaina, int kiekis) {
    double nuolaida = 0;
    if(kiekis >= 10) {
        nuolaida = kiekis * kaina * 0.1;
    }
    return nuolaida;
}

double sumaBeNuolaidos(double kaina, int kiekis) {
    double sum = kaina * kiekis;
    return sum;
}

double galutineSuma(double sumaBeNuolaidos, double nuolaida) {
    double sum = sumaBeNuolaidos - nuolaida;
    return sum;
}

void kategorijosIsvestis(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[], string pasirinktaKategorija) {
    cout << "Pasirinktos kategorijos prekes:" << endl;
    for(int i = 0; i < n; i++) {
        if(kategorija[i] == pasirinktaKategorija){
            cout << left << setw(15) << kategorija[i]
                << setw(50) << pavadinimas[i]
                << right << fixed << setprecision(2)
                << setw(15) << kaina[i]
                << setw(10) << kiekis[i] << endl;
        }
    }
}
