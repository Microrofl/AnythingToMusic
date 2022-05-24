#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "midiplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSaveMIDI_clicked();

    void on_pushButtonPlay_clicked();

private:
    QMidiFile* generateMidi() const;

    Ui::MainWindow *ui;
    QSettings* settings = nullptr;
    MidiPlayer midiPlayer;
};
#endif // MAINWINDOW_H
