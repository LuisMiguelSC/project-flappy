#include "flappyproject.h"
#include "ui_flappyproject.h"

FlappyProject::FlappyProject(QWidget *parent, const QString &selectedImagePath)
    : QMainWindow(parent)
    , ui(new Ui::FlappyProject)

{

    ui->setupUi(this);
    this->setStyleSheet("QWidget { background-color: transparent; }");

    qDebug() << selectedImagePath;
    QPixmap birdPixmap(selectedImagePath);
    ui->bird->setPixmap(birdPixmap.scaled(ui->bird->size(), Qt::KeepAspectRatio));
    if (!birdPixmap.isNull()) {
        ui->bird->setPixmap(birdPixmap.scaled(ui->bird->size(), Qt::KeepAspectRatio));
    } else {
        qDebug() << "Error: Unable to load image from path:" << selectedImagePath;
    }


    ui->bird->resize(71, 51);
    ui->bird->move(100, 100);

    // 3 canciones, una detrás de otra
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);

    // Primera canción
    player->setSource(QUrl("qrc:/assets/sounds/first_song.mp3"));
    player->play();

    // Conectamos la señal mediaStatusChanged() a la ranura nextSong() y así controlamos la canción que se tiene en cada momento
    QObject::connect(player, &QMediaPlayer::mediaStatusChanged, this, &FlappyProject::nextSong);

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

    // Ponemos el contador
    contador = 0;

    // Creamos un temporizador para actualizar el contador periódicamente
    QTimer* temp = new QTimer(this);
    connect(temp, &QTimer::timeout, this, &FlappyProject::updateCounter);
    temp->start(1000); // Actualiza cada 1 segundo

    // El juego termina en el 5:52 aprox.

    score = 0;

    // Conectamos el evento de inicio del juego al método iniciar_juego() (esto para cuando le demos al botón de iniciar)
    //connect(boton_iniciar_juego, &QPushButton::clicked, this, &Juego::iniciar_juego);

    // Luego también podemos poner que cuando se termine el juego se pare el contador (ya sea por colisión o por final) y que se muestre una pantallita
    // indicando el tiempo que se ha sobrevivido y la puntuación (número de tubos atravesados con éxito)
}

FlappyProject::~FlappyProject()
{
    delete ui;
}

void FlappyProject::closeEvent(QCloseEvent *event)
{
    emit flappyProjectDestroyed(); // Emitir la señal antes de cerrar

    delete player; // Libera la memoria ocupada por el objeto QMediaPlayer
    delete audioOutput; // Libera la memoria ocupada por el objeto QAudioOutput

    QMainWindow::closeEvent(event); // Llamar a la función closeEvent de la clase base
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

    // Si la tuberías se salen de la pantalla, moverla a la posición inicial. Añadimos uno a la puntuación.
    if (pipe_x + ui->pipe->width() < 0) {
        pipe_x = this->width();
        top_pipe_x = this->width();

        pipe_height = QRandomGenerator::global()->generate() % 301 + 300; // Genera un número aleatorio entre 100 y 400

        pipe_y = pipe_height;
        top_pipe_y = pipe_height - 550;

        score++;
        QString score_str = QString::number(score);
        ui->score->setText(score_str);
    }

    // Movemos los dos fondos uno detrás del otro para que haga el efecto de que es uno infinito
    if (background_x + ui->background->width()< 0){
        background_x = background_2_x + ui->background_2->width();
    }

    if (background_2_x + ui->background_2->width()< 0){
        background_2_x = background_x + ui->background->width();
    }

    //qDebug() << "Bird height:" << ui->bird->pos().y();

    // Movemos los dos fondos uno detrás del otro para que haga el efecto de que es uno infinito
    if (background_x + ui->background->width()< 0){
        background_x = background_2_x + ui->background_2->width();
    }

    if (background_2_x + ui->background_2->width()< 0){
        background_2_x = background_x + ui->background->width();
    }
    //Si el pajaro se sale de la pantalla se detiene el juego
    if (bird_pos_y + ui->bird->width() < 0  || bird_pos_y+ui->bird->width() > ui->background->height()){
        qDebug()<<"Limites imagen";
    }

    if((bird_pos_y + ui->bird->width() >pipe_y)  &&( 100 + ui->bird->width() >pipe_x )){
        qDebug()<<"Colision";
    }

    if((bird_pos_y + ui->bird->width() >top_pipe_y)  &&( 100 + ui->bird->width() >top_pipe_x )){
        qDebug()<<"Colision";
    }


    //Se reinicia el contador

    //contador=0;
    // QTime tiempo(0, 0);
    //tiempo = tiempo.addSecs(contador);
    // QString tiempo_str;
    // tiempo_str = tiempo.toString("m:ss");
    // label_contador->setText(tiempo_str);

    // ui->bird->move(100, 100);

    //bird_pos_y = ui->bird->y();
    // ui->pipe->move(pipe_x, pipe_y);
    // ui->top_pipe->move(top_pipe_x, top_pipe_y);
    // pipe_x = ui->pipe->x();
    // pipe_y = ui->pipe->y();
    //top_pipe_x = ui->top_pipe->x();
    //top_pipe_y = ui->top_pipe->y();
    // }

}



void FlappyProject::nextSong() // Para pasar de una canción a otra
{
    if (player->mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        QString nextSong;
        // Determina la siguiente canción según la canción actual
        if (player->source() == QUrl("qrc:/assets/sounds/first_song.mp3"))
            nextSong = "qrc:/assets/sounds/second_song.mp3"; // Segunda canción
        else
            nextSong = "qrc:/assets/sounds/third_song.mp3"; // Tercera canción
        // Cambia a la siguiente canción y la reproduce
        player->setSource(QUrl(nextSong));
        player->play();
        pipe_velocity = pipe_velocity+3; // Aumentamos la velocidad al cambiar de canción (se pasa al siguiente nivel)
    }
}

void FlappyProject::updateCounter()
{
    contador++;
    QTime tiempo(0, 0);
    tiempo = tiempo.addSecs(contador);
    QString tiempo_str;
    tiempo_str = tiempo.toString("m:ss");
    ui->timer->setText(tiempo_str);
}
