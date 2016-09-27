#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    ui->groupBox_2->hide();
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    this->typyKaset=QStringList()<<"S-VHS"<<"VHS-C"<<"D-VHS";
    ui->comboBox->addItems(this->typyKaset);
    header->resizeSection(0,139);
    header->resizeSection(1,180);
    header->resizeSection(2,40);
    header->resizeSection(3,180);
    header->resizeSection(4,120);
    header->resizeSection(5,40);

    header=ui->kaswideo_tab->horizontalHeader();
    header->resizeSection(0,139);
    header->resizeSection(1,180);
    header->resizeSection(2,40);
    header->resizeSection(3,180);
    header->resizeSection(4,70);
    header->resizeSection(5,45);
    header->resizeSection(6,45);

    header = ui->kasaudio_tab->horizontalHeader();
    header->resizeSection(0,139);
    header->resizeSection(1,180);
    header->resizeSection(2,40);
    header->resizeSection(3,180);
    header->resizeSection(4,120);
    header->resizeSection(5,40);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSortingEnabled(true);
    ui->kaswideo_tab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->kaswideo_tab->setSortingEnabled(true);
    ui->kasaudio_tab->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->kasaudio_tab->setSortingEnabled(true);
    this->zaladujPlik();
    this->wypelnijPlyty();
}

MainWindow::~MainWindow()
{
    std::sort(lista.begin(), lista.end(),
                  [](const Pozycja *a, const Pozycja *b) {
                        if((*a).getAutor().toLower()!=(*b).getAutor().toLower())
                            return (*a).getAutor().toLower() < (*b).getAutor().toLower();
                        return (*a).getTytul().toLower() < (*b).getTytul().toLower();
                    });
    plik.open(nazwaPliku.toStdString().c_str(), std::ios::out | std::ios::binary);
    for(QVector<Pozycja*>::Iterator it=lista.begin(); it!=lista.end(); ++it){
        TypPozycji pozycja = (*it)->getTyp();
        plik.write((char*)&pozycja, sizeof(TypPozycji));
        switch(pozycja){
            case PLYTACD:
                plik.write((char*)(*it), sizeof(PlytaCD));
            break;
            case KASETAWIDEO:
                plik.write((char*)(*it), sizeof(KasetaWideo));
            break;
            case KASETAWIDEODVHS:
                plik.write((char*)(*it), sizeof(KasetaDVHS));
            break;
            case KASETAAUDIO:
                plik.write((char*)(*it), sizeof(KasetaAudio));
            break;
        }
        delete (*it);
    }
    plik.close();
    delete ui;
}

/* Ładowanie danych z pliku binarnego do wektora */

void MainWindow::zaladujPlik(){
    plik.open(nazwaPliku.toStdString().c_str(), std::ios::in | std::ios::binary);
    if(plik.is_open()){
    char *temp;
    TypPozycji typ;
    while(plik){
       plik.read((char*)&typ, sizeof(TypPozycji));
       switch(typ){
           case PLYTACD:
               temp = new char[sizeof(PlytaCD)];
               plik.read(temp, sizeof(PlytaCD));
               lista.push_back(new PlytaCD((PlytaCD*)temp));
               delete[] temp;
           break;
           case KASETAWIDEO:
               temp = new char[sizeof(KasetaWideo)];
               plik.read(temp, sizeof(KasetaWideo));
               lista.push_back(new KasetaWideo((KasetaWideo*)temp));
               delete[] temp;
           break;
           case KASETAWIDEODVHS:
               temp = new char[sizeof(KasetaDVHS)];
               plik.read(temp, sizeof(KasetaDVHS));
               lista.push_back(new KasetaDVHS((KasetaDVHS*)temp));
               delete[] temp;
           break;
           case KASETAAUDIO:
               temp = new char[sizeof(KasetaAudio)];
               plik.read(temp, sizeof(KasetaAudio));
               lista.push_back(new KasetaAudio((KasetaAudio*)temp));
               delete[] temp;
           break;
       }
    }
    if(lista.size()>0)
        delete lista.last();
        lista.pop_back();
    }
    plik.close();
    //Sortowanie wektora po autorze i tytule
    std::sort(lista.begin(), lista.end(),
                  [](const Pozycja *a, const Pozycja *b) {
                        if((*a).getAutor().toLower()!=(*b).getAutor().toLower())
                            return (*a).getAutor().toLower() < (*b).getAutor().toLower();
                        return (*a).getTytul().toLower() < (*b).getTytul().toLower();
                    });
}

