#include <QApplication>
#include "dialog.h"
#include <QSplashScreen>
#include <QPixmap>
#include <QThread>




class Producer : public QThread
{
public:
    void run() Q_DECL_OVERRIDE
    {

    }
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/image/bg.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    Producer::msleep(500);
    //wait 2 seconds
    splash.showMessage(QString("加载数据..."),Qt::AlignBottom|Qt::AlignLeft,Qt::white);
    Producer::msleep(3000);
    //wait 2 seconds
    splash.showMessage(QString("加载完成"),Qt::AlignBottom|Qt::AlignLeft,Qt::green);
    Producer::msleep(1000);
    Dialog *mainWindow = new Dialog();
    mainWindow->show();

    splash.finish(mainWindow);

    return a.exec();
}
