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
	solution_1 p;//创建一个成员p
	int n;
	cin >> n;
	cout << p.isugly(n) << endl;
	return 0;
}
 
//丑数2：给整数n，返回丑数列中第n个丑数
//思路：1.最小堆法
       // 由于丑数序列递增的，首先初始化一个空的最小堆，先将1加入进去，然后把他取出来，把他的2，3，5倍加进去。
       //后面也都是先将现在堆中最小（堆顶）的丑数curr取出来（弹出）：如果是第n次，则就是第n个丑数；否则，取出后将curr的2，3，5倍去重后加入堆中
      //所以每个数当沦为最小后就会被弹出，将由他生成的3个新丑数加入后，就功成身退了
//此方法用到哈希表和最优队列
#include<iostream>
using namespace std;
class solution_2 {
public:

};

//思路（优化）：2。动态规划（三指针法）：
//dp[i]肯定是其前面的某个数乘以 2 （或乘以 3、乘以 5）得出来的，
//而dp[i] x 2 、dp[i] x 3、dp[i] x 5 这三个数，肯定也是dp 数组后面某个位置的数。
//那就可以推断出来，dp这个数组上的数，每个位置肯定都要x2\x3\x5 一遍，其结果是放在dp 数组后面某个位置。
//那我们就可以从这个数组初始的状态，即dp[1] = 1 开始，用p2\p3\p5 表示当前该哪个位置该乘以2\3\5 了。
//我们只要每次取乘以 2、3、5 后的结果中最小的值，那这个最小的值就是最新一个的dp 值，
//然后相应地移动一下计算出这个新dp 值的 p2（或 p3 或p5）索引，即该下一个数去乘以2（或3 或5）了。按次遍历，计算出第i个数，即为dp[i]
#include <iostream>
using namespace std;

class Solution {
public:
	int nthUglyNumber(int n) {
		// 创建一个普通数组用来存前 n 个丑数 (数组开到 1700 足够装下 1690 个)
		int dp[1700] = { 0 };//初始化为0记得

		// 第 1 个丑数固定是 1
		dp[1] = 1;

		// 设置三个“指针”!本质就是数组的下标! 初始都指向第 1 个丑数
		int p2 = 1;
		int p3 = 1;
		int p5 = 1;

		for (int i = 2; i <= n; i++) {
			// 分别算出三个队伍当前的排头兵是谁
			// (用 long long 是防止！计算过程中间！超出 int 范围)
			long long num2 = (long long)dp[p2] * 2;
			long long num3 = (long long)dp[p3] * 3;
			long long num5 = (long long)dp[p5] * 5;

			// 找出三个数里面最小的那个
			long long nextUgly = num2;
			if (num3 < nextUgly) nextUgly = num3;
			if (num5 < nextUgly) nextUgly = num5;

			// 把最小的数放进我们的丑数数组里
			dp[i] = nextUgly;

			// 谁被选中了，谁的指针就往前走一步
			// 注意：这里用的是三个独立的 if，不是 else if！
			// 这样如果 num2 和 num3 都是 6，p2 和 p3 都会前进，完美避免重复
			if (dp[i] == num2) p2++;
			if (dp[i] == num3) p3++;
			if (dp[i] == num5) p5++;
		}  //用彼此独立的if，可确保如果几个同时是最小，都可加一

		// 循环结束，直接返回第 n 个丑数
		return dp[n];
	}
};
//由于始终是dp（丑数数组）里的数在衍生出新的数来，所以逐渐是1*2，1*3，2*2，1*5，2*3，2*5...就是混合的丑数！

//判断丑数用反复除法，找到丑数用直接生长法

//洛谷5736：质数筛
#include<iostream>
using namespace std;
bool isprime(int n) {
	if (n <= 1 || n > 10e5) //这些不符合要求的数一概返回false，也确保了不会输出。同时1本来也就不算质数
		return false;
	if (n == 2) //2单独判断
		return true;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}
