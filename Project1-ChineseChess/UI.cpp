#include "UI.h"

const short TOP_BOUND = 1, BOTTOM_BOUND = 24, LEFT_BOUND = 1, RIGHT_BOUND = 106, ROW_ONE = 28, ROW_TWO = 66;
const char ESC = 0x1B, UP = 0x48, DOWN = 0x50, LEFT = 0x4B, RIGHT = 0x4D, ENTER = 0x0D;

UI::UI()
{
    lastChosed = NULL;
    cueMode = true;
}


// Intent: 讀取鍵盤
// Pre: UI物件
// Post: 依據鍵盤傳入的值做出反應
void UI::readKeyBoard()
{
    SetPosition(chessToCursor({ 4,6 }));
    char key;
    string fileName;
    while (1)
    {
        position cursorPosition = getCursorPosition();  // 取得當前游標位置
        switch (key = _getch())
        {
        case UP:                                        // 上
            if (cursorPosition.y - 2 > TOP_BOUND + 2)
            {
                SetPosition({ cursorPosition.x,cursorPosition.y - 2 });
            }
            break;
        case DOWN:                                      // 下
            if (cursorPosition.y + 2 < BOTTOM_BOUND)
            {
                SetPosition({ cursorPosition.x,cursorPosition.y + 2 });
            }
            break;
        case  LEFT:                                     // 左
            if (cursorPosition.x - 4 > ROW_ONE + 2)
            {
                SetPosition({ cursorPosition.x - 4,cursorPosition.y });
            }
            break;
        case  RIGHT:                                     // 右
            if (cursorPosition.x + 4 < ROW_TWO - 2)
            {
                SetPosition({ cursorPosition.x + 4,cursorPosition.y });
            }
            break;
        case ENTER:
            position chessPosition = cursorToChess(cursorPosition);
            if (lastChosed == NULL)                                         // 若非選棋狀態
            {
                Chess* currentChosed = chessBoard.getChess(chessPosition);
                if (currentChosed != NULL)                                   // 選的地方又有棋子
                {
                    if (chessBoard.getTurn() == 0 && currentChosed->getChessType() <= 7 ||
                        chessBoard.getTurn() == 1 && currentChosed->getChessType() >= 8)    // 選棋符合turn
                    {
                        chessBoard.manageLegalMove(chessPosition.x, chessPosition.y);
                        lastChosed = chessBoard.getChess(chessPosition);
                        lastChosed->setChosen(true);
                        if (cueMode == true)                                    // 若提示開啟則印出提示
                        {
                            chessBoard.printChosenPlane();
                            SetPosition(cursorPosition);
                        }
                    }
                }
            }
            else                                                           // 若已有選擇的棋
            {
                bool inLegalMove = false;                                         // 點選可移動的區域則移動
                for (unsigned i = 0; i < chessBoard.legalMove.size(); i++)
                {
                    if (chessPosition == chessBoard.legalMove[i])
                    {
                        inLegalMove = true;
                        if (chessBoard.getChess(chessPosition) != NULL && chessBoard.getChess(chessPosition)->getChessType() == 1) // 吃到將
                        {
                            lastChosed = NULL;
                            if (showWin(1))
                            {
                                // 重新開始
                                SetColor(0x07);
                                chessBoard.readTheBoard("Initial.txt");
                                chessBoard.clearLegalMove();
                                Record::clearRecord();
								Record::returnStep.clear();
                                system("cls");
                                printUI();
                                chessBoard.printThePlane();
                                SetPosition(chessToCursor({ 4, 6 }));
                            }
                            else
                            {
                                return;
                            }
                        }
                        else if (chessBoard.getChess(chessPosition) != NULL && chessBoard.getChess(chessPosition)->getChessType() == 8) // 吃到帥
                        {
                            lastChosed = NULL;
                            if (showWin(0))
                            {
                                // 重新開始
                                SetColor(0x07);
                                chessBoard.readTheBoard("Initial.txt");
                                chessBoard.clearLegalMove();
                                Record::clearRecord();
								Record::returnStep.clear();
                                system("cls");
                                printUI();
                                chessBoard.printThePlane();
                                SetPosition(chessToCursor({ 4, 6 }));
                            }
                            else
                            {
                                return;
                            }
                        }
                        else
                        {
							int eatenType = 0, ifOnly = 0, total = 0, soldierPos = 0;
							if (chessBoard.wholePosition[chessPosition.x][chessPosition.y] != NULL)
							{
								eatenType = chessBoard.wholePosition[chessPosition.x][chessPosition.y]->getChessType();
							}
							for (int i = 0; i < 10; i++)
							{
								if (chessBoard.wholePosition[lastChosed->getCurrentPosition().x][i] != NULL)
								{
									if (lastChosed->getChessType() == chessBoard.wholePosition[lastChosed->getCurrentPosition().x][i]->getChessType())
									{
										total++;
										if (i < lastChosed->getCurrentPosition().y) { ifOnly = 2; soldierPos++; }
										else if (i > lastChosed->getCurrentPosition().y) { ifOnly = 1; }
									}
								}
							}

							if (lastChosed->getChessType() == 7 || lastChosed->getChessType() == 14)
							{
								if (total == 1)
								{
									ifOnly = 0;
								}
								else
								{
									ifOnly = total * 10 + soldierPos + 1;
								}
							}
							
                            Record::saveThisStep(lastChosed->getChessType(), lastChosed->getCurrentPosition(),chessPosition, ifOnly, eatenType);
							Record::returnStep.clear();
                            chessBoard.moveTheChess(lastChosed->getCurrentPosition().x,
                                lastChosed->getCurrentPosition().y,
                                chessPosition.x,
                                chessPosition.y
							);

                            lastChosed->setChosen(false);
                            lastChosed = NULL;
                            chessBoard.clearLegalMove();
                            chessBoard.changeTurn();
                            chessBoard.printThePlane();
                            Record::printRecord();
                            if (chessBoard.getTurn() == 0)
                            {
                                SetPosition(chessToCursor({ 4, 3 }));
                            }
                            else
                            {
                                SetPosition(chessToCursor({ 4, 6 }));
                            }
                        }
                        break;
                    }
                }
                if (inLegalMove == false)                                         // 點選其他地方則取消
                {
                    lastChosed->setChosen(false);
                    lastChosed = NULL;
                    chessBoard.clearLegalMove();
                    chessBoard.printThePlane();
                }
                SetPosition(cursorPosition);
            }
            break;
        case ESC:                                      // 選單
            switch (showMenu())
            {
            case 0:                                     // 繼續遊戲
                chessBoard.printThePlane();
                SetPosition(cursorPosition);
                break;
            case 1:                                     // 重新開始
                if (showAlert("重新開始？", false) == true)
                {
                    SetColor(0x07);
                    chessBoard.readTheBoard("Initial.txt");
                    chessBoard.clearLegalMove();
                    Record::clearRecord();
                    system("cls");
                    printUI();
                    chessBoard.printThePlane();
                    SetPosition(chessToCursor({ 4, 6 }));
                }
                else
                {
                    chessBoard.printThePlane();
                    SetPosition(cursorPosition);
                }
                break;
            case 2:                                     // 儲存遊戲
                fileName = showInput("輸入檔名");
                if (showAlert("確定儲存？", false, fileName.insert(0,"檔名：")) == true)
                {
                    fileName = fileName.substr(6);
                    _mkdir("save");
                    chessBoard.saveTheBoard(fileName.insert(0, "save/"));
                }
                chessBoard.printThePlane();
                SetPosition(cursorPosition);
                break;
            case 3:                            
                fileName = showInput("輸入檔名");       // 讀取遊戲
                if (showAlert("確定讀取？", false, fileName.insert(0, "檔名：")) == true)
                {
                    fileName = fileName.substr(6);
                    if (chessBoard.readTheBoard(fileName.insert(0, "save/")) == true)
                    {
                        // 待補讀取成功
                    }
                    else
                    {
                        // 待補讀取失敗
                    }
                }
                chessBoard.printThePlane();
                SetPosition(chessToCursor({ 4, 6 }));
                break;
            case 4:                                     // 使用提示
                if (showAlert("使用提示？", true) == true)
                {
                    cueMode = true;
                    chessBoard.printThePlane();
                }
                else
                {
                    cueMode = false;
                    chessBoard.printThePlane();
                }
                SetPosition(cursorPosition);
                break;
                break;
            case 5:                                     // 設定音樂
                Music::setMusic(1);
                chessBoard.printThePlane();
                SetPosition(cursorPosition);
                break;
            case 6:                                     // 結束遊戲
                if (showAlert("結束遊戲？", false) == true)
                {
                    return;
                }
                else
                {
                    chessBoard.printThePlane();
                    SetPosition(cursorPosition);
                }
                break;
            }
            break;
        case 'r':
        case 'R':                                       // 悔棋
            if (showAlert("確定悔棋？", false) == true)
            {
				if (Record::record.size() != 0)
				{
					chessBoard.moveTheChess(Record::getToPos().x, Record::getToPos().y, Record::getFromPos().x, Record::getFromPos().y);
					if (Record::getEaten() != 0)
					{
						chessBoard.wholePosition[Record::getToPos().x][Record::getToPos().y] = new Chess(Record::getEaten(), Record::getToPos().x, Record::getToPos().y);
					}
					Record::regretStep();
					chessBoard.changeTurn();
				}
				else
				{
					showYesAlert("已經沒有更早的步數了",34);
				}
                chessBoard.printThePlane();
				Record::printRecord();
            }
            else
            {
                // 不悔棋就直接印原本棋盤把alert蓋掉
                chessBoard.printThePlane();
            }
            SetPosition(cursorPosition);
            break;
        case 'u':
        case 'U':                                       // 還原
            if (showAlert("確定還原？", false) == true)
            {
				if (Record::returnStep.size() != 0)
				{
					chessBoard.moveTheChess(Record::returnStep[Record::returnStep.size() - 1].fromPos.x,
						Record::returnStep[Record::returnStep.size() - 1].fromPos.y,
						Record::returnStep[Record::returnStep.size() - 1].toPos.x,
						Record::returnStep[Record::returnStep.size() - 1].toPos.y
					);
					Record::returnRegret();
					chessBoard.changeTurn();
				}
				else
				{
					showYesAlert("已經到最新的步數了",34);
				}
				
                chessBoard.printThePlane();
				Record::printRecord();
            }
            else
            {
                // 不還原就直接印原本棋盤把alert蓋掉
                chessBoard.printThePlane();
            }
            SetPosition(cursorPosition);
            break;
        }
    }
}

