#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qfiledialog.h>
#include <qdiriterator.h>
#include <qdebug.h>
#include <qcheckbox.h>
#include <qlistwidget.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include <qlist.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QListWidgetItem* mSingleClickedItem;
        bool mDoubleClicked;
        QString dir;
    QList<QCheckBox*> checkb;
    void Filtra();
    QList<QString> filtri;
    bool loaded;
private slots:
    void loadFile();
    void itemClickedTimeout();
    void itemClicked(QListWidgetItem* listWidgetItem);
    void itemDoubleClicked(QListWidgetItem* listWidgetItem);
    void checkBoxStateChanged(int state);
    void chiudiFinestra();
};

#endif // MAINWINDOW_H
