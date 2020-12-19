#include "mainwindow.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    MainWindow w(".");
    w.setWindowTitle("Tag Editor");
    w.setWindowIcon(QIcon(":/resources/logo.svg"));
    w.show();
    if (argc >= 2)
        w.getSetFWindow(argv[1]);
    int res = a.exec();
    // system("leaks -q utag");
    return res;
}