/*
    @@ Sekcja wypełniania tabeli odpowiednimi wpisami z wektora
*/

void MainWindow::wypelnijPlyty(){

    QVector<Pozycja*>::Iterator it=std::find_if(lista.begin(), lista.end(), [](const Pozycja *n){return (*n).getTyp()==PLYTACD;});
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    PlytaCD plyta;
    for(int row=0; it!=lista.end(); ++row, it=std::find_if(++it, lista.end(), [](const Pozycja *n){return (*n).getTyp()==PLYTACD;})){
                plyta = dynamic_cast<PlytaCD*>(*it);
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setData(Qt::UserRole, it-lista.begin());
                item->setData(Qt::DisplayRole, plyta.getAutor());
                ui->tableWidget->setItem(row, 0, item);
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(plyta.getTytul()));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(plyta.getDlugosc()));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(plyta.getWydawnictwo()));
                ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(plyta.getLiczbaUtworow())));
                ui->tableWidget->setItem(row, ui->tableWidget->columnCount()-1, new QTableWidgetItem(QString::number(plyta.getLiczebnosc())));
    }
}

void MainWindow::wypelnijKasetyWideo(){
    QVector<Pozycja*>::Iterator it=std::find_if(lista.begin(), lista.end(), [](const Pozycja *n){return (*n).getTyp()==KASETAWIDEO || (*n).getTyp()==KASETAWIDEODVHS;});
    ui->kaswideo_tab->clearContents();
    ui->kaswideo_tab->setRowCount(0);
    for(int row=0; it!=lista.end(); ++row, it=std::find_if(++it, lista.end(), [](const Pozycja *n){return (*n).getTyp()==KASETAWIDEO || (*n).getTyp()==KASETAWIDEODVHS;})){
        if((*it)->getTyp()==KASETAWIDEO){
                KasetaWideo kaseta = dynamic_cast<KasetaWideo*>(*it);
                ui->kaswideo_tab->setRowCount(ui->kaswideo_tab->rowCount()+1);
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setData(Qt::UserRole, it-lista.begin());
                item->setData(Qt::DisplayRole, kaseta.getAutor());
                ui->kaswideo_tab->setItem(row, 0, item);
                ui->kaswideo_tab->setItem(row, 1, new QTableWidgetItem(kaseta.getTytul()));
                ui->kaswideo_tab->setItem(row, 2, new QTableWidgetItem(kaseta.getDlugosc()));
                ui->kaswideo_tab->setItem(row, 3, new QTableWidgetItem(kaseta.getWydawnictwo()));
                ui->kaswideo_tab->setItem(row, 4, new QTableWidgetItem(this->typyKaset[kaseta.getRodzajKasety()]));
                ui->kaswideo_tab->setItem(row, 5, new QTableWidgetItem(QString("Brak")));
                ui->kaswideo_tab->setItem(row, ui->kaswideo_tab->columnCount()-1, new QTableWidgetItem(QString::number(kaseta.getLiczebnosc())));
        } else {
                KasetaDVHS kaseta = dynamic_cast<KasetaDVHS*>(*it);
                ui->kaswideo_tab->setRowCount(ui->kaswideo_tab->rowCount()+1);
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setData(Qt::UserRole, it-lista.begin());
                item->setData(Qt::DisplayRole, kaseta.getAutor());
                ui->kaswideo_tab->setItem(row, 0, item);
                ui->kaswideo_tab->setItem(row, 1, new QTableWidgetItem(kaseta.getTytul()));
                ui->kaswideo_tab->setItem(row, 2, new QTableWidgetItem(kaseta.getDlugosc()));
                ui->kaswideo_tab->setItem(row, 3, new QTableWidgetItem(kaseta.getWydawnictwo()));
                ui->kaswideo_tab->setItem(row, 4, new QTableWidgetItem(this->typyKaset[kaseta.getRodzajKasety()]));
                ui->kaswideo_tab->setItem(row, 5, new QTableWidgetItem(QString::number(kaseta.getJakosc())));
                ui->kaswideo_tab->setItem(row, ui->kaswideo_tab->columnCount()-1, new QTableWidgetItem(QString::number(kaseta.getLiczebnosc())));
        }
    }
}

