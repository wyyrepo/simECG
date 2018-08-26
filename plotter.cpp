/****************************************************************************
**
** Antonio Cardoso Martins    (digiplan.pt@gmail.com)
** Paulo Dias Costa           (mestre.do.pau@gmail.com)
** João Silva Marques         (joaomiguelsilvamarques@gmail.com)
**
** Copyright (c) 2009 All Rights Reserved
**
** Date: May 2009
**
** This file is part of simECG
**
** simECG is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** simECG is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include <QtGui>

#include "plotter.h"
#include <QStylePainter>
#include <QLabel>
#include <QStyleOptionFocusRect>

using namespace std;

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
    QPalette myPalette;
    myPalette.setColor(QPalette::Window, Qt::white);
    setPalette(myPalette);
    setBackgroundRole(QPalette::Window);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    showScale = false;
    showData = true;
    ecgPaperDisplay = true;

    // Prepare the heartRate QLabel display widget in the right corner
    heartRateDisplay.setParent(this);
    heartRateDisplay.setText(QString("<html><body style=\"font-size:28pt;\">\n200</body></html>"));
    heartRateDisplay.setAlignment(Qt::AlignRight);
    heartRateDisplay.setFixedSize(heartRateDisplay.sizeHint());
    updateHeartRateDisplay();

    plotSettings = PlotSettings();
    refreshPixmap();
}


void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
    curveMap[id] = data;
    refreshPixmap();
}


void Plotter::clearCurve(int id)
{
    curveMap.remove(id);
    refreshPixmap();
}


QSize Plotter::minimumSizeHint() const
{
    return QSize(6 * Margin, 4 * Margin);
}


QSize Plotter::sizeHint() const
{
    return QSize(12 * Margin, 8 * Margin);
}


void Plotter::displayData(bool status)
{
    showData = status;
    //heartRateDisplay.setShown(status);
    refreshPixmap();
}

void Plotter::setEcgPaperDisplay(const bool &status)
{
    QPalette myPalette;

    ecgPaperDisplay = status;

    if (ecgPaperDisplay) {
        myPalette.setColor(QPalette::Window, Qt::white);
        myPalette.setColor(QPalette::WindowText, Qt::black);
    } else {
        myPalette.setColor(QPalette::Window, Qt::black);
        myPalette.setColor(QPalette::WindowText, Qt::white);
    }
    setPalette(myPalette);

    refreshPixmap();
}

void Plotter::paintEvent(QPaintEvent * /* event */)
{
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, pixmap);

    if (hasFocus()) {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = Qt::white;
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}

void Plotter::resizeEvent(QResizeEvent * /* event */)
{
    heartRateDisplay.move(width() - heartRateDisplay.width() - 40, 30);
    refreshPixmap();
}

void Plotter::refreshPixmap()
{
    pixmap = QPixmap(size());
    pixmap.fill(this, 0, 0);

    QPainter painter(&pixmap);
    painter.initFrom(this);

    // Paint paper background
    if (ecgPaperDisplay) {
        drawGridPaper(&painter);
    }

    // Paint curve and heart rate
    if (showData) {
        drawCurves(&painter);
        updateHeartRateDisplay();
    }
    update();
}


