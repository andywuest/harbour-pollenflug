#ifndef ABSTRACT_POLLEN_H
#define ABSTRACT_POLLEN_H

#include <QObject>

class AbstractPollen : public QObject {
    Q_OBJECT

public:
    explicit AbstractPollen(int pollenId);
    ~AbstractPollen();

    int getPollenId();
    QString getPollenName(int pollenId);

protected:
    QString getPollenImageFileName(int pollenId);

private:

    int pollenId;
    QString getInternalPollenName(int pollenId);

};

#endif // ABSTRACT_POLLEN_H