void MainWindow::wypelnijKasetyAudio(){
    QVector<Pozycja*>::Iterator it=std::find_if(lista.begin(), lista.end(), [](const Pozycja *n){return (*n).getTyp()==KASETAAUDIO;});
    ui->kasaudio_tab->clearContents();
    ui->kasaudio_tab->setRowCount(0);
    KasetaAudio kaseta;
    for(int row=0; it!=lista.end(); ++row, it=std::find_if(++it, lista.end(), [](const Pozycja *n){return (*n).getTyp()==KASETAAUDIO;})){
        kaseta = dynamic_cast<KasetaAudio*>(*it);
        ui->kasaudio_tab->setRowCount(ui->kasaudio_tab->rowCount()+1);
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(Qt::UserRole, it-lista.begin());
        item->setData(Qt::DisplayRole, kaseta.getAutor());
        ui->kasaudio_tab->setItem(row, 0, item);
        ui->kasaudio_tab->setItem(row, 1, new QTableWidgetItem(kaseta.getTytul()));
        ui->kasaudio_tab->setItem(row, 2, new QTableWidgetItem(kaseta.getDlugosc()));
        ui->kasaudio_tab->setItem(row, 3, new QTableWidgetItem(kaseta.getWydawnictwo()));
        ui->kasaudio_tab->setItem(row, 4, new QTableWidgetItem(QString::number(kaseta.getCena())));
        ui->kasaudio_tab->setItem(row, ui->kasaudio_tab->columnCount()-1, new QTableWidgetItem(QString::number(kaseta.getLiczebnosc())));
    }
}

/*
    @@ Sekcja edycji wartości znajdujących się w komórkach tabelii
*/

//Edycja płytcd
void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    this->edytujElement(item, ui->tableWidget);
}

//Edycja kaset wideo
void MainWindow::on_kaswideo_tab_itemChanged(QTableWidgetItem *item)
{
    this->edytujElement(item, ui->kaswideo_tab);
}

//edycja kaset audio
void MainWindow::on_kasaudio_tab_itemChanged(QTableWidgetItem *item)
{
    this->edytujElement(item, ui->kasaudio_tab);
}

/*
    @@ Sekcja tworzenia obiektów i dodawania ich do wektora
*/

//Stworzenie obiektu typu PlytaCD
void MainWindow::on_pushButton_pressed()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() &&
       !ui->lineEdit_3->text().isEmpty() && !ui->lineEdit_5->text().isEmpty() &&
        ui->lineEdit_4->text().contains(":")){
        QVector<Pozycja*>::Iterator find = std::find_if(lista.begin(), lista.end(),
                                         [this](const Pozycja *n){
                                            return ((*n).getAutor().toLower()==ui->lineEdit->text() &&
                                                    (*n).getTytul().toLower()==ui->lineEdit_2->text() &&
                                                    (*n).getTyp()==PLYTACD);
                                            });
        if(find!=lista.end()){
                msg.setText("Pozycja już istnieje. Zwiększono jej liczebność");
                (*find)->zwiekszLiczebnosc();
        } else {
            lista.push_back(new PlytaCD(ui->lineEdit->text().toStdString().c_str(),
                                        ui->lineEdit_2->text().toStdString().c_str(),
                                        ui->lineEdit_3->text().toStdString().c_str(),
                                        ui->lineEdit_4->text().toStdString().c_str(),
                                        ui->lineEdit_5->text().toInt()
                                        ));
            msg.setText("Dodano pozycję");
            foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                widget->clear();
            }
        }
        this->on_tabWidget_tabBarClicked(0);
    } else {
        msg.setText("Uzupełnij wszystkie pola");
    }
    msg.exec();
}

//Stworzenie obiektu typu KasetaWideo
void MainWindow::on_pushButton_3_pressed()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    if(!ui->kas_autor->text().isEmpty() && ui->kas_czas->text().contains(":") &&
       !ui->kas_tytul->text().isEmpty() && !ui->kas_wydaw->text().isEmpty()){
        QVector<Pozycja*>::Iterator find = std::find_if(lista.begin(), lista.end(),
                                         [this](const Pozycja *n){
                                            return ((*n).getAutor().toLower()==ui->kas_autor->text() &&
                                                    (*n).getTytul().toLower()==ui->kas_tytul->text() &&
                                                    (*n).getTyp()==KASETAWIDEO);
                                            });
        if(find!=lista.end()){
                    msg.setText("Pozycja już istnieje. Zwiększono jej liczebność");
                    (*find)->zwiekszLiczebnosc();
        } else {
            lista.push_back(new KasetaWideo(ui->kas_autor->text().toStdString().c_str(),
                                        ui->kas_tytul->text().toStdString().c_str(),
                                        ui->kas_wydaw->text().toStdString().c_str(),
                                        ui->kas_czas->text().toStdString().c_str(),
                                        ui->comboBox->currentIndex()
                                        ));
            msg.setText("Dodano pozycję");
            foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                widget->clear();
            }
        }
    this->on_tabWidget_tabBarClicked(1);
    } else {
        msg.setText("Uzupełnij wszystkie pola");
    }
    msg.exec();
}

