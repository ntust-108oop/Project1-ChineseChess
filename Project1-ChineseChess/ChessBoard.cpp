#include "ChessBoard.h"
const short TOP_BOUND = 1, BOTTOM_BOUND = 24, ROW_ONE = 28, ROW_TWO = 66;
const short BOARD_TOP = TOP_BOUND + 2, BOARD_BOTTOM = BOTTOM_BOUND - 1, BOARD_LEFT = ROW_ONE + 3, BOARD_RIGHT = ROW_TWO - 2;

ChessBoard::ChessBoard()
{
    //開局初始化
    turns = 1;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 9; j++)
            wholePosition[j][i] = NULL;

    //指標賦值
    wholePosition[0][0] = new Chess(4, 0, 0);
    wholePosition[1][0] = new Chess(5, 1, 0);
    wholePosition[2][0] = new Chess(3, 2, 0);
    wholePosition[3][0] = new Chess(2, 3, 0);
    wholePosition[4][0] = new Chess(1, 4, 0);
    wholePosition[5][0] = new Chess(2, 5, 0);
    wholePosition[6][0] = new Chess(3, 6, 0);
    wholePosition[7][0] = new Chess(5, 7, 0);
    wholePosition[8][0] = new Chess(4, 8, 0);
    wholePosition[1][2] = new Chess(6, 1, 2);
    wholePosition[7][2] = new Chess(6, 7, 2);
    wholePosition[0][3] = new Chess(7, 0, 3);
    wholePosition[2][3] = new Chess(7, 2, 3);
    wholePosition[4][3] = new Chess(7, 4, 3);
    wholePosition[6][3] = new Chess(7, 6, 3);
    wholePosition[8][3] = new Chess(7, 8, 3);

    wholePosition[0][9] = new Chess(11, 0, 9);
    wholePosition[1][9] = new Chess(12, 1, 9);
    wholePosition[2][9] = new Chess(10, 2, 9);
    wholePosition[3][9] = new Chess(9, 3, 9);
    wholePosition[4][9] = new Chess(8, 4, 9);
    wholePosition[5][9] = new Chess(9, 5, 9);
    wholePosition[6][9] = new Chess(10, 6, 9);
    wholePosition[7][9] = new Chess(12, 7, 9);
    wholePosition[8][9] = new Chess(11, 8, 9);
    wholePosition[1][7] = new Chess(6, 1, 7);
    wholePosition[7][7] = new Chess(6, 7, 7);
    wholePosition[0][6] = new Chess(7, 0, 6);
    wholePosition[2][6] = new Chess(7, 2, 6);
    wholePosition[4][6] = new Chess(7, 4, 6);
    wholePosition[6][6] = new Chess(7, 6, 6);
    wholePosition[8][6] = new Chess(7, 8, 6);
}

ChessBoard::~ChessBoard()
{
}

ChessBoard::ChessBoard(string fileTxt)
{
    readTheBoard(fileTxt);
}

