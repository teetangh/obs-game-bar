#include <obs-frontend-api.h>
#include <obs-module.h>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("my-plugin", "en-US")

enum Mode
{
    MODE_RECORDING,
    MODE_STREAMING
};

Mode currentMode = MODE_RECORDING;

void on_mode_changed(int index)
{
    currentMode = (Mode)index;
}

void on_start_button_clicked()
{
    if (currentMode == MODE_RECORDING)
    {
        // Start recording
        obs_frontend_recording_start();
    }
    else if (currentMode == MODE_STREAMING)
    {
        // Start streaming
        obs_frontend_streaming_start();
    }
}

void on_pause_button_clicked()
{
    if (currentMode == MODE_RECORDING)
    {
        // Pause or unpause recording
        obs_frontend_recording_pause(!obs_frontend_recording_paused());
    }
    else if (currentMode == MODE_STREAMING)
    {
        // Pause or unpause streaming is not currently supported by the OBS API
    }
}

void on_stop_button_clicked()
{
    if (currentMode == MODE_RECORDING)
    {
        // Stop recording
        obs_frontend_recording_stop();
    }
    else if (currentMode == MODE_STREAMING)
    {
        // Stop streaming
        obs_frontend_streaming_stop();
    }
}

bool obs_module_load(void)
{
    // Create a new dockable widget
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    widget->setLayout(layout);

    // Create the mode selection combo box
    QComboBox *modeComboBox = new QComboBox();
    modeComboBox->addItem("Recording");
    modeComboBox->addItem("Streaming");
    layout->addWidget(modeComboBox);
    QObject::connect(modeComboBox, SIGNAL(currentIndexChanged(int)), on_mode_changed);

    // Create the start button
    QPushButton *startButton = new QPushButton("Start");
    layout->addWidget(startButton);
    QObject::connect(startButton, &QPushButton::clicked, on_start_button_clicked);

    // Create the pause button
    QPushButton *pauseButton = new QPushButton("Pause");
    layout->addWidget(pauseButton);
    QObject::connect(pauseButton, &QPushButton::clicked, on_pause_button_clicked);

    // Create the stop button
    QPushButton *stopButton = new QPushButton("Stop");
    layout->addWidget(stopButton);
    QObject::connect(stopButton, &QPushButton::clicked, on_stop_button_clicked);

    // Add the widget to the OBS UI
    obs_frontend_add_dock(widget);

    return true;
}

void obs_module_unload(void)
{
}
