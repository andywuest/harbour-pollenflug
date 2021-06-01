#ifndef ABSTRACT_POLLEN_H
#define ABSTRACT_POLLEN_H

class AbstractPollen {
public:
    AbstractPollen() = default;

protected:
    QString getPollenName(int pollenId);
    QString getPollenImageFileName(int pollenId);

private:
    QString getInternalPollenName();

};

#endif // ABSTRACT_POLLEN_H