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

void addSpaceship(Ship spaceship[], int jumlahSpaceship, int &countShip, int MAX_SHIP);
void displaySpaceship(Ship spaceship[], int jumlahSpaceship);
void isiBahanBakar(Ship spaceship[], int jumlahSpaceship);
void repairShip(Ship spaceship[], int jumlahSpaceship);
void misi(Ship spaceship[], int countShip);
void randomEvent(Ship spaceship[], int countShip);
bool hancur(Ship spaceship[], int countShip, int &indexHancur, int &jumlahHancur);

int main(){
    srand(time(0));
    const int MAX_SHIP = 5;
    Ship spaceship[MAX_SHIP];
    int jumlahSpaceship = 0;
    int countShip = 0;
    int menu;
    int indexHancur = 0;
    int jumlahHancur = 0;

    cout << "Masukkan jumlah spaceship (Maks = " << MAX_SHIP <<"): ";
    cin >> jumlahSpaceship;
    while(jumlahSpaceship > MAX_SHIP || jumlahSpaceship < 1){
        cout << "Masukkan jumlah yang valid!\n";
        cout << "Masukkan jumlah spaceship (Maks = " << MAX_SHIP <<"): ";
        cin >> jumlahSpaceship;
    }
    addSpaceship(spaceship, jumlahSpaceship, countShip, MAX_SHIP);
    displaySpaceship(spaceship, jumlahSpaceship);
    do{
        cout << "------------------------- MENU -------------------------\n";
        cout << "1. Tambah spaceship\n2. Isi bahan bakaar spaceship\n3. Perbaiki spaceship\n4. Menjalankan misi\n5. Laporan misi\n6. Keluar\n";
        cin >> menu;
        if(menu == 1){
            addSpaceship(spaceship, jumlahSpaceship, countShip, MAX_SHIP);
        }else if(menu == 2){
            isiBahanBakar(spaceship, jumlahSpaceship);
        }else if(menu == 3){
            repairShip(spaceship, jumlahSpaceship);
        }else if(menu == 4){
            cout << "Spaceship sedang menjalankan misi...\n";
            misi(spaceship, countShip);
            bool isHancur = hancur(spaceship, countShip, indexHancur, jumlahHancur);
            if(isHancur == true){
                for(int i = indexHancur; i < countShip - jumlahHancur; i++){
                    spaceship[i] = spaceship[i+1];
                }
                countShip--;
            }
        }else if(menu == 5){

        }else if(menu == 6){
            cout << "Terima kasih telah bermain!";
        }else{
            cout << "Masukkan pilihan yang valid!";
        }
    }while(menu != 6);
    return 0;
}

void addSpaceship(Ship spaceship[], int jumlahSpaceship, int &countShip, int MAX_SHIP){
    if(countShip == 0){
        for(int i = 0; i < jumlahSpaceship; i++){
            cin.ignore();
            cout << "Masukkan nama spaceship yang ke-" << i + 1 << ": ";
            getline(cin, spaceship[i].nama);
            cout << "Masukkan jumlah kru: ";
            cin >> spaceship[i].kru;
            while(spaceship[i].kru < 1){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan jumlah kru: ";
                cin >> spaceship[i].kru;
            }
            cout << "Masukkan presentase bahan bakar spaceship: ";
            cin >> spaceship[i].bahanBakar;
            while(spaceship[i].bahanBakar < 0 || spaceship[i].bahanBakar > 100){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan bahan bakar awal: ";
                cin >> spaceship[i].bahanBakar;
            }
            cout << "Masukkan presentase kondisi spaceship: ";
            cin >> spaceship[i].kondisi;
            while(spaceship[i].kondisi < 0 || spaceship[i].kondisi > 100){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan kondisi awal spaceship: ";
                cin >> spaceship[i].kondisi;
            }
            countShip++;
        }
    }
    else{
        cout << "Masukkan jumlah kapal yang ingin ditambah: ";
        cin >> jumlahSpaceship;
        while(countShip + jumlahSpaceship > MAX_SHIP){
            cout << "Jumlah melebihi batas maksimal!";
            cout << "Masukkan jumlah kapal yang ingin ditambah: ";
            cin >> jumlahSpaceship;
        }
        for(int i = 0; i < jumlahSpaceship; i++){
            cin.ignore();
            cout << "Masukkan nama spaceship yang ke-" << countShip + i + 1 << ": ";
            getline(cin, spaceship[countShip + i].nama);
            cout << "Masukkan jumlah kru: ";
            cin >> spaceship[countShip + i].kru;
            while(spaceship[countShip + i].kru < 1){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan jumlah kru: ";
                cin >> spaceship[countShip + i].kru;
            }
            cout << "Masukkan presentase bahan bakar spaceship: ";
            cin >> spaceship[countShip + i].bahanBakar;
            while(spaceship[countShip + i].bahanBakar < 0 || spaceship[countShip + i].bahanBakar > 100){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan bahan bakar awal: ";
                cin >> spaceship[countShip + i].bahanBakar;
            }
            cout << "Masukkan presentase kondisi spaceship: ";
            cin >> spaceship[countShip + i].kondisi;
            while(spaceship[countShip + i].kondisi < 0 || spaceship[countShip + i].kondisi > 100){
                cout << "Masukkan jumlah yang sesuai!\n";
                cout << "Masukkan kondisi awal spaceship: ";
                cin >> spaceship[countShip + i].kondisi;
            }
            countShip++;
        }
    }
    cout << '\n';
}

