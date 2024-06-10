#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPdfDocument>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , document(new QPdfDocument(this))
    , currentPage(0)
{
    ui->setupUi(this);

    pdfView = ui->graphicsView;
    scene = new QGraphicsScene(this);
    pdfView->setScene(scene);

    // Load the PDF document
    QString pdfFilePath = "/home/zinis/document.pdf";
    if (document->load(pdfFilePath) != QPdfDocument::NoError) {
        // Handle error
        return;
    }

    displayPage(currentPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::displayPage(int pageNumber)
{
    if (pageNumber < 0 || pageNumber >= document->pageCount()) {
        return;
    }

    // Get the page size in points (1/72 inch)
    QSizeF pageSize = document->pageSize(pageNumber);

    // Define the desired resolution in DPI
    const int dpi = 300;

    // Calculate the size in pixels
    QSize imageSize = pageSize.toSize() * dpi / 120;

    // Render the page with the calculated size
    QImage image = document->render(pageNumber, imageSize);

    // Update the QGraphicsScene with the rendered image
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}
void MainWindow::on_previousPageBtn_clicked()
{
    if (currentPage > 0) {
        currentPage--;
        displayPage(currentPage);
    }
}


void MainWindow::on_nextPageBtn_clicked()
{    if (currentPage < document->pageCount() - 1) {
        currentPage++;
        displayPage(currentPage);
    }

}

