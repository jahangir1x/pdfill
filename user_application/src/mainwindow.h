#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QMainWindow>
#include <QPdfDocument>
#include <QPushButton>

#include "pdfhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   protected:
    void resizeEvent(QResizeEvent *event) override;

   private slots:
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void on_addTextButton_clicked();
    void on_saveButton_clicked();
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();

   private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    // QPdfDocument *document;
    QLineEdit *textInput;
    QPushButton *addTextButton;
    QPushButton *saveButton;
    PdfHandler *pdfHandler;
    // qreal currentZoomLevel;
    // int currentPage;
    // void displayPage(int pageNumber);
    // void addTextToPage(const QString &text);
};

#endif  // MAINWINDOW_H
