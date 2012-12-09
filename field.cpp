#include "field.h"

field::field():
    universeSize(50)
{
    memset(&universe, false, sizeof(universe));
    memset(&next, false, sizeof(next));
}

void field::clear()
{
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k][j] = false;
        }
    }
}

int field::cellNumber()
{
    return universeSize;
}

void field::setCellNumber(const int &s)
{
    universeSize = s;
}

void field::returnMap(bool a[102][102])
{
    for(int k = 1; k <= universeSize; k++)
    {
        for(int j = 1; j <= universeSize; j++)
        {
            a[k][j]=universe[k][j];
        }
    }

}

QString field::dump()
{
    char temp;
    QString master = "";
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            if(universe[k][j] == true) {
                temp = '*';
            } else {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}

void field::setDump(const QString &data)
{
    int current = 0;
    for(int k = 1; k <= universeSize; k++) {
        for(int j = 1; j <= universeSize; j++) {
            universe[k][j] = data[current] == '*';
            current++;
        }
        current++;
    }
}

void field::generation(int &notChanged)
{
    for(int k=1; k <= universeSize; k++)
    {
        for(int j=1; j <= universeSize; j++)
        {
            next[k][j] = isAlive(k, j);
            if(next[k][j] == universe[k][j])
                notChanged++;
        }
    }
    for(int k=1; k <= universeSize; k++)
    {
        for(int j=1; j <= universeSize; j++)
        {
            universe[k][j] = next[k][j];
        }
    }
}

void field::swtchCell(int k, int j)
{
    universe[k][j] = !universe[k][j];
}

bool field::isAlive(int k, int j)
{
    int power = 0;
    power += universe[k+1][j];
    power += universe[k-1][j];
    power += universe[k][j+1];
    power += universe[k][j-1];
    power += universe[k+1][j+1];
    power += universe[k-1][j-1];
    power += universe[k-1][j+1];
    power += universe[k+1][j-1];
    if (((universe[k][j] == true) && (power == 2)) || (power == 3))
           return true;
    return false;
}
