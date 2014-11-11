#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include "overlay.h"
#include <QColor>

class QPaintEvent;
class QMouseEvent;

class ColorSlider : public Overlay
{
    Q_OBJECT
public:
    explicit ColorSlider(QWidget *parent = 0, QColor color = QColor(255, 0, 0, 128));

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
    QPoint curPressPos;
    QColor drawColor;
    Overlay *nextOverlay;
    float drawPercent;
};

#endif // COLORSLIDER_H