// Intent: 印出操作畫面
// Pre: UI物件
// Post: 印出結果
void UI::printUI()
{
    SetColor(0x07);
    for (short i = 0; i < BOTTOM_BOUND - 1; i++)            // 印直線
    {
        SetPosition({ LEFT_BOUND, TOP_BOUND + i });             // 最左兩條
        cout << "║ ║";
        SetPosition({ ROW_ONE, TOP_BOUND + i });                // 棋盤左邊
        cout << "║";
        SetPosition({ ROW_TWO, TOP_BOUND + i });                // 棋盤右邊
        cout << "║";
        SetPosition({ RIGHT_BOUND - 2, TOP_BOUND + i });        // 最右兩條
        cout << "║ ║";
    }

    SetPosition({ LEFT_BOUND, TOP_BOUND });                 // 印橫線
    for (short i = 0; i < RIGHT_BOUND - 1; i++)                 // 最上
    {
        cout << "═";
    }
    SetPosition({ LEFT_BOUND, BOTTOM_BOUND });                  // 最下
    for (short i = 0; i < RIGHT_BOUND - 1; i++)
    {
        cout << "═";
    }
    SetPosition({ LEFT_BOUND + 2, TOP_BOUND + 1 });             // 左欄的上邊
    for (short i = 0; i < ROW_ONE - 2; i++)
    {
        cout << "═";
    }
    SetPosition({ LEFT_BOUND + 2, BOTTOM_BOUND - 1 });              // 左欄的下邊
    for (short i = 0; i < ROW_ONE - 2; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO, TOP_BOUND + 1 });             // 右欄的上邊
    for (short i = 0; i < RIGHT_BOUND - 2 - ROW_TWO; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO + 1, BOTTOM_BOUND - 1 });          // 右欄的下邊
    for (short i = 0; i < RIGHT_BOUND - 2 - ROW_TWO; i++)
    {
        cout << "═";
    }
    SetPosition({ ROW_TWO, BOTTOM_BOUND - 9 });                  // 右欄的分隔線
    for (short i = 0; i < RIGHT_BOUND - ROW_TWO - 1; i++)
    {
        cout << "═";
    }

    SetPosition({ LEFT_BOUND, TOP_BOUND });                 // 印角角
    cout << "╔";
    SetPosition({ LEFT_BOUND + 2, TOP_BOUND + 1 });
    cout << "╔";
    SetPosition({ ROW_TWO, TOP_BOUND + 1 });
    cout << "╔";

    SetPosition({ RIGHT_BOUND, TOP_BOUND });
    cout << "╗";
    SetPosition({ RIGHT_BOUND - 2, TOP_BOUND + 1 });
    cout << "╗";
    SetPosition({ ROW_ONE, TOP_BOUND + 1 });
    cout << "╗";

    SetPosition({ LEFT_BOUND, BOTTOM_BOUND });
    cout << "╚";
    SetPosition({ LEFT_BOUND + 2, BOTTOM_BOUND - 1 });
    cout << "╚";
    SetPosition({ ROW_TWO, BOTTOM_BOUND - 1 });
    cout << "╚";

    SetPosition({ RIGHT_BOUND, BOTTOM_BOUND });
    cout << "╝";
    SetPosition({ RIGHT_BOUND - 2, BOTTOM_BOUND - 1 });
    cout << "╝";
    SetPosition({ ROW_ONE, BOTTOM_BOUND - 1 });
    cout << "╝";

    SetPosition({ ROW_TWO, BOTTOM_BOUND - 9 });
    cout << "╠";
    SetPosition({ RIGHT_BOUND - 2, BOTTOM_BOUND - 9 });
    cout << "╣";

    SetPosition({ LEFT_BOUND + 6, TOP_BOUND + 1 });           // 印字
    cout << "  戰  況  顯  示  ";
    SetPosition({ ROW_TWO + 6,BOTTOM_BOUND - 8 });
    cout << "ESC 選單    R 悔棋    U 還原";
    SetPosition({ ROW_TWO + 9,BOTTOM_BOUND - 6 });
    cout << "Enter     選取棋子";
    SetPosition({ ROW_TWO + 11,BOTTOM_BOUND - 4 });
    cout << "↑";
    SetPosition({ ROW_TWO + 9,BOTTOM_BOUND - 3 });
    cout << "←  →  方向鍵控制游標";
    SetPosition({ ROW_TWO + 11,BOTTOM_BOUND - 2 });
    cout << "↓";
}

