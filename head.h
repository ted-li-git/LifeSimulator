#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <atomic>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());
atomic<bool> stopFlag(false);

int money = 0, hp = 100, bsd = 100, sfd = 100, house = 0;
int joblevel = 1;
string gongzuo = "no-gz", username = "user";
vector<string> items; // 背包中的物品列表

bool checkFileExtension(const string& filePath) {
    size_t dotPos = filePath.rfind('.');
    if (dotPos == string::npos) return false;
    string extension = filePath.substr(dotPos + 1);
    return extension == "ls";
}

void loadSaveFile(string& filePath) {
    if (filePath != "nosave") {
        if (!checkFileExtension(filePath)) {
            cerr << "错误：您的文件后缀不是.ls" << endl;
            return;
        }
        ifstream file(filePath.c_str());
        if (!file.good()) {
            cerr << "错误：打不开您的文件" << endl;
            return;
        }
        file >> username;
        file >> money;
        file >> gongzuo;
        file >> house;
        file >> joblevel;

        // 读取背包中的物品
        items.clear();
        string item;
        while (file >> item) {
            items.push_back(item);
        }

        if (file.fail()) {
            file.close();
            return;
        }
        file.close();
    } else {
        filePath = ".\\Save\\save.ls";
    }
}

string house_detection(int house) {
    if (house == 1) {
        return "146,MonaStreet,MoyaCity-120m2-png:<url id=\"d2ba7m2que5s1gmbufsg\" type=\"url\" status=\"failed\" title=\"\" wc=\"0\">https://ted-lijunyu.top/rsmnq/house/png/1.png</url>   ";
    } else if (house == 2) {
        return "213,PodaStreet,MoyaCity-60m2-png:<url id=\"d2ba7m2que5s1gmbuft0\" type=\"url\" status=\"failed\" title=\"\" wc=\"0\">https://ted-lijunyu.top/rsmnq/house/png/2.png</url>   ";
    } else {
        return "no-house";
    }
}

void increaseMoneyPeriodically() {
    while (!stopFlag) {
        if (gongzuo == "police") {
            this_thread::sleep_for(chrono::seconds(10));
            money += 600 * (joblevel * 0.5);
        } else if (gongzuo == "doctor") {
            this_thread::sleep_for(chrono::seconds(10));
            money += 850 * (joblevel * 0.5);
        } else if (gongzuo == "teacher") {
            this_thread::sleep_for(chrono::seconds(10));
            money += 450 * (joblevel * 0.5);
        } else if (gongzuo == "cleaner") {
            this_thread::sleep_for(chrono::seconds(10));
            money += 10000 * (joblevel * 0.5);
        } else if (gongzuo == "cxy") {
            this_thread::sleep_for(chrono::seconds(60));
            money += 2300 * (joblevel * 0.5);
        } else if (gongzuo == "cy") {
            this_thread::sleep_for(chrono::seconds(180));
            money += 20000 * (joblevel * 0.5);
        } else {
            this_thread::sleep_for(chrono::seconds(10));
            money += 100;
        }
    }
}

void saveGame(string& filePath) {
    if (!checkFileExtension(filePath)) {
        filePath += ".ls";
    }

    ofstream file(filePath, ios::trunc);
    if (!file.is_open()) {
        cerr << "错误：打不开您的文件" << endl;
        return;
    }

    file << username << " " << money << " " << gongzuo << " " << house << " " << joblevel << " ";
    for (const auto& item : items) {
        file << item << " ";
    }

    if (file.fail()) {
        return;
    } else {
        cout << "存档成功！" << endl;
    }

    file.close();
}

void saveGamenotip(string filePath) {
    if (!checkFileExtension(filePath)) {
        filePath += ".ls";
    }

    ofstream file(filePath, ios::trunc);
    if (!file.is_open()) {
        cerr << "错误：打不开您的文件" << endl;
        return;
    }

    file << username << " " << money << " " << gongzuo << " " << house << " " << joblevel << " ";
    for (const auto& item : items) {
        file << item << " ";
    }

    file.close();
}

void cls() {
    system("cls");
}

void xcls() {
    while (true) {
        char key = _getch();
        if (key == 'X' || key == 'x') {
            system("cls");
            break;
        }
    }
}

void printx() {
    cout << "按X键回到主页" << endl;
}

void noop() {
    // 空操作
}

void ReloadSaveFile(const string& filePath) {
    if (!checkFileExtension(filePath)) {
        cerr << "错误：您的文件后缀不是.ls" << endl;
        return;
    }

    ifstream file(filePath.c_str());
    if (!file.good()) {
        cerr << "错误：打不开您的文件" << endl;
        return;
    }

    file >> username;
    file >> money;
    file >> gongzuo;
    file >> house;
    file >> joblevel;

    // 读取背包中的物品
    items.clear();
    string item;
    while (file >> item) {
        items.push_back(item);
    }

    if (file.fail()) {
        file.close();
        return;
    }

    file.close();
}

void displayItems() {
    cout << "背包内容：" << endl;
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << "." << items[i] << endl;
    }
}

void addItem(const string& item) {
    items.push_back(item);
}

void removeItem(int index) {
    if (index > 0 && index <= items.size()) {
        items.erase(items.begin() + index + 1);
    } else {
        cout << "无效的位置: " << index << endl;
    }
}

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
