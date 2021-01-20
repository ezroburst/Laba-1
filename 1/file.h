
#ifndef FILE__H
#define FILE__H

#include <QObject>

class Shop;
class Subscriber;

class FileCheck final : public QObject
{
    Q_OBJECT

public:
    ~FileCheck();

    // Функция "взывать". Она возвращает ссылку на единственный объекьт класса FileManager
    static FileCheck& instance();
void add_subscriber();
void add_shop();
void connect();
void list();
void size();
void delete_shop();
void delete_subscriber();
void get_counter();
void resign();
    // Сигнал добавления журнала
    Q_SIGNAL void addshop(const QString& path);

    // Сигнал добавления подписчика
    Q_SIGNAL void addSubscriber(const QString& name);

    // Сигнал связывания журнала и подписчика
    Q_SIGNAL void connect(const qint32& idshop, const qint32& idSubscriber);

    // Сигнал удаления журнала
    Q_SIGNAL void deleteshop(const qint32& index);

    // Сигнал удаления подписчика
    Q_SIGNAL void deleteSubscriber(const qint32& index);

    // Сигнал, который вызывает функцию у журнала ( счётчик подписчиков )
    Q_SIGNAL void getCounter(const qint32& index);

    // Сигнал переподписки подписчика
    Q_SIGNAL void resign(const qint32& idSubscriber, const qint32& idshop);

    void TERMINAL();

private:
    explicit FileCheck();
    void printshop();
    void printSubscribers();

    private:
    QVector<Shop*>		shops;
    QVector<Subscriber*>	subscribers;
    QVector<QString>		com;
};

#endif // FILE__H
