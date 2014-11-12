#include "multislider.h"
#include "ui_multislider.h"
#include "colorslider.h"

MultiSlider::MultiSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiSlider)
{
    ui->setupUi(this);
    initSliders();
}

MultiSlider::~MultiSlider()
{
    delete ui;
}

void MultiSlider::resizeEvent(QResizeEvent *event)
{
    foreach(auto *slider, sliders) {
        slider->setGeometry(rect());
    }
}

void MultiSlider::initSliders()
{
    auto *slider = new ColorSlider(this,
                                   QColor(255, 0, 0, 128),
                                   0);
    slider->setPercent(0.7);
    sliders.append(slider);

    slider = new ColorSlider(this,
                             QColor(0, 255, 0, 128),
                             1);

    slider->setPercent(0.5);
    sliders.append(slider);

    slider = new ColorSlider(this,
                             QColor(0, 0, 255, 128),
                             2);
    slider->setPercent(0.2);
    sliders.append(slider);

    for (int i = sliders.size() - 1; i > 0 ; --i) {
        sliders[i]->setNextOverlay(sliders[i-1]);
    }
}
