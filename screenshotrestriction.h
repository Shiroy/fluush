#ifndef SCREENSHOTRESTRICTION_H
#define SCREENSHOTRESTRICTION_H

#include <QDialog>
#include <QPixmap>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>

class ScreenShotRestriction : public QDialog
{
    Q_OBJECT
public:
    explicit ScreenShotRestriction(const QPixmap &screenchot, QWidget *parent = 0);

    virtual void keyPressEvent(QKeyEvent *e);
    virtual void paintEvent(QPaintEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

signals:
    void imageCaptured(QPixmap p);
public slots:

private:
    const QPixmap screen;
    QPoint origin;
    QPoint mousePos;
    QRect selectionRect;

};

#endif // SCREENSHOTRESTRICTION_H
