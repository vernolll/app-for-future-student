#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("App for applicants");

    connectDatabase();
    query = new QSqlQuery(db);
    query->prepare("CREATE TABLE IF NOT EXISTS Users (username TEXT PRIMARY KEY, password TEXT)");

    ui->stackedWidget->setCurrentWidget(ui->page_authorization);

    QPixmap pix("D:/my game/qt_app/for_applicants/images/label.png");
    ui->label_pic0->setPixmap(pix.scaled(340, 340));
    QPixmap pix1("D:/my game/qt_app/for_applicants/images/university.jpg");
    ui->label_pic1->setPixmap(pix1.scaled(600, 380));
    QPixmap pix2("D:/my game/qt_app/for_applicants/images/volleyball.jpg");
    ui->label_pic2->setPixmap(pix2.scaled(700, 450));

    window2 = new add_file;
}


MainWindow::~MainWindow()
{
    delete ui;
}


















