#include "subscriber_.h"

Subscriber::Subscriber(const QString& name) :
    name(name),isSubscribe(false)
{
}

QString Subscriber::getName() const
{
    return name;
}

QString& Subscriber::getMagazine()
{
    return magazine;
}

bool& Subscriber::subscribe()
{
    return isSubscribe;
}
