#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>
#include <QtDebug>
#include <QSqlDatabase>
#include <QtWidgets>
#include <QMessageBox>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

namespace Ui
{
class MainWindow;
}

class Authorization : public QObject
{
    Q_OBJECT

public:
    explicit Authorization(Ui::MainWindow *ui, QObject *parent = nullptr);
    ~Authorization();

public slots:

    void data_reconciliation();

    void switching_to_registration();

    void add_a_new_user();

    bool connectDatabase();

    bool isPasswordStrong(const QString &password);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
};


#endif // AUTHORIZATION_H
