#include "add_file.h"
#include "ui_add_file.h"

add_file::add_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_file)
{
    ui->setupUi(this);
}

add_file::~add_file()
{
    delete ui;
}


void add_file::on_pushButton_add_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Open Image", ".", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    if (!fileName.isEmpty())
    {
        QPixmap pixmap(fileName);
        ui->image_label->setPixmap(pixmap.scaled(400, 300, Qt::KeepAspectRatio));
    }
}

void add_file::on_pushButton_confirm_clicked()
{
    // Define the destination directory (the folder with the application)
    QString destinationDir = QDir::currentPath(); // Gets current application directory
    QString destFileName = destinationDir + QDir::separator() + QFileInfo(fileName).fileName(); // File name for the destination

    // Copy the file to the destination directory
    if (QFile::copy(fileName, destFileName))
    {
        QFile file("info.txt");

        if (!file.exists()) {
            qDebug() << "File does not exist.";
            return;
        }

        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << destFileName << "\n";
            file.close();
        }
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to copy the file.");
    }
}
