#ifndef RELACJA_H
#define RELACJA_H
#include <QString>
#include <QStringList>
#include <QVector>
#include "element.h"

namespace Rel {

class Relacja
{
protected:
    Element* Pierwszy;  //pokazywany przez strzalke
    Element* Drugi;
    QString komentarz;
    Widocznosc widocznosc;
    QString kontener;
public:

    Relacja(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = ""):Pierwszy(pierwszy),Drugi(drugi),widocznosc(wid),komentarz(koment)
    {}
    ~Relacja();
    bool CzyJestElement();
    virtual void draw() = 0;
    QString getNameDrugi(){return Drugi->getNazwa();}
    QString getNamePierwszy(){return Pierwszy->getNazwa();}
    QString getKomentarz(){return komentarz;}
    QString getKontener();
    void setKontener(QString konte);
    void setKomentarz(QString koment);
    bool czyZgadzaSieAdresZElementemPierwszym(Element* element);
    bool czyZgadzaSieAdresZElementemDrugim(Element* element);
    bool czyPierwszyToPrzestrzen();
    bool czyPierwszyToKlasa();
    bool czyDrugiToKlasa();
    bool czyPierwszyToStruktura();
    bool czyDrugiToStruktura();
    Element* dajAdresPierwszy(){return Pierwszy;}
    Element* dajAdresDrugi(){return Drugi;}
    Widocznosc getWidocznosc(){return widocznosc;}
    void setWidocznosc(Widocznosc wid);
};

class Dependency: public Relacja
{

public:
    Dependency(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = ""):Relacja(pierwszy,drugi,wid,koment)
    {}
    void draw(){}
};

class Composition: public Relacja
{
    Krotnosc Ile;
    int n;
public:
    Composition(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = "",Krotnosc ile = Jeden, int ileTychN = 0):Relacja(pierwszy,drugi,wid,koment),Ile(ile),n(ileTychN)
    {}
    Krotnosc getKrotnosc(){return Ile;}
    void setKrotnosc(Krotnosc krot){Ile = krot;}
    void setIleTychN(int num){n = num;}
    int getIleTychN(){return n;}
    void draw(){}
};

class Aggregation: public Relacja
{
    Krotnosc Ile;
    int n;
public:
    Aggregation(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = "",Krotnosc ile = Jeden, int ileTychN = 0):Relacja(pierwszy,drugi,wid,koment),Ile(ile),n(ileTychN)
    {}
    Krotnosc getKrotnosc(){return Ile;}
    int getIleTychN(){return n;}
    void setKrotnosc(Krotnosc krot){Ile = krot;}
    void setIleTychN(int num){n = num;}
    void draw(){}
};

class Generalization: public Relacja
{
public:
    Generalization(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = ""):Relacja(pierwszy,drugi,wid,koment)
    {}
    void draw(){}
};

class Association: public Relacja
{
    Krotnosc Ile;
    int n;
public:
    Association(Element* pierwszy, Element* drugi, Widocznosc wid= wPrivate, QString koment = "",Krotnosc ile = Jeden, int ileTychN = 0):Relacja(pierwszy,drugi,wid,koment),Ile(ile),n(ileTychN)
    {}
    Krotnosc getKrotnosc(){return Ile;}
    int getIleTychN(){return n;}
    void setKrotnosc(Krotnosc krot){Ile = krot;}
    void setIleTychN(int num){n = num;}
    void draw(){}
};

}

#endif // RELACJA_H
