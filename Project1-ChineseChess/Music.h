#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
using namespace std;

struct note
{
    DWORD frequency;
    double duration;
};

class Music
{
public:
    ~Music();
    // ¿ï¾Ü¦±¥Ø
    static void setMusic(unsigned);
    static void player(vector<note>, double);

private:
    static bool play;
    static thread* music;
};

#endif // !MUSIC_H