// Intent: 跳出選單
// Pre: UI物件
// Post: 回傳選擇
int UI::showMenu()
{
    vector<string> list = { "繼續遊戲", "重新開始","儲存遊戲","讀取遊戲", "設定提示", "設定音樂", "結束遊戲" };
    const short MENU_TOP = 7, MENU_LEFT = 38, MENU_RIGHT = 57;
    short menuBottom = static_cast<short>(MENU_TOP + list.size() * 2);
    SetColor(0x01);      // 設定黑底藍字

    for (short i = MENU_TOP; i < menuBottom; i++)              // 印黑底
    {
        SetPosition({ MENU_LEFT,i });
        for (short j = MENU_LEFT; j <= MENU_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = MENU_LEFT; i <= MENU_RIGHT; i++)     // 畫橫線
    {
        SetPosition({ i,MENU_TOP });
        cout << "═";
        SetPosition({ i,menuBottom });
        cout << "═";
    }

    for (short i = MENU_TOP; i < menuBottom; i++)     // 畫直線
    {
        SetPosition({ MENU_LEFT,i });
        cout << "║";
        SetPosition({ MENU_RIGHT - 1,i });
        cout << "║";
    }

    SetPosition({ MENU_LEFT,menuBottom });
    cout << "╙";
    SetPosition({ MENU_RIGHT - 1,menuBottom });
    cout << "╜";
    SetPosition({ MENU_LEFT,MENU_TOP });
    cout << "╓";
    SetPosition({ MENU_RIGHT - 1,MENU_TOP });
    cout << "╖";


    setCursorVisable(false);

    char key;
    int choice = 0;
    for (short i = 0; i < static_cast<short>(list.size()); i++)
    {
        if (i == choice)
        {
            SetColor(0x70);      // 設定亮灰底黑字
        }
        else
        {
            SetColor(0x07);      // 設定黑底亮灰字
        }
        SetPosition({ MENU_LEFT + 6,MENU_TOP + 1 + 2 * i });
        cout << list[i];
    }
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case UP:
            if (choice > 0)
            {
                choice--;
            }
            else
            {
                choice = static_cast<int>(list.size() - 1);
            }
            for (short i = 0; i < static_cast<short>(list.size()); i++)
            {
                if (i == choice)
                {
                    SetColor(0x70);      // 設定亮灰底黑字
                }
                else
                {
                    SetColor(0x07);      // 設定黑底亮灰字
                }
                SetPosition({ MENU_LEFT + 6,MENU_TOP + 1 + 2 * i });
                cout << list[i];
            }
            break;
        case DOWN:
            if (choice < list.size() - 1)
            {
                choice++;
            }
            else
            {
                choice = 0;
            }
            for (short i = 0; i < static_cast<short>(list.size()); i++)
            {
                if (i == choice)
                {
                    SetColor(0x70);      // 設定亮灰底黑字
                }
                else
                {
                    SetColor(0x07);      // 設定黑底亮灰字
                }
                SetPosition({ MENU_LEFT + 6,MENU_TOP + 1 + 2 * i });
                cout << list[i];
            }
            break;
        case ENTER:
            setCursorVisable(true);
            SetPosition({ ROW_ONE + 3,TOP_BOUND + 3 });

            return choice;
            break;
        }
    }
}

