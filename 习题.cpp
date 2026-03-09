#include <iostream>
#include <iomanip>  //调整精确度
#include <cmath>  //包含数学运算符
#include <climits>   //定义了各种有整型的极限值，对于插char,int,long,long long
using namespace std;
void task1() {
	int s;
	cin >> s;
	double s_2 = s * 0.9 - 500;
	cout << fixed << setprecision(2) << s_2 << endl;
}
void task2() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a + b > c && a + c > b && b + c > a) {
		double p = (a + b + c);       //注意把p的数据类型设置为浮点数！避免整数除法得到整数，截断了小数位
		double s = p / 2;		//小数除以整数可打破整除，得到浮点数。但若没设置得到了整数，会隐式转换为规定的s类型即double，只是值不对
		double area = sqrt(s * (s - a) * (s - b) * (s - c));
		cout << fixed << setprecision(3) << p << " " << area << endl;
	}
	else
		cout << "Error" << endl;
}
void task3() {
	int n;
	cin >> n;
	int 
}

void task1() {
	int n;
	cin >> n;
	int arr[100]; //定义一个长度(必须为定值！）为100的数组，意味着最多可放100个整数；注意，数组里面变量类型必须唯一。
	for (int i = 0; i < n; i++)
		cin >> arr[i];  //输入所用的n个变量放入数组中；
	int max_score = arr[0];  //时刻注意初始化
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > max_score)
			max_score = arr[i]; //更新最大值
	}
	cout << max_score;
}
void task2() {
	int n;
	cin >> n;
	int arr[100];
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	double average = sum / n;
	cout << sum << " " << average;
}

	/*for (int i = n-1 ; i >=0; i--)
		cout << " "<<arr[i];*/    //变式:逆向输出n个数

void task3()  //如何寻找到数组中第二大的数
{
	int n;
	cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	int max1 = INT_MIN;   //这个值肯定最小，确保数组中任何元素均可大于它，从而一定可以更新掉这个值
	int max2 = INT_MIN;  //指的是对于整数最小的可能值，int为32位，所以其值为-2*31.
	for (int i = 0; i < n; i++) {  //遍历其中每一个值，有如下两种情况会替换max2
		if (arr[i] > max1) {
			max2 = max1;
			max1 = arr[i];   //第一个是它大于max1，则原来的max1充当现在max2，同时记得更改max1
		}
		else if (arr[i > max2 && arr[i] < max1]) {
			max2 = arr[i];  //第二个是它仅仅大于max2，则只更换max2
		}                 //当它小于max2时，啥也不动
	}				//注意，for的{}里放的是循环操作，所以cout在外面！
	cout << max2 << endl;
}

void task4() {    //判断数组中是否有重复数字
	int n;
	cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}						//以下为嵌套循环来比较
	bool flag = false;  //初始化flag值为false
	for (int i = 0; i < n && !flag; i++) //此处&&为取交集，第二块代表继续（而非停止）条件（没找到重复时，为true&&true=true，可执行，找到后，！flag变为false，&&所得为false，停止循环	
	{										//这里引入！flag是为了可以提前终止，跳出对于i的外层循环
		for (int j = i + 1; j < n; j++) {  //这里j不用从0开始，因为若i前面的数有与第i个相等的，已经在i取那个小值时发现并停下了！
			if (arr[i] = arr[j]) {			//若用j从0开始，还需抠除掉i=j这一个点
				flag = true;   //更改！flag为false
				break;    // 用break跳出对j的内部循环
			}
		}
	}
	if (flag) {  //布尔值本身就可当条件语句使用。除此之外，只输入整型也可做条件，因为非零转换为true，零转换为false
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
}

void task5() {		//求凸多边形对角线交点个数    已知任何三条对角线都不会交于一点（故寻找两条交于一起的）
	//从低阶开始，根据三角形无对角线，四边形两条对角线产生一个交点，故寻找四边形个数 C n 4
	unsigned long long n;		//为了使得n边型尽可能都包含，n取最大限度的整数
	cin >> n;
	if (n < 4) {
		cout << 0;
	}
	else
	{
		cout << n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4 << endl;
	}          // 不把1234放在最后除是因为，可能虽然所输入的n本身没有超过范围，但前几个含n的数相乘会超过unsigned long long
			  //故把他们分散开来确保每一步的缩小：两相邻数必有一个为偶数，三个相邻必有一个是3的倍数，同理最后会余下含4的因子
}				//故此题考察数字溢出

