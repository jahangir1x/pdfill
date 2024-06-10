#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QPdfDocument>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_previousPageBtn_clicked();
    void on_nextPageBtn_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsView *pdfView;
    QGraphicsScene *scene;
    QPdfDocument *document;
    int currentPage;

    void displayPage(int pageNumber);
};
#endif // MAINWINDOW_H
