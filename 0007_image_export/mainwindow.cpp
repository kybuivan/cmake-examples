#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QMessageBox>
#include <QStringListModel>
#include "image_export.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    // Fix window size and resizeable is false
    this->setFixedSize(this->size());

    ui->btExport->setDisabled(true);

    _colorTable.push_back(qMakePair("White", QColor(255, 255, 255)));
    _colorTable.push_back(qMakePair("Black", QColor(0,0,0)));
    _colorTable.push_back(qMakePair("Pink", QColor(255, 192, 203)));
    _colorTable.push_back(qMakePair("Red", QColor(255, 0, 0)));

    QStringList colorName;
    foreach(auto color,  _colorTable)
    {
        colorName.push_back(color.first);
    }
    QStringListModel* modelColor = new QStringListModel;
    modelColor->setStringList(colorName);
    ui->cmbBackgroundColor->setModel(modelColor);

    update_ImageSizing(ui->cbFitImage->isChecked());
}

void MainWindow::on_btChoose_clicked()
{
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::Directory);
    QString folderName = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());

    if(!folderName.isEmpty())
    {
        ui->lbFolderName->setText(folderName);
        ui->btExport->setEnabled(true);
    }
}

void MainWindow::on_btExport_clicked()
{
    ImageExport _ImageExport;
    QString msg;
    if(_ImageExport.loadImage(ui->lbFolderName->text().toStdString()))
    {
        _ImageExport.run();
        msg = "The image export has been finished.";
    }
    else
    {
        msg = "The image export has been failed. Folder doesn't have images.";
    }


    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::on_btDone_clicked()
{
    this->window()->close();
}

void MainWindow::on_btCancel_clicked()
{
    this->window()->close();
}

void MainWindow::on_leSubFolder_editingFinished()
{
    if(ui->leSubFolder->text().isEmpty())
        ui->leSubFolder->setText("lk");
}

void MainWindow::update_ImageSizing(bool isEnable)
{
    if(ui->leImageWidth->isEnabled() != isEnable)
    {
        ui->leImageWidth->setEnabled(isEnable);
        ui->leImageHeight->setEnabled(isEnable);
        ui->leLeftMargin->setEnabled(isEnable);
        ui->leRightMargin->setEnabled(isEnable);
        ui->leUpMargin->setEnabled(isEnable);
        ui->leDownMargin->setEnabled(isEnable);
        ui->cmbImageSize->setEnabled(isEnable);
    }
}

void MainWindow::update_ImageSizing(float res)
{
}

void MainWindow::on_cbFitImage_stateChanged(int arg1)
{
    update_ImageSizing((bool)arg1);
}

void MainWindow::on_leImageRevolution_editingFinished()
{

}

