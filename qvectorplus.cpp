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

#include "qvectorplus.h"

// Unidimentional Matrix addition operation with number
QVectorPlus &QVectorPlus::uniMatrixAdd(const double &other)
{
    for (int i = 0; i < this->size(); i++) {
        (*this)[i] += other;
    }
    return *this;
}


// Unidimentional Matrix addition operation with another unidimentional matrix
QVectorPlus &QVectorPlus::uniMatrixAdd(QVectorPlus &other)
{
    // Matrix must be equal in size
    Q_ASSERT(this->size() == other.size());

    for (int i = 0; i < this->size(); i++) {
        (*this)[i] += other[i];
    }
    return *this;
}


// Unidimentional Matrix subtraction operation with another unidimentional matrix
QVectorPlus &QVectorPlus::uniMatrixSubtract(QVectorPlus &other)
{
    // Matrix must be equal in size
    Q_ASSERT(this->size() == other.size());

    for (int i = 0; i < this->size(); i++) {
        (*this)[i] -= other[i];
    }
    return *this;
}


// Unidimentional Matrix multiplication operation with number
QVectorPlus &QVectorPlus::uniMatrixMultiply(const double &other)
{
    for (int i = 0; i < this->size(); i++) {
        (*this)[i] *= other;
    }
    return *this;
}


// Unidimentional Matrix multiplication operation with another unidimentional matrix
QVectorPlus &QVectorPlus::uniMatrixMultiply(QVectorPlus &other)
{
    // Matrix must be equal in size
    Q_ASSERT(this->size() == other.size());

    for (int i = 0; i < this->size(); i++) {
        (*this)[i] *= other[i];
    }
    return *this;
}
