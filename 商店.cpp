#include "head.h"
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
	string filePath;
	jieshoustring(filePath);
	loadSaveFile(filePath); 
	string m1="��ӭ����Opera�̵꣨����һ�������̵꣩";
	string line1="1.Noodles 2.hamburger 3.cake";
	string line2="4.apple 5.house-key 6.light"; 
	while(1){
		int q;
		te(m1,6,12);
		te(line1,6,12);
		te(line2,6,12);
		cout<<"������ѡ��"<<endl;
		cin>>q;
		if(q==1||q==2||q==3||q==4){
			int q2;
			cout<<"35Ԫ 1.ȷ��2.ȡ��"<<endl;
			cin>>q2;
			if(q2==1){
				money-=35;
				addItem("food");
				saveGamenotip(filePath);
				cls();
			}else{
				cout<<"��ȡ��"<<endl;
				noop();
				printx();
				xcls();
			}
		}else if(q==5){
			cout<<"��ͨ����ҳ��������"<<endl;
			printx();
			xcls();
		}else if(q==6){
			cout<<"���ɹ���"<<endl;
			printx();
			xcls();
		}else{
			cout<<"������Ʒ��ȴ�1.1.2�汾��"<<endl;
			printx();
			xcls();
		}
	}
	system("pause"); 
}
