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

#include <QApplication>
#include <QSplashScreen>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QTime>
#include <QLabel>
#include "version.h"
#include <QThread>
#include "mymainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Setup a splash screen
    QLabel *versionDisplay = new QLabel;
    QPixmap pixmap(":/images/simecg-ss1.png");
    QSplashScreen splash(pixmap);
    // Display version number on splash screen
    versionDisplay->setParent((QWidget *)&splash);
    versionDisplay->setText(QString(QObject::tr("version ") + BUILDVERSION));
    versionDisplay->setFixedSize(versionDisplay->sizeHint());
    versionDisplay->move(pixmap.size().width() * 0.90 - versionDisplay->width(),
                        pixmap.size().height() * 0.95 - versionDisplay->height());
    splash.show();

    // Initialize random number generator
    // Used in classes:
    //     Assessment to select random questions
    //     ECGPlotter to generate signal noise
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    // Internacionalization (i18n) support
    QTranslator qtTranslator, myappTranslator;
    QString locale = QLocale::system().name();
    qDebug("System locale is %s", locale.toLatin1().constData());

    // Load translation strings
    qtTranslator.load("qt_" +locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    myappTranslator.load(":/translations/simecg_" + locale);
    app.installTranslator(&myappTranslator);

    myMainWindow w;

    app.processEvents();

    // Usually the splash screen takes a short moment, so we insert
    // some 2 more seconds for it to be seen by the user
    // Windows do not implement the same way as Linux and others
#ifdef Q_WS_WIN
    _sleep(1000);           // For the windows platform only
#else
    QThread::sleep(2);               // Every other platform
#endif

    w.show();
    splash.finish(&w);
    return app.exec();
}
