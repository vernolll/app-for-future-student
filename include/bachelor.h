#ifndef BACHELOR_H
#define BACHELOR_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"


// This class describes all the methods for undergraduate and specialist studies
// Since their methods are common

class Bachelor : public QObject
{
    Q_OBJECT
public:
    explicit Bachelor(Ui::MainWindow *ui, QObject *parent = nullptr);
    ~Bachelor();

public slots:
    bool connectDatabase(bool specialitet);

    void sorting_of_specialties();

    void sorting_of_profiles();

    void writing_to_a_file();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db1;
    QSqlQuery *query1;
    QSqlQuery *query2;
};

#endif // BACHELOR_H
