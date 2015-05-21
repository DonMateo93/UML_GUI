#include <QtGui>
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QMessageBox>

#include "mainwindow.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "arrow.h"

const int InsertTextButton = 10;

MainWindow::MainWindow()
{
    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu,AtributeOperationContextMenu,AtributeContextMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
            this, SLOT(itemInserted(DiagramItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
        this, SLOT(textInserted(QGraphicsTextItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
        this, SLOT(itemSelected(QGraphicsItem*)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::backgroundButtonGroupClicked(QAbstractButton *button)
{// Tu wyzwalanie strzaleczek
    QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons)
    {
        if (myButton != button)
            myButton->setChecked(false);
    }

    scene->setMode(DiagramScene::InsertLine);

    if(button->text() == "Generalization")
        scene->setArrowType(Arrow::Generalization);
    else if(button->text() == "Dependency")
        scene->setArrowType(Arrow::Dependency);
    else if(button->text() == "Composition")
        scene->setArrowType(Arrow::Composition);
    else if(button->text() == "Aggregation")
        scene->setArrowType(Arrow::Aggregation);
    else if(button->text() == "Association")
        scene->setArrowType(Arrow::Association);


    scene->update();
    view->update();
}

void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();

    foreach (QAbstractButton *button, buttons)
    {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }

    //W razie problemu wkleić kod z GitHuba

    scene->setTextItemType(DiagramTextItem::DiagramTextType(id));
    scene->setMode(DiagramScene::InsertText);//Gdyby były problemy zamienic na insertItem

}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems())
    {
        if (item->type() == Arrow::Type)
        {
            scene->removeItem(item);
            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems())
    {
         if (item->type() == DiagramItem::Type)
         {
             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
         }
         scene->removeItem(item);
         delete item;
    }
}

void MainWindow::addAttribute()
{
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    if(selectedItems.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setText("Musi być wybrany tylko jeden element");
        msgBox.exec();
        return;
    }

    DiagramTextItem* textItem = dynamic_cast<DiagramTextItem*>(selectedItems.at(0));
    if(textItem == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("Wybrany element musi być prostokątem");
        msgBox.exec();
        return;
    }

    AtrybutDialog dialog(textItem->getElementAdress());
    dialog.exec();
}

void MainWindow::addOperation()
{
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    if(selectedItems.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setText("Musi być wybrany tylko jeden element");
        msgBox.exec();

        return;
    }

    if(dynamic_cast<DiagramTextItem*>(selectedItems.at(0)))
    {
        Element* element = dynamic_cast<DiagramTextItem*>(selectedItems.at(0))->getElementAdress();

        OperacjaDialog operacjaDialog(element);
        operacjaDialog.exec();
    }else
    {
        QMessageBox msgBox;
        msgBox.setText("Nie wybrano elementu");
        msgBox.exec();
    }
}

void MainWindow::setProperties()
{   
    if (scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    if(selectedItems.size() != 1)
    {
        QMessageBox msgBox;
        msgBox.setText("Musi być wybrany tylko jeden element");
        msgBox.exec();
        return;
    }

    DiagramTextItem* item;
    item = dynamic_cast<DiagramTextItem*>(selectedItems.at(0));

    if(item != NULL)
    {
        PropertiesDialog propDialog(item);
        propDialog.exec();
    }else
    {
        QMessageBox msgBox;
        msgBox.setText("Błąd, mainwindow.cpp, funkcjaSetProperties");
        msgBox.exec();
    }
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::bringToFront()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue &&
            item->type() == DiagramItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue &&
            item->type() == DiagramItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void MainWindow::textInserted(QGraphicsTextItem *)
{
    //buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}

void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                ":/MojeSkarby/textpointer.png",
                qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

void MainWindow::itemColorChanged()
{
    fillAction = qobject_cast<QAction *>(sender());
    fillColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/MojeSkarby/floodfill.png",
                 qvariant_cast<QColor>(fillAction->data())));
    fillButtonTriggered();
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                 ":/MojeSkarby/linecolor.png",
                 qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}

void MainWindow::fillButtonTriggered()
{
    scene->setItemColor(qvariant_cast<QColor>(fillAction->data()));
}

void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem =
    qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    QColor color = textItem->defaultTextColor();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("Author: Mateusz Osypiński"));
}

void MainWindow::codeGenHandle()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("utworzPlik"),"C://","Plik nagłówkowy (*.h)");
    if(filePath != "")
    {
        QList<QGraphicsItem*> itemy = scene->items();
        Element* element;
        Rel::Relacja* relacja;
        Koder* kod = new KoderCpp;

        for(int i = 0; i < itemy.size(); i++)
        {
            if(dynamic_cast<DiagramTextItem*>(itemy.at(i)))
            {
                element = (dynamic_cast<DiagramTextItem*>(itemy.at(i)))->getElementAdress();
                element->setNazwa(dynamic_cast<DiagramTextItem*>(itemy.at(i))->toPlainText());
                kod->dodajElementDoListy(element);
            }else if(dynamic_cast<Arrow*>(itemy.at(i)))
            {
                relacja = (dynamic_cast<Arrow*>(itemy.at(i)))->getRelacjaAdres();
                kod->dodajRelacje(relacja);
            }
        }

        kod->wprowadzDoPlikuWszystkieElementy(filePath);
        kod->wprowadzDoPlikuWszyskieRelacje(filePath);
        kod->poprawKodWPliku(filePath);
    }
}

