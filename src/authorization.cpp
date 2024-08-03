#include "include/authorization.h"


Authorization::Authorization(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
    connectDatabase();
    query = new QSqlQuery(db);
}


Authorization::~Authorization()
{
    delete ui;
    delete query;
}


bool Authorization::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // Replace "QSQLITE" with your DB driver
    db.setDatabaseName("users.db"); // Path to your database

    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully.";
    return true;
}


void Authorization::data_reconciliation()
{
    query = new QSqlQuery(db);
    query->prepare("CREATE TABLE IF NOT EXISTS Users (username TEXT PRIMARY KEY, password TEXT)");

    QString username = ui->user_name->text();
    QString password = ui->pass_word->text();

    query->prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    query->bindValue(":username", username);
    query->bindValue(":password", password);
    query->exec();

    if (query->next())
    {
        qDebug() << "Authorization successful";
        db.close();
        ui->stackedWidget->setCurrentWidget(ui->page_the_uni);
    }
    else
    {
        qDebug() << "Authorization failed";
        QMessageBox::critical(nullptr, "Ошибка!", "Неверный логин и/или пароль.");
    }
}


void Authorization::switching_to_registration()
{
    ui->stackedWidget->setCurrentWidget(ui->page_registration);
}


bool Authorization::isPasswordStrong(const QString &password)
{
    // Check length
    if (password.length() < 8)
    {
        return false; // Minimum length
    }

    // Check for upper case, lower case, digit, and special character
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (const QChar &c : password)
    {
        if (c.isUpper())
        {
            hasUpper = true;
        }
        else if (c.isLower())
        {
            hasLower = true;
        }
        else if (c.isDigit())
        {
            hasDigit = true;
        }
        else if (!c.isSpace() && !c.isLetterOrNumber())
        {
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}


void Authorization::add_a_new_user()
{
    if(ui->checkBox_agree->isChecked() && !ui->lineEdit_login->text().isEmpty() && !ui->lineEdit_password->text().isEmpty())
    {
        QString login = ui->lineEdit_login->text();
        QString password = ui->lineEdit_password->text();

        if (!isPasswordStrong(password))
        {
            QMessageBox::warning(nullptr, "Ненадежный пароль", "Пароль должен содержать не менее 8 символов и состоять из прописных и строчных букв, цифр и специальных символов.", QMessageBox::Ok);
            qDebug() << "Ненадежный пароль";
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
            db.close();
            ui->stackedWidget->setCurrentWidget(ui->page_authorization);
        }
    }
}