//Stworzenie obiektu typu KasetaDVHS
void MainWindow::on_pushButton_4_pressed()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    if(!ui->kas_autor->text().isEmpty() && ui->kas_czas->text().contains(":") &&
       !ui->kas_tytul->text().isEmpty() && !ui->kas_wydaw->text().isEmpty() &&
       !ui->kas_jakosc->text().isEmpty()){
        QVector<Pozycja*>::Iterator find = std::find_if(lista.begin(), lista.end(),
                                         [this](const Pozycja *n){
                                            return ((*n).getAutor().toLower()==ui->kas_autor->text() &&
                                                    (*n).getTytul().toLower()==ui->kas_tytul->text() &&
                                                    (*n).getTyp()==KASETAWIDEODVHS);
                                            });
        if(find!=lista.end()){
                    msg.setText("Pozycja już istnieje. Zwiększono jej liczebność");
                    (*find)->zwiekszLiczebnosc();
        } else {
            lista.push_back(new KasetaDVHS(ui->kas_autor->text().toStdString().c_str(),
                                        ui->kas_tytul->text().toStdString().c_str(),
                                        ui->kas_wydaw->text().toStdString().c_str(),
                                        ui->kas_czas->text().toStdString().c_str(),
                                        ui->comboBox->currentIndex(),
                                        ui->kas_jakosc->text().toInt()
                                        ));
            msg.setText("Dodano pozycję");
            foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                widget->clear();
            }
        }
         this->on_tabWidget_tabBarClicked(1);
    } else {
        msg.setText("Uzupełnij wszystkie pola");
    }
    msg.exec();
}

//Stworzenie obiektu typu KasetaAudio
void MainWindow::on_pushButton_6_pressed()
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Information);
    if(!ui->kasa_autor->text().isEmpty() && ui->kasa_czas->text().contains(":") &&
       !ui->kasa_tytul->text().isEmpty() && !ui->kasa_wydaw->text().isEmpty() &&
       !ui->kasa_cena->text().isEmpty()){
        QVector<Pozycja*>::Iterator find = std::find_if(lista.begin(), lista.end(),
                                         [this](const Pozycja *n){
                                            return ((*n).getAutor().toLower()==ui->kasa_autor->text() &&
                                                    (*n).getTytul().toLower()==ui->kasa_tytul->text() &&
                                                    (*n).getTyp()==KASETAAUDIO);
                                            });
        if(find!=lista.end()){
                    msg.setText("Pozycja już istnieje. Zwiększono jej liczebność");
                    (*find)->zwiekszLiczebnosc();
        } else {
            lista.push_back(new KasetaAudio(ui->kasa_autor->text().toStdString().c_str(),
                                        ui->kasa_tytul->text().toStdString().c_str(),
                                        ui->kasa_wydaw->text().toStdString().c_str(),
                                        ui->kasa_czas->text().toStdString().c_str(),
                                        ui->kasa_cena->text().toDouble()
                                        ));
            msg.setText("Dodano pozycję");
            foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                widget->clear();
            }
        }
        this->on_tabWidget_tabBarClicked(2);
    } else {
        msg.setText("Uzupełnij wszystkie pola");
    }
    msg.exec();
}

/*
    @@ Sekcja usuwania obiektów z tabeli oraz z wektora i usuwania ich z pamięci
*/

//Usuwanie Plyt CD
void MainWindow::on_pushButton_2_pressed()
{
    this->usunElement(ui->tableWidget, 0);
}

//Usuwanie kaset wideo
void MainWindow::on_pushButton_5_pressed()
{
    this->usunElement(ui->kaswideo_tab, 1);
}

//Usuwanie kaset audio
void MainWindow::on_pushButton_7_pressed()
{
    this->usunElement(ui->kasaudio_tab, 2);
}

/*
    @@ Inne sekcje wykorzystywane w innych metodach
*/