/**
  *
  * Draws the background grid as ECG paper
  *
**/
void Plotter::drawGridPaper(QPainter *painter)
{
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
    if (!rect.isValid()) return;

    QPen gridColor(QColor(0xFF, 0xC0, 0xC0), 0, Qt::DotLine, Qt::RoundCap);

    for (int i = 0; i <= plotSettings.numXTicks; ++i) {
        int x = rect.left() + (i * (rect.width() - 1) / plotSettings.numXTicks);
        double label = plotSettings.minX + (i * plotSettings.spanX() / plotSettings.numXTicks);
        // Draw the grid (x)
        if (!(i % 25)) {
            gridColor.setWidth(2);
        } else if (!(i % 5)) {
            gridColor.setWidth(1);
        } else {
            gridColor.setWidth(0);
        }
        painter->setPen(gridColor);
        painter->drawLine(x, rect.top(), x, rect.bottom());
        // Draw the scale (x)
        if (showScale) {
            painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
            // Draw the numbers
            if (!(i % 5)) {
                painter->drawText(x - 50, rect.bottom() + 5, 100, 15,
                                  Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
            }
        }
    }

    for (int j = 0; j <= plotSettings.numYTicks; ++j) {
        int y = rect.bottom() - (j * (rect.height() - 1) / plotSettings.numYTicks);
        double label = plotSettings.minY + (j * plotSettings.spanY() / plotSettings.numYTicks);
        // Draw the grid (y)
        if (!(j % 25)) {
            gridColor.setWidth(2);
        } else if (!(j % 5)) {
            gridColor.setWidth(1);
        } else {
            gridColor.setWidth(0);
        }
       painter->setPen(gridColor);
       painter->drawLine(rect.left(), y, rect.right(), y);
        // Draw the scale (y)
        if (showScale) {
            painter->drawLine(rect.left() - 5, y, rect.left(), y);
            // Draw the numbers
            if (!(j % 5)) {
                painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20,
                                  Qt::AlignRight | Qt::AlignVCenter, QString::number(label));
            }
        }
    }

    painter->drawRect(rect.adjusted(0, 0, -1, -1));
}



void Plotter::drawCurves(QPainter *painter)
{
    static QColor colorForIds[6] = {
        Qt::black, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow
    };
    // If the display type is monitor, signal is shown white. Green otherwise
    if (ecgPaperDisplay) {
        colorForIds[0] = Qt::black;
    } else {
        colorForIds[0] = QColor(0x2f, 0xe2, 0x2f);
    }

    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
    if (!rect.isValid()) return;

    painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

    QMapIterator<int, QVector<QPointF> > i(curveMap);
    while (i.hasNext()) {
        i.next();

        int id = i.key();
        const QVector<QPointF> &data = i.value();
        QPolygonF polyline(data.count());

        for (int j = 0; j < data.count(); ++j) {
            double dx = data[j].x() - plotSettings.minX;
            double dy = data[j].y() - plotSettings.minY;
            double x = rect.left() + (dx * (rect.width() - 1) / plotSettings.spanX());
            double y = rect.bottom() - (dy * (rect.height() - 1) / plotSettings.spanY());
            polyline[j] = QPointF(x, y);
        }
        painter->setPen(colorForIds[uint(id) % 6]);
        painter->drawPolyline(polyline);
    }
}

void Plotter::updateHeartRateDisplay()
{
    QString rate = QString("<html><body style=\"font-size:22pt;\">\n%1</body></html>").arg(heartRate);
    heartRateDisplay.setText(rate);
}

//
// PlotSettings class
//

PlotSettings::PlotSettings()
{
    minX = 0;
    maxX = 6;
    numXTicks = 150;

    minY = -2.0;
    maxY = 2.0;
    numYTicks = 40;
}

void PlotSettings::scroll(int dx, int dy)
{
    double stepX = spanX() / numXTicks;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = spanY() / numYTicks;
    minY += dy * stepY;
    maxY += dy * stepY;
}

void PlotSettings::adjust()
{
    adjustAxis(minX, maxX, numXTicks);
    adjustAxis(minY, maxY, numYTicks);
}

void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 4;
    double grossStep = (max - min) / MinTicks;
    double step = pow(10.0, floor(log10(grossStep)));

    if (5 * step < grossStep) {
        step *= 5;
    } else if (2 * step < grossStep) {
        step *= 2;
    }

    numTicks = int(ceil(max / step) - floor(min / step));
    if (numTicks < MinTicks)
        numTicks = MinTicks;
    min = floor(min / step) * step;
    max = ceil(max / step) * step;
}