void printEmptyPlane()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);      // 設定白底黑字

    for (short i = BOARD_TOP; i < BOARD_BOTTOM; i++)              // 印白底
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { BOARD_LEFT,i });
        for (unsigned j = BOARD_LEFT; j <= BOARD_RIGHT; j++)
        {
            cout << " ";
        }
    }
    for (short i = BOARD_TOP + 1; i <= BOARD_BOTTOM; i += 2)            // 印橫線
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { BOARD_LEFT + 1,i });
        for (short j = BOARD_LEFT + 1; j <= BOARD_RIGHT - 1; j++)
        {
            cout << "─";
        }
    }
    for (short i = BOARD_TOP; i <= BOARD_BOTTOM; i++)                // 印直線
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { BOARD_LEFT,i });
        cout << "║";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { BOARD_RIGHT - 1,i });
        cout << "║";
        for (short j = BOARD_LEFT + 4; j <= BOARD_RIGHT - 1 - 4; j += 4)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { j,i });
            cout << "│";
        }
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 3),static_cast<short>(BOTTOM_BOUND - 2) });
    cout << "╙";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_TWO - 3),static_cast<short>(BOTTOM_BOUND - 2) });
    cout << "╜";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 3),static_cast<short>(TOP_BOUND + 3) });
    cout << "╓";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_TWO - 3),static_cast<short>(TOP_BOUND + 3) });
    cout << "╖";

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 17),static_cast<short>(TOP_BOUND + 4) });
    cout << "╲";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 21),static_cast<short>(TOP_BOUND + 6) });
    cout << "╲";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 17),static_cast<short>(TOP_BOUND + 18) });
    cout << "╲";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 21),static_cast<short>(TOP_BOUND + 20) });
    cout << "╲";

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 21),static_cast<short>(TOP_BOUND + 4) });
    cout << "╱";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 17),static_cast<short>(TOP_BOUND + 6) });
    cout << "╱";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 21),static_cast<short>(TOP_BOUND + 18) });
    cout << "╱";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 17),static_cast<short>(TOP_BOUND + 20) });
    cout << "╱";

    for (short i = ROW_ONE + 7; i < ROW_TWO - 3; i += 4)
    {
        for (short j = TOP_BOUND + 5; j < BOTTOM_BOUND - 2; j += 2)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(i),static_cast<short>(j) });
            cout << "┼";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(i),static_cast<short>(TOP_BOUND + 13) });
        cout << "┬";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(i),static_cast<short>(TOP_BOUND + 3) });
        cout << "┬";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(i),static_cast<short>(TOP_BOUND + 11) });
        cout << "┴";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(i),static_cast<short>(BOTTOM_BOUND - 2) });
        cout << "┴";
    }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 4),static_cast<short>(TOP_BOUND + 12) });
    cout << "     楚河            漢界      ";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 253);      // 設定白底粉字
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 3),static_cast<short>(TOP_BOUND + 2) });
    cout << "１  ２  ３  ４  ５  ６  ７  ８  ９";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(ROW_ONE + 3),static_cast<short>(BOTTOM_BOUND - 1) });
    cout << "九  八  七  六  五  四  三  二  一";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void ChessBoard::printThePlane()
{
    printEmptyPlane();
    for (unsigned i = 0; i < 9; i++)
    {
        for (unsigned j = 0; j < 10; j++)
        {
            if (wholePosition[i][j] != NULL)
            {
                int type = wholePosition[i][j]->getChessType();
                if (type <= 7)
                {
                    SetColor(0x80);                         // 黑棋：灰底黑字
                }
                else if (type >= 8)
                {
                    SetColor(0x84);                         // 紅棋：灰底紅字
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(BOARD_LEFT + i * 4), static_cast<short>(BOARD_TOP + 1 +2*  j) });
                switch (type)
                {
                case 1:
                    cout << "將";
                    break;
                case 2:
                    cout << "士";
                    break;
                case 3:
                    cout << "象";
                    break;
                case 4:
                    cout << "車";
                    break;
                case 5:
                    cout << "馬";
                    break;
                case 6:
                    cout << "包";
                    break;
                case 7:
                    cout << "卒";
                    break;
                case 8:
                    cout << "帥";
                    break;
                case 9:
                    cout << "仕";
                    break;
                case 10:
                    cout << "相";
                    break;
                case 11:
                    cout << "俥";
                    break;
                case 12:
                    cout << "傌";
                    break;
                case 13:
                    cout << "炮";
                    break;
                case 14:
                    cout << "兵";
                    break;
                }

            }
        }
    }
}

void ChessBoard::printChosenPlane()
{
    for (int i = 5; i < 40; i++) // 測試排版：清一塊空白的區域
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(42),static_cast<short>(i) });
        for (int j = 0; j < 65; j++)
        {
            cout << " ";
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // 測試排版
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(50 + j * 5),static_cast<short>(2 + i * 4) });

            position tmp;
            tmp.x = j;
            tmp.y = i;
            //從legalMove中找到可以走的位置，改變顏色配置
            vector<position>::iterator it = find(legalMove.begin(), legalMove.end(), tmp);
            if (it != legalMove.end()) SetColor(112);
            else SetColor();
            if (wholePosition[j][i] != NULL)cout << wholePosition[j][i]->getChessType() << "\t";
            else cout << "0\t";
        }
        cout << "\n";
    }
    // 因為畫框框會被影響所以稍微寫一下
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<short>(50),static_cast<short>(42) });

    cout << turns << "\n";
}

