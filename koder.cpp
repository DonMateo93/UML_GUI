#include "koder.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QString>

using namespace Rel;

QString KoderCpp::dekodujAtrybut(const Atrybut& atrybut)
{
    // atrybut = + Nazwa : Typ licznosc = 0 {virtual, const etc.}
    QString zakodowany;
    zakodowany << atrybut;
    QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
    QString zdekodowany = "";
    QString str;
    QString kontener;

    if("" != atrybut.getKontener()){
        kontener = atrybut.getKontener();
    }else {
        kontener = RodzajStosowanegoKontenera;
    }
    bool ok = false;
    bool ok2 = false;

    if(zakodowany != "")
    {
        //DO WYWALENIA
        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.indexOf("{");

        if(list[ind1+1] != "}" && ind1 != -1)
        {
            QStringList list2 = list[ind1+1].split(",");
            for(int i = 0; i < list2.size(); i++ )
            {
                zdekodowany = zdekodowany + list2[i] + " ";
            }
        }

        ind1 = list.indexOf(":");

        if(ind1 + 2 < list.size())
        {

            if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
            {
                ok = true;
                if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                    ok2 = true;
            }

            if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
            {
                if(list[ind1+2] == "1..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.indexOf(":")+1] + "> ";
                else if(list[ind1+2] == "0..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.indexOf(":")+1] + "> ";
                else if(ok2)
                {
                    zdekodowany = zdekodowany + list[list.indexOf(":")+1] + "[" + list[ind1+2] + "] ";
                }
            }else
            {
                zdekodowany = zdekodowany + list[list.indexOf(":")+1];
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.indexOf(":")+1];
        }

        if(zdekodowany[zdekodowany.size()-2] == ' ')
            zdekodowany = zdekodowany + list[list.indexOf(":")-1];
        else
            zdekodowany = zdekodowany + " " + list[list.indexOf(":")-1];

        if(list.contains("="))
        {
            zdekodowany = zdekodowany + " = " + list[list.indexOf("=") + 1] + " ";
        }

        zdekodowany = zdekodowany + ";";
    }else
    {
        //ZASTANOWIĆ SIĘ CZY NIE DODAĆ OBSŁUGI BŁĘDÓW
        zdekodowany = "";
    }

    return zdekodowany;
}

void KoderCpp::generujKodDoPliku(QString path = "")
{

}

QString KoderCpp::dekodujOperacje(const Operacja& operacja, QString przedrostekDoCpp)
{
    QString zakodowany;
    QString zdekodowany = "";
    zakodowany << operacja;

    QString kontener;
    if(operacja.getKontener() != ""){
        kontener = operacja.getKontener();
    }else {
        kontener = RodzajStosowanegoKontenera;
    }

    if(zakodowany != "")
    {
        QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
        QString str;
        bool ok = false;
        bool ok2 = false;

        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.lastIndexOf("{");

        if(ind1 != -1)
        {
            if(list[ind1+1] != "}")
            {
                QStringList list2 = list[ind1+1].split(",",QString::SkipEmptyParts);
                for(int i = 0; i < list2.size(); i++ )
                {
                    zdekodowany = zdekodowany + list2[i] + " ";
                }
            }
        }

        ind1 = list.lastIndexOf(":");

        //SPRAWDZANIE MULTIPLICITY
        if(ind1+2<list.size())
        {
            if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
            {
                ok = true;
                if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                    ok2 = true;
            }

            if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
            {
                QString pomoCh = list[list.lastIndexOf(":")+1][list[list.lastIndexOf(":")+1].size() - 1]; //Ostatni znak w stringu przechowującym typ(może to być * lub &)
                if(pomoCh == "*" || pomoCh == "&")
                {
                    list[list.lastIndexOf(":")+1].chop(1);
                }
                else
                    pomoCh = "";
                if(list[ind1+2] == "1..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
                else if(list[ind1+2] == "0..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
                else if(ok2)
                {
                    zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + "[" + list[ind1+2] + "] ";
                }
            }else
            {
                zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
        }

        if(list[0] == "#" || list[0] == "~" || list[0] == "+" || list[0] == "-" )
        {
            zdekodowany =zdekodowany + przedrostekDoCpp + list[1] ;
        }
        else
        {
            zdekodowany = zdekodowany + przedrostekDoCpp + list[0];
        }
        ind1 = list.indexOf("(");
        int ind2 = list.indexOf(")");

        QStringList list2;
        list2.clear();

        for(int j = 0; j < (ind2 - ind1) - 1; j++)
        {
            list2.push_back(list[ind1 + j + 1]);
        }

        zdekodowany = zdekodowany + "(";

        str = "";
        str = list2.join(" ");
        list2.clear();
        list2 = str.split(" , ",QString::SkipEmptyParts);

        str = "";
        QString pom = "";

        for(int k = 0; k < list2.size(); k++)
        {
            pom = list2[k];
            str = dekodujAtrybut(pom);
            str.chop(1);
            zdekodowany = zdekodowany + str;
            if(k<list2.size() - 1)
                zdekodowany = zdekodowany + ", ";
        }

        zdekodowany = zdekodowany  + ")";
    }

    return zdekodowany;
}

QString KoderCpp::dekodujOperacje(const QString& operacja, QString przedrostekDoCpp)
{
    QString zakodowany = "";
    QString zdekodowany = "";

    QString kontener;
    if(operacja.getKontener() != ""){
        kontener = operacja.getKontener();
    }else {
        kontener = RodzajStosowanegoKontenera;
    }

    if(operacja != "")
    {
        zakodowany = operacja;
        QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
        QString str;
        bool ok = false;
        bool ok2 = false;

        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.lastIndexOf("{");
        if(ind1 != -1)
        {
            if(list[ind1+1] != "}")
            {
                QStringList list2 = list[ind1+1].split(",",QString::SkipEmptyParts);
                for(int i = 0; i < list2.size(); i++ )
                {
                    zdekodowany = zdekodowany + list2[i] + " ";
                }
            }
        }

        ind1 = list.lastIndexOf(":");

        //SPRAWDZANIE MULTIPLICITY
        if(ind1+2<list.size())
        {
            if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
            {
                ok = true;
                if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                    ok2 = true;
            }

            if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
            {
                QString pomoCh = list[list.lastIndexOf(":")+1][list[list.lastIndexOf(":")+1].size() - 1]; //Ostatni znak w stringu przechowującym typ(może to być * lub &)
                if(pomoCh == "*" || pomoCh == "&")
                {
                    list[list.lastIndexOf(":")+1].chop(1);
                }
                else
                    pomoCh = "";
                if(list[ind1+2] == "1..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
                else if(list[ind1+2] == "0..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.lastIndexOf(":")+1] + ">" + pomoCh + " ";
                else if(ok2)
                {
                    zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + "[" + list[ind1+2] + "] ";
                }
            }else
            {
                zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.lastIndexOf(":")+1] + " ";
        }

        if(list[0] == "#" || list[0] == "~" || list[0] == "+" || list[0] == "-" )
            zdekodowany =zdekodowany + przedrostekDoCpp + list[1];
        else
            zdekodowany =zdekodowany + przedrostekDoCpp + list[0];

        ind1 = list.indexOf("(");
        int ind2 = list.indexOf(")");

        QStringList list2;
        list2.clear();

        for(int j = 0; j < (ind2 - ind1) - 1; j++)
        {
            list2.push_back(list[ind1 + j + 1]);
        }

        zdekodowany = zdekodowany + "(";

        str = "";
        str = list2.join(" ");
        list2.clear();
        list2 = str.split(" , ",QString::SkipEmptyParts);

        str = "";
        QString pom = "";

        for(int k = 0; k < list2.size(); k++)
        {
            pom = list2[k];
            str = dekodujAtrybut(pom);
            str.chop(1);
            zdekodowany = zdekodowany + str;
            if(k<list2.size() - 1)
                zdekodowany = zdekodowany + ", ";
        }

        zdekodowany = zdekodowany  + ")";
    }

    return zdekodowany;
}


QString KoderCpp::dekodujAtrybut(const QString& atrybut)
{
    // atrybut = + Nazwa : Typ licznosc = 0 {virtual, const etc.}
    QString zakodowany;
    zakodowany = atrybut;
    QStringList list = zakodowany.split(" ", QString::SkipEmptyParts);
    QString zdekodowany = "";
    QString str;
    bool ok = false;
    bool ok2 = false;

    QString kontener;
    if(atrybut.getKontener() != ""){
        kontener = atrybut.getKontener();
    }else {
        kontener = RodzajStosowanegoKontenera;
    }

    if(zakodowany != "")
    {
        //DO WYWALENIA
        for(int i = 0; i < list.size(); i++ )
        {
            str = str + "\n" + list[i];
        }



        int ind1 = list.indexOf("{");

        if(list[ind1+1] != "}" && ind1 != -1)
        {
            QStringList list2 = list[ind1+1].split(",");
            for(int i = 0; i < list2.size(); i++ )
            {
                zdekodowany = zdekodowany + list2[i] + " ";
            }
        }

        ind1 = list.indexOf(":");

        if(ind1 + 2 < list.size())
        {

            if(list[ind1+2].contains('0') || list[ind1+2].contains('1')|| list[ind1+2].contains('2')|| list[ind1+2].contains('3')|| list[ind1+2].contains('4')|| list[ind1+2].contains('5')|| list[ind1+2].contains('6')|| list[ind1+2].contains('7')|| list[ind1+2].contains('8')|| list[ind1+2].contains('9'))
            {
                ok = true;
                if( ! ( list[ind1+2].contains('.') || list[ind1+2].contains('.') ) )
                    ok2 = true;
            }

            if(list[ind1+2] == "1..*" || list[ind1+2] == "0..1" || list[ind1+2] == "0..*" || ok)
            {
                if(list[ind1+2] == "1..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.indexOf(":")+1] + "> ";
                else if(list[ind1+2] == "0..*")
                    zdekodowany = zdekodowany + kontener + "<" + list[list.indexOf(":")+1] + "> ";
                else if(ok2)
                {
                    zdekodowany = zdekodowany + list[list.indexOf(":")+1] + "[" + list[ind1+2] + "] ";
                }
            }else
            {
                zdekodowany = zdekodowany + list[list.indexOf(":")+1];
            }
        }else
        {
            zdekodowany = zdekodowany + list[list.indexOf(":")+1];
        }

        if(zdekodowany[zdekodowany.size()-2] == ' ')
            zdekodowany = zdekodowany + list[list.indexOf(":")-1];
        else
            zdekodowany = zdekodowany + " " + list[list.indexOf(":")-1];

        if(list.contains("="))
        {
            zdekodowany = zdekodowany + " = " + list[list.indexOf("=") + 1] + " ";
        }

        zdekodowany = zdekodowany + ";";
    }else
    {
        //ZASTANOWIĆ SIĘ CZY NIE DODAĆ OBSŁUGI BŁĘDÓW
        zdekodowany = "";
    }

    return zdekodowany;
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, PrzestrzenNazw* Przestrzen, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    FilePathAndName.chop(2);
    FilePathAndName += ".cpp";
    QFile PlikZrodlo(FilePathAndName);

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);
            QTextStream stream2(&PlikZrodlo);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(Przestrzen);
            stream << wszystko;

            QString przedrostek = Przestrzen->getNazwa() + "::";
            QString wszystkoCpp = przygotujBlokTekstuDoCpp(Przestrzen, przedrostek);
            stream2 << wszystkoCpp;



            Plik.close();
            PlikZrodlo.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(Przestrzen);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);
                QTextStream stream2(&PlikZrodlo);

                QString buffor = in.readAll();
                out << buffor;

                QString przedrostek = DoJakiej->getNazwa() + "::" + Przestrzen->getNazwa() + "::";
                QString wszystkoCpp = przygotujBlokTekstuDoCpp(Przestrzen, przedrostek);
                stream2 << wszystkoCpp;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();
                PlikZrodlo.close();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Struktura* struktura, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    FilePathAndName.chop(2);
    FilePathAndName += ".cpp";
    QFile PlikZrodlo(FilePathAndName);

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);
            QTextStream stream2(&PlikZrodlo);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(struktura);
            stream << wszystko;

            QString przedrostek = struktura->getNazwa() + "::";
            QString wszystkoCpp = przygotujBlokTekstuDoCpp(struktura, przedrostek);
            stream2 << wszystkoCpp;

            Plik.close();
            PlikZrodlo.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(struktura);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);
                QTextStream stream2(&PlikZrodlo);

                QString buffor = in.readAll();
                out << buffor;

                QString przedrostek = DoJakiej->getNazwa() + "::" + struktura->getNazwa() + "::";
                QString wszystkoCpp = przygotujBlokTekstuDoCpp(struktura, przedrostek);
                stream2 << wszystkoCpp;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();
                PlikZrodlo.close();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Wyliczenie* wyliczenie, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(wyliczenie);
            stream << wszystko;

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(wyliczenie);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}

void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Unia* unia, PrzestrzenNazw* DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(unia);
            stream << wszystko;

            Plik.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(unia);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);

                QString buffor = in.readAll();
                out << buffor;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }
}


void KoderCpp::wprowadzElementDoPliku(QString FilePathAndName, Klasa* klasa, PrzestrzenNazw *DoJakiej)
{
    QFile Plik(FilePathAndName);
    QString pom;

    FilePathAndName.chop(2);
    FilePathAndName += ".cpp";
    QFile PlikZrodlo(FilePathAndName);

    if(DoJakiej == NULL) // MOŻNA WPISAC NA KONIEC PLIKU NOWY NAMESPACE
    {
        if(Plik.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
        {
            QTextStream stream(&Plik);
            QTextStream stream2(&PlikZrodlo);

            QString wszystko = przygotujBlokTekstuDoWpisaniaElementu(klasa);
            stream << wszystko;

            QString przedrostek = klasa->getNazwa() + "::";
            QString wszystkoCpp = przygotujBlokTekstuDoCpp(klasa, przedrostek);
            stream2 << wszystkoCpp;

            Plik.close();
            PlikZrodlo.close();

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }else // TRZEBA ZNALEZC W PLIKU NAMESPACE DO KTOREGO TRZEBA WPISAC NOWY
    {
        QFile PlikPom("PlikPomocniczy.txt");
        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString szukacz =  "namespace " + DoJakiej->getNazwa();
            pom = in.readLine();
            bool obserwator = false;

            while(!pom.isNull()) // PRZEPISYWANIE DO POMOCNICZEGO PLIKU
            {
                out << pom + "\n";
                if(pom.contains(szukacz)) //SZUKA GDZIE ZACZYNA SIE NAMESPACE DO KTOREGO TRZEBA WPISAC
                {
                    pom = in.readLine();
                    out << pom + "\n";
                    QString calosc = przygotujBlokTekstuDoWpisaniaElementu(klasa);
                    out << calosc;
                    obserwator = true;
                }

                pom = in.readLine();

            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate) && PlikPom.open(QIODevice::ReadOnly | QIODevice::Text) && PlikZrodlo.open(QIODevice::WriteOnly|QIODevice::Append| QIODevice::Text))
            {
                //PRZEPISANIE WSZYSTKICH DANYCH DO WŁAŚCIWEGO PLIKU
                QTextStream in(&PlikPom);
                QTextStream out(&Plik);
                QTextStream stream2(&PlikZrodlo);

                QString buffor = in.readAll();
                out << buffor;

                QString przedrostek = DoJakiej->getNazwa() + "::" + klasa->getNazwa() + "::";
                QString wszystkoCpp = przygotujBlokTekstuDoCpp(klasa, przedrostek);
                stream2 << wszystkoCpp;

                Plik.close();
                PlikPom.close();
                PlikPom.remove();
                PlikZrodlo.close();

            }else
            {
                //OBSLUGA BLEDU
            }

            if(!obserwator)
            {
                //POINFORMUJ O TYM ŻE NIE MA SZUKANEGO NAMESPACE W PLIKU
            }

        }else
        {
            //DODAC OBSLUGE BLEDU
        }
    }}


QString KoderCpp::dekodujBlokOperacji(const QString& BlokOperacji, QString przedrostekDoCpp)
{
    QString ZdekodowanyBlok = "";

    if(BlokOperacji != "")
    {
        QStringList ListaOperacji = BlokOperacji.split("\n");

        for(int i = 0; i< ListaOperacji.size(); i++)
        {
            ListaOperacji[i] = dekodujOperacje(ListaOperacji[i], przedrostekDoCpp);
        }

        ZdekodowanyBlok = ListaOperacji.join("\n");
        ZdekodowanyBlok += "\n";
    }

    return ZdekodowanyBlok;
}

QString KoderCpp::dekodujBlokAtrybutow(const QString& BlokAtrybutow, bool CzyZPustymiLiniami)
{
    QString ZdekodowanyBlok = "";
    if(BlokAtrybutow != "")
    {
        QStringList ListaAtrybutow = BlokAtrybutow.split("\n");

        for(int i = 0; i< ListaAtrybutow.size(); i++)
        {
            ListaAtrybutow[i] = dekodujAtrybut(ListaAtrybutow[i]);
        }


        if(CzyZPustymiLiniami)
        {
            ZdekodowanyBlok = ListaAtrybutow.join("\n\n");
            ZdekodowanyBlok += "\n\n";
        }
        else
        {
            ZdekodowanyBlok = ListaAtrybutow.join("\n");
            ZdekodowanyBlok += "\n";
        }
    }

    return ZdekodowanyBlok;
}

void KoderCpp::poprawKodWPliku(const QString &PathAndName)
{
    //UNIEMOŻLIWIĆ WPISANIE PLIK POMOCNICZY W FILE DIALOG
    QFile Plik(PathAndName);
    QFile PlikPom("PlikPomocniczy.txt");
    int ileNawiasow = 0;
    bool ok = true;
    bool pomocB = false;


    if(Plik.open(QIODevice::ReadOnly|QIODevice::Text) && PlikPom.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
    {
        if(Plik.size() != 0)
        {
            QTextStream in(&Plik);
            QTextStream out(&PlikPom);
            QString linia;
            QString pomoc = "";

            linia = in.readLine();
            while(!linia.isNull())
            {
                linia.remove('\t');
                if(linia.contains("{"))
                {
                    pomoc = "";

                    for(int i = 0; i < ileNawiasow; i++)
                    {
                        pomoc += "\t";
                    }

                    linia = pomoc + linia + "\n\n";
                    ileNawiasow++;
                    pomocB = false;
                }else if(linia.contains("}"))
                {
                    ileNawiasow--;

                    pomoc = "";

                    for(int i = 0; i < ileNawiasow; i++)
                    {
                        pomoc += "\t";
                    }
                    linia = pomoc + linia + "\n\n";
                    pomocB = false;
                }else if(linia == "")
                {

                }
                else if(linia.contains("private") || linia.contains("public") || linia.contains("protected"))
                {
                    if(pomocB)
                        linia = "\n" + linia;

                    pomoc = "";
                    for(int i = 0; i < ileNawiasow -1; i ++)
                        pomoc += "\t";

                    linia += "\n";
                    linia = pomoc + linia;
                    pomocB = false;
                }
                else
                {
                    pomoc = "";

                    for(int i = 0; i < ileNawiasow; i++)
                    {
                        pomoc += "\t";
                    }

                    if(pomocB)
                        linia = "\n" + pomoc + linia + "\n";
                    else
                        linia = pomoc + linia + "\n";

                    pomocB = true;
                }

                out << linia;
                linia = in.readLine();
            }

            Plik.close();
            PlikPom.close();

            if(Plik.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate)| PlikPom.open(QIODevice::ReadOnly|QIODevice::Text))
            {
                QTextStream in2(&PlikPom);
                QTextStream out2(&Plik);

                if(PlikPom.size() != 0)
                {
                    linia = in2.readLine();
                    while(!linia.isNull())
                    {
                        out2 << linia+ "\n";
                        linia = in2.readLine();
                    }

                    Plik.close();
                    PlikPom.close();
                    PlikPom.remove();

                }else
                    ok = false;

            }else
                ok = false;
        }else
            ok = false;
    }else
        ok = false;

    if(!ok)
    {
        //OBSŁUGA BŁĘDÓW
    }
}

// Zawiera wszystkie dane odnosnie elemetnu w jednym stringu gotowym do wpisania do pliku
QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(PrzestrzenNazw* Przestrzen)
{
    QString zwracana = "";
    if(Przestrzen != NULL)
    {
        QString pom = "";
        zwracana += "namespace " + Przestrzen->getNazwa() + "\n{\n" ;


        pom = Przestrzen->getWszystkieAtrybuty();
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;


        pom = Przestrzen->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n"); //USUNIĘTO \n{\n\n}
        }

        zwracana += "\n}\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Klasa* klasa)
{
    QString zwracana = "";

    if(klasa != NULL)
    {
        QString pom = "";
        QString pom2 = "";

        zwracana += "class " + klasa->getNazwa() + "\n{\n" ;
        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //----------------------------------------------------------------------------

        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wProtected);
        pom = dekodujBlokAtrybutow(pom,true);

        pom2 = klasa->getOperacjeOSpecyfikatorzeDostepu(wProtected);
        pom2 = dekodujBlokOperacji(pom2);

        if(pom != "" || pom2 != "")
            zwracana += "\nprotected:\n";

        zwracana += pom;

        ListaPom.clear();
        ListaPom = pom2.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //----------------------------------------------------------------------------
//        zwracana += "\nprotected:\n";
//        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wProtected);
//        pom = dekodujBlokAtrybutow(pom,true);
//        zwracana += pom;

//        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wProtected);
//        pom = dekodujBlokOperacji(pom);
//        ListaPom.clear();
//        ListaPom = pom.split("\n", QString::SkipEmptyParts);

//        for(int i = 0; i < ListaPom.size(); i++)
//        {
//            zwracana += (ListaPom[i] + "\n{\n\n}\n");
//        }
        //----------------------------------------------------------------------------

        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokAtrybutow(pom,true);

        pom2 = klasa->getOperacjeOSpecyfikatorzeDostepu(wPublic);
        pom2 = dekodujBlokOperacji(pom2);

        if(pom != "" || pom2 != "")
            zwracana += "\npublic:\n";

        zwracana += pom;

        ListaPom.clear();
        ListaPom = pom2.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

       //----------------------------------------------------------------------------
//        zwracana += "\npublic:\n";
//        pom = klasa->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
//        pom = dekodujBlokAtrybutow(pom,true);
//        zwracana += pom;

//        pom = klasa->getOperacjeOSpecyfikatorzeDostepu(wPublic);
//        pom = dekodujBlokOperacji(pom);
//        ListaPom.clear();
//        ListaPom = pom.split("\n", QString::SkipEmptyParts);

//        for(int i = 0; i < ListaPom.size(); i++)
//        {
//            zwracana += (ListaPom[i] + "\n{\n\n}\n");
//        }

       //----------------------------------------------------------------------------

        zwracana += "\n};\n";


    }else
    {
        //ZGłOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Struktura* struktura)
{
    QString zwracana = "";

    if(struktura != NULL)
    {
        QString pom = "";
        QString pom2 = "";

        zwracana += "struct " + struktura->getNazwa() + "\n{\n" ;
        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        pom = struktura->getOperacjeOSpecyfikatorzeDostepu(wPublic);
        pom = dekodujBlokOperacji(pom);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //--------------------------------------------
        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
        pom = dekodujBlokAtrybutow(pom,true);

        pom2 = struktura->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
        pom2 = dekodujBlokOperacji(pom2);

        if(pom != "" || pom2 != "")
            zwracana += "\nprivate:\n";

        zwracana += pom;


        ListaPom.clear();
        ListaPom = pom2.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + ";\n");
        }

        //--------------------------------------------
//        zwracana += "\nPrivate:\n";
//        pom = struktura->getAtrybutyOSpecyfikatorzeDostepu(wPrivate);
//        pom = dekodujBlokAtrybutow(pom,true);
//        zwracana += pom;

//        pom = struktura->getOperacjeOSpecyfikatorzeDostepu(wPrivate);
//        pom = dekodujBlokOperacji(pom);
//        ListaPom.clear();
//        ListaPom = pom.split("\n", QString::SkipEmptyParts);

//        for(int i = 0; i < ListaPom.size(); i++)
//        {
//            zwracana += (ListaPom[i] + "\n{\n\n}\n");
//        }
        //--------------------------------------------

        zwracana += "\n};\n";


    }else
    {
        //ZGłOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Unia* unia)
{
    QString zwracana = "";
    if(unia != NULL)
    {
        QString pom = "";
        zwracana += "union " + unia->getNazwa() + "\n{\n" ;


        pom = unia->getWszystkieAtrybuty();
        pom = dekodujBlokAtrybutow(pom,true);
        zwracana += pom;

        zwracana += "\n};\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoWpisaniaElementu(Wyliczenie* wyliczenie)
{
    QString zwracana = "";
    if(wyliczenie != NULL)
    {
        QString pom = "";
        zwracana += "enum " + wyliczenie->getNazwa() + "\n{\n" ;


        pom = wyliczenie->getWszystkieAtrybuty();
        pom = dekodujBlokAtrybutow(pom,true);
        QStringList lista = pom.split("\n",QString::SkipEmptyParts);
        pom = lista.join(",\n");

        zwracana += pom;

        zwracana += "\n};\n";


    }else
    {
        //ZGŁOŚ BŁĄD
    }
    return zwracana;
}

void KoderCpp::wprowadzDoPlikuWszystkieElementy(QString FilePathAndName)
{
    //FUNKCJA JEST NIE SKOŃCZONA, NALEŻY DODAĆ PRZESZUKIWANIE RELACJI W CELU ZNALEZIENIA
    //KOINCYDENCJI Z JAKIMIŚ PRZESTRZENIAMI NAZW

    //Przeszukiwanie przestrzeni nazw nie znajdujących się w innych przestrzeniach nazw
    ileObiektow = 0;
    PrzestrzenNazw* nadrzedna = NULL;
    for(int i = 0; i < ListaElementow.size(); i++)
    {
        PrzestrzenNazw* przestrzen = dynamic_cast<PrzestrzenNazw*>(ListaElementow[i]);
        if(przestrzen)
        {
            if(dajAdresNadrzednejPrzestrzeni(przestrzen) == NULL)
            {
                wprowadzElementDoPliku(FilePathAndName, przestrzen);
            }
        }
    }

    for(int k = 0; k < ListaElementow.size(); k ++)
    {
        PrzestrzenNazw* przestrzen = dynamic_cast<PrzestrzenNazw*>(ListaElementow[k]);

        if(przestrzen)
        {
            nadrzedna = dajAdresNadrzednejPrzestrzeni(przestrzen);

            if(nadrzedna != NULL)
            {
               wprowadzElementDoPliku(FilePathAndName,przestrzen,nadrzedna);
            }
        }
    }

    for(int j = 0; j < ListaElementow.size(); j++)
    {
        if(dynamic_cast<Klasa*>(ListaElementow[j]))
        {
            Klasa* klasa = dynamic_cast<Klasa*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);

        }else if(dynamic_cast<Struktura*>(ListaElementow[j]))
        {
            Struktura* klasa = dynamic_cast<Struktura*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);

        }else if(dynamic_cast<Wyliczenie*>(ListaElementow[j]))
        {
            Wyliczenie* klasa = dynamic_cast<Wyliczenie*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);

        }else if(dynamic_cast<Unia*>(ListaElementow[j]))
        {
            Unia* klasa = dynamic_cast<Unia*>(ListaElementow[j]);
            nadrzedna = dajAdresNadrzednejPrzestrzeni(klasa);
            wprowadzElementDoPliku(FilePathAndName,klasa,nadrzedna);
        }
    }
}

void Koder::dodajElementDoListy(Element* element)
{
    bool ok = true;

    for(int i = 0; i < ListaElementow.size(); i++)
    {
        if(ListaElementow[i]->getNazwa() == element->getNazwa())
        {
            ok = false;
            break;
        }
    }

    if(ok)
    {
        ListaElementow.push_back(element);
    }else
    {
        //OBSŁUGA BŁĘDU
    }

}

void KoderCpp::dodajRelacje(Relacja *relacja)
{
// DODAĆ KONTROLĘ WPROWADZANIA
    ListaRelacji.push_back(relacja);
}


PrzestrzenNazw* KoderCpp::dajAdresNadrzednejPrzestrzeni(Element* element)
{
    PrzestrzenNazw* zwrot = NULL;

    if(element != NULL)
    {
        //BARDZO WAŻNE!!!! SPRAWDZIĆ CZY KONCEPCJA ADRESÓW DZIAŁA
        for(int i = 0; i < ListaRelacji.size(); i++)
        {
            if(dynamic_cast<Aggregation*>(ListaRelacji[i]) || dynamic_cast<Composition*>(ListaRelacji[i]))
            {
                if(ListaRelacji[i]->czyZgadzaSieAdresZElementemDrugim(element))
                {
                    if(ListaRelacji[i]->czyPierwszyToPrzestrzen())
                    {
                        zwrot = dynamic_cast<PrzestrzenNazw*>(ListaRelacji[i]->dajAdresPierwszy());
                        break;
                    }
                }
            }
        }
    }

    return zwrot;
}

QString KoderCpp::przygotujBlokTekstuDoCpp(PrzestrzenNazw* przestrzen, QString przedrostekDoCpp)
{
    QString zwracana = "";
    if(przestrzen != NULL)
    {
        QString pom = "";


        pom = przestrzen->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom, przedrostekDoCpp);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n\n");
        }

    }else
    {
        //ZGŁOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoCpp(Klasa* klasa, QString przedrostekDoCpp)
{
    QString zwracana = "";
    if(klasa != NULL)
    {
        QString pom = "";


        pom = klasa->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom, przedrostekDoCpp);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n\n");
        }

    }else
    {
        //ZGŁOŚ BŁĄD
    }

    return zwracana;
}

