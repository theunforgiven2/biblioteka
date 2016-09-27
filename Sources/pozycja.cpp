#include "pozycja.h"

Pozycja::Pozycja(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int liczebnosc_)
{
    strcpy_safe(this->autor, autor_);
    strcpy_safe(this->tytul, tytul_);
    strcpy_safe(this->wydawnictwo, wydawnictwo_);
    strcpy_safe(this->dlugosc, dlugosc_);
    this->liczebnosc=liczebnosc_;
}

void Pozycja::strcpy_safe(char *docelowy, const char *zrodlo, int size){
    if(strcpy_s(docelowy, sizeof(char)*size, zrodlo)){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        msg.setText("Przekroczono zakres buforu, takie cos sie nie zapisze");
        msg.exec();
    }
}

QString Pozycja::getAutor() const{
    return QString(this->autor);
}

QString Pozycja::getTytul() const{
    return QString(this->tytul);
}

QString Pozycja::getWydawnictwo(){
    return QString(this->wydawnictwo);
}

QString Pozycja::getDlugosc(){
    return QString(this->dlugosc);
}

int Pozycja::getLiczebnosc(){
    return this->liczebnosc;
}

TypPozycji Pozycja::getTyp() const{
    return this->typ;
}
