#include <iostream>
#include <iomanip>
#include <fstream>
#include <ostream>
#include <sstream>

using namespace std;

void menu();
bool nuskaitymas(int& n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]);
bool saugojimas(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]);
void isvestisIEkrana(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]);
double kategorijosSuma(int n, string kategorija[], double kaina[], int kiekis[], string parinktis);
double nuolaidos(double kaina, int kiekis);
double galutineSuma(double sumaBeNuolaidos, double nuolaida);
double sumaBeNuolaidos(double kaina, int kiekis);
void kategorijosIsvestis(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[], string pasirinktaKategorija);
void kategorijosSumosIsvestis(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[], string pasirinktaKategorija);

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
            case 1: {
                cout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Vieneto kaina" << setw(10) << "Kiekis" << endl;
                cout << string(117, '-') << endl;
                for(int i = 0; i < n; i++){
                    cout << left << setw(15) << kategorija[i]
                        << setw(50) << pavadinimas[i]
                        << right << fixed << setprecision(2)
                        << setw(15) << kaina[i]
                        << setw(15) << kiekis[i] << endl;
                }
                cout << string(117, '-') << endl;
                break;
            }
            case 2: {
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
                cout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Suma" << endl;
                cout << string(117, '-') << endl;
                for(int i = 0; i < n; i++){
                    cout << left << setw(15) << kategorija[i]
                        << setw(50) << pavadinimas[i]
                        << right << fixed << setprecision(2)
                        << setw(15) << sumaBeNuolaidos(kaina[i], kiekis[i]) << endl;
                }
                cout << string(117, '-') << endl;
                break;
            }
            case 4: {
                int x;
                cout << "Pasirinkite kategorija: " << endl;
                cout << "1. Dviraciai" << endl;
                cout << "2. Dalys" << endl;
                cout << "3. Aksesuarai" << endl;
                cin >> x;
                switch (x) {
                    case 1: {
                        kategorijosSumosIsvestis(n, kategorija, pavadinimas, kaina, kiekis, "Dviraciai");
                        break;
                    }
                    case 2: {
                        kategorijosSumosIsvestis(n, kategorija, pavadinimas, kaina, kiekis, "Dalys");
                        break;
                    }
                    case 3: {
                        kategorijosSumosIsvestis(n, kategorija, pavadinimas, kaina, kiekis, "Aksesuarai");
                        break;
                    }
                    default: {
                        cout << "Tokio pasirinkimo nera, bandykite dar karta." << endl;
                        break;
                    }
                }
                break;
            }
            case 5: {
                isvestisIEkrana(n, kategorija, pavadinimas, kaina, kiekis);
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

    if(!(fin >> n)) {
        cout << "Nepavyko nuskaityti irasu skaiciaus." << endl;
        fin.close();
        return false;
    }

    if(n <= 0 ||n > 100) {
        cout << "Irasu skaicius neatitinka ribu. Turi buti 1-100" << endl;
        fin.close();
        return false;
    }
    string input;
    getline(fin, input);
    for(int i = 0; i < n; i++) {
        if(!getline(fin, input)) {
            cout << "Truksta duomenu, nuskaityta " << i << " is " << n << " irasu." << endl;
            fin.close();
            return false;
        }

        if(input.empty()) {
            i--;
            continue;
        }

        stringstream ss(input);
        string kainaString, kiekisString;

        if(!getline(ss, kategorija[i], ';') ||!getline(ss, pavadinimas[i], ';') || !getline(ss, kainaString, ';') || !getline(ss, kiekisString)) {
            cout << i + 1 << " irase truksta duomenu." << endl;
            fin.close();
            return false;
        }

        if(kategorija[i] != "Dviraciai" && kategorija[i] != "Dalys" && kategorija[i] != "Aksesuarai") {
            cout << i + 1 << " irase neteisingas kategorijos pavadinimas." << endl;
            fin.close();
            return false;
        }

        if(pavadinimas[i].empty()) {
            cout << i + 1 << " irase nera pavadinimo." << endl;
            fin.close();
            return false;
        }

        stringstream ssKaina(kainaString);
        char likutis;
        if(!(ssKaina >> kaina[i]) || (ssKaina >> likutis) || kaina[i] <= 0) {
            cout << i + 1 << " irase netinkamas kainos formatas. Iveskite teigiama skaiciu." << endl;
            fin.close();
            return false;
        }

        stringstream ssKiekis(kiekisString);
        if(!(ssKiekis >> kiekis[i]) || (ssKiekis >> likutis) || kiekis[i] <= 0) {
            cout << i + 1 << " irase netinkamas kiekio formatas. Iveskite teigima sveika skaiciu." << endl;
            fin.close();
            return false;
        }
    }
    string extra;
    while(getline(fin, extra)) {
        if(!extra.empty()) {
            cout << "Faile yra daugiau duomenu nei nurodyta." << endl;
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

bool saugojimas(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]){
    double bendraSumaBeNuolaidos = 0, nuolaiduSuma = 0, finalSuma = 0;
    ofstream fout("ataskaita.txt");
    if(!fout.is_open()) {
        cout << "Nepavyko atidaryti rezultatu failo." << endl;
        return false;
    }
    fout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Vieneto kaina" << setw(10) << "Kiekis" << setw(15) << "Suma" << setw(15) << "Nuolaida" << setw(15) << "Galutine suma" << endl;
    fout << string(140, '-') << endl;
    for(int i = 0; i < n; i++){
        fout << left << setw(15) << kategorija[i]
            << setw(50) << pavadinimas[i]
            << right << fixed << setprecision(2)
            << setw(15) << kaina[i]
            << setw(10) << kiekis[i]
            << setw(15) << sumaBeNuolaidos(kaina[i], kiekis[i])
            << setw(15) << nuolaidos(kaina[i], kiekis[i])
            << setw(15) << galutineSuma(sumaBeNuolaidos(kaina[i], kiekis[i]), nuolaidos(kaina[i], kiekis[i])) << endl;
        bendraSumaBeNuolaidos += (kaina[i] * kiekis[i]);
        if(nuolaidos(kaina[i], kiekis[i]) > 0){
                nuolaiduSuma += nuolaidos(kaina[i], kiekis[i]);
        }
        finalSuma += galutineSuma(sumaBeNuolaidos(kaina[i], kiekis[i]), nuolaidos(kaina[i], kiekis[i]));
    }
    fout << string(140, '-') << endl;
    fout << left<< setw(30) << "Dviraciu suma po nuolaidu: " << right << setw(10) << kategorijosSuma(n, kategorija, kaina, kiekis, "Dviraciai") << right << setw(85) << "Bendra suma be nuolaidu: " << setw(10) << fixed << setprecision(2) << bendraSumaBeNuolaidos << endl;
    fout << left<< setw(30) << "Daliu suma po nuolaidu: " << right << setw(10) <<kategorijosSuma(n, kategorija, kaina, kiekis, "Dalys") << right << setw(85) << "Nuolaidu suma: " << setw(10) << fixed << setprecision(2) << nuolaiduSuma << endl;
    fout << left<< setw(30) << "Aksesuaru suma po nuolaidu: " << right << setw(10) << kategorijosSuma(n, kategorija, kaina, kiekis, "Aksesuarai") << right << setw(85) << "Galutine moketina suma po nuolaidu: " << setw(10) << fixed << setprecision(2) << finalSuma << endl;
    fout.close();
    return true;
}

double kategorijosSuma(int n, string kategorija[], double kaina[], int kiekis[], string parinktis) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        if(kategorija[i] == parinktis) {
            sum += (kaina[i] * kiekis[i] - nuolaidos(kaina[i], kiekis[i]));
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
    int count = 0;
    cout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Vieneto kaina" << setw(10) << "Kiekis" << endl;
    cout << string(117, '-') << endl;
    for(int i = 0; i < n; i++) {
        if(kategorija[i] == pasirinktaKategorija){
            cout << left << setw(15) << kategorija[i]
                << setw(50) << pavadinimas[i]
                << right << fixed << setprecision(2)
                << setw(15) << kaina[i]
                << setw(10) << kiekis[i] << endl;
            count++;
        }
    }
    if(count == 0){
        cout << "Prekiu sioje kategorijoje nera." << endl;
    }
    cout << string(117, '-') << endl;
}

void kategorijosSumosIsvestis(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[], string pasirinktaKategorija) {
    int count = 0;
    cout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Suma" << endl;
    cout << string(117, '-') << endl;
    for(int i = 0; i < n; i++) {
        if(kategorija[i] == pasirinktaKategorija){
            cout << left << setw(15) << kategorija[i]
                << setw(50) << pavadinimas[i]
                << right << fixed << setprecision(2)
                << setw(15) << sumaBeNuolaidos(kaina[i], kiekis[i]) << endl;
            count++;
        }
    }
    if(count == 0){
        cout << "Prekiu sioje kategorijoje nera." << endl;
    }
    cout << string(117, '-') << endl;
}

void isvestisIEkrana(int n, string kategorija[], string pavadinimas[], double kaina[], int kiekis[]) {
    double bendraSumaBeNuolaidos = 0, nuolaiduSuma = 0, finalSuma = 0;
    cout << left << setw(15) << "Kategorija" << setw(50) << "Pavadinimas" << right << setw(15) << "Vieneto kaina" << setw(10) << "Kiekis" << setw(15) << "Suma" << setw(15) << "Nuolaida" << setw(15) << "Galutine suma" << endl;
    cout << string(140, '-') << endl;
    for(int i = 0; i < n; i++){
        cout << left << setw(15) << kategorija[i]
            << setw(50) << pavadinimas[i]
            << right << fixed << setprecision(2)
            << setw(15) << kaina[i]
            << setw(10) << kiekis[i]
            << setw(15) << sumaBeNuolaidos(kaina[i], kiekis[i])
            << setw(15) << nuolaidos(kaina[i], kiekis[i])
            << setw(15) << galutineSuma(sumaBeNuolaidos(kaina[i], kiekis[i]), nuolaidos(kaina[i], kiekis[i])) << endl;
        bendraSumaBeNuolaidos += (kaina[i] * kiekis[i]);
        if(nuolaidos(kaina[i], kiekis[i]) > 0){
                nuolaiduSuma += nuolaidos(kaina[i], kiekis[i]);
        }
        finalSuma += galutineSuma(sumaBeNuolaidos(kaina[i], kiekis[i]), nuolaidos(kaina[i], kiekis[i]));
    }
    cout << string(140, '-') << endl;
    cout << left<< setw(30) << "Dviraciu suma po nuolaidu: " << right << setw(10) << kategorijosSuma(n, kategorija, kaina, kiekis, "Dviraciai") << right << setw(85) << "Bendra suma be nuolaidu: " << setw(10) << fixed << setprecision(2) << bendraSumaBeNuolaidos << endl;
    cout << left<< setw(30) << "Daliu suma po nuolaidu: " << right << setw(10) <<kategorijosSuma(n, kategorija, kaina, kiekis, "Dalys") << right << setw(85) << "Nuolaidu suma: " << setw(10) << fixed << setprecision(2) << nuolaiduSuma << endl;
    cout << left<< setw(30) << "Aksesuaru suma po nuolaidu: " << right << setw(10) << kategorijosSuma(n, kategorija, kaina, kiekis, "Aksesuarai") << right << setw(85) << "Galutine moketina suma po nuolaidu: " << setw(10) << fixed << setprecision(2) << finalSuma << endl;
}
