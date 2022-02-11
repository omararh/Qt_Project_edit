#include "annotationwidget.h"

const QColor AnnotationWidget::DEFAULT_PEN_COLOR(Qt::black);
const QPoint AnnotationWidget::NO_POINT(-1, -1);

AnnotationWidget::AnnotationWidget(QWidget *parent) : QWidget(parent), _pixmap(nullptr), _filename(), _oldPos(NO_POINT), _pen()
{
    initDefaultPixMap();

    _pen.setColor(DEFAULT_PEN_COLOR);
    _pen.setWidth(DEFAULT_PEN_WIDTH);
}

AnnotationWidget::~AnnotationWidget() {
	delete _pixmap;
}

void AnnotationWidget::loadImage(const QString &fileName) {
    QFile imgFile(fileName);
    if(imgFile.exists()) {
        if(!_pixmap) {
            _pixmap = new QPixmap;
        }
        if(!_pixmap->load(fileName)) {
            initDefaultPixMap();
            return;
        }
        _filename=fileName;

        // On redimensionne le widget en fonction de l'image
        QSize widgetSize(_pixmap->size());
        QSize screenSize = QGuiApplication::screenAt(topLevelWidget()->geometry().topLeft())->availableSize();
        // Tout en faisant attention à ne pas dépasser la taille de l'écran
        if(widgetSize.height() > screenSize.height()) {
            widgetSize.setHeight(screenSize.height());
        }
        if(widgetSize.width() > screenSize.width()) {
            widgetSize.setWidth(screenSize.width());
        }
        setMinimumSize(widgetSize);
    } else {
        // Si le fichier n'existe pas, on remet le texte par défaut
        initDefaultPixMap();
    }

    // On redessine le widget
    update();
}

void AnnotationWidget::setBlue(bool) {
    _pen.setColor(Qt::blue);
}

void AnnotationWidget::setBlack(bool) {
    _pen.setColor(Qt::black);
}

void AnnotationWidget::setGreen(bool) {
    _pen.setColor(Qt::green);
}

void AnnotationWidget::setRed(bool) {
    _pen.setColor(Qt::red);
}

void AnnotationWidget::setPenSize(int size) {
    _pen.setWidth(size);
}

void AnnotationWidget::reset(bool) {
    if(_filename.isEmpty() || !_pixmap->load(_filename)) {
        initDefaultPixMap();
    }
    update();
}

void AnnotationWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, *_pixmap);
}

void AnnotationWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        drawLine(event->pos());
    }
}

void AnnotationWidget::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        drawLine(event->pos());
    }
}

void AnnotationWidget::mouseReleaseEvent(QMouseEvent *) {
    _oldPos = NO_POINT;
}

void AnnotationWidget::initDefaultPixMap() {
    setMinimumSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    if(_pixmap) {
        delete _pixmap;
    }
    _pixmap = new QPixmap(this->size());
    QPainter painter(_pixmap);
    painter.fillRect(rect(), this->palette().background());
    painter.setPen(Qt::black);
    painter.drawText(rect(), Qt::AlignHCenter | Qt::AlignVCenter, tr("Load a picture to annotate it..."));
}

void AnnotationWidget::drawLine(const QPoint &endPoint) {
    QPainter painter(_pixmap);
    painter.setPen(_pen);

    if(_oldPos == NO_POINT) {
        painter.drawPoint(endPoint);
    } else {
        painter.drawLine(_oldPos, endPoint);
    }
    _oldPos = endPoint;

    update();
}
