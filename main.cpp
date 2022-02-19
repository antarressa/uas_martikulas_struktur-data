#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <vector>

using namespace std;

// GLOBAL VARIABLE DECRARATION
char escChar = 27; // the decimal code for escape character is 27

// GLOBAL VARIABLE DECRARATION AS TEMPORARY DATABASE
struct Mahasiswa {
  char nim[10];
  string nama;
  char jurusan[10];
};
// Mahasiswa mhs[0];
std::vector<Mahasiswa> mhs;

struct Matakuliah {
  char kode[5];
  string nama;
  int bobot;
};
std::vector<Matakuliah> mtl;

struct Nilai {
  char nimMhs[10];
  char kodeMtl[5];
  int uts;
  int tugas;
  int uas;
};
std::vector<Nilai> nil;

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

int getMaxMhs(){
  return mhs.size();
}

int getMaxMtl(){
  return mtl.size();
}

int getMaxNil(){
  return nil.size();
}

int getIdxMhsByNim(char *nimMhs){
  int totalMhs = getMaxMhs();
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
  int totalMtl = getMaxMtl();
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
  cout<<"             INPUT DATA MAHASISWA             "<< endl;
  cout<<"=============================================="<< endl;

  if(getMaxMhs() < 1){
    int size;
    cout<<"Input Jumlah Mahasiswa = ";
    cin>>size;
    cout<<endl;
    mhs.resize(size);
  }

  int index = getIdxMhsByNim("");
  if(index >= 0){
    cout<<"INPUT MAHASISWA KE "<<index+1<<". MAX("<<getMaxMhs()<<")"<< endl;

    cout<<"NIM = ";
    cin>>mhs[index].nim;

    cin.ignore();
    cout<<"NAMA = ";
    getline(cin, mhs[index].nama);

    cout<<"JURUSAN = ";
    cin>>mhs[index].jurusan;

    int index = getIdxMhsByNim("");
    if(index >= 0){
      char wantContinue;
      cout << escChar << "[1m" << "Pilih Y" << escChar << "[0m" << " untuk menginput data berikutnya" << endl;
      cin>>wantContinue;
      if(wantContinue == 'y' || wantContinue == 'Y'){
        renderMhs();
        return;
      }
    }

    cout<<"Data berhasil tersimpan!"<< endl;

  } else {
    cout<<"Maaf, Data mahasiswa telah penuh!"<< endl;
  }
}

void renderMtl(){
  clear();

  cout<<"             INPUT DATA MATAKULIAH             "<< endl;
  cout<<"==============================================="<< endl;

  if(getMaxMtl() < 1){
    int size;
    cout<<"Input Jumlah Matakuliah = ";
    cin>>size;
    cout<<endl;
    mtl.resize(size);
  }

  int index = getIdxMtlByKode("");
  if(index >= 0){

    cout<<"INPUT MATAKULIAH KE "<<index+1<<". MAX("<<getMaxMtl()<<")"<< endl;

    cout<<"Kode Matakuliah = ";
    cin>>mtl[index].kode;

    cin.ignore();
    cout<<"Nama Matakuliah = ";
    getline(cin, mtl[index].nama);

    cout<<"BOBOT SKS = ";
    cin>>mtl[index].bobot;

    int index = getIdxMtlByKode("");
    if(index >= 0){
      char wantContinue;
      cout << escChar << "[1m" << "Pilih Y" << escChar << "[0m" << " untuk menginput data berikutnya" << endl;
      cin>>wantContinue;
      if(wantContinue == 'y' || wantContinue == 'Y'){
        renderMtl();
        return;
      }
    }

    cout<<"Data berhasil tersimpan!"<< endl;

  } else {
    cout<<"Maaf, Data matakuliah telah penuh!"<< endl;
  }
}

void renderNil(){
  clear();

  cout<<"             INPUT NILAI             "<< endl;
  cout<<"====================================="<< endl;

  if(getMaxMhs() < 1){
    cout<<"Silahkan Input Mahasiswa terlebih dahulu!"<< endl;
    return;
  }
  else if(getMaxMtl() < 1){
    cout<<"Silahkan Input Matakuliah terlebih dahulu!"<< endl;
    return;
  }

  if(getMaxNil() < 1){
    nil.resize(getMaxMhs() * getMaxMtl());
  }

  char nimMhs[10];
  char kodeMtl[5];

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

  int totalNil = getMaxNil();
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

  cout<<"                                  DATA NILA MAHASISWA                                  "<< endl;
  cout<<"======================================================================================="<< endl;
  cout<<"NO.| NIM | NAMA | JURUSAN | KODEMTK | NAMAMTK | SKS | UTS | TUGAS | UAS | AKHIR | GRADE"<< endl;
  cout<<"======================================================================================="<< endl;
  int totalNil = getMaxNil();
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
