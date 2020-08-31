/****************************************************************************
** Form interface generated from reading ui file 'editpreference.ui'
**
** Created by User Interface Compiler
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef EDITPREFERENCE_H
#define EDITPREFERENCE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLabel;
class QComboBox;
class QRadioButton;

class EditPreference : public QWidget
{
    Q_OBJECT

public:
    EditPreference( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~EditPreference();

    QPushButton* pushButtonPhasing;
    QPushButton* pushButtonPulsarConsole;
    QLabel* textLabelAcqBw;
    QLabel* textLabelChan;
    QLabel* textLabelStokes;
    QLabel* textLabelIfBw;
    QLabel* textLabelFinBw;
    QLabel* textLabelBeams;
    QPushButton* pushButtonPowerEq;
    QComboBox* comboBoxChan;
    QComboBox* comboBoxIfBw;
    QComboBox* comboBoxFinBw;
    QPushButton* pushButtonDataMon;
    QComboBox* comboBoxAcqBw;
    QComboBox* comboBoxStokes;
    QComboBox* comboBoxBeams;
    QComboBox* comboBoxLta;
    QPushButton* pushButtonOnline;
    QRadioButton* radioButtonGain;
    QLabel* textLabelMode;
    QLabel* textLabelLta;
    QPushButton* pushButtonQuit;
    QPushButton* pushButtonDefault;
    QPushButton* pushButtonLoad;
    QPushButton* pushButtonSave;
    QComboBox* comboBoxMode;
    QRadioButton* radioButtonFstop;
    QPushButton* pushButtonDasConsole;

public slots:
    virtual void GpuMode( const QString & );
    virtual void GpuLta( const QString & );
    virtual void GpuAcqBw( const QString & );
    virtual void GpuChan( const QString & );
    virtual void GpuStokes( const QString & );
    virtual void GpuControl();
    virtual void GpuIfBw( const QString & );
    virtual void GpuFinBw( const QString & );
    virtual void GpuBeams( const QString & );
    virtual void GpuGain_clicked();
    virtual void GpuFstop_clicked();
    virtual void dasconsole();
    virtual void DasConsole_stateChanged();
    virtual void save();
    virtual void write_shm();
    virtual void load();
    virtual void defaultpara();
    virtual void radioButtonFstop_stateChanged( int t );
    virtual void radioButtonGain_stateChanged( int t );
    virtual void close();
    virtual void GpuMode_textChanged( const QString & );
    virtual void DasConsole_started();
    virtual void DasConsole_exited();

protected:

protected slots:
    virtual void languageChange();

private:
    void init();

};

#endif // EDITPREFERENCE_H
