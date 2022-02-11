#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QFileDialog>

#include "annotationwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();

private:
    void createActions();
    void createMenu();
    void createToolBar();

    QAction *_newFileAction;
    QAction *_quitAction;

    QAction *_rouge;
    QAction *_vert;
    QAction *_bleu;
    QAction *_noir;
    QAction *_reset;

    AnnotationWidget *_annotationWidget;
};

#endif // MAINWINDOW_H
