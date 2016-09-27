#ifndef KASETADVHS_H
#define KASETADVHS_H
#include <kasetawideo.h>

class KasetaDVHS : public KasetaWideo
{
private:
    int jakosc;
public:
    KasetaDVHS(){}
    KasetaDVHS(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], int rodzajKasety_, int jakosc_, int liczebnosc_=1);
    KasetaDVHS(KasetaDVHS *file):KasetaDVHS(file->autor, file->tytul, file->wydawnictwo, file->dlugosc, file->rodzajKasety, file->jakosc, file->liczebnosc){}
    void edytuj(QString, int);
    int getJakosc(){return this->jakosc;}
    ~KasetaDVHS(){}
};

#endif // KASETADVHS_H
