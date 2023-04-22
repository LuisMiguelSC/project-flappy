#include "startwindow.h"
#include "ui_startwindow.h"
#include "flappyproject.h"

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    // Color de fondo amarillo
    this->setStyleSheet("QWidget { background-color: rgb(255, 255, 0); }");

    // Seleccionamos el primer personaje por defecto
    applySelectedStyle(ui->button1);
    selectedImagePath = ":/assets/images/flappy_Azul.png";
    applyUnselectedStyle(ui->button2);
    applyUnselectedStyle(ui->button3);

    // Conectamos los botones a sus correspondientes funciones
    connect(ui->Inicio, &QPushButton::clicked, this, &StartWindow::openGameWindow);
    connect(ui->button1, &QPushButton::clicked, this, &StartWindow::on_button1_clicked);
    connect(ui->button2, &QPushButton::clicked, this, &StartWindow::on_button2_clicked);
    connect(ui->button3, &QPushButton::clicked, this, &StartWindow::on_button3_clicked);
}

void StartWindow::openGameWindow()
{
    /* Función para empezar la ventana de juego al darle a empezar */
    FlappyProject *flappyProject = new FlappyProject(nullptr, selectedImagePath);


    // Conectamos la señal de destruirse con el slot del launcher para recibir dicha señal
    connect(flappyProject, &FlappyProject::flappyProjectDestroyed, this, &StartWindow::onFlappyProjectDestroyed);

    // Desactivar el botón de minimizar
    flappyProject->setWindowFlags(flappyProject->windowFlags() & ~Qt::WindowMinimizeButtonHint);
    flappyProject->show();

    // Evitamos iniciar otra ventana
    disconnect(ui->Inicio, &QPushButton::clicked, this, &StartWindow::openGameWindow);

    // Cierra y elimina la ventana actual
    this->close();

}


StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::onFlappyProjectDestroyed() {
    // Función para volver a conectar el botón de Jugar tras cerrar la ventana de juego
    connect(ui->Inicio, &QPushButton::clicked, this, &StartWindow::openGameWindow);
}

void StartWindow::on_button1_clicked()
{
    // Función para poner el sprite del primer personaje
    selectedImagePath = ":/assets/images/flappy_Azul.png";
    applySelectedStyle(ui->button1);
    applyUnselectedStyle(ui->button2);
    applyUnselectedStyle(ui->button3);
}

void StartWindow::on_button2_clicked()
{
    // Función para poner el sprite del segundo personaje
    selectedImagePath = ":/assets/images/flappy_Tano.png";
    applySelectedStyle(ui->button2);
    applyUnselectedStyle(ui->button1);
    applyUnselectedStyle(ui->button3);
}

void StartWindow::on_button3_clicked()
{
    // Función para poner el sprite del tercer personaje
    selectedImagePath = ":/assets/images/flappy_Seductor.png";
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


