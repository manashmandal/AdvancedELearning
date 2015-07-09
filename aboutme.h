#ifndef ABOUTME_H
#define ABOUTME_H

#include <QDialog>

namespace Ui {
class aboutme;
}

class aboutme : public QDialog
{
    Q_OBJECT

public:
    explicit aboutme(QWidget *parent = 0);
    ~aboutme();

private:
    Ui::aboutme *ui;
};

#endif // ABOUTME_H
