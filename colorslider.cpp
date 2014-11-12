#include "colorslider.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QCursor>

int ColorSlider::activeId = -1;

ColorSlider::ColorSlider(QWidget *parent, QColor color, int wId) :
    Overlay(parent), drawColor(color), drawPercent(0.5f),
    leftButtonPressed(false), nextOverlay(nullptr), id(wId),
    controllable(false)
{
    setMouseTracking(true);
    controllerColor = drawColor;
    controllerColor.setAlpha(255);
}

void ColorSlider::setNextOverlay(Overlay *overlay)
{
    nextOverlay = overlay;
}

void ColorSlider::setPercent(float p)
{
    drawPercent = std::max(p, 0.f);
    drawPercent = std::min(p, 100.f);
    update();
}

void ColorSlider::setDrawColor(const QColor &c)
{
    drawColor = c;
    controllerColor = c;
    controllerColor.setAlpha(255);
    update();
}

void ColorSlider::paintEvent(QPaintEvent *paintEvent)
{
    QPainter p(this);
    QRect drawArea = rect();
    auto drawX = drawArea.width() * drawPercent;
    drawArea.setWidth(drawX);
    p.fillRect(drawArea, drawColor);

    if (controllable) {
        QPen pen(controllerColor);
        p.setPen(pen);
        p.drawEllipse(QPoint(drawX, height() / 2), 8, 8);
        p.setBrush(QBrush(controllerColor));
        p.drawEllipse(QPoint(drawX, height() / 2), 6, 6);
    }
}

void ColorSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
            isValidPressPos(event->pos())) {
        activeId = id;
        leftButtonPressed = true;
        curPressPos = event->pos();
    } else if (nextOverlay) {
        qApp->sendEvent(nextOverlay, event);
    }
}

void ColorSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if (leftButtonPressed) {
        curPressPos = event->pos();
    }
    leftButtonPressed = false;
    activeId = INT_MAX;

    if (nextOverlay) {
        qApp->sendEvent(nextOverlay, event);
    }
}

void ColorSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (isValidPressPos(event->pos()) || leftButtonPressed) {
        controllable = true;

        if (leftButtonPressed && activeId == id) {
            drawPercent = event->pos().x() / static_cast<float>(width());
        } else {
            if (nextOverlay) {
                qApp->sendEvent(nextOverlay, event);
            }
        }
    } else {
        controllable = false;

        if (nextOverlay){
            qApp->sendEvent(nextOverlay, event);
        }
    }

    update();
}

bool ColorSlider::isValidPressPos(const QPoint &p)
{
    float error = p.x();
    error = fabs(error - drawPercent * width());

    if (error < 8) {
        return true;
    }
    return false;
}
