#include "flappyproject.h"
#include "ui_flappyproject.h"
#include <QKeyEvent>
#include <QTimer>

FlappyProject::FlappyProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyProject)
{
    ui->setupUi(this);
    bird_pos_y = ui->bird->y();
    bird_vel_y = 0;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlappyProject::update);
    timer->start(15);
}

FlappyProject::~FlappyProject()
{
    delete ui;
}

/* PARA MOVERSE CON WASD
void FlappyProject::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
            ui->label->move(ui->label->pos().x(), ui->label->pos().y() - 5);
            break;
        case Qt::Key_A:

            break;
        case Qt::Key_S:
            ui->label->move(ui->label->pos().x(), ui->label->pos().y() + 5);
            break;
        case Qt::Key_D:
            ui->label->move(ui->label->pos().x() + 5, ui->label->pos().y());
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
*/

void FlappyProject::keyPressEvent(QKeyEvent *event)
{
    /* Metodo encargado de resetear la velocidad al presionar espacio */
    if (event->key() == Qt::Key_Space) {
        bird_vel_y = JUMP_VELOCITY;
        qDebug() << "Space bar pressed";
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

}
