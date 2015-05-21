#include "element.h"

Element::~Element()
{

}

int Element::IleElementow = 0;

QString&
operator<<(QString& wyjscie, const ParametrOperacji parOp)
{
    wyjscie = "";

    wyjscie = parOp.Nazwa + " : ";

    if(parOp.CzyConst)
        wyjscie = wyjscie + "const ";

    wyjscie = wyjscie + parOp.Typ;

    if(parOp.CzyDomyslnaWartosc)
        wyjscie = wyjscie + "=" + parOp.DomyslnaWartosc;

    switch (parOp.Przekazanie)
    {
        case przezReferencje:
            wyjscie = wyjscie + "&";
            break;
        case przezWskaznik:
            wyjscie = wyjscie + "*";
            break;
    }

    return wyjscie;
}

void Element::zmienNazwe(QString NowaNazwa)
{
    NazwaElementu = NowaNazwa;
}

QString Element::getNazwa()
{
    return NazwaElementu;
}

QVector<Atrybut> Element::getListaAtrybutow()
{
    return WektorAtrybutow;
}

void Element::setNazwa(QString nazwa)
{
    NazwaElementu = nazwa;
}

QString&
operator<<(QString& napis, Operacja Op)
{
    napis = "";
    QString pomoc = "", pomoc2,tmp;

    switch(Op.Visibility)
    {
    case wPrivate:
        pomoc2 = "- ";
        break;
    case wPublic:
        pomoc2 = "+ ";
        break;
    case wProtected:
        pomoc2 = "# ";
        break;
    case wPackage:
        pomoc2 = "~ ";
        break;
    case ND:
        pomoc2 = "";
        break;
    }

    for(int i = 0; i < Op.ListaParamMetod.size(); i++)
    {
        tmp<<Op.ListaParamMetod[i];
        if(tmp[0] == '#' || tmp[0] == '~' || tmp[0] == '-' || tmp[0] == '+' || tmp[0] == '^' )
            tmp.remove(0,2);
        pomoc = pomoc + tmp;
        if(i<Op.ListaParamMetod.size() - 1)
        {
            pomoc = pomoc + " , ";
        }
    }

    napis = pomoc2 + Op.Nazwa + " ( " + pomoc + " ) : ";


    switch (Op.Ile)
    {
    case Jeden:
        pomoc2 = "";
        break;
    case JedenLubX:
        pomoc2 = " 1..*";
        break;
    case ZeroLub1:
        pomoc2 = " 0..1";
        break;
    case ZeroLubX:
        pomoc2 = " 0..*";
        break;
    case N:
        pomoc2 = " " + QString::number(Op.n);
        break;
    case WiecejNizN:
        pomoc2 = " " + QString::number(Op.n) + "..*";
        break;
    }

    napis = napis + Op.Typ;

    switch (Op.Przekaz)
    {
        case przezReferencje:
            napis = napis + "&";
            break;
        case przezWskaznik:
            napis = napis + "*";
            break;
    }

    napis = napis + pomoc2;

    if(Op.Komentarz != "")
        napis = napis + " { " + Op.Komentarz + " } ";

    return napis;
}

KontenerOperacji::~KontenerOperacji()
{
    for(int i = 0; i < WektorOperacji.size(); i++)
    {
        delete WektorOperacji[i];
    }

    WektorOperacji.clear();
}


QString&
operator<<(QString& napis, Atrybut atrybut)
{
    if(!atrybut.doEnum)
    {
    napis = "";
    QString pomoc2;
    switch (atrybut.Visibility)
    {
    case wPrivate:
        napis = "-";
        break;
    case wPublic:
        napis = "+";
        break;
    case wProtected:
        napis = "#";
        break;
    case wPackage:
        napis = "~";
        break;
    case ND:
        napis = "";
        break;
    }

    if(napis != "")
        napis = napis +" " + atrybut.Nazwa + " : " + atrybut.Typ;
    else
        napis = napis + atrybut.Nazwa + " : " + atrybut.Typ;


    switch (atrybut.Ile)
    {
    case Jeden:
        pomoc2 = "";
        break;
    case JedenLubX:
        pomoc2 = " 1..*";
        break;
    case ZeroLub1:
        pomoc2 = " 0..1";
        break;
    case ZeroLubX:
        pomoc2 = " 0..*";
        break;
    case N:
        pomoc2 = " " + QString::number(atrybut.n);
        break;
    case WiecejNizN:
        pomoc2 = " " + QString::number(atrybut.n) + "..*";
        break;
    }

    napis = napis + pomoc2;

    if(atrybut.DomyslnaWartosc != "")
        napis = napis + " = " + atrybut.DomyslnaWartosc;

    if(atrybut.Komentarz != "")
        napis = napis + " { " + atrybut.Komentarz + " }";
    }else
    {
        napis = atrybut.Nazwa;
        if(atrybut.DomyslnaWartosc != "")
            napis += "=" + atrybut.DomyslnaWartosc;
    }

    return napis;
}

