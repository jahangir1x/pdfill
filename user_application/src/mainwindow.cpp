#include "mainwindow.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPdfDocument>
#include <QPdfDocumentRenderOptions>
#include <QPdfWriter>
#include <iostream>
#include <ostream>

#include "infodb.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    textInput = new QLineEdit(this);
    addTextButton = new QPushButton("Add Text", this);
    saveButton = new QPushButton("Save PDF", this);

    ui->horizontalLayout->addWidget(textInput);
    ui->horizontalLayout->addWidget(addTextButton);
    ui->horizontalLayout->addWidget(saveButton);

    connect(addTextButton, &QPushButton::clicked, this, &MainWindow::on_addTextButton_clicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);

    pdfHandler = new PdfHandler(scene, ui->graphicsView);
    pdfHandler->renderPage(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_nextButton_clicked() {
    pdfHandler->renderNextPage();
}

void MainWindow::on_prevButton_clicked() {
    pdfHandler->renderPreviousPage();
}

void MainWindow::on_addTextButton_clicked() {
    QString text = textInput->text();
    if (!text.isEmpty()) {
        InfoDb *infoDb = new InfoDb();
        pdfHandler->addTextToPage(text, infoDb->getCoordinates(10));
        pdfHandler->renderPage(pdfHandler->getCurrentPage());
    }
}

void MainWindow::on_saveButton_clicked() {
    pdfHandler->savePdf(this);
}

void MainWindow::on_zoomInButton_clicked() {
    pdfHandler->zoomIn();
}

void MainWindow::on_zoomOutButton_clicked() {
    pdfHandler->zoomOut();
}
