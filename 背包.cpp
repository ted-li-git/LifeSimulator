#include "head.h"
void jieshoustring(string& data) {
    ifstream inFile("passstring.txt");
    if (inFile.is_open()) {
        getline(inFile, data);
        inFile.close();
        if (remove("passstring.txt") != 0) {
            cerr << "无法删除文件: passstring.txt" << endl;
        }
    } else {
        if (remove("passstring.txt") != 0) {
            cerr << "无法删除文件: passstring.txt" << endl;
        }
    }
}

int main() {
    string filePath;
    jieshoustring(filePath);
    loadSaveFile(filePath);
    while (true) {
    	ReloadSaveFile(filePath);
        displayItems();
        int q;
        cout << "请输入对应物品数字" << endl;
        cin >> q;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区
        if (q < 1 || q > items.size()) {
            cout << "无效的物品编号" << endl;
            continue;
        }
        
        int q2;
        cout << "执行什么操作？1.使用 2.卖出 0.取消" << endl;
        cin >> q2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区
        
        if (q2 == 1) {
            if (items[q-1] == "food") {
                cout << "使用完毕" << endl;
                bsd += 10;
                hp += 1;
                money += 5;
                removeItem(q);
                saveGamenotip(filePath);
            } else if (items[q-1] == "house-key") {
                cout << "已将你传送至房子" << endl;
            } else {
                cout << "不可互动" << endl;
            }
        } else if (q2 == 2) {
            if (items[q-1] == "food") {
                money += 20;
                removeItem(q);
                saveGamenotip(filePath);
            } else if (items[q-1] == "bv") {
                money += 10000;
                removeItem(q);
                saveGamenotip(filePath);
            } else {
                cout << "不可卖出" << endl;
                break;
            }
        } else if (q2 == 0) {
            cout << "已取消" << endl;
            break; // 退出循环
        } else {
            cout << "无效的操作编号" << endl;
        }
    }

    system("pause");
    return 0;
}
