#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <string>

using namespace std;

// 地图尺寸
const int MAP_W = 70;
const int MAP_H = 30;
// 地图数据（F=家具/不可通行，#=墙，+=门）
char map[MAP_H][MAP_W + 1];
// 玩家坐标（x为偶数，适配中文宽度）
int px = 30, py = 15;
int oldPx = px, oldPy = py;
// 控制台句柄
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
// 交互提示缓存
string tipText = "";

// ========== 工具函数 ==========
// 设置光标位置
void setPos(int x, int y) {
    SetConsoleCursorPosition(hOut, {(SHORT)x, (SHORT)y});
}

// 隐藏光标
void hideCursor() {
    CONSOLE_CURSOR_INFO ci{1, FALSE};
    SetConsoleCursorInfo(hOut, &ci);
}

// 绘制单字符
void draw(int x, int y, char c, WORD color = 7) {
    COORD pos = {(SHORT)x, (SHORT)y};
    DWORD w;
    FillConsoleOutputCharacterA(hOut, c, 1, pos, &w);
    FillConsoleOutputAttribute(hOut, color, 1, pos, &w);
}

// 绘制字符串（仅玩家和提示用）
void drawStr(int x, int y, const char* str, WORD color = 7) {
    setPos(x, y);
    SetConsoleTextAttribute(hOut, color);
    cout << str;
    SetConsoleTextAttribute(hOut, 7);
}

// 清空指定位置
void clearPos(int x, int y, int len = 2) {
    COORD pos = {(SHORT)x, (SHORT)y};
    DWORD w;
    FillConsoleOutputCharacterA(hOut, ' ', len, pos, &w);
}

// 清空底部提示栏
void clearTipBar() {
    setPos(0, MAP_H + 1);
    cout << string(MAP_W, ' '); // 用空格覆盖整行
}

