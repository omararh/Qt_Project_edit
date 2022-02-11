#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _annotationWidget = new AnnotationWidget(this);
    setCentralWidget(_annotationWidget);

    createActions();
    createMenu();
    createToolBar();

    statusBar()->showMessage(tr("Load a file..."));
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Load a picture ..."), QString(), tr("Images (*.png *.jpg)"));
    _annotationWidget->loadImage(filename);
    // On redimensionne la fenêtre en fonction de l'image
    adjustSize();
    setStatusTip(tr("Loading picture %1 ...").arg(filename));
}

void MainWindow::createActions() {
    _newFileAction = new QAction(tr("Load a picture"), this);
    _newFileAction->setShortcut(QKeySequence::Open); // Open = CTRL+O
    //_newFileAction->setShortcut(tr("CTRL+O")); // Autre possibilité
    //_newFileAction->setShortcut(Qt::Key_Control + Qt::Key_O); // Autre possibilité, mais non-conseillée
    _newFileAction->setStatusTip(tr("Load a picture to annotate it"));
    connect(_newFileAction, &QAction::triggered, this, &MainWindow::newFile);

    _quitAction = new QAction(tr("Exit"), this);
    _quitAction->setShortcut(QKeySequence::Quit); // Quit = CTRL+Q
    _quitAction->setStatusTip(tr("Close the application"));
    connect(_quitAction, &QAction::triggered, this, &QApplication::quit);

    _rouge = new QAction(tr("Red"), this);
    _rouge->setStatusTip(tr("Change pen color to red"));
    connect(_rouge, &QAction::triggered, _annotationWidget, &AnnotationWidget::setRed);

    _vert = new QAction(tr("Green"), this);
    _vert->setStatusTip(tr("Change pen color to green"));
    connect(_vert, &QAction::triggered, _annotationWidget, &AnnotationWidget::setGreen);

    _bleu = new QAction(tr("Blue"), this);
    _bleu->setStatusTip(tr("Change pen color to blue"));
    connect(_bleu, &QAction::triggered, _annotationWidget, &AnnotationWidget::setBlue);

    _noir = new QAction(tr("Black"), this);
    _noir->setStatusTip(tr("Change pen color to black"));
    connect(_noir, &QAction::triggered, _annotationWidget, &AnnotationWidget::setBlack);

    _reset = new QAction(tr("Erase annotations"), this);
    _reset->setStatusTip(tr("Erase annotations and load back original picture"));
    connect(_reset, &QAction::triggered, _annotationWidget, &AnnotationWidget::reset);
}

void MainWindow::createMenu() {
    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(_newFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(_quitAction);

    QMenu *editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addSection(tr("Changing color to..."));
    editMenu->addAction(_noir);
    editMenu->addAction(_rouge);
    editMenu->addAction(_vert);
    editMenu->addAction(_bleu);
    editMenu->addSeparator();
    editMenu->addAction(_reset);
}

void MainWindow::createToolBar() {
    QToolBar *toolBar = addToolBar(tr("Buttons"));

    toolBar->addWidget(new QLabel(tr("Pen size:")));

    QSpinBox *penSize = new QSpinBox(this);
    penSize->setMinimum(1);
    penSize->setValue(AnnotationWidget::DEFAULT_PEN_WIDTH);
    penSize->setStatusTip(tr("Change pen size"));
    connect(penSize, QOverload<int>::of(&QSpinBox::valueChanged), _annotationWidget, &AnnotationWidget::setPenSize);

    toolBar->addWidget(penSize);

    toolBar->addSeparator();

    toolBar->addAction(_noir);
    toolBar->addAction(_rouge);
    toolBar->addAction(_vert);
    toolBar->addAction(_bleu);

    toolBar->addSeparator();

    toolBar->addAction(_reset);
}
