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

#ifndef ASSESSMENTFRAME_H
#define ASSESSMENTFRAME_H

#include <QFrame>
#include <QTimer>
#include <QAbstractButton>

#define TOTALQUESTIONS      10      // Number of questions in assessment
#define TOTALTIME           60      // Max. time for answering all questions

namespace Ui {
    class AssessmentFrame;
}

class AssessmentFrame : public QFrame {
    Q_OBJECT
    Q_DISABLE_COPY(AssessmentFrame)

public:
    explicit AssessmentFrame(QWidget *parent = 0);
    virtual ~AssessmentFrame();

    void resetScore();
    void endAssessment();
    inline bool isAssessmentRunning() { return started; }
    inline void setAssessmentAnswers(QList<QAbstractButton *> answersButtonList) {
        answerList = answersButtonList; }

public slots:
    void startAssessment();
    void nextQuestion();

signals:
    void questionChanged(QString);
    void assessmentRunning(bool);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::AssessmentFrame *m_ui;
    void chooseQuestions();
    QList<QAbstractButton *> answerList;

    QTimer *timer;
    bool started;                   // Is an assessment running ?
    int answeredQuestions;          // Number of answers given so far
    int correctAnswers;             // Number of correct answers given
    int correctAnswer;              // The index of the correct button in a given moment of the assessment
                                    // this index refers to answerList QList
    int question1, question2, question3; // Index in answerList for each question
    int timeRemaining;              // Time remaining for assessment to finish

private slots:
    void updateTimer();

};

#endif // ASSESSMENTFRAME_H
