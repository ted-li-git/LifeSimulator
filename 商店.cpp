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
	string m1="欢迎来到Opera商店（这是一个凉心商店）";
	string line1="1.Noodles 2.hamburger 3.cake";
	string line2="4.apple 5.house-key 6.light"; 
	while(1){
		int q;
		te(m1,6,12);
		te(line1,6,12);
		te(line2,6,12);
		cout<<"请输入选项"<<endl;
		cin>>q;
		if(q==1||q==2||q==3||q==4){
			int q2;
			cout<<"35元 1.确定2.取消"<<endl;
			cin>>q2;
			if(q2==1){
				money-=35;
				addItem("food");
				saveGamenotip(filePath);
				cls();
			}else{
				cout<<"已取消"<<endl;
				noop();
				printx();
				xcls();
			}
		}else if(q==5){
			cout<<"请通过主页购房购买"<<endl;
			printx();
			xcls();
		}else if(q==6){
			cout<<"不可购买"<<endl;
			printx();
			xcls();
		}else{
			cout<<"更多商品请等待1.1.2版本后"<<endl;
			printx();
			xcls();
		}
	}
	system("pause"); 
}
