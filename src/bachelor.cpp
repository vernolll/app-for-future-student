#include "include/mainwindow.h"
#include "ui_mainwindow.h"


bool MainWindow::connectDatabase1()
{
    if(!specialitet)
    {
        db1 = QSqlDatabase::addDatabase("QSQLITE"); // Replace "QSQLITE" with your DB driver
        db1.setDatabaseName("bachelor1.db"); // Path to your database
        if (!db1.open()) {
            qDebug() << "Error: Unable to open database" << db1.lastError().text();
            return false;
        }

        qDebug() << "Database connected successfully.";
    }

    else
    {
        db1  = QSqlDatabase::addDatabase("QSQLITE");
        db1.setDatabaseName("specialitet1.db"); // Path to your database
        if (!db1.open()) {
            qDebug() << "Error: Unable to open database" << db1.lastError().text();
            return false;
        }

        qDebug() << "Database connected successfully.";
    }

    return true;
}




void MainWindow::on_comboBox_spec_2_currentIndexChanged(int index)
{
    // Clear existing profiles
    ui->comboBox_prof_2->clear();

    // Get the selected specialty code
    QString selectedCode = ui->comboBox_spec_2->currentData().toString();

    // Fetch profiles based on the selected specialty code
    query4 = new QSqlQuery(db2);
    query4->prepare("SELECT Code, Profile FROM Profiles WHERE Code = :specialtyCode");
    query4->bindValue(":specialtyCode", selectedCode);
    query4->exec();

    while (query4->next())
    {
        QString profile = query4->value(1).toString();
        ui->comboBox_prof_2->addItem(profile);
    }

}


void MainWindow::on_pushButton_choose_clicked()
{
    QString spec = ui->comboBox_spec_2->currentText();
    QString prof = ui->comboBox_prof_2->currentText();

    QFile file("info.txt");
    if (!file.exists())
    {
        qDebug() << "File not exist.";
        return;
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << spec << "\n";
        out << prof << "\n";
        file.close();
    }

    db1.close();

    ui->stackedWidget->setCurrentWidget(ui->page_7_data);
}