void task6() {			//数字翻转，如123.4变成4.321
	float num;
	cin >> num;
	int num_2=num*10;
	int num_3;
	int flag = 0;
	while (num_2 > 0) {
		if (flag == 1) {
			cout << ".";
		}
		num_3 = num_2 % 10;
		cout << num_3;
		num_2 /= 10;
		flag++;
	}
}
void task62() {  //数字翻转，且只保留三位


}

void task7() {
	int s, v;
	cin >> s >> v;				//若只+v,那么若s可以整除v，又多加了一个1！考虑到所有不可整除数都>=kv+1.则只需＋(v-1),就会>=k+1倍
	int time_walk = (s + v - 1) / v;  //向上取整，确保小数时间按整数计入路途时长，而不被整除抹掉；
//cmath库里有取整函数 ceil向上取整，floor向下取整。若ceil（s/v)会报错，因为s/v是整型了，而ceil针对的是小数，所以把一个定义换成小数即可
	int time_total = time_walk + 10;							//或者可以ceil(double(s)/v)  用类型转换
	int start_time = 8 * 60 - time_total;
	if (start_time < 0) {
		start_time += 24 * 60;
	}
	int hour = start_time / 60;
	int minutes = start_time % 60;
	cout << setw(2) << setfill('0') << hour << ":";
	cout << setw(2) << setfill('0') << minutes << endl;  //setw是补足几位输出，是右对齐。所以往前补0对齐。注意默认空格补齐，故要规定用字符‘0
}								
void task8() {
	int num;
	cin >> num;
	bool prop1 = (num % 2 == 0);	//先把这两个条件赋值给布尔值。因为逻辑运算符两边 应该是结果为逻辑值的表达式
	bool prop2 = (num > 4 && num <= 12);  //这两个已经变成true ，false即1，0.方便下面1&&1，1||0判断
	bool a = prop1 && prop2;
	bool b = prop1||prop2;
	bool c = (prop1 && !prop2) || (!prop1 && prop2);
	bool d = !prop1 && !prop2;
	cout << a << b << c << d << endl;
}

void task9() {
	int x;
	cin >> x;
	if (x == 0 || x == 1) {
		cout << "Today,I ate" << x << "apple.";
	}
	else {
		cout << "Today,I ate" << x << "apples.";
	}

}
void task10() {
	int a, b, c;
	cin >> a >> b >> c;
	if (a > b) {     //若a大于b，交换两数，使a最小
		int temp = a;
		a = b;
		b = temp;
	}
	if (a> c) {   //若a大于c，交换两数，使a最小
		int temp = a;
		a = c;
		c = temp;
	}
	if (b> c) {   //此时a最小，比较b，c，可能交换两者，使b小于c
		int temp = b;
		b = c;
		c = temp;
	}
	cout << a << " " << b << " " << c;//从而顺序输出
}