void ChessBoard::moveTheChess(int fromX, int fromY, int toX, int toY)
{
    if (wholePosition[toX][toY] != NULL)
    {
        delete wholePosition[toX][toY];
        wholePosition[toX][toY] = wholePosition[fromX][fromY];
        wholePosition[fromX][fromY] = NULL;
    }
    else
    {
        wholePosition[toX][toY] = wholePosition[fromX][fromY];
        wholePosition[fromX][fromY] = NULL;
    }
}

void ChessBoard::readTheBoard(string fileTxt)
{
    //開檔讀取並新建所需的棋子
    fstream file(fileTxt);
    if (file.is_open())
    {
        //丟掉現存的棋盤內容
        /*待補record部分的清除*/
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 9; j++)
                if (wholePosition[j][i] != NULL)
                {
                    delete wholePosition[j][i];
                    wholePosition[j][i] = NULL;
                }
        }

        int tmp;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                file >> tmp;
                if (tmp != 0)wholePosition[j][i] = new Chess(tmp, j, i);
            }
        }
        file >> turns;
    }
    file.close();
    file.clear();
}

void ChessBoard::saveTheBoard(string fileTxt)
{
    fstream file(fileTxt);
    if (file.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                wholePosition[j][i] == NULL ? file << wholePosition[j][i]->getChessType() : file << '0';
                file << ' ';
            }
            file << '\n';
        }
        file << turns;
    }
    file.close();
    file.clear();
}

void ChessBoard::saveTheBoard()
{
    fstream file;
    file.open("file.txt", ios::trunc);
    if (file.is_open())
    {
        file.clear();
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                wholePosition[j][i] == NULL ? file << wholePosition[j][i]->getChessType() : file << '0';
                file << ' ';
            }
            file << '\n';
        }
        file >> turns;
    }
    file.close();
    file.clear();
}