void Operacja::aktualizujKomentarz()
{
    Komentarz = "";
    if(CzyConst || CzyStatyczna)
    {
        if(CzyWirtualna)
            Komentarz = Komentarz + "virtual";

        if(CzyStatyczna)
        {
            if(Komentarz != "")
                Komentarz = Komentarz + ",static";
            else
                Komentarz = Komentarz + "static";
        }

        if(CzyConst)
        {
            if(Komentarz != "")
                Komentarz = Komentarz + ",const";
            else
                Komentarz = Komentarz + "const";
        }
    }
}

QString Atrybut::getDomyslnaWartosc()
{
    return DomyslnaWartosc;
}

bool Atrybut::getDoEnum()
{
    return doEnum;
}

void Atrybut::setDomyslnaWartosc(QString domyslna)
{
    DomyslnaWartosc = domyslna;
}

void Atrybut::setDoEnum(bool doNiego)
{
    doEnum = doNiego;
}

void Atrybut::aktualizujKomentarz()
{
    Komentarz = "";
    if(CzyConst || CzyStatyczna)
    {
        if(CzyStatyczna)
            Komentarz = Komentarz + "static";

        if(CzyConst)
        {
            if(Komentarz != "")
                Komentarz = Komentarz + ",const";
            else
                Komentarz = Komentarz + "const";
        }
    }

}


QList<Atrybut> Operacja::getListaParametrow()
{
    return ListaParamMetod;
}

PrzekazanieParametru Operacja::getTypPrzekazaniaParametru()
{
    return Przekaz;
}

bool Operacja::getCzyWirtualna()
{
    return CzyWirtualna;
}

void Operacja::setPrzekazanieParametru(PrzekazanieParametru przekaz)
{
    Przekaz = przekaz;
}

void Operacja::setCzyWirtualna(bool czyTak)
{
    CzyWirtualna = czyTak;
}

void Operacja::usunParametrAt(int gdzie)
{
    ListaParamMetod.removeAt(gdzie);
}

int Operacja::dodajParametr(Atrybut Parametr)
{
    ListaParamMetod.push_back(Parametr);
    return int(1);
}

void Operacja::replaceAtrybutAt(Atrybut atrybut, int at)
{
    if(ListaParamMetod.size()-1<at)
    {
        return;
    }else
    {
        ListaParamMetod.replace(at,atrybut);
    }
}

bool Operacja::getAtrybutAt(Atrybut &atrybut,int at)
{
    if(ListaParamMetod.size()-1 < at)
    {
        return false;
    }else
    {
        atrybut = ListaParamMetod.at(at);
        return true;
    }
}

QString Element::getWszystkieAtrybuty()
{
    QString WszystkieAtrybuty = "";
    QString pom = "";

    for(int i = 0; i < WektorAtrybutow.size(); i++)
    {
        pom << WektorAtrybutow[i];
        WszystkieAtrybuty += pom;

        if(i < WektorAtrybutow.size() - 1)
            WszystkieAtrybuty += "\n";
    }

    return WszystkieAtrybuty;

}

void ElementZOperacjami::dodajOperacje(const Operacja& operacja)
{   //TU I W PODOBNYCH DODAĆ SPRAWDZANIE CZY SIĘ NIE POWTARZA
    WektorOperacji.push_back(operacja);
}

QVector<Operacja> ElementZOperacjami::getListaOperacji()
{
    return WektorOperacji;
}

void ElementZOperacjami::usunOperacjaAt(int pos)
{
    WektorOperacji.remove(pos);
}

QString ElementZOperacjami::getWszystkieOperacje()
{
    QString WszystkieOperacje = "";
    QString pom;
    for(int i = 0; i < WektorOperacji.size(); i++)
    {
        pom << WektorOperacji[i];
        WszystkieOperacje += pom;

        if(i < WektorOperacji.size() - 1)
            WszystkieOperacje += "\n";
    }

    return WszystkieOperacje;
}

