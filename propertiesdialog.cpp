#include "propertiesdialog.h"

PropertiesDialog::PropertiesDialog(DiagramTextItem* item, QWidget *parent):
    QDialog(parent)
{
    Element* elem = item->getElementAdress();
    elem->setNazwa(item->toPlainText());

    Itemisko = item;
    elemWyswietlany = elem;

    if(dynamic_cast<Klasa*>(elem))
    {
        ustawKlasa(dynamic_cast<Klasa*>(elem));
        myProperties = Klassa;
    }else if(dynamic_cast<Struktura*>(elem))
    {
        ustawDlaOperacji(dynamic_cast<ElementZOperacjami*>(elem));
        myProperties = zOperacjami;
    }else if(dynamic_cast<Wyliczenie*>(elem))
    {
        ustawBezOperacji(elem);
        myProperties = bezOperacji;
    }else if(dynamic_cast<Unia*>(elem))
    {
        ustawBezOperacji(elem);
        myProperties = bezOperacji;
    }else if(dynamic_cast<PrzestrzenNazw*>(elem))
    {
        ustawDlaOperacji(dynamic_cast<ElementZOperacjami*>(elem));
        myProperties = zOperacjami;
    }
}

PropertiesDialog::~PropertiesDialog()
{

}

void PropertiesDialog::ustawDlaOperacji(ElementZOperacjami *element)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *fLayout = new QFormLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    NazwaLE = new QLineEdit;
    ok = new QPushButton("OK");
    close = new QPushButton("Close");
    addOperacja = new QPushButton("Dodaj");
    addAtrybut = new QPushButton("Dodaj");
    OperacjeLista = new QListWidget;
    AtrybutyLista = new QListWidget;
    line = new QFrame();
    line2 = new QFrame();

    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);

    fLayout->addRow(new QLabel("Nazwa "),NazwaLE);
    fLayout->addRow(line);
    fLayout->addRow(new QLabel("Lista Atrybutów:"));
    fLayout->addRow(AtrybutyLista);
    fLayout->addRow(addAtrybut);
    fLayout->addRow(line2);
    fLayout->addRow(new QLabel("Lista Operacji:"));
    fLayout->addRow(OperacjeLista);
    fLayout->addRow(addOperacja);

    hLayout->addWidget(ok);
    hLayout->addWidget(close);

    layout->addLayout(fLayout);
    layout->addLayout(hLayout);

    setLayout(layout);

    setWindowTitle(tr("Properties"));

    NazwaLE->setText(element->getNazwa());

    QVector<Operacja> operWekt = element->getListaOperacji();
    QStringList listaPom;
    listaPom.clear();
    QString pomocny;
    for(int i = 0; i < operWekt.size(); i++)
    {
        pomocny << operWekt[i];
        listaPom.append(pomocny);
    }

    OperacjeLista->addItems(listaPom);

    QVector<Atrybut> atrWekt = element->getListaAtrybutow();
    listaPom.clear();
    for(int i = 0; i < atrWekt.size(); i++)
    {
        pomocny << atrWekt[i];
        listaPom.append(pomocny);
    }
    AtrybutyLista->addItems(listaPom);


    connect(addOperacja, SIGNAL(clicked()), this, SLOT(addOperacjaHandle()));
    connect(addAtrybut, SIGNAL(clicked()), this, SLOT(addAtrybutHandle()));
    connect(ok,SIGNAL(clicked()),this,SLOT(okHandle()));
    connect(close,SIGNAL(clicked()),this,SLOT(closeHandle()));
    connect(OperacjeLista,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(operacjaModifyHandle(QListWidgetItem*)));
    connect(AtrybutyLista,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(atrybutModifyHandle(QListWidgetItem*)));
}

void PropertiesDialog::ustawBezOperacji(Element *element)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *fLayout = new QFormLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    NazwaLE = new QLineEdit;
    ok = new QPushButton("OK");
    close = new QPushButton("Close");
    addAtrybut = new QPushButton("Dodaj");
    AtrybutyLista = new QListWidget;
    line = new QFrame();
    line2 = new QFrame();

    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);

    fLayout->addRow(new QLabel("Nazwa "),NazwaLE);
    fLayout->addRow(line);
    fLayout->addRow(new QLabel("Lista Atrybutów:"));
    fLayout->addRow(AtrybutyLista);
    fLayout->addRow(addAtrybut);

    hLayout->addWidget(ok);
    hLayout->addWidget(close);

    layout->addLayout(fLayout);
    layout->addLayout(hLayout);

    setLayout(layout);

    setWindowTitle(tr("Properties"));

    NazwaLE->setText(element->getNazwa());

    QStringList listaPom;
    listaPom.clear();
    QString pomocny;
    QVector<Atrybut> atrWekt = element->getListaAtrybutow();
    for(int i = 0; i < atrWekt.size(); i++)
    {
        pomocny << atrWekt[i];
        listaPom.append(pomocny);
    }
    AtrybutyLista->addItems(listaPom);

    connect(addAtrybut, SIGNAL(clicked()), this, SLOT(addAtrybutHandle()));
    connect(ok,SIGNAL(clicked()),this,SLOT(okHandle()));
    connect(close,SIGNAL(clicked()),this,SLOT(closeHandle()));
    connect(AtrybutyLista,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(atrybutModifyHandle(QListWidgetItem*)));
}

