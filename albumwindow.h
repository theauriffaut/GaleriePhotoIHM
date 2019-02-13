#pragma once

#include <ui_albumwindow.h>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QSqlQuery>

#include "bddgalleryphoto.h"
#include "smartdelete.h"

class AlbumWindow : public QWidget, private Ui::AlbumWindow
{
    Q_OBJECT
public:
    explicit AlbumWindow(const BddGalleryPhoto* pbdd, QWidget *parent = nullptr);
    ~AlbumWindow();
    void newBDDRequest(QVector<Album *> albTab);
private:
    const BddGalleryPhoto* bdd;

    //void openImage(const QString &fileName);
signals:

public slots:
    void changeTab();
    void addAlbum();
private slots:
};