void Element::dodajAtrybut(Atrybut atrybut)
{
    if(!czyJestAtrybutONazwie(atrybut))
    {
        WektorAtrybutow.push_back(atrybut);
    }else
    {
        //OBSŁUGA BŁĘDÓW
    }
}

void Element::usunAtrybutAt(int pos)
{
    WektorAtrybutow.remove(pos);
}

QString SkladowaElementu::getNazwa()
{
    return Nazwa;
}

QString SkladowaElementu::getTyp()
{
    return Typ;
}

QString SkladowaElementu::getKomentarz()
{
    return Komentarz;
}

QString SkladowaElementu::getKontener()
{
    return Kontener;
}

bool SkladowaElementu::getCzyStatyczna()
{
    return CzyStatyczna;
}

bool SkladowaElementu::getCzyConst()
{
    return CzyConst;
}

Krotnosc SkladowaElementu::getKrotnosc()
{
    return Ile;
}

int SkladowaElementu::getN()
{
    return n;
}

void SkladowaElementu::setNazwa(QString name)
{
    Nazwa = name;
}

void SkladowaElementu::setTyp(QString type)
{
    Typ = type;
}

void SkladowaElementu::setKontener(QString kont)
{
    Kontener = kont;
}

void SkladowaElementu::setKomentarz(QString kom)
{
    Komentarz = kom;
}

void SkladowaElementu::setCzyStatyczna(bool czyTak)
{
    CzyStatyczna = czyTak;
}

void SkladowaElementu::setCzyConst(bool czyTak)
{
    CzyConst = czyTak;
}

void SkladowaElementu::setKrotnosc(Krotnosc ilezTego)
{
    Ile = ilezTego;
}

void SkladowaElementu::setN(int ileN)
{
    n = ileN;
}

void SkladowaElementu::setSpecyfikatorDostepu(Widocznosc specDost)
{
    Visibility = specDost;
}

bool Element::czyJestAtrybutONazwie(Atrybut atrybut)
{
    bool ok = false;

    for(int i = 0; i < WektorAtrybutow.size(); i ++)
    {
        if(WektorAtrybutow[i].getNazwa() == atrybut.getNazwa())
        {
            ok = true;
            break;
        }
    }

    return ok;
}

bool Element::czyJestAtrybutONazwie(const QString& nazwa)
{
    bool ok = false;

    for(int i = 0; i < WektorAtrybutow.size(); i ++)
    {
        if(nazwa == WektorAtrybutow[i].getNazwa())
        {
            ok = true;
            break;
        }
    }

    return ok;
}

PrzekazanieParametru Operacja::przezCoPrzekazujesz()
{
    return Przekaz;
}

QString Element::getAtrybutyOSpecyfikatorzeDostepu(Widocznosc SpecyfikatorDostepu)
{
    QString Atrybuty = "";
    QString pom = "";

    for(int i = 0; i < WektorAtrybutow.size(); i++)
    {
        if(WektorAtrybutow[i].getSpecyfikatorDostepu() == SpecyfikatorDostepu)
        {
            pom << WektorAtrybutow[i];
            Atrybuty += pom;
            Atrybuty += "\n";
        }
    }

    if(Atrybuty != "")
        Atrybuty.chop(1);

    return Atrybuty;
}

QString ElementZOperacjami::getOperacjeOSpecyfikatorzeDostepu(Widocznosc SpecyfikatorDostepu)
{
    QString Operacje = "";
    QString pom = "";

    for(int i = 0; i < WektorOperacji.size(); i++)
    {
        if(WektorOperacji[i].getSpecyfikatorDostepu() == SpecyfikatorDostepu)
        {
            pom << WektorOperacji[i];
            Operacje += pom;
            Operacje += "\n";
        }
    }

    if(Operacje != "")
        Operacje.chop(1);

    return Operacje;
}

Widocznosc SkladowaElementu::getSpecyfikatorDostepu()
{
    return Visibility;
}


bool Klasa::getCzyAbstrakcyjna()
{
    return CzyAbstrakcyjna;
}

void Klasa::setCzyAbstrakcyjna(bool czyAbstrakcyjna)
{
    CzyAbstrakcyjna = czyAbstrakcyjna;
}
