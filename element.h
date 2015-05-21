#ifndef ELEMENT_H
#define ELEMENT_H
#include <QString>
#include <QPoint>
#include <QList>
#include <QVector>

//DODAĆ ITERATORY
//DODAC FUNKCJE CZY JEST OPERACJA O NAZWIE

class Atrybut;

class Operacja;

enum PrzekazanieParametru
{
    przezWartosc    = 0,
    przezReferencje = 1,
    przezWskaznik   = 2
};

enum Widocznosc
{
    wPrivate    = '-',
    wPublic     = '+',
    wProtected  = '#',
    wPackage    = '~',
    ND          = '^'
};

enum Krotnosc
{
    Jeden       = 1,
    JedenLubX   = 2,
    ZeroLub1    = 3,
    ZeroLubX    = 4,
    N           = 5,
    WiecejNizN  = 6
};

class Element
{
protected:
    QString NazwaElementu;
    static int IleElementow;
    int IleWskaznikowNaObiekt;
    QPoint Polozenie;
    QVector<Atrybut> WektorAtrybutow;

public:
    Element(QString nazwa = ""):NazwaElementu(nazwa)
    {}
    ~Element();
    QString getNazwa();
    QVector<Atrybut> getListaAtrybutow();
    void setNazwa(QString nazwa);
    void zmienNazwe(QString NowaNazwa);
    void dodajAtrybut(Atrybut atrybut);
    void czyJestAtrybut(Atrybut atrybut);
    void zmienWlasciwosciAtrybutuONazwie(QString nazwa, QString typ, Widocznosc wid, Krotnosc ile, bool czyStatyczna, bool czyConst,int n);
    void wymazAtrybut(QString atrybut);
    void usunAtrybutAt(int pos);
    QString atrybutGetText();
    virtual QString dajInfoDlaKodera() = 0;
    QString getWszystkieAtrybuty();
    QString getAtrybutyOSpecyfikatorzeDostepu(Widocznosc SpecyfikatorDostepu);
    bool czyJestAtrybutONazwie(Atrybut atrybut);
    bool czyJestAtrybutONazwie(const QString& nazwa);
};

class ElementZOperacjami: public Element
{
protected:
    QVector<Operacja> WektorOperacji;
public:
    ElementZOperacjami(QString nazwa = ""):Element(nazwa){}
    void dodajOperacje(const Operacja &operacja);
    void czyJestOperacja(QString operacja);
    void zmienWlasciwosciOperacjiONazwie(QString nazwa, QString typ, Widocznosc wid, Krotnosc ile, bool czyStatyczna, bool czyConst,int n, QString komentarz, PrzekazanieParametru przekaz);
    void wymazOperacje(QString operacja);
    QVector<Operacja> getListaOperacji();
    void usunOperacjaAt(int pos);
    QString getWszystkieOperacje();
    QString getOperacjeOSpecyfikatorzeDostepu(Widocznosc SpecyfikatorDostepu);
};

class SkladowaElementu
{
protected:
    int n;
    Krotnosc Ile;
    QString Typ;
    QString Komentarz;
    QString Nazwa;
    QString Kontener;
    Widocznosc Visibility;
    bool CzyStatyczna;
    bool CzyConst;
    virtual void aktualizujKomentarz() = 0;

public:
    SkladowaElementu(QString nazwa = "", QString typ = "", Widocznosc wid = wPrivate, bool czyStatyczna = false, bool czyConst = false,Krotnosc ile = Jeden,int ileN = 0):Nazwa(nazwa),Typ(typ), Visibility(wid),CzyStatyczna(czyStatyczna), CzyConst(czyConst),Ile(ile),n(ileN)
    {}

    QString getNazwa();
    QString getTyp();
    QString getKomentarz();
    QString getKontener();
    bool getCzyStatyczna();
    bool getCzyConst();
    Krotnosc getKrotnosc();
    int getN();
    void setNazwa(QString name);
    void setTyp(QString type);
    void setKontener(QString kont);
    void setKomentarz(QString kom);
    void setCzyStatyczna(bool czyTak);
    void setCzyConst(bool czyTak);
    void setKrotnosc(Krotnosc ilezTego);
    void setN(int ileN);
    void setSpecyfikatorDostepu(Widocznosc specDost);
    Widocznosc getSpecyfikatorDostepu();
};

class ParametrOperacji
{
    bool CzyDomyslnaWartosc;
    bool CzyConst;
    QString Typ;
    QString Nazwa;
    QString DomyslnaWartosc;
    PrzekazanieParametru Przekazanie;

public:
    ParametrOperacji(QString nazwa,QString typ = "",bool czyConst = false,PrzekazanieParametru przekazanie = przezWartosc, bool czyDomyslnaWart = false, QString domyslnaWart = ""):Nazwa(nazwa),CzyConst(czyConst),Typ(typ),Przekazanie(przekazanie),CzyDomyslnaWartosc(czyDomyslnaWart),DomyslnaWartosc(domyslnaWart)
    {}
    friend QString&
       operator<<(QString& wyjscie, const ParametrOperacji metoda);
    QString getName();
    void setName(QString nazwa);
    QString getType();
    void setType(QString nazwa);
    PrzekazanieParametru getPass();
    void setPass(PrzekazanieParametru przekaz);

};

