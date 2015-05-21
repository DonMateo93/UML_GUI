#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include <QStringList>
#include <QCheckBox>
#include <QListWidget>
#include <QFrame>
#include "operacjadialog.h"
#include "atrybutdialog.h"
#include "element.h"
#include "diagramtextitem.h"

class PropertiesDialog: public QDialog
{
    Q_OBJECT

public:
    enum PropertiesType{zOperacjami, bezOperacji, Klassa};
    explicit PropertiesDialog(DiagramTextItem *item, QWidget *parent = 0);
    ~PropertiesDialog();

public slots:
    void addOperacjaHandle();
    void addAtrybutHandle();
    void okHandle();
    void closeHandle();
    void operacjaModifyHandle(QListWidgetItem* item);
    void atrybutModifyHandle(QListWidgetItem* item);

private:
    void ustawDlaOperacji(ElementZOperacjami *element);
    void ustawBezOperacji(Element *element);
    void ustawKlasa(Klasa *element);

    QFrame* line;
    QFrame* line2;
    QLineEdit* NazwaLE;
    QPushButton* ok;
    QPushButton* addOperacja;
    QPushButton* addAtrybut;
    QPushButton* close;
    QListWidget* OperacjeLista;
    QListWidget* AtrybutyLista;
    QCheckBox* CzyAbstrakcyjna;
    Element* elemWyswietlany;
    DiagramTextItem* Itemisko;
    PropertiesType myProperties;
};

#endif // PROPERTIESDIALOG_H
