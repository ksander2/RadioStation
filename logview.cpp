#include "logview.h"
#include "ui_logview.h"

LogView::LogView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogView)
{
    ui->setupUi(this);
}

LogView::~LogView()
{
    delete ui;
}

void LogView::setLogtext(const QString &value)
{
    logtext = value;
    ui->textBrowser->setText(value);
}
