#ifndef RECORD_H
#define RECORD_H
#include "Chess.h"
#include <vector>
using namespace std;

class Record
{

public:
    Record();
    ~Record();

	// 用來儲存資料的
	static vector<int> chessTypeData;
    static vector<struct position> fromPos;
    static vector<struct position> toPos;
	static vector<int> ifOnly;

    static void printRecord();
    static void saveThisStep(int chessType, int fromX, int fromY, int toX, int toY, int only);
	static void clearRecord();
};

#endif // !RECORD_H

