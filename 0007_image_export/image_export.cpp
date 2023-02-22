#include "image_export.h"

ImageExport::ImageExport()
{
}

ImageExport::~ImageExport()
{
}

bool ImageExport::loadImage(std::string path)
{
    QDir directory(QString::fromStdString(path));
    if(!directory.exists())
        return false;
    QStringList nameFilter;
    nameFilter << "*.png" << "*.jpg" << "*.tif" << "*.PNG" << "*.JPG" << "*.TIF";
    QFileInfoList list = directory.entryInfoList( nameFilter, QDir::Files );

    if(list.empty())
        return false;

    for (auto idx = 0; idx < list.size(); idx++)
    {
        QPixmap pixmap;
        QString path = list[idx].absoluteFilePath();
        if(pixmap.load(path))
            m_pixmap.insert(list[idx].fileName(), pixmap);

    }
    return true;
}

void ImageExport::run()
{

}
