#include "kasetadvhs.h"


KasetaDVHS::KasetaDVHS(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int rodzajKasety_, int jakosc_, int liczebnosc_)
    :KasetaWideo(autor_, tytul_, wydawnictwo_, dlugosc_, rodzajKasety_, liczebnosc_)
{
    this->jakosc=jakosc_;
    this->typ=KASETAWIDEODVHS;
}
void KasetaDVHS::edytuj(QString val, int col){
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
        case 5:
            this->jakosc = val.toInt();
            break;
        case 6:
            this->liczebnosc = val.toInt();
            break;
     }
}
