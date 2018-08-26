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

#include "ecgmemory.h"

ECGmemory::ECGmemory()
{
    heartRate = 70;
    noiseFilter = true;

    showPWave = true;
    a_pwave = 0.15;
    d_pwave = 0.08;
    t_pwave = 0.15;
    positive_pwave = true;

    showQWave = true;
    a_qwave = 0.025;
    d_qwave = 0.066;
    t_qwave = 0.166;

    showQRSWave = true;
    a_qrswave = 1.0;
    d_qrswave = 0.08;
    positive_qrswave = true;

    showSWave = true;
    a_swave = 0.25;
    d_swave = 0.066;
    t_swave = 0.09;

    showTWave = true;
    a_twave = 0.30;
    d_twave = 0.18;
    t_twave = 0.2;
    positive_twave = true;

    showUWave = false;
    a_uwave = 0.035;
    d_uwave = 0.0476;
    t_uwave = 0.433;
}

//
// Preset signals
//

void ECGmemory::sinusRhythm()
{
    ECGmemory();
}

void ECGmemory::sinusBradycardia()
{
    ECGmemory();
    heartRate = 50;
}

void ECGmemory::sinusTachycardia()
{
    ECGmemory();
    heartRate = 110;
}

// TODO: Not implemented yet
// Atrial Fibrilation:
// Freq = 70; Without p-wave; qrs normal but irregular;
void ECGmemory::atrialFibrillation()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
// Rapid Atrial Fibrilation:
// Same as atrial fibrilation but with fast rate (120);
void ECGmemory::fastAtrialFibrillation()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
// Isolated PAC (premature atrial contraction):
// Without P-wave; QRS must be premature;
void ECGmemory::isolatedSVE()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
// Paired PAC:
// Double premature QRS; coupling interval 300ms;
void ECGmemory::pairedSVE()
{
    Q_ASSERT(false);
}

void ECGmemory::supraventricularTachychardia()
{
    ECGmemory();
    showPWave = false;
    heartRate = 180;
}

// TODO: Not implemented yet
// Introduce a pause between the 2 qrs complexes; > 2000ms; freq = 70;
void ECGmemory::sinusPause()
{
    Q_ASSERT(false);
}

void ECGmemory::junctionalRhythm()
{
    ECGmemory();

    heartRate = 47;
    showPWave = false;
    showQWave = false;
}

void ECGmemory::acceleratedJunctionalRhythm()
{
    ECGmemory();

    heartRate = 80;
    t_pwave = 0.12;
    showQWave = false;
    positive_pwave = false;
}

void ECGmemory::idioventricularRhythm()
{
    ECGmemory();

    heartRate = 35;
    showPWave = false;
    showQWave = false;
    d_qrswave = 0.16;
    positive_twave = false;
}

void ECGmemory::acceleratedIdioventricularRhythm()
{
    ECGmemory();

    heartRate = 65;
    showPWave = false;
    showQWave = false;
    d_qrswave = 0.16;
    positive_twave = false;
}

// TODO: Not implemented yet
void ECGmemory::sinoAtrialBlock()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
void ECGmemory::isolatedMonoVE()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
void ECGmemory::isolatedPolyVE()
{
    Q_ASSERT(false);
}

void ECGmemory::monomorphicVT()
{
    ECGmemory();

    heartRate = 195;
    t_pwave = 0.08;
    a_pwave = 0;
    d_pwave = 0.01;
    a_qrswave = 2;
    d_qrswave = 0.15;
    a_twave = 0.4;
    d_twave = 0.16;
    positive_twave = false;
}

// TODO: Not implemented yet
void ECGmemory::polymorphicVT()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
void ECGmemory::ventricularFibrillation()
{
    Q_ASSERT(false);
}

void ECGmemory::firstDegreeAVBlock()
{
    ECGmemory();

    heartRate = 62;
    showQWave = false;
    t_pwave = 0.3;
}

// TODO: Not implemented yet
void ECGmemory::type1AVBlock()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
void ECGmemory::type2AVBlock()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
void ECGmemory::twoOneAVBlock()
{
    Q_ASSERT(false);
}

// TODO: Not implemented yet
void ECGmemory::dissociation()
{
    Q_ASSERT(false);
}

ECGmemory &ECGmemory::operator=(const ECGmemory &other)
{
    heartRate = other.heartRate;
    noiseFilter = other.noiseFilter;

    showPWave = other.showPWave;
    a_pwave = other.a_pwave;
    d_pwave = other.d_pwave;
    t_pwave = other.t_pwave;
    positive_pwave = other.positive_pwave;

    showQWave = other.showQWave;
    a_qwave = other.a_qwave;
    d_qwave = other.d_qwave;
    t_qwave = other.t_qwave;

    showQRSWave = other.showQRSWave;
    a_qrswave = other.a_qrswave;
    d_qrswave = other.d_qrswave;
    positive_qrswave = other.positive_qrswave;

    showSWave = other.showSWave;
    a_swave = other.a_swave;
    d_swave = other.d_swave;
    t_swave = other.t_swave;

    showTWave = other.showTWave;
    a_twave = other.a_twave;
    d_twave = other.d_twave;
    t_twave = other.t_twave;
    positive_twave = other.positive_twave;

    showUWave = other.showUWave;
    a_uwave = other.a_uwave;
    d_uwave = other.d_uwave;
    t_uwave = other.t_uwave;

    return *this;
}
