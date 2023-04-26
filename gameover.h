#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QLabel>
//Para mostrar la tabla de puntuaciones
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

namespace Ui {
class gameover;
}

class gameover : public QDialog
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = nullptr);
    ~gameover();
    void ONpuntuacion();
    void tiempo(QString t);
    void openpuntuacion(QString p);
    void scoreboard();

    struct Data {
        std::string tm;
        int punt;
        bool operator<(const Data& other) const {
            return punt > other.punt;
        }
    };

private slots:
    void on_returnMenu_clicked();



private:
    Ui::gameover *ui;

    int contador;
    QLabel *label_contador;
    int score;



};


#endif // GAMEOVER_H
