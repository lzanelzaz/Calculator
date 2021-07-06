#include "Calculator.h"
#include "expression_parser.h"

#include <QRegularExpression>
#include <QString>

/* Change size of symbols */
template <typename T>
void font_size (T pointer, int size)
{
    QFont font = pointer->font();
    font.setPointSize(font.pointSize() + size);
    pointer->setFont(font);
}

Calculator::Calculator(QWidget* pwgt/*= О*/) : QWidget(pwgt)
{
    /* expression line */
    m_plcd = new QLineEdit("0");
    font_size(m_plcd, 12);
    m_plcd->setMinimumSize(150, 50);

    /* answer line */
    m_plcd_result = new QLineEdit("");
    font_size(m_plcd_result, 12);
    m_plcd_result->setMinimumSize(150, 50);

    QString aButtons[5] [4] = {{"(", ")", "<-", "CE"},
                             {"7", "8", "9", "/"},
                             {"4", "5", "6", "*"},
                             {"1", "2", "3", "-"},
                             {"0", ".", "=", "+"}
                            };
    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(m_plcd_result, 1, 0, 1, 4);

    pcmd = new QRadioButton("DEC");
    pcmd->setMinimumSize(70, 50);
    font_size(pcmd, 8);

    ptopLayout->addWidget(pcmd, 2, 0);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
        ptopLayout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }
    setLayout(ptopLayout);
}

QPushButton* Calculator::createButton(const QString& str) {
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(70, 50);
    font_size(pcmd, 8);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}

void Calculator::calculate(){
    fResult = ParseCondition(m_strDisplay);
    if (fResult == Rational(1,0)){
        m_plcd_result->setText("Error"); // prevents app crashes
        return;
    }
    /* fraction form */
    m_plcd_result->setText(fResult.toString());
    /* if button's state is "on" */
    if (pcmd->isChecked()){
        /* decimal form */
        m_plcd_result->setText(QString::number(fResult.toDecimal()));
    }
    /* change from fraction to decimal while answer is on screen */
    connect(pcmd, SIGNAL(toggled(bool)), SLOT(decimalButtonClicked(bool) ));
}

void Calculator::slotButtonClicked() {
    disconnect(pcmd, SIGNAL(toggled(bool)), this, SLOT(decimalButtonClicked(bool)));
    QString str = ((QPushButton*)sender())->text(); // value of clicked button
    /* backspace */
    if (str == "<-") {
        if (!m_strDisplay.isEmpty()){ // if equation line is not empty
            m_strDisplay.chop(1); // delete last character
            m_plcd->setText(m_strDisplay); // change text of expression line
        return; // skip next
        }
        else {
            str = "CE"; // if expression line is empty clear everything
        }
    }
    /* clear everything */
    if (str == "CE") {
        m_strDisplay = "";
        m_plcd->setText("0");
        m_plcd_result->setText("");
        return;
    }
    /* display digits */
    else if (str.contains(QRegularExpression("[0-9]"))) {
        m_strDisplay += str;
        m_plcd->setText(m_strDisplay);
        m_plcd_result->setText(""); // so previous answer won't be there
    }
    /* User can write ".2" instead of "0.2" */
    else if (str == ".") {
        if (!m_strDisplay.right(1).contains(QRegularExpression("\\d"))){
            m_strDisplay += "0";
        }
        m_strDisplay += str;
        m_plcd->setText(m_strDisplay);
    }
    else if (str == "=") {
        /* User can write in the line instead of clicking buttons */
        m_strDisplay = m_plcd->text();
        /* If double click, app doesn't crash */
        if (m_strDisplay.right(1) == "="){
            return;
        }
        while (m_strDisplay.right(1).contains(QRegularExpression("\\D"))){  // last number is not there
            m_strDisplay = m_strDisplay.left(m_strDisplay.length()-1);      // example: 8/-=
        }
        calculate();
        m_strDisplay += str;
        m_plcd->setText(m_strDisplay);
    }
    else { /* '/', '*', '-', '+', '(', ')' */
        m_strDisplay += str;
        m_plcd->setText(m_strDisplay);
    }
}

void Calculator::decimalButtonClicked(bool checked){
    if (checked) { m_plcd_result->setText(QString::number(fResult.toDecimal())); }  // decimal form
    else { m_plcd_result->setText(fResult.toString()); }                            // fraction form
}
