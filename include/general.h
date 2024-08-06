#ifndef GENERAL_H
#define GENERAL_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QCoreApplication>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/add_file.h"
#include "include/bachelor.h"
#include "include/master.h"


namespace Ui
{
class MainWindow;
}

class Bachelor;
class Master;
class add_file;


// This class stores methods that are common to everything

class General : public QObject
{
    Q_OBJECT
public:
     explicit General(Ui::MainWindow *ui, QObject *parent = nullptr);
    ~General();


public slots:
    void choosing_degree();

    void add_profile_photo();

    void write_info_to_file();

    void next_page();

    void back_page();

    void page_question();

    void page_degree();

    void closing();

private:
    Ui::MainWindow *ui;
    add_file *window2;
    Bachelor *bachelor;
    Master *master;
    QString name, sername, otche, passport, phone;

};

#endif // GENERAL_H
