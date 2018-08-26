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

#ifndef ECGMEMORY_H
#define ECGMEMORY_H

#include <QObject>

#define MAXNOISE 0.10             // Maximum allowable noise percentage (10%)

class ECGmemory : public QObject
{
public:
    ECGmemory();

    // GET methods
    inline const int &getHeartRate() { return heartRate; }
    inline const bool &getNoiseFilter() { return noiseFilter; }

    // P wave
    inline const bool &getDisplayPWave() { return showPWave; }
    inline const double &getAmplitude_P_wave() { return a_pwave; }
    inline const double &getDuration_P_wave() { return d_pwave; }
    inline const double &getInterval_P_wave() { return t_pwave; }
    inline const bool &getPositive_P_wave() { return positive_pwave; }
    // Q wave
    inline const bool &getDisplayQWave() { return showQWave; }
    inline const double &getAmplitude_Q_wave() { return a_qwave; }
    inline const double &getDuration_Q_wave() { return d_qwave; }
    inline const double &getInterval_Q_wave() { return t_qwave; }
    // QRS wave
    inline const bool &getDisplayQRSWave() { return showQRSWave; }
    inline const double &getAmplitude_QRS_wave() { return a_qrswave; }
    inline const double &getDuration_QRS_wave() { return d_qrswave; }
    inline const bool &getPositive_QRS_wave() { return positive_qrswave; }
    // S wave
    inline const bool &getDisplaySWave() { return showSWave; }
    inline const double &getAmplitude_S_wave() { return a_swave; }
    inline const double &getDuration_S_wave() { return d_swave; }
    inline const double &getInterval_S_wave() { return t_swave; }
    // T wave
    inline const bool &getDisplayTWave() { return showTWave; }
    inline const double &getAmplitude_T_wave() { return a_twave; }
    inline const double &getDuration_T_wave() { return d_twave; }
    inline const double &getInterval_T_wave() { return t_twave; }
    inline const bool &getPositive_T_wave() { return positive_twave; }
    // U wave
    inline const bool &getDisplayUWave() { return showUWave; }
    inline const double &getAmplitude_U_wave() { return a_uwave; }
    inline const double &getDuration_U_wave() { return d_uwave; }
    inline const double &getInterval_U_wave() { return t_uwave; }

    // SET methods
    inline void setHeartRate(const int &hr) { heartRate = hr; }
    inline void setNoiseFilter(const bool &status) { noiseFilter = status; }

    // Set separate parameters
    inline void set_P_wave(const double &a, const double &d, const double &t)
        {a_pwave = a; d_pwave = d; t_pwave =t; }
    inline void set_Q_wave(const double &a, const double &d, const double &t)
        {a_qwave = a; d_qwave = d; t_qwave =t; }
    inline void set_QRS_wave(const double &a, const double &d)
        {a_qrswave = a; d_qrswave = d; }
    inline void set_S_wave(const double &a, const double &d, const double &t)
        {a_swave = a; d_swave = d; t_swave = t; }
    inline void set_T_wave(const double &a, const double &d, const double &t)
        {a_twave = a; d_twave = d; t_twave = t; }
    inline void set_U_wave(const double &a, const double &d, const double &t)
        {a_uwave = a; d_uwave = d; t_uwave = t; }
    // P wave
    void setAmplitude_P_wave(const double &a) { a_pwave = a; }
    void setDuration_P_wave(const double &d) { d_pwave = d; }
    void setInterval_P_wave(const double &t) { t_pwave = t; }
    void setPositive_P_wave(const bool &p) { positive_pwave = p; }
    // Q wave
    void setAmplitude_Q_wave(const double &a) { a_qwave = a; }
    void setDuration_Q_wave(const double &d) { d_qwave = d; }
    void setInterval_Q_wave(const double &t) { t_qwave = t; }
    // QRS wave
    void setAmplitude_QRS_wave(const double &a) { a_qrswave = a; }
    void setDuration_QRS_wave(const double &d) { d_qrswave = d; }
    // no interval
    void setPositive_QRS_wave(const bool &p) { positive_qrswave = p; }
    // S wave
    void setAmplitude_S_wave(const double &a) { a_swave = a; }
    void setDuration_S_wave(const double &d) { d_swave = d; }
    void setInterval_S_wave(const double &t) { t_swave = t; }
    // T wave
    void setAmplitude_T_wave(const double &a) { a_twave = a; }
    void setDuration_T_wave(const double &d) { d_twave = d; }
    void setInterval_T_wave(const double &t) { t_twave = t; }
    void setPositive_T_wave(const bool &p) { positive_twave = p; }
    // U wave
    void setAmplitude_U_wave(const double &a) { a_uwave = a; }
    void setDuration_U_wave(const double &d) { d_uwave = d; }
    void setInterval_U_wave(const double &t) { t_uwave = t; }

    // Preset signals
    void sinusRhythm();
    void sinusBradycardia();
    void sinusTachycardia();
    void firstDegreeAVBlock();
    void isolatedMonoVE();
    void sinusPause();
    void junctionalRhythm();
    void acceleratedJunctionalRhythm();
    void isolatedSVE();
    void pairedSVE();
    void isolatedPolyVE();
    void idioventricularRhythm();
    void acceleratedIdioventricularRhythm();
    void supraventricularTachychardia();
    void type2AVBlock();
    void monomorphicVT();
    void atrialFibrillation();
    void type1AVBlock();
    void twoOneAVBlock();
    void polymorphicVT();
    void fastAtrialFibrillation();
    void sinoAtrialBlock();
    void dissociation();
    void ventricularFibrillation();

    ECGmemory & operator=(const ECGmemory &);

private:

    //
    // Wave variables
    //

    int heartRate;          // Heart rate
    bool noiseFilter;       // Noise filter (false means not filtering)

    // P Wave
    bool showPWave;
    double a_pwave;         // P wave amplitude
    double d_pwave;         // P wave duration
    double t_pwave;         // P wave interval
    bool positive_pwave;     // P vave positiveness

    // Q Wave
    bool showQWave;
    double a_qwave;         // Q wave amplitude
    double d_qwave;         // Q wave duration
    double t_qwave;         // Q wave interval

    // QRS Wave
    bool showQRSWave;
    double a_qrswave;       // QRS wave amplitude
    double d_qrswave;       // QRS wave duration
    // no interval information
    bool positive_qrswave;  // QRS wave positiveness

    // S Wave
    bool showSWave;
    double a_swave;         // S wave amplitude
    double d_swave;         // S wave duration
    double t_swave;         // S wave interval

    // T Wave
    bool showTWave;
    double a_twave;         // T wave amplitude
    double d_twave;         // T wave duration
    double t_twave;         // T wave interval
    bool positive_twave;    // T wave positiveness

    // U Wave
    bool showUWave;
    double a_uwave;         // U wave amplitude
    double d_uwave;         // U wave duration
    double t_uwave;         // U wave interval
};

#endif // ECGMEMORY_H
