#ifndef COUNTERWIDGET_H
#define COUNTERWIDGET_H

#include <QLCDNumber>
#include <QLabel>
#include <QTimer>
#include "gpio.h"

class CounterWidget : public QWidget
{
    Q_OBJECT

public:
    CounterWidget(QWidget *parent = nullptr);
    ~CounterWidget();

public slots:
    void updateCounter();
    void decToBin(int n);
    void setLEDS();
private:
     int m_count;
     QTimer m_timer;
     Gpio m_gpio;
     QLCDNumber* m_output = new QLCDNumber(this);
     QList<bool> m_states;
     QList<bool> m_ledstates;


};

#endif // COUNTERWIDGET_H
