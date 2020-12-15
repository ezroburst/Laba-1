#ifndef SUBSCRIBER__H
#define SUBSCRIBER__H

#include <QObject>

class Subscriber : public QObject
{
    Q_OBJECT

public:
    // Инициализация имени
    explicit Subscriber(const QString& name);
    ~Subscriber() = default;

    QString getName() const;

    QString& getMagazine();

    // Возвращает флаг, подписан ли подпичик на журнал или нет
    bool& subscribe();
private:
    QString name;
    QString magazine;
    bool isSubscribe;
};
#endif // SUBSCRIBER__H