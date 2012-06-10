/*
 * Copyright (c) 2012 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "player.h"
#include "scrubbar.h"
#include "mainwindow.h"
#include "widgets/timespinbox.h"
#include "widgets/audiosignal.h"
#include <QtGui>

#define VOLUME_KNEE (88)
#define SEEK_INACTIVE (-1)

QT_BEGIN_NAMESPACE

namespace Ui {
class Player
{
public:
    QAction *actionPlay;
    QAction *actionPause;
    QAction *actionSkipNext;
    QAction *actionSkipPrevious;
    QAction *actionProgressive;
    QAction *actionOneField;
    QAction *actionLinearBlend;
    QAction *actionYadifTemporal;
    QAction *actionYadifSpatial;
    QAction *actionNearest;
    QAction *actionBilinear;
    QAction *actionBicubic;
    QAction *actionHyper;
    QAction *actionRewind;
    QAction *actionFastForward;

    void setupActions(QWidget* widget)
    {
        actionPlay = new QAction(widget);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay->setIcon(icon2);
        actionPause = new QAction(widget);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon3);
        actionSkipNext = new QAction(widget);
        actionSkipNext->setObjectName(QString::fromUtf8("actionSkipNext"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/media-skip-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSkipNext->setIcon(icon4);
        actionSkipPrevious = new QAction(widget);
        actionSkipPrevious->setObjectName(QString::fromUtf8("actionSkipPrevious"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/media-skip-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSkipPrevious->setIcon(icon5);
        actionProgressive = new QAction(widget);
        actionProgressive->setObjectName(QString::fromUtf8("actionProgressive"));
        actionProgressive->setCheckable(true);
        actionOneField = new QAction(widget);
        actionOneField->setObjectName(QString::fromUtf8("actionOneField"));
        actionOneField->setCheckable(true);
        actionLinearBlend = new QAction(widget);
        actionLinearBlend->setObjectName(QString::fromUtf8("actionLinearBlend"));
        actionLinearBlend->setCheckable(true);
        actionYadifTemporal = new QAction(widget);
        actionYadifTemporal->setObjectName(QString::fromUtf8("actionYadifTemporal"));
        actionYadifTemporal->setCheckable(true);
        actionYadifSpatial = new QAction(widget);
        actionYadifSpatial->setObjectName(QString::fromUtf8("actionYadifSpatial"));
        actionYadifSpatial->setCheckable(true);
        actionNearest = new QAction(widget);
        actionNearest->setObjectName(QString::fromUtf8("actionNearest"));
        actionNearest->setCheckable(true);
        actionBilinear = new QAction(widget);
        actionBilinear->setObjectName(QString::fromUtf8("actionBilinear"));
        actionBilinear->setCheckable(true);
        actionBicubic = new QAction(widget);
        actionBicubic->setObjectName(QString::fromUtf8("actionBicubic"));
        actionBicubic->setCheckable(true);
        actionHyper = new QAction(widget);
        actionHyper->setObjectName(QString::fromUtf8("actionHyper"));
        actionHyper->setCheckable(true);
        actionRewind = new QAction(widget);
        actionRewind->setObjectName(QString::fromUtf8("actionRewind"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/media-seek-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRewind->setIcon(icon6);
        actionFastForward = new QAction(widget);
        actionFastForward->setObjectName(QString::fromUtf8("actionFastForward"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/media-seek-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFastForward->setIcon(icon7);

        retranslateUi(widget);
        QMetaObject::connectSlotsByName(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        const char* name = widget->objectName().toUtf8().constData();
        actionPlay->setText(QApplication::translate(name, "Play", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay->setToolTip(QApplication::translate(name, "Start playback (K)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPlay->setShortcut(QApplication::translate(name, "Space", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate(name, "Pause", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPause->setToolTip(QApplication::translate(name, "Pause playback (K)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPause->setShortcut(QApplication::translate(name, "Backspace", 0, QApplication::UnicodeUTF8));
        actionSkipNext->setText(QApplication::translate(name, "Skip Next", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSkipNext->setToolTip(QApplication::translate(name, "Skip to the next point (Alt+Right)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSkipNext->setShortcut(QApplication::translate(name, "Alt+Right", 0, QApplication::UnicodeUTF8));
        actionSkipPrevious->setText(QApplication::translate(name, "Skip Previous", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSkipPrevious->setToolTip(QApplication::translate(name, "Skip to the previous point (Alt+Left)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSkipPrevious->setShortcut(QApplication::translate(name, "Alt+Left", 0, QApplication::UnicodeUTF8));
        actionProgressive->setText(QApplication::translate(name, "Progressive", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionProgressive->setToolTip(QApplication::translate(name, "Force the video preview to deinterlace if needed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOneField->setText(QApplication::translate(name, "One Field (fast)", 0, QApplication::UnicodeUTF8));
        actionLinearBlend->setText(QApplication::translate(name, "Linear Blend (fast)", 0, QApplication::UnicodeUTF8));
        actionYadifTemporal->setText(QApplication::translate(name, "YADIF - temporal only (good)", 0, QApplication::UnicodeUTF8));
        actionYadifSpatial->setText(QApplication::translate(name, "YADIF - temporal + spatial (best)", 0, QApplication::UnicodeUTF8));
        actionNearest->setText(QApplication::translate(name, "Nearest Neighbor (fast)", 0, QApplication::UnicodeUTF8));
        actionBilinear->setText(QApplication::translate(name, "Bilinear (good)", 0, QApplication::UnicodeUTF8));
        actionBicubic->setText(QApplication::translate(name, "Bicubic (better)", 0, QApplication::UnicodeUTF8));
        actionHyper->setText(QApplication::translate(name, "Hyper/Lanczoz (best)", 0, QApplication::UnicodeUTF8));
        actionRewind->setText(QApplication::translate(name, "Rewind", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRewind->setToolTip(QApplication::translate(name, "Play quickly backwards (J)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRewind->setShortcut(QApplication::translate(name, "J", 0, QApplication::UnicodeUTF8));
        actionFastForward->setText(QApplication::translate(name, "Fast Forward", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFastForward->setToolTip(QApplication::translate(name, "Play quickly forwards (L)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionFastForward->setShortcut(QApplication::translate(name, "L", 0, QApplication::UnicodeUTF8));
    }
};
} // namespace Ui

QT_END_NAMESPACE

Player::Player(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Player)
    , m_position(0)
{
    setObjectName("Player");
    ui->setupActions(this);

    // These use the icon theme on Linux, with fallbacks to the icons specified in QtDesigner for other platforms.
    ui->actionPlay->setIcon(QIcon::fromTheme("media-playback-start", ui->actionPlay->icon()));
    ui->actionPause->setIcon(QIcon::fromTheme("media-playback-pause", ui->actionPause->icon()));
    ui->actionSkipNext->setIcon(QIcon::fromTheme("media-skip-forward", ui->actionSkipNext->icon()));
    ui->actionSkipPrevious->setIcon(QIcon::fromTheme("media-skip-backward", ui->actionSkipPrevious->icon()));
    ui->actionRewind->setIcon(QIcon::fromTheme("media-seek-backward", ui->actionRewind->icon()));
    ui->actionFastForward->setIcon(QIcon::fromTheme("media-seek-forward", ui->actionFastForward->icon()));
    ui->actionPlay->setEnabled(false);
    ui->actionSkipPrevious->setEnabled(false);
    ui->actionSkipNext->setEnabled(false);
    ui->actionRewind->setEnabled(false);
    ui->actionFastForward->setEnabled(false);
    m_playIcon = ui->actionPlay->icon();
    m_pauseIcon = ui->actionPause->icon();

    readSettings();

    // Create a layout.
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setObjectName("playerLayout");
    layout->setMargin(0);
    layout->setSpacing(0);

    // Create MLT video widget.
    Mlt::Controller::singleton(this);
    MLT.videoWidget()->setProperty("progressive", ui->actionProgressive->isChecked());
    if (ui->actionOneField->isChecked())
        MLT.videoWidget()->setProperty("deinterlace_method", "onefield");
    else if (ui->actionLinearBlend->isChecked())
        MLT.videoWidget()->setProperty("deinterlace_method", "linearblend");
    else if (ui->actionYadifTemporal->isChecked())
        MLT.videoWidget()->setProperty("deinterlace_method", "yadif-nospatial");
    else
        MLT.videoWidget()->setProperty("deinterlace_method", "yadif");
    if (ui->actionNearest->isChecked())
        MLT.videoWidget()->setProperty("rescale", "nearest");
    else if (ui->actionBilinear->isChecked())
        MLT.videoWidget()->setProperty("rescale", "bilinear");
    else if (ui->actionBicubic->isChecked())
        MLT.videoWidget()->setProperty("rescale", "bicubic");
    else
        MLT.videoWidget()->setProperty("rescale", "hyper");
    MLT.videoWidget()->setContentsMargins(0, 0, 0, 0);
    MLT.videoWidget()->setContextMenuPolicy(Qt::CustomContextMenu);
    MLT.videoWidget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Add the volume and signal level meter
    QWidget* tmp = new QWidget(this);
    QHBoxLayout *hlayout = new QHBoxLayout(tmp);
    hlayout->setSpacing(0);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(MLT.videoWidget(), 10);
    hlayout->addSpacing(4);
    m_volumeSlider = new QSlider(Qt::Vertical);
    m_audioSignal = new AudioSignal(this);
    hlayout->addWidget(m_volumeSlider);
    hlayout->addWidget(m_audioSignal);
    m_volumeSlider->setRange(0, 99);
    m_volumeSlider->setValue(m_settings.value("player/volume", VOLUME_KNEE).toInt());
    connect(m_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeChanged(int)));
    connect(this, SIGNAL(audioSamplesSignal(const QVector<int16_t>&, const int&, const int&, const int&)),
                         m_audioSignal, SLOT(slotReceiveAudio(const QVector<int16_t>&, const int&, const int&, const int&)));

    layout->addWidget(tmp, 10);
    layout->addStretch();

    // Add the scrub bar.
    m_scrubber = new ScrubBar(this);
    m_scrubber->setObjectName("scrubBar");
    m_scrubber->hide();
    layout->addSpacing(4);
    layout->addWidget(m_scrubber);
    layout->addSpacing(4);

    // Add toolbar for transport controls.
    QToolBar* toolbar = new QToolBar(tr("Transport Controls"), this);
    int s = style()->pixelMetric(QStyle::PM_SmallIconSize);
    toolbar->setIconSize(QSize(s, s));
    toolbar->setContentsMargins(0, 0, 5, 0);
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    m_positionSpinner = new TimeSpinBox(this);
    m_positionSpinner->setToolTip(tr("Current position"));
    m_positionSpinner->setEnabled(false);
    m_positionSpinner->setKeyboardTracking(false);
    m_durationLabel = new QLabel(this);
    m_durationLabel->setToolTip(tr("Duration"));
    m_durationLabel->setText("0.000");
    m_durationLabel->setAlignment(Qt::AlignRight);
    m_durationLabel->setContentsMargins(0, 5, 0, 0);
    m_durationLabel->setFixedWidth(m_positionSpinner->width());
    toolbar->addWidget(m_positionSpinner);
    toolbar->addWidget(spacer);
    toolbar->addAction(ui->actionSkipPrevious);
    toolbar->addAction(ui->actionRewind);
    toolbar->addAction(ui->actionPlay);
    toolbar->addAction(ui->actionFastForward);
    toolbar->addAction(ui->actionSkipNext);
    spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    toolbar->addWidget(spacer);
    toolbar->addWidget(m_durationLabel);
    layout->addWidget(toolbar);

    connect(MLT.videoWidget(), SIGNAL(frameReceived(Mlt::QFrame)), this, SLOT(onShowFrame(Mlt::QFrame)));
    connect(MLT.videoWidget(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onVideoWidgetContextMenu(QPoint)));
    connect(ui->actionPlay, SIGNAL(triggered()), this, SLOT(togglePlayPaused()));
    connect(ui->actionPause, SIGNAL(triggered()), this, SLOT(pause()));
    connect(m_scrubber, SIGNAL(seeked(int)), this, SLOT(seek(int)));
    connect(m_scrubber, SIGNAL(inChanged(int)), this, SLOT(onInChanged(int)));
    connect(m_scrubber, SIGNAL(outChanged(int)), this, SLOT(onOutChanged(int)));
    connect(m_positionSpinner, SIGNAL(valueChanged(int)), this, SLOT(seek(int)));
    connect(m_positionSpinner, SIGNAL(editingFinished()), this, SLOT(setFocus()));
    connect(this, SIGNAL(seeked()), this, SLOT(pause()));
    connect(this, SIGNAL(endOfStream()), this, SLOT(pause()));
    setFocusPolicy(Qt::StrongFocus);
}

void Player::readSettings()
{
    ui->actionProgressive->setChecked(m_settings.value("player/progressive", true).toBool());
    QString deinterlacer = m_settings.value("player/deinterlacer", "onefield").toString();
    QString interpolation = m_settings.value("player/interpolation", "nearest").toString();

    if (deinterlacer == "onefield")
        ui->actionOneField->setChecked(true);
    else if (deinterlacer == "linearblend")
        ui->actionLinearBlend->setChecked(true);
    else if (deinterlacer == "yadif-nospatial")
        ui->actionYadifTemporal->setChecked(true);
    else
        ui->actionYadifSpatial->setChecked(true);

    if (interpolation == "nearest")
        ui->actionNearest->setChecked(true);
    else if (interpolation == "bilinear")
        ui->actionBilinear->setChecked(true);
    else if (interpolation == "bicubic")
        ui->actionBicubic->setChecked(true);
    else
        ui->actionHyper->setChecked(true);
}

void Player::setIn(unsigned pos)
{
//    onInChanged(pos);
    m_scrubber->setInPoint(pos);
}

void Player::setOut(unsigned pos)
{
//    onOutChanged(pos);
    m_scrubber->setOutPoint(pos);
}

void Player::resizeEvent(QResizeEvent*)
{
    MLT.onWindowResize();
}

void Player::play(double speed)
{
    MLT.play(speed);
    // TODO: use stop icon for live sources
    ui->actionPlay->setIcon(m_pauseIcon);
    ui->actionPlay->setText(tr("Pause"));
    ui->actionPlay->setToolTip(tr("Pause playback"));
//    forceResize();
}

void Player::pause()
{
    MLT.pause();
    ui->actionPlay->setIcon(m_playIcon);
    ui->actionPlay->setText(tr("Play"));
    ui->actionPlay->setToolTip(tr("Start playback"));
//    forceResize();
}

void Player::stop()
{
    MLT.stop();
    ui->actionPlay->setIcon(m_playIcon);
    ui->actionPlay->setText(tr("Play"));
    ui->actionPlay->setToolTip(tr("Start playback"));
}

void Player::togglePlayPaused()
{
    if (ui->actionPlay->icon().cacheKey() == m_playIcon.cacheKey())
        play();
    else if (MLT.producer() && (
             MLT.producer()->get_int("seekable") ||
                 // generators can pause and show property changes
                 QString(MLT.producer()->get("mlt_service")) == "color" ||
                 QString(MLT.producer()->get("mlt_service")).startsWith("frei0r.")))
        pause();
    else
        stop();
}

void Player::seek(int position)
{
    if (MLT.producer()->get_int("seekable")) {
        emit seeked();
        if (position >= 0) {
            if (m_seekPosition == SEEK_INACTIVE)
                MLT.seek(qMin(position, MLT.producer()->get_length() - 1));
            m_seekPosition = qMin(position, MLT.producer()->get_length() - 1);
        }
    }
}

void Player::onProducerOpened()
{
    int len = MLT.producer()->get_length();
    bool seekable = MLT.producer()->get_int("seekable");

    MLT.producer()->set("ignore_points", 1);
    m_scrubber->setFramerate(MLT.profile().fps());
    m_scrubber->setScale(len);
    if (seekable) {
        m_durationLabel->setText(MLT.producer()->get_length_time());
        m_scrubber->setInPoint(MLT.producer()->get_in());
        m_scrubber->setOutPoint(MLT.producer()->get_out());
        m_scrubber->show();
    }
    else {
        m_durationLabel->setText(tr("Live"));
        m_scrubber->hide();
    }
    m_positionSpinner->setEnabled(seekable);
    onVolumeChanged(m_volumeSlider->value());

    ui->actionPlay->setEnabled(true);
    ui->actionSkipPrevious->setEnabled(seekable);
    ui->actionSkipNext->setEnabled(seekable);
    ui->actionRewind->setEnabled(seekable);
    ui->actionFastForward->setEnabled(seekable);

    play();
}

void Player::onShowFrame(Mlt::QFrame frame)
{
    if (MLT.producer() && MLT.producer()->is_valid()) {
        int position = frame.frame()->get_position();
        if (position < MLT.producer()->get_length()) {
            m_position = position;
            m_positionSpinner->blockSignals(true);
            m_positionSpinner->setValue(position);
            m_positionSpinner->blockSignals(false);
            m_scrubber->onSeek(position);
        }
        if (position >= MLT.producer()->get_length() - 1)
            emit endOfStream();
        showAudio(frame.frame());
        if (m_seekPosition != SEEK_INACTIVE)
            MLT.seek(m_seekPosition);
        m_seekPosition = SEEK_INACTIVE;
    }
}

void Player::onInChanged(int in)
{
    if (MLT.producer())
        MLT.producer()->set("in", in);
}

void Player::onOutChanged(int out)
{
    if (MLT.producer())
        MLT.producer()->set("out", out);
}

void Player::on_actionSkipNext_triggered()
{
    int pos = position();
    if (pos < MLT.producer()->get_in())
        MLT.seek(MLT.producer()->get_in());
    else if (pos >= MLT.producer()->get_out())
        MLT.seek(MLT.producer()->get_length() - 1);
    else
        MLT.seek(MLT.producer()->get_out());
    emit showStatusMessage(ui->actionSkipNext->toolTip());
}

void Player::on_actionSkipPrevious_triggered()
{
    int pos = position();
    if (pos > MLT.producer()->get_out())
        MLT.seek(MLT.producer()->get_out());
    else if (pos <= MLT.producer()->get_in())
        MLT.seek(0);
    else
        MLT.seek(MLT.producer()->get_in());
    emit showStatusMessage(ui->actionSkipPrevious->toolTip());
}

void Player::on_actionRewind_triggered()
{
    if (MLT.producer()->get_int("seekable")) {
        if (MLT.producer()->get_speed() >= 0)
            play(-1.0);
        else
            MLT.producer()->set_speed(MLT.producer()->get_speed() * 2);
    }
}

void Player::on_actionFastForward_triggered()
{
    if (MLT.producer()->get_int("seekable")) {
        if (MLT.producer()->get_speed() <= 0)
            play();
        else
            MLT.producer()->set_speed(MLT.producer()->get_speed() * 2);
    }
}

void Player::onVideoWidgetContextMenu(const QPoint& pos)
{
    QMenu menu(this);
    menu.addAction(ui->actionProgressive);
    QMenu* sub = menu.addMenu(tr("Deinterlacer"));
    QActionGroup deinterlacerGroup(sub);
    deinterlacerGroup.addAction(ui->actionOneField);
    deinterlacerGroup.addAction(ui->actionLinearBlend);
    deinterlacerGroup.addAction(ui->actionYadifTemporal);
    deinterlacerGroup.addAction(ui->actionYadifSpatial);
    sub->addActions(deinterlacerGroup.actions());
    sub = menu.addMenu(tr("Interpolation"));
    QActionGroup scalerGroup(sub);
    scalerGroup.addAction(ui->actionNearest);
    scalerGroup.addAction(ui->actionBilinear);
    scalerGroup.addAction(ui->actionBicubic);
    scalerGroup.addAction(ui->actionHyper);
    sub->addActions(scalerGroup.actions());
    menu.exec(this->mapToGlobal(pos));
}

void Player::on_actionProgressive_triggered(bool checked)
{
    MLT.videoWidget()->setProperty("progressive", checked);
    if (MLT.consumer() && !MLT.profile().progressive()) {
        MLT.consumer()->stop();
        MLT.consumer()->set("progressive", checked);
        MLT.consumer()->start();
    }
    m_settings.setValue("player/progressive", checked);
}

void Player::changeDeinterlacer(bool checked, const char* method)
{
    if (checked) {
        MLT.videoWidget()->setProperty("deinterlace_method", method);
        if (MLT.consumer()) {
            MLT.consumer()->stop();
            MLT.consumer()->set("deinterlace_method", method);
            MLT.consumer()->start();
        }
    }
    m_settings.setValue("player/deinterlacer", method);
}

void Player::on_actionOneField_triggered(bool checked)
{
    changeDeinterlacer(checked, "onefield");
}

void Player::on_actionLinearBlend_triggered(bool checked)
{
    changeDeinterlacer(checked, "linearblend");
}

void Player::on_actionYadifTemporal_triggered(bool checked)
{
    changeDeinterlacer(checked, "yadif-nospatial");
}

void Player::on_actionYadifSpatial_triggered(bool checked)
{
    changeDeinterlacer(checked, "yadif");
}

void Player::changeInterpolation(bool checked, const char* method)
{
    if (checked) {
        MLT.videoWidget()->setProperty("rescale", method);
        if (MLT.consumer()) {
            MLT.consumer()->stop();
            MLT.consumer()->set("rescale", method);
            MLT.consumer()->start();
        }
    }
    m_settings.setValue("player/interpolation", method);
}

void Player::on_actionNearest_triggered(bool checked)
{
    changeInterpolation(checked, "nearest");
}

void Player::on_actionBilinear_triggered(bool checked)
{
    changeInterpolation(checked, "bilinear");
}

void Player::on_actionBicubic_triggered(bool checked)
{
    changeInterpolation(checked, "bicubic");
}

void Player::on_actionHyper_triggered(bool checked)
{
    changeInterpolation(checked, "hyper");
}

void Player::showAudio(Mlt::Frame* frame)
{
    if (frame->get_int("test_audio"))
        return;
    mlt_audio_format format = mlt_audio_s16;
    int frequency = 0;
    int channels = 0;
    int samples = 0;
    int16_t* data = (int16_t*) frame->get_audio(format, frequency, channels, samples);

    if (samples && data) {
        QVector<int16_t> pcm(samples * channels);
        memcpy(pcm.data(), data, samples * channels * sizeof(int16_t));
        emit audioSamplesSignal(pcm, frequency, channels, samples);
    }
}

//----------------------------------------------------------------------------
// IEC standard dB scaling -- as borrowed from meterbridge (c) Steve Harris

static inline float IEC_dB ( float fScale )
{
	float dB = 0.0f;

	if (fScale < 0.025f)	    // IEC_Scale(-60.0f)
		dB = (fScale / 0.0025f) - 70.0f;
	else if (fScale < 0.075f)	// IEC_Scale(-50.0f)
		dB = (fScale - 0.025f) / 0.005f - 60.0f;
	else if (fScale < 0.15f)	// IEC_Scale(-40.0f)
		dB = (fScale - 0.075f) / 0.0075f - 50.0f;
	else if (fScale < 0.3f)		// IEC_Scale(-30.0f)
		dB = (fScale - 0.15f) / 0.015f - 40.0f;
	else if (fScale < 0.5f)		// IEC_Scale(-20.0f)
		dB = (fScale - 0.3f) / 0.02f - 30.0f;
	else /* if (fScale < 1.0f)	// IED_Scale(0.0f)) */
		dB = (fScale - 0.5f) / 0.025f - 20.0f;

	return (dB > -0.001f && dB < 0.001f ? 0.0f : dB);
}

void Player::onVolumeChanged(int volume)
{
    const double gain = double(volume) / VOLUME_KNEE;
    MLT.setVolume(gain);
    emit showStatusMessage(QString("%1 dB").arg(IEC_dB(gain)));
    m_settings.setValue("player/volume", volume);
}