#ifndef NUMBERBASECHART_H
#define NUMBERBASECHART_H

#define DEFAULT_FONT_SIZE 8

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class NumberBaseChart;
}

class NumberBaseChart : public QDialog
{
    Q_OBJECT

public:
    explicit NumberBaseChart(QWidget *parent = 0);
    ~NumberBaseChart();

public slots:
    void setNumberSize(int size);

private:
    Ui::NumberBaseChart *ui;
};

#endif // NUMBERBASECHART_H
