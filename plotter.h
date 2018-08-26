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

#ifndef PLOTTER_H
#define PLOTTER_H

#include <QMap>
#include <QPixmap>
#include <QWidget>
#include <QLabel>

//
// PlotSettings class
//

class PlotSettings
{

public:
    PlotSettings();

    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX; }
    double spanY() const { return maxY - minY; }

    double minX;
    double maxX;
    int numXTicks;
    double minY;
    double maxY;
    int numYTicks;

private:
    static void adjustAxis(double &min, double &max, int &numTicks);
};


//
// Plotter class
//

class Plotter : public QWidget
{
    Q_OBJECT

public:
    Plotter(QWidget *parent = 0);

    void setCurveData(int id, const QVector<QPointF> &data);
    void clearCurve(int id);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    inline void setHeartRate(const int &rate) { heartRate = rate; }

public slots:
    void displayData(bool status);
    void setEcgPaperDisplay(const bool &);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void refreshPixmap();
    void drawGridPaper(QPainter *painter);
    void drawCurves(QPainter *painter);
    void updateHeartRateDisplay();

    enum { Margin = 10 };

    QMap<int, QVector<QPointF> > curveMap;
    QPixmap pixmap;
    PlotSettings plotSettings;
    bool showScale;                     // True if grid scale is to be shown
    bool showData;                      // True if curve data is to be displayed
    bool ecgPaperDisplay;               // True if ECG paper type display, vital monitor otherwise
    QLabel heartRateDisplay;            // The widget that shows heart rate
    int heartRate;                      // Current heart rate value
};

#endif