void displaySpaceship(Ship spaceship[], int jumlahSpaceship){
    cout << "--------------------------- Daftar spaceship ---------------------------\n";
    for(int i = 0; i < jumlahSpaceship; i++){
        cout << i+1 << ". " << spaceship[i].nama << " ship | Jumlah kru: " << spaceship[i].kru << " | Bahan bakar: " << spaceship[i].bahanBakar << "% | Kondisi awak: " << spaceship[i].kondisi << "%\n";
    }
    cout << "Peringatan bahan bakar rendah, pada spaceship nomor | ";
    for(int i = 0; i < jumlahSpaceship; i++){
        if(spaceship[i].bahanBakar <= 30){
            cout << i + 1 << " | ";
        }
    }
    cout << "\n\n";
}

void isiBahanBakar(Ship spaceship[], int jumlahSpaceship){
    int pilihSpaceship;
    cout << "Mau isi bahan bakar spaceship nomor berapa: ";
    cin >> pilihSpaceship;
    int isianBB = 0;
    cout << "Masukkan jumlah pengisian bahan bakar: ";
    cin >> isianBB;
    spaceship[pilihSpaceship - 1].bahanBakar += isianBB;
    displaySpaceship(spaceship, jumlahSpaceship);
}

void repairShip(Ship spaceship[], int jumlahSpaceship){
    int pilihSpaceship;
    cout << "Mau isi perbaiki spaceship nomor berapa: ";
    cin >> pilihSpaceship;
    int perbaikan = 0;
    cout << "Masukkan presentase perbaikan: ";
    cin >> perbaikan;
    spaceship[pilihSpaceship - 1].kondisi += perbaikan;
    displaySpaceship(spaceship, jumlahSpaceship);
}

void misi(Ship spaceship[], int countShip){
    for(int i = 0; i < countShip; i++){
        int bahanBakarKurang = rand() % 11 + 10;
        spaceship[i].bahanBakar -= bahanBakarKurang;
        cout << "Bahan bakar spaceship " << spaceship[i].nama << " berkurang sebanyak " << bahanBakarKurang << "%\n";
    }
    for(int i = 0; i < countShip; i++){
        int kondisiKurang = rand() % 6;
        spaceship[i].kondisi -= kondisiKurang;
        cout << "Kesehatan spaceship " << spaceship[i].nama << " berkurang sebanyak " << kondisiKurang << "%\n";
    }
    randomEvent(spaceship, countShip);
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
            cout << "Jumlah kru spaceship " << spaceship[i].nama << " berkurang sebanyak " << kruMeninggal << " karena terkena benturan asteroid\n";
            cout << "Kesehatan spaceship " << spaceship[i].nama << " berkurang sebanyak " << kondisiKurang << "% lagi karena terkena asteroid\n";
        }
    }
}

bool hancur(Ship spaceship[], int countShip, int &indexHancur, int &jumlahHancur){
    for(int i = 0; i < countShip; i++){
        if(spaceship[i].bahanBakar < 0 || spaceship[i].kondisi < 0 || spaceship[i].kru <= 0){
            indexHancur = i;
            jumlahHancur++;
            cout << "Spaceship " << spaceship[i].nama << " telah hancur\n";
            return true;
        }
    }
    return false;
}