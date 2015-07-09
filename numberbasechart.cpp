#include "numberbasechart.h"
#include "ui_numberbasechart.h"



NumberBaseChart::NumberBaseChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumberBaseChart)
{
    ui->setupUi(this);



    connect(ui->fontSizeBox, SIGNAL(valueChanged(int)), this, SLOT(setNumberSize(int)));

    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
        for (int j = 0; j < ui->tableWidget->columnCount(); j++){
            ui->tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->fontSizeBox->setValue(DEFAULT_FONT_SIZE);

}

void NumberBaseChart::setNumberSize(int size)
{
    QFont font("MS Shell Dlg 2", size);
    ui->tableWidget->setFont(font);
}

NumberBaseChart::~NumberBaseChart()
{
    delete ui;
}