void task11() {
	int n;
	cin >> n;
	if (5 * n > 3 * n + 11) {
		cout << "Luogu";
	}
	else {
		cout << "Local";
	}
}
void task12() {
	double m, h;
	cin >> m >> h;
	double BMI = m / h / h;
	if (BMI < 18.5) {
		cout << "Underweight" << endl;
	}
	else if (BMI < 24) {
		cout << "Normal" << endl;
	}
	else {
		cout << setprecision(6) << BMI << endl;
		cout << "Overweight" << endl;
	}
}
void task13() {
	double cost=0;
	int i;
	cin >> i;
	int c = i / 50;
	switch (c) {
	default:
		cost += (i - 400) * 0.5663; i = 400;
	case 3:case 4:case 5:case 6:case 7:case 8:
		cost += (i - 150) * 0.4663; i = 150;
	case 1:case 2:case 0:
		cost += i * 0.4463;
		cout << fixed<<setprecision(1)<<cost;
	}
}
void task14() {
	int school, extra;
	int max = 0;
	int unhappy = 0;
	for (int day = 1; day <= 7; day++) {
		cin >> school >>extra;
		int total = school + extra;
		if (total > 8 && total > max) {
			max = total;
			unhappy = day;
		}
	}
	cout << unhappy << endl;
}
void task15() {
	int n;
	cin >> n;
	int min_cost = 100000000;
	for (int choice = 0; choice < 3; choice++) {
		int count, price;
		cin >> count >> price;
		int package = ceil(double(n) / count);
		int total_cost = package * price;
		if (total_cost < min_cost) {
			min_cost = total_cost;
		}
	}
	cout << min_cost << endl;
}
void task16() {
	int x, n;
	cin >> x >> n;
	int total = 0;
	for (int i = 0; i < n; i++) {
		if (x != 6 && x != 7) {
			total += 250;
		}
		x++;
		if (x > 7) {
			x = 1;
		}
	}
	cout << total << endl;
}
void task17() {
	int n, k;
	int countA, countB;
	double sumA, sumB;
	for (int i = 1; i <= n; i++) {
		if (i % k == 0) {
			countA++;
			sumA += i;
		}
		else {
			countB++;
			sumB += i;
		}
	}
		double averageA = sumA / countA;
		double averageB = sumB / countB;
		cout << fixed << setprecision(1) << averageA << ' ' << averageB;
	
}

void task18() {
	int N;
	cin >> N;
	int maxdays = 1;
	int currentdays = 1;
	int prevTemp, currentTemp;
	cin >> prevTemp;
	for (int i = 1; i < N; i++) {
		cin >> currentTemp;
		if (currentTemp > prevTemp) {
			currentdays++;
			if (currentdays > maxdays) {
				maxdays = currentdays;
			}
		}
		else {
			currentdays = 1;  //注意重置连续上升天数，之前作废，回到1！！！
		}
		prevTemp = currentTemp;  //每一次循环后更新previous temperature，以确保下一个与新的上一个比较。
	}
	cout << maxdays << endl;
}

void task19() {
	int n;
	cin >> n;
	int totalunhappy = 0;
	int prevunhappy = 0;
	for (int i = 0; i < n; i++) {
		int school, extra;
		cin >> school >> extra;
		int today_hours = school + extra;
		int todayunhappy = today_hours + prevunhappy - 8;
		totalunhappy += todayunhappy;
		prevunhappy = todayunhappy;
	}
	cout << totalunhappy << endl;
}

void task20() {
	int n, x;
	cin >> n >> x;
	int count;
	for (int i = 1; i <= n; i++) {
		int num = i;
		while (num > 0) {
			int digt = num % 10;
			if (digt == x) {
				count++;
			}
			num = num / 10;
		}
	}
	cout << count;

}
void task21() {
	int L;
	cin >> L;
	int sum = 0;
	int count = 0;
	for (int i = 2; ; i++) {
		bool flag = true;
		for (int j = 2; j <= sqrt(i); j++) {
			if (i % j == 0) {
				break;
				flag = false;
			}
		}
		if (flag && sum + i <= L) {
			cout << i;
			sum += i;
			count++;
		}
		else if (sum + i > L) {
			break;
		}
	}
	cout << count << endl;
}

void task22() {
	int n;
	cin >> n;
	int num = 1;
	for (int i = n; i > 0; i--) {
		for (int j = 1; j <= i; j++) {
			cout << setw(2) << setfill('0') << num;
			num++;
		}
		cout << endl;
	}
}

