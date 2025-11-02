#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ---------- 1. 跨平台原始键盘 ----------
#ifdef _WIN32
    #include <conio.h>
    int getKey() {
        int ch = _getch();
        if (ch == 0 || ch == 224)          // 方向键前缀
            return _getch();
        return ch;
    }
#else
    #include <termios.h>
    #include <unistd.h>
    int getKey() {
        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

// ---------- 2. 工具 ----------
void moveCursor(int y, int x) {
    cout << "\033[" << y << ";" << x << "H";
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

// ---------- 3. 手机模拟 ----------
struct App {
    string name;
};

// ---------- 3. 假功能 ----------
// ---------- 假功能：拨号界面 ----------
void fakePhone() {
    const vector<string> dial = {
        "1","2","3",
        "4","5","6",
        "7","8","9",
        "*","0","#",
        "返回"
    };
    int sel = 13;          // 默认停在“返回”
    bool inDial = true;

    while (inDial) {
        clearScreen();

        // 画标题
        moveCursor(1,5);
        cout << "拨号界面";

        // 3×4 网格 + 返回
        for (size_t i = 0; i < dial.size(); ++i) {
            int y = 3 + (int)(i / 3) * 2;      // 每行 3 个按钮
            int x = 4 + (int)(i % 3) * 4;
            moveCursor(y, x);
            if (i == (size_t)sel) cout << "\033[7m";
            cout << " " << dial[i] << " ";
            cout << "\033[0m";
        }

        // 提示
        moveCursor(11,1);
        cout << "方向键移动，回车选择";

        // 键盘
        int ch = getKey();
#ifdef _WIN32
        switch (ch) {
            case 72: if (sel > 2) sel -= 3; break;        // ↑
            case 80: if (sel < 12) sel += 3; break;       // ↓
            case 75: if (sel % 3) --sel; break;           // ←
            case 77: if ((sel % 3) < 2) ++sel; break;     // →
            case 13:   // Windows
    			if (sel == 13) {            // 13 对应 “返回”
        			inDial = false;         // 退出拨号界面
    			} else {
        			moveCursor(12, 1);
        			cout << "正在拨打 " << dial[sel] << " ... 按任意键";
        			getKey();
    			}
    			break;
        }
#else
        switch (ch) {
            case 27:
                if (getKey() == '[') {
                    switch (getKey()) {
                        case 'A': if (sel > 2) sel -= 3; break; // ↑
                        case 'B': if (sel < 12) sel += 3; break; // ↓
                        case 'C': if ((sel % 3) < 2) ++sel; break; // →
                        case 'D': if (sel % 3) --sel; break; // ←
                    }
                }
                break;
            case 10:
                if (sel == 13) { inDial = false; }        // 返回
                else {
                    moveCursor(12,1);
                    cout << "正在拨打 " << dial[sel] << " ... 按任意键";
                    getKey();
                }
                break;
        }
#endif
    }
}

void fakeSms() {
    clearScreen();
    cout << "+--------------+\n";
    cout <<"| 短信列表     |\n";
    cout <<"| 无新消息     |\n";
    cout <<"| 任意键返回   |\n";
    cout <<"+--------------+\n";
    getKey();
}

void fakeGallery() {
    clearScreen();
    cout << "+--------------+\n";
    cout << "| 相册         |\n";
    cout << "| 0 张照片     |\n";
    cout << "| 任意键返回   |\n";
    cout << "+--------------+\n";
    getKey();
}

void fakeSettings() {
    clearScreen();
    cout << "+--------------+\n";
    cout << "| 设置         |\n";
    cout << "| 声音 100%    |\n";
    cout << "| 任意键返回   |\n";
    cout << "+--------------+\n";
    getKey();
}

// ---------- 4. 主循环 ----------
int main() {
    const vector<App> apps = {
        {"电话"},
        {"短信"},
        {"相册"},
        {"设置"}
    };
    int sel = 0;
    bool running = true;

    while (running) {
        clearScreen();

        // 画外框
        moveCursor(1, 1);
        cout << "+--------------+";
        for (int i = 2; i <= 7; ++i) {
            moveCursor(i, 1);
            cout << "|              |";
        }
        moveCursor(8, 1);
        cout << "+--------------+";

        // 标题
        moveCursor(2, 3);
        cout << "主界面";

        // 应用列表
        for (size_t i = 0; i < apps.size(); ++i) {
            moveCursor(4 + (int)i, 3);
            if (i == (size_t)sel)
                cout << "\033[7m";          // 反色
            cout << apps[i].name;
            cout << "\033[0m";
        }

        // 状态提示
        moveCursor(9, 1);

        // ---------- 键盘处理 ----------
        int ch = getKey();
#ifdef _WIN32
        switch (ch) {
            case 72: if (sel > 0) --sel; break;           // ↑
            case 80: if (sel < (int)apps.size() - 1) ++sel; break; // ↓
            case 13:                                         // 回车
                switch (sel) {
                    case 0: fakePhone();    break;
                    case 1: fakeSms();      break;
                    case 2: fakeGallery();  break;
                    case 3: fakeSettings(); break;
                }
                break;
            case 'q': case 'Q': running = false; break;
        }
#else
        switch (ch) {
            case 27: {                       // ESC 前缀
                if (getKey() == '[') {
                    switch (getKey()) {
                        case 'A': if (sel > 0) --sel; break; // ↑
                        case 'B': if (sel < (int)apps.size() - 1) ++sel; break; // ↓
                    }
                }
                break;
            }
            case 10:                          // 回车
                switch (sel) {
                    case 0: fakePhone();    break;
                    case 1: fakeSms();      break;
                    case 2: fakeGallery();  break;
                    case 3: fakeSettings(); break;
                }
                break;
            case 'q': case 'Q': running = false; break;
        }
#endif
    }

    clearScreen();
    cout << "再见\n";
    return 0;
}
