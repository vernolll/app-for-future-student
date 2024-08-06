#include "include/master.h"

Master::Master(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
}


Master::~Master()
{
    delete ui;
}


void Master::connectDatabase()
{
    db2 = QSqlDatabase::addDatabase("QSQLITE");
    db2.setDatabaseName("master.db");

    if (!db2.open())
    {
        qDebug() << "Error: Unable to open database" << db2.lastError().text();
    }

    qDebug() << "Database connected successfully.";

    spec();
}


void Master::spec()
{
    query2 = new QSqlQuery(db2);
    // Load specialties into the combo box
    ui->comboBox_spec->clear(); // Clear existing specialties
    QMap<QString, QString> specialtyMap; // Store code-specialty mappings
    query2->exec("SELECT Код, Специальность FROM Специальности");
    while (query2->next())
    {
        QString code = query2->value(0).toString();
        QString specialty = query2->value(1).toString();
        specialtyMap.insert(code, specialty);
        ui->comboBox_spec->addItem(specialty, code); // Store the code in item data
    }
}



// Clear and populate profiles combobox based on selected specialty
void Master::sorting_profiles()
{
     query2 = new QSqlQuery(db2);

    // Clear existing profiles
    ui->comboBox_prof->clear();

    // Get the selected specialty code
    QString selectedCode = ui->comboBox_spec->currentData().toString();

    // Fetch profiles based on the selected specialty code
    query2->prepare("SELECT Код, Профиль FROM Профиль WHERE Код = :specialtyCode");
    query2->bindValue(":specialtyCode", selectedCode);
    query2->exec();

    while (query2->next())
    {
        QString profile = query2->value(1).toString();
        ui->comboBox_prof->addItem(profile);
    }
}


void Master::writing_info_to_file()
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
        delete query2;
    }

    db2.close();

    ui->stackedWidget->setCurrentWidget(ui->page_7_data);
}

