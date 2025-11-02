#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Ship{
    string nama;
    int kru;
    int bahanBakar;
    int kondisi;
};

void addSpaceship(Ship spaceship[], int jumlahSpaceshipBaru, int &countShip, int MAX_SHIP);
void displaySpaceship(Ship spaceship[], int countShip);
void isiBahanBakar(Ship spaceship[], int &countShip);
void repairShip(Ship spaceship[], int &countShip);
void misi(Ship spaceship[], int countShip, string namaPlanet[], int jarakPlanet[], int &planetKe, int &jarakTotal, string planetDikunjungi[], int &totalBahanBakar);
void randomEvent(Ship spaceship[], int countShip);
bool hancur(Ship spaceship[], int countShip, int &indexHancur, int &jumlahHancur);
void laporanMisi(Ship spaceship[], int totalBahanBakar, int jarakTotal, int countShip, int planetKe, string planetDikunjungi[]);

int main(){
    srand(time(0));
    const int MAX_SHIP = 5;
    Ship spaceship[MAX_SHIP];
    string namaPlanet[5] = {"Jogja", "Moskow", "Tokyo", "Godean", "Gunkid"};
    //jarak dalam juta km
    int jarakPlanet[5] = {232, 541, 443, 85, 67};
    string planetDikunjungi[5];
    int jumlahSpaceship = 0;
    int countShip = 0;
    int menu;
    int indexHancur = 0;
    int jumlahHancur = 0;
    int planetKe = 0;
    int jarakTotal = 0;
    int totalBahanBakar = 0;

    cout << "Masukkan jumlah spaceship (Maks = " << MAX_SHIP <<"): ";
    cin >> jumlahSpaceship;
    while(jumlahSpaceship > MAX_SHIP || jumlahSpaceship < 1){
        cout << "Masukkan jumlah yang valid!\n";
        cout << "Masukkan jumlah spaceship (Maks = " << MAX_SHIP <<"): ";
        cin >> jumlahSpaceship;
    }
    addSpaceship(spaceship, jumlahSpaceship, countShip, MAX_SHIP);
    displaySpaceship(spaceship, countShip);
    do{
        cout << "\n============================================================\n";
        cout << "                             MENU                           \n";
        cout << "============================================================\n";
        cout << "1. Tambah spaceship\n";
        cout << "2. Isi bahan bakar spaceship\n";
        cout << "3. Perbaiki spaceship\n";
        cout << "4. Menjalankan misi\n";
        cout << "5. Laporan misi\n";
        cout << "6. Keluar\n";
        cout << "------------------------------------------------------------\n";
        cout << "Masukkan pilihan: ";
        while(!(cin >> menu)){
            cout << "Input tidak valid! Masukkan angka.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan pilihan: ";
        }
        if(menu == 1){
            addSpaceship(spaceship, jumlahSpaceship, countShip, MAX_SHIP);
            displaySpaceship(spaceship, countShip);
        }else if(menu == 2){
            isiBahanBakar(spaceship, countShip);
            displaySpaceship(spaceship, countShip);
        }else if(menu == 3){
            repairShip(spaceship, countShip);
            displaySpaceship(spaceship, countShip);
        }else if(menu == 4){
            cout << "Spaceship sedang menjalankan misi...\n";
            misi(spaceship, countShip, namaPlanet, jarakPlanet, planetKe, jarakTotal, planetDikunjungi, totalBahanBakar);
            while(true) {
                bool isHancur = hancur(spaceship, countShip, indexHancur, jumlahHancur);
                if(!isHancur) break;
                for(int i = indexHancur; i < countShip - 1; i++){
                    spaceship[i] = spaceship[i+1];
                }
                countShip--;
            }
            displaySpaceship(spaceship, countShip);
        }else if(menu == 5){
            cout << "Laporan misi:\n";
            laporanMisi(spaceship, totalBahanBakar, jarakTotal, countShip, planetKe, planetDikunjungi);
            displaySpaceship(spaceship, countShip);
        }else if(menu == 6){
            cout << "Terima kasih telah bermain!";
        }else{
            cout << "Masukkan pilihan yang valid!";
        }
    }while(menu != 6);
    return 0;
}

