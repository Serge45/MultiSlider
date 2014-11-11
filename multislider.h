#ifndef MULTISLIDER_H
#define MULTISLIDER_H

#include <QWidget>
#include <QList>

class QResizeEvent;
class ColorSlider;

namespace Ui {
class MultiSlider;
}

class MultiSlider : public QWidget
{
    Q_OBJECT

public:
    explicit MultiSlider(QWidget *parent = 0);
    ~MultiSlider();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initSliders();

private:
    Ui::MultiSlider *ui;
    QList<ColorSlider *> sliders;
};

#endif // MULTISLIDER_H
