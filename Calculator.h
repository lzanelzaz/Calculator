#pragma once

#include <QtWidgets>
#include <QLineEdit>

#include "expression_parser.h"

class Calculator : public QWidget {
Q_OBJECT
private:
    QLineEdit* m_plcd; // expression line
    QLineEdit* m_plcd_result; // answer line
    QRadioButton* pcmd; // decimal/fraction form change button
    QString m_strDisplay; // text of expression line
    Rational fResult; // answer
public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();
public slots:
    void slotButtonClicked();
    void decimalButtonClicked(bool);
};
