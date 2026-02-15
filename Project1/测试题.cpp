#include<iostream>
using namespace std;
int main() {
	const int v1 = 3;
	const int v2 = 9;
	int T;
	cin >> T;
	int t;
	int s1 =0;
	int s2 = 0;
	int resttime=0;  //对于兔子，它并不是一直一个状态--跑步。
	int runtime=0;   //他的时间而是被分割为两类，跑步时间和休息时间。
	for (t = 1; t <= T; t++) {
		s1 += v1;  //乌龟每一秒都是在＋3的跑步中
		if (resttime != 0) {
			resttime--;
		}
		else {
			s2 += v2;
			runtime++;  //跑步状态在逼近临界时长10
			if (runtime ==10) {
				if (s2 > s1) {
					resttime = 30;
				}
				runtime = 0;  //无论是否执行上面的休息代码，都要这一part运行完把runtime重新初始化为0；
			}
		}

	}
	if (s1 > s2) {
		cout << "@_@" << ' ' << s1;
	}
	else if (s1 < s2) {
		cout << "^_^" << ' ' << s2;
	}
	else {
		cout << "-_-" << ' ' << s1;
	}
	
}

#include<iostream>
#include<string>
using namespace std;
int main() {
	string s;
	cin >> s;
	string word = "";
	bool flag = true;
	for (int i = 0; i < s.length(); i++) {
		char ch = s[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch - 'a' + 'A';
			word += ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			word += ch;
		}
		else {
			if (word != "") {
				if (flag) {
					cout << word;
					flag = false;
				}
				else {
					cout << ' ' << word;
				}
				word = "";
			}
		}
	}
	if (word != "") {
		if (flag) {
			cout << word;
		}
		else {
			cout << ' ' << word;
		}
	}
	return 0;
}

#include<iostream>
using namespace std;
int main() {
	int m;
	cin >> m;
	if (m < 1 || m>9) {
		cout << "WRONG";
		return 0;
	}
	int a[9][9], b[9][9], c[9][9];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cin >> b[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			c[i][j] = 0;
			for (int k = 0; k < m; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
			cout << c[i][j];
			if (j < m - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}
}

#include<iostream>
#include<string>
using namespace std;
int main() {
	int n;
	cin >> n;
	struct competent {
		string name;
		int score;
	}tab[100];
	for(int i=0;i<n;i++){
		cin >> tab[i].name;
		int score[7];
		for (int j = 0; j < 7; j++) {
			cin >> score[j];
		}
		int max = score[0];
		int min = score[0];
		int sum = score[0];
		for (int j = 1; j < 7; j++) {
			if (score[j] >max) {
				max = score[j];
			}
			if (score[j] < min) {
				min= score[j];
			}
			sum += score[j];
		}
		tab[i].score = sum - max - min;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (tab[j].score > tab[j - 1].score) {
				competent temp = tab[j];
				tab[j] = tab[j - 1];
				tab[j - 1] = temp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << tab[i].name << ' ' << tab[i].score << endl;
	}
	return 0;
