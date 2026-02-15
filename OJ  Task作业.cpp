#include<iostream>
#include<string>
using namespace std;
void task1() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {  //对于每一行，都新定义一个字符串，操作M，和n。这样避免存储所有大量数据
		string s;
		char M;
		int n;
		cin >> s >> M >> n;
		int len = s.length(); //定义len变量，方便后续用到总长度计算
		string s2;  //新字符串。没有初始化，程序会自动默认为空字符串（数组）
		int actn = n % len; //！！！当n>len时，依次旋转len个，会回到原样。故取余可以确保真正有效的移动位数。
		if (M == 'L') {  //数组中应该是旋转0到n-1位
			for (int j = actn; j < len; j++) {
				s2 += s[j];
			}
			for (int j = 0; j < actn; j++) {
				s2 += s[j];
			}
		}
		else if (M == 'R') {
			for (int j = len - actn; j < len; j++) {
				s2 += s[j];
			}
			for(int j=0;j<len-actn;j++){
				s2 += s[j];
			}
		}
		else {
			s2 = s;
		}
		for (int j = 0; j < s2.length(); j += 2) {
			cout << s2[j];
		}
		cout << endl;
	}
}


#include <iostream>
#include <string>
using namespace std;

// 定义学生结构体
struct Student {
	string id;      // 学号
	string name;    // 姓名
	double math;    // 数学成绩
	double chinese; // 语文成绩
	double english; // 英语成绩
};

int main() {
	int N;
	cin >> N;

	Student students[100]; // 最多100名学生

	// 输入学生信息
	for (int i = 0; i < N; i++) {
		cin >> students[i].id >> students[i].name
			>> students[i].math >> students[i].chinese >> students[i].english;
	}

	int sortType;
	cin >> sortType;

	// 检查排名依据是否有效
	if (sortType < 1 || sortType > 3) {
		cout << "ERROR" << endl;
		return 0;
	}

	// 冒泡排序（直接读取结构体中的成绩进行比较）
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			bool flag = false;

			// 1. 根据 sortType 获取两名学生当前科目的分数
			double s1, s2;

			if (sortType == 1) { // 数学
				s1 = students[j].math;
				s2 = students[j + 1].math;
			}
			else if (sortType == 2) { // 语文
				s1 = students[j].chinese;
				s2 = students[j + 1].chinese;
			}
			else { // 英语
				s1 = students[j].english;
				s2 = students[j + 1].english;
			}

			// 2. 比较分数（从高到低）
			if (s1 < s2) {
				flag = true;
			}
			// 3. 成绩相同，按学号从小到大（字典序）
			else if (s1 == s2) {
				if (students[j].id > students[j + 1].id) {
					flag = true;
				}
			}

			// 4. 执行交换
			if (flag) {
				// 直接交换整个结构体，所有信息（学号、姓名、各科成绩）都会同步交换
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}

	// 输出排序后的学生学号和姓名
	for (int i = 0; i < N; i++) {
		cout << students[i].id << " " << students[i].name << endl;
	}

	return 0;
}

void task2() {
	int N;
	cin >> N;
	
	string id[100];
	string name[100];
	double math[100];
	double chinese[100];
	double english[100];

	for (int i = 0; i < N; i++) {
		cin >> id[i] >> name[i] >> math[i] >> chinese[i] >> english[i];
	}
	int sortType;
	cin >> sortType;
	double a[100];
	
	switch(sortType){
	case 1:
		for (int i = 0; i < N; i++) {
			a[i] = math[i];
		}
		break;
	case 2:
		for (int i = 0; i < N; i++) {
			a[i] = chinese[i];
		}
		break;
	case 3:
		for (int i = 0; i < N; i++) {
			a[i] = english[i];
		}
		break;
	default:
		cout << "ERROR" << endl;
		return 0;
	}
	for (int i = 0; i < N - 1; i++) {
		bool flag = false;
		for (int j = N - 2; j >= i; j--) {
			if (a[j] < a[j + 1]) {
				flag = true;
			}
			else if (a[j] == a[j + 1]) {
				if (id[j] > id[j + 1]) {
					flag = true;
				}
			}
			if (flag) {
				string id_temp = id[j];
				id[j] = id[j + 1];
				id[j + 1] = id_temp;

				string name_temp = name[j];
				name[j] = name[j + 1];
				name[j + 1] = name_temp;

				double score_temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = score_temp;
			}
		}
	}
	for (int j = 0; j < N; j++)
		cout << id[j] << ' ' << name[j] << endl;
}

void task3() {
	int M, N;
	cin >> M >> N;
	int a[100],  b[100],  merged[200];
	for (int i = 0; i < M; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> b[i];
	}
	int total = M + N;
	for (int i = 0; i < M; i++) {
		merged[i] = a[i];
	}
	for (int i = 0; i < N; i++) {
		merged[M + i] = b[i];
	}
	for (int i = 0; i < M + N - 1; i++) {
		for (int j = M + N - 1; j > i; j--) {
			if (merged[j - 1] > merged[j]) {
				int temp = merged[j - 1];
				merged[j - 1] = merged[j];
				merged[j] = temp;
			}
		}
	}
	cout << merged[0];
	for (int i = 0; i < total- 1; i++) {
		if (merged[i] != merged[i + 1]) {
			cout <<' '<< merged[i + 1];
		}
	}
}
void task4() {
	int m, n;
	cin >> m >> n;
	int arr[10][10];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < n; j++) {
				cout << arr[i][j];
				if (!(i == m - 1 && j == n - 1)) {
					cout << ' ';
				}
			}
		}
		else {
			for (int j = n - 1; j >= 0; j--) {
				cout << arr[i][j];
				if (!(i == m - 1 && j == 0)) {
					cout << ' ';
				}
			}
		}
	}
	cout << endl;
	int top = 0, bottom = m - 1, left = 0, right = n - 1;
	int count = 0;
	int total = m * n;
	while (count < total) { //注意不可加等号，否则当 count=total时，下面条件都不成立。则count永远不会加一，那么永远处于=状态，无限死循环
		for (int j = left; j <= right && count < total; j++) {
			cout << arr[top][j];
			count++;
			if (count < total) {
				cout << ' ';
			}
		}
		top++;
		for (int i = top; i <= bottom && count<total; i++) {
			cout << arr[i][right];
			count++;
			if (count < total) {
				cout << ' ';
			}
		}
		right--;
		for (int j = right; j >= left && count < total; j--) {
			cout << arr[bottom][j];
			count++;
			if (count < total) {
				cout << ' ';
			}
		}
		bottom--;
		for (int i = bottom; i >= top && count < total; i--) {
			cout << arr[i][left];
			count++;
			if (count < total) {
				cout << ' ';
			}
		}
		left++;
	}
}
 #include<iostream>
 using namespace std;
