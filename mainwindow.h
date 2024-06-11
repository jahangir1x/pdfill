#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPdfDocument>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPdfDocument *document;
    int currentPage;
    QLineEdit *textInput;
    QPushButton *addTextButton;
    QPushButton *saveButton;
    void displayPage(int pageNumber);
    void addTextToPage(const QString &text);
};

#endif // MAINWINDOW_H