int main() {
	int n, arr[105];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i] ;
	}
	for (int i = 0; i < n; i++) {
		bool flag=isprime(arr[i]);
		if (flag == true) {
			cout << arr[i] << ' ';
		}
	}
}
//int就是正负数均包含。从-2*31到2*31-1
//洛谷B2129
#include<iostream>
#include<iomanip>
using namespace std;
int max_1(int a, int b, int c) {
	int flag = (a > b) ? a : b;
	if (c > flag)
		flag = c;
	return flag;
}
int max_2(int a, int b, int c) {
	int flag = (a + b > b) ? (a + b) : b;
	if (c > flag)
		flag = c;
	return flag;
}
int max_3(int a, int b, int c) {
	int flag = (a > b) ? a : b;
	if (b + c > flag) {
		flag = b + c;
	}
	return flag;
}
int main() {
	int x,y,z;
	cin >> x >> y >> z;
	if (max_2(x, y, z) == 0 || max_3(x, y, z) == 0) {
		return 0;
	}
	//需要判断分母是否有0，若有，直接结束运行
	double m;
	m =1.0* max_1(x, y, z) / max_2(x, y, z) / max_3(x, y, z);
	//此处一定注意由于找最大值函数返回值是整数，整数乘除会截断小数位，所以精度丧失，所以需要*1.0来让结果保留成小数
	cout << fixed << setprecision(3) << m << endl;
}

//设计两个重载函数，分别返回两个数和三个数最大值
int myMax(int a, int b) {
	return a > b ? a : b;
}
int myMax(int a, int b, int c) {
	return myMax(myMax(a, b), c);
}
//注意点：1.重载函数（同名函数）区分不靠返回值，而是靠参数表：参数类型，数目，顺序...
       // 2.由于三个参数比较需要先两个比，再与第三者比。所以注意递进式设问！可以使用刚设计完的两个参数比较的函数！

//洛谷：U271244 类的设计
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
class date {
private:
	int year, month, day;
	bool isLeapYear(int y)const {  //加const在函数后面是为了！保证：该成员函数不会修改任何成员变量的值！
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}  //判断闰年：1.是4倍数但不是100倍数 2.是400倍数（注意是100倍数但不是400倍数 是平年）
	int getDaysInMonth(int y, int m)const {
		int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };// 先用一个列表存储每个月天数，对应月份参数返回对应天数
		if (isLeapYear(y) && m == 2)
			return 29; //如果是闰年的二月，为29天，天数不在列表里
		
		return days[m - 1]; //因为列表首元素即为第0位
	}
	void addoneday() {
		day++;
		if (day > getDaysInMonth(year, month)) {  //相当于我把y,m,d赋值给year...但我的函数形参叫重了，所以把year..当成实参又赋值给形参y,m,d
			month++;								//所以前后y，m，d并不同
			day = 1;
			if (month > 12) {
				year++;
				month = 1;
			}  //先判断月份限度，再判断年份限度
		}
	}
	void suboneday() {
		day--;
		if (day < 1) {
			month--; 
			if (month < 1) {
				year--;
				month = 12;
			}
			day = getDaysInMonth(year, month); //此处与加一天不同，因为减一天是到上一月的最后一天，
												//但上一月万一也不再是这一年的，需要即使更改
		}
	}
public:
	date(int y, int m, int d) :year(y), month(m), day(d) {

	}
	date operator+(int n)const {
		date result = *this; //this是隐式指针1指向调用该函数的对象！现在dl调用，*this=dl,那么相当于把dl所有数据拷贝一份给result
							//这块才定义对象result，所以是初始化操作，调用默认拷贝构造函数。只有不加date声名，才是普通赋值
		for (int i = 0; i < n; i++) {
			result.addoneday(); //重复对result进行操作，碰不到原dl。
		}
		return result;
	}
	date operator-(int n)const {
		date result = *this;
		for (int i = 0; i < n; i++) {
			result.suboneday();
		}
		return result;
	}
	string toText()const {
		return to_string(year) + '-' + to_string(month) + '-' + to_string(day);
	}
};
int main()
{
	int y, m, d;
	cin >> y >> m >> d;
	date d1(y, m, d);

	int n;
	cin >> n;

	cout << d1.toText() << " + " << n << " = " << (d1 + n).toText() << endl; //由于totext函数是类的成员函数，只能对象调用，所以上面把重载+函数返回值设为date类型
	cout << d1.toText() << " - " << n << " = " << (d1 - n).toText() << endl;
	return 0;
}