#include<iostream>
using namespace std;
int main() {
	long int l;
	int m;
	cin >> l >> m;
	int u[100];
	int v[100];
	cin >> u[0] >> v[0];
	int sum = v[0] - u[0] + 1;
	for (int i = 1; i < m; i++) {
		cin >> u[i] >> v[i];
		int s;
		if (u[i] <= v[i-1]&&v[i-1]<=v[i]) {
			s = v[i-1]-u[i] + 1;
		}
		else if (u[i] <= u[i - 1] && u[i - 1] <= v[i]) {
			s = v[i] - u[i - 1] + 1;
		}
		else {
			s = 0;
		}
		sum += v[i] - u[i] +1- s;
	}
	long int left = l - sum;
	cout << left;
}// 有问题！修改见Gemini 2种方法
 //如下修改 移走树木问题（练习六）
void task24() {
	int l, m;
	cin >> l >> m;
	int tree[10005];  //用一个数组来存储树木状态，只有存好了后期才可修改
	for (int i = 0; i <= l;i++) {
		tree[i] = 1;
	}
	for (int i = 0; i < m; i++) {  
		int u, v;
		cin >> u >> v; // 每一个区间内再定义u,v，不用存储这俩数，减少数据库压力
		for (int j = u; j <= v; j++) {
			tree[j] = 0; // 这样子如果！前面已经修改为0了，再多次赋值为0也okay，解决了重叠问题
		}        //相当于区间内树直接砍掉！以后便不会重复计数了
	}
	int count = 0;
	for (int i = 0; i <= l; i++) {
		if (tree[i] == 1) {
			count++;  // 最后遍历所有树木状态，仍然是1说明没被砍，count+1即可
		}
	}
	cout << count << endl;
}
//第二种！普适方法！对于L非常大，再一个个存储树木状态就占很大内存
//但L长，所建地铁的区段数量不会多。即M不会很大！
//之前我们问题在于，只跟前一个比较。但如果是第三个和第一个也有重叠，但和第二个无重叠，就把第三个全盘计入，计多了，错了
//解决方案是：！把数组按照起点先后顺序排好序！这样只需要跟前一个比较也不会有误。这样是最万能方法！

struct interval {
		int left;
		int right;
};
int main(){
	int l, m;
	cin >> l >> m;
	interval a[110];
	for (int i = 0; i < m; i++) {
		cin >> a[i].left >> a[i].right;
	} //这里不再是每一个区间用完即消失，他用一个110长度的结构体数组将每一个u,v都存储了，以便于比较排序
	for (int i = 0; i < m - 1; i++) {
		for (int j = m - 1; j > i; j--) {
			if (a[j].left < a[j - 1].left) {
				interval temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
			}
		}
	}
	int removesum = 0;
	int leftnow = a[0].left;
	int rightnow = a[0].right;
	for (int i = 1; i < m; i++) {
		if (a[i].left <= rightnow) {
			if (a[i].right > rightnow) {
				rightnow = a[i].right;
			} //有重叠，取最大作为右端点，左端点肯定第一个最小不用变
		}
		else {
			removesum += (rightnow - leftnow + 1);// 若断开了，先把前面那个大区间结算了
			leftnow = a[i].left;
			rightnow = a[i].right; //再更新新的左右端点，从头开始
		}  
	}
	//循环完后，手里还剩了一个断开余下的或者之前合并的大区间没有计入sum中
	removesum += (rightnow - leftnow + 1);
	cout << l + 1 - removesum << endl;
}

