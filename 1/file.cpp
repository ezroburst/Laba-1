#include "file.h"
#include "shop.h"
#include "sub.h"

#include <QTextStream>
#include <QFileInfo>
#include <thread>
#include <QTimer>

FileCheck::~FileCheck()
{
    for (const auto& it : subscribers)
        delete it;

    for (const auto& it : shops)
        delete it;
}

FileCheck& FileCheck::instance()
{
    static FileCheck obj;
    return obj;
}

void FileCheck::printshop()
{
    QTextStream(stdout) << "\tshopS" << endl;
    qint32 i = 0;

    for (const auto&shop : shops)
        QTextStream(stdout) << "\t" << i++ << "      " << shop->getName() << endl;
}

void FileCheck::printSubscribers()
{
    QTextStream(stdout) << "\tSUBSCRIBERS" << endl;
    qint32 i = 0;

    for (const auto& subscriber : subscribers)
        QTextStream(stdout) << "\t" << i++ << "      " << subscriber->getName() << endl;
}
 QTextStream cin(stdin), cout(stdout);
void FileCheck:: add_subscriber()
{
    QString name;
    bool isAdd = false;//флаг сдежит за разрешением на добавление

    // Блок добавление подписчика
    while (!isAdd)
    {
        cout << '\t' << "Input subscriber: " << flush;
        name = cin.readLine();
        isAdd = true;

        // цикл по всем существующим подписчикам
        for (const auto& it : subscribers)
        {
            // Если такой подписчик уже существует, то нужно ввести другое имя
            if (it->getName() == name)
            {
                cout << "\t" << name << " no!" << endl;
                isAdd = false;
                break;
            }
        }

        // можем добавить, вызываем сигрнал
        if (isAdd)
            emit addSubscriber(name);
    }

    // выход

}


