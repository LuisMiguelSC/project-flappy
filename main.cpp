#include "flappyproject.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlappyProject w;
    w.show();
    return a.exec();
}
