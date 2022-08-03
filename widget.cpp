#include "widget.h"
#include "ui_widget.h"
#include "gishandler.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    GisHandler handler;


}

Widget::~Widget()
{
    delete ui;
}



