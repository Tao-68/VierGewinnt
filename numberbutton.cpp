#include "numberbutton.h"

NumberButton::NumberButton(int number, QWidget* parent): QPushButton(parent), number(number)
{
    connect(this, &NumberButton::clicked, this, &NumberButton::clickedSlot);
    setText(QString::number(number+1));
}

void NumberButton::clickedSlot()
{
    emit numberButtonClicked(number);
}
