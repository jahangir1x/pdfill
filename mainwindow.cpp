#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPdfDocument>
#include <QGraphicsPixmapItem>
#include <QPdfDocumentRenderOptions>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , document(new QPdfDocument(this))
    , currentPage(0)
{
    ui->setupUi(this);

    // Initialize the QGraphicsScene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Load the PDF document
    QString pdfFilePath = QFileDialog::getOpenFileName(this, "Open PDF", "", "PDF Files (*.pdf)");
    if (document->load(pdfFilePath) != QPdfDocument::NoError) {
        // Handle error
        return;
    }

    // Set up the text input and buttons
    textInput = new QLineEdit(this);
    addTextButton = new QPushButton("Add Text", this);
    saveButton = new QPushButton("Save PDF", this);

    ui->verticalLayout->addWidget(textInput);
    ui->verticalLayout->addWidget(addTextButton);
    ui->verticalLayout->addWidget(saveButton);

    connect(addTextButton, &QPushButton::clicked, this, &MainWindow::on_addTextButton_clicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);

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
    QSize imageSize = pageSize.toSize() * dpi / 72;

    // Render the page with the calculated size
    QImage image = document->render(pageNumber, imageSize);

    // Update the QGraphicsScene with the rendered image
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_nextButton_clicked()
{
    if (currentPage < document->pageCount() - 1) {
        currentPage++;
        displayPage(currentPage);
    }
}

void MainWindow::on_prevButton_clicked()
{
    if (currentPage > 0) {
        currentPage--;
        displayPage(currentPage);
    }
}

void MainWindow::on_addTextButton_clicked()
{
    QString text = textInput->text();
    if (!text.isEmpty()) {
        addTextToPage(text);
        displayPage(currentPage); // Re-display the current page to show the added text
    }
}

void MainWindow::addTextToPage(const QString &text)
{
    QString pdfFilePath = "/home/zinis/document.pdf";
    QString modifiedPdfFilePath = "/home/zinis/document_modified.pdf";

    // Open the original PDF
    QFile pdfFile(pdfFilePath);
    if (!pdfFile.open(QIODevice::ReadOnly)) {
        // Handle error
        return;
    }

    // Create a PDF writer to write the modified PDF
    QPdfWriter writer(modifiedPdfFilePath);
    writer.setResolution(300);

    QPainter painter(&writer);

    for (int i = 0; i < document->pageCount(); ++i) {
        if (i > 0) {
            writer.newPage();
        }

        // Render the current page
        QImage image = document->render(i, QSize(writer.width(), writer.height()));
        painter.drawImage(0, 0, image);

        if (i == currentPage) {
            // Add the text to the current page
            painter.setPen(Qt::black);
            painter.setFont(QFont("Helvetica", 12));
            painter.drawText(100, 100, text); // Adjust the position as needed
        }
    }

    painter.end();
}

void MainWindow::on_saveButton_clicked()
{
    QString modifiedPdfFilePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (modifiedPdfFilePath.isEmpty()) {
        return;
    }

    // Copy the modified PDF to the user-selected location
    QFile::copy("/home/zinis/document_modified.pdf", modifiedPdfFilePath);
}
