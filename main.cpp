#include <iostream>
#include <string>
#include <map>
#include <cstring>

using namespace std;

// GLOBAL VARIABLE DECRARATION
char escChar = 27; // the decimal code for escape character is 27

// GLOBAL VARIABLE DECRARATION AS TEMPORARY DATABASE
struct Mahasiwa {
  char nim[10];
  char nama[32];
  char jurusan[10];
};
Mahasiwa mhs[4];

struct Matakuliah {
  char kode[5];
  char nama[10];
  int bobot;
};
Matakuliah mtl[4];

struct Nilai {
  char nimMhs[10];
  char kodeMtl[5];
  int uts;
  int tugas;
  int uas;
};
Nilai nil[8];

// FUNCTION
void clear() {
  #ifdef __unix__
    // BASH
    system("clear");
  #else
    //DOS
    system("cls");
  #endif
}

int getTotalNil(int a, int b, int c){
  return (0.3 * a) + (0.3 * b) + (0.4 * c);
}

char getGrade(int a){
  if(a >= 85){
    return 'A';
  } else if(a >= 75){
    return 'B';
  } else if(a >= 60){
    return 'C';
  } else if(a >= 40){
    return 'D';
  } else {
    return 'E';
  }
}

int getIdxMhsByNim(char *nimMhs){
  int totalMhs = sizeof(mhs)/sizeof(mhs[0]);
  bool foundMhs = false;
  int indexMhs = -1;
  for(int i = 0; i < totalMhs; i++){
    if(strcmp(mhs[i].nim, nimMhs) == 0 && foundMhs == false){
      foundMhs = true;
      indexMhs = i;
    }
  }
  return indexMhs;
}

int getIdxMtlByKode(char *kodeMtl){
  int totalMtl = sizeof(mtl)/sizeof(mtl[0]);
  bool foundMtl = false;
  int indexMtl = -1;
  for(int i = 0; i < totalMtl; i++){
    if(strcmp(mtl[i].kode, kodeMtl) == 0 && foundMtl == false){
      foundMtl = true;
      indexMtl = i;
    }
  }
  return indexMtl;
}

void renderMhs(){
  clear();
  int index = getIdxMhsByNim("");
  if(index >= 0){
    cout<<"             INPUT DATA MAHASISWA             "<< endl;
    cout<<"=============================================="<< endl;

    cout<<"NIM = ";
    cin>>mhs[index].nim;

    cout<<"NAMA = ";
    cin>>mhs[index].nama;

    cout<<"JURUSAN = ";
    cin>>mhs[index].jurusan;

    cout<<"Data berhasil tersimpan!"<< endl;

  } else {
    cout<<"Maaf, Data mahasiswa telah penuh!"<< endl;
  }
}

void renderMtl(){
  clear();
  int index = getIdxMtlByKode("");
  if(index >= 0){
    cout<<"             INPUT DATA MATAKULIAH             "<< endl;
    cout<<"==============================================="<< endl;

    cout<<"Kode Matakuliah = ";
    cin>>mtl[index].kode;

    cout<<"Nama Matakuliah = ";
    cin>>mtl[index].nama;

    cout<<"BOBOT SKS = ";
    cin>>mtl[index].bobot;

    cout<<"Data berhasil tersimpan!"<< endl;

  } else {
    cout<<"Maaf, Data matakuliah telah penuh!"<< endl;
  }
}

