#include "shop.h"
#include "sub.h"

Shop::Shop(const QString& name) :
    name(name), counter(0)
{
}

QString Shop::getName() const
{
    return name;
}

void Shop::addSubscriber(Subscriber* subscriber)
{
    subscribers.push_back(subscriber);
    ++counter;
}

QVector<Subscriber*>& Shop::getSubscribers()
{
    return subscribers;
}

qint32& Shop::getCounter()
{
    return counter;
}