void FileCheck:: add_shop()
{
    QString path;
    bool isAdd = false;

    // Блок добавления журнала
    while (!isAdd)
    {
        cout << '\t' << "Input shop: " << flush;
        path = cin.readLine();
        isAdd = true;

        for (const auto& it : shops)
        {
           if (it->getName() == path)
            {
                cout << "\t" << path << " exists!" << endl;
                isAdd = false;
                break;
            }
        }

        // Если путь не пустой
        if (!path.isEmpty() && isAdd)
        {
            emit addshop(path);
            isAdd = true;
        }
    }
}
void FileCheck::connect()
{
    bool isConnect = false;

    // Функции, которые выводят подписчиков и журналы
    this->printshop();
    this->printSubscribers();
    // Если список журналов пуст, то переходим на новую итерацию
     if (shops.isEmpty())
     {
         cout << "\tNO shopS!" << endl;
         return;
     }

     if (subscribers.isEmpty())
     {
         cout << "\tNO SUBSCRIBERS!" << endl;
         return;
     }

    // Блок связывания журнала и подписчика
     while (!isConnect)
       {
        qint32 idshop, idSubscriber;

        cout << "\tInput ID magazine which you want to connect: " << flush;

        idshop = cin.readLine().toInt();

        cout << "\tInput ID subscriber which you want to connect: " << flush;

        idSubscriber = cin.readLine().toInt();

        // Если ввели правильные IDs, то выполняем
        if ((idshop >= 0 && idshop < shops.size()) && (idSubscriber >= 0 && idSubscriber < subscribers.size()))
        {
            // Если подписчик не подписан, то подписываем его на журнал ( чтобы подписчик был подписан только на один журнал )
            if (!subscribers[idSubscriber]->subscribe())
            {
                // Вызываем сигнал связывания
                emit connect(idshop, idSubscriber);
                isConnect = true;
            }
            // Если подписчик уже подписан, то говорим об этом
            else
                cout << "\tSubscriber " << subscribers[idSubscriber]->getName() << " already a subscriber! " << subscribers[idSubscriber]->getshop() << endl;
        }
        else
        {
            cout << "\t" << "Error connect!" << endl;
        }
    }
}
void FileCheck::list()
{
    // Если список журналов не пуст, то выводим их
    if (!shops.isEmpty())
    {
        this->printshop();
    }
    else
    {
        cout << "\tNO shopS!" << endl;
    }

    // Если список подписчиков не пуст, то выводим их
    if (!subscribers.isEmpty())
    {
        this->printSubscribers();
    }
    else
    {
        cout << "\tNO SUBSCRIBERS!" << endl;
    }
}
void FileCheck::size()
{
    bool isSize = false;

    // Если подписчики есть
    if (!subscribers.isEmpty())
    {
        this->printSubscribers();

        // Блок вывода размера журнала, на который подписан подписчик
        while (!isSize)
        {
            cout << "\tEnter the id of the subscriber from whom you want to find out the size of shop: " << flush;

            qint32 idSubscriber = cin.readLine().toInt();

            // Если ввели верный ID, то выполняем
            if (idSubscriber >= 0 && idSubscriber < subscribers.size())
            {
                // Если подписчик подписан на журнал, то выводим размер журнала, на который он подписан
                if (subscribers[idSubscriber]->subscribe())
                {
                    cout << "\t\tSize is " << QFileInfo(subscribers[idSubscriber]->getshop()).size() << " byte" << endl;
                    isSize = true;
                }
                else
                {
                    cout << "\t\tSubscriber has not shop!" << endl;
                    break;
                }
            }
            else
            {
                cout << "\t\tWrong id!" << endl;
            }
        }
    }
    else
    {
        cout << "\tNO SUBSCRIBES!" << endl;
    }
}
void FileCheck::delete_shop()
{
    // Если список журналов пуст, то переходим на новую итерацию
    if (shops.isEmpty())
    {
        cout << "\tNO shopS!" << endl;
        return;;
    }

    this->printshop();

    cout << "\t\tInput number shop which you want to delete: " << flush;

    bool isDelete = false;

    // Блок удаления журнала из вектора ( массива )
    while (!isDelete)
    {
        // toInt из QString делает Int
        qint32 idshop = cin.readLine().toInt();

        // Если введённый ID существует, то выполняем
        if (idshop >= 0 && idshop < shops.size())
        {
            // Вызываем синал удаления журнала
            emit deleteshop(idshop);

            isDelete = true;
        }
    }
}
void FileCheck::delete_subscriber()
{
    if (subscribers.isEmpty())
    {
        cout << "\tNO SUBSCRIBES!" << endl;
        return;
    }

    this->printSubscribers();

    cout << "\t\tInput number of subcriber which you want to delete: " << flush;

    bool isDelete = false;

    // Блок удаления подписчика
    while (!isDelete)
    {
        qint32 idSubscriber = cin.readLine().toInt();

        // Если ID существует, то выполняем
        if (idSubscriber >= 0 && idSubscriber < subscribers.size())
        {
            // Вызываем сигнал удаления подписчика
            emit deleteSubscriber(idSubscriber);

            isDelete = true;
        }
    }
}
void FileCheck::get_counter()
{
    if (shops.isEmpty())
    {
        cout << "\tNO shopS!" << endl;
        return;
    }

    this->printshop();

    cout << "\t\tInput number shop which you want to know counter: " << flush;

    bool isCounter = false;

    // Блок возврата количества подписчиков у журнала
    while (!isCounter)
    {
        qint32 idshop = cin.readLine().toInt();

        if (idshop >= 0 && idshop < shops.size())
        {
            // Вызываем сигнал, который выведет число подписчиков у журнала
            emit getCounter(idshop);

            isCounter = true;
        }
    }
}
void FileCheck::resign()
{
    if (subscribers.isEmpty())
    {
        cout << "\tNO SUBSCRIBERS!" << endl;
        return;
    }

    if (shops.isEmpty())
    {
        cout << "\tNO shopS!" << endl;
        return;
    }

    this->printshop();
    this->printSubscribers();

    cout << "\t\tInput number subscriber which you want to re-sign: " << flush;

    bool isResign = false;

    // Блок переподписки
    while(!isResign)
    {
        qint32 idSubscriber = cin.readLine().toInt();

        if (idSubscriber >= 0 && idSubscriber < subscribers.size())
        {
            cout << "\t\tInput the idshop which you want to subscribe to: " << flush;

            qint32 idshop = cin.readLine().toInt();

            if (idshop >= 0 && idshop < shops.size())
            {
                // Вызываем сигнал переподписки
                emit resign(idSubscriber, idshop);

                isResign = true;
            }
        }
    }
}
void FileCheck::TERMINAL()
{

   // QFile data("1.txt");
  //  QTextStream cin(&data);

int a=0;
    while(a=0)
    {
       QString command;
       bool isCommand = false;

        // Блок отвечающий за ввод команд
        while (!isCommand)
        {
            // Выводим пользователю приглашение ввести команду ( flush - позволяет очистить буфер, чтобы вывести текст )
            cout << "Go to command: " << flush;
            // Считываем строкУ
           // command="add subscriber";
            command = cin.readLine();
            // Ищем в векторе команд введёную с консоли команду, если нашли флаг в true
            if(std::find(com.begin(), com.end(), command) != com.end())
            {
                isCommand = true;
            }
            else
            {
                isCommand = false;
            }

            // Если мы не нашли команду , то выходим и заново в цикл ожидать команду
            if (!isCommand && command.isEmpty())
            {
                break;
            }
        }

        // add subscriber

        if (command == com[0])
        {

        add_subscriber();
            // выход
            continue;
        }

        // add shop
        if (command == com[1])
        {
            add_shop();

            continue;
        }

        // connect
        if (command == com[2])
        {

connect();
            continue;
        }

        // list
        if (command == com[3])
        {

list();
            continue;
        }

        // size
        if (command == com[4])
        {

size();
            continue;
        }

        // deleteshop
        if (command == com[5])
        {

delete_shop();
            continue;
        }

        // delete subscriber
        if (command == com[6])
        {

delete_subscriber();
            continue;
        }

        // get counter
        if (command == com[7])
        {
            get_counter();

            continue;
        }

        // resign ( переподписка )
        if (command == com[8])
        {

resign();
            continue;
        }

    }
}