void PropertiesDialog::ustawKlasa(Klasa *element)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *fLayout = new QFormLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;

    NazwaLE = new QLineEdit;
    ok = new QPushButton("OK");
    close = new QPushButton("Close");
    addOperacja = new QPushButton("Dodaj");
    addAtrybut = new QPushButton("Dodaj");
    OperacjeLista = new QListWidget;
    AtrybutyLista = new QListWidget;
    CzyAbstrakcyjna = new QCheckBox;
    line = new QFrame();
    line2 = new QFrame();

    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    fLayout->addRow(new QLabel("Nazwa "),NazwaLE);
    fLayout->addRow(new QLabel("Czy abstrakcyjna"),CzyAbstrakcyjna);
    fLayout->addRow(line);
    fLayout->addRow(new QLabel("Lista Atrybutów:"));
    fLayout->addRow(AtrybutyLista);
    fLayout->addRow(addAtrybut);
    fLayout->addRow(line2);
    fLayout->addRow(new QLabel("Lista Operacji:"));
    fLayout->addRow(OperacjeLista);
    fLayout->addRow(addOperacja);

    hLayout->addWidget(ok);
    hLayout->addWidget(close);

    layout->addLayout(fLayout);
    layout->addLayout(hLayout);

    setLayout(layout);

    setWindowTitle(tr("Properties"));

    NazwaLE->setText(element->getNazwa());

    QVector<Operacja> operWekt = element->getListaOperacji();
    QStringList listaPom;
    listaPom.clear();
    QString pomocny;
    for(int i = 0; i < operWekt.size(); i++)
    {
        pomocny << operWekt[i];
        listaPom.append(pomocny);
    }
    OperacjeLista->addItems(listaPom);

    QVector<Atrybut> atrWekt = element->getListaAtrybutow();
    listaPom.clear();
    pomocny;
    for(int i = 0; i < atrWekt.size(); i++)
    {
        pomocny << atrWekt[i];
        listaPom.append(pomocny);
    }
    AtrybutyLista->addItems(listaPom);

    if(element->getCzyAbstrakcyjna())
    {
        CzyAbstrakcyjna->setChecked(true);
    }else
    {
        CzyAbstrakcyjna->setChecked(false);
    }

    connect(addOperacja, SIGNAL(clicked()), this, SLOT(addOperacjaHandle()));
    connect(addAtrybut, SIGNAL(clicked()), this, SLOT(addAtrybutHandle()));
    connect(ok,SIGNAL(clicked()),this,SLOT(okHandle()));
    connect(close,SIGNAL(clicked()),this,SLOT(closeHandle()));
    connect(OperacjeLista,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(operacjaModifyHandle(QListWidgetItem*)));
    connect(AtrybutyLista,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(atrybutModifyHandle(QListWidgetItem*)));
}

void PropertiesDialog::addOperacjaHandle()
{
    if(dynamic_cast<ElementZOperacjami*>(elemWyswietlany))
    {
        int numKeeper = (dynamic_cast<ElementZOperacjami*>(elemWyswietlany))->getListaOperacji().size();
        OperacjaDialog operDialog(elemWyswietlany);
        operDialog.exec();

        if(numKeeper != (dynamic_cast<ElementZOperacjami*>(elemWyswietlany))->getListaOperacji().size())
        {
            QString pomoc;
            pomoc << (dynamic_cast<ElementZOperacjami*>(elemWyswietlany))->getListaOperacji().at((dynamic_cast<ElementZOperacjami*>(elemWyswietlany))->getListaOperacji().size()-1);
            OperacjeLista->addItem(pomoc);
        }
    }
}

void PropertiesDialog::addAtrybutHandle()
{
    int rozmiar = elemWyswietlany->getListaAtrybutow().size();
    AtrybutDialog atrDialog(elemWyswietlany);
    atrDialog.exec();
    if(rozmiar<elemWyswietlany->getListaAtrybutow().size())
    {
        QString pomoc;
        pomoc << elemWyswietlany->getListaAtrybutow().at(elemWyswietlany->getListaAtrybutow().size()-1);
        AtrybutyLista->addItem(pomoc);
    }
}

void PropertiesDialog::okHandle()
{
    elemWyswietlany->setNazwa(NazwaLE->text());
    Itemisko->setPlainText(NazwaLE->text());

    if(myProperties == Klassa)
        (dynamic_cast<Klasa*>(elemWyswietlany))->setCzyAbstrakcyjna(CzyAbstrakcyjna->isChecked());
    reject();
}

void PropertiesDialog::closeHandle()
{
    reject();
}

void PropertiesDialog::operacjaModifyHandle(QListWidgetItem *item)
{
    int numKeeper;
    for(int i = 0; i < OperacjeLista->count(); i++)
    {
        if(OperacjeLista->item(i) == item)
        {
            numKeeper = i;
            break;
        }
    }
    Operacja* operacja = new Operacja;
    *operacja = (dynamic_cast<ElementZOperacjami*>(elemWyswietlany))->getListaOperacji().at(numKeeper);
    OperacjaDialog oper(operacja);
    oper.exec();
    (dynamic_cast<ElementZOperacjami*>(elemWyswietlany))->getListaOperacji().replace(numKeeper,*operacja);
    QString pomoc;
    pomoc << (*operacja);
    item->setText(pomoc);
    delete operacja;
}

void PropertiesDialog::atrybutModifyHandle(QListWidgetItem *item)
{
    int numKeeper;
    for(int i = 0; i < AtrybutyLista->count(); i++)
    {
        if(AtrybutyLista->item(i) == item)
        {
            numKeeper = i;
            break;
        }
    }
    Atrybut* atrybut = new Atrybut;
    *atrybut = elemWyswietlany->getListaAtrybutow().at(numKeeper);
    AtrybutDialog atrDialog(atrybut);
    atrDialog.exec();
    elemWyswietlany->getListaAtrybutow().replace(numKeeper,*atrybut);
    QString pomoc;
    pomoc << (*atrybut);
    item->setText(pomoc);
    delete atrybut;
}

