#include "flappyproject.h"
#include "ui_flappyproject.h"
#include <QKeyEvent>
#include <QTimer>

FlappyProject::FlappyProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyProject)
{
    ui->setupUi(this);

    // Añadimos la cancion de fondo en bucle
    player = new QMediaPlayer;
    player->setLoops(QMediaPlayer::Infinite);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/assets/sounds/default_song.mp3"));
    audioOutput->setVolume(50);
    player->play();


    // Inicializamos variables pajaro
    bird_pos_y = ui->bird->y();
    bird_vel_y = 0;

    // Inicializar la posición inicial de las tuberías
    pipe_x = ui->pipe->x();
    pipe_y = ui->pipe->y();
    top_pipe_x = ui->top_pipe->x();
    top_pipe_y = ui->top_pipe->y();

    // Inicializar la posición inicial de los fondos
    background_x = ui->background->x();
    background_2_x = ui->background_2->x();
    background_y = ui->background->y();

    // Hacemos que update() se ejecute cada 15 ms
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlappyProject::update);
    timer->start(15);
}

FlappyProject::~FlappyProject()
{
    delete ui;
}

void FlappyProject::keyPressEvent(QKeyEvent *event)
{
    /* Metodo encargado de resetear la velocidad al presionar espacio */
    if (event->key() == Qt::Key_Space) {
        bird_vel_y = JUMP_VELOCITY;
    } else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
        bird_vel_y = JUMP_VELOCITY;
    } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
        // Do nothing for now
    } else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
        ui->bird->move(ui->bird->pos().x() - 5, ui->bird->pos().y());
    } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
        ui->bird->move(ui->bird->pos().x() + 5, ui->bird->pos().y());
    }
}

void FlappyProject::update()
{
    /* Metodo encargado de ir actualizando el juego en cada frame */

    // Le añadimos la gravedad a la velocidad del pajaro actual
    bird_vel_y += GRAVITY;
    // Le restamos a la posición del pajaro la velocidad actual y lo aplicamos
    bird_pos_y -= bird_vel_y;
    ui->bird->move(ui->bird->x(), bird_pos_y);

    // Actualizar la posición de las tuberías en cada intervalo de tiempo
    pipe_x -= pipe_velocity;
    top_pipe_x -= pipe_velocity;
    ui->pipe->move(pipe_x, pipe_y);
    ui->top_pipe->move(top_pipe_x, top_pipe_y);

    background_x -= 1;
    ui->background->move(background_x, background_y);
    background_2_x -= 1;
    ui->background_2->move(background_2_x, background_y);

    // Si la tuberías se salen de la pantalla, moverla a la posición inicial
    if (pipe_x + ui->pipe->width() < 0) {
        pipe_x = this->width();
        top_pipe_x = this->width();

        pipe_height = QRandomGenerator::global()->generate() % 301 + 300; // Genera un número aleatorio entre 100 y 400

        pipe_y = pipe_height;
        top_pipe_y = pipe_height - 550;
    }

    // Movemos los dos fondos uno detrás del otro para que haga el efecto de que es uno infinito
    if (background_x + ui->background->width()< 0){
        background_x = background_2_x + ui->background_2->width();
    }

    if (background_2_x + ui->background_2->width()< 0){
        background_2_x = background_x + ui->background->width();
    }
}
