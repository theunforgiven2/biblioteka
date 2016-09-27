#include "kasetaaudio.h"
KasetaAudio::KasetaAudio(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], double cena_, int liczebnosc_)
    :Pozycja(autor_, tytul_, wydawnictwo_, dlugosc_, liczebnosc_)
{
    this->cena=cena_;
    this->typ=KASETAAUDIO;
}

void KasetaAudio::edytuj(QString val, int col){
    switch(col){
        case 0:
            strcpy_safe(this->autor, val.toStdString().c_str());
            break;
        case 1:
            strcpy_safe(this->tytul, val.toStdString().c_str());
            break;
        case 2:
            strcpy_safe(this->dlugosc, val.toStdString().c_str(), 7);
            break;
        case 3:
            strcpy_safe(this->wydawnictwo, val.toStdString().c_str());
            break;
        case 4:
            this->cena = val.toDouble();
            break;
        case 5:
            this->liczebnosc = val.toInt();
            break;
     }
}

double KasetaAudio::getCena(){
    return this->cena;
}
