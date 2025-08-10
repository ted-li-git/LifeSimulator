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
    string m1 = "���㿴�������Ϸ��ʱ��...";
    te(m1, 50, 200);
    string m2 = "��֤�������Ϸ�Ѿ�����ȥ�ˣ���";
    te(m2, 1, 10);
    string m3 = "       ��������Ա����";
    te(m3, 12, 24);
    string m4 = "     ���������ƣ�LJT";
    te(m4, 12, 24);
    string m5 = "   ����.cpp������ƣ�LJT";
    te(m5, 12, 24);
	string m6 = "       ������ƣ�LJT";
    te(m6, 12, 24); 
    string m7 = " ������ߣ�advanced installer";
    te(m7, 12, 24);
    string m8 = "       �����Ա��LJT";
    te(m8, 12, 24);
    string m9 = "   �ֿⴴ���ߣ�ted-li-git";
    te(m9, 12, 24);
    string m10 = "        ��֯�ߣ�LJT";
    te(m10, 12, 24);
    string m11 = "      ��Ϸ�߻���LJT";
    te(m11, 12, 24);
    string m12 = "      ������ƣ�LJT";
    te(m12, 12, 24);
    string m13 = "   README��ƣ�KimiAi,LJT";
    te(m13, 12, 24);
    string m14 = "   ����༭����dev-c++,vscode";
    te(m14, 12, 24);
    string m15 = "       ��Ʒ��LJTStudio";
    te(m15, 12, 24);
    string m16 = "  �����ƹ㣺����LJTStudio��Ա";
    te(m16, 12, 24);
    string m17 = "     -----LJTStudio-----";
    te(m17, 0, 1);
    string m19 = "���ǵ���վ:https://ted-lijunyu.top";
    te(m19, 1, 10);
    string m18 = "     --------END--------";
    te(m18, 12, 24);
    system("pause");
    return 0;
}
