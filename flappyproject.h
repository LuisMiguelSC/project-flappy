#ifndef FLAPPYPROJECT_H
#define FLAPPYPROJECT_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QtGlobal>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class FlappyProject; }
QT_END_NAMESPACE

class FlappyProject : public QMainWindow
{
    Q_OBJECT

public:
    FlappyProject(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void update();
    ~FlappyProject();
    void siguienteCancion();


private:
    float GRAVITY = -0.1;
    float JUMP_VELOCITY = 4;

    Ui::FlappyProject *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    float bird_pos_y;
    float bird_vel_y;

    float pipe_x;
    float pipe_y;
    int pipe_height = QRandomGenerator::global()->generate() % 301 + 100;

    float top_pipe_x;
    float top_pipe_y;

    int pipe_velocity = 5;
};
#endif // FLAPPYPROJECT_H
