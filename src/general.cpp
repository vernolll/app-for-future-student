#include "include/mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_pushButton_3_clicked()
{

    connectDatabase1();
    // Clear the existing items in the combo box
    ui->comboBox_spec_2->clear();

    // Store code-specialty mappings
    QMap<QString, QString> specialtyMap;
    query1 = new QSqlQuery(db1);

    QStringList checkedsubs;

    // Check which subjects are checked and add them to the checked subscription list
    if(ui->checkBox_bio->isChecked())
    {
        checkedsubs.append("Биология");
    }
    if(ui->checkBox_chem->isChecked())
    {
        checkedsubs.append("Химия");
    }
    if(ui->checkBox_eng->isChecked())
    {
        checkedsubs.append("Английский");
    }
    if(ui->checkBox_lit->isChecked())
    {
        checkedsubs.append("Литература");
    }
    if(ui->checkBox_inf->isChecked())
    {
        checkedsubs.append("Информатика и ИКТ или Физика");
    }
    if(ui->checkBox_phis->isChecked())
    {
        checkedsubs.append("Информатика и ИКТ или Физика");
        checkedsubs.append("Физика");
    }
    if(ui->checkBox_geo->isChecked())
    {
        checkedsubs.append("География");
    }
    if (ui->checkBox_history->isChecked())
    {
        checkedsubs.append("История");
    }


    // Check if both Math and Russian are selected
    if (ui->checkBox_math->isChecked() && ui->checkBox_rus->isChecked() /*&& !checkedsubs.isEmpty()*/)
    {
        QString subjectPlaceholder = checkedsubs.join("','");
        subjectPlaceholder = "'" + subjectPlaceholder + "'";

        // Execute the query
        if (query1->exec("SELECT Code, Specialty FROM Specialties WHERE Subject3 IN (" + subjectPlaceholder + ")"))
        {
            qDebug() << query1->lastQuery();
            while (query1->next())
            {
                qDebug() << query1->lastQuery();
                QString code = query1->value(0).toString();
                QString specialty = query1->value(1).toString();
                ui->comboBox_spec_2->addItem(specialty, code);
            }
        }
        else
        {
            qDebug() << "Query execution error:" << query1->lastError().text();
        }
        query1->lastError();
    }
    else if (checkedsubs.isEmpty())
    {
        qDebug() << "No subjects checked.";
    }
}


void MainWindow::on_pushButton_conf_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString sername = ui->lineEdit_sername->text();
    QString otche = ui->lineEdit_otche->text();
    QString phone = ui->lineEdit_phone->text();
    QString passport = ui->lineEdit_passport->text();


    QFile file("info.txt");

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        return;
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << "\n";
        out << sername << "\n";
        out << otche << "\n";
        out << phone << "\n";
        out << passport << "\n";
        file.close();
    }

    else
    {
        qDebug() << "Failed to open the file for writing.";
    }

    QMessageBox::information(this, "Успех!", "Вы успешно подали заявление на поступление.");

    this->close();
}
