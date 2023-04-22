#include "gameover.h"
#include "ui_gameover.h"
#include "startwindow.h"

gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_returnMenu_clicked()
{
    // Crea un objeto de la ventana Game Over
    StartWindow *hola = new StartWindow();

    // Cierra y elimina la ventana actual
    this->close();
    this->deleteLater();

    // Muestra la ventana Game Over
    hola->show();

}



