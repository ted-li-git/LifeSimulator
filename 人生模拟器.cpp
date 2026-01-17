#include "head.h"
using namespace std;
string index;
string filePath;

void createPassStringFile(const string& filePath) {
    ofstream outFile("passstring.txt");
    if (outFile.is_open()) {
        outFile << filePath << endl;
        outFile.close();
    }
}


int main() {
	changecolor("9");
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
    changecolor("E");
    while (true) {
    	cout << "注意：本版本（1.1.0alpha）为alpha测试版，拥有超多不知名bug和已知bug，遇到bug请理性反馈，谢谢" << endl; 
        cout << "dcs.检测当前状态" << endl;
        cout << "gh.购房" << endl;
        cout << "fw.找工作" << endl;
        cout << "save.存档" << endl;
        cout << "work.去工作" << endl;
        cout << "rn.改名" << endl;
        cout << "about.关于" << endl;
        cout << "bag.背包" << endl;
        cout << "shop.商店" << endl;
        cout << "phone.手机" << endl;
        cout << "exit.退出" << endl;
        cout << "输入字符来开始游戏" << endl;
        cin >> index;
        hd = house_detection(house);
        ReloadSaveFile(filePath);
        if (index == "dcs") {
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
        } else if (index == "gh") {
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
        } else if (index == "fw") {
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
            
        } else if (index == "save") {
        	cls();
        	cout<<"存档后将会覆盖原存档，是否继续？继续y停止n"<<endl;
			char q;
			cin>>q;
			if(q=='y'){
				saveGame(filePath); 
				printx();
				xcls();
			}else if(q=='n'){
				cout<<"已取消"<<endl;
				printx();
				xcls();
			}else{
				cout<<"已自动取消"<<endl;
				printx();
				xcls();
			}
            
        } else if (index == "work") {
            system("start 工作.exe");
            createPassStringFile(filePath);
            cls();
        }else if(index=="rn"){
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
		}else if(index=="about"){
        	system("start 关于.exe");
        	cls();
		}else if(index=="bag"){
        	createPassStringFile(filePath);
        	system("start 背包.exe");
        	cls();
		}else if(index=="shop"){
        	createPassStringFile(filePath);
        	system("start 商店.exe");
        	cls();
		}else if(index=="phone"){
			system("start 手机.exe");
			cls();
		}else if(index=="exit"){
			stopFlag=true;
        	cout << "欢迎再来" << endl;
            moneyThread.join();
            break;
		}else{
        	cout<<"这是啥子玩意，重输！"<<endl;
		}
    }
    return 0;
}
