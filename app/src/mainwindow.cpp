#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string path, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_dir(this, path) {
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint |
                   Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    ui->setupUi(this);
    toFirstScreen();
    m_list = new DirList(this, ui->ChDir);
    m_list->setWidgets(m_dir.getList());
    ui->YearLe->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->TrackLe->setValidator(new QIntValidator(0, INT_MAX, this));
    connect(ui->Back, &QPushButton::clicked, this, &MainWindow::toFirstScreen);
    connect(ui->Sort, &QPushButton::clicked, this, &MainWindow::changeSort);
    connect(ui->Rec, &QPushButton::clicked, this, &MainWindow::changeRec);
    connect(ui->Dir, &QPushButton::clicked, this, &MainWindow::changeDir);
    connect(ui->CurrS, &QPushButton::clicked, this, &MainWindow::chooseImg);
    connect(ui->PrevS, &QPushButton::clicked, this, &MainWindow::switchPrev);
    connect(ui->NextS, &QPushButton::clicked, this, &MainWindow::switchNext);
    connect(ui->Save, &QPushButton::clicked, this, &MainWindow::saveInfo);
    ui->AlbumLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->ArtistLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->CommentLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->GenreLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->TitleLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->YearLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->TrackLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->LyricsLe->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

MainWindow::~MainWindow() {
    delete m_list;
    delete ui;
}

static void setIconButton(QPushButton *button, std::string path) {
    TagLib::MPEG::File file(path.c_str());
    TagLib::ID3v2::Tag *m_tag = file.ID3v2Tag(true);
    TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");

    if(frameList.isEmpty()) {
        button->setIcon(QIcon(":/resources/note.svg"));
        return ;
    }
    TagLib::ID3v2::AttachedPictureFrame *coverImg = 
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());

    QImage coverQImg;
    coverQImg.loadFromData((const uchar *)coverImg->picture().data(),
                            coverImg->picture().size());
    QPixmap pix = QPixmap::fromImage(coverQImg).scaled(
        button->width(),
        button->height(),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
    );
    QBitmap map(pix.width(), pix.height());
    map.fill(Qt::color0);
    QPainter painter(&map);
    painter.setBrush(Qt::color1);
    painter.drawRoundedRect(0, 0, pix.width(), pix.height(), 50, 50);
    pix.setMask(map);
    button->setIcon(QIcon(pix));
}

std::string MainWindow::getPathIcon(int index) {
    return m_dir.fullPath(m_itr[index].getPath(), const_cast<char *>(m_itr[index].getName().c_str()));
}

void MainWindow::switchNext(void) {
    ui->PrevS->show();
    m_index += 1;
    ui->SongName->setText(QString(m_itr[m_index].getName().c_str()));
    setInfo();
    setIconButton(ui->PrevS, getPathIcon(m_index - 1));
    imgResize(ui->PrevS);
    if (m_index + 1 == int(m_itr.size()))
        ui->NextS->hide();
    else {
        ui->NextS->show();
        setIconButton(ui->NextS, getPathIcon(m_index + 1));
        imgResize(ui->NextS);
    }
}

void MainWindow::switchPrev(void) {
    ui->NextS->show();
    m_index -= 1;
    ui->SongName->setText(QString(m_itr[m_index].getName().c_str()));
    setInfo();
    setIconButton(ui->NextS, getPathIcon(m_index + 1));
    imgResize(ui->NextS);
    if (m_index == 0)
        ui->PrevS->hide();
    else {
        ui->PrevS->show();
        setIconButton(ui->PrevS, getPathIcon(m_index - 1));
        imgResize(ui->PrevS);
    }
}

void MainWindow::setInfo(void) {
    setIconButton(ui->CurrS, getPathIcon(m_index));
    imgResize(ui->CurrS);
    t_Element info = m_itr[m_index].getInfo();
    TagLib::String length;

    ui->AlbumLe->setText(QString(info.album.toCString()));
    ui->ArtistLe->setText(QString(info.artist.toCString()));
    ui->CommentLe->setText(QString(info.comment.toCString()));
    ui->GenreLe->setText(QString(info.genre.toCString()));
    ui->TitleLe->setText(QString(info.title.toCString()));
    ui->YearLe->setText(QString(info.year.toCString()));
    ui->TrackLe->setText(QString(info.track.toCString()));
    ui->LyricsLe->setText(QString(info.lyrics.toCString()));
    ui->BitRateLe->setText(QString(info.bitrate.toCString()));
    ui->SampleRateLe->setText(QString(info.sampleRate.toCString()));
    ui->ChannelsLe->setText(QString(info.channels.toCString()));
    length = info.minutes.size() == 0 ? "00"
                : info.minutes.size() == 1 ? "0" + info.minutes
                : info.minutes;
    length += info.seconds.size() == 0 ? ":00"
                : info.seconds.size() == 1 ? ":0" + info.seconds
                : ":" + info.seconds;
    ui->LengthLe->setText(QString(length.toCString()));
}

