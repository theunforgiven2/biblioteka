#ifndef KASETAAUDIO_H
#define KASETAAUDIO_H
#include <pozycja.h>

class KasetaAudio : public Pozycja
{
private:
    double cena;
public:
    KasetaAudio(){}
    KasetaAudio(const char autor_[], const char tytul_[], const char wydawnictwo_[], const char dlugosc_[], double cena_, int liczebnosc_=1);
    KasetaAudio(KasetaAudio *file):KasetaAudio(file->autor, file->tytul, file->wydawnictwo, file->dlugosc, file->cena, file->liczebnosc){}
    void edytuj(QString, int);
    double getCena();
    ~KasetaAudio(){}
};

#endif // KASETAAUDIO_H
