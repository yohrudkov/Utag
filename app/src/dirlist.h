#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>

#include "RunLine.h"

#define COUNT 3
#define FOLDER ":/resources/folder.svg"

class Element;
class MainWindow;

class DirList : public QWidget {
    Q_OBJECT
public:
    explicit DirList(MainWindow *parent_cl, QWidget *parent = nullptr);
    ~DirList();

    void setWidgets(std::map<std::string, std::vector<Element>> list);
    void buttonProperties(int row,
                          int column,
                          std::string path);
    void labelProperties(int row,
                         int column,
                         std::string path);
    void deleteWdgets(void);

private:
    MainWindow *m_parent;
    QWidget *m_pwd;
    QVector<QPushButton *> m_list;
};
