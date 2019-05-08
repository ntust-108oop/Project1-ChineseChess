#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
using namespace std;
class Music
{
public:
    Music();
    ~Music();
    static void setMusic(unsigned);

private:
    static bool play;
    static thread* music;

    // ¦±¥Ø
    static void bee();
    static void familyMart();
};

#endif // !MUSIC_H


