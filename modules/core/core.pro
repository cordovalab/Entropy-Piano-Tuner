include(../../entropypianotuner_config.pri)
include(../../entropypianotuner_func.pri)

# create the core as a lib
TEMPLATE = lib

# on msvc compilers we need to instanciate std::string,
# but this is already done in Qt
# If we use Qt and core in the same subproject (app) the
# compiler does not know which one to use.
# Therefore also use the instance of Qt in the core
QT += core

# configuration
contains(EPT_CONFIG, static_core):CONFIG += staticlib
else:CONFIG += dll

CONFIG += c++11

# add this define to set dllimport/dllexport for msvc
DEFINES += EPT_BUILD_CORE

# set the destiantion dir
DESTDIR = $$EPT_CORE_OUT_DIR

# basic include dirs
INCLUDEPATH += $$EPT_ROOT_DIR $$EPT_BASE_DIR $$EPT_MODULES_DIR $$PWD $$EPT_MODULES_DIR/umidi

# Dependencies
$$depends_dirent()
$$depends_fftw3()
$$depends_getmemorysize()
$$depends_libuv()
$$depends_timesupport()

LIBS += -L$$EPT_ROOT_OUT_DIR/modules/umidi -lumidi

# debugging flags: all warnings and check arrays, etc
linux-g++*:!android {
    QMAKE_CXXFLAGS_DEBUG += -D_GLIBCXX_DEBUG -Wall -Wpedantic
}

#-------------------------------------------------
#                  Core files
#-------------------------------------------------


#------------- Message system --------------------

CORE_MESSAGE_SYSTEM_HEADERS = \
    messages/messagelistener.h \
    messages/messagehandler.h \
    messages/message.h \
    messages/messagerecorderenergychanged.h \
    messages/messagemodechanged.h \
    messages/messagekeyselectionchanged.h \
    messages/messagecaluclationprogress.h \
    messages/messageprojectfile.h \
    messages/messagemidievent.h \
    messages/messagenewfftcalculated.h \
    messages/messagepreliminarykey.h \
    messages/messagefinalkey.h \
    messages/messagechangetuningcurve.h \
    messages/messagetuningdeviation.h \
    messages/messagekeydatachanged.h \
    messages/messagestroboscope.h \

CORE_MESSAGE_SYSTEM_SOURCES = \
    messages/messagelistener.cpp \
    messages/messagehandler.cpp \
    messages/message.cpp \
    messages/messagerecorderenergychanged.cpp \
    messages/messagemodechanged.cpp \
    messages/messagekeyselectionchanged.cpp \
    messages/messagecaluclationprogress.cpp \
    messages/messageprojectfile.cpp \
    messages/messagemidievent.cpp \
    messages/messagenewfftcalculated.cpp \
    messages/messagepreliminarykey.cpp \
    messages/messagefinalkey.cpp \
    messages/messagechangetuningcurve.cpp \
    messages/messagetuningdeviation.cpp \
    messages/messagekeydatachanged.cpp \
    messages/messagestroboscope.cpp \

#------------- Drawers --------------------

CORE_DRAWER_HEADERS = \
    drawers/drawerbase.h \
    drawers/tuningcurvegraphdrawer.h \
    drawers/fourierspectrumgraphdrawer.h \
    drawers/tuningindicatordrawer.h \
    drawers/tuningcurvegraphdrawer.h \
    drawers/fourierspectrumgraphdrawer.h \
    drawers/graphicsitem.h \

CORE_DRAWER_SOURCES = \
    drawers/drawerbase.cpp \
    drawers/tuningindicatordrawer.cpp \
    drawers/tuningcurvegraphdrawer.cpp \
    drawers/fourierspectrumgraphdrawer.cpp \
    drawers/graphicsitem.cpp \

#------------- Adapters --------------------

CORE_ADAPTER_HEADERS = \
    adapters/recorderlevel.h \
    adapters/modeselectoradapter.h \
    adapters/projectmanageradapter.h \
    adapters/calculationadapter.h \
    adapters/graphicsviewadapter.h \
    adapters/filemanager.h \
    adapters/coreinitialisationadapter.h \
    adapters/xmlfactory.h \
    adapters/xmlreaderinterface.h \
    adapters/xmlwriterinterface.h \

CORE_ADAPTER_SOURCES = \
    adapters/calculationadapter.cpp \
    adapters/modeselectoradapter.cpp \
    adapters/projectmanageradapter.cpp \
    adapters/recorderlevel.cpp \
    adapters/filemanager.cpp \
    adapters/coreinitialisationadapter.cpp \
    adapters/graphicsviewadapter.cpp \
    adapters/xmlfactory.cpp \
    adapters/xmlreaderinterface.cpp \
    adapters/xmlwriterinterface.cpp \

#---------------- Audio -----------------

CORE_AUDIO_HEADERS = \
    audio/audiobase.h \
    audio/circularbuffer.h \
    audio/player/audioplayeradapter.h \
    audio/player/hammerknock.h \
    audio/player/pcmwriterinterface.h \
    audio/player/soundgenerator.h \
    audio/player/synthesizer.h \
    audio/player/waveformgenerator.h \
    audio/midi/midiadapter.h \
    audio/recorder/audiorecorderadapter.h \
    audio/recorder/stroboscope.h \
    audio/recorder/recordingmanager.h \