void ChessBoard::manageLegalMove(int x, int y)
{
    position temp = wholePosition[x][y]->getCurrentPosition();
    switch (wholePosition[x][y]->getChessType())
    {
    case 1: //黑將
        if (temp.x > 3) //向左
        {
            temp.x--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x < 5) //向右
        {
            temp.x++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.y > 7) //向上
        {
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.y < 9) //向下
        {
            temp.y++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        // 王不見王
        while (temp.y > 0)
        {
            temp.y--;
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                // 若是中間被擋住就沒事
                if (wholePosition[temp.x][temp.y]->getChessType() != 8)
                {
                    break;
                }
                else
                {
                    legalMove.push_back(temp);
                    break;
                }
            }
        }
        break;

    case 2: //黑士
        if (temp.x > 3 && temp.y > 7) //向左上
        {
            temp.x--;
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x < 5 && temp.y > 7) //向右上
        {
            temp.x++;
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x > 3 && temp.y < 9) //向左下
        {
            temp.x--;
            temp.y++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x < 5 && temp.y < 9) //向右下
        {
            temp.x++;
            temp.y++;
            legalMove.push_back(temp);
        }
        break;

    case 3: //黑象
        if (temp.x - 2 >= 0 && temp.y - 2 >= 5 && (wholePosition[x - 1][y - 1] == NULL)) //向左上
        {
            temp.x -= 2;
            temp.y -= 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 2 <= 8 && temp.y - 2 >= 5 && (wholePosition[x + 1][y - 1] == NULL)) //向右上
        {
            temp.x += 2;
            temp.y -= 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x - 2 >= 0 && temp.y + 2 <= 9 && (wholePosition[x - 1][y + 1] == NULL)) //向左下
        {
            temp.x -= 2;
            temp.y += 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 2 <= 8 && temp.y + 2 <= 9 && (wholePosition[x + 1][y + 1] == NULL)) //向右下
        {
            temp.x += 2;
            temp.y += 2;
            legalMove.push_back(temp);
        }
        break;


    case 4:  //黑車
    case 11: //紅車
        while (temp.x > 0) //向左
        {
            temp.x--;
            legalMove.push_back(temp);
        }
        temp = wholePosition[x][y]->getCurrentPosition();
        while (temp.x < 8) //向右
        {
            temp.x++;
            legalMove.push_back(temp);
        }
        temp = wholePosition[x][y]->getCurrentPosition();
        while (temp.y > 0) //向上
        {
            temp.y--;
            legalMove.push_back(temp);
        }
        temp = wholePosition[x][y]->getCurrentPosition();
        while (temp.y < 9) //向下
        {
            temp.y++;
            legalMove.push_back(temp);
        }
        break;

    case 5: //黑馬
    case 12: //紅傌
        if (temp.x - 2 >= 0 && temp.y - 1 >= 0 && wholePosition[temp.x - 1][temp.y] == NULL) //向 10 點鐘方向
        {
            temp.x = temp.x - 2;
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x - 1 >= 0 && temp.y - 2 >= 0 && wholePosition[temp.x][temp.y - 1] == NULL) //向 11 點鐘方向
        {
            temp.x--;
            temp.y = temp.y - 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 1 <= 8 && temp.y - 2 >= 0 && wholePosition[temp.x][temp.y - 1] == NULL) //向 1 點鐘方向
        {
            temp.x++;
            temp.y = temp.y - 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 2 <= 8 && temp.y - 1 >= 0 && wholePosition[temp.x + 1][temp.y] == NULL) //向 2 點鐘方向
        {
            temp.x = temp.x + 2;
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 2 <= 8 && temp.y + 1 <= 9 && wholePosition[temp.x + 1][temp.y] == NULL) //向 4 點鐘方向
        {
            temp.x = temp.x + 2;
            temp.y++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 1 <= 8 && temp.y + 2 <= 9 && wholePosition[temp.x][temp.y + 1] == NULL) //向 5 點鐘方向
        {
            temp.x++;
            temp.y = temp.y + 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x - 1 >= 0 && temp.y + 2 <= 9 && wholePosition[temp.x][temp.y + 1] == NULL) //向 7 點鐘方向
        {
            temp.x--;
            temp.y = temp.y + 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x - 2 >= 0 && temp.y + 1 <= 9 && wholePosition[temp.x - 1][temp.y] == NULL) //向 8 點鐘方向
        {
            temp.x = temp.x - 2;
            temp.y++;
            legalMove.push_back(temp);
        }
        break;

    case 6: //黑包
    case 13: //紅炮
        while (temp.x > 0) //向左
        {
            temp.x--;
            legalMove.push_back(temp);
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                break;
            }
        }
        while (temp.x > 0)  // 取得可以吃的那一個
        {
            temp.x--;
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                legalMove.push_back(temp);
                break;
            }
        }
        temp = wholePosition[x][y]->getCurrentPosition();

        while (temp.x < 8) //向右
        {
            temp.x++;
            legalMove.push_back(temp);
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                break;
            }
        }
        while (temp.x < 8)
        {
            temp.x++;
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                legalMove.push_back(temp);
                break;
            }
        }
        temp = wholePosition[x][y]->getCurrentPosition();

        while (temp.y > 0) //向上
        {
            temp.y--;
            legalMove.push_back(temp);
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                break;
            }
        }
        while (temp.y > 0)
        {
            temp.y--;
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                legalMove.push_back(temp);
                break;
            }
        }
        temp = wholePosition[x][y]->getCurrentPosition();

        while (temp.y < 9) //向下
        {
            temp.y++;
            legalMove.push_back(temp);
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                break;
            }
        }
        while (temp.y < 9)
        {
            temp.y++;
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                legalMove.push_back(temp);
                break;
            }
        }
        break;

    case 7: //黑卒
        if (temp.y >= 5) //在己方範圍，只能向下
        {
            temp.y--;
            legalMove.push_back(temp);
        }
        else //在敵方範圍
        {
            if (temp.x > 0) //向左
            {
                temp.x--;
                legalMove.push_back(temp);
                temp = wholePosition[x][y]->getCurrentPosition();
            }
            if (temp.x < 8) //向右
            {
                temp.x++;
                legalMove.push_back(temp);
                temp = wholePosition[x][y]->getCurrentPosition();
            }
            if (temp.y > 0) //向下
            {
                temp.y--;
                legalMove.push_back(temp);
            }
        }
        break;

    case 8: //紅帥
        if (temp.x > 3) //向左
        {
            temp.x--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x < 5) //向右
        {
            temp.x++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.y > 0) //向下
        {
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.y < 2) //向上
        {
            temp.y++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        // 王不見王
        while (temp.y < 9)
        {
            temp.y++;
            if (wholePosition[temp.x][temp.y] != NULL)
            {
                // 若是中間被擋住就沒事
                if (wholePosition[temp.x][temp.y]->getChessType() != 8)
                {
                    break;
                }
                else
                {
                    legalMove.push_back(temp);
                    break;
                }
            }
        }
        break;

    case 9: //紅仕
        if (temp.x > 3 && temp.y > 0) //向左上
        {
            temp.x--;
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x < 5 && temp.y > 0) //向右上
        {
            temp.x++;
            temp.y--;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x > 3 && temp.y < 2) //向左下
        {
            temp.x--;
            temp.y++;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x < 5 && temp.y < 2) //向右下
        {
            temp.x++;
            temp.y++;
            legalMove.push_back(temp);
        }
        break;

    case 10: //紅相
        if (temp.x - 2 >= 0 && temp.y - 2 >= 0 && (wholePosition[x - 1][y - 1] == NULL)) //向左下
        {
            temp.x = temp.x - 2;
            temp.y = temp.y - 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 2 <= 8 && temp.y - 2 >= 0 && (wholePosition[x + 1][y - 1] == NULL)) //向右下
        {
            temp.x = temp.x + 2;
            temp.y = temp.y - 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x - 2 >= 0 && temp.y + 2 <= 4 && (wholePosition[x - 1][y + 1] == NULL)) //向左上
        {
            temp.x = temp.x - 2;
            temp.y = temp.y + 2;
            legalMove.push_back(temp);
            temp = wholePosition[x][y]->getCurrentPosition();
        }
        if (temp.x + 2 <= 8 && temp.y + 2 <= 4 && (wholePosition[x + 1][y + 1] == NULL)) //向右上
        {
            temp.x = temp.x + 2;
            temp.y = temp.y + 2;
            legalMove.push_back(temp);
        }
        break;

    case 14: //紅兵
        if (temp.y <= 4) //在己方範圍，只能向上
        {
            temp.y++;
            legalMove.push_back(temp);
        }
        else //在敵方範圍
        {
            if (temp.x > 0) //向左
            {
                temp.x--;
                legalMove.push_back(temp);
                temp = wholePosition[x][y]->getCurrentPosition();
            }
            if (temp.x < 8) //向右
            {
                temp.x++;
                legalMove.push_back(temp);
                temp = wholePosition[x][y]->getCurrentPosition();
            }
            if (temp.y < 9) //向上
            {
                temp.y++;
                legalMove.push_back(temp);
            }
        }
        break;
    }
}


Chess* ChessBoard::getChess(position cursorPosition)
{
    position chessPosition;
    chessPosition.x = (cursorPosition.x - ROW_ONE - 3) / 4;
    chessPosition.y = cursorPosition.y - TOP_BOUND - 3;
    return wholePosition[chessPosition.x][chessPosition.y];
}

int ChessBoard::getTurn()
{
    return turns;
}

void ChessBoard::clearLegalMove()
{
    legalMove.clear();
}

void ChessBoard::SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