// ========== 地图构建（符号化家具+加宽门体） ==========
void buildHouse() {
    // 1. 初始化空白地图
    for (int y = 0; y < MAP_H; ++y)
        for (int x = 0; x < MAP_W; ++x)
            map[y][x] = ' ';

    // 2. 双层外墙
    for (int x = 0; x < MAP_W; ++x) {
        map[0][x] = map[1][x] = map[MAP_H - 1][x] = map[MAP_H - 2][x] = '#';
    }
    for (int y = 0; y < MAP_H; ++y) {
        map[y][0] = map[y][1] = map[y][MAP_W - 1] = map[y][MAP_W - 2] = '#';
    }

    // 3. 内部房间隔墙
    // 客厅（10-50列，5-25行）
    int hall_l = 10, hall_r = 50, hall_t = 5, hall_b = 25;
    for (int x = hall_l; x <= hall_r; ++x) { map[hall_t][x] = '#'; map[hall_b][x] = '#'; }
    for (int y = hall_t; y <= hall_b; ++y) { map[y][hall_l] = '#'; map[y][hall_r] = '#'; }
    // 卧室（3-8列，8-22行）
    int bed_l = 3, bed_r = 8, bed_t = 8, bed_b = 22;
    for (int x = bed_l; x <= bed_r; ++x) { map[bed_t][x] = '#'; map[bed_b][x] = '#'; }
    for (int y = bed_t; y <= bed_b; ++y) { map[y][bed_l] = '#'; map[y][bed_r] = '#'; }
    // 厨房（53-65列，10-23行）
    int kit_l = 53, kit_r = 65, kit_t = 10, kit_b = 23;
    for (int x = kit_l; x <= kit_r; ++x) { map[kit_t][x] = '#'; map[kit_b][x] = '#'; }
    for (int y = kit_t; y <= kit_b; ++y) { map[y][kit_l] = '#'; map[y][kit_r] = '#'; }
    // 卫生间（53-65列，5-8行）
    int toi_l = 53, toi_r = 65, toi_t = 5, toi_b = 8;
    for (int x = toi_l; x <= toi_r; ++x) { map[toi_t][x] = '#'; map[toi_b][x] = '#'; }
    for (int y = toi_t; y <= toi_b; ++y) { map[y][toi_l] = '#'; map[y][toi_r] = '#'; }

    // 4. 门（加宽为3格）
    for (int x = 29; x <= 31; ++x) map[hall_t][x] = '+';    // 客厅正门
    for (int y = 14; y <= 16; ++y) map[y][hall_l] = '+';    // 客厅→卧室门
    for (int y = 14; y <= 16; ++y) map[y][hall_r] = '+';    // 客厅→厨房门
    for (int y = 6; y <= 8; ++y) map[y][hall_r] = '+';     // 客厅→卫生间门
    for (int x = 4; x <= 6; ++x) map[bed_t][x] = '+';      // 卧室侧门

    // 5. 家具（符号化，直接写入地图，F标记不可通行）
    // 客厅
    for (int x = 15; x <= 25; ++x) { map[12][x] = 'S'; map[12][x] = 'F'; } // 沙发(S)
    for (int x = 20; x <= 24; ++x) { map[15][x] = 'T'; map[15][x] = 'F'; } // 茶几(T)
    for (int x = 35; x <= 45; ++x) { map[8][x] = 'V'; map[8][x] = 'F'; }   // 电视(V)
    // 卧室
    for (int x = 4; x <= 7; ++x) { map[15][x] = 'B'; map[15][x] = 'F'; }   // 床(B)
    for (int x = 3; x <= 7; ++x) { map[10][x] = 'C'; map[10][x] = 'F'; }   // 衣柜(C)
    // 厨房
    for (int x = 55; x <= 60; ++x) { map[15][x] = 'Z'; map[15][x] = 'F'; } // 灶台(Z)
    for (int x = 55; x <= 63; ++x) { map[18][x] = 'G'; map[18][x] = 'F'; } // 橱柜(G)
    // 卫生间
    map[7][55] = 'M'; map[7][55] = 'F'; // 马桶(M)
    map[7][60] = 'X'; map[7][60] = 'F'; // 洗手台(X)

    // 修正：家具符号直接写入地图（上面的F标记覆盖了符号，重新赋值）
    // 客厅
    for (int x = 15; x <= 25; ++x) map[12][x] = 'S'; // 沙发(S)
    for (int x = 20; x <= 24; ++x) map[15][x] = 'T'; // 茶几(T)
    for (int x = 35; x <= 45; ++x) map[8][x] = 'V';  // 电视(V)
    // 卧室
    for (int x = 4; x <= 7; ++x) map[15][x] = 'B';  // 床(B)
    for (int x = 3; x <= 7; ++x) map[10][x] = 'C';  // 衣柜(C)
    // 厨房
    for (int x = 55; x <= 60; ++x) map[15][x] = 'Z'; // 灶台(Z)
    for (int x = 55; x <= 63; ++x) map[18][x] = 'G'; // 橱柜(G)
    // 卫生间
    map[7][55] = 'M'; // 马桶(M)
    map[7][60] = 'X'; // 洗手台(X)
}

