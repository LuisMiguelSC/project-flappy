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
    // Crea un objeto de StarWindow
    StartWindow *new_menu = new StartWindow();

    // Cierra y elimina la ventana actual
    this->close();
    this->deleteLater();

    // Muestra la ventana
    new_menu->show();

}

//Función para que muestre la puntuación final
void gameover::openpuntuacion(QString p)
{
    ui->score->setText(p);
}

//Funcion para que muestre el tiempo final
void gameover::tiempo(QString t)
{
    ui->timer->setText(t);
}

void gameover::scoreboard(){
    std::ifstream file("scoreboard.txt");
    std::vector<Data> data;
    std::string line;
    while (std::getline(file, line)) {
        Data d;
        std::istringstream iss(line);
        std::getline(iss, d.tm, ',');
        iss >> d.punt;
        data.push_back(d);
    }
    std::partial_sort(data.begin(), data.begin() + 10, data.end());
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += std::to_string(i+1) + ".   " + "Pts:  " + std::to_string(data[i].punt) + "    Tiempo:  " + data[i].tm + "\n";
    }
    ui->textEdit->setText(QString::fromStdString(result));
}
