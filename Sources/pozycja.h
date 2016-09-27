#ifndef POZYCJA_H
#define POZYCJA_H
#include <cstring>
#include <QString>
#include <QMessageBox>
#include <QDebug>

enum TypPozycji {
    PLYTACD,
    KASETAWIDEO,
    KASETAWIDEODVHS,
    KASETAAUDIO
};

class Pozycja
{
protected:
    char autor[128];
    char tytul[128];
    char wydawnictwo[128];
    char dlugosc[7];
    int liczebnosc=1;
    TypPozycji typ;
public:
    Pozycja(){}
    Pozycja(const char[], const char[], const char[], const char[], int);
    virtual void edytuj(QString, int)=0;
    void strcpy_safe(char*, const char*, int size=127);
    QString getAutor() const;
    QString getTytul() const;
    QString getWydawnictwo();
    QString getDlugosc();
    void zwiekszLiczebnosc(){this->liczebnosc++;}
    int getLiczebnosc();
    TypPozycji getTyp() const;
    virtual ~Pozycja(){}
};

#endif // POZYCJA_H
