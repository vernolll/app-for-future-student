/********************************************************************************
** Form generated from reading UI file 'add_file.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_FILE_H
#define UI_ADD_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_add_file
{
public:
    QLabel *image_label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_confirm;

    void setupUi(QDialog *add_file)
    {
        if (add_file->objectName().isEmpty())
            add_file->setObjectName(QString::fromUtf8("add_file"));
        add_file->resize(400, 300);
        image_label = new QLabel(add_file);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setGeometry(QRect(60, 40, 261, 141));
        widget = new QWidget(add_file);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(160, 210, 95, 64));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_add = new QPushButton(widget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));

        verticalLayout->addWidget(pushButton_add);

        pushButton_confirm = new QPushButton(widget);
        pushButton_confirm->setObjectName(QString::fromUtf8("pushButton_confirm"));

        verticalLayout->addWidget(pushButton_confirm);


        retranslateUi(add_file);

        QMetaObject::connectSlotsByName(add_file);
    } // setupUi

    void retranslateUi(QDialog *add_file)
    {
        add_file->setWindowTitle(QCoreApplication::translate("add_file", "Dialog", nullptr));
        image_label->setText(QString());
        pushButton_add->setText(QCoreApplication::translate("add_file", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        pushButton_confirm->setText(QCoreApplication::translate("add_file", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_file: public Ui_add_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_FILE_H
