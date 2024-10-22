#include "include/bachelor.h"

Bachelor::Bachelor(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
}


Bachelor::~Bachelor()
{
    delete ui;
}


bool Bachelor::connectDatabase(bool specialitet)
{
    if(!specialitet)
    {
        db1 = QSqlDatabase::addDatabase("QSQLITE"); // Replace "QSQLITE" with your DB driver
        db1.setDatabaseName("bachelor1.db"); // Path to your database
        qDebug() << "bach";
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
        qDebug() << "spec";
        if (!db1.open()) {
            qDebug() << "Error: Unable to open database" << db1.lastError().text();
            return false;
        }

        qDebug() << "Database connected successfully.";
    }

    return true;
}


void Bachelor::sorting_of_specialties()
{
    query1 = new QSqlQuery(db1);

    // Clear the existing items in the combo box
    ui->comboBox_spec_2->clear();

    // Store code-specialty mappings
    QMap<QString, QString> specialtyMap;

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
    if (ui->checkBox_math->isChecked() && ui->checkBox_rus->isChecked() && !checkedsubs.isEmpty())
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


void Bachelor::sorting_of_profiles()
{
    // Clear existing profiles
    ui->comboBox_prof_2->clear();

    // Get the selected specialty code
    QString selectedCode = ui->comboBox_spec_2->currentData().toString();

    // Fetch profiles based on the selected specialty code
    query2 = new QSqlQuery(db1);
    query2->prepare("SELECT Code, Profile FROM Profiles WHERE Code = :specialtyCode");
    query2->bindValue(":specialtyCode", selectedCode);
    query2->exec();

    while (query2->next())
    {
        QString profile = query2->value(1).toString();
        ui->comboBox_prof_2->addItem(profile);
    }
}


void Bachelor::writing_to_a_file()
{
    QString spec = ui->comboBox_spec_2->currentText();
    QString prof = ui->comboBox_prof_2->currentText();

    QFile file("info.txt");
    if (!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << spec << "\n";
        out << prof << "\n";
        file.close();
    }

    db1.close();

    delete query1;
    delete query2;

    ui->stackedWidget->setCurrentWidget(ui->page_7_data);
}

