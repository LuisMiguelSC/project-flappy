#ifndef FLAPPYPROJECT_H
#define FLAPPYPROJECT_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class FlappyProject; }
QT_END_NAMESPACE

class FlappyProject : public QMainWindow
{
    Q_OBJECT

public:
    FlappyProject(QWidget *parent = nullptr);
    explicit FlappyProject(QWidget *parent = nullptr, const QString &selectedImagePath = QString());// añadido
    void keyPressEvent(QKeyEvent *event);
    void update();
    ~FlappyProject();
    void nextSong();
    void updateCounter();

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void flappyProjectDestroyed();

private:
    float GRAVITY = -0.2;
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

    float background_x;
    float background_2_x;
    float background_y;

    int contador;
    QLabel *label_contador;

    int score;
};
#endif // FLAPPYPROJECT_H