void addSpaceship(Ship spaceship[], int jumlahSpaceshipBaru, int &countShip, int MAX_SHIP){
    if(countShip == 0){
        for(int i = 0; i < jumlahSpaceshipBaru && i < MAX_SHIP; i++){
            cout << "Masukkan nama spaceship yang ke-" << i + 1 << ": ";
            cin.ignore(1000, '\n');
            getline(cin, spaceship[i].nama);
            
            cout << "Masukkan jumlah kru: ";
            while(!(cin >> spaceship[i].kru) || spaceship[i].kru < 1){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan jumlah kru: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            cout << "Masukkan presentase bahan bakar spaceship: ";
            while(!(cin >> spaceship[i].bahanBakar) || spaceship[i].bahanBakar < 0 || spaceship[i].bahanBakar > 100){
                cout << "Masukkan jumlah yang sesuai (0-100)!\n";
                cout << "Masukkan bahan bakar awal: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            cout << "Masukkan presentase kondisi spaceship: ";
            while(!(cin >> spaceship[i].kondisi) || spaceship[i].kondisi < 0 || spaceship[i].kondisi > 100){
                cout << "Masukkan jumlah yang sesuai (0-100)!\n";
                cout << "Masukkan kondisi awal spaceship: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            countShip++;
        }
    }
    else{
        int tambah = 0;
        cout << "Masukkan jumlah spaceship yang ingin ditambah: ";
        while(!(cin >> tambah) || tambah < 0 || countShip + tambah > MAX_SHIP){
            cout << "Jumlah tidak valid atau melebihi batas maksimal!\n";
            cout << "Masukkan jumlah spaceship yang ingin ditambah: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        
        for(int i = 0; i < tambah; i++){
            cout << "Masukkan nama spaceship yang ke-" << countShip + 1 << ": ";
            cin.ignore(1000, '\n');
            getline(cin, spaceship[countShip].nama);
            
            cout << "Masukkan jumlah kru: ";
            while(!(cin >> spaceship[countShip].kru) || spaceship[countShip].kru < 1){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan jumlah kru: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            cout << "Masukkan presentase bahan bakar spaceship: ";
            while(!(cin >> spaceship[countShip].bahanBakar) || spaceship[countShip].bahanBakar < 0 || spaceship[countShip].bahanBakar > 100){
                cout << "Masukkan jumlah yang sesuai (0-100)!\n";
                cout << "Masukkan bahan bakar awal: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            
            cout << "Masukkan presentase kondisi spaceship: ";
            while(!(cin >> spaceship[countShip].kondisi) || spaceship[countShip].kondisi < 0 || spaceship[countShip].kondisi > 100){
                cout << "Masukkan jumlah yang sesuai (0-100)!\n";
                cout << "Masukkan kondisi awal spaceship: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            countShip++;
        }
    }
    cout << '\n';
}

void displaySpaceship(Ship spaceship[], int countShip){
    cout << "\n============================================================\n";
    cout << "                    DAFTAR SPACESHIP                       \n";
    cout << "============================================================\n";
    if(countShip == 0) {
        cout << "              Belum ada spaceship yang dibuat              \n";
    } else {
        for(int i = 0; i < countShip; i++){
            cout << "\n " << i+1 << ". " << spaceship[i].nama << "\n";
            cout << "    |-- Jumlah kru        : " << spaceship[i].kru << "\n";
            cout << "    |-- Bahan bakar       : " << spaceship[i].bahanBakar << "%\n";
            cout << "    +-- Kondisi spaceship : " << spaceship[i].kondisi << "%\n";
        }
    }
    cout << "============================================================\n";

    bool adaPeringatan = false;
    for(int i = 0; i < countShip; i++){
        if(spaceship[i].bahanBakar <= 30){
            if(!adaPeringatan) {
                cout << "\n! PERINGATAN !\n";
                cout << "------------------------------------------------------------\n";
                cout << "Bahan bakar rendah pada spaceship:\n";
                adaPeringatan = true;
            }
            cout << "  - " << spaceship[i].nama << " (Nomor " << i + 1 << ")\n";
        }
    }
    if(adaPeringatan) {
        cout << "------------------------------------------------------------\n";
    }
}
 
void isiBahanBakar(Ship spaceship[], int &countShip){
    int pilihSpaceship;
    cout << "Mau isi bahan bakar spaceship nomor berapa: ";
    cin >> pilihSpaceship;
    while(pilihSpaceship < 1 || pilihSpaceship > countShip){
        cout << "Masukkan nomor spaceship yang benar!\n";
        cout << "Mau isi isi bahan spaceship nomor berapa: ";
        cin >> pilihSpaceship;
    }
    int isianBB = 0;
    cout << "Masukkan jumlah pengisian bahan bakar: ";
    cin >> isianBB;
    while(isianBB < 0 || spaceship[pilihSpaceship-1].bahanBakar + isianBB > 100){
        if(isianBB < 0){
            cout << "Nilai tidak boleh negatif!\n";
        } else {
            cout << "Tidak dapat melebihi 100%\n";
        }
        cout << "Masukkan jumlah pengisian bahan bakar: ";
        cin >> isianBB;
    }
    spaceship[pilihSpaceship - 1].bahanBakar += isianBB;
}

void repairShip(Ship spaceship[], int &countShip){
    int pilihSpaceship;
    cout << "Mau isi perbaiki spaceship nomor berapa: ";
    cin >> pilihSpaceship;
    while(pilihSpaceship < 1 || pilihSpaceship > countShip){
        cout << "Masukkan nomor spaceship yang benar!\n";
        cout << "Mau isi perbaiki spaceship nomor berapa: ";
        cin >> pilihSpaceship;
    }
    int perbaikan = 0;
    cout << "Masukkan presentase perbaikan: ";
    cin >> perbaikan;
    while(perbaikan < 0 || spaceship[pilihSpaceship-1].kondisi + perbaikan > 100){
        if(perbaikan < 0){
            cout << "Nilai tidak boleh negatif!\n";
        } else {
            cout << "Tidak dapat melebihi 100%\n";
        }
        cout << "Masukkan presentase perbaikan: ";
        cin >> perbaikan;
    }
    spaceship[pilihSpaceship - 1].kondisi += perbaikan;
}

void misi(Ship spaceship[], int countShip, string namaPlanet[], int jarakPlanet[], int &planetKe, int &jarakTotal, string planetDikunjungi[], int &totalBahanBakar){
    if(planetKe >= 5){
        cout << "Semua planet telah dikunjungi";
        return;
    }
    if(planetKe < 0){
        cout << "Error: Invalid planet index";
        return;
    }
    jarakTotal += jarakPlanet[planetKe];
    planetDikunjungi[planetKe] = namaPlanet[planetKe];
    for(int i = 0; i < countShip; i++){
        if(jarakPlanet[planetKe] < 100){
            int bahanBakarKurang = rand() % 11 + 10;
            spaceship[i].bahanBakar -= bahanBakarKurang;
            totalBahanBakar += bahanBakarKurang;
            cout << "Bahan bakar spaceship " << spaceship[i].nama << " berkurang sebanyak " << bahanBakarKurang << "%\n";
        }else if(jarakPlanet[planetKe] < 500){
            int bahanBakarKurang = rand() % 11 + 15;
            spaceship[i].bahanBakar -= bahanBakarKurang;
            totalBahanBakar += bahanBakarKurang;
            cout << "Bahan bakar spaceship " << spaceship[i].nama << " berkurang sebanyak " << bahanBakarKurang << "%\n";
        }else if(jarakPlanet[planetKe] < 1000){
            int bahanBakarKurang = rand() % 11 + 20;
            spaceship[i].bahanBakar -= bahanBakarKurang;
            totalBahanBakar += bahanBakarKurang;
            cout << "Bahan bakar spaceship " << spaceship[i].
            nama << " berkurang sebanyak " << bahanBakarKurang << "%\n";
        }
    }
    for(int i = 0; i < countShip; i++){
        int kondisiKurang = rand() % 6;
        spaceship[i].kondisi -= kondisiKurang;
        cout << "Kesehatan spaceship " << spaceship[i].nama << " berkurang sebanyak " << kondisiKurang << "%\n";
    }
    randomEvent(spaceship, countShip);
    planetKe++;
}

void randomEvent(Ship spaceship[], int countShip){
    int peluangAsteroid = rand() % 100;
    bool kenaAsteroid = (peluangAsteroid < 30);
    if(kenaAsteroid == true){
        for(int i = 0; i < countShip; i++){
            int kondisiKurang = rand() % 6 + 5;
            int kruMeninggal = rand() % 3;
            spaceship[i].kondisi -= kondisiKurang;
            spaceship[i].kru -= kruMeninggal;
            if(spaceship[i].kru < 0){
                spaceship[i].kru = 0;
            }
            cout << "Jumlah kru spaceship " << spaceship[i].nama << " berkurang sebanyak " << kruMeninggal << " karena terkena benturan asteroid\n";
            cout << "Kesehatan spaceship " << spaceship[i].nama << " berkurang sebanyak " << kondisiKurang << "% lagi karena terkena asteroid\n";
        }
    }
}

bool hancur(Ship spaceship[], int countShip, int &indexHancur, int &jumlahHancur){
    jumlahHancur = 0;
    bool adaHancur = false;
    for(int i = 0; i < countShip; i++){
        if(spaceship[i].bahanBakar < 0 || spaceship[i].kondisi < 0 || spaceship[i].kru <= 0){
            indexHancur = i;
            cout << "\n[!] SPACESHIP " << spaceship[i].nama << " TELAH HANCUR [!]\n";
            jumlahHancur++;
            adaHancur = true;
            break;
        }
    }
    return adaHancur;
}

void laporanMisi(Ship spaceship[], int totalBahanBakar, int jarakTotal, int countShip, int planetKe, string planetDikunjungi[]){
    int totalKru = 0;
    cout << "\nSTATUS SPACESHIP:\n";
    cout << "------------------------------------------------------------\n";
    for(int i = 0; i < countShip; i++){
        cout << spaceship[i].nama << ":\n";
        cout << "  -- Sisa bahan bakar: " << spaceship[i].bahanBakar << "%\n";
        totalKru += spaceship[i].kru;
    }
    
    cout << "\nSTATISTIK MISI:\n";
    cout << "------------------------------------------------------------\n";
    cout << "Total bahan bakar terpakai : " << totalBahanBakar << "%\n";
    cout << "Total kru yang bertahan    : " << totalKru << " orang\n";
    cout << "Total jarak tempuh         : " << jarakTotal << " juta km\n";
    
    cout << "\nPLANET YANG DIKUNJUNGI:\n";
    cout << "------------------------------------------------------------\n";
    for(int i = 0; i < planetKe; i++){
        cout << " " << i+1 << ". " << planetDikunjungi[i] << '\n';
    }
    cout << "============================================================\n";
}