#include "pdfhandler.h"

#include <QFileDialog>
#include <QPdfWriter>
#include <iostream>

PdfHandler::PdfHandler(QGraphicsScene* scene, QGraphicsView* view) {
    this->scene = scene;
    this->view = view;
    document = new QPdfDocument();
    currentZoomLevel = 1.0;
    currentPage = 0;
    QFile::copy(PDF_FILE_PATH, TEMP_FILE_PATH);
    if (document->load(PDF_FILE_PATH) != QPdfDocument::NoError) {
        std::cerr << "Failed to load the PDF document" << std::endl;
        return;
    }
}

void PdfHandler::renderPage(int pageNumber) {
    if (pageNumber < 0 || pageNumber >= document->pageCount()) {
        return;
    }

    // Get the page size in points (1/72 inch)
    QSizeF pageSize = document->pageSize(pageNumber);

    // Define the desired resolution in DPI
    const int dpi = 300;

    // Calculate the size in pixels
    QSize imageSize = pageSize.toSize() * dpi / 72;

    // Render the page with the calculated size
    QImage image = document->render(pageNumber, imageSize);

    // Update the QGraphicsScene with the rendered image
    this->scene->clear();
    this->scene->addPixmap(QPixmap::fromImage(image));
    this->view->resetTransform();
    this->view->scale(currentZoomLevel, currentZoomLevel);
    this->view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}
void PdfHandler::renderNextPage() {
    if (currentPage < document->pageCount() - 1) {
        currentPage++;
        renderPage(currentPage);
    }
}

void PdfHandler::renderPreviousPage() {
    if (currentPage > 0) {
        currentPage--;
        renderPage(currentPage);
    }
}

int PdfHandler::getCurrentPage() {
    return currentPage;
}

void PdfHandler::savePdf(QWidget* widget) {
    QString modifiedPdfFilePath = QFileDialog::getSaveFileName(widget, "Save PDF", "", "PDF Files (*.pdf)");
    if (modifiedPdfFilePath.isEmpty()) {
        return;
    }

    // Copy the modified PDF to the user-selected location
    QFile::copy(TEMP_FILE_PATH, modifiedPdfFilePath);
}

void PdfHandler::setZoomLevel(qreal zoomLevel) {
    currentZoomLevel = zoomLevel;
    view->scale(currentZoomLevel, currentZoomLevel);
    // view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void PdfHandler::zoomIn() {
    currentZoomLevel += 0.1;
    setZoomLevel(currentZoomLevel);
}

void PdfHandler::zoomOut() {
    currentZoomLevel -= 0.1;
    setZoomLevel(currentZoomLevel);
}

void PdfHandler::addTextToPage(const QString& text, const QPair<double, double> coordinates) {
    QPdfWriter writer(TEMP_FILE_PATH);
    writer.setResolution(300);
    QPainter painter(&writer);

    for (int i = 0; i < document->pageCount(); i++) {
        if (i > 0) {
            writer.newPage();
        }

        QImage image = document->render(i, QSize(writer.width(), writer.height()));
        painter.drawImage(0, 0, image);

        if (i == currentPage) {
            painter.setPen(Qt::red);
            painter.setFont(QFont("Arial", 12));
            painter.drawText(coordinates.first, coordinates.second, text);
        }
    }

    painter.end();
}
