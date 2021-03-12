#include "widget.h"
#include "ui_widget.h"

#include <QTimer>

#include <Windows.h>
#include <WinUser.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_SendInput_clicked()
{
    int delay = ui->spinBox_Delay->value();

    int type = ui->comboBox_InputType->currentIndex();

    switch (type) {
    case 0: // mouse event
    {
        LONG dx = ui->spinBox_MouseX->value();
        LONG dy = ui->spinBox_MouseY->value();
        DWORD data = ui->spinBox_Data->value();
        DWORD flag = 0;
        if (ui->checkBox_Absolute->isChecked())
            flag |= MOUSEEVENTF_ABSOLUTE;
        if (ui->checkBox_HWheel->isChecked())
            flag |= MOUSEEVENTF_HWHEEL;
        if (ui->checkBox_Move->isChecked())
            flag |= MOUSEEVENTF_MOVE;

        if (ui->checkBox_LeftDown->isChecked())
            flag |= MOUSEEVENTF_LEFTDOWN;
        if (ui->checkBox_LeftUp->isChecked())
            flag |= MOUSEEVENTF_LEFTUP;
        if (ui->checkBox_RightDown->isChecked())
            flag |= MOUSEEVENTF_RIGHTDOWN;
        if (ui->checkBox_RightUp->isChecked())
            flag |= MOUSEEVENTF_RIGHTUP;
        if (ui->checkBox_MiddleDown->isChecked())
            flag |= MOUSEEVENTF_MIDDLEDOWN;
        if (ui->checkBox_MiddleUp->isChecked())
            flag |= MOUSEEVENTF_MIDDLEUP;
        if (ui->checkBox_VirtualDesk->isChecked())
            flag |= MOUSEEVENTF_VIRTUALDESK;
        if (ui->checkBox_Wheel->isChecked())
            flag |= MOUSEEVENTF_WHEEL;
        if (ui->checkBox_XDown->isChecked())
            flag |= MOUSEEVENTF_XDOWN;
        if (ui->checkBox_XUp->isChecked())
            flag |= MOUSEEVENTF_XUP;

        QTimer::singleShot(delay*1000, [dx, dy, data, flag](){
            INPUT input = {0};
            input.type = INPUT_MOUSE;
            input.mi.dx = dx;
            input.mi.dy = dy;
            input.mi.dwFlags = flag;
            input.mi.mouseData = data;

            UINT ret = SendInput(1, &input, sizeof(input));
//            SetCursorPos(dx, dy);
            if (ret == 0)
            {
                DWORD errcode = GetLastError();
                qDebug("SendInput failed with error: %d", errcode);
            }
        });
    }
        break;
    case 1: // keyboard input
        break;
    case 2:
        break;
    default:
        break;

    }

}

