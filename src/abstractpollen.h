#ifndef ABSTRACT_POLLEN_H
#define ABSTRACT_POLLEN_H

class AbstractPollen {
public:
    explicit AbstractPollen(int pollenId);
    ~AbstractPollen();

    int getPollenId();

protected:
    QString getPollenName(int pollenId);
    QString getPollenImageFileName(int pollenId);

private:

    int pollenId;
    QString getInternalPollenName();

};

#endif // ABSTRACT_POLLEN_H