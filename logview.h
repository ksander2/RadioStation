#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDialog>

namespace Ui {
class LogView;
}

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = 0);
    ~LogView();

    void setLogtext(const QString &value);

private:
    Ui::LogView *ui;

    QString logtext;
};

#endif // LOGVIEW_H
