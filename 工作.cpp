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
		cout<<"�ϰ���������1.����2.ȥ�ϰ�"<<endl;
		cin>>q2;
		if(q2==1){
			cout<<"�㱻�����ˣ�"<<endl;
			gongzuo="no-gz";
			saveGamenotip(data);
			system("pause");
			return 0;
		}else if(q2==2){
			cout<<"������:oh 9-1-1 I'm in 23B,DirayStreet please help I"<<endl;
			cout<<"���˵��1.��˵���ﰡ2.������3.ح"<<endl;
			int q3;
			cin>>q3;
			if(q3==1){
				cout<<"�㱻������ ԭ�������"<<endl;
				gongzuo="no-gz";
				saveGamenotip(data); 
			}else if(q3==2){
				cout<<"���10000�����⳥����\"��\"���˾����"<<endl;
				money+=10000;
				gongzuo="no-gz";
				saveGamenotip(data); 
			}else{
				uniform_int_distribution<> dis(1, 100);
				int ri = dis(gen);
				cout<<"�����ˣ��õģ������Ҿ��Ǳ��پ���"<<endl;
				cout<<"���1000000����"<<endl;
				money+=1000000;
				joblevel += 15;
				saveGamenotip(data);
				if(ri >= 75){
					cout<<"�����¼���XXX��˾CEO���д̣���δ�ܳɹ�����Ӱ��ܴ���˾����Ѱ���д̵���"<<endl;
					cout<<"1.ȥ����2.������"<<endl;
					int q5;
					cin >> q5;
					if(q5==1&&joblevel>=1){
						cout<<"����ɹ���������50joblevel����20��Ǯ"<<endl;
						joblevel += 50;
						money += 200000;
						saveGamenotip(data);
					}else{
						cout<<"�㱻��˾��ְ��"<<endl;
						joblevel -= 100;
						saveGamenotip(data);
					}
				}else{
					cout<<"��������"<<endl;
					system("pause");
					return 0; 
				}
			}
		}
	}else{
		cout<<"����ְҵ�������龴���ڴ�1.1.0���Ժ�汾..."<<endl;
	}
	system("pause");
	return 0;
}
