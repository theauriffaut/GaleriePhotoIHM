#include "albumwindow.h"

#include <QLabel>

static void deleteChildWidgets(QLayoutItem *item) {
  QLayout *layout = item->layout();
  if (layout) {
    int itemCount = layout->count();
    for (int i = 0; i < itemCount; i++) {
      deleteChildWidgets(layout->itemAt(i));
    }
  }
  delete item->widget();
}

static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
  // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
  for (int i = layout->count() - 1; i >= 0; i--) {
    int r, c, rs, cs;
    layout->getItemPosition(i, &r, &c, &rs, &cs);
    if (
        (row == -1 || (r <= row && r + rs > row)) &&
        (column == -1 || (c <= column && c + cs > column))) {
      QLayoutItem *item = layout->takeAt(i);
      if (deleteWidgets) {
        deleteChildWidgets(item);
      }
      delete item;
    }
  }
}

static void removeCell(QGridLayout *layout, int row, int column, bool deleteWidgets = true) {
  remove(layout, row, column, deleteWidgets);
}


AlbumWindow::AlbumWindow(const BddGalleryPhoto* pbdd, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    bdd = pbdd;

    boutonAdd = new ImageButton(pathBoutonAddH, pathBoutonAdd, 200, 100, this);
    boutonSwitchD = new ImageButton(pathBoutonSwitchDroitH, pathBoutonSwitchDroit, 700, 80, this);
    boutonSwitchD->loadImageEnable(pathBoutonSwitchDroit);
    boutonSwitchD->loadImageDisable(pathBoutonSwitchDroitH);
    boutonSwitchG = new ImageButton(pathBoutonSwitchGaucheH, pathBoutonSwitchGauche, 700, 80, this);
    boutonSwitchG->loadImageEnable(pathBoutonSwitchGauche);
    boutonSwitchG->loadImageDisable(pathBoutonSwitchGaucheH);
    boutonSearch = new ImageButton(pathBoutonSearchH, pathBoutonSearch, 60, 100, this);

    layoutBoutonAdd->addWidget(boutonAdd);
    layoutBoutonDroit->addWidget(boutonSwitchD);
    layoutBoutonGauche->addWidget(boutonSwitchG);
    layoutBoutonSearch->addWidget(boutonSearch);

    connect(boutonSwitchG, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(boutonSwitchD, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(boutonAdd, SIGNAL(clicked()), this, SLOT(addAlbum()));
    connect(boutonSearch, SIGNAL(clicked()), this, SLOT(searchRequest()));
    connect(lineEdit, SIGNAL(returnPressed()), boutonSearch, SIGNAL(clicked()));

    formCreateAlbum = new FormCreateAlbum(bdd);
    connect(formCreateAlbum, SIGNAL(albumAdded()), this, SLOT(searchRequest()));

    newBDDRequest(bdd->getAllAlbums());
}

AlbumWindow::~AlbumWindow()
{
    //bdd->destroyBdd();
    smartDeleteMrNovelli(bdd);
}

void AlbumWindow::changeTab()
{
    if(sender() == boutonSwitchD) {
        boutonSwitchD->setDisable(true);
        boutonSwitchG->setDisable(false);
        stackedWidget->setCurrentIndex(1);
    } else if (sender() == boutonSwitchG) {
        boutonSwitchD->setDisable(false);
        boutonSwitchG->setDisable(true);
        stackedWidget->setCurrentIndex(0);
    }
}

void AlbumWindow::addAlbum() {
    formCreateAlbum->clean();
    formCreateAlbum->show();
}

void AlbumWindow::searchRequest(){
    newBDDRequest(bdd->getAllAlbums("name", lineEdit->text()));
}

void AlbumWindow::newBDDRequest(QVector<Album *> albTab)
{
    const int SIZE_IMAGE = 250;
    const int NB_IMAGES  = 5;

    if(listAlbum->count() > 0){
        removeCell(listAlbum,-1,-1);
    }
    int k = 0;
    if(!albTab.isEmpty()){
        for(int i = 0; i < static_cast<int>(albTab.size() / NB_IMAGES) + 1 ; i++){
            for (int j = 0; j < NB_IMAGES; j++) {
                k = j + i * NB_IMAGES;
                if(k < albTab.size()){
                    QLabel * label = new QLabel();
                    label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
                    label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
                    QPixmap pix = QPixmap();
                    bool validate = pix.load(albTab[k]->getCover());
                    if(validate){
                        pix = pix.scaled(SIZE_IMAGE,SIZE_IMAGE,Qt::KeepAspectRatio);
                        label->setPixmap(pix);
                        listAlbum->addWidget(label, i, j);
                    } else {
                        qDebug() << "Erreur : Lors du chargement de l'image de l'album >" << albTab[k]->getCover() << "| Dans la fonction" << __FUNCTION__;
                    }
                }
            }
        }
    } else {
        QLabel * label = new QLabel();
        label->setMaximumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setMinimumSize(SIZE_IMAGE, SIZE_IMAGE);
        label->setScaledContents(true);
        label->setPixmap(QPixmap());
        listAlbum->addWidget(label, 0, 0);
    }

}