void MainWindow::saveInfo(void) {
    t_Element info;

    if (!ui->AlbumLe->text().isEmpty())
        info.album = ui->AlbumLe->text().toStdString().c_str();
    if (!ui->ArtistLe->text().isEmpty())
        info.artist = ui->ArtistLe->text().toStdString().c_str();
    if (!ui->CommentLe->text().isEmpty())
        info.comment = ui->CommentLe->text().toStdString().c_str();
    if (!ui->GenreLe->text().isEmpty())
        info.genre = ui->GenreLe->text().toStdString().c_str();
    if (!ui->TitleLe->text().isEmpty())
        info.title = ui->TitleLe->text().toStdString().c_str();
    if (!ui->YearLe->text().isEmpty())
        info.year = ui->YearLe->text().toStdString().c_str();
    if (!ui->TrackLe->text().isEmpty())
        info.track = ui->TrackLe->text().toStdString().c_str();
    if (!ui->LyricsLe->toPlainText().isEmpty())
        info.lyrics = ui->LyricsLe->toPlainText().toStdString().c_str();
    m_itr[m_index].setNewInfo(info);
}

void MainWindow::toFirstScreen(void) {
    ui->Screen->setCurrentIndex(0);
}

void MainWindow::toSecondScreen(std::string path) {
    m_index = 0;
    m_itr = (*m_dir.getList().find(path)).second;
    m_dir.sortVector(m_sort ? BY_NAME : BY_TAG, m_itr);
    ui->SongName->setText(QString(m_itr[m_index].getName().c_str()));
    ui->PrevS->hide();
    if (m_itr.size() == 1)
        ui->NextS->hide();
    else {
        setIconButton(ui->NextS, getPathIcon(m_index + 1));
        imgResize(ui->NextS);
    }
    setInfo();
    ui->Screen->setCurrentIndex(1);
}

void MainWindow::changeSort(void) {
    m_sort = m_sort ? false : true;
    ui->Sort->setIcon(m_sort ? QIcon(NAME) : QIcon(TAG));
    if (m_itr.empty())
        return ;
    m_dir.sortVector(m_sort ? BY_NAME : BY_TAG, m_itr);
    m_index = 0;
    ui->SongName->setText(QString(m_itr[m_index].getName().c_str()));
    ui->PrevS->hide();
    if (m_itr.size() == 1)
        ui->NextS->hide();
    setInfo();
}

void MainWindow::changeRec(void) {
    ui->Rec->setIcon(m_rec ? QIcon(REC1) : QIcon(REC2));
    m_rec = m_rec ? false : true;
}

void MainWindow::changeDir(void) {
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isNull() && QDir(dir).exists() && QDir(dir).isReadable()) {
        m_list->deleteWdgets();
        m_dir.changeDir(dir.toStdString(), m_rec);
        m_list->setWidgets(m_dir.getList());
    }
}

void MainWindow::chooseImg(void) {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", ".",
        "Image Files (*.jpg)");
    
    if (!fileName.isNull() && QFileInfo(fileName).exists() && QFileInfo(fileName).isWritable()) {
        m_itr[m_index].setNewImg(fileName.toStdString());
        setIconButton(ui->CurrS, getPathIcon(m_index));
        imgResize(ui->CurrS);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    if (!m_resize) {
        m_resize = true;
        return ;
    }
    imgResize(ui->Dir);
    imgResize(ui->Sort);
    imgResize(ui->Rec);
    imgResize(ui->Back);
    imgResize(ui->Save);
    imgResize(ui->CurrS);
    imgResize(ui->NextS);
    imgResize(ui->PrevS);
}

void MainWindow::imgResize(QPushButton *elem) {
    elem->setIconSize(QSize(elem->width() - 25, elem->height() - 25));
}

void MainWindow::printError(std::string error) {
    QMessageBox msgBox;

    msgBox.setIconPixmap(QPixmap(ERROR).scaled(50, 50, Qt::KeepAspectRatio));
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setStyleSheet("QMessageBox{background-color: #383B49;}"
                         "QMessageBox QPushButton:pressed{margin-top: 4px; border-bottom: 0px;}"
                         "QMessageBox QPushButton {font-size: 16px; min-width: 72 px;"
                            "border: 1px solid black; border-radius: 5px; color: white;"
                            "background: qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 #ed8770, stop:1 #d9519d);"
                            "border-bottom: 4px solid qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 #c15841, stop:1 #bb2077);"
                         "}"
                         "QMessageBox QLabel {font-size: 16px; margin-top: 20px;}");
    msgBox.setText(QString(error.c_str()));
    msgBox.exec();
}

void MainWindow::getSetFWindow(std::string path) {
    m_dir.changeDir(path, m_rec);
    m_list->setWidgets(m_dir.getList());
}
