#include <QApplication>
#include "Calculator.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    Calculator calculator;

    calculator.setWindowTitle("Calculator");
    calculator.resize(250, 300);

    calculator.show();

    return app.exec();
}
