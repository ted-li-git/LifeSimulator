#include "head.h"
void jieshoustring(string& data) {
    ifstream inFile("passstring.txt");
    if (inFile.is_open()) {
        getline(inFile, data);
        inFile.close();
        if (remove("passstring.txt") != 0) {
            cerr << "�޷�ɾ���ļ�: passstring.txt" << endl;
        }
    } else {
        if (remove("passstring.txt") != 0) {
            cerr << "�޷�ɾ���ļ�: passstring.txt" << endl;
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
        cout << "�������Ӧ��Ʒ����" << endl;
        cin >> q;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ��ջ�����
        if (q < 1 || q > items.size()) {
            cout << "��Ч����Ʒ���" << endl;
            continue;
        }
        
        int q2;
        cout << "ִ��ʲô������1.ʹ�� 2.���� 0.ȡ��" << endl;
        cin >> q2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ��ջ�����
        
        if (q2 == 1) {
            if (items[q-1] == "food") {
                cout << "ʹ�����" << endl;
                bsd += 10;
                hp += 1;
                money += 5;
                removeItem(q);
                saveGamenotip(filePath);
            } else if (items[q-1] == "house-key") {
                cout << "�ѽ��㴫��������" << endl;
            } else {
                cout << "���ɻ���" << endl;
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
                cout << "��������" << endl;
                break;
            }
        } else if (q2 == 0) {
            cout << "��ȡ��" << endl;
            break; // �˳�ѭ��
        } else {
            cout << "��Ч�Ĳ������" << endl;
        }
    }

    system("pause");
    return 0;
}
