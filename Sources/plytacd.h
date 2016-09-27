#ifndef PLYTACD_H
#define PLYTACD_H
#include "pozycja.h"
#include <QDebug>

class PlytaCD : public Pozycja
{
private:
    int liczbaUtworow;
public:
    PlytaCD(){}
    PlytaCD(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int liczbaUtworow_, int liczebnosc_=1);
    PlytaCD(PlytaCD *file):PlytaCD(file->autor, file->tytul, file->wydawnictwo, file->dlugosc, file->liczbaUtworow, file->liczebnosc){}
    void edytuj(QString, int);
    int getLiczbaUtworow();
    ~PlytaCD(){}
};

#endif // PLYTACD_H
