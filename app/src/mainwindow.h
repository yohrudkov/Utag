#pragma once

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QBitmap>
#include <QPainter>

#include "Window.h"
#include "dirlist.h"

#define ERROR   ":/resources/error.svg"
#define NAME    ":/resources/name.svg"
#define TAG     ":/resources/tag.svg"
#define REC1    ":/resources/rec1.svg"
#define REC2    ":/resources/rec2.svg"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(std::string path = nullptr,
                        QWidget *parent = nullptr);
    ~MainWindow();

    void toFirstScreen(void);
    void toSecondScreen(std::string path);
    void changeSort(void);
    void switchNext(void);
    void switchPrev(void);
    void changeRec(void);
    void changeDir(void);
    void chooseImg(void);
    void saveInfo(void);
    void setInfo(void);
    void imgResize(QPushButton *elem);
    void printError(std::string error);
    void getSetFWindow(std::string path);
    std::string getPathIcon(int index);

private:
    Ui::MainWindow *ui;
    DirList *m_list;
    Window m_dir;
    std::vector<Element> m_itr;
    bool m_resize {false};
    bool m_sort {false};
    bool m_rec {false};
    int m_shift {1};
    int m_index {0};

public slots:
    void resizeEvent(QResizeEvent* event);
};
