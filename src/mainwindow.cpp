#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("App for applicants");

    stackedWidget = ui->stackedWidget;
    authorization = new Authorization(ui);
    general = new General(ui);
    bachelor = new Bachelor(ui);
    master = new Master(ui);

    connect(this, SIGNAL(on_pushButton_autoriz_clicked()), authorization, SLOT(data_reconciliation()));
    connect(this, SIGNAL(on_pushButton_registr_clicked()), authorization, SLOT(switching_to_registration()));
    connect(this, SIGNAL(on_pushButton_registr_2_clicked()), authorization, SLOT(add_a_new_user()));
    connect(this, SIGNAL(on_pushButton_2_clicked()), general, SLOT(choosing_degree()));
    connect(this, SIGNAL(on_pushButton_add_photo_clicked()), general, SLOT(add_profile_photo()));
    connect(this, SIGNAL(on_pushButton_conf_clicked()), general, SLOT(write_info_to_file()));
    connect(this, SIGNAL(on_pushButton_3_clicked()), bachelor, SLOT(sorting_of_specialties()));
    connect(this, SIGNAL(on_comboBox_spec_2_currentIndexChanged(int)), bachelor, SLOT(sorting_of_profiles()));
    connect(this, SIGNAL(on_pushButton_choose_clicked()), bachelor, SLOT(writing_to_a_file()));
    connect(this, SIGNAL(on_comboBox_spec_currentIndexChanged(int)), master, SLOT(sorting_profiles()));
    connect(this, SIGNAL(on_pushButton_4_clicked()), master, SLOT(writing_info_to_file()));
    connect(this, SIGNAL(on_pushButton_next_clicked()), general, SLOT(next_page()));
    connect(this, SIGNAL(on_pushButton_back_clicked()), general, SLOT(back_page()));
    connect(this, SIGNAL(on_pushButton_next_2_clicked()), general, SLOT(page_question()));
    connect(this, SIGNAL(on_pushButton_yes_clicked()), general, SLOT(page_degree()));
    connect(this, SIGNAL(on_pushButton_no_clicked()), general, SLOT(closing()));

    ui->stackedWidget->setCurrentWidget(ui->page_authorization);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete authorization;
    delete general;
    delete bachelor;
    delete master;
    delete stackedWidget;
}
