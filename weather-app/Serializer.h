#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Serializable.h"

class Serializer
{
public:

    Serializer() = default;
    ~Serializer() = default;
    void save(const Serializable& serializable, const QString& filepath);
    void load(Serializable& serializable, const QString& filepath);

};

#endif // SERIALIZER_H
