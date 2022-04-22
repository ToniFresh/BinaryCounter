#include <QHBoxLayout>
#include "counterwidget.h"
#include "config.h"
#include <QDebug>

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent), m_count(0), m_timer(this), m_gpio(this)
{
    m_states = {0, 0, 0};
    m_ledstates = {0, 0, 0, 0};
    m_count = 0;

    setWindowTitle("BinaryCounter");
    resize(300, 200);
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);

    //QLCDNumber zur Anzeige des Zaehlerstandes dezimal:
    layout->addWidget(m_output);


    connect(&m_timer, &QTimer::timeout, this, &CounterWidget::updateCounter);    
    m_timer.start(T_UPDATE);
}

CounterWidget::~CounterWidget()
{

}

// Zaehlerstand im Widget und dual ueber LEDs anzeigen:
void CounterWidget::updateCounter()
{
    int cnt = 0;
    for(auto pin : BUTTONS) m_states[cnt++] = m_gpio.isActivated(pin);

    if(m_states[0] == 1) m_count--;
    if(m_states[1] == 1) m_count = 0;
    if(m_states[2] == 1) m_count++;
    if(m_count > 15) m_count = 0;
    if(m_count < 0) m_count = 15;

    for(int cnt = 0; cnt < 4; cnt++) m_ledstates[cnt] = 0;

    decToBin(m_count);

    m_output->display(m_count);
}

void CounterWidget::decToBin(int n)
{
    for(int i=0;n>0;i++)
    {
        m_ledstates[i]= n%2;
        n=n/2;
    }

    setLEDS();
}

void CounterWidget::setLEDS()
{
    int cnt = 0;
    for(auto pin : LEDS) m_gpio.set(pin, m_ledstates[cnt++]);
}



