#include "startwindow.h"
#include "ui_startwindow.h"
#include "flappyproject.h"

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget { background-color: rgb(255, 255, 0); }");
    connect(ui->Inicio, &QPushButton::clicked, this, &StartWindow::openGameWindow);

    applySelectedStyle(ui->button1);
    selectedImagePath = ":/assets/images/flappy_Azul.png";
    applyUnselectedStyle(ui->button2);
    applyUnselectedStyle(ui->button3);

    connect(ui->button1, &QPushButton::clicked, this, &StartWindow::on_button1_clicked);
    connect(ui->button2, &QPushButton::clicked, this, &StartWindow::on_button2_clicked);
    connect(ui->button3, &QPushButton::clicked, this, &StartWindow::on_button3_clicked);
}
void StartWindow::openGameWindow()
{
    FlappyProject *flappyProject = new FlappyProject(this,selectedImagePath);
    flappyProject->show();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_button1_clicked()
{
    selectedImagePath = ":/assets/images/flappy_Azul.png";
    qDebug("Se hizo clic en button1");
    applySelectedStyle(ui->button1);
    applyUnselectedStyle(ui->button2);
    applyUnselectedStyle(ui->button3);
}

void StartWindow::on_button2_clicked()
{
    selectedImagePath = ":/assets/images/flappy_Tano.png";
    qDebug("Se hizo clic en button2");
    applySelectedStyle(ui->button2);
    applyUnselectedStyle(ui->button1);
    applyUnselectedStyle(ui->button3);
}

void StartWindow::on_button3_clicked()
{
    selectedImagePath = ":/assets/images/flappy_Seductor.png";
    qDebug("Se hizo clic en button3");
    applySelectedStyle(ui->button3);
    applyUnselectedStyle(ui->button1);
    applyUnselectedStyle(ui->button2);
}

void StartWindow::applySelectedStyle(QPushButton *button) {
    button->setStyleSheet("border: 2px solid red;");
}

void StartWindow::applyUnselectedStyle(QPushButton *button) {
    button->setStyleSheet("border: none;");
}


