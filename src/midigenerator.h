#ifndef MIDIGENERATOR_H
#define MIDIGENERATOR_H

#include <QObject>
#include "QMidiFile.h"

class MidiGenerator : public QObject
{
    Q_OBJECT
public:
    explicit MidiGenerator(QObject *parent = nullptr);

    QMidiFile* generateFromText(const QString& text);

signals:

};

#endif // MIDIGENERATOR_H
