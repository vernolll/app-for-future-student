#include "include/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_pushButton_next_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_sport);
}


void MainWindow::on_pushButton_back_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_the_uni);
}


void MainWindow::on_pushButton_next_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_question);
}


void MainWindow::on_pushButton_yes_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5_degree);
}


void MainWindow::on_pushButton_no_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_add_photo_clicked()
{
    window2->show();
}
