#ifndef MASTER_H
#define MASTER_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"


// This class describes the methods for the Master's degree

class Master : public QObject
{
    Q_OBJECT
public:
    explicit Master(Ui::MainWindow *ui, QObject *parent = nullptr);
    ~Master();

public slots:
    void connectDatabase();

    void sorting_profiles();

    void writing_info_to_file();

    void spec();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db2;
    QSqlQuery *query2;
};

#endif // MASTER_H
