#include "midigenerator.h"

namespace
{

static const QList<int> Harmony = {0, 2, 3, 5, 7, 9, 10};
static const int NoteStart = 55;

int stepHarmony(const int step, const int noteStart, const int transposition, const QList<int>& harmony)
{
    int note = noteStart + transposition + harmony.at(step % harmony.size()) + 12 * (step / harmony.size());

    return note;
}

}

MidiGenerator::MidiGenerator(QObject *parent)
    : QObject{parent}
{

}

QMidiFile *MidiGenerator::generateFromText(const QString &text)
{
    QMidiFile* midi = new QMidiFile();
    midi->setResolution(480);

    const int instrument = 0;
    const int track = midi->createTrack();
    midi->createProgramChangeEvent(track, 0, track, instrument);
    midi->createMetaEvent(track, 0, QMidiEvent::MetaNumbers::TrackName, "Track 1");

    const int tempo = 120;
    midi->createTempoEvent(0, 0, tempo);

    float preTime = 0;

    for (const QChar& c : text)
    {
        float startNoteTime = preTime;
        float stopNoteTime = startNoteTime;

        if (c == ' ')
        {
            // pause

            const ushort duration = 8;
            stopNoteTime  = startNoteTime + 240.0f / tempo / duration;
        }
        else
        {
            // note

            const ushort note = c.unicode() % 12;
            const ushort duration = (1 + (c.unicode() % 4)) * 4;
            stopNoteTime  = startNoteTime + 240.0f / tempo / duration;

            midi->createNote(track,
                             midi->tickFromTime(startNoteTime),
                             midi->tickFromTime(stopNoteTime),
                             track,
                             stepHarmony(note, NoteStart, 0, Harmony),
                             95,
                             95);
        }

        preTime = stopNoteTime;
    }

    return midi;
}
