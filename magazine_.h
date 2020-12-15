#ifndef MAGAZINE__H
#define MAGAZINE__H

#include <QObject>

class Subscriber;

class Magazine : public QObject
{
    Q_OBJECT

public:
    // Конструктор принимает имя журнала
    explicit Magazine(const QString& name);

    // Деструктор создаётся по умолчанию компилятором
    ~Magazine() = default;

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
#endif // MAGAZINE__H
