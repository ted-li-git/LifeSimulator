#include "head.h"
using namespace std;
int index;
string filePath;

void createPassStringFile(const string& filePath) {
    ofstream outFile("passstring.txt");
    if (outFile.is_open()) {
        outFile << filePath << endl;
        outFile.close();
    }
}


int main() {
	 
    cout << "              ����ģ����" << endl;
    cout << "            powered by LJT" << endl;
    cout << "��ȡ�浵��������·����û�д浵������\"nosave\"��";
    cin >> filePath;
    string hd;
    int q;
    loadSaveFile(filePath);
    thread moneyThread(increaseMoneyPeriodically);
    cls();
    cout<<"��ã��û� "<<username<<" "<<endl;
    while (true) {
        cout << "1.��⵱ǰ״̬" << endl;
        cout << "2.����" << endl;
        cout << "3.�ҹ���" << endl;
        cout << "4.�浵" << endl;
        cout << "5.ȥ����" << endl;
        cout << "6.����" << endl;
        cout << "7.����" << endl;
        cout << "8.����" << endl;
        cout << "9.�̵�" << endl;
        cout << "10.�˳�" << endl;
        cout << "�����ַ�����ʼ��Ϸ" << endl;
        cin >> index;
        hd = house_detection(house);
        ReloadSaveFile(filePath);
        if (index == 1) {
        	ReloadSaveFile(filePath);
        	cls();
        	cout << "Ŀǰ���֣�" << username << endl;
            cout << "ĿǰHP:" << hp << endl;
            cout << "ĿǰǮ��:" << money << endl;
            cout << "Ŀǰ����:" << hd << endl;
            cout << "Ŀǰ����:" << gongzuo << endl;
            cout << "Ŀǰ�����ȼ�:" << joblevel << endl;
            cout << "Ŀǰ��ʳ��:" << bsd << " " << "Ŀǰ�ڿ�ֵ:" << sfd << endl;
            printx();
            xcls();
        } else if (index == 2) {
        	cls();
            cout << "����1 �ۼ�2600000" << "����2 �ۼ�1200000" << endl;
            cin >> q;
            if (q == 1) {
                if (money >= 2600000) {
                    cout << "����ɹ�" << endl;
                    money-=2600000;
                    house = 1;
                    saveGamenotip(filePath); 
                } else {
                    cout << "����ʧ�� ԭ��Ǯ����" << endl;
                }
            } else if (q == 2) {
                if (money >= 1200000) {
                    cout << "����ɹ�" << endl;
                    money-=1200000;
					house = 2;
					saveGamenotip(filePath); 
                } else {
                    cout << "����ʧ�� ԭ��Ǯ����" << endl;
                }
            }
            printx();
            xcls();
        } else if (index == 3) {
        	cls();
            if (gongzuo.empty()) {
                int q2;
                cout << "��ʲô������1.ҽ��2.����3.��ʦ4.��๤5.����Ա6.��ҵ����ҪǮ�ƴ��ڵ���100000��0.�˳�" << endl;
                cin >> q2;
                if (q2 == 1) {
                    gongzuo = "doctor";
                    saveGamenotip(filePath); 
                    printx();
					xcls();
                } else if (q2 == 2) {
                    gongzuo = "police";
                    saveGamenotip(filePath); 
                    printx();
					xcls();
                } else if (q2 == 3) {
                    gongzuo = "teacher";
                    saveGamenotip(filePath); 
                    printx();
					xcls();
                } else if (q2 == 4) {
                    gongzuo = "cleaner";
                    saveGamenotip(filePath); 
                    printx();
					xcls();
                } else if (q2 == 5) {
                    gongzuo = "cxy";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                } else if (q2 == 6 && money >= 100000) {
                    gongzuo = "cy";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                }else if (q2 == 0){
                	noop();
                	cls();
				}
            } else {
                int q2;
                cout << "��ʲô������1.ҽ��2.����3.��ʦ4.��๤5.����Ա6.��ҵ����ҪǮ�ƴ��ڵ���100000��0.�˳�" << endl;
                cin >> q2;
                if (q2 == 1) {
                    gongzuo = "doctor";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                } else if (q2 == 2) {
                    gongzuo = "police";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                } else if (q2 == 3) {
                    gongzuo = "teacher";
                    saveGamenotip(filePath); 
                    printx();
					xcls();
                } else if (q2 == 4) {
                    gongzuo = "cleaner";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                } else if (q2 == 5) {
                    gongzuo = "cxy";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                } else if (q2 == 6 && money >= 100000) {
                    gongzuo = "cy";
                    saveGamenotip(filePath);  
                    printx();
					xcls();
                }else if (q2 == 0){
                	noop();
                	cls();
				}
            }
            
        } else if (index == 4) {
        	cls();
            saveGame(filePath); 
        } else if (index == 5) {
            system("start ����.exe");
            createPassStringFile(filePath);
            cls();
        }else if(index==6){
        	cls();
        	string cache;
        	int q6;
        	cout<<"Ŀǰ����"<<username<<endl;
			cout<<"�ĳ�ʲô��"<<endl;
			cin>>cache;
			cout<<"ȷ����1.ȷ��2.ȡ��"<<endl;
			cin>>q6;
			if(q6==1){
				username=cache;
				cout<<"�����ɹ���";
				printx();
				xcls();
			}else if(q6==2){
				cache="";
				printx();
				xcls();
			}else{
				cout<<"?";
				printx();
				xcls();
			}
		}else if(index==7){
        	system("start ����.exe");
        	cls();
		}else if(index==8){
        	createPassStringFile(filePath);
        	system("start ����.exe");
        	cls();
		}else if(index==9){
        	createPassStringFile(filePath);
        	system("start �̵�.exe");
        	cls();
		}else if(index==10){
			stopFlag=true;;
        	cout << "��ӭ����" << endl;
            moneyThread.join();
            break;
		}else{
        	cout<<"����ɶ�����⣬���䣡"<<endl;
		}
    }
    return 0;
}