void MainWindow::usunElement(QTableWidget *tab, int tabela){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    if(!tab->selectionModel()->selection().indexes().isEmpty()){
        msgBox.setText("Czy na pewno chcesz usunąć tą pozycję z biblioteki?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setIcon(QMessageBox::Question);
        int ret = msgBox.exec();
        switch(ret){
            case QMessageBox::Yes:
                QModelIndexList index = tab->selectionModel()->selectedRows();
                std::sort(index.begin(), index.end());
                std::reverse(index.begin(), index.end());
                foreach (QModelIndex ind, index) {
                   QVariant v = tab->item(ind.row(), 0)->data(Qt::UserRole);
                   delete lista[v.toInt()];
                   lista.remove(v.toInt());

                }
                this->on_tabWidget_tabBarClicked(tabela);
            break;
        }
    } else {
        msgBox.setText("Aby usunąć jakąś pozycję, musisz ją najpierw wybrać");
        msgBox.exec();
    }
}

void MainWindow::edytujElement(QTableWidgetItem *item, QTableWidget *tab){
    if(item->isSelected()){
        QVariant v = tab->item(item->row(), 0)->data(Qt::UserRole);
        lista[v.toInt()]->edytuj(item->text(), item->column());
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==2){
        ui->groupBox_2->show();
        ui->pushButton_3->setEnabled(false);
    } else {
        ui->groupBox_2->hide();
        ui->pushButton_3->setEnabled(true);
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch(index){
    case 0:
        this->wypelnijPlyty();
        break;
    case 1:
        this->wypelnijKasetyWideo();
        //this->wypelnijKasetyDVHS();
        break;
    case 2:
        this->wypelnijKasetyAudio();
        break;
    }
}

/*
    @@ Sekcja wyszukiwania po frazie
*/

//Wyszukiwarka CD
void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    if(arg1.length()!=0){
        QVector<Pozycja*>::Iterator it = std::find_if(lista.begin(), lista.end(),
                                                        [this, &arg1](const Pozycja *n){
                                                            return ((*n).getAutor().toLower().contains(arg1.toLower()) ||
                                                                    (*n).getTytul().toLower().contains(arg1.toLower())) &&
                                                                    (*n).getTyp()==PLYTACD;});
        PlytaCD plyta;
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        for(int row=0; it!=lista.end();++row, it = std::find_if(++it, lista.end(),
            [this, &arg1](const Pozycja *n){return ((*n).getAutor().toLower().contains(arg1.toLower()) ||
            (*n).getTytul().toLower().contains(arg1.toLower())) && (*n).getTyp()==PLYTACD;}))
        {
            plyta = dynamic_cast<PlytaCD*>(*it);
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::UserRole, it-lista.begin());
            item->setData(Qt::DisplayRole, plyta.getAutor());
            ui->tableWidget->setItem(row, 0, item);
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(plyta.getTytul()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(plyta.getDlugosc()));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(plyta.getWydawnictwo()));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(plyta.getLiczbaUtworow())));
            ui->tableWidget->setItem(row, ui->tableWidget->columnCount()-1, new QTableWidgetItem(QString::number(plyta.getLiczebnosc())));
        }
    } else {
        this->on_tabWidget_tabBarClicked(0);
    }
}

