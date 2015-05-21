#include "operacjadialog.h"

OperacjaDialog::OperacjaDialog(Element* element,QWidget *parent):
    QDialog(parent)
{
    myElement = element;
    myOperacja = new Operacja;
    setUpGui();
}

OperacjaDialog::OperacjaDialog(Operacja *operacja, QWidget *parent):
    QDialog(parent)
{
    myOperacja = operacja;
    myElement = NULL;
    setUpGui();
    NazwaLE->setText(myOperacja->getNazwa());
    TypLE->setText(myOperacja->getTyp());
    IleLE->setText(QString::number(myOperacja->getN()));
    KontenerLE->setText(myOperacja->getKontener());
    switch(myOperacja->getSpecyfikatorDostepu())
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

    switch(myOperacja->getKrotnosc())
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

    switch(myOperacja->getTypPrzekazaniaParametru())
    {
    case przezWartosc:
        PrzekazanieParametruCB->setCurrentIndex(0);
        break;
    case przezReferencje:
        PrzekazanieParametruCB->setCurrentIndex(1);
        break;
    case przezWskaznik:
        PrzekazanieParametruCB->setCurrentIndex(2);
        break;
    }
    CzyStaticRB->setChecked(myOperacja->getCzyStatyczna());
    CzyConstRB->setChecked(myOperacja->getCzyConst());
    CzyWirtualnaRB->setChecked(myOperacja->getCzyWirtualna());
    QString pomoc;
    QList<Atrybut> atrList;
    atrList = myOperacja->getListaParametrow();
    for(int i = 0; i < atrList.size(); i ++)
    {
        pomoc << atrList.at(i);
        ParametryOperacji->addItem(pomoc);
    }
}

OperacjaDialog::~OperacjaDialog()
{

}

void OperacjaDialog::okHandle()
{
    myOperacja->setNazwa(NazwaLE->text());
    myOperacja->setTyp(TypLE->text());
    myOperacja->setN(IleLE->text().toInt());
    myOperacja->setKontener(KontenerLE->text());
    switch(WidocznoscCB->currentIndex())
    {
    case 0:
        myOperacja->setSpecyfikatorDostepu(wPrivate);
        break;
    case 1:
        myOperacja->setSpecyfikatorDostepu(wPublic);
        break;
    case 2:
        myOperacja->setSpecyfikatorDostepu(wProtected);
        break;
    case 3:
        myOperacja->setSpecyfikatorDostepu(ND);
        break;
    }

    switch(KrotnoscCB->currentIndex())
    {
    case 0:
        myOperacja->setKrotnosc(Jeden);
        break;
    case 1:
        myOperacja->setKrotnosc(JedenLubX);
        break;
    case 2:
        myOperacja->setKrotnosc(ZeroLub1);
        break;
    case 3:
        myOperacja->setKrotnosc(ZeroLubX);
        break;
    case 4:
        myOperacja->setKrotnosc(N);
        break;
    case 5:
        myOperacja->setKrotnosc(WiecejNizN);
        break;
    }

    switch(PrzekazanieParametruCB->currentIndex())
    {
    case 0:
        myOperacja->setPrzekazanieParametru(przezWartosc);
        break;
    case 1:
        myOperacja->setPrzekazanieParametru(przezReferencje);
        break;
    case 2:
        myOperacja->setPrzekazanieParametru(przezWskaznik);
        break;
    }
    myOperacja->setCzyStatyczna(CzyStaticRB->isChecked());
    myOperacja->setCzyConst(CzyConstRB->isChecked());
    myOperacja->setCzyWirtualna(CzyWirtualnaRB->isChecked());

    if(myElement != NULL)
    {
        if(dynamic_cast<ElementZOperacjami*>(myElement))
        {
            (dynamic_cast<ElementZOperacjami*>(myElement))->dodajOperacje(*myOperacja);

        }
    }
    reject();
}