//acwing：求 1 + 2 + … + n
//要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句(A ? B : C)
//n*(n+1)/2不可用。for循环1到n相加不可用。
//递归也不可用！（因为递归需要if判断终止条件）

//核心：逻辑短路：&&运算，只要第1个为false，后面都不执行！可以以此代替if，作为递归的终止条件判断
//递归仍是核心，可以多次调用所需运算函数，不用显式化整个循环！
class solution {
	int getsum(int n) {   //n==1时
		int result = n;   //res先=1
		(n > 0) && (result += getsum(n - 1)); //此时调用getsum（0），n==0第一个为false，触发短路，后面不加，则返回0本身
		return result;  //result=1+0
	} //其实每重递归会新给函数内 局部变量n，result在栈区新开一个空间，所以是同名但不是同一个
};    //每一个result都是先保存住自己的n，等待调用后面把小数加和到自己这层的result上  //完美符合getsum是所有小数之和
    //注意：随着递归变深，地址通常会向内存的一个方向（通常是向下）连续偏移。
	// 这就是为什么如果递归太深（比如 n 极大），会导致 Stack Overflow（栈溢出） —— 也就是这块专门存“套娃”的内存空间被用光了。


//acwing 链表（不同于数组，非连续的存储结构，由结点通过指针链接）
//链表核心是由 结点 组成：每个结点存储两个东西：1.数据域 2.指针域，存储下一个结点的地址
// 头结点；尾结点：最后一个，指针域是NULL，代表后面没人了
//1.单向链表：只有一个指针域，指向后继结点，只能单向遍历，必须从头开始，慢
//2.双向链表：包含两个指针域，指向前后两侧，双向遍历，但每个结点需要额外空间存储前驱指针
//3.循环链表：在单向或双向链表基础上，将尾部指向头结点。从任一点出发可遍历整个链表

struct ListNode {
	int val;         // 存储的数据
	ListNode* next;  //指向下一个结点的指针,指针存放的是地址，
					// 64位系统（代表CPU寻址能力，需要8个字节门牌号即地址），所以指针大小固定！都是8字节。所以只要开的空间确定，就可以先写进来
					//注意：这个还没定义完的数据类型的变量不可写进来，会无限套娃导致不知道大小，无限大内存，报错
	ListNode(int x) : val(x), next(NULL) {} //方便快速定义的函数
};
class solution {
public:
	void deleteNode(ListNode* node) {
		//将下一个C的 数据值 赋给当前B
		node->val = node->next->val;
		//中间先把C的地址临时保存一下，方便最后彻底释放C内存
		ListNode* temp = node->next;
		//用D的地址替换掉原先B指向的地址（原为c）
		node->next = node->next->next;
		delete temp;
	}

};
//O（1）时间复杂度删除元素 实现思路：
//常规：要删掉B，需要把A叫来更改指向地址为C。但是单向列表只知道C在哪，找不到上一个元素A，必须遍历一圈，耗费O(n)
// 巧解：狸猫换太子！
// 把C指向的D地址和C的值全部赋值给B，让B成为假C这时再删除C
// 那么以后A继续找'B'，但貌似找的就是C相当于把B删掉了





// 这是一个标准的单向链表结点定义
struct ListNode {
	int val;         // 这里存数据
	ListNode* next;  // 这里存下一个结点的地址

	// 这是一个“构造函数”，方便我们快速创建新结点并赋值
	ListNode(int x) {
		val = x;
		next = nullptr; // nullptr 是 C++ 中的空指针，代表后面没东西了（初始化）
	}
};
// 1. 先创造三个独立的人（结点）
ListNode* node1 = new ListNode(1);
ListNode* node2 = new ListNode(3);
ListNode* node3 = new ListNode(5);
// 2. 把他们按顺序连起来（交换小纸条）
node1->next = node2; // 1 的下一个是 3
node2->next = node3; // 3 的下一个是 5
// node3 的 next 默认就是 nullptr，不用管
// 此时，node1 就是这个链表的“头结点” (Head)



