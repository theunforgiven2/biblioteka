#ifndef KASETAWIDEO_H
#define KASETAWIDEO_H
#include "pozycja.h"

class KasetaWideo : public Pozycja
{
protected:
    int rodzajKasety;
public:
    KasetaWideo(){}
    KasetaWideo(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int rodzajKasety_, int liczebnosc_=1);
    KasetaWideo(KasetaWideo *file):KasetaWideo(file->autor, file->tytul, file->wydawnictwo, file->dlugosc, file->rodzajKasety, file->liczebnosc){}
    void edytuj(QString, int);
    int getRodzajKasety() const;
    ~KasetaWideo(){}
};

#endif // KASETAWIDEO_H