FileCheck::FileCheck() :
    QObject(nullptr),
    com({
        "add subscriber",
        "add shop",
        "connect",
        "list",
        "size",
        "delete shop",
        "delete subscriber",
        "get counter",
        "resign",
        })
{
    // Связываем сигнал добавления журнала с лямбда-функцией
    QObject::connect(this, &FileCheck::addshop, [&](const QString& path)
        {
            // Если журнал(путь) существует и он файл
            if (QFileInfo(path).exists() && QFileInfo(path).isFile())
            {
                shops.push_back(new Shop(path));
                QTextStream(stdout) << "\t\tshop " << path << " was added!" << endl;
            }
            else
            {
                QTextStream(stdout) << "\t\tPath to shop was not added!" << endl;
            }
        });

    QObject::connect(this, &FileCheck::addSubscriber, [&](const QString& name)
        {
            if (!name.isEmpty())
            {
                subscribers.push_back(new Subscriber(name));
                QTextStream(stdout) << "\t\tSubscriber " << name << " was added!" << endl;
            }
            else
            {
                QTextStream(stdout) << "\t\tSubscriber was not added!" << endl;
            }
        });

    QObject::connect(this, &FileCheck::connect, [&](const qint32& idshop, const qint32& idSubscriber)
        {
            // Если выбранный подписчик не подписан, то выполняем
            if (!subscribers[idSubscriber]->subscribe())
            {
                // Обращаемся к журналу, на который хотим подписаться и добавляем ему подписчика
                shops[idshop]->addSubscriber(subscribers[idSubscriber]);
                // Добавляем подписчику журнал
                subscribers[idSubscriber]->getshop() = shops[idshop]->getName();

                // Выставляем подписчику флаг, что он был подписан
                subscribers[idSubscriber]->subscribe() = true;

                QTextStream(stdout) << "\t\t" << shops[idshop]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
            }
            else
            {
                QTextStream(stdout) << "\t\tConnection error!" << endl;
            }
        });

    QObject::connect(this, &FileCheck::deleteshop, [&](const qint32& index)
        {
            for (qint32 i = 0; i < shops.size(); ++i)
            {
                // Находим нужный индекс журнала, который надо удалить
                if (i == index)
                {
                    QTextStream(stdout) << "\t\t" <<shops[i]->getName() << " was deleted!" << endl;

                    // Проходимся по всем подписчикам, и удаляем у этих подписчиков этот журнал
                    for (const auto& subscriber : shops[i]->getSubscribers())
                    {
                        subscriber->getshop().clear();
                        subscriber->subscribe() = false;
                    }

                    // Удаляем журнал из вектора ( массива )
                    shops.remove(i);

                    break;
                }
            }
        });

    QObject::connect(this, &FileCheck::deleteSubscriber, [&](const qint32& index)
        {
            for (qint32 i = 0; i < subscribers.size(); ++i)
            {
                // Ищем индекс нужного подписчика, которого надо удалить
                if (i == index)
                {
                    QTextStream(stdout) << "\t\t" << subscribers[i]->getName() << " was deleted!" << endl;

                    // Проходим по списку журналов
                    for (qint32 iMag = 0; iMag < shops.size(); ++iMag)
                    {
                        // Ищем у каждого журнала нашего подписчика
                        for (qint32 iSub = 0; iSub < shops[iMag]->getSubscribers().size(); ++iSub)
                        {
                            // Если мы нашли нашего подписчика у журнала, то выполняем
                            if (subscribers[index]->getName() == shops[iMag]->getSubscribers()[iSub]->getName())
                            {
                                // Удаляем у журнала этого подписчика
                                shops[iMag]->getSubscribers().remove(iSub);
                                shops[iMag]->getCounter()--;
                            }
                        }
                    }

                    // Удаляем подписчика из вектора ( массива )
                    subscribers.remove(i);

                    break;
                }
            }
        });

    QObject::connect(this, &FileCheck::getCounter, [&](const qint32& index)
        {
            for (qint32 i = 0; i < shops.size(); ++i)
            {
                // Находим нужный индекс магазина
                if (i == index)
                {
                    QTextStream(stdout) << "\t\tCounter " << shops[i]->getName() << " is equal " << shops[i]->getCounter() << endl;
                    break;
                }
            }
        });

    QObject::connect(this, &FileCheck::resign, [&](const qint32& idSubscriber, const qint32& idshop)
        {
            for (qint32 i = 0; i < subscribers.size(); ++i)
            {
                // Находим ID подписчика, которого надо переподписать
                if (i == idSubscriber)
                {
                    // Если подписчик ещё не подписан, то выполняем
                    if (!subscribers[idSubscriber]->subscribe())
                    {
                        QTextStream(stdout) << "\t\tThe subscriber is not subscribed yet!" << endl;
                    }
                    else
                    {
                        // Проходим по всем журналам
                        for (qint32 mag = 0; mag < shops.size(); ++mag)
                        {
                            // Если нашли нужный журнал, то удаляем из подписки этого подписчика
                            if (shops[mag]->getName() == subscribers[idSubscriber]->getshop())
                            {
                                for (qint32 sub = 0; sub < shops[mag]->getSubscribers().size(); ++sub)
                                {
                                    if (shops[mag]->getSubscribers()[sub]->getName() == subscribers[idSubscriber]->getName())
                                    {
                                        shops[mag]->getSubscribers().remove(sub);
                                        shops[mag]->getCounter()--;
                                    }
                                }
                            }
                        }

                        // Здесь подписываем на новый журнал
                        shops[idshop]->addSubscriber(subscribers[idSubscriber]);
                        subscribers[idSubscriber]->getshop() = shops[idshop]->getName();
                        subscribers[idSubscriber]->subscribe() = true;

                        QTextStream(stdout) << "\t\t" << shops[idshop]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
                    }
                }
            }
        });

}

