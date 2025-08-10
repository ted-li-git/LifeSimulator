#include "head.h"
using namespace std;
void jieshoustring(string& data) {
    ifstream inFile("passstring.txt");
    if (inFile.is_open()) {
        getline(inFile, data);
        inFile.close();
        remove("passstring.txt");
    }else{
    	remove("passstring.txt");
	}
}
int main(){
	string data;
	jieshoustring(data); 
	loadSaveFile(data);
	if(gongzuo=="police"){
		int q2; 
		cout<<"上班啦！！！1.赖床2.去上班"<<endl;
		cin>>q2;
		if(q2==1){
			cout<<"你被开除了！"<<endl;
			gongzuo="no-gz";
			saveGamenotip(data);
			system("pause");
			return 0;
		}else if(q2==2){
			cout<<"报警人:oh 9-1-1 I'm in 23B,DirayStreet please help I"<<endl;
			cout<<"你会说：1.别说鸟语啊2.听不懂3.丨"<<endl;
			int q3;
			cin>>q3;
			if(q3==1){
				cout<<"你被开除了 原因：骂报警人"<<endl;
				gongzuo="no-gz";
				saveGamenotip(data); 
			}else if(q3==2){
				cout<<"获得10000马内赔偿并被\"请\"出了警察局"<<endl;
				money+=10000;
				gongzuo="no-gz";
				saveGamenotip(data); 
			}else{
				uniform_int_distribution<> dis(1, 100);
				int ri = dis(gen);
				cout<<"报警人：好的，本来我就是报假警的"<<endl;
				cout<<"获得1000000马内"<<endl;
				money+=1000000;
				joblevel += 15;
				saveGamenotip(data);
				if(ri >= 75){
					cout<<"紧急事件：XXX大公司CEO被行刺，虽未能成功，但影响很大，上司派你寻找行刺的人"<<endl;
					cout<<"1.去处理2.不处理"<<endl;
					int q5;
					cin >> q5;
					if(q5==1&&joblevel>=1){
						cout<<"处理成功！你获得了50joblevel，和20万钱"<<endl;
						joblevel += 50;
						money += 200000;
						saveGamenotip(data);
					}else{
						cout<<"你被上司降职了"<<endl;
						joblevel -= 100;
						saveGamenotip(data);
					}
				}else{
					cout<<"工作结束"<<endl;
					system("pause");
					return 0; 
				}
			}
		}
	}else{
		cout<<"更多职业工作剧情敬请期待1.1.0及以后版本..."<<endl;
	}
	system("pause");
	return 0;
}
