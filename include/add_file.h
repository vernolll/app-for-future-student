#ifndef ADD_FILE_H
#define ADD_FILE_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class add_file;
}

class add_file : public QDialog
{
    Q_OBJECT

public:
    explicit add_file(QWidget *parent = nullptr);
    ~add_file();

signals:
    void window2();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::add_file *ui;
    QString fileName;
};

#endif // ADD_FILE_H
