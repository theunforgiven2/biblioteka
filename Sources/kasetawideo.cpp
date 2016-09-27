#include "kasetawideo.h"

KasetaWideo::KasetaWideo(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int rodzajKasety_, int liczebnosc_)
    :Pozycja(autor_, tytul_, wydawnictwo_, dlugosc_, liczebnosc_)
{
    this->rodzajKasety=rodzajKasety_;
    this->typ=KASETAWIDEO;
}

void KasetaWideo::edytuj(QString val, int col){
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
            this->rodzajKasety = val.toInt();
            break;
        case 6:
            this->liczebnosc = val.toInt();
            break;
     }
}

int KasetaWideo::getRodzajKasety() const{
    return this->rodzajKasety;
}