// ========== 绘制完整地图（符号化家具） ==========
void drawAll() {
    // 绘制墙/门/家具符号
    for (int y = 0; y < MAP_H; ++y) {
        for (int x = 0; x < MAP_W; ++x) {
            WORD color = 7;
            switch (map[y][x]) {
                case '#': color = 8; break;    // 墙：深灰
                case '+': color = 10; break;   // 门：绿色
                case 'S': color = 13; break;   // 沙发(S)：粉色
                case 'T': color = 11; break;   // 茶几(T)：青色
                case 'V': color = 9;  break;   // 电视(V)：蓝色
                case 'B': color = 14; break;   // 床(B)：黄色
                case 'C': color = 13; break;   // 衣柜(C)：粉色
                case 'Z': color = 4;  break;   // 灶台(Z)：红色
                case 'G': color = 11; break;   // 橱柜(G)：青色
                case 'M': color = 10; break;   // 马桶(M)：绿色
                case 'X': color = 14; break;   // 洗手台(X)：黄色
            }
            draw(x, y, map[y][x], color);
        }
    }

    // 绘制房间名称（符号标注，非中文）
    drawStr(25, 6, "[Hall]", 14);       // 客厅
    drawStr(4, 9,  "[Bedroom]", 13);    // 卧室
    drawStr(58, 11,"[Kitchen]", 4);     // 厨房
    drawStr(58, 6, "[Toilet]", 10);     // 卫生间

    // 绘制门标注（符号）
    drawStr(28, 5, "[Door]", 10);       // 正门
    drawStr(8, 15, "[Door]", 10);       // 卧室门
    drawStr(51, 15,"[Door]", 10);       // 厨房门
    drawStr(51, 7, "[Door]", 10);       // 卫生间门
    drawStr(3, 8,  "[Door]", 10);       // 卧室侧门
}

// ========== 检测玩家位置并生成交互提示（适配符号家具） ==========
void checkPlayerPosTip() {
    string newTip = "";
    int x = px;
    int y = py;

    // 1. 检测门区域
    if (map[y][x] == '+' || map[y][x-1] == '+' || map[y][x+1] == '+' ||
        map[y-1][x] == '+' || map[y+1][x] == '+') {
        newTip = "Near [Door] - Passable";
    }
    // 2. 检测客厅
    else if (x >= 10 && x <= 50 && y >= 5 && y <= 25) {
        newTip = "In [Hall] - Leisure Area";
        // 检测客厅家具
        if (x >= 15 && x <= 25 && y == 12) newTip = "Near [Sofa(S)] - Rest";
        else if (x >= 20 && x <= 24 && y == 15) newTip = "Near [Table(T)] - Eat";
        else if (x >= 35 && x <= 45 && y == 8) newTip = "Near [TV(V)] - Watch";
    }
    // 3. 检测卧室
    else if (x >= 3 && x <= 8 && y >= 8 && y <= 22) {
        newTip = "In [Bedroom] - Rest Area";
        if (x >= 4 && x <= 7 && y == 15) newTip = "Near [Bed(B)] - Sleep";
        else if (x >= 3 && x <= 7 && y == 10) newTip = "Near [Closet(C)] - Dress";
    }
    // 4. 检测厨房
    else if (x >= 53 && x <= 65 && y >= 10 && y <= 23) {
        newTip = "In [Kitchen] - Cooking Area";
        if (x >= 55 && x <= 60 && y == 15) newTip = "Near [Stove(Z)] - Cook";
        else if (x >= 55 && x <= 63 && y == 18) newTip = "Near [Cabinet(G)] - Store";
    }
    // 5. 检测卫生间
    else if (x >= 53 && x <= 65 && y >= 5 && y <= 8) {
        newTip = "In [Toilet] - Wash Area";
        if (x == 55 && y == 7) newTip = "Near [Toilet(M)] - Use";
        else if (x == 60 && y == 7) newTip = "Near [Sink(X)] - Wash";
    }
    else {
        newTip = "In [Corridor] - Connect Rooms";
    }

    // 更新提示
    if (newTip != tipText) {
        tipText = newTip;
        clearTipBar();
        drawStr(0, MAP_H + 1, tipText.c_str(), 14);
    }
}

