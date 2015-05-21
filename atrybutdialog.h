#ifndef ATRYBUTDIALOG_H
#define ATRYBUTDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include <QStringList>
#include <QCheckBox>
#include "element.h"

namespace Ui {
class AtrybutDialog;
}

class AtrybutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AtrybutDialog(Element* element,QWidget *parent = 0);
    explicit AtrybutDialog(Atrybut* atrybut,QWidget *parent = 0);
    ~AtrybutDialog();

public slots:
    void addAtrybutHandle();
    void closeHandle();

private:
    void tworzGuiDlaEnum();
    void tworzGuiNormal();
    QLineEdit* NazwaLE;
    QLineEdit* IleLE;
    QLineEdit* KontenerLE;
    QLineEdit* TypLE;
    QLineEdit* DomyslnaWartoscLe;
    QComboBox* KrotnoscCB;
    QComboBox* WidocznoscCB;
    QCheckBox* CzyStaticRB;
    QCheckBox* CzyConstRB;
    QPushButton* ok;
    QPushButton* close;
    Atrybut* myAtrybut;
    Element* myElement;
};

#endif // ATRYBUTDIALOG_H
