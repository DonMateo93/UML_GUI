#ifndef KODER_H
#define KODER_H
#include "relacja.h"
#include "element.h"
#include <QVector>
#include <QList>

using namespace Rel;

class Koder
{
protected:
//    virtual void sprawdzPlik();
    QList<Relacja*> ListaRelacji;
    QList<Element*> ListaElementow;
    QString RodzajStosowanegoKontenera;
    bool CzyKontrolowacLogikePoloczen;
    int ileObiektow;

public:
    Koder(bool czyKontrolowac = false, QString rodzajKontenera = "std::deque"):CzyKontrolowacLogikePoloczen(czyKontrolowac),ileObiektow(0),RodzajStosowanegoKontenera(rodzajKontenera){}
    ~Koder(){}
    virtual void poprawKodWPliku(const QString& PathAndName) = 0;
    virtual void wprowadzElementDoPliku(QString FilePath, PrzestrzenNazw* przestrzen, PrzestrzenNazw* doJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Struktura* struktura, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Wyliczenie* wyliczenie, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzElementDoPliku(QString FilePathAndName, Unia* unia, PrzestrzenNazw* DoJakiej = NULL) = 0;
    virtual void wprowadzDoPlikuWszystkieElementy(QString FilePathAndName) = 0;
    virtual void wprowadzDoPlikuWszyskieRelacje(QString FilePathAndName) = 0;
    virtual void dodajRelacje(Relacja* relacja) = 0;
    virtual void wprowadzDoPlikuAgregacjeLubKompozycje(QString FilePathAndName, Relacja* relacja) = 0;
    virtual void wprowadzDoPlikuAsocjacje(QString FilePathAndName, Relacja* relacja) = 0;
    virtual void wprowadzDoPlikuGeneralizacje(QString FilePathAndName, Relacja* relacja) = 0;
    virtual void wprowadzDoPlikuDependency(QString FilePathAndName, Relacja* relacja) = 0;
    void dodajElementDoListy(Element* element);
    virtual PrzestrzenNazw* dajAdresNadrzednejPrzestrzeni(Element* element) = 0;
    virtual QString dekodujAtrybut(const Atrybut& atrybut) = 0;
    virtual QString dekodujOperacje(const Operacja& operacja, QString przedrostekDoCpp = "") = 0;
    virtual QString dekodujBlokOperacji(const QString& BlokOperacji, QString przedrostekDoCpp = "") = 0;
    virtual QString dekodujBlokAtrybutow(const QString& BlokAtrybutow,bool CzyZPustymiLiniami = false) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(PrzestrzenNazw* przestrzen) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Klasa* klasa) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Struktura* struktura) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Unia* unia) = 0;
    virtual QString przygotujBlokTekstuDoWpisaniaElementu(Wyliczenie* wyliczenie) = 0;
    virtual QString przygotujBlokTekstuDoCpp(PrzestrzenNazw* przestrzen, QString przedrostekDoCpp) = 0;
    virtual QString przygotujBlokTekstuDoCpp(Klasa* klasa, QString przedrostekDoCpp) = 0;
    virtual QString przygotujBlokTekstuDoCpp(Struktura* struktura, QString przedrostekDoCpp) = 0;
};

class KoderCpp: public Koder
{

public:
    KoderCpp(bool czyKontrolowac = false):Koder(czyKontrolowac){}
    void poprawKodWPliku(const QString& PathAndName);
    void wprowadzElementDoPliku(QString FilePathAndName, PrzestrzenNazw *Przestrzen, PrzestrzenNazw *DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa, PrzestrzenNazw* DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Struktura* struktura, PrzestrzenNazw* DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Wyliczenie* wyliczenie, PrzestrzenNazw* DoJakiej = NULL);
    void wprowadzElementDoPliku(QString FilePathAndName, Unia* unia, PrzestrzenNazw* DoJakiej = NULL);
    void generujKodDoPliku(QString path);
    void wprowadzDoPlikuWszystkieElementy(QString FilePathAndName);
    void wprowadzDoPlikuWszyskieRelacje(QString FilePathAndName);
    void dodajRelacje(Relacja* relacja);
    void wprowadzDoPlikuAgregacjeLubKompozycje(QString FilePathAndName, Relacja* relacja);
    void wprowadzDoPlikuAsocjacje(QString FilePathAndName, Relacja* relacja);
    void wprowadzDoPlikuGeneralizacje(QString FilePathAndName, Relacja* relacja);
    void wprowadzDoPlikuDependency(QString FilePathAndName, Relacja* relacja);
    PrzestrzenNazw* dajAdresNadrzednejPrzestrzeni(Element *element);
    QString dekodujAtrybut(const QString& atrybut);
    QString dekodujAtrybut(const Atrybut& atrybut);
    QString dekodujOperacje(const Operacja& operacja, QString przedrostekDoCpp = "");
    QString dekodujOperacje(const QString& operacja, QString przedrostekDoCpp = "");
    QString dekodujBlokOperacji(const QString& BlokOperacji, QString przedrostekDoCpp = "");
    QString dekodujBlokAtrybutow(const QString& BlokAtrybutow, bool CzyZPustymiLiniami = false);
    QString przygotujBlokTekstuDoWpisaniaElementu(PrzestrzenNazw* przestrzen);
    QString przygotujBlokTekstuDoWpisaniaElementu(Klasa* klasa);
    QString przygotujBlokTekstuDoWpisaniaElementu(Struktura* struktura);
    QString przygotujBlokTekstuDoWpisaniaElementu(Unia* unia);
    QString przygotujBlokTekstuDoWpisaniaElementu(Wyliczenie* wyliczenie);
    QString przygotujBlokTekstuDoCpp(PrzestrzenNazw* przestrzen, QString przedrostekDoCpp);
    QString przygotujBlokTekstuDoCpp(Klasa* klasa, QString przedrostekDoCpp);
    QString przygotujBlokTekstuDoCpp(Struktura* struktura, QString przedrostekDoCpp);
};

class KoderJava: public Koder
{

public:
};

#endif // KODER_H
