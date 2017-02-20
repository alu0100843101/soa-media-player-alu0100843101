#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::help()
{

   //Insertamos logo de Qt y documentación de Qt en la versión usada.
   QPixmap pixmap("/home/andperqui/Documentos/SOA/media-player/MediaPlayer/images/qt-logo.png");
   ui->label->setPixmap(pixmap);

   ui->textLabel->setText(tr("Help Information\n"
                      "Qt: Code less.\n"
                      "Create more.\n"
                      "Deploy Everywhere.\n\n"
                      "Based on Qt 5.8.0 © \n\n"
                      "All you need in: http://doc.qt.io/qt-5/"));
}
