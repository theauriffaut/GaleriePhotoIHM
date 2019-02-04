#ifndef BDDGALLERYPHOTO_H
#define BDDGALLERYPHOTO_H

#include <QSqlDatabase>
#include <QString>
#include <Qdir>

#include <QtDebug>
#include "album.h"
#include "image.h"



class BddGalleryPhoto
{
public:
    BddGalleryPhoto(QString path);
    ~BddGalleryPhoto();
    QSqlDatabase getBdd() const;

    bool open();
    void close();
    bool insertImage(Image entry) const;
    Image* getImageByName(QString name) const;
    //bool insertAlbum(Album entry);

    bool initBdd();
private:
    QSqlDatabase bdd;
};

#endif // BDDGALLERYPHOTO_H