#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include "overlay.h"
#include <QColor>

class QPaintEvent;
class QMouseEvent;

class ColorSlider : public Overlay
{
    Q_OBJECT

    static int activeId;

public:
    explicit ColorSlider(QWidget *parent = 0,
                         QColor color = QColor(255, 0, 0, 128),
                         int wId = 0);

public:
    void setNextOverlay(Overlay *overlay);

public slots:
    void setPercent(float p);
    void setDrawColor(const QColor &c);

protected:
    void paintEvent(QPaintEvent *paintEvent);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    bool isValidPressPos(const QPoint &p);

private:
    bool leftButtonPressed;
    bool controllable;
    QPoint curPressPos;
    QColor drawColor;
    QColor controllerColor;
    Overlay *nextOverlay;
    float drawPercent;
    int id;
};

#endif // COLORSLIDER_H
