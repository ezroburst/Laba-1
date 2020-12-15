#include "magazine_.h"
#include "subscriber_.h"

Magazine::Magazine(const QString& name) :
    name(name), counter(0)
{
}

QString Magazine::getName() const
{
    return name;
}

void Magazine::addSubscriber(Subscriber* subscriber)
{
    subscribers.push_back(subscriber);
    ++counter;
}

QVector<Subscriber*>& Magazine::getSubscribers()
{
    return subscribers;
}

qint32& Magazine::getCounter()
{
    return counter;
}
