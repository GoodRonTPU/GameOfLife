#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>
#include "field.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);

public slots:
    void startGame(const int &number = -1); // start
    void stepGame();    // one generation (step)
    void stopGame(); // finish
    void clear(); // clear
    void setCellNumber(const int &s); // set number of the cells in one row

    int interval(); // interval between generations
    void setInterval(int msec); // set interval between generations

    QColor masterColor(); // color of the cells
    void setMasterColor(const QColor &color); // set color of the cells

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    QColor m_masterColor;
    QTimer* timer;
    int generations;
public:
    field* gamefield;
    
};

#endif // GAMEWIDGET_H