//Wyszukiwarka kaset wideo i dvhs
void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    if(arg1.length()!=0){
        QVector<Pozycja*>::Iterator it = std::find_if(lista.begin(), lista.end(),
                                                        [this, &arg1](const Pozycja *n){
                                                            return ((*n).getAutor().toLower().contains(arg1.toLower()) ||
                                                                    (*n).getTytul().toLower().contains(arg1.toLower())) &&
                                                                    ((*n).getTyp()==KASETAWIDEODVHS || (*n).getTyp()==KASETAWIDEO);});
        ui->kaswideo_tab->clearContents();
        ui->kaswideo_tab->setRowCount(0);
        for(int row=0; it!=lista.end(); ++row, it = std::find_if(++it, lista.end(),
            [this, &arg1](const Pozycja *n){return ((*n).getAutor().toLower().contains(arg1.toLower()) ||
            (*n).getTytul().toLower().contains(arg1.toLower())) && ((*n).getTyp()==KASETAWIDEODVHS || (*n).getTyp()==KASETAWIDEO);}))
        {
            if((*it)->getTyp()==KASETAWIDEO){
                    KasetaWideo kaseta = dynamic_cast<KasetaWideo*>(*it);
                    ui->kaswideo_tab->setRowCount(ui->kaswideo_tab->rowCount()+1);
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setData(Qt::UserRole, it-lista.begin());
                    item->setData(Qt::DisplayRole, kaseta.getAutor());
                    ui->kaswideo_tab->setItem(row, 0, item);
                    ui->kaswideo_tab->setItem(row, 1, new QTableWidgetItem(kaseta.getTytul()));
                    ui->kaswideo_tab->setItem(row, 2, new QTableWidgetItem(kaseta.getDlugosc()));
                    ui->kaswideo_tab->setItem(row, 3, new QTableWidgetItem(kaseta.getWydawnictwo()));
                    ui->kaswideo_tab->setItem(row, 4, new QTableWidgetItem(this->typyKaset[kaseta.getRodzajKasety()]));
                    ui->kaswideo_tab->setItem(row, 5, new QTableWidgetItem(QString("Brak")));
                    ui->kaswideo_tab->setItem(row, ui->kaswideo_tab->columnCount()-1, new QTableWidgetItem(QString::number(kaseta.getLiczebnosc())));
            } else {
                    KasetaDVHS kaseta = dynamic_cast<KasetaDVHS*>(*it);
                    ui->kaswideo_tab->setRowCount(ui->kaswideo_tab->rowCount()+1);
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setData(Qt::UserRole, it-lista.begin());
                    item->setData(Qt::DisplayRole, kaseta.getAutor());
                    ui->kaswideo_tab->setItem(row, 0, item);
                    ui->kaswideo_tab->setItem(row, 1, new QTableWidgetItem(kaseta.getTytul()));
                    ui->kaswideo_tab->setItem(row, 2, new QTableWidgetItem(kaseta.getDlugosc()));
                    ui->kaswideo_tab->setItem(row, 3, new QTableWidgetItem(kaseta.getWydawnictwo()));
                    ui->kaswideo_tab->setItem(row, 4, new QTableWidgetItem(this->typyKaset[kaseta.getRodzajKasety()]));
                    ui->kaswideo_tab->setItem(row, 5, new QTableWidgetItem(QString::number(kaseta.getJakosc())));
                    ui->kaswideo_tab->setItem(row, ui->kaswideo_tab->columnCount()-1, new QTableWidgetItem(QString::number(kaseta.getLiczebnosc())));
            }
        }
    } else {
        this->on_tabWidget_tabBarClicked(1);
    }
}

//Wyszukiwarka Kasety Audio
void MainWindow::on_lineEdit_8_textChanged(const QString &arg1)
{
    if(arg1.length()!=0){
        QVector<Pozycja*>::Iterator it = std::find_if(lista.begin(), lista.end(),
                                                        [this, &arg1](const Pozycja *n){
                                                            return ((*n).getAutor().toLower().contains(arg1.toLower()) ||
                                                                    (*n).getTytul().toLower().contains(arg1.toLower())) &&
                                                                    (*n).getTyp()==KASETAAUDIO;});
        KasetaAudio kaseta;
        ui->kasaudio_tab->clearContents();
        ui->kasaudio_tab->setRowCount(0);
        for(int row=0; it!=lista.end(); ++row, it = std::find_if(++it, lista.end(),
            [this, &arg1](const Pozycja *n){return ((*n).getAutor().toLower().contains(arg1.toLower()) ||
            (*n).getTytul().toLower().contains(arg1.toLower())) && (*n).getTyp()==KASETAAUDIO;}))
        {
            kaseta = dynamic_cast<KasetaAudio*>(*it);
            ui->kasaudio_tab->setRowCount(ui->kasaudio_tab->rowCount()+1);
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::UserRole, it-lista.begin());
            item->setData(Qt::DisplayRole, kaseta.getAutor());
            ui->kasaudio_tab->setItem(row, 0, item);
            ui->kasaudio_tab->setItem(row, 1, new QTableWidgetItem(kaseta.getTytul()));
            ui->kasaudio_tab->setItem(row, 2, new QTableWidgetItem(kaseta.getDlugosc()));
            ui->kasaudio_tab->setItem(row, 3, new QTableWidgetItem(kaseta.getWydawnictwo()));
            ui->kasaudio_tab->setItem(row, 4, new QTableWidgetItem(QString::number(kaseta.getCena())));
            ui->kasaudio_tab->setItem(row, ui->kasaudio_tab->columnCount()-1, new QTableWidgetItem(QString::number(kaseta.getLiczebnosc())));
        }
    } else {
        this->on_tabWidget_tabBarClicked(2);
    }
}