//例题：将两个原本顺序排列的链表组合后仍保持从小到大的排序
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		// 1. 请出一个“假人”作为新链表的 虚拟头结点！
		ListNode* dummy = new ListNode(-1);
		// cur 就像是老师的手，指向当前新队伍排到了哪里
		ListNode* cur = dummy; //这是动态指针，标识进度
		//此段代码中dummy同front (充当头结点)；cur同rear（充当尾结点）
		

		// 2. 当两队都还有人的时候，不断比较
		while (l1 != nullptr && l2 != nullptr) {
			if (l1->val <= l2->val) {
				// l1 的人更矮（或一样高），接在 cur 后面
				cur->next = l1;//内容交给了新队伍
				l1 = l1->next; // l1 队伍换下一个人上前
			}
			else {
				// l2 的人更矮，接在 cur 后面
				cur->next = l2;
				l2 = l2->next; // l2 队伍换下一个人上前
			}
			cur = cur->next; // 老师的手也往后挪一位，准备牵下一个人
		}

		// 3. 既然循环结束，肯定有一队人空了，另一队还有剩
		// 既然剩下的本来就是排好序的，直接把整串“尾巴”接上去就行了
		if (l1 != nullptr) {
			cur->next = l1;
		}
		else {
			cur->next = l2;
		}

		// 4. 找到真正的头结点，释放假人（虚拟头结点）
		ListNode* realHead = dummy->next;
		delete dummy; // 好习惯：new 出来的内存要 delete 掉

		return realHead;
	}
};

//链表形式的队列：定义+入队+出队
#include <iostream>
using namespace std;

// 你给出的结点定义（补充完整）
struct ListNode {   //链队列 同链表一样：先定义一个节点类(由于希望外界能访问节点数值和指针库，所以用struct即可默认public)
	int val;                           //再定义一个链表类(其中需要引用到 节点类型 数据/指针)
	ListNode* next;   //？类型指针代表其指向？类型数据的地址
	ListNode(int x) : val(x), next(nullptr) {}  //有参构造函数，便于后续创建一个节点时 快速初始化
};

// 带头结点的链队列类
class LQueue {
private:
	//定义两个指针
	ListNode* front;   // 指向头结点
	ListNode* rear;    // 指向队尾结点
	
public:
	LQueue() { initQueue(); } //自己定义一个无参构造函数，函数体内容为 调用一个 定义空队列的函数

	// 初始化空队列（带头结点）  即使一开始没有任何有效元素，仍有一个无意义的占位节点，
	                          // 方便统一 所有情况下的入队和出队操作
	void initQueue() {
		front = rear = new ListNode(0); // 头结点，val 无实际意义
		front->next = nullptr;  //此行尽量写上，确保front指向为空，说明无元素；rear不用了，因为last one后面一定是空
	}

	// 判断队列是否为空
	bool isEmpty() const {
		return front == rear;   // 或 front->next == nullptr
	}

	// 入队  注意队列从后面进
	void enQueue(int x) {
		ListNode* newNode = new ListNode(x);
		rear->next = newNode;  //先确保 当下的rear（末尾）和newNode连上
		rear = newNode;        //再移动rear的指向
	}

	// 出队（成功返回 true，并将出队元素存入 变量x这个容器中）
	bool deQueue(int& x) {
		if (isEmpty()) 
			return false;

		//注意出队列的必须是front的下一个 实际头
		ListNode* firstNode = front->next;   // 第一个实际数据结点
		x = firstNode->val;
		front->next = firstNode->next;

		// 若删除的是最后一个结点，需将 rear 复位到头结点
		if (rear == firstNode) {
			rear = front;
		}  //注意考虑边界条件

		delete firstNode;
		return true;
	}

	// 析构函数（释放所有余结点，包括头结点） ！重要！
	~LQueue() {
		while (front != nullptr) {
			ListNode* temp = front;
			front = front->next; //移动front位置
			delete temp;
		}
	}
};

