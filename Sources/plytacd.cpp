#include "plytacd.h"
#include <QDebug>
PlytaCD::PlytaCD(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int liczbaUtworow_, int liczebnosc_)
    :Pozycja(autor_, tytul_, wydawnictwo_, dlugosc_, liczebnosc_)
{
    this->liczbaUtworow=liczbaUtworow_;
    this->typ=PLYTACD;
}

void PlytaCD::edytuj(QString val, int col){
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
            this->liczbaUtworow = val.toInt();
            break;
        case 5:
            this->liczebnosc = val.toInt();
            break;
     }
}

int PlytaCD::getLiczbaUtworow(){
    return this->liczbaUtworow;
}