// Intent: 跳出Y/N視窗
// Pre: UI物件、訊息、預設為是或否
// Post: 回傳真假值
bool UI::showAlert(string message, bool defaultChoice)
{
    const short ALERT_TOP = TOP_BOUND + 8, ALERT_BOTTOM = ALERT_TOP+6, ALERT_LEFT = ROW_ONE + 8, ALERT_RIGHT = ROW_TWO - 7;
    SetColor(0x04);      // 設定黑底暗紅字

    for (short i = ALERT_TOP; i < ALERT_BOTTOM; i++)              // 印黑底
    {
        SetPosition({ ALERT_LEFT,i });
        for (unsigned j = ALERT_LEFT; j <= ALERT_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = ALERT_LEFT; i <= ALERT_RIGHT; i++)     // 畫橫線
    {
        SetPosition({ i,ALERT_TOP });
        cout << "═";
        SetPosition({ i,ALERT_BOTTOM });
        cout << "═";
    }

    for (short i = ALERT_TOP; i <= ALERT_BOTTOM; i++)     // 畫直線
    {
        SetPosition({ ALERT_LEFT,i });
        cout << "║";
        SetPosition({ ALERT_RIGHT - 1,i });
        cout << "║";
    }

    SetPosition({ ALERT_LEFT,ALERT_BOTTOM });
    cout << "╙";
    SetPosition({ ALERT_RIGHT - 1,ALERT_BOTTOM });
    cout << "╜";
    SetPosition({ ALERT_LEFT,ALERT_TOP });
    cout << "╓";
    SetPosition({ ALERT_RIGHT - 1,ALERT_TOP });
    cout << "╖";

    SetColor(0x07);
    SetPosition({ ALERT_LEFT + 8,ALERT_TOP + 2 });
    cout << message;

    SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 4 });
    cout << "是        否";
    if (defaultChoice == true)
    {
        SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 4 });
    }
    else
    {
        SetPosition({ ALERT_LEFT + 16,ALERT_TOP + 4 });
    }

    char key;
    bool choice = defaultChoice;
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case LEFT:
        case RIGHT:
            if (choice == true)
            {
                choice = false;
                SetPosition({ ALERT_LEFT + 16,ALERT_TOP + 4 });
            }
            else
            {
                choice = true;
                SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 4 });
            }
            break;
        case ENTER:
            return choice;
        }
    }
}

