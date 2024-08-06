#include "include/general.h"

General::General(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
    window2 = new add_file;
    bachelor = new Bachelor(ui, this);
    master = new Master(ui, this);
}


extern bool is_add;


General::~General()
{
    delete ui;
    delete window2;
    delete bachelor;
}


void General::choosing_degree()
{
    bool specialitet = false;
    if (ui->radioButton_bachelor->isChecked())
    {
        bachelor->connectDatabase(specialitet);
        ui->stackedWidget->setCurrentWidget(ui->page_6_bach_spec);
    }
    else if(ui->radioButton_spec->isChecked())
    {
       specialitet = true;
       bachelor->connectDatabase(specialitet);
       ui->stackedWidget->setCurrentWidget(ui->page_6_bach_spec);

    }
    else if(ui->radioButton_master->isChecked())
    {
        master->connectDatabase();
        ui->stackedWidget->setCurrentWidget(ui->page_8_master);

    }
}


void General::add_profile_photo()
{
    window2->show();
}


void General::write_info_to_file()
{
    QString name = ui->lineEdit_name->text();
    QString sername = ui->lineEdit_sername->text();
    QString otche = ui->lineEdit_otche->text();
    QString phone = ui->lineEdit_phone->text();
    QString passport = ui->lineEdit_passport->text();


    QFile file("info.txt");

    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << "\n";
        out << sername << "\n";
        out << otche << "\n";
        out << phone << "\n";
        out << passport << "\n";
        file.close();
    }

    else
    {
        qDebug() << "Failed to open the file for writing.";
    }
    if (name!=NULL && sername != NULL && otche != NULL && phone != NULL && passport != NULL && is_add)
    {
        QMessageBox::information(nullptr, "Успех!", "Вы успешно подали заявление на поступление.");
        QCoreApplication::quit();
    }
    else
    {
        QMessageBox::warning(nullptr, "Ошибка!", "Заполните все поля.");
    }
}



void General::next_page()
{
   ui->stackedWidget->setCurrentWidget(ui->page_sport);
}


void General::back_page()
{
   ui->stackedWidget->setCurrentWidget(ui->page_the_uni);
}


void General::page_question()
{
    ui->stackedWidget->setCurrentWidget(ui->page_question);
}


void General::page_degree()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5_degree);
}


void General::closing()
{
    QCoreApplication::quit();
}


