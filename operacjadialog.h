#ifndef OPERACJADIALOG_H
#define OPERACJADIALOG_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QRadioButton>
#include <QStringList>
#include <QCheckBox>
#include <QListWidget>
#include <QFrame>
#include <QStackedLayout>
#include "atrybutdialog.h"


class OperacjaDialog: public QDialog
{
    Q_OBJECT
public:
    explicit OperacjaDialog(Element *element, QWidget *parent = 0);
    explicit OperacjaDialog(Operacja *operacja, QWidget *parent = 0);
    ~OperacjaDialog();

public slots:
    void okHandle();
    void closeHandle();
    void addParamHandle();
    void wybranoParametrHandle(QListWidgetItem* item);

private:
    QFrame* line;
    QLineEdit* NazwaLE;
    QLineEdit* TypLE;
    QLineEdit* IleLE;
    QLineEdit* KontenerLE;
    QComboBox* KrotnoscCB;
    QComboBox* WidocznoscCB;
    QComboBox* PrzekazanieParametruCB;
    QCheckBox* CzyStaticRB;
    QCheckBox* CzyWirtualnaRB;
    QCheckBox* CzyConstRB;
    QPushButton* ok;
    QPushButton* close;
    QPushButton* addParametr;
    QListWidget* ParametryOperacji;
    Element* myElement;
    Operacja* myOperacja;
    void setUpGui();
};

#endif // OPERACJADIALOG_H
