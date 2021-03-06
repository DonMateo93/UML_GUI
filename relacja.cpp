#include "relacja.h"

using namespace Rel;

Relacja::~Relacja()
{

}

QString Relacja::getKontener()
{
    return kontener;
}

void Relacja::setKontener(QString konte)
{
    kontener = konte;
}

void Relacja::setKomentarz(QString koment)
{
    komentarz = koment;
}

bool Relacja::czyZgadzaSieAdresZElementemDrugim(Element* element)
{
    if(element == Drugi)
    {
        return true;
    }else
    {
        return false;
    }
}

bool Relacja::czyZgadzaSieAdresZElementemPierwszym(Element* element)
{
    if(element == Pierwszy)
    {
        return true;
    }else
    {
        return false;
    }
}

bool Relacja::czyPierwszyToPrzestrzen()
{
    if(dynamic_cast<PrzestrzenNazw*>(Pierwszy))
    {
        return true;
    }else
    {
        return false;
    }
}

bool Relacja::czyPierwszyToKlasa()
{
    if(dynamic_cast<Klasa*>(Pierwszy))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Relacja::czyDrugiToKlasa()
{
    if(dynamic_cast<Klasa*>(Drugi))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Relacja::czyPierwszyToStruktura()
{
    if(dynamic_cast<Struktura*>(Drugi))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Relacja::czyDrugiToStruktura()
{
    if(dynamic_cast<Struktura*>(Drugi))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Relacja::setWidocznosc(Widocznosc wid)
{
    widocznosc = wid;
}