CORE_AUDIO_SOURCES = \
    audio/audiobase.cpp \
    audio/player/audioplayeradapter.cpp \
    audio/player/soundgenerator.cpp \
    audio/player/synthesizer.cpp \
    audio/player/waveformgenerator.cpp \
    audio/midi/midiadapter.cpp \
    audio/recorder/audiorecorderadapter.cpp \
    audio/recorder/stroboscope.cpp \
    audio/recorder/recordingmanager.cpp \

#------------- Mathematical ----------------

CORE_MATH_HEADERS = \
    math/fftadapter.h \
    math/fftimplementation.h \
    math/mathtools.h \

CORE_MATH_SOURCES = \
    math/fftimplementation.cpp \
    math/mathtools.cpp \

#--------------- System --------------------

CORE_SYSTEM_HEADERS = \
    system/log.h \
    system/simplethreadhandler.h \
    system/eptexception.h \
    system/timer.h \
    system/version.h \
    system/platformtoolscore.h \
    system/serverinfo.h \
    system/basecallback.h \
    system/sharedlibrary.h \

CORE_SYSTEM_SOURCES = \
    system/log.cpp \
    system/simplethreadhandler.cpp \
    system/eptexception.cpp \
    system/timer.cpp \
    system/platformtoolscore.cpp \
    system/serverinfo.cpp \
    system/basecallback.cpp \

# shared library is only required on shared algorithm builds
# General include causes linker error on iOS (... has no symbols)
contains(EPT_CONFIG, shared_algorithms) {
    CORE_SYSTEM_SOURCES += system/sharedlibrary.cpp
}

#--------------- Analyzers -----------------

CORE_ANALYZER_HEADERS = \
    analyzers/signalanalyzer.h \
    analyzers/keyrecognizer.h \
    analyzers/fftanalyzer.h \
    analyzers/fftanalyzererrorcodes.h \
    analyzers/overpull.h \

CORE_ANALYZER_SOURCES = \
    analyzers/signalanalyzer.cpp \
    analyzers/keyrecognizer.cpp \
    analyzers/fftanalyzer.cpp \
    analyzers/overpull.cpp \

#---------------- Piano --------------------

CORE_PIANO_HEADERS = \
    piano/piano.h \
    piano/key.h \
    piano/pianomanager.h \
    piano/keyboard.h \
    piano/pianodefines.h \

CORE_PIANO_SOURCES = \
    piano/piano.cpp  \
    piano/key.cpp \
    piano/pianomanager.cpp \
    piano/keyboard.cpp \
    piano/pianodefines.cpp \

#--------------- Calculation ---------------

CORE_CALCULATION_HEADERS = \
    calculation/calculationmanager.h \
    calculation/algorithmplugin.h \
    calculation/algorithm.h \
    calculation/algorithmfactory.h \
    calculation/algorithmfactorydescription.h \
    calculation/algorithminformation.h \
    calculation/algorithmparameterdescription.h \
    calculation/algorithmparameters.h \
    calculation/algorithminformationparser.h \


CORE_CALCULATION_SOURCES = \
    calculation/calculationmanager.cpp \
    calculation/algorithm.cpp \
    calculation/algorithmfactory.cpp \
    calculation/algorithmfactorydescription.cpp \
    calculation/algorithminformation.cpp \
    calculation/algorithmparameterdescription.cpp \
    calculation/algorithmparameters.cpp \
    calculation/algorithminformationparser.cpp \

#----------------- Core --------------------

CORE_HEADERS = \
    config.h \
    core.h \
    settings.h \
    prerequisites.h \

CORE_SOURCES = \
    core.cpp \
    settings.cpp \

#---------------- complete --------------------

HEADERS += \
    $$CORE_HEADERS \
    $$CORE_MESSAGE_SYSTEM_HEADERS \
    $$CORE_DRAWER_HEADERS \
    $$CORE_ADAPTER_HEADERS \
    $$CORE_AUDIO_HEADERS \
    $$CORE_MIDI_HEADERS \
    $$CORE_MATH_HEADERS \
    $$CORE_ANALYZER_HEADERS \
    $$CORE_PIANO_HEADERS \
    $$CORE_CALCULATION_HEADERS \
    $$CORE_SYSTEM_HEADERS \

SOURCES += \
    $$CORE_SOURCES \
    $$CORE_MESSAGE_SYSTEM_SOURCES \
    $$CORE_DRAWER_SOURCES \
    $$CORE_ADAPTER_SOURCES \
    $$CORE_AUDIO_SOURCES \
    $$CORE_MIDI_SOURCES \
    $$CORE_MATH_SOURCES \
    $$CORE_ANALYZER_SOURCES \
    $$CORE_PIANO_SOURCES \
    $$CORE_CALCULATION_SOURCES \
    $$CORE_SYSTEM_SOURCES \

