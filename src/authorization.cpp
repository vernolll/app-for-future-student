#include "include/authorization.h"

Authorization::Authorization(Ui::MainWindow *ui, QObject *parent) :
    QObject(parent),
    ui(ui)
{
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


void Authorization::on_pushButton_autoriz_clicked()
{
    QSqlDatabase db;
    //query = new QSqlQuery(db);
    query->prepare("CREATE TABLE IF NOT EXISTS Users (username TEXT PRIMARY KEY, password TEXT)");

    QString username = ui->user_name->text();
    QString password = ui->pass_word->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();

    if (query.next())
    {
        qDebug() << "Authorization successful";
        ui->stackedWidget->setCurrentWidget(ui->page_the_uni);
        db.close();
    }
    else
    {
        qDebug() << "Authorization failed";
        QMessageBox::critical(nullptr, "Error", "Invalid data.");
    }
}


void Authorization::on_pushButton_registr_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_registration);
}


bool isPasswordStrong(const QString &password)
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


void Authorization::on_pushButton_registr_2_clicked()
{
    if(ui->checkBox_agree->isChecked() && !ui->lineEdit_login->text().isEmpty() && !ui->lineEdit_password->text().isEmpty())
    {
        QString login = ui->lineEdit_login->text();
        QString password = ui->lineEdit_password->text();

        if (!isPasswordStrong(password))
        {
            //QMessageBox::warning(parent(), "Ненадежный пароль", "Пароль должен содержать не менее 8 символов и состоять из прописных и строчных букв, цифр и специальных символов.", QMessageBox::Ok);
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
            ui->stackedWidget->setCurrentWidget(ui->page_authorization);
        }
    }
}
