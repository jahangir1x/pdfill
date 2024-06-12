#ifndef PDFHANDLER_H
#define PDFHANDLER_H

#include <qgraphicsscene.h>

#include <QPdfDocument>
#include <QtWidgets/QGraphicsView>

#define TEMP_FILE_PATH "./temp.pdf"
#define PDF_FILE_PATH "./document.pdf"
class PdfHandler {
   public:
    PdfHandler(QGraphicsScene *scene, QGraphicsView *view);
    ~PdfHandler();
    void renderPage(int pageNumber);
    void renderNextPage();
    void renderPreviousPage();
    int getCurrentPage();
    void savePdf(QWidget *widget);
    void setZoomLevel(qreal zoomLevel);
    void zoomIn();
    void zoomOut();
    qreal getZoomLevel();
    void addTextToPage(const QString &text, const QPair<double, double> coordinates);

   private:
    QPdfDocument *document;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QString pdfFilePath;
    int currentPage;
};

#endif  // PDFHANDLER_H