void OperacjaDialog::closeHandle()
{
    if(myElement != NULL)
        delete myOperacja;
    reject();
}

void OperacjaDialog::addParamHandle()
{
    Atrybut* atrybut = new Atrybut;
    AtrybutDialog atrDialog(atrybut);
    atrDialog.exec();
    if(atrybut->getNazwa() != "" && atrybut->getTyp() != "")
    {
        myOperacja->dodajParametr(*atrybut);
        QString pomoc;
        pomoc << (*atrybut);
        ParametryOperacji->addItem(pomoc);
    }else
    {
        delete atrybut;
    }
}

void OperacjaDialog::wybranoParametrHandle(QListWidgetItem *item)
{
    int numKeeper;
    for(int i = 0; i < ParametryOperacji->count(); i++)
    {
        if(ParametryOperacji->item(i) == item)
        {
            numKeeper = i;
            break;
        }
    }
    Atrybut* atrybut = new Atrybut;
    *atrybut = myOperacja->getListaParametrow().at(numKeeper);
    AtrybutDialog atrDialog(atrybut);
    atrDialog.exec();
    myOperacja->replaceAtrybutAt(*atrybut,numKeeper);
    QString pomoc;
    pomoc << (*atrybut);
    item->setText(pomoc);
    delete atrybut;
}

void OperacjaDialog::setUpGui()
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
    PrzekazanieParametruCB = new QComboBox;
    CzyStaticRB = new QCheckBox;
    CzyConstRB = new QCheckBox;
    CzyWirtualnaRB = new QCheckBox;
    ok = new QPushButton("OK");
    close = new QPushButton("Close");
    addParametr = new QPushButton("Dodaj parametr");
    ParametryOperacji = new QListWidget;

    QStringList itemsForComboBox;
    itemsForComboBox << "Private" << "Public" << "Protected" << "ND";
    WidocznoscCB->addItems(itemsForComboBox);
    itemsForComboBox.clear();
    itemsForComboBox << "Jeden" << "JedenLubX" << "ZeroLub1" << "ZeroLubX" << "N" << "WiecejNizN";
    KrotnoscCB->addItems(itemsForComboBox);
    itemsForComboBox.clear();
    itemsForComboBox << "Wartosc" << "Referencja" << "Wskaźnik";
    PrzekazanieParametruCB->addItems(itemsForComboBox);

    line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    fLayout->addRow(new QLabel("Nazwa "),NazwaLE);
    fLayout->addRow(new QLabel("Typ"),TypLE);
    fLayout->addRow(new QLabel("Widocznosc"),WidocznoscCB);
    fLayout->addRow(new QLabel("Krotnosc"),KrotnoscCB);
    fLayout->addRow(new QLabel("Ile (N)"),IleLE);
    fLayout->addRow(new QLabel("Typ kontenera"),KontenerLE);
    fLayout->addRow(new QLabel("Przekazanie Parametru"),PrzekazanieParametruCB);
    fLayout->addRow(new QLabel("Czy Static"),CzyStaticRB);
    fLayout->addRow(new QLabel("Czy Const"),CzyConstRB);
    fLayout->addRow(new QLabel("Czy Virtual"),CzyWirtualnaRB);
    fLayout->addRow(line);
    fLayout->addRow(new QLabel("Lista Parametrow"));
    fLayout->addRow(ParametryOperacji);
    fLayout->addRow(addParametr);

    hLayout->addWidget(ok);
    hLayout->addWidget(close);

    layout->addLayout(fLayout);
    layout->addLayout(hLayout);

    setLayout(layout);

    setWindowTitle(tr("Dodaj operację"));

    connect(ok,SIGNAL(clicked()),this,SLOT(okHandle()));
    connect(close,SIGNAL(clicked()),this,SLOT(closeHandle()));
    connect(addParametr,SIGNAL(clicked()),this,SLOT(addParamHandle()));
    connect(ParametryOperacji,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(wybranoParametrHandle(QListWidgetItem*)));
}

