#ifndef NUMBERBUTTON_H
#define NUMBERBUTTON_H

#include <QPushButton>



class NumberButton: public QPushButton
{
    Q_OBJECT

public:
    NumberButton(int number, QWidget* parent = nullptr);

private slots:
    void clickedSlot();

signals:
    void numberButtonClicked(int number);

private:
    int number;
};

#endif // NUMBERBUTTON_H
