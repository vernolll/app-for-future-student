#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>
#include <QtDebug>
#include <QSqlDatabase>
#include <QtWidgets>
#include <QMessageBox>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class Authorization : public QObject
{
    Q_OBJECT

public:
    explicit Authorization(Ui::MainWindow *ui, QObject *parent = nullptr);

public slots:

    void on_pushButton_autoriz_clicked();

    void on_pushButton_registr_clicked();

    void on_pushButton_registr_2_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
};


bool connectDatabase();
bool isPasswordStrong(const QString &password);


#endif // AUTHORIZATION_H
