#ifndef FILEMANAGER__H
#define FILEMANAGER__H

#include <QObject>

class Magazine;
class Subscriber;

class FileManager final : public QObject
{
    Q_OBJECT

public:
    ~FileManager();

    // Функция "взывать". Она возвращает ссылку на единственный объекьт класса FileManager
    static FileManager& instance();

    // Сигнал добавления журнала
    Q_SIGNAL void addMagazine(const QString& path);

    // Сигнал добавления подписчика
    Q_SIGNAL void addSubscriber(const QString& name);

    // Сигнал связывания журнала и подписчика
    Q_SIGNAL void connect(const qint32& idMagazine, const qint32& idSubscriber);

    // Сигнал удаления журнала
    Q_SIGNAL void deleteMagazine(const qint32& index);

    // Сигнал удаления подписчика
    Q_SIGNAL void deleteSubscriber(const qint32& index);

    // Сигнал, который вызывает функцию у журнала ( счётчик подписчиков )
    Q_SIGNAL void getCounter(const qint32& index);

    // Сигнал переподписки подписчика
    Q_SIGNAL void resign(const qint32& idSubscriber, const qint32& idMagazine);

    void TERMINAL();

private:
    explicit FileManager();
    void printMagazines();
    void printSubscribers();

    private:
    QVector<Magazine*>		magazines;
    QVector<Subscriber*>	subscribers;
    QVector<QString>		com;
};

#endif // FILEMANAGER__H