//杨辉三角
void task25() {
	int n;
	cin >> n;
	long long a[20][20];
	for (int i = 0; i < n; i++) {
		a[i][0] = 1;
		a[i][i] = 1;
		for (int j = 1; j < i; j++) {
			a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) { //注意i和j都是从0开始，每行最后列数等于行数，所以最终结尾一定是i=j=n-1.故记得加等号
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}
void task26() {
	int n;
	cin >> n;
	int t = 0;
	int a[10000];
	a[0] = n;
	while (n != 1) {
		if (n % 2 == 1) {
			n = n * 3 + 1;
		}
		else {
			n /= 2;
		}
		t++;
		a[t] = n;
	}
	for (int i = t; i >= 0; i--) {
		cout << a[i] << ' ';
	}
}

const int maxindex = 2000005; //a*t上限说明了灯的数量上限，而灯状态只有两种，所以用bool更方便
bool lights[maxindex]; //将数组定义在main函数外，全局变量。不仅可以自动初始化为0（false），而且空间更大，不会超限报错
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		double a;
		int t;
		for (int j = 1; j <= t; j++) {
			int index = (int)(a * j);
			lights[index] = !lights[index];
		}
	}
	for (int i = 0; i < maxindex; i++) {
		if (lights[i] == true) {
			cout << i << endl;
			break; // 由于已知只有一盏灯是亮的，所以找到后可以直接退出！节省时间
		}
	}
}
#include<iostream>
using namespace std;
int digit(int n,int k) {
	for (int i = 1; i < k; i++) {
		n /= 10;
	}
	return n % 10;
}
int main() {
	int n, k;
	cin >> n >> k;
	cout << digit(n, k) << endl;
}
#include<iostream>
using namespace std;
int n;
char arr[15];
void deep(int num) {
	if (num > n) {
		for (int i = 1; i <=n; i++) {
			cout << arr[i];
		}
		cout << endl;
		return;
	}
	arr[num] = 'N';
	deep(num + 1);
	arr[num] = 'Y';
	deep(num + 1);
}
int main() {
	cin >> n;
	deep(1);
	return 0;
}
#include<iostream>
using namespace std;
int n, k;
int path[15];
bool used[15];
void deep(int num) {
	if (num > k) {
		for (int i = 1; i <= k; i++) {
			cout << path[i] <<' ';
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (used[i] == false) {
			path[num] = i;
			used[i] = true;
			deep(num+1);
			used[i] = false;//!这里重新归为false，是为了给以后上一层再调用可用做准备！
		}
	}//而并不影响此处循环，因为花括号后自动i++，进入了下一个，不会重复取用上面这个值。故最后取到n终结此层所有循环，到下一个花括号
} //此处括号代表该层彻底结束销毁，退栈区，进入上一层冻结页面接着往下运行，上一层把刚用过的数先释放，然后顺位往下面接着去
   //从而实现了先把最后一位遍历，再倒着把前面几位也遍历。
int main() {
	cin >> n >> k;
	deep(1);
	return 0;
}

#include<iostream>
using namespace std;
int mono[1005];
int approach(int n) {
	if (mono[n] != 0) {
		return mono[n];
	}
	int count = 1;
	for (int i = 1; i <= (n / 2); i++) {
		count += approach(i);
	}
	return mono[n]=count;
}
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < 1000; i++) {
		mono[i] = 0;
	}
	cout << approach(n) << endl;
}
#include<iostream>
using namespace std;
struct complex {
	int real;
	int imag;
};
complex operator+(const complex& a, const complex& b) {
	complex res;
	res.real = a.real + b.real;
	res.imag = a.imag + b.imag;
	return res;
}
complex operator-(const complex& a, const complex& b) {
	complex res;
	res.real = a.real - b.real;
	res.imag = a.imag - b.imag;
	return res;
}
complex operator*(const complex& a, const complex& b) {
	complex res;
	res.real = a.real * b.real - a.imag * b.imag;
	res.imag = a.real * b.imag + a.imag * b.real;
	return res;
}
void printcomplex(const complex&c) {
	cout << c.real;
	if (c.imag > 0) {
		cout << '+' << c.imag << 'i';
	}
	else if (c.imag < 0) {
		cout << c.imag << 'i';
	}
	//else(c.imag==0) 什么都不输出
	cout << endl;
}

int main() {
	int r1, i1, r2, i2;
	cin >> r1 >> i1 >> r2 >> i2;
	complex c1 = { r1,i1 };
	complex c2 = { r2,i2 };
	printcomplex(c1 + c2);
	printcomplex(c1 - c2);
	printcomplex(c1 * c2);
	return 0;
}
#include<iostream>
#include<cstring>
using namespace std;
bool isprime(int n) {
	if (n < 2)
		return false;// 注意，0,1不是质数，质数是指他的因子只有1和自己，2是最小的质数；
	else if(n == 2)
		return true;
	else {
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0)
				return false;
		}
		return true;
	}
}
int main() {
	string s;
	cin >> s;
	int count[26] = { 0 };//数26个字母出现次数
	for (int i = 0; i < s.length(); i++) {
		count[s[i] - 'a']++;
	}

	int minn = 100;
	int maxn = 0;
	for (int i = 0; i < 26; i++) {
		if (count[i] == 0)
			continue;
		if (count[i] < minn)
			minn = count[i];
		if (count[i] > maxn)
			maxn = count[i];

	}
	int diff = maxn - minn;
	if (isprime(diff)) {
		cout << "Lucky Word" << endl;
		cout << diff << endl;
	}
	else {
		cout << "No Answer" << endl;
		cout << 0 << endl;
	}
	return 0;
}
#include <iostream>
#include <cstring>