bool isprime(int num) {
	if (num <= 1) {
		return false;
	}
	else if (num == 2) {
		return true;
	}
	else {
		for (int i = 2; i * i <= num; i++) {
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}
}
int main() {
	int N;
	cin >> N;
	if (N <= 0 || N > 10000) {
		cout << "INCORRECT INPUT!";
		return 0;
	}
	for (int i = 0; i < N; i++) {
		int M;
		cin >> M;
		if (M <= 0 || M >= 1000000) {
			cout << "INCORRECT INPUT!";
			return 0;
		}
		if (isprime(M)) {
			cout << M << ' ' << 0 << endl;
			continue;
		}
		int leftnum;
		int left_distance = 1000000;
		for (int left = M - 1; left >= 2; left--) {
			if (isprime(left)) {
				leftnum = left;
				left_distance = M - left;
				break;
			}
		}
		int rightnum;
		int right_distance = 1000000;
		for (int right = M + 1; right < 1000000; right++) {
			if (isprime(right)) {
				rightnum = right;
				right_distance = right - M;
				break;
			}
		}
		if (left_distance <= right_distance) {
			cout << leftnum << ' ' << left_distance << endl;
		}
		else {
			cout << rightnum << ' ' << right_distance << endl;
		}
	}
	return 0;
}

#include <iostream>
#include<cmath>
#include<cstring>
using namespace std;
void OddFilter(int a[], int length) {
	int result[1000];
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (a[i] % 2 != 0) {
			result[count] = a[i];
			count++;
		}
	}
	if (count == 0) {
		cout << "No Odd!" << endl;
	}
	else {
		for (int i = 0; i < count - 1; i++) {
			for (int j = count - 1; j > i; j--) {
				if(result[j-1]>result[j]){
					int temp = result[j - 1];
					result[j - 1] = result[j];
					result[j] = temp;
				}
			}
		}
		for (int i = 0; i < count; i++) {
			if (i > 0) {
				cout << ' ';
			}
			cout << result[i];
		}
		cout << endl;
	}
}
void OddFilter(double a[], int length) {
	int result[1000];
	int count = 0;
	for (int i = 0; i < length; i++) {
		int num = int(a[i] + 0.5);
		if (num % 2 != 0) {
			result[count] = num;
			count++;
		}
	}
	if (count == 0) {
		cout << "No Odd!" << endl;
	}
	else {
		for (int i = 0; i < count - 1; i++) {
			for (int j = count - 1; j > i; j--) {
				if (result[j - 1] > result[j]) {
					int temp = result[j - 1];
					result[j - 1] = result[j];
					result[j] = temp;
				}
			}
		}
		for (int i = 0; i < count; i++) {
			if (i > 0) {
				cout << ' ';
			}
			cout << result[i];
		}
		cout << endl;
	}
}
void OddFilter(char a[],int length) {
	int frequency[256] = { 0 };
	char result[1000];
	int count = 0;
	for (int i = 0; i < length; i++) {
		frequency[unsigned char(a[i])]++;
	}
	for (int i = 0; i < 256; i++) {
		if (frequency[i] % 2 != 0) {
			result[count] = char(i);
			count++;
		}
	}
	if (count == 0) {
		cout << "No Odd!" << endl;
	}
	else {
		for (int i = 0; i < count - 1; i++) {
			for (int j = count - 1; j > i; j--) {
				if (result[j - 1] > result[j]) {
					char temp = result[j - 1];
					result[j - 1] = result[j];
					result[j] = temp;
				}
			}
		}
		for (int i = 0; i < count; i++) {
			if (i > 0) {
				cout << ' ';
			}
			cout << result[i];
		}
		cout << endl;
	}
}
int main() {
	int M, N;
	cin >> M >> N;
	int intarray[1000];
	for (int i = 0; i < M; i++) {
		cin >> intarray[i];
	}
	double doublearray[1000];
	for (int i = 0; i < N; i++) {
		cin >> doublearray[i];
	}
	char str[1000];
	cin >> str;
	int len = static_cast<int>(strlen(str));
	OddFilter(intarray, M);
	OddFilter(doublearray, N);
	OddFilter(str, len);
	return 0;
}
//字符串和字符数组的区别（是否含有串尾符/0）
//char a1[6]="AB"; 字符串输入，末尾隐含有/0
//char a2[6];
//a2[0]='A';  a2[1]='B';
//这时输出两个数组，由于字符串末尾隐含/0表明结束，所以只会输出AB。但是第二个由于后四个位无定义，所以可能输出乱码。
//当是全局变量时，即写在任何代码块和函数外部，系统才会默认初始化为 0，/0(字符），{0}（数组）
//若是部分变量，必须初始化