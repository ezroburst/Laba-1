#include <QCoreApplication>
#include "filemanager_.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream cin(stdin), cout(stdout);
    cout<<"press the ENTER to see all the commands"<<endl;
    // Благодаря одиночке мы можем работать только с единственным экемпляром класса FileManager
        FileManager::instance().TERMINAL();

        QCoreApplication::exec();

}