// Intent: 跳出Y/N視窗(兩行)
// Pre: UI物件、訊息、預設為是或否
// Post: 回傳真假值
bool UI::showAlert(string message, bool defaultChoice, string secondaryMessage)
{
    const short ALERT_TOP = TOP_BOUND + 9, ALERT_BOTTOM = BOTTOM_BOUND - 6, ALERT_LEFT = ROW_ONE + 8, ALERT_RIGHT = ROW_TWO - 7;
    SetColor(0x04);      // 設定黑底暗紅字

    for (short i = ALERT_TOP; i < ALERT_BOTTOM; i++)              // 印黑底
    {
        SetPosition({ ALERT_LEFT,i });
        for (unsigned j = ALERT_LEFT; j <= ALERT_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = ALERT_LEFT; i <= ALERT_RIGHT; i++)     // 畫橫線
    {
        SetPosition({ i,ALERT_TOP });
        cout << "═";
        SetPosition({ i,ALERT_BOTTOM });
        cout << "═";
    }

    for (short i = ALERT_TOP; i <= ALERT_BOTTOM; i++)     // 畫直線
    {
        SetPosition({ ALERT_LEFT,i });
        cout << "║";
        SetPosition({ ALERT_RIGHT - 1,i });
        cout << "║";
    }

    SetPosition({ ALERT_LEFT,ALERT_BOTTOM });
    cout << "╙";
    SetPosition({ ALERT_RIGHT - 1,ALERT_BOTTOM });
    cout << "╜";
    SetPosition({ ALERT_LEFT,ALERT_TOP });
    cout << "╓";
    SetPosition({ ALERT_RIGHT - 1,ALERT_TOP });
    cout << "╖";

    SetColor(0x07);
    SetPosition({ ALERT_LEFT + 8,ALERT_TOP + 3 });
    cout << message;
    SetColor(0x08);
    SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 4 });
    cout << secondaryMessage;

    SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 6 });
    cout << "是        否";
    if (defaultChoice == true)
    {
        SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 6 });
    }
    else
    {
        SetPosition({ ALERT_LEFT + 16,ALERT_TOP + 6 });
    }

    char key;
    bool choice = defaultChoice;
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case LEFT:
        case RIGHT:
            if (choice == true)
            {
                choice = false;
                SetPosition({ ROW_ONE + 24,ALERT_TOP + 6 });
            }
            else
            {
                choice = true;
                SetPosition({ ROW_ONE + 14,ALERT_TOP + 6 });
            }
            break;
        case ENTER:
            return choice;
        }
    }
}

// Intent: 跳出確定視窗
// Pre: UI物件、訊息、預設為是或否
// Post: 回傳真假值
void UI::showYesAlert(string message, short left)
{
    const short ALERT_TOP = TOP_BOUND + 8, ALERT_BOTTOM = ALERT_TOP +6, ALERT_LEFT = left, ALERT_RIGHT = left+static_cast<short>(message.length())+8;
    SetColor(0x04);      // 設定黑底暗紅字

    for (short i = ALERT_TOP; i < ALERT_BOTTOM; i++)              // 印黑底
    {
        SetPosition({ ALERT_LEFT,i });
        for (auto j = ALERT_LEFT; j <= ALERT_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = ALERT_LEFT; i <= ALERT_RIGHT; i++)     // 畫橫線
    {
        SetPosition({ i,ALERT_TOP });
        cout << "═";
        SetPosition({ i,ALERT_BOTTOM });
        cout << "═";
    }

    for (short i = ALERT_TOP; i <= ALERT_BOTTOM; i++)     // 畫直線
    {
        SetPosition({ ALERT_LEFT,i });
        cout << "║";
        SetPosition({ ALERT_RIGHT - 1,i });
        cout << "║";
    }

    SetPosition({ ALERT_LEFT,ALERT_BOTTOM });
    cout << "╙";
    SetPosition({ ALERT_RIGHT - 1,ALERT_BOTTOM });
    cout << "╜";
    SetPosition({ ALERT_LEFT,ALERT_TOP });
    cout << "╓";
    SetPosition({ ALERT_RIGHT - 1,ALERT_TOP });
    cout << "╖";

    SetColor(0x07);
    SetPosition({ ALERT_LEFT + 4,ALERT_TOP + 2 });
    cout << message;
    SetColor(0x70);
    SetPosition({ ALERT_LEFT+(ALERT_RIGHT - ALERT_LEFT)/2  -2,ALERT_TOP + 4 });
    cout << "確定";

    setCursorVisable(false);
    char key;
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case ENTER:
            setCursorVisable(true);
            return;
        }
    }
}

// Intent: 跳出獲勝視窗
// Pre: UI物件
// Post: 回傳真假值
bool UI::showWin(unsigned color)
{
    const short WIN_TOP = TOP_BOUND + 1, WIN_BOTTOM = BOTTOM_BOUND - 1, WIN_LEFT = LEFT_BOUND + 24, WIN_RIGHT = RIGHT_BOUND - 25;
    SetColor(0x77);
    setCursorVisable(false);

    for (short i = WIN_TOP; i < WIN_BOTTOM; i++)              // 印白底
    {
        SetPosition({ WIN_LEFT,i });
        for (unsigned j = WIN_LEFT; j <= WIN_RIGHT - 1; j++)
        {
            cout << " ";
        }
    }

    SetColor(0x11);
    for (short i = WIN_TOP; i <= WIN_BOTTOM; i++)     // 畫直線
    {
        SetPosition({ WIN_LEFT,i });
        cout << "█";
        SetPosition({ WIN_RIGHT - 2,i });
        cout << "█";
    }

    for (short i = WIN_LEFT; i <= WIN_RIGHT - 1; i += 2)     // 畫橫線
    {
        SetPosition({ i,WIN_TOP });
        cout << "█";
        SetPosition({ i,WIN_BOTTOM });
        cout << "█";
    }

    if (color == 0)
    {
        SetColor(0x70);
    }
    else
    {
        SetColor(0x7C);
    }
    for (int i = 0; i < 15; i++)
    {
        SetPosition({ WIN_LEFT + 4,WIN_TOP + 2 + i });
        switch (i)
        {
        case 0:
            cout << "██     ███          ████   ████";
            break;
        case 1:
            cout << " ██     ██  ████  ███   　██ ";
            break;
        case 2:
            cout << "  ██  ██   ██   ██  ██     ██";
            break;
        case 3:
            cout << "   ████    ██   ██  ██    ██";
            break;
        case 4:
            cout << "     ██      ██  ██    █████";
            break;
        case 5:
            cout << "   ████     ████      ████      █";
            break;
        case 6:
            cout << "                                           ██";
            break;
        case 7:
            cout << "███  █  ███ ███ ██    ███  ███";
            break;
        case 8:
            cout << " ██  ██  ██   ██   ██    ██   ███";
            break;
        case 9:
            cout << " ██  ██  ██   ██   ███  ██    ██";
            break;
        case 10:
            cout << "  ██ ██ ██    ██   ██████     █";
            break;
        case 11:
            cout << "  ███████    ██   ██████";
            break;
        case 12:
            cout << "   ██████     ██   ██   ███    █";
            break;
        case 13:
            cout << "    ██  ██      ██   ██     ██   ██";
            break;
        case 14:
            cout << "     █    █      ███ ███     ██   █";
            break;
        }
    }

    SetColor(0x07);
    SetPosition({ WIN_RIGHT - 37,WIN_BOTTOM - 2 });

    cout << "開啟新局";

    SetColor(0x70);
    cout << "  ";
    cout << "結束遊戲";

    char key;
    bool choice = true;
    while (1)
    {
        key = _getch();
        switch (key)
        {
        case LEFT:
        case RIGHT:
            if (choice == true)
            {
                choice = false;
                SetColor(0x70);
                SetPosition({ WIN_RIGHT - 37,WIN_BOTTOM - 2 });
                cout << "開啟新局";
                cout << "  ";
                SetColor(0x07);
                cout << "結束遊戲";
            }
            else
            {
                choice = true;
                SetColor(0x07);
                SetPosition({ WIN_RIGHT - 37,WIN_BOTTOM - 2 });
                cout << "開啟新局";
                SetColor(0x70);
                cout << "  ";
                cout << "結束遊戲";
            }
            break;
        case ENTER:
            setCursorVisable(true);
            return choice;
        }
    }
}