QString KoderCpp::przygotujBlokTekstuDoCpp(Struktura* struktura, QString przedrostekDoCpp)
{
    QString zwracana = "";
    if(struktura != NULL)
    {
        QString pom = "";


        pom = struktura->getWszystkieOperacje();
        pom = dekodujBlokOperacji(pom, przedrostekDoCpp);
        QStringList ListaPom = pom.split("\n", QString::SkipEmptyParts);

        for(int i = 0; i < ListaPom.size(); i++)
        {
            zwracana += (ListaPom[i] + "\n{\n\n}\n\n");
        }

    }else
    {
        //ZGŁOŚ BŁĄD
    }

    return zwracana;
}

void KoderCpp::wprowadzDoPlikuWszyskieRelacje(QString FilePathAndName)
{
    for(int i = 0; i < ListaRelacji.size(); i ++)
    {
        if(dynamic_cast<Aggregation*>(ListaRelacji[i]))
        {
            if(!ListaRelacji[i]->czyPierwszyToPrzestrzen())
            {
                wprowadzDoPlikuAgregacjeLubKompozycje(FilePathAndName,ListaRelacji[i]);
            }
        }
        else if(dynamic_cast<Composition*>(ListaRelacji[i]))
        {
            if(!ListaRelacji[i]->czyPierwszyToPrzestrzen())
            {
                wprowadzDoPlikuAgregacjeLubKompozycje(FilePathAndName,ListaRelacji[i]);
            }
        }
        else if(dynamic_cast<Association*>(ListaRelacji[i]))
        {
            if(!(dynamic_cast<PrzestrzenNazw*>(ListaRelacji[i]->dajAdresDrugi())))
            {
                wprowadzDoPlikuAsocjacje(FilePathAndName,ListaRelacji[i]);
            }
        }
        else if(dynamic_cast<Dependency*>(ListaRelacji[i]))
        {
            if((ListaRelacji[i]->czyPierwszyToKlasa() || ListaRelacji[i]->czyPierwszyToStruktura()) && (ListaRelacji[i]->czyDrugiToKlasa() || ListaRelacji[i]->czyDrugiToStruktura()))
            {
                wprowadzDoPlikuDependency(FilePathAndName,ListaRelacji[i]);
            }
        }
        else if(dynamic_cast<Generalization*>(ListaRelacji[i]))
        {
            if(ListaRelacji[i]->czyPierwszyToKlasa() && ListaRelacji[i]->czyDrugiToKlasa())
            {
                wprowadzDoPlikuGeneralizacje(FilePathAndName,ListaRelacji[i]);
            }
        }
    }
}

