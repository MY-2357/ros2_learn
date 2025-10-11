#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    // QLabel label("Hello, Qt!");
    // label.show();
    // return App.exec();
    QLabel *label = new QLabel();
    QString message = QString::fromStdString("Hello Qt!");
    label->setText(message);
    label->show();
    App.exec();
    return 0;
};