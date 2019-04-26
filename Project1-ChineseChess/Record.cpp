#include "Record.h"



Record::Record()
{
}


Record::~Record()
{
}

void Record::printRecord()
{
}

void Record::saveThisStep(int chessType, int fromX, int fromY, int toX, int toY)
{
	struct position from;
	struct position to;

	from.x = fromX;
	from.y = fromY;
	to.x = toX;
	to.y = toY;

	chessTypeData.push_back(chessType);
	fromPos.push_back(from);
	toPos.push_back(to);
	
}

void Record::clearRecord()
{
	chessTypeData.clear();
	fromPos.clear();
	toPos.clear();
}

