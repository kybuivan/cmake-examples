#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btChoose_clicked();

    void on_btExport_clicked();

    void on_btDone_clicked();

    void on_btCancel_clicked();

    void on_leSubFolder_editingFinished();

    void on_cbFitImage_stateChanged(int arg1);

    void on_leImageRevolution_editingFinished();

private:
    void Init();

    void update_ImageSizing(bool isEnable);

    void update_ImageSizing(float res);
private:
    Ui::MainWindow *ui;
    QVector<QPair<QString, QColor>> _colorTable;
};
#endif // MAINWINDOW_H
