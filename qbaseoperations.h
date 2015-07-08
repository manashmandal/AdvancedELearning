#ifndef QBASEOPERATIONS_H
#define QBASEOPERATIONS_H

#include <QWidget>
#include <QString>
#include <QRegExp>
#include <QRegExpValidator>
#include <QStringList>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class QBaseOperations;
}

class QBaseOperations : public QWidget
{
    Q_OBJECT

public:
    explicit QBaseOperations(QWidget *parent = 0);
    ~QBaseOperations();


    void clearBaseGBoxLineEdits();


public slots:
    void reduceBinEditFloat(QString in);
    void reduceHexEditFloat(QString in);
    void reduceCusEditFloat(QString in);
    void reduceOctEditFloat(QString in);
    void reduceDecEditFloat(QString in);
    void reduceRsInputEditFloat(QString in);

    void binaryToOthers(QString in);
    void decimalToOthers(QString in);
    void customToOthers(QString in);
    void octalToOthers(QString in);
    void hexadecimalToOthers(QString in);
    void complementValidatorGenerator(int val);
    void calculateRsComplement(QString in);
    void grayToBinary(QString in);
    void binaryToGray(QString in);
    void BCD(QString in);
private slots:
    //Custom Slots
    void customBaseValidatorGenerator(int val);


    //Generated Slots
    void on_moreButton_toggled(bool checked);
    void on_doneButton_clicked();

    void on_clearButton_clicked();



    void on_complementBaseSpinBox_valueChanged(int arg1);

private:
    void removeExtraFloatingPoint(QString in, QLineEdit *currEdit);

    QString reserved_base_digits;
    Ui::QBaseOperations *ui;
};

#endif // QBASEOPERATIONS_H
