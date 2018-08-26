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

#ifndef QVECTORPLUS_H
#define QVECTORPLUS_H

#include <QVector>

//template <typename T>
class QVectorPlus : public QVector<double>
{
public:
    inline QVectorPlus() : QVector<double>() {}
    inline QVectorPlus(int size, const double &initVal) : QVector<double>(size, initVal) {}
    QVectorPlus &uniMatrixAdd(const double &);
    QVectorPlus &uniMatrixAdd(QVectorPlus &);
    inline QVectorPlus &uniMatrixSubtract(const double &value)
        { return uniMatrixAdd(-value); }
    QVectorPlus &uniMatrixSubtract(QVectorPlus &);
    QVectorPlus &uniMatrixMultiply(const double &);
    QVectorPlus &uniMatrixMultiply(QVectorPlus &);
};

#endif // QVECTORPLUS_H
