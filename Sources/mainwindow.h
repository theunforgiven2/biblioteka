#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QVector>
#include <QVectorIterator>
#include <QDebug>
#include <QtAlgorithms>
#include <fstream>
#include "pozycja.h"
#include "plytacd.h"
#include "kasetawideo.h"
#include "kasetadvhs.h"
#include "kasetaaudio.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_tabWidget_tabBarClicked(int index);

    void wypelnijPlyty();

    void wypelnijKasetyWideo();

    void wypelnijKasetyAudio();

    void usunElement(QTableWidget*, int);

    void edytujElement(QTableWidgetItem*, QTableWidget*);

    void zaladujPlik();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_comboBox_currentIndexChanged(int index);

    void on_kaswideo_tab_itemChanged(QTableWidgetItem *item);

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_6_pressed();

    void on_pushButton_7_pressed();

    void on_kasaudio_tab_itemChanged(QTableWidgetItem *item);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_lineEdit_7_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QVector<Pozycja*> lista;
    std::fstream plik;
    QStringList typyKaset;
    QString nazwaPliku = "data.dat";
};

#endif // MAINWINDOW_H
