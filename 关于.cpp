#include <iostream>
#include <thread>
#include <chrono>
#include <random>
using namespace std;
void te(const string& text, int min_delay_ms, int max_delay_ms) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_delay_ms, max_delay_ms);
    for (char c : text) {
        cout << c;
        int delay_ms = dis(gen);
        this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    cout << endl;
}

int main() {
    string m1 = "当你看到这个游戏的时候...";
    te(m1, 50, 200);
    string m2 = "就证明这个游戏已经发出去了！！";
    te(m2, 1, 10);
    string m3 = "       开发者人员名单";
    te(m3, 12, 24);
    string m4 = "     主体代码设计：LJT";
    te(m4, 12, 24);
    string m5 = "   工作.cpp代码设计：LJT";
    te(m5, 12, 24);
	string m6 = "       关于设计：LJT";
    te(m6, 12, 24); 
    string m7 = " 打包工具：advanced installer";
    te(m7, 12, 24);
    string m8 = "       打包人员：LJT";
    te(m8, 12, 24);
    string m9 = "   仓库创建者：ted-li-git";
    te(m9, 12, 24);
    string m10 = "        组织者：LJT";
    te(m10, 12, 24);
    string m11 = "      游戏策划：LJT";
    te(m11, 12, 24);
    string m12 = "      动画设计：LJT";
    te(m12, 12, 24);
    string m13 = "   README设计：KimiAi,LJT";
    te(m13, 12, 24);
    string m14 = "   代码编辑器：dev-c++,vscode";
    te(m14, 12, 24);
    string m15 = "       出品：LJTStudio";
    te(m15, 12, 24);
    string m16 = "  宣传推广：所有LJTStudio成员";
    te(m16, 12, 24);
    string m17 = "     -----LJTStudio-----";
    te(m17, 0, 1);
    string m19 = "我们的网站:https://ted-lijunyu.top";
    te(m19, 1, 10);
    string m18 = "     --------END--------";
    te(m18, 12, 24);
    system("pause");
    return 0;
}