void KoderCpp::wprowadzDoPlikuAgregacjeLubKompozycje(QString FilePathAndName, Relacja* relacja)
{
    QFile Naglowek(FilePathAndName);
    QFile Pom("PlikPomocniczy.txt");
    QString pomoc1 = "";
    QString szukana = "";
    QString wpisywana = "";

    QString kontener;
    if(relacja->getKontener() != ""){
        kontener = relacja->getKontener();
    }else {
        kontener = RodzajStosowanegoKontenera;
    }

    if((dynamic_cast<Aggregation*>(relacja))->getKrotnosc() == Jeden)
    {
        wpisywana = relacja->dajAdresDrugi()->getNazwa() + " element" + QString::number(ileObiektow++) + ";";
    }
    else if((dynamic_cast<Aggregation*>(relacja))->getKrotnosc() == JedenLubX || (dynamic_cast<Association*>(relacja))->getKrotnosc() == ZeroLub1 || (dynamic_cast<Association*>(relacja))->getKrotnosc() == ZeroLubX)
    {
        wpisywana = kontener + "<" + relacja->dajAdresDrugi()->getNazwa() + ">" + " element" + QString::number(ileObiektow++) + ";";
    }
    else if((dynamic_cast<Aggregation*>(relacja))->getKrotnosc() == N)
    {
        wpisywana = relacja->dajAdresDrugi()->getNazwa() + " element" + QString::number(ileObiektow++) + "[" + QString::number((dynamic_cast<Association*>(relacja))->getIleTychN()) + "]" + ";";
    }

    if(dynamic_cast<Klasa*>(relacja->dajAdresPierwszy()))
    {
        szukana = "class " + relacja->dajAdresPierwszy()->getNazwa();
    }
    else if(dynamic_cast<Struktura*>(relacja->dajAdresPierwszy()))
    {
        szukana = "struct " + relacja->dajAdresPierwszy()->getNazwa();
    }
    else if(dynamic_cast<Unia*>(relacja->dajAdresPierwszy()))
    {
        szukana = "union " + relacja->dajAdresPierwszy()->getNazwa();
    }

    if(szukana != "")
    {
        if(Naglowek.open(QIODevice::Text | QIODevice::ReadOnly) && Pom.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream str1(&Naglowek), str2(&Pom);
            pomoc1 = str1.readLine();
            while(!pomoc1.isNull())
            {
                str2 << pomoc1;
                if(pomoc1.contains(szukana))
                {
                    pomoc1 = str1.readLine();

                    if(pomoc1.contains("{"))
                    {
                        switch(relacja->getWidocznosc()) // Rozdzial na przypadki widocznosci
                        {
                        case wPrivate:
                            if(szukana.contains("class"))
                            {
                                str2 << pomoc1;
                                str2 << wpisywana;
                            }
                            else if(szukana.contains("struct")) // skladowa prywatna nie jest na poczatku klasy
                            {
                                bool ok1 = false;
                                int wagaNawiasy = 0;
                                QStringList lista;
                                lista.clear();
                                do
                                {
                                    lista.push_back(pomoc1);

                                    //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                    if(pomoc1.contains("{"))
                                    {
                                        wagaNawiasy++;
                                    }
                                    else if(pomoc1.contains("}"))
                                    {
                                        wagaNawiasy--;
                                    }

                                    if(pomoc1.contains("private"))
                                    {
                                        lista.push_back(wpisywana);
                                        ok1 = true;
                                        break;
                                    }

                                    pomoc1 = str1.readLine();

                                }while(wagaNawiasy > 0);

                                if(!ok1)
                                {
                                    lista.insert(lista.size() - 1,"private:");
                                    lista.insert(lista.size() - 1, wpisywana);
                                    if(!pomoc1.isNull())
                                    {
                                        lista.push_back(pomoc1);
                                    }

                                }

                                QString sklej = lista.join('\n');
                                str2 << sklej;
                            }
                            break;
                        case wPublic:
                            if(szukana.contains("class"))
                            {
                                bool ok1 = false;
                                int wagaNawiasy = 0;
                                QStringList lista;
                                lista.clear();
                                do
                                {
                                    lista.push_back(pomoc1);

                                    //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                    if(pomoc1.contains("{"))
                                    {
                                        wagaNawiasy++;
                                    }
                                    else if(pomoc1.contains("}"))
                                    {
                                        wagaNawiasy--;
                                    }

                                    if(pomoc1.contains("public"))
                                    {
                                        lista.push_back(wpisywana);
                                        ok1 = true;
                                        break;
                                    }

                                    pomoc1 = str1.readLine();

                                }while(wagaNawiasy > 0);

                                if(!ok1)
                                {
                                    lista.insert(lista.size() - 1,"public:");
                                    lista.insert(lista.size() - 1, wpisywana);
                                    if(!pomoc1.isNull())
                                    {
                                        lista.push_back(pomoc1);
                                    }
                                }

                                QString sklej = lista.join('\n');
                                str2 << sklej;
                            }
                            else if(szukana.contains("struct"))
                            {
                                str2 << pomoc1;
                                str2 << wpisywana;
                            }
                            break;
                        case wProtected:
                            if(szukana.contains("class") || szukana.contains("struct"))
                            {
                                bool ok1 = false;
                                int wagaNawiasy = 0;
                                QStringList lista;
                                lista.clear();
                                do
                                {
                                    lista.push_back(pomoc1);

                                    //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                    if(pomoc1.contains("{"))
                                    {
                                        wagaNawiasy++;
                                    }
                                    else if(pomoc1.contains("}"))
                                    {
                                        wagaNawiasy--;
                                    }

                                    if(pomoc1.contains("protected"))
                                    {
                                        lista.push_back(wpisywana);
                                        ok1 = true;
                                        break;
                                    }

                                    pomoc1 = str1.readLine();

                                }while(wagaNawiasy > 0);

                                if(!ok1)
                                {
                                    lista.insert(lista.size() - 1,"protected:");
                                    lista.insert(lista.size() - 1, wpisywana);
                                    if(!pomoc1.isNull())
                                    {
                                        lista.push_back(pomoc1);
                                    }
                                }

                                QString sklej = lista.join('\n');
                                str2 << sklej;
                            }
                            break;
                        case ND: //Tu siłą rzeczy może być tylko unia
                            if(szukana.contains("union"))
                            {
                                str2 << pomoc1;
                                str2 << wpisywana;
                            }
                            break;
                        }
                    }
                    else
                    {
                        if(!pomoc1.isNull())
                            str2 << pomoc1;
                    }

                }
                pomoc1 = str1.readLine();
            }
        }else
        {
            //OBSŁUGA BŁĘDU
        }

        Naglowek.close();
        Pom.close();

        if(Naglowek.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate) && Pom.open(QIODevice::Text | QIODevice::ReadOnly))
        {
            QTextStream str1(&Naglowek), str2(&Pom);

            pomoc1 = str2.readLine();
            while(!pomoc1.isNull())
            {
                str1 << pomoc1;
                pomoc1 = str2.readLine();
            }

            Pom.close();
            Naglowek.close();
            Pom.remove();
        }
        else
        {
            //OBSŁUGA BŁĘDU = PROBLEM Z PLIKAMI
        }
    }


}


void KoderCpp::wprowadzDoPlikuAsocjacje(QString FilePathAndName, Relacja* relacja)
{
    QString kontener;
    if(relacja->getKontener() != ""){
        kontener = relacja->getKontener();
    }else {
        kontener = RodzajStosowanegoKontenera;
    }
    if(relacja != NULL)
    {
        if(!dynamic_cast<PrzestrzenNazw*>(relacja->dajAdresDrugi()))
        {
            QFile Naglowek(FilePathAndName);
            QFile Pom("PlikPomocniczy.txt");
            QString pomoc1 = "";
            QString szukana = "";
            QString wpisywana = "";

            if((dynamic_cast<Association*>(relacja))->getKrotnosc() == Jeden)
            {
                wpisywana = relacja->dajAdresDrugi()->getNazwa() + "* element" + QString::number(ileObiektow++) + ";";
            }
            else if((dynamic_cast<Association*>(relacja))->getKrotnosc() == JedenLubX || (dynamic_cast<Association*>(relacja))->getKrotnosc() == ZeroLub1 || (dynamic_cast<Association*>(relacja))->getKrotnosc() == ZeroLubX)
            {
                wpisywana = kontener + "<" + relacja->dajAdresDrugi()->getNazwa() + "*>" + " element" + QString::number(ileObiektow++) + ";";
            }
            else if((dynamic_cast<Association*>(relacja))->getKrotnosc() == N)
            {
                wpisywana = relacja->dajAdresDrugi()->getNazwa() + "* element" + QString::number(ileObiektow++) + "[" + QString::number((dynamic_cast<Association*>(relacja))->getIleTychN()) + "]" + ";";
            }

            if(dynamic_cast<Klasa*>(relacja->dajAdresPierwszy()))
            {
                szukana = "class " + relacja->dajAdresPierwszy()->getNazwa();
            }
            else if(dynamic_cast<Struktura*>(relacja->dajAdresPierwszy()))
            {
                szukana = "struct " + relacja->dajAdresPierwszy()->getNazwa();
            }
            else if(dynamic_cast<Unia*>(relacja->dajAdresPierwszy()))
            {
                szukana = "union " + relacja->dajAdresPierwszy()->getNazwa();
            }
            else if(dynamic_cast<PrzestrzenNazw*>(relacja->dajAdresPierwszy()))
            {
                szukana = "namespace " + relacja->dajAdresPierwszy()->getNazwa();
            }
            else if(dynamic_cast<Wyliczenie*>(relacja->dajAdresPierwszy()))
            {
                szukana = "enum " + relacja->dajAdresPierwszy()->getNazwa();
            }

            if(szukana != "")
            {
                if(Naglowek.open(QIODevice::Text | QIODevice::ReadOnly) && Pom.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
                {
                    QTextStream str1(&Naglowek), str2(&Pom);
                    pomoc1 = str1.readLine();
                    while(!pomoc1.isNull())
                    {
                        str2 << pomoc1 << endl;
                        if(pomoc1.contains(szukana))
                        {
                            pomoc1 = str1.readLine();

                            if(pomoc1.contains("{"))
                            {
                                if(szukana.contains("class"))
                                {
                                    if(relacja->getWidocznosc() == wPrivate)
                                    {
                                        str2 << pomoc1 << endl;
                                        str2 << wpisywana << endl;
                                    }
                                    else if(relacja->getWidocznosc() == wPublic || relacja->getWidocznosc() == wProtected)
                                    {
                                        QString pomoc2 = "";
                                        if(relacja->getWidocznosc() == wPublic)
                                            pomoc2 = "public";
                                        else
                                            pomoc2 = "protected";

                                        bool ok1 = false;
                                        int wagaNawiasy = 0;
                                        QStringList lista;
                                        lista.clear();
                                        do
                                        {
                                            lista.push_back(pomoc1);

                                            //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                            if(pomoc1.contains("{"))
                                            {
                                                wagaNawiasy++;
                                            }
                                            else if(pomoc1.contains("}"))
                                            {
                                                wagaNawiasy--;
                                            }

                                            if(pomoc1.contains(pomoc2))
                                            {
                                                lista.push_back(wpisywana);
                                                ok1 = true;
                                                break;
                                            }

                                            pomoc1 = str1.readLine();

                                        }while(wagaNawiasy > 0);

                                        if(!ok1)
                                        {
                                            pomoc2 += ":";
                                            lista.insert(lista.size() - 1,pomoc2);
                                            lista.insert(lista.size() - 1, wpisywana);
                                            if(!pomoc1.isNull())
                                            {
                                                lista.push_back(pomoc1);
                                            }
                                        }

                                        QString sklej = lista.join('\n');
                                        str2 << sklej << endl;
                                    }
                                }
                                else if(szukana.contains("struct"))
                                {
                                    if(relacja->getWidocznosc() == wPublic)
                                    {
                                        str2 << pomoc1 << endl;
                                        str2 << wpisywana << endl;
                                    }
                                    else if(relacja->getWidocznosc() == wPrivate || relacja->getWidocznosc() == wProtected)
                                    {
                                        QString pomoc2 = "";
                                        if(relacja->getWidocznosc() == wPublic)
                                            pomoc2 = "private";
                                        else
                                            pomoc2 = "protected";

                                        bool ok1 = false;
                                        int wagaNawiasy = 0;
                                        QStringList lista;
                                        lista.clear();
                                        do
                                        {
                                            lista.push_back(pomoc1);

                                            //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                            if(pomoc1.contains("{"))
                                            {
                                                wagaNawiasy++;
                                            }
                                            else if(pomoc1.contains("}"))
                                            {
                                                wagaNawiasy--;
                                            }

                                            if(pomoc1.contains(pomoc2))
                                            {
                                                lista.push_back(wpisywana);
                                                ok1 = true;
                                                break;
                                            }

                                            pomoc1 = str1.readLine();

                                        }while(wagaNawiasy > 0);

                                        if(!ok1)
                                        {
                                            pomoc2 += ":";
                                            lista.insert(lista.size() - 1,pomoc2);
                                            lista.insert(lista.size() - 1, wpisywana);
                                            if(!pomoc1.isNull())
                                            {
                                                lista.push_back(pomoc1);
                                            }
                                        }

                                        QString sklej = lista.join('\n');
                                        str2 << sklej << endl;
                                    }
                                }  // W poniższych nie ma problemu prywatnosci wiec nie zastanawiając się wpisujemy na początek
                                else if(szukana.contains("enum") || szukana.contains("union") || szukana.contains("namespace"))
                                {
                                    str2 << pomoc1 << endl;
                                    str2 << wpisywana << endl;
                                }
                            }
                            else
                            {
                                if(!pomoc1.isNull())
                                    str2 << pomoc1 << endl;
                            }
                        }
                        pomoc1 = str1.readLine();
                    }
                }
                else
                {
                    //OBSŁUGA BŁĘDU = PROBLEM Z PLIKIEM
                }

                Naglowek.close();
                Pom.close();

                if(Naglowek.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate) && Pom.open(QIODevice::Text | QIODevice::ReadOnly))
                {
                    QTextStream str1(&Naglowek), str2(&Pom);

                    pomoc1 = str2.readLine();
                    while(!pomoc1.isNull())
                    {
                        str1 << pomoc1 << endl;
                        pomoc1 = str2.readLine();
                    }

                    Pom.close();
                    Naglowek.close();
                    Pom.remove();
                }
                else
                {
                    //OBSŁUGA BŁĘDU = PROBLEM Z PLIKAMI
                }
            }
        }
    }
}

