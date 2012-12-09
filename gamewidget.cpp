#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generations(-1)//,
//    gamefield(this)
//    universeSize(50)
{
    timer->setInterval(300);
    m_masterColor = "#000";
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
//    memset(&universe, false, sizeof(universe));
//    memset(&next, false, sizeof(next));
}

void GameWidget::clear()
{
    gamefield.clear();
    update();
}

void GameWidget::setCellNumber(const int &s)
{
    gamefield.setCellNumber(s);
    update();
}


void GameWidget::startGame(const int &number)
{
    generations = number;
    timer->start();
}

void GameWidget::stepGame()
{
    generations++;
    timer->setSingleShot(true);
    timer->start();
}

void GameWidget::stopGame()
{
    timer->stop();
}

//void GameWidget::clear()
//{
//    for(int k = 1; k <= universeSize; k++) {
//        for(int j = 1; j <= universeSize; j++) {
//            universe[k][j] = false;
//        }
//    }
//    update();
//}

//int GameWidget::cellNumber()
//{
//    return universeSize;
//}

//void GameWidget::setCellNumber(const int &s)
//{
//    universeSize = s;
//    update();
//}

//QString GameWidget::dump()
//{
//    char temp;
//    QString master = "";
//    for(int k = 1; k <= universeSize; k++) {
//        for(int j = 1; j <= universeSize; j++) {
//            if(universe[k][j] == true) {
//                temp = '*';
//            } else {
//                temp = 'o';
//            }
//            master.append(temp);
//        }
//        master.append("\n");
//    }
//    return master;
//}

//void GameWidget::setDump(const QString &data)
//{
//    int current = 0;
//    for(int k = 1; k <= universeSize; k++) {
//        for(int j = 1; j <= universeSize; j++) {
//            universe[k][j] = data[current] == '*';
//            current++;
//        }
//        current++;
//    }
//    update();
//}

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

//bool GameWidget::isAlive(int k, int j)
//{
//    int power = 0;
//    power += universe[k+1][j];
//    power += universe[k-1][j];
//    power += universe[k][j+1];
//    power += universe[k][j-1];
//    power += universe[k+1][j+1];
//    power += universe[k-1][j-1];
//    power += universe[k-1][j+1];
//    power += universe[k+1][j-1];
//    if (((universe[k][j] == true) && (power == 2)) || (power == 3))
//           return true;
//    return false;
//}

void GameWidget::newGeneration()
{
    if(timer->isSingleShot())
        timer->setSingleShot(false);

    if(generations < 0)
        generations++;
    int notChanged=0;
//    for(int k=1; k <= universeSize; k++)
//    {
//        for(int j=1; j <= universeSize; j++)
//        {
//            next[k][j] = isAlive(k, j);
//            if(next[k][j] == universe[k][j])
//                notChanged++;
//        }
//    }
    gamefield.generation(notChanged);
    int universeSize = gamefield.cellNumber();

    if(notChanged == universeSize*universeSize)
    {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        return;
    }
//    for(int k=1; k <= universeSize; k++)
//    {
//        for(int j=1; j <= universeSize; j++)
//        {
//            universe[k][j] = next[k][j];
//        }
//    }
    update();
//    generations--;
//    if(generations == 0)
//    {
//        stopGame();
//        QMessageBox::information(this,
//                                 tr("Game finished."),
//                                 tr("Iterations finished."),
//                                 QMessageBox::Ok,
//                                 QMessageBox::Cancel);
//    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    int universeSize = gamefield.cellNumber();

    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    gamefield.swtchCell(k,j);
//    universe[k][j] = !universe[k][j];
    update();
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    QColor gridColor = m_masterColor; // color of the grid
    gridColor.setAlpha(50); // must be lighter than main color
    p.setPen(gridColor);
    int universeSize = gamefield.cellNumber();
    double cellWidth = (double)width()/universeSize; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/universeSize; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    int universeSize = gamefield.cellNumber();
    double cellWidth = (double)width()/universeSize;
    double cellHeight = (double)height()/universeSize;
    bool map[102][102];
    gamefield.returnMap(map);

    for(int k=1; k <= universeSize; k++) {
        for(int j=1; j <= universeSize; j++) {
            if(map[k][j] == true) { // if there is any sense to paint it
                qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(m_masterColor)); // fill cell with brush of main color
            }
        }
    }
}

QColor GameWidget::masterColor()
{
    return m_masterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    m_masterColor = color;
    update();
}
