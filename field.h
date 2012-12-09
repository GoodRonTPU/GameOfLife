#ifndef FIELD_H
#define FIELD_H
#include <QWidget>

class field
{
public:
    field();
    void generation(int &notChanged);
    void swtchCell(int k, int j);
    void returnMap(bool a[102][102]);

    QString dump(); // dump of current universe
    void setDump(const QString &data); // set current universe from it's dump

    int cellNumber(); // number of the cells in one row
    void setCellNumber(const int &s); // set number of the cells in one row

    void clear(); // clear

private:
    bool universe[102][102]; // map
    bool next[102][102]; // map
    int universeSize;

    bool isAlive(int k, int j); // return true if universe[k][j] accept rules
};

#endif // FIELD_H