void KoderCpp::wprowadzDoPlikuGeneralizacje(QString FilePathAndName, Relacja* relacja)
{
    QFile Zrodlo(FilePathAndName);
    QFile Pom("PlikPomocniczy.txt");

    if(relacja != NULL)
    {
        if(Zrodlo.open(QIODevice::Text | QIODevice::ReadOnly) && Pom.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream str1(&Zrodlo), str2(&Pom);
            QString wstawiana;
            QString bufor1;
            QString szukana = "class " + relacja->dajAdresDrugi()->getNazwa();

            switch(relacja->getWidocznosc())
            {
            case wPublic:
                wstawiana = "public " + relacja->dajAdresPierwszy()->getNazwa();
                break;
            case wPrivate:
                wstawiana = "public " + relacja->dajAdresPierwszy()->getNazwa();
                break;
            case wProtected:
                wstawiana = "public " + relacja->dajAdresPierwszy()->getNazwa();
                break;
            }

            bufor1 = str1.readLine();

            while(!bufor1.isNull())
            {
                if(bufor1.contains(szukana))
                {
                    QString bufor2 = str1.readLine();
                    if(bufor2.contains("{"))
                    {
                        if(bufor1.contains(":"))
                        {
                            bufor1 += "," + wstawiana;
                        }
                        else
                        {
                            bufor1 += ":" + wstawiana;
                        }
                    }

                    str2 << bufor1 << endl;
                    str2 << bufor2 << endl;
                    bufor1 = str1.readLine();
                }

                str2 << bufor1 << endl;
                bufor1 = str1.readLine();
            }

            Zrodlo.close();
            Pom.close();

            if(Zrodlo.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly) && Pom.open(QIODevice::Text | QIODevice::ReadOnly))
            {
                QTextStream str3(&Zrodlo), str4(&Pom);

                bufor1 = str4.readLine();

                while(!bufor1.isNull())
                {
                    str3 << bufor1 << endl;
                    bufor1 = str4.readLine();
                }

                Pom.close();
                Zrodlo.close();
                Pom.remove();
            }

        }
        else
        {
            //OBSLUGA BLEDU = PROBLEM Z PLIKIEM
        }
    }
}

