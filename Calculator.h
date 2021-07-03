#pragma once

#include <QtWidgets>
#include <QLineEdit>

#include "rational.h"

class QPushButton;

class Calculator : public QWidget {
Q_OBJECT
private:
    QLineEdit* m_plcd;
    QLineEdit* m_plcd_result;
    QRadioButton* pcmd;
    QString m_strDisplay;
    Rational fResult;
public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();
public slots:
    void slotButtonClicked();
    void decimalButtonClicked(bool);
};