void MainWindow::createToolBox()
{

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QVBoxLayout *layout = new QVBoxLayout;

    for ( int fooInt = DiagramItem::Class; fooInt != DiagramItem::Union + 1; fooInt++ )
    {
       layout->addWidget(createCellWidget(static_cast<DiagramItem::DiagramType>(fooInt)));
    }

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    backgroundButtonGroup = new QButtonGroup(this);
    connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

    QVBoxLayout *backgroundLayout = new QVBoxLayout;
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Generalization"),
                ":/MojeSkarby/UML_Arrows/Generalization.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Dependency"),
                ":/MojeSkarby/UML_Arrows/Dependency.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Composition"),
                    ":/MojeSkarby/UML_Arrows/Composition.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Aggregation"),
                ":/MojeSkarby/UML_Arrows/Aggregation.png"));
    backgroundLayout->addWidget(createBackgroundCellWidget(tr("Association"),
                ":/MojeSkarby/UML_Arrows/Association.png"));

    QWidget *backgroundWidget = new QWidget;
    backgroundWidget->setLayout(backgroundLayout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width()+18);
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
    toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void MainWindow::createActions()
{
    toFrontAction = new QAction(QIcon(":/MojeSkarby/bringtofront.png"),
                                tr("Bring to &Front"), this);
    toFrontAction->setShortcut(tr("Ctrl+F"));
    toFrontAction->setStatusTip(tr("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()),
            this, SLOT(bringToFront()));

    sendBackAction = new QAction(QIcon(":/MojeSkarby/sendtoback.png"),
                                 tr("Send to &Back"), this);
    sendBackAction->setShortcut(tr("Ctrl+B"));
    sendBackAction->setStatusTip(tr("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()),
        this, SLOT(sendToBack()));

    deleteAction = new QAction(QIcon(":/MojeSkarby/delete.png"),
                               tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()),
        this, SLOT(deleteItem()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/MojeSkarby/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/MojeSkarby/italic.png"),
                               tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/MojeSkarby/underline.png"),
                                  tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()),
            this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    ProperitiesAction = new QAction(tr("Properities"),this);
    connect(ProperitiesAction, SIGNAL(triggered()),this, SLOT(setProperties()));

    AttributeAction = new QAction(tr("Add atribute"),this);
    connect(AttributeAction, SIGNAL(triggered()),this, SLOT(addAttribute()));

    OperationAction = new QAction(tr("Add operation"),this);
    connect(OperationAction, SIGNAL(triggered()),this, SLOT(addOperation()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);

    AtributeOperationContextMenu = new QMenu();
    AtributeOperationContextMenu->addAction(AttributeAction);
    AtributeOperationContextMenu->addAction(OperationAction);
    AtributeOperationContextMenu->addAction(ProperitiesAction);
    AtributeOperationContextMenu->addSeparator();
    AtributeOperationContextMenu->addAction(deleteAction);
    AtributeOperationContextMenu->addAction(toFrontAction);
    AtributeOperationContextMenu->addAction(sendBackAction);

    AtributeContextMenu = new QMenu();
    AtributeContextMenu->addAction(AttributeAction);
    AtributeContextMenu->addAction(ProperitiesAction);
    AtributeContextMenu->addSeparator();
    AtributeContextMenu->addAction(deleteAction);
    AtributeContextMenu->addAction(toFrontAction);
    AtributeContextMenu->addAction(sendBackAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);

    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()),
                                                 Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(
    ":/MojeSkarby/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));

    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(createColorMenu(SLOT(itemColorChanged()),
                         Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(createColorToolButtonIcon(
    ":/MojeSkarby/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()),
            this, SLOT(fillButtonTriggered()));

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()),
                                 Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
        ":/MojeSkarby/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/MojeSkarby/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/MojeSkarby/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton,
                                int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

    cppButton = new QToolButton;
    cppButton->setCheckable(true);
    cppButton->setIcon(QIcon(":/MojeSkarby/cpp2.png"));
    connect(cppButton,SIGNAL(clicked()),this,SLOT(codeGenHandle()));

    GenToolbar = addToolBar(tr("Generate Code"));
    GenToolbar->addWidget(cppButton);
}

QWidget *MainWindow::createBackgroundCellWidget(const QString &text,
                        const QString &image)
{
    QToolButton *button = new QToolButton;
    button->setText(text);
    button->setIcon(QIcon(image));
    button->setIconSize(QSize(50, 20));
    button->setCheckable(true);
    backgroundButtonGroup->addButton(button);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QWidget *MainWindow::createCellWidget(DiagramItem::DiagramType type)
{
    DiagramItem item(type, itemMenu);

    QToolButton *button = new QToolButton;
    button->setText(item.textForButton());
    button->setCheckable(true);
    button->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()),
                this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor) {
            colorMenu->setDefaultAction(action);
        }
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile,
                        QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    QRect target(0, 0, 50, 60);
    QRect source(0, 0, 42, 42);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}
