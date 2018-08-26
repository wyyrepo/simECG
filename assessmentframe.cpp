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

#include <QtGlobal>
#include <QMessageBox>

#include "assessmentframe.h"
#include "ui_assessmentframe.h"

AssessmentFrame::AssessmentFrame(QWidget *parent) : QFrame(parent),
    m_ui(new Ui::AssessmentFrame)
{
    m_ui->setupUi(this);

    // Prepare the timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    connect(m_ui->pushButtonBegin, SIGNAL(clicked()), this, SLOT(startAssessment()));
    connect(m_ui->pushButtonNext, SIGNAL(clicked()), this, SLOT(nextQuestion()));

    // Resets all variables and widgets
    resetScore();
}

AssessmentFrame::~AssessmentFrame()
{
    delete m_ui;
}

void AssessmentFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AssessmentFrame::startAssessment()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle(tr("Start assessment", "Dialog title"));
    msgBox.setText(QString(tr("You are about to start an ECG assessment. You will be asked %1 questions during %2 seconds. "))
                   .arg(TOTALQUESTIONS).arg(TOTALTIME)
                   + QString(tr("Each question will have an ECG signal displayed, and three possible answers. "))
                   + QString(tr("You need to choose the correct one. After answering all the questions, you will get a final score. "))
                   + QString(tr("Good luck!")));
    msgBox.setInformativeText(tr("Ready to start?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Cancel) return;

    // Ask the first question
    chooseQuestions();
    m_ui->radioAnswer1->show();
    m_ui->radioAnswer2->show();
    m_ui->radioAnswer3->show();
    started = true;
    m_ui->pushButtonBegin->setDisabled(true);
    emit assessmentRunning(true);


    // Start counting time
    timer->start(1000);
}


void AssessmentFrame::updateTimer()
{
    // Decrease main counter (in seconds)
    timeRemaining--;
    // Update LCD display
    m_ui->lcdTimeCounter->display(timeRemaining);
    // Start another timing for the next second, or stops assessment
    if (! timeRemaining) {
        timer->stop();
        endAssessment();
    }
}

void AssessmentFrame::endAssessment()
{
    int score = correctAnswers * timeRemaining;
    QMessageBox msgBox;

    msgBox.setWindowTitle(tr("Assessment finished"));
    if (timeRemaining) {
        if (! score) {
            msgBox.setText(QString(tr("Sorry. You took %1 seconds to complete the assessment, but your score was a lousy 0 points."))
                           .arg(TOTALTIME - timeRemaining));
        } else {
            msgBox.setText(QString(tr("Congratulations! Your score was %1 points.\nYou took %2 seconds to complete the assessment."))
                       .arg(score).arg(TOTALTIME - timeRemaining));
        }
    } else {
        msgBox.setText(QString(tr("Sorry your assessment time has expired.\nYour score was %1 points.")).arg(score));
    }
    msgBox.exec();

    resetScore();
}

void AssessmentFrame::nextQuestion()
{
    int userAnswer = -1;

    // If assessment is not started, next button does nothing
    if (! started) return;

    // Do not proceed if there is not a correct answer
    Q_ASSERT(correctAnswer >= 0);

    // Check what was the user answer
    if (m_ui->radioAnswer1->isChecked()) {
        userAnswer = question1;
    } else if (m_ui->radioAnswer2->isChecked()) {
        userAnswer = question2;
    } else if (m_ui->radioAnswer3->isChecked()) {
        userAnswer = question3;
    } else {
        qDebug("User has not checked any buttons.");
    }

    answeredQuestions++;

    // Update score if the answer is correct
    if (userAnswer == correctAnswer) {
        qDebug("(%d/%d) The answer was correct!", answeredQuestions, TOTALQUESTIONS);
        correctAnswers++;
    } else {
        qDebug("(%d/%d) The answer was wrong. Correct was %s.",
               answeredQuestions, TOTALQUESTIONS,
               answerList.at(correctAnswer)->text().toLatin1().constData());
    }

    // Update progress bar
    m_ui->progressBar->setValue(answeredQuestions * 100 / TOTALQUESTIONS);

    // Uncheck all answer radio buttons
    m_ui->radioAnswer1->setAutoExclusive(false);
    m_ui->radioAnswer2->setAutoExclusive(false);
    m_ui->radioAnswer3->setAutoExclusive(false);
    m_ui->radioAnswer1->setChecked(Qt::Unchecked);
    m_ui->radioAnswer2->setChecked(Qt::Unchecked);
    m_ui->radioAnswer3->setChecked(Qt::Unchecked);
    m_ui->radioAnswer1->setAutoExclusive(true);
    m_ui->radioAnswer2->setAutoExclusive(true);
    m_ui->radioAnswer3->setAutoExclusive(true);

    // Check if assessment has finished
    if (answeredQuestions == TOTALQUESTIONS) {
        timer->stop();
        endAssessment();
    } else {
        chooseQuestions();
    }
}

void AssessmentFrame::resetScore()
{
    answeredQuestions = 0;
    timeRemaining = TOTALTIME;
    correctAnswers = 0;
    // Choose invalid question indexes from the answerList
    question1 = -1;
    question2 = -1;
    question3 = -1;
    correctAnswer = -2;
    started = false;

    emit assessmentRunning(false);
    timer->stop();
    m_ui->pushButtonBegin->setDisabled(false);
    m_ui->radioAnswer1->setAutoExclusive(false);
    m_ui->radioAnswer2->setAutoExclusive(false);
    m_ui->radioAnswer3->setAutoExclusive(false);
    m_ui->radioAnswer1->setChecked(Qt::Unchecked);
    m_ui->radioAnswer2->setChecked(Qt::Unchecked);
    m_ui->radioAnswer3->setChecked(Qt::Unchecked);
    m_ui->radioAnswer1->setAutoExclusive(true);
    m_ui->radioAnswer2->setAutoExclusive(true);
    m_ui->radioAnswer3->setAutoExclusive(true);
    m_ui->radioAnswer1->hide();
    m_ui->radioAnswer2->hide();
    m_ui->radioAnswer3->hide();
    m_ui->progressBar->setValue(0);
    m_ui->lcdTimeCounter->display(TOTALTIME);
}

///////////////////////////////////////////////////////////////////////////////
//
// Choose 3 questions from the set of available ECG preset signals
//
void AssessmentFrame::chooseQuestions()
{
    Q_ASSERT(!answerList.empty());

    //QTime midnight(0, 0, 0);
    //qsrand(midnight.secsTo(QTime::currentTime()));

    do {
        question1 = qrand() % answerList.size();
    } while (!answerList.at(question1)->isEnabled());
    m_ui->radioAnswer1->setText(answerList.at(question1)->text());

    do {
        question2 = qrand() % answerList.size();
    } while (question2 == question1 || !answerList.at(question2)->isEnabled());
    m_ui->radioAnswer2->setText(answerList.at(question2)->text());

    do {
        question3 = qrand() % answerList.size();
    } while (question3 == question2 || question3 == question1 || !answerList.at(question3)->isEnabled());
    m_ui->radioAnswer3->setText(answerList.at(question3)->text());

    // Choose the question that will be correct answer
    int random = qrand() % 3;
    // Place the index of the selected correct answer (from answerList) in the correctAnswer variable
    switch (random) {
        case 0:
            correctAnswer = question1;
        case 1:
            correctAnswer = question2;
        case 2:
            correctAnswer = question3;
            break;
        default:
            // This should never happen
            Q_ASSERT(false);
    }
    // display the correct ECG signal
    emit questionChanged(answerList.at(correctAnswer)->text());

    // Use only for testing purposes
    /*
    // How many presets do we have ??
    qDebug("Number of ECG presets: %d", answerList.size());

    // How many enabled presets do we have ??
    int enabledPresets = 0;
    for (int i = 0; i < answerList.size(); i++) {
        if (answerList.at(i)->isEnabled()) enabledPresets++;
    }
    qDebug("Number of enabled ECG presets: %d", enabledPresets);

    // Show all button names
    QString presetName;
    Q_ASSERT(answerList.size() > 0);
    for (int i = 0; i < answerList.size(); i++) {
        presetName = answerList.at(i)->text();
        qDebug("Button text is %s", presetName.toAscii().constData());
    }
    */
}
