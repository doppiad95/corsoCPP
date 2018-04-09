#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionLoad_file, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(ui->actionClose,SIGNAL(triggered(bool)),this,SLOT(chiudiFinestra()));
}
void MainWindow::loadFile()
{
    if(loaded){
        while(ui->listWidget->count()>0)
        {
          ui->listWidget->takeItem(0);//handle the item if you don't
                                  //have a pointer to it elsewhere
        }
        QLayoutItem *child;
        while ((child = ui->verticalLayout->takeAt(0)) != 0) {
            delete child->widget();
            delete child;
        }
    }
            QStringList checkBox;
            QList<QListWidgetItem*> itemToAdd;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString fileOrFolder = it.next();
        QStringList ql = fileOrFolder.split("/");

        if(fileOrFolder.contains(".jpg")){
            ui->listWidget->setViewMode(QListWidget::IconMode);

            ui->listWidget->setIconSize(QSize(120,120));

            ui->listWidget->setResizeMode(QListWidget::Adjust);
        QListWidgetItem* toAdd = new QListWidgetItem(QIcon(fileOrFolder), ql.at(ql.count()-2));
        toAdd->setWhatsThis(fileOrFolder);
        itemToAdd.append(toAdd);

            if(!checkBox.contains(ql.at(ql.count()-2)))
                    checkBox.append(ql.at(ql.count()-2));
        }
loaded = true;
 }
    std::random_shuffle(itemToAdd.begin(),itemToAdd.end());
    foreach(QListWidgetItem* toAdd,itemToAdd){
     ui->listWidget->addItem(toAdd);
}
    QCheckBox *cb = new QCheckBox("All", this);
    cb->setChecked(true);
    ui->verticalLayout->addWidget(cb);
    connect(cb , SIGNAL(stateChanged(int)),this,SLOT(checkBoxStateChanged(int)));
    for(int i = 0; i<checkBox.count();i++){
        QCheckBox *cb = new QCheckBox(checkBox[i], this);
        cb->setChecked(true);
            ui->verticalLayout->addWidget(cb);
            connect(cb , SIGNAL(stateChanged(int)),this,SLOT(checkBoxStateChanged(int)));
            checkb.append(cb);
    }
    QObject::connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
    QObject::connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClicked(QListWidgetItem*)));
}
void MainWindow::itemClicked(QListWidgetItem* listWidgetItem) {
        QTimer::singleShot(QApplication::doubleClickInterval(), this, SLOT(itemClickedTimeout()));
        // use QApplication::doubleClickInterval() instead of 300
        mSingleClickedItem = listWidgetItem;
}
void MainWindow::checkBoxStateChanged(int state){
    QCheckBox* c = qobject_cast<QCheckBox*>(sender());
    QMessageBox* msg = new QMessageBox(this->parentWidget());
    msg->setWindowTitle("Hello !");
    if(c->text() == "All" && !state){
        foreach(QCheckBox* qc,checkb){
            qc->setChecked(false);
            if(!filtri.contains(qc->text()))
                filtri.append(qc->text());
        }
    }
    if(c->text() == "All" && state){
        foreach(QCheckBox* qc,checkb){
            qc->setChecked(true);
            filtri.clear();
        }
    }
    if(c->text()!="All" && !state)
    {
        if(!filtri.contains(c->text()))
            filtri.append(c->text());
    }if(c->text()!="All" && state)
    {
        filtri.removeOne(c->text());
    }
    Filtra();

};
void MainWindow::itemClickedTimeout() {
    if (!mDoubleClicked) {
        // do something, listitem has been clicked once
    } else mDoubleClicked = false;
}
void MainWindow::Filtra(){
                QList<QListWidgetItem*> itemToAdd;
    while(ui->listWidget->count()>0)
    {
      ui->listWidget->takeItem(0);//handle the item if you don't
                              //have a pointer to it elsewhere
    }
    QDirIterator it(dir, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString fileOrFolder = it.next();
        QStringList ql = fileOrFolder.split("/");

        if(fileOrFolder.contains(".jpg") && !filtri.contains(ql.at(ql.count()-2))){
            ui->listWidget->setViewMode(QListWidget::IconMode);

            ui->listWidget->setIconSize(QSize(120,120));

            ui->listWidget->setResizeMode(QListWidget::Fixed);
            QListWidgetItem* toAdd = new QListWidgetItem(QIcon(fileOrFolder), ql.at(ql.count()-2));
            toAdd->setWhatsThis(fileOrFolder);
            itemToAdd.append(toAdd);
            }

     }
        std::random_shuffle(itemToAdd.begin(),itemToAdd.end());
        foreach(QListWidgetItem* toAdd,itemToAdd){
         ui->listWidget->addItem(toAdd);
    }

 //   QObject::connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
 //   QObject::connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClicked(QListWidgetItem*)));
}
void MainWindow::itemDoubleClicked(QListWidgetItem* listWidgetItem) {
    mDoubleClicked = true;
    QMessageBox msgBox;
    //QString dd = listWidgetItem->icon();
    Dialog* dia = new Dialog;
    dia->setWindowIcon(listWidgetItem->icon());
    dia->setImage(listWidgetItem->whatsThis());
    dia->show();
    //dir + "/" + listWidgetItem->text() + "/" +
    // do something, listitem has been clicked twice
}
void MainWindow::chiudiFinestra(){
    qApp->closeAllWindows();
    qApp->exit(0);
}
MainWindow::~MainWindow()
{
    while(ui->listWidget->count()>0)
    {
      ui->listWidget->takeItem(0);//handle the item if you don't
                              //have a pointer to it elsewhere
    }
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
    qDeleteAll(checkb);
    filtri.clear();
    delete &filtri;
    checkb.clear();
    delete ui;
}