void renderNil(){
  clear();
  char nimMhs[10];
  char kodeMtl[5];

  cout<<"             INPUT NILAI             "<< endl;
  cout<<"====================================="<< endl;

  cout<<"Input NIM = ";
  cin>>nimMhs;

  // SEARCH MAHASISWA
  int indexMhs = getIdxMhsByNim(nimMhs);
  if(indexMhs >= 0){
    cout<<"Nama = "<< mhs[indexMhs].nama << endl;
    cout<<"Jurusan = "<< mhs[indexMhs].jurusan << endl;
  }
  else {
    cout<<"Mahasiswa tidak ditemukan!"<< endl;
    return;
  }

  cout<<"Input Kode Matakuliah = ";
  cin>>kodeMtl;

  // SEARCH MATAKULIAH
  int indexMtl = getIdxMtlByKode(kodeMtl);
  if(indexMtl >= 0){
    cout<<"Nama Matakuliah = "<< mtl[indexMtl].nama << endl;
    cout<<"Bobot SKS = "<< mtl[indexMtl].bobot << endl;
  }
  else {
    cout<<"Matakuliah tidak ditemukan!"<< endl;
    return;
  }

  int totalNil = sizeof(nil)/sizeof(nil[0]);
  bool alreadyFilled = false;
  bool canContinue = false;
  int index = 0;
  for(int i = 0; i < totalNil; i++){
    if(strcmp(nil[i].nimMhs, nimMhs) == 0 && strcmp(nil[i].kodeMtl, kodeMtl) == 0){
      alreadyFilled = true;
    }
    if(!*nil[i].nimMhs && canContinue == false && alreadyFilled == false){
      canContinue = true;
      index = i;
    }
  }
  if(canContinue == true){

    strcpy(nil[index].nimMhs,nimMhs);
    strcpy(nil[index].kodeMtl,kodeMtl);

    cout<<"Input Nilai UTS = ";
    cin>>nil[index].uts;

    cout<<"Input Nilai TUGAS = ";
    cin>>nil[index].tugas;

    cout<<"Input Nilai UAS = ";
    cin>>nil[index].uas;

    int totalNilai = getTotalNil(nil[index].uts,nil[index].tugas,nil[index].uas);

    cout<<"Nilai Akhir = "<<  totalNilai << endl;
    cout<<"Grade = "<<  getGrade(totalNilai) << endl;

    cout<<"Data berhasil tersimpan!"<< endl;

  } else {
    cout<<"Maaf, Data nilai telah diinput sebelumnya!"<< endl;
  }

}

void renderList(){
  clear();
  char nimMhs[10];
  char kodeMtl[5];

  cout<<"                                  DATA NILAI MAHASISWA                                  "<< endl;
  cout<<"========================================================================================"<< endl;
  cout<<"NO.| NIM | NAMA | JURUSAN | KODEMTK | NAMAMTK | SKS | UTS | TUGAS | UAS | AKHIR | GRADE"<< endl;
  cout<<"========================================================================================"<< endl;
  int totalNil = sizeof(nil)/sizeof(nil[0]);
  bool hasFilledData = false;
  for(int i = 0; i < totalNil; i++){
    if(*nil[i].nimMhs){
      hasFilledData = true;
      int totalNilai = getTotalNil(nil[i].uts,nil[i].tugas,nil[i].uas);

      cout<<(i+1);

      // SEARCH MAHASISWA
      int indexMhs = getIdxMhsByNim(nil[i].nimMhs);
      if(indexMhs >= 0){
        cout<<" | "<<  mhs[indexMhs].nim;
        cout<<" | "<<  mhs[indexMhs].nama;
        cout<<" | "<<  mhs[indexMhs].jurusan;
      }

      // SEARCH MATAKULIAH
      int indexMtl = getIdxMtlByKode(nil[i].kodeMtl);
      if(indexMtl >= 0){
        cout<<" | "<<  mtl[indexMtl].kode;
        cout<<" | "<<  mtl[indexMtl].nama;
        cout<<" | "<<  mtl[indexMtl].bobot;
      }

      cout<<" | "<<  nil[i].uts;
      cout<<" | "<<  nil[i].tugas;
      cout<<" | "<<  nil[i].uas;
      cout<<" | "<<  totalNilai;
      cout<<" | "<<  getGrade(totalNilai) << endl;
    }
  }
  if(hasFilledData == false){
    cout<<"Maaf, belum terdapat data!"<< endl;
  }

}

int main() {

  // SCOPPED VARIABLE DECRARATION
  int pilihan;
  char isX;

  do {
    clear();
    cout<<"============================= DATA NILAI ============================="<< endl;
    cout<<"1. Input Mahasiswa"<<endl;
    cout<<"2. Input Matakuliah"<<endl;
    cout<<"3. Input Nilai Mahasiswa"<<endl;
    cout<<"4. Cetak Daftar Nilai Mahasiswa"<<endl;
    cout<<"============================="<<endl;
    cout<<"Masukkan Pilihan [1...4]:";
    cin>>pilihan;
    cout<<"============================="<<endl;

    // LOGIC
    switch(pilihan){
      case 1:
        renderMhs();
        break;
      case 2:
        renderMtl();
        break;
      case 3:
        renderNil();
        break;
      case 4:
        renderList();
        break;
      default:
        cout<<"Menu tidak terdaftar!"<<endl;
    }

    cout << escChar << "[1m" << "Pilih X" << escChar << "[0m" << " untuk kembali ke Menu Utama" << endl;

    cin>>isX;
  }
  while (isX=='x' || isX=='X');
  cout<<"Terimakasih!"<<endl;
  return 0;
}
