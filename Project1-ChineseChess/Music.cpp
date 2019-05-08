#include "Music.h"

const DWORD C = 262, Cs = 277, Db = 277, D = 294, Ds = 311, Eb = 311, E = 330, F = 349, Fs = 370,
Gb = 370, G = 392, Gs = 415, Ab = 415, A = 440, As = 466, Bb = 466, B = 494;
unsigned DELAY = 60000;

struct note
{
    DWORD frequency;
    double duration;
};

bool Music::play = true;
thread* Music::music = new thread(bind(&setMusic, 2));

Music::~Music()
{
    if (music != NULL)
    {
        play = false;
        music->join();
        delete music;
    }
}

void Music::setMusic(unsigned choice)
{

    if (music != NULL)
    {
        play = false;
        music->join();
        delete music;
        music = NULL;
    }
    if (choice != 0)
    {
        play = true;
        switch (choice)
        {
        case 1:
            bee();
            break;
        case 2:
            familyMart();
            break;
        }
    }
}
void Music::bee()
{
    double speed = 160;
    vector<note> song = { {G,1},{E,1},{E,2},{F,1},{D,1},{D,2},
                         {C,1},{D,1},{E,1},{F,1},{G,1},{G,1},{G,2},
                         {G,1},{E,1},{E,2},{F,1},{D,1},{D,2},
                         {C,1},{E,1},{G,1},{G,1},{E,4},
                         {D,1},{D,1},{D,1},{D,1},{D,1},{E,1},{F,2},
                         {E,1},{E,1},{E,1},{E,1},{E,1},{F,1},{G,2},
                         {G,1},{E,1},{E,2},{F,1},{D,1},{D,2},
                         {C,1},{E,1},{G,1},{G,1},{C,4} };

    short i = 0;
    while (play)
    {
        for (note n : song)
        {
            if (play)
            {
                Beep(n.frequency, static_cast<DWORD>(n.duration*(DELAY / speed)));
            }

        }
    }
}

void Music::familyMart()
{
    double speed = 108;
    vector<note> song = { {E,0.5},{C,0.5},{G / 2,0.5},{C,0.5},{D,0.5},{G,1.5},
                         {D,0.5},{E,0.5},{D,0.5},{G / 2,0.5},{C,2},
                         {E,0.5},{C,0.5},{G / 2,0.5},{C,0.5},{D,0.5},{G,1.5},
                         {D,0.5},{E,0.5},{D,0.5},{G / 2,0.5},{C,2},
                         {E,0.5},{C,0.5},{G / 2,0.5},{C,0.5},{D,0.5},{G,1.5},
                         {D,0.5},{E,0.5},{D,0.5},{G / 2,0.5},{E,0.5},{C,0.5},{D,0.5},{E,0.5} };

    short i = 0;
    while (play)
    {
        for (note n : song)
        {
            if (play)
            {
                Beep(n.frequency, static_cast<DWORD>(n.duration*(DELAY / speed)));
            }

        }
    }
}
