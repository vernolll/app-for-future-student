#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "include/add_file.h"
#include "include/authorization.h"
#include "include/general.h"
#include "include/bachelor.h"
#include "include/master.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Authorization;
class General;
class Bachelor;
class Master;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

    void on_pushButton_autoriz_clicked();

    void on_pushButton_registr_clicked();

    void on_pushButton_registr_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_add_photo_clicked();

    void on_pushButton_conf_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_spec_2_currentIndexChanged(int index);

    void on_pushButton_choose_clicked();

    void on_comboBox_spec_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_next_2_clicked();

    void on_pushButton_yes_clicked();

    void on_pushButton_no_clicked();


private:
    Ui::MainWindow *ui;

    QStackedWidget *stackedWidget;
    Authorization *authorization;
    General *general;
    Bachelor *bachelor;
    Master *master;
};

#endif // MAINWINDOW_H
