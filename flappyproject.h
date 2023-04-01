#ifndef FLAPPYPROJECT_H
#define FLAPPYPROJECT_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>

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


private:
    float GRAVITY = -0.1;
    float JUMP_VELOCITY = 4;

    Ui::FlappyProject *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    float bird_pos_y;
    float bird_vel_y;
};
#endif // FLAPPYPROJECT_H
