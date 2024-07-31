#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "add_file.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_next_2_clicked();

    void on_pushButton_yes_clicked();

    void on_pushButton_no_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    bool connectDatabase1();

    void on_pushButton_conf_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_spec_currentIndexChanged(int index);

    void on_comboBox_spec_2_currentIndexChanged(int index);


    void on_pushButton_choose_clicked();

    void on_pushButton_registr_clicked();

    void on_pushButton_registr_2_clicked();

    void on_pushButton_add_photo_clicked();

    void on_pushButton_autoriz_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlDatabase db1;
    QSqlDatabase db2;
    QSqlQuery *query;
    QSqlQuery *query1;
    QSqlQuery *query2;
    QSqlQuery *query3;
    QSqlQuery *query4;
    QSortFilterProxyModel *proxyModel;
    add_file *window2;

    int row;
    bool choosed;
    bool specialitet;
};

bool connectDatabase();
bool connectDatabase1();

#endif // MAINWINDOW_H
