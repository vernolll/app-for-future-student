#include "mainwindow.h"
#include "ui_mainwindow.h"


// Clear and populate profiles combobox based on selected specialty
void MainWindow::on_comboBox_spec_currentIndexChanged(int index)
{
    // Clear existing profiles
    ui->comboBox_prof->clear();

    // Get the selected specialty code
    QString selectedCode = ui->comboBox_spec->currentData().toString();

    // Fetch profiles based on the selected specialty code
    query3 = new QSqlQuery(db2);
    query3->prepare("SELECT Код, Профиль FROM Профиль WHERE Код = :specialtyCode");
    query3->bindValue(":specialtyCode", selectedCode);
    query3->exec();

    while (query3->next())
    {
        QString profile = query3->value(1).toString();
        ui->comboBox_prof->addItem(profile);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QString spec = ui->comboBox_spec->currentText();
    QString prof = ui->comboBox_prof->currentText();


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

     ui->stackedWidget->setCurrentWidget(ui->page_7_data);
}
