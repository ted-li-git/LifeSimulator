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
	 
    cout << "              人生模拟器" << endl;
    cout << "            powered by LJT" << endl;
    cout << "读取存档，请输入路径，没有存档请输入\"nosave\"：";
    cin >> filePath;
    string hd;
    int q;
    loadSaveFile(filePath);
    thread moneyThread(increaseMoneyPeriodically);
    cls();
    cout<<"你好，用户 "<<username<<" "<<endl;
    while (true) {
        cout << "1.检测当前状态" << endl;
        cout << "2.购房" << endl;
        cout << "3.找工作" << endl;
        cout << "4.存档" << endl;
        cout << "5.去工作" << endl;
        cout << "6.改名" << endl;
        cout << "7.关于" << endl;
        cout << "8.背包" << endl;
        cout << "9.商店" << endl;
        cout << "10.退出" << endl;
        cout << "输入字符来开始游戏" << endl;
        cin >> index;
        hd = house_detection(house);
        ReloadSaveFile(filePath);
        if (index == 1) {
        	ReloadSaveFile(filePath);
        	cls();
        	cout << "目前名字：" << username << endl;
            cout << "目前HP:" << hp << endl;
            cout << "目前钱财:" << money << endl;
            cout << "目前房子:" << hd << endl;
            cout << "目前工作:" << gongzuo << endl;
            cout << "目前工作等级:" << joblevel << endl;
            cout << "目前饱食度:" << bsd << " " << "目前口渴值:" << sfd << endl;
            printx();
            xcls();
        } else if (index == 2) {
        	cls();
            cout << "房子1 售价2600000" << "房子2 售价1200000" << endl;
            cin >> q;
            if (q == 1) {
                if (money >= 2600000) {
                    cout << "购买成功" << endl;
                    money-=2600000;
                    house = 1;
                    saveGamenotip(filePath); 
                } else {
                    cout << "购买失败 原因：钱不够" << endl;
                }
            } else if (q == 2) {
                if (money >= 1200000) {
                    cout << "购买成功" << endl;
                    money-=1200000;
					house = 2;
					saveGamenotip(filePath); 
                } else {
                    cout << "购买失败 原因：钱不够" << endl;
                }
            }
            printx();
            xcls();
        } else if (index == 3) {
        	cls();
            if (gongzuo.empty()) {
                int q2;
                cout << "找什么工作？1.医生2.警察3.教师4.清洁工5.程序员6.创业（需要钱财大于等于100000）0.退出" << endl;
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
                cout << "换什么工作？1.医生2.警察3.教师4.清洁工5.程序员6.创业（需要钱财大于等于100000）0.退出" << endl;
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
            system("start 工作.exe");
            createPassStringFile(filePath);
            cls();
        }else if(index==6){
        	cls();
        	string cache;
        	int q6;
        	cout<<"目前名字"<<username<<endl;
			cout<<"改成什么？"<<endl;
			cin>>cache;
			cout<<"确定？1.确定2.取消"<<endl;
			cin>>q6;
			if(q6==1){
				username=cache;
				cout<<"改名成功！";
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
        	system("start 关于.exe");
        	cls();
		}else if(index==8){
        	createPassStringFile(filePath);
        	system("start 背包.exe");
        	cls();
		}else if(index==9){
        	createPassStringFile(filePath);
        	system("start 商店.exe");
        	cls();
		}else if(index==10){
			stopFlag=true;;
        	cout << "欢迎再来" << endl;
            moneyThread.join();
            break;
		}else{
        	cout<<"这是啥子玩意，重输！"<<endl;
		}
    }
    return 0;
}
