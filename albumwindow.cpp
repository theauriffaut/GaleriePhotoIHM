#include "albumwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>

AlbumWindow::AlbumWindow(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    connect(albPersoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(albAutoButton, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(newImageButton, SIGNAL(clicked()),this, SLOT(searchImage()));

}

void AlbumWindow::changeTab()
{
    if(sender() == albAutoButton) {
        stackedWidget->setCurrentIndex(1);
    } else if (sender() == albPersoButton) {
        stackedWidget->setCurrentIndex(0);
    }

}
void AlbumWindow::searchImage()
{
    QUrl imgPath = QFileDialog::getOpenFileUrl(this);
    if (!imgPath.isEmpty()) {
        qDebug() << "GG";
        labelImg->setPixmap(QPixmap(imgPath.url()));
    }

        //openImage(fileName);
}

/*void AlbumWindow::openImage(const QString &fileName)
{

    QFile file(fileName);

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}*/

