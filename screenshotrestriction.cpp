#include "screenshotrestriction.h"
#include <QLabel>
#include <QPainter>

ScreenShotRestriction::ScreenShotRestriction(const QPixmap &screenshot, QWidget *parent) :
    QDialog(parent), screen(screenshot), origin(-1, -1)
{

}

void ScreenShotRestriction::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        close();
    else if(e->key() == Qt::Key_Return)
    {
        if(selectionRect.isValid())
        {
            QPixmap selection = screen.copy(selectionRect);
            emit imageCaptured(selection);
            close();
        }
    }
}

void ScreenShotRestriction::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter paint(this);

    paint.drawPixmap(QPoint(0, 0), screen);
    QColor fillColor(128, 128, 128, 100);
    selectionRect = selectionRect.normalized();

    paint.fillRect(0, 0, selectionRect.x(), height(), fillColor);
    paint.fillRect(selectionRect.x(), 0, selectionRect.width(), selectionRect.y(), fillColor);
    paint.fillRect(selectionRect.x()+selectionRect.width(), 0, width()-selectionRect.width(), height(), fillColor);
    paint.fillRect(selectionRect.x(), selectionRect.y()+selectionRect.height(), selectionRect.width(), height()-(selectionRect.y()+selectionRect.height()), fillColor);
}

void ScreenShotRestriction::mousePressEvent(QMouseEvent *e)
{
    origin = e->pos();
}

void ScreenShotRestriction::mouseMoveEvent(QMouseEvent *e)
{
    if(origin != QPoint(-1, -1))
    {
        mousePos = e->pos();
        selectionRect = QRect(origin, mousePos);
        selectionRect = selectionRect.normalized();
        update();
    }
}

void ScreenShotRestriction::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    origin = QPoint(-1, -1);
}
