#ifndef ANNOTATIONWIDGET_H
#define ANNOTATIONWIDGET_H

#include <QWidget>
#include <QColor>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QPen>
#include <QPainter>
#include <QScreen>
#include <QGuiApplication>

class AnnotationWidget : public QWidget
{
    Q_OBJECT
public:
    AnnotationWidget(QWidget *parent = nullptr);
    ~AnnotationWidget();

    void loadImage(const QString &fileName);

    static const int DEFAULT_PEN_WIDTH=3;
    static const QColor DEFAULT_PEN_COLOR;

public slots:
    void setBlue(bool);
    void setRed(bool);
    void setBlack(bool);
    void setGreen(bool);
    void setPenSize(int size);
    void reset(bool);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    void initDefaultPixMap();
    void drawLine(const QPoint &endPoint);

    static const QPoint NO_POINT;
    static const int DEFAULT_WIDTH=800;
    static const int DEFAULT_HEIGHT=600;

    QPixmap *_pixmap;
    QString _filename;
    QPoint _oldPos;

    QPen _pen;
};

#endif // ANNOTATIONWIDGET_H
