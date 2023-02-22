#ifndef IMAGE_EXPORT_H
#define IMAGE_EXPORT_H

#include <string>
#include <QMainWindow>
#include <QMap>
#include <QColor>
#include <QApplication>
#include <QFileInfoList>
#include <QDir>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define IN_TO_CM 2.54
enum IMG_RESOLUTION
{
    PIXEL_PER_INCH,
    PIXEL_PER_CM
};

class ImageExport
{
public:
    ImageExport();
    ~ImageExport();
    void setResolution(IMG_RESOLUTION res) {_resolutionImage = res;};
    bool loadImage(std::string path);// {_folderPath = path;}
    void setBackgroundColor(QColor color){ _backgroundColor = color;}
    void setBorderColor(QColor color){ _borderColor = color;}
    void run();
protected:
private:
    QMap<QString, QPixmap> m_pixmap;
    QString _folderPath;
    unsigned int _width;
    unsigned int _height;
    IMG_RESOLUTION _resolutionImage;
    QColor _backgroundColor;
    QColor _borderColor;
};

#endif // IMAGE_EXPORT_H
