/*****************************************************************************
 * Copyright 2016 Haye Hinrichsen, Christoph Wick
 *
 * This file is part of Entropy Piano Tuner.
 *
 * Entropy Piano Tuner is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Entropy Piano Tuner is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Entropy Piano Tuner. If not, see http://www.gnu.org/licenses/.
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QToolButton>
#include <memory>

#include <QtMidi/qmidiautoconnector.h>

#include "prerequisites.h"

#include "core/config.h"
#include "core/core.h"
#include "core/messages/messagelistener.h"
#include "core/adapters/modeselectoradapter.h"

#include "implementations/projectmanagerforqt.h"
#include "calculationprogressgroup.h"
#include "signalanalyzergroupbox.h"
#include "volumecontrolgroupbox.h"
#include "tuningindicatorgroupbox.h"
#include "versioncheck.h"
#include "progressdisplay.h"

class KeyboardGraphicsView;

namespace Ui {
class MainWindow;
}

///////////////////////////////////////////////////////////////////////////////
/// \brief The main window.
///
///////////////////////////////////////////////////////////////////////////////
class MainWindow : public QMainWindow,
        public MessageListener,
        public ModeSelectorAdapter,
        public FileChangesCallback
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Constructor.
    /// \param parent : Parent widget or nullptr.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    explicit MainWindow(QWidget *parent = nullptr);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// This will delete the ui.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~MainWindow();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Initialised the window using the given Core.
    /// \param core : Pointer to the Core.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void init(Core *core);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Starts the main window.
    ///
    /// This will initialize all label with default values.
    ///////////////////////////////////////////////////////////////////////////////
    void start();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Getter function for the core.
    /// \return mCore
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Core *getCore() {return mCore;}

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Getter function for the midi auto connector
    /// \return mMidiAutoConnector
    ///
    ///////////////////////////////////////////////////////////////////////////////
    QMidiAutoConnector *getMidiAutoConnector() {return mMidiAutoConnector;}

protected:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Reimplementation of the close event.
    /// \param event : The QCloseEvent
    ///
    /// This will store the current geometry.
    ///////////////////////////////////////////////////////////////////////////////
    void closeEvent ( QCloseEvent * event ) override;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Message handling.
    /// \param m : The Message
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void handleMessage(MessagePtr m) override;

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Called if changed in file are made to update the window title.
    /// \param b : Changes are made?
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void changesInFileUpdated(bool b) override final;

private:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Update the note name.
    /// \param key : The key index.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void updateNoteName(int key);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Update the frequency label
    /// \param key : The key index.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void updateFrequency(const Key *key);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Update the window title.
    ///
    /// The window title displays the current file name and a '*' if there are
    /// changes in the file.
    ///////////////////////////////////////////////////////////////////////////////
    void updateWindowTitle();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief This will update the positions of the labels in the volume bar.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void updateVolumeBar();
private:
    /// Set to true if a close event was accepted
    bool mClosing = false;

    /// The icon postfix set to @2x on devices with a higher pixeldensity of the display
    /// e.g. on iPad iwth retina displays
    const QString mIconPostfix;

    /// Pointer to the Core.
    Core *mCore = nullptr;

    /// Ui of the Mainwindow.
    Ui::MainWindow *ui = nullptr;

    /// Pointer to the CalculationProgressGroup.
    CalculationProgressGroup *mCalculationProgressGroup = nullptr;

    /// Pointer to the SignalAnalyzerGroupBox
    SignalAnalyzerGroupBox *mSignalAnalyzerGroup = nullptr;

    /// Pointer to the TuningIndicatorGroupBox
    TuningIndicatorGroupBox *mTuningIndicatorGroup = nullptr;

    /// Pointer to the VolumeControlGroupBox
    VolumeControlGroupBox *mVolumeControlGroup = nullptr;

    KeyboardGraphicsView *mKeyboardGraphicsView = nullptr;

    /// Progress display on the lower right side
    ProgressDisplay *mProgressDisplay = nullptr;

    QToolBar *mFileToolBar = nullptr;

    /// Tool buttons for all modes.
    QToolButton *mModeToolButtons[OperationMode::MODE_COUNT];

    /// Instance of the midi auto connector
    QMidiAutoConnector *mMidiAutoConnector = nullptr;

signals:
    void modeChanged(OperationMode mode);

public slots:
    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to open the sound control.
    ///
    /// This is platform dependent and works on linux (gnome, pavucontrol),
    /// Mac OsX, Windows.
    ///////////////////////////////////////////////////////////////////////////////
    void onOpenSoundControl();
    bool isSoundControlSupported();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to reset the noise level.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onResetNoiseLevel();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Toggle the mute button.
    /// \param checked : Button state
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onToggleMicroMute(bool checked);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Toggle the mute button.
    /// \param checked : Button state
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onToggleSpeakerMute(bool checked);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot called for creating a new file.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onFileNew();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to save the current file.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onFileSave();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to save the current file as a new file.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onFileSaveAs();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to open a new file.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onFileOpen();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to store the current file.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onFileShare();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to edit the current piano data sheet.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onEditPianoDataSheet();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to reset the recording.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onResetRecording();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to open the options.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onOptions();

    /// \brief Slot to open the mathematical plots dialog
    void onOpenPlots();

    ///////////////////////////////////////////////////////////////////////////////
    /// \biref Slot to open the tutorial.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onTutorial();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to open the manual.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onManual();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to open the about dialog.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onAbout();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to open the log viewer.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onViewLog();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to switch to idle mode.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onModeIdle(bool);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to switch to recording mode.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onModeRecord(bool);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to switch to calculation mode.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onModeCalculate(bool);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to switch to tuning mode.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onModeTune(bool);

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to select the next mode.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onSelectNextMode();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to select the previous mode.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onSelectPreviousMode();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to toggle full screen of the MainWindow.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onToggleFullscreen();

    ///////////////////////////////////////////////////////////////////////////////
    /// \brief Slot to toggle between the two tuning indicator modes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void onToggleTuningIndictator();

    /// \brief Slot to open the export dialog
    void onExport();


private slots:
    void onVersionUpdate(VersionInformation information);

    void onMidiInputDeviceCreated(const QMidiInput *input);
    void onMidiMessageReceived(const QMidiMessage &message);
};

#endif // MAINWINDOW_H
