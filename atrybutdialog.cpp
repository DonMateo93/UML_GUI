#include "atrybutdialog.h"
#include "ui_atrybutdialog.h"

AtrybutDialog::AtrybutDialog(Element *element, QWidget *parent) :
    QDialog(parent)
{
    if(element != NULL)
    {
        myElement = element;
        myAtrybut = new Atrybut();
        if(dynamic_cast<Wyliczenie*>(element))
        {
            tworzGuiDlaEnum();
        }else
        {
            tworzGuiNormal();
        }
    }else
        reject();
}

AtrybutDialog::AtrybutDialog(Atrybut *atrybut, QWidget *parent):
    QDialog(parent)
{
    myElement = NULL;
    myAtrybut = atrybut;
    if(myAtrybut != NULL)
    {
        if(myAtrybut->getDoEnum())
        {
            tworzGuiDlaEnum();
        }else
        {
            tworzGuiNormal();
        }
    }else
    {
        reject();
    }
}

AtrybutDialog::~AtrybutDialog()
{

}

void AtrybutDialog::addAtrybutHandle()
{
    myAtrybut->setNazwa(NazwaLE->text());
    myAtrybut->setDomyslnaWartosc(DomyslnaWartoscLe->text());
    if(!myAtrybut->getDoEnum())
    {
        myAtrybut->setTyp(TypLE->text());
        myAtrybut->setN(IleLE->text().toInt());
        myAtrybut->setKontener(KontenerLE->text());
        switch(WidocznoscCB->currentIndex())
        {
        case 0:
            myAtrybut->setSpecyfikatorDostepu(wPrivate);
            break;
        case 1:
            myAtrybut->setSpecyfikatorDostepu(wPublic);
            break;
        case 2:
            myAtrybut->setSpecyfikatorDostepu(wProtected);
            break;
        case 3:
            myAtrybut->setSpecyfikatorDostepu(ND);
            break;
        }

        switch(KrotnoscCB->currentIndex())
        {
        case 0:
            myAtrybut->setKrotnosc(Jeden);
            break;
        case 1:
            myAtrybut->setKrotnosc(JedenLubX);
            break;
        case 2:
            myAtrybut->setKrotnosc(ZeroLub1);
            break;
        case 3:
            myAtrybut->setKrotnosc(ZeroLubX);
            break;
        case 4:
            myAtrybut->setKrotnosc(N);
            break;
        case 5:
            myAtrybut->setKrotnosc(WiecejNizN);
            break;
        }
        myAtrybut->setCzyStatyczna(CzyStaticRB->isChecked());
        myAtrybut->setCzyConst(CzyConstRB->isChecked());
    }

    if(myElement != NULL)
    {
        myElement->dodajAtrybut(*myAtrybut);
    }
    reject();
}

void AtrybutDialog::closeHandle()
{
    delete myAtrybut;
    reject();
}

void AtrybutDialog::tworzGuiDlaEnum()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *fLayout = new QFormLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    NazwaLE = new QLineEdit;
    DomyslnaWartoscLe = new QLineEdit;
    ok = new QPushButton("OK");
    close = new QPushButton("Close");

    fLayout->addRow(new QLabel("Nazwa "),NazwaLE);
    fLayout->addRow(new QLabel("Domyslna wartosc"),DomyslnaWartoscLe);

    hLayout->addWidget(ok);
    hLayout->addWidget(close);

    layout->addLayout(fLayout);
    layout->addLayout(hLayout);

    setLayout(layout);

    setWindowTitle(tr("Dodaj atrybut"));

    NazwaLE->setText(myAtrybut->getNazwa());
    DomyslnaWartoscLe->setText(myAtrybut->getDomyslnaWartosc());

    connect(ok, SIGNAL(clicked()), this, SLOT(addAtrybutHandle()));
    connect(close, SIGNAL(clicked()), this, SLOT(closeHandle()));
}

void AtrybutDialog::tworzGuiNormal()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *fLayout = new QFormLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    NazwaLE = new QLineEdit;
    TypLE = new QLineEdit;
    IleLE = new QLineEdit;
    KontenerLE = new QLineEdit;
    WidocznoscCB = new QComboBox;
    KrotnoscCB = new QComboBox;
    DomyslnaWartoscLe = new QLineEdit;
    CzyStaticRB = new QCheckBox;
    CzyConstRB = new QCheckBox;
    ok = new QPushButton("OK");
    close = new QPushButton("Close");

    QStringList itemsForComboBox;
    itemsForComboBox << "Private" << "Public" << "Protected" << "ND";
    WidocznoscCB->addItems(itemsForComboBox);
    itemsForComboBox.clear();
    itemsForComboBox << "Jeden" << "JedenLubX" << "ZeroLub1" << "ZeroLubX" << "N" << "WiecejNizN";
    KrotnoscCB->addItems(itemsForComboBox);


    fLayout->addRow(new QLabel("Nazwa "),NazwaLE);
    fLayout->addRow(new QLabel("Typ"),TypLE);
    fLayout->addRow(new QLabel("Widocznosc"),WidocznoscCB);
    fLayout->addRow(new QLabel("Krotnosc"),KrotnoscCB);
    fLayout->addRow(new QLabel("Ile (N)"),IleLE);
    fLayout->addRow(new QLabel("Typ kontenera"),KontenerLE);
    fLayout->addRow(new QLabel("CzyStatic"),CzyStaticRB);
    fLayout->addRow(new QLabel("CzyConst"),CzyConstRB);
    fLayout->addRow(new QLabel("Domyslna wartosc"),DomyslnaWartoscLe);

    hLayout->addWidget(ok);
    hLayout->addWidget(close);

    layout->addLayout(fLayout);
    layout->addLayout(hLayout);

    setLayout(layout);

    setWindowTitle(tr("Dodaj atrybut"));

    NazwaLE->setText(myAtrybut->getNazwa());
    TypLE->setText(myAtrybut->getTyp());
    IleLE->setText(QString::number(myAtrybut->getN()));
    KontenerLE->setText(myAtrybut->getKontener());
    switch(myAtrybut->getSpecyfikatorDostepu())
    {
    case wPrivate:
        WidocznoscCB->setCurrentIndex(0);
        break;
    case wPublic:
        WidocznoscCB->setCurrentIndex(1);
        break;
    case wProtected:
        WidocznoscCB->setCurrentIndex(2);
        break;
    case ND:
        WidocznoscCB->setCurrentIndex(3);
        break;
    }

    switch(myAtrybut->getKrotnosc())
    {
    case Jeden:
        KrotnoscCB->setCurrentIndex(0);
        break;
    case JedenLubX:
        KrotnoscCB->setCurrentIndex(1);
        break;
    case ZeroLub1:
        KrotnoscCB->setCurrentIndex(2);
        break;
    case ZeroLubX:
        KrotnoscCB->setCurrentIndex(3);
        break;
    case N:
        KrotnoscCB->setCurrentIndex(4);
        break;
    case WiecejNizN:
        KrotnoscCB->setCurrentIndex(5);
        break;
    }

    DomyslnaWartoscLe->setText(myAtrybut->getDomyslnaWartosc());
    CzyStaticRB->setChecked(myAtrybut->getCzyStatyczna());
    CzyConstRB->setChecked(myAtrybut->getCzyConst());


    connect(ok, SIGNAL(clicked()), this, SLOT(addAtrybutHandle()));
    connect(close, SIGNAL(clicked()), this, SLOT(closeHandle()));
}
