#include "mainwindow.h"
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


void MainWindow::on_pushButton_autoriz_clicked()
{
    QString username = ui->user_name->text();
    QString password = ui->pass_word->text();

    query->prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    query->bindValue(":username", username);
    query->bindValue(":password", password);
    query->exec();

    if (query->next())
    {
        qDebug() << "Authentication successful";
        ui->stackedWidget->setCurrentWidget(ui->page_the_uni);
        db.close();
    }
    else
    {
        qDebug() << "Authentication failed";
        QMessageBox::critical(this, "Ошибка", "Неверные данные.");
    }

}

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


bool connectDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // Replace "QSQLITE" with your DB driver
    db.setDatabaseName("users.db"); // Path to your database

    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully.";
    return true;
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->radioButton_bachelor->isChecked())
    {
        ui->stackedWidget->setCurrentWidget(ui->page_6_bach_spec);

        connectDatabase1();
    }
    else if(ui->radioButton_master->isChecked())
    {
        ui->stackedWidget->setCurrentWidget(ui->page_8_master);

        db2 = QSqlDatabase::addDatabase("QSQLITE");
        db2.setDatabaseName("master.db");

        if (!db2.open())
        {
            qDebug() << "Error: Unable to open database" << db2.lastError().text();
        }

        qDebug() << "Database connected successfully.";

        // Load specialties into the combo box
        ui->comboBox_spec->clear(); // Clear existing specialties
        QMap<QString, QString> specialtyMap; // Store code-specialty mappings
        query2 = new QSqlQuery(db2);
        query2->exec("SELECT Код, Специальность FROM Специальности");
        while (query2->next())
        {
            QString code = query2->value(0).toString();
            QString specialty = query2->value(1).toString();
            specialtyMap.insert(code, specialty);
            ui->comboBox_spec->addItem(specialty, code); // Store the code in item data
        }
    }
    else if(ui->radioButton_spec->isChecked())
    {
       ui->stackedWidget->setCurrentWidget(ui->page_6_bach_spec);
       specialitet = true;
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


void MainWindow::on_pushButton_registr_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_registration);
}


bool isPasswordStrong(const QString &password) {
    // Check length
    if (password.length() < 8) {
        return false; // Minimum length
    }

    // Check for upper case, lower case, digit, and special character
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (const QChar &c : password) {
        if (c.isUpper()) {
            hasUpper = true;
        } else if (c.isLower()) {
            hasLower = true;
        } else if (c.isDigit()) {
            hasDigit = true;
        } else if (!c.isSpace() && !c.isLetterOrNumber()) {
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}


void MainWindow::on_pushButton_registr_2_clicked()
{
    if(ui->checkBox_agree->isChecked() && !ui->lineEdit_login->text().isEmpty() && !ui->lineEdit_password->text().isEmpty())
    {
        QString login = ui->lineEdit_login->text();
        QString password = ui->lineEdit_password->text();

        if (!isPasswordStrong(password))
        {
            QMessageBox::warning(this, "Ненадежный пароль", "Пароль должен содержать не менее 8 символов и состоять из прописных и строчных букв, цифр и специальных символов.");
            return;
        }

        query->prepare("INSERT INTO Users (username, password) VALUES (:log, :pas)");
        query->bindValue(":log", login);
        query->bindValue(":pas", password);

        if (!query->exec())
        {
            qDebug() << "Error executing query:" << query->lastError().text();
        }
        else
        {
            qDebug() << "User registered successfully!";
            ui->stackedWidget->setCurrentWidget(ui->page_authorization);
        }
    }
}


void MainWindow::on_pushButton_add_photo_clicked()
{
    window2->show();
}

