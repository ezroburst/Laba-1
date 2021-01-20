#include "sub.h"


Subscriber::Subscriber(const QString& name) :
    name(name),isSubscribe(false)
{
}

QString Subscriber::getName() const
{
    return name;
}

QString& Subscriber::getshop()
{
    return shop;
}

bool& Subscriber::subscribe()
{
    return isSubscribe;
}
