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

#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>

#include "assessmentframe.h"
#include "ecgmemory.h"

#define PRESETSTAB      0
#define CUSTOMTAB       1
#define ASSESSMENTTAB   2

namespace Ui
{
    class myMainWindowClass;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    myMainWindow(QWidget *parent = 0);
    ~myMainWindow();
    QList<QAbstractButton *> getPresetsButtons();

private:
    Ui::myMainWindowClass *ui;
    ECGmemory otherMemory;
    AssessmentFrame *assessment;
    int currentTab;

private slots:
    void on_action_About_triggered();
    void on_action_Exit_triggered();
    void optionsTabChanged(int);

public slots:
    void changePWavePositiveness(int);
    void changeTWavePositiveness(int);
};

#endif