class Operacja: public SkladowaElementu
{
    QList<Atrybut> ListaParamMetod;
    PrzekazanieParametru Przekaz;
    bool CzyWirtualna;

public:
    QList<Atrybut> getListaParametrow();
    PrzekazanieParametru getTypPrzekazaniaParametru();
    bool getCzyWirtualna();
    void setPrzekazanieParametru(PrzekazanieParametru przekaz);
    void setCzyWirtualna(bool czyTak);
    void usunParametrAt(int gdzie);
    int dodajParametr(Atrybut Parametr);
    bool czyJestParametr(Atrybut Parametr);
    void replaceAtrybutAt(Atrybut atrybut, int at);
    bool getAtrybutAt(Atrybut& atrybut, int at);
    Operacja(QString nazwa = "",QString typ = "",Widocznosc wid = wPrivate,PrzekazanieParametru przekaz = przezWartosc, bool czyStatyczna = false, bool czyConst = false, bool czyWirtualna = false,Krotnosc ile = Jeden,int ileN = 0):SkladowaElementu(nazwa,typ,wid,czyStatyczna,czyConst,ile,ileN),Przekaz(przekaz), CzyWirtualna(czyWirtualna){aktualizujKomentarz();}
    Operacja(QList<Atrybut> ListaParam, QString typ = "", Widocznosc wid = wPrivate, QString nazwa = "",PrzekazanieParametru przekaz = przezWartosc, bool czyStatyczna = false, bool czyConst = false, bool czyWirtualna = false,Krotnosc ile = Jeden):SkladowaElementu(nazwa,typ,wid,czyStatyczna,czyConst,ile),ListaParamMetod(ListaParam), Przekaz(przekaz), CzyWirtualna(czyWirtualna){aktualizujKomentarz();}
    int ParamSize();

    friend QString&
        operator<<(QString& napis, Operacja operacja);

    void aktualizujKomentarz();
    PrzekazanieParametru przezCoPrzekazujesz();
};

class KontenerOperacji
{
    QVector<Operacja*> WektorOperacji;

public:
    KontenerOperacji(){}
    KontenerOperacji(QVector<Operacja*> gotowaLista);
    ~KontenerOperacji();
    bool CzyJestOperacjaODanejNazwie(QString operacja);
    void add(Operacja* operacja);

};

class Atrybut: public SkladowaElementu
{
    QString DomyslnaWartosc;
    bool doEnum;

public:
    Atrybut(QString nazwa = "",QString typ = "",Widocznosc wid = wPrivate,Krotnosc ile = Jeden,QString domyslnaWart = "", bool czyStatyczna = false, bool czyConst = false,int ileN = 0,bool czyDoEnum = false):SkladowaElementu(nazwa,typ,wid,czyStatyczna,czyConst,ile,ileN), DomyslnaWartosc(domyslnaWart),doEnum(czyDoEnum){aktualizujKomentarz();}

    QString getDomyslnaWartosc();
    bool getDoEnum();
    void setDomyslnaWartosc(QString domyslna);
    void setDoEnum(bool doNiego);

    friend QString&
    operator<<(QString& napis, Atrybut atrybut);
    void aktualizujKomentarz();
};

class Klasa: public ElementZOperacjami
{
    bool CzyAbstrakcyjna;
public:
    bool getCzyAbstrakcyjna();
    void setCzyAbstrakcyjna(bool czyAbstrakcyjna);
    Klasa(QString nazwa = "", bool czyAbstrakcyjna = false):ElementZOperacjami(nazwa),CzyAbstrakcyjna(czyAbstrakcyjna)
    {
        IleElementow++;
    }
    ~Klasa()
    {
        IleElementow--;
    }
    QString dajInfoDlaKodera(){return "Klasa";}
};

class Struktura: public ElementZOperacjami
{
public:
    QString dajInfoDlaKodera(){return "Struktura";}

    Struktura(QString nazwa = ""):ElementZOperacjami(nazwa)
    {
        IleElementow++;
    }
    ~Struktura()
    {
        IleElementow--;
    }

};

class PrzestrzenNazw: public ElementZOperacjami
{
public:
    QString dajInfoDlaKodera(){return "Package";}
    PrzestrzenNazw(QString nazwa = ""):ElementZOperacjami(nazwa)
    {
        IleElementow++;
    }
    ~PrzestrzenNazw()
    {
        IleElementow--;
    }

};

class Unia: public Element
{
public:
    QString dajInfoDlaKodera(){return "Union";}
    Unia(QString nazwa = ""):Element(nazwa)
    {
        IleElementow++;
    }
    ~Unia()
    {
        IleElementow--;
    }
};

class Wyliczenie: public Element
{
public:
    QString dajInfoDlaKodera(){return "Element";}
    Wyliczenie(QString nazwa = ""):Element(nazwa)
    {
        IleElementow++;
    }
    ~Wyliczenie()
    {
        IleElementow--;
    }
};

#endif // ELEMENT_H
