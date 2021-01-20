#ifndef SHOP__H
#define SHOP__H

#include <QObject>

class Subscriber;

class Shop : public QObject
{
    Q_OBJECT

public:
    // Конструктор принимает имя журнала
    explicit Shop(const QString& name);

    // Деструктор создаётся по умолчанию компилятором
    ~Shop() = default;

    // Возвращает имя журнала
    // const - спецификатор, означающий что функция не изменяет поля класса ( исключения mutable )
    QString getName() const;

    // Добавление подписчика в журнал
    void addSubscriber(Subscriber* subscriber);

    // Возвращает вектор (массив) подписчиков
    QVector<Subscriber*>& getSubscribers();

    // Возвращает количество подписчиков
    qint32& getCounter();

private:
    QVector<Subscriber*> subscribers;
    qint32 counter;
    QString name;

};
#endif // SHOP__H
