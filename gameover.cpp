#include "gameover.h"
#include "ui_gameover.h"
#include "startwindow.h"
#include "flappyproject.h"
#include "ui_flappyproject.h"
gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);



    //tiempo

   // QTimer* m_temporizadorSeñal = new QTimer(this);
    //connect(m_temporizadorSeñal, &QTimer::timeout, this, &FlappyProject::updateCounter);
    //temp->start(1000);
    // Actualiza cada 1 segundo
QTimer *timer = new QTimer(this);
connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
timer->start(1000);
     score = 0;
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

//Función para que muestre la puntuación final
void gameover::openpuntuacion()
{




    // Conectamos la señal de puntuacion con el slot del launcher para recibir dicha señal



}

//Funcion para que muestre el tiempo final
void gameover:: tiempo()
{


}

void gameover:: ONpuntuacion()
{


}
