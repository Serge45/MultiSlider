#include "colorslider.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QCursor>

ColorSlider::ColorSlider(QWidget *parent, QColor color) :
    Overlay(parent), drawColor(color), drawPercent(0.5f),
    leftButtonPressed(false), nextOverlay(nullptr)
{
    setMouseTracking(true);
}

void ColorSlider::setNextOverlay(Overlay *overlay)
{
    nextOverlay = overlay;
}

void ColorSlider::setPercent(float p)
{
    drawPercent = p;
    update();
}

void ColorSlider::setDrawColor(const QColor &c)
{
    drawColor = c;
    update();
}

void ColorSlider::paintEvent(QPaintEvent *paintEvent)
{
    QPainter p(this);
    QRect drawArea = rect();
    drawArea.setWidth(drawArea.width() * drawPercent);
    p.fillRect(drawArea, drawColor);
}

void ColorSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
            isValidPressPos(event->pos())) {
        leftButtonPressed = true;
        curPressPos = event->pos();
    } else if (nextOverlay) {
        qApp->sendEvent(nextOverlay, event);
    }
}

void ColorSlider::mouseReleaseEvent(QMouseEvent *event)
{
    leftButtonPressed = false;
    curPressPos = event->pos();

    if (nextOverlay) {
        qApp->sendEvent(nextOverlay, event);
    }
    qApp->restoreOverrideCursor();
}

void ColorSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (isValidPressPos(event->pos()) || leftButtonPressed) {
        qApp->setOverrideCursor(Qt::SizeHorCursor);

        if (leftButtonPressed) {
            drawPercent = event->pos().x() / static_cast<float>(width());
            update();
        }
        return;
    } else {
        if (nextOverlay) {
            qApp->sendEvent(nextOverlay, event);
            return;
        }
    }
    qApp->restoreOverrideCursor();
}

bool ColorSlider::isValidPressPos(const QPoint &p)
{
    float error = p.x();
    error = fabs(error - drawPercent * width());
    error /= width();

    if (error < 0.02) {
        return true;
    }
    return false;
}