// Intent: 跳出輸入視窗
// Pre: UI物件、訊息
// Post: 回傳字串
string UI::showInput(string message)
{
    const short ALERT_TOP = TOP_BOUND + 9, ALERT_BOTTOM = BOTTOM_BOUND - 7, ALERT_LEFT = ROW_ONE + 8, ALERT_RIGHT = ROW_TWO - 7;
    SetColor(0x04);      // 設定黑底暗紅字

    for (short i = ALERT_TOP; i < ALERT_BOTTOM; i++)              // 印黑底
    {
        SetPosition({ ALERT_LEFT,i });
        for (unsigned j = ALERT_LEFT; j <= ALERT_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = ALERT_LEFT; i <= ALERT_RIGHT; i++)     // 畫橫線
    {
        SetPosition({ i,ALERT_TOP });
        cout << "═";
        SetPosition({ i,ALERT_BOTTOM });
        cout << "═";
    }

    for (short i = ALERT_TOP; i <= ALERT_BOTTOM; i++)     // 畫直線
    {
        SetPosition({ ALERT_LEFT,i });
        cout << "║";
        SetPosition({ ALERT_RIGHT - 1,i });
        cout << "║";
    }

    SetPosition({ ALERT_LEFT,ALERT_BOTTOM });
    cout << "╙";
    SetPosition({ ALERT_RIGHT - 1,ALERT_BOTTOM });
    cout << "╜";
    SetPosition({ ALERT_LEFT,ALERT_TOP });
    cout << "╓";
    SetPosition({ ALERT_RIGHT - 1,ALERT_TOP });
    cout << "╖";

    SetColor(0x07);
    SetPosition({ ALERT_LEFT + 8,ALERT_TOP + 3 });
    cout << message;

    SetPosition({ ALERT_LEFT + 6,ALERT_TOP + 5 });
    SetColor(0x70);
    cout << "           ";
    SetPosition({ ALERT_LEFT + 7,ALERT_TOP + 5 });

    string userInput;
    cin >> userInput;
    return userInput;
}