// ========== 玩家移动逻辑（防吃门+符号适配） ==========
void movePlayer(int dx, int dy) {
    int nx = px + dx * 2; 
    int ny = py + dy;

    // 边界检测
    if (nx < 2 || nx >= MAP_W - 2 || ny < 2 || ny >= MAP_H - 2) 
        return;

    // 碰撞检测（仅墙#/家具符号不可通行）
    char cell_core = map[ny][nx];
    char cell_left = map[ny][nx - 1];
    char cell_right = map[ny][nx + 1];
    // 家具符号列表：S/T/V/B/C/Z/G/M/X 都不可通行
    bool isFurniture = (cell_core == 'S' || cell_core == 'T' || cell_core == 'V' ||
                        cell_core == 'B' || cell_core == 'C' || cell_core == 'Z' ||
                        cell_core == 'G' || cell_core == 'M' || cell_core == 'X');
    bool isWall = (cell_core == '#' || cell_left == '#' || cell_right == '#');
    bool isFurBlock = (cell_left == 'S' || cell_left == 'T' || cell_left == 'V' ||
                       cell_left == 'B' || cell_left == 'C' || cell_left == 'Z' ||
                       cell_left == 'G' || cell_left == 'M' || cell_left == 'X' ||
                       cell_right == 'S' || cell_right == 'T' || cell_right == 'V' ||
                       cell_right == 'B' || cell_right == 'C' || cell_right == 'Z' ||
                       cell_right == 'G' || cell_right == 'M' || cell_right == 'X');
    if (isWall || isFurniture || isFurBlock) return;

    // 擦除旧位置（恢复原始符号/门/墙）
    // 核心点
    char oldCell = map[oldPy][oldPx];
    WORD oldColor = 7;
    switch (oldCell) {
        case '#': oldColor = 8; break;
        case '+': oldColor = 10; break;
        case 'S': oldColor = 13; break;
        case 'T': oldColor = 11; break;
        case 'V': oldColor = 9; break;
        case 'B': oldColor = 14; break;
        case 'C': oldColor = 13; break;
        case 'Z': oldColor = 4; break;
        case 'G': oldColor = 11; break;
        case 'M': oldColor = 10; break;
        case 'X': oldColor = 14; break;
    }
    draw(oldPx, oldPy, oldCell, oldColor);
    // 左侧点
    char oldCellL = map[oldPy][oldPx - 1];
    WORD oldColorL = 7;
    switch (oldCellL) {
        case '#': oldColorL = 8; break;
        case '+': oldColorL = 10; break;
        case 'S': oldColorL = 13; break;
        case 'T': oldColorL = 11; break;
        case 'V': oldColorL = 9; break;
        case 'B': oldColorL = 14; break;
        case 'C': oldColorL = 13; break;
        case 'Z': oldColorL = 4; break;
        case 'G': oldColorL = 11; break;
        case 'M': oldColorL = 10; break;
        case 'X': oldColorL = 14; break;
    }
    draw(oldPx - 1, oldPy, oldCellL, oldColorL);

    // 更新坐标
    px = nx;
    py = ny;
    // 绘制玩家（保留中文“我”，或改为符号P）
    drawStr(px - 1, py, "我", 12); // 若要全符号，改为 drawStr(px-1, py, "P", 12);
    // 记录旧坐标
    oldPx = px;
    oldPy = py;

    // 更新提示
    checkPlayerPosTip();
}

// ========== 弹窗提示（符号说明） ==========
void showTipDialog() {
    string tip = 
        "===== 家园系统（beta） =====\n"
        " 移动: WASD\n"
        " 关闭并回到主界面: Q\n"
        "======================================\n"
        "      按下确定进入";
    MessageBoxA(NULL, tip.c_str(), "Operation Tip", MB_OK | MB_ICONINFORMATION);
}

// ========== 主函数 ==========
int main() {
    srand((unsigned)time(nullptr));
    hideCursor();
    showTipDialog();
    buildHouse();
    drawAll();
    drawStr(px - 1, py, "我", 12); // 玩家符号
    checkPlayerPosTip();

    // 主循环
    while (true) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'w': case 'W': movePlayer(0, -1); break;
                case 's': case 'S': movePlayer(0,  1); break;
                case 'a': case 'A': movePlayer(-1, 0); break;
                case 'd': case 'D': movePlayer(1,  0); break;
                case 'q': case 'Q': return 0;
            }
        }
        Sleep(30);
    }
    return 0;
}