void KoderCpp::wprowadzDoPlikuDependency(QString FilePathAndName, Relacja* relacja)
{
    if(relacja != NULL)
    {
        if(relacja->getKomentarz() == "friend")
        {
            if(!dynamic_cast<PrzestrzenNazw*>(relacja->dajAdresDrugi()) && !dynamic_cast<Wyliczenie*>(relacja->dajAdresDrugi()) && !dynamic_cast<Unia*>(relacja->dajAdresDrugi()))
            {
                QFile Naglowek(FilePathAndName);
                QFile Pom("PlikPomocniczy.txt");
                QString pomoc1 = "";
                QString szukana = "";
                QString wpisywana = "";

                if(dynamic_cast<Klasa*>(relacja->dajAdresDrugi()))
                {
                    wpisywana = "friend class " + relacja->dajAdresDrugi()->getNazwa() + ";";
                }else if(dynamic_cast<Struktura*>(relacja->dajAdresDrugi()))
                {
                    wpisywana = "friend struct " + relacja->dajAdresDrugi()->getNazwa() + ";";
                }
                if(wpisywana != "")
                {
                    if(dynamic_cast<Klasa*>(relacja->dajAdresPierwszy()))
                    {
                        szukana = "class " + relacja->dajAdresPierwszy()->getNazwa();
                    }
                    else if(dynamic_cast<Struktura*>(relacja->dajAdresPierwszy()))
                    {
                        szukana = "struct " + relacja->dajAdresPierwszy()->getNazwa();
                    }
                    else if(dynamic_cast<Unia*>(relacja->dajAdresPierwszy()))
                    {
                        szukana = "union " + relacja->dajAdresPierwszy()->getNazwa();
                    }
                    else if(dynamic_cast<PrzestrzenNazw*>(relacja->dajAdresPierwszy()))
                    {
                        szukana = "namespace " + relacja->dajAdresPierwszy()->getNazwa();
                    }
                    else if(dynamic_cast<Wyliczenie*>(relacja->dajAdresPierwszy()))
                    {
                        szukana = "enum " + relacja->dajAdresPierwszy()->getNazwa();
                    }

                    if(szukana != "")
                    {
                        if(Naglowek.open(QIODevice::Text | QIODevice::ReadOnly) && Pom.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate))
                        {
                            QTextStream str1(&Naglowek), str2(&Pom);
                            pomoc1 = str1.readLine();
                            while(!pomoc1.isNull())
                            {
                                str2 << pomoc1 << endl;
                                if(pomoc1.contains(szukana))
                                {
                                    pomoc1 = str1.readLine();

                                    if(pomoc1.contains("{"))
                                    {
                                        if(szukana.contains("class"))
                                        {
                                            if(relacja->getWidocznosc() == wPrivate)
                                            {
                                                str2 << pomoc1 << endl;
                                                str2 << wpisywana << endl;
                                            }
                                            else if(relacja->getWidocznosc() == wPublic || relacja->getWidocznosc() == wProtected)
                                            {
                                                QString pomoc2 = "";
                                                if(relacja->getWidocznosc() == wPublic)
                                                    pomoc2 = "public";
                                                else
                                                    pomoc2 = "protected";

                                                bool ok1 = false;
                                                int wagaNawiasy = 0;
                                                QStringList lista;
                                                lista.clear();
                                                do
                                                {
                                                    lista.push_back(pomoc1);

                                                    //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                                    if(pomoc1.contains("{"))
                                                    {
                                                        wagaNawiasy++;
                                                    }
                                                    else if(pomoc1.contains("}"))
                                                    {
                                                        wagaNawiasy--;
                                                    }

                                                    if(pomoc1.contains(pomoc2))
                                                    {
                                                        lista.push_back(wpisywana);
                                                        ok1 = true;
                                                        break;
                                                    }

                                                    pomoc1 = str1.readLine();

                                                }while(wagaNawiasy > 0);

                                                if(!ok1)
                                                {
                                                    pomoc2 += ":";
                                                    lista.insert(lista.size() - 1,pomoc2);
                                                    lista.insert(lista.size() - 1, wpisywana);
                                                    if(!pomoc1.isNull())
                                                    {
                                                        lista.push_back(pomoc1);
                                                    }
                                                }

                                                QString sklej = lista.join('\n');
                                                str2 << sklej << endl;
                                            }
                                        }
                                        else if(szukana.contains("struct"))
                                        {
                                            if(relacja->getWidocznosc() == wPublic)
                                            {
                                                str2 << pomoc1 << endl;
                                                str2 << wpisywana << endl;
                                            }
                                            else if(relacja->getWidocznosc() == wPrivate || relacja->getWidocznosc() == wProtected)
                                            {
                                                QString pomoc2 = "";
                                                if(relacja->getWidocznosc() == wPublic)
                                                    pomoc2 = "private";
                                                else
                                                    pomoc2 = "protected";

                                                bool ok1 = false;
                                                int wagaNawiasy = 0;
                                                QStringList lista;
                                                lista.clear();
                                                do
                                                {
                                                    lista.push_back(pomoc1);

                                                    //Pobieramy do buforowej listy dopoki nie pobierzemy calego ciala
                                                    if(pomoc1.contains("{"))
                                                    {
                                                        wagaNawiasy++;
                                                    }
                                                    else if(pomoc1.contains("}"))
                                                    {
                                                        wagaNawiasy--;
                                                    }

                                                    if(pomoc1.contains(pomoc2))
                                                    {
                                                        lista.push_back(wpisywana);
                                                        ok1 = true;
                                                        break;
                                                    }

                                                    pomoc1 = str1.readLine();

                                                }while(wagaNawiasy > 0);

                                                if(!ok1)
                                                {
                                                    pomoc2 += ":";
                                                    lista.insert(lista.size() - 1,pomoc2);
                                                    lista.insert(lista.size() - 1, wpisywana);
                                                    if(!pomoc1.isNull())
                                                    {
                                                        lista.push_back(pomoc1);
                                                    }
                                                }

                                                QString sklej = lista.join('\n');
                                                str2 << sklej << endl;
                                            }
                                        }  // W poniższych nie ma problemu prywatnosci wiec nie zastanawiając się wpisujemy na początek
                                        else if(szukana.contains("enum") || szukana.contains("union") || szukana.contains("namespace"))
                                        {
                                            str2 << pomoc1 << endl;
                                            str2 << wpisywana << endl;
                                        }
                                    }
                                    else
                                    {
                                        if(!pomoc1.isNull())
                                            str2 << pomoc1 << endl;
                                    }
                                }
                                pomoc1 = str1.readLine();
                            }
                        }
                        else
                        {
                            //OBSŁUGA BŁĘDU = PROBLEM Z PLIKIEM
                        }

                        Naglowek.close();
                        Pom.close();

                        if(Naglowek.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate) && Pom.open(QIODevice::Text | QIODevice::ReadOnly))
                        {
                            QTextStream str1(&Naglowek), str2(&Pom);

                            pomoc1 = str2.readLine();
                            while(!pomoc1.isNull())
                            {
                                str1 << pomoc1 << endl;
                                pomoc1 = str2.readLine();
                            }

                            Pom.close();
                            Naglowek.close();
                            Pom.remove();
                        }
                        else
                        {
                            //OBSŁUGA BŁĘDU = PROBLEM Z PLIKAMI
                        }
                    }
                }
            }
        }
    }
}






