#include <iostream>
#include <string>
using namespace std;
string num[10] = {"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
string wei[5] = {"","Shi","Bai","Qian","Wan"};
string s,ans;
string fourdigits(string s) {
	int len = s.length();
	bool flag = false;//false ǰ��û��0
	string v;
	for(int i = 0; i < len; i ++) {
		if(s[i] == '0') {
			if(!flag) flag = true;
		} else {
			if(!flag) { //ǰ��û��0����ǰ���ֲ���0
				v += num[s[i] - '0'] + " " + wei[len - i - 1] + " ";
			} else { //ǰ����0����ǰ���ֲ���0�����ǰ���0��Ȼ���������ǰ����
				v += num[0] + " ";
				v += num[s[i] - '0'] + " " + wei[len - i - 1] + " ";
			}
			flag = false;
		}
	}
	return v;
}

int main() {

	cin >> s;
	if(s[0] == '-') {
		cout << "Fu ";
		s = s.substr(1);
	}
	int len = s.length();
	if(len == 9) {
		ans += num[s[0] - '0'] + " Yi ";
		string tmp = fourdigits(s.substr(1,4));
		ans += tmp;
		if(tmp.length() != 0)  ans += "Wan ";
		ans += fourdigits(s.substr(5,4));
	} else if(len <= 8 && len > 4) {
		string tmp = fourdigits(s.substr(0,len - 4));
		ans = tmp;
		if(tmp.length() != 0) ans += "Wan ";
		ans += fourdigits(s.substr(len - 4));
	} else {
		ans += fourdigits(s);
	}
	if(ans.length() == 0) ans = "ling";
	while(ans.back() == ' ') ans.pop_back();
	int f = ans.find("  ");
	while(f != ans.npos) {
		ans.replace(f,2," ");
		f = ans.find("  ");
	}
	cout << ans << endl;
	return 0;
}

