#include "dirlist.h"
#include "mainwindow.h"

#include <QtDebug>
#include <QGridLayout>
#include <QLabel>

DirList::DirList(MainWindow *parent_cl, QWidget *parent) : QWidget(parent) {
    m_parent = parent_cl;
    m_pwd = parent;
}

DirList::~DirList() {
    deleteWdgets();
    m_list.clear();
}

void DirList::setWidgets(std::map<std::string, std::vector<Element>> list) {
    int row = 0;

    for (auto itr = list.begin(); itr != list.end(); row++) {
        int j = 0;

        for (j = 0; j < COUNT && itr != list.end(); j++, itr++)
            buttonProperties(row, j, itr->first);
        row += 1;
        for (; j > 0; j--)
            itr--;
        for (j = 0; j < COUNT && itr != list.end(); j++, itr++)
            labelProperties(row, j, itr->first);
    }
    dynamic_cast<QGridLayout *>(m_pwd->layout())->setSpacing(15);
}

void DirList::buttonProperties(int row, int column, std::string path) {
    QPushButton *button = new QPushButton(m_pwd);
    QPixmap pixmap(FOLDER);
    QIcon ButtonIcon(pixmap);

    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
    button->setStyleSheet("border-radius: 12px;"
                          "border: 1px solid black;");
    button->setMinimumSize(500 / COUNT - 50, 500 / COUNT);
    button->setMaximumSize(800 / COUNT - 50, 800 / COUNT);
    dynamic_cast<QGridLayout *>(m_pwd->layout())->addWidget(button, row, column);
    connect(button, &QPushButton::clicked, [this, path]() {
        m_parent->toSecondScreen(path);
    });
    m_list.push_front(button);
}

void DirList::labelProperties(int row, int column, std::string path) {
    RunLine *label = new RunLine(m_pwd);

    label->setString(QString((path + "     ").c_str()));
    label->setSpeed(3);
    label->sizePolicy().setVerticalPolicy(QSizePolicy::Preferred);
    label->setAlignment(Qt::AlignCenter);
    label->lower();
    label->setMinimumSize(500 / COUNT - 50, 25);
    label->setMaximumSize(800 / COUNT - 50, 50);
    dynamic_cast<QGridLayout *>(m_pwd->layout())->addWidget(label, row, column);
}

void DirList::deleteWdgets(void) {
    for (int i = 0; i < dynamic_cast<QGridLayout*>(m_pwd->layout())->count(); i++)
        dynamic_cast<QGridLayout *>(m_pwd->layout())->itemAt(i)->widget()->deleteLater();
    m_list.clear();
}
