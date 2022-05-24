#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "midigenerator.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(new QSettings(this))
    , midiPlayer(settings, "midiPlayer")
{
    ui->setupUi(this);
    QThreadPool::globalInstance()->start(&midiPlayer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSaveMIDI_clicked()
{
    QMidiFile* midi = generateMidi();
    if (!midi)
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to generate MIDI"));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, ("Save MIDI"),
                                                          QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/from_text.midi",
                                                          ("MIDI (*.mid *.midi);;All files (*)"));
    if (!fileName.isEmpty())
    {
        if (!midi->save(fileName))
        {
            QMessageBox::critical(this, tr("Error"), tr("Failed to save file \"%1\"").arg(fileName));
        }
    }
}


void MainWindow::on_pushButtonPlay_clicked()
{
    QMidiFile* midi = generateMidi();
    if (!midi)
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to generate MIDI"));
        return;
    }

    const MidiPlayer::Error error = midiPlayer.play(midi);
    if (error.type() != MidiPlayer::ErrorType::NoError)
    {
        QMessageBox::critical(this, tr("Error"), error.text());
    }
}

QMidiFile *MainWindow::generateMidi() const
{
    return MidiGenerator().generateFromText(ui->plainTextEdit->toPlainText());
}

