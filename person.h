#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Person : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Person();
    Person(QPixmap);

private:

};

#endif // PERSON_H
