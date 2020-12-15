#include "filemanager_.h"
#include "magazine_.h"
#include "subscriber_.h"

#include <QTextStream>
#include <QFileInfo>
#include <thread>
#include <QTimer>

FileManager::~FileManager()
{
    for (const auto& it : subscribers)
        delete it;

    for (const auto& it : magazines)
        delete it;
}

FileManager& FileManager::instance()
{
    static FileManager obj;
    return obj;
}

void FileManager::printMagazines()
{
    QTextStream(stdout) << "\tMAGAZINES" << endl;
    qint32 i = 0;

    for (const auto& magazine : magazines)
        QTextStream(stdout) << "\t" << i++ << " ---> " << magazine->getName() << endl;
}

void FileManager::printSubscribers()
{
    QTextStream(stdout) << "\tSUBSCRIBERS" << endl;
    qint32 i = 0;

    for (const auto& subscriber : subscribers)
        QTextStream(stdout) << "\t" << i++ << " ---> " << subscriber->getName() << endl;
}

void FileManager::TERMINAL()
{
    QTextStream cin(stdin), cout(stdout);

    forever
    {
       QString command;
       bool isCommand = false;

        // Блок отвечающий за ввод команд
        while (!isCommand)
        {
            // Выводим пользователю приглашение ввести команду ( flush - позволяет очистить буфер, чтобы вывести текст )
            cout << "Input the command: " << flush;
            // Считываем строкУ
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

            // Если мы не нашли команду , то мы выводим окно подсказки команд
            if (!isCommand && command.isEmpty())
            {
                // Разделяем список команд по \n
                QStringList help = QString("Add subscriber - added subscriber\nAdd magazine - added magazine\nConnect - connections subscriber with magazine\nList - list of subscribers and magazines\nDelete magazine - delete magazine\nSize magazine\nDelete Subscriber - delete subscriber\nGet counter - to know size of subscribers by magazine\nResign - change magazine\n").split('\n');
                // Цикл foreach позволяем пройтись по всем элементам help и вывести каждую команду
                foreach(const auto & it, help)
                {
                    cout << '\t' << it << endl;
                }
                isCommand = true;
            }
        }

        // add subscriber
        if (command == com[0])
        {
            QString name;
            bool isAdd = false;

            // Блок добавление подписчика
            while (!isAdd)
            {
                cout << '\t' << "Input subscriber: " << flush;
                name = cin.readLine();
                isAdd = true;

                // Проходимся по всем подписчикам
                for (const auto& it : subscribers)
                {
                    // Если такой подписчик уже существует, то мы об этом уведомим пользователя и
                    //не добавим его(имя другое ввести необходимо)
                    if (it->getName() == name)
                    {
                        cout << "\t" << name << " exists!" << endl;
                        isAdd = false;
                        break;
                    }
                }

                // Если мы можем добавить пользователя, то вызываем сигнал
                if (isAdd)
                    emit addSubscriber(name);
            }

            // Переход на следующий цикл
            continue;
        }

        // add magazine
        if (command == com[1])
        {
            QString path;
            bool isAdd = false;

            // Блок добавления журнала
            while (!isAdd)
            {
                cout << '\t' << "Input magazine: " << flush;
                path = cin.readLine();
                isAdd = true;

                for (const auto& it : magazines)
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
                    emit addMagazine(path);
                    isAdd = true;
                }
            }

            continue;
        }

        // connect
        if (command == com[2])
        {
            bool isConnect = false;

            // Функции, которые выводят подписчиков и журналы
            this->printMagazines();
            this->printSubscribers();
            // Если список журналов пуст, то переходим на новую итерацию
             if (magazines.isEmpty())
             {
                 cout << "\tNO MAGAZINES!" << endl;
                 continue;
             }

             if (subscribers.isEmpty())
             {
                 cout << "\tNO SUBSCRIBERS!" << endl;
                 continue;
             }

            // Блок связывания журнала и подписчика
             while (!isConnect)
               {
                qint32 idMagazine, idSubscriber;

                cout << "\tInput ID magazine which you want to connect: " << flush;

                idMagazine = cin.readLine().toInt();

                cout << "\tInput ID subscriber which you want to connect: " << flush;

                idSubscriber = cin.readLine().toInt();

                // Если ввели правильные IDs, то выполняем
                if ((idMagazine >= 0 && idMagazine < magazines.size()) && (idSubscriber >= 0 && idSubscriber < subscribers.size()))
                {
                    // Если подписчик не подписан, то подписываем его на журнал ( чтобы подписчик был подписан только на один журнал )
                    if (!subscribers[idSubscriber]->subscribe())
                    {
                        // Вызываем сигнал связывания
                        emit connect(idMagazine, idSubscriber);
                        isConnect = true;
                    }
                    // Если подписчик уже подписан, то говорим об этом
                    else
                        cout << "\tSubscriber " << subscribers[idSubscriber]->getName() << " already a subscriber! " << subscribers[idSubscriber]->getMagazine() << endl;
                }
                else
                {
                    cout << "\t" << "Error connect!" << endl;
                }
            }

            continue;
        }

        // list
        if (command == com[3])
        {
            // Если список журналов не пуст, то выводим их
            if (!magazines.isEmpty())
            {
                this->printMagazines();
            }
            else
            {
                cout << "\tNO MAGAZINES!" << endl;
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

            continue;
        }

        // size
        if (command == com[4])
        {
            bool isSize = false;

            // Если подписчики есть
            if (!subscribers.isEmpty())
            {
                this->printSubscribers();

                // Блок вывода размера журнала, на который подписан подписчик
                while (!isSize)
                {
                    cout << "\tEnter the id of the subscriber from whom you want to find out the size of magazine: " << flush;

                    qint32 idSubscriber = cin.readLine().toInt();

                    // Если ввели верный ID, то выполняем
                    if (idSubscriber >= 0 && idSubscriber < subscribers.size())
                    {
                        // Если подписчик подписан на журнал, то выводим размер журнала, на который он подписан
                        if (subscribers[idSubscriber]->subscribe())
                        {
                            cout << "\t\tSize is " << QFileInfo(subscribers[idSubscriber]->getMagazine()).size() << " byte" << endl;
                            isSize = true;
                        }
                        else
                        {
                            cout << "\t\tSubscriber has not magazine!" << endl;
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

            continue;
        }

        // delete magazine
        if (command == com[5])
        {
            // Если список журналов пуст, то переходим на новую итерацию
            if (magazines.isEmpty())
            {
                cout << "\tNO MAGAZINES!" << endl;
                continue;
            }

            this->printMagazines();

            cout << "\t\tInput number magazine which you want to delete: " << flush;

            bool isDelete = false;

            // Блок удаления журнала из вектора ( массива )
            while (!isDelete)
            {
                // toInt из QString делает Int
                qint32 idMagazine = cin.readLine().toInt();

                // Если введённый ID существует, то выполняем
                if (idMagazine >= 0 && idMagazine < magazines.size())
                {
                    // Вызываем синал удаления журнала
                    emit deleteMagazine(idMagazine);

                    isDelete = true;
                }
            }

            continue;
        }

        // delete subscriber
        if (command == com[6])
        {
            if (subscribers.isEmpty())
            {
                cout << "\tNO SUBSCRIBES!" << endl;
                continue;
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

            continue;
        }

        // get counter
        if (command == com[7])
        {
            if (magazines.isEmpty())
            {
                cout << "\tNO MAGAZINES!" << endl;
                continue;
            }

            this->printMagazines();

            cout << "\t\tInput number magazine which you want to know counter: " << flush;

            bool isCounter = false;

            // Блок возврата количества подписчиков у журнала
            while (!isCounter)
            {
                qint32 idMagazine = cin.readLine().toInt();

                if (idMagazine >= 0 && idMagazine < magazines.size())
                {
                    // Вызываем сигнал, который выведет число подписчиков у журнала
                    emit getCounter(idMagazine);

                    isCounter = true;
                }
            }

            continue;
        }

        // resign ( переподписка )
        if (command == com[8])
        {
            if (subscribers.isEmpty())
            {
                cout << "\tNO SUBSCRIBERS!" << endl;
                continue;
            }

            if (magazines.isEmpty())
            {
                cout << "\tNO MAGAZINES!" << endl;
                continue;
            }

            this->printMagazines();
            this->printSubscribers();

            cout << "\t\tInput number subscriber which you want to re-sign: " << flush;

            bool isResign = false;

            // Блок переподписки
            while(!isResign)
            {
                qint32 idSubscriber = cin.readLine().toInt();

                if (idSubscriber >= 0 && idSubscriber < subscribers.size())
                {
                    cout << "\t\tInput the idMagazine which you want to subscribe to: " << flush;

                    qint32 idMagazine = cin.readLine().toInt();

                    if (idMagazine >= 0 && idMagazine < magazines.size())
                    {
                        // Вызываем сигнал переподписки
                        emit resign(idSubscriber, idMagazine);

                        isResign = true;
                    }
                }
            }

            continue;
        }

    }
}

FileManager::FileManager() :
    QObject(nullptr),
    com({
        "add subscriber",
        "add magazine",
        "connect",
        "list",
        "size",
        "delete magazine",
        "delete subscriber",
        "get counter",
        "resign",
        })
{
    // Связываем сигнал добавления журнала с лямбда-функцией
    QObject::connect(this, &FileManager::addMagazine, [&](const QString& path)
        {
            // Если журнал(путь) существует и он файл
            if (QFileInfo(path).exists() && QFileInfo(path).isFile())
            {
                magazines.push_back(new Magazine(path));
                QTextStream(stdout) << "\t\tMagazine " << path << " was added!" << endl;
            }
            else
            {
                QTextStream(stdout) << "\t\tPath to magazine was not added!" << endl;
            }
        });

    QObject::connect(this, &FileManager::addSubscriber, [&](const QString& name)
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

    QObject::connect(this, &FileManager::connect, [&](const qint32& idMagazine, const qint32& idSubscriber)
        {
            // Если выбранный подписчик не подписан, то выполняем
            if (!subscribers[idSubscriber]->subscribe())
            {
                // Обращаемся к журналу, на который хотим подписаться и добавляем ему подписчика
                magazines[idMagazine]->addSubscriber(subscribers[idSubscriber]);
                // Добавляем подписчику журнал
                subscribers[idSubscriber]->getMagazine() = magazines[idMagazine]->getName();

                // Выставляем подписчику флаг, что он был подписан
                subscribers[idSubscriber]->subscribe() = true;

                QTextStream(stdout) << "\t\t" << magazines[idMagazine]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
            }
            else
            {
                QTextStream(stdout) << "\t\tConnection error!" << endl;
            }
        });

    QObject::connect(this, &FileManager::deleteMagazine, [&](const qint32& index)
        {
            for (qint32 i = 0; i < magazines.size(); ++i)
            {
                // Находим нужный индекс журнала, который надо удалить
                if (i == index)
                {
                    QTextStream(stdout) << "\t\t" << magazines[i]->getName() << " was deleted!" << endl;

                    // Проходимся по всем подписчикам, и удаляем у этих подписчиков этот журнал
                    for (const auto& subscriber : magazines[i]->getSubscribers())
                    {
                        subscriber->getMagazine().clear();
                        subscriber->subscribe() = false;
                    }

                    // Удаляем журнал из вектора ( массива )
                    magazines.remove(i);

                    break;
                }
            }
        });

    QObject::connect(this, &FileManager::deleteSubscriber, [&](const qint32& index)
        {
            for (qint32 i = 0; i < subscribers.size(); ++i)
            {
                // Ищем индекс нужного подписчика, которого надо удалить
                if (i == index)
                {
                    QTextStream(stdout) << "\t\t" << subscribers[i]->getName() << " was deleted!" << endl;

                    // Проходим по списку журналов
                    for (qint32 iMag = 0; iMag < magazines.size(); ++iMag)
                    {
                        // Ищем у каждого журнала нашего подписчика
                        for (qint32 iSub = 0; iSub < magazines[iMag]->getSubscribers().size(); ++iSub)
                        {
                            // Если мы нашли нашего подписчика у журнала, то выполняем
                            if (subscribers[index]->getName() == magazines[iMag]->getSubscribers()[iSub]->getName())
                            {
                                // Удаляем у журнала этого подписчика
                                magazines[iMag]->getSubscribers().remove(iSub);
                                magazines[iMag]->getCounter()--;
                            }
                        }
                    }

                    // Удаляем подписчика из вектора ( массива )
                    subscribers.remove(i);

                    break;
                }
            }
        });

    QObject::connect(this, &FileManager::getCounter, [&](const qint32& index)
        {
            for (qint32 i = 0; i < magazines.size(); ++i)
            {
                // Находим нужный индекс магазина
                if (i == index)
                {
                    QTextStream(stdout) << "\t\tCounter " << magazines[i]->getName() << " is equal " << magazines[i]->getCounter() << endl;
                    break;
                }
            }
        });

    QObject::connect(this, &FileManager::resign, [&](const qint32& idSubscriber, const qint32& idMagazine)
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
                        for (qint32 mag = 0; mag < magazines.size(); ++mag)
                        {
                            // Если нашли нужный журнал, то удаляем из подписки этого подписчика
                            if (magazines[mag]->getName() == subscribers[idSubscriber]->getMagazine())
                            {
                                for (qint32 sub = 0; sub < magazines[mag]->getSubscribers().size(); ++sub)
                                {
                                    if (magazines[mag]->getSubscribers()[sub]->getName() == subscribers[idSubscriber]->getName())
                                    {
                                        magazines[mag]->getSubscribers().remove(sub);
                                        magazines[mag]->getCounter()--;
                                    }
                                }
                            }
                        }

                        // Здесь подписываем на новый журнал
                        magazines[idMagazine]->addSubscriber(subscribers[idSubscriber]);
                        subscribers[idSubscriber]->getMagazine() = magazines[idMagazine]->getName();
                        subscribers[idSubscriber]->subscribe() = true;

                        QTextStream(stdout) << "\t\t" << magazines[idMagazine]->getName() << " was connect with " << subscribers[idSubscriber]->getName() << endl;
                    }
                }
            }
        });

}