using namespace std;

int main() {
	
	int q;
	cin >> q; // 输入操作次数

	string doc;
	cin >> doc; // 输入初始文档字符串

	while (q--) {//当操作次数非零时，转化成true，可以执行下面操作
		int type;
		cin >> type; // 输入操作类型

		if (type == 1) {
			string str;
			cin >> str;
			doc += str; // 1. 追加
			cout << doc << endl;

		}     //注意每次操作是递推影响的，所以注意更新改变字符串。
		else if (type == 2) {
			int a, b;
			cin >> a >> b;  //根据实例，a指的是下标，而c++中string库里指的都是下标，直接对应即可
			// 2. 截取：substr(起始下标, 截取长度)
			doc = doc.substr(a, b); //这个必须要用doc=来更新，因为substr截取函数只是把这段复制出来，不改变原字符串。而现在需要改变原有字符串
			cout << doc << endl;

		}
		else if (type == 3) {
			int a;
			string str;
			cin >> a >> str;
			// 3. 插入：insert(插入位置下标, 字符串)  在该下标！前面！插入
			doc.insert(a, str);
			cout << doc << endl;

		}
		else if (type == 4) {
			string str;
			cin >> str;
			// 4. 查找：find 返回的是 size_t 类型（无符号长整型）
			// 如果找不到会返回 string::npos 最大的无符号长整型
			// 强转为 int 后，npos 会变成 -1，正好符合题目要求
			int pos = (int)doc.find(str);
			cout << pos << endl;
		}
	}

	return 0;
}
//可以通过全局变量；静态变量static int a；引用。这三种方式来可直接通过改变参数来改变变量。
//数组作为参数传递时，实际是退化为指针，只是传递数组首地址，会同步影响外部原数组
//有3方法：1.直接数组名做指针 int arr[]，无需写大小。2.传递指针int*arr。3.传递引用int(&arr)[].此方法可保留数组大小

/*丑数的判断。
定义：一个数如果只包含2，3，5这三个质因子，且是正整数。
思路：1.首先，判断是否int n>0。
	  2.由于丑数n=2的k次幂*3的p次幂*5的m次幂(k,p,m均>=0),且幂次均为0时为1（故而1也是丑数）。
	    所以采用n反复除以2，3，5，直到不再含有其中任意一个因子。如果此时剩下的是1，那么说明不含其他因数，所以是丑数；若非1，则不是丑数
*/
#include<iostream>
using namespace std;
class solution_1 { 
public: //一定记得加，否则class默认私有，外界没法调用函数
	bool isugly(int n) {  //先创建一个类，里面有个成员函数isugly用于判断丑数
		if (n <= 0) {
			return false;
		}
		while (n % 2 == 0) {
			n /= 2; //如果它的因子里有2，则除以2.由于！while循环！会执行到不能继续为止，所以会把所有2因子除干净！
		}
		while (n % 3 == 0) {
			n /= 3; //同样，判断完2，再看是不是3的倍数
		}
		while (n % 5 == 0) {
			n /= 5;
		}
		return n == 1; //最后这句先看n==1是否成立成立返回值即为true，是丑数；不成立返回false
	}
};
int main() {
	solution p;//创建一个成员p
	int n;
	cin >> n;
	cout << p.isugly(n) << endl;
	return 0;
}
 
//丑数2：
#include<iostream>
using namespace std;
class solution_2 {

};