//task3：分配，释放内存并输出
#include<iostream>
#include<string>
using namespace std;
int main() {
	int size;
	cin >> size;
	int arr[1005] = { 0 }; //初始化数组所有相为0
	int n;
	cin >> n;
	string prompt;  //字符串类型prompt
	for (int k = 0; k < n; k++) {
		cin >> prompt;   //对于两类提示语句，统一都先输入一个提示词
		if (prompt == "ALLOCATE") {
			int rs;
			cin >> rs;  // 对于allocate ，只再加一项rs代表 要求内存大小
			bool allocated = false; //在遍历所有i之前设定为false
			for (int i = 0; i <= size - rs; i++) {
				bool can_allocate = true; //每开始循环一个新的i下所有j前，重新初始化为true
				for (int j = i; j < i + rs; j++) {
					if (arr[j] != 0) {
						can_allocate = false;
						break; // 找见一个非0的j时，直接改为false并跳出j循环
					}
				}
				if (can_allocate) { //遍历所有j后，全为0则仍保持为true
					for (int j = i; j < i + rs; j++) {
						arr[j] = 1;
					}
					cout << "Allocate at index" << i << endl;
					allocated = true;
					break; // 找到这个完美的i后，不再遍历后面，跳出
				}
			}
			if (!allocated) {
				cout << "Allocation failed" << endl;
			}

		}
		else if (prompt == "Free") {
			int start, length;
			cin >> start >> length; //free提示词下需要 定义并输入2个变量
			if (start<0 || start + length>size)//判断1.边界问题，要么是偏左，要么是偏右。注意符号！
			{
				cout << "Invalid free operation" << endl;
			}
			else {
				bool free = true;
				for (int i = start; i < start + length; i++) {
					if (arr[i] != 1) {
						free = false;
						break;  //判断2：每一格状态，全为1，才可执行最终的释放
					}
				}
				if (free) {
					for (int i = start; i < start + length; i++) {
						arr[i] = 0;
					}
					cout << "Free" << length << "blocks from index" << start << endl;
				}
				else {
					cout << "Invalid free operation" << endl;
				}
			}
		}
	}
	return 0;

}


//task2:找到距离最大的两点坐标
#include<iostream>
#include<cmath>
using namespace std;
struct dian {
	int num;
	double x;
	double y;
};
int main() {
	int m;
	cin >> m;
	if (m <= 0 || m >= 100) {
		return 0;
	}
	if (m == 1) {
		cout << "No Distance!" << endl;
		return 0;
	}
	dian point[105];
	for (int i = 1; i <= m; i++) {
		point[i].num = i; //并不输入序号，手动顺序编排序号
		cin >> point[i].x >> point[i].y;
		for (int j = 1; j < i; j++) { //!往前!对比是否有相同
			if (point[i].x == point[j].x && point[i].y == point[j].y) {
				cout << "Repeated Points!" << endl;
				return 0;
			}
		}
	}  //这个循环主要是输入结构体内容
	double max_dis = 0;
	
	for (int i = 1; i < m; i++) {
		for (int j = i + 1; j <= m; j++) { //往后找j来算距离共 m*（m-1）/2 个distance
			double dx = point[j].x - point[i].x;
			double dy = point[j].y - point[i].y;
			double dis = sqrt(dx * dx + dy * dy);

			if (dis > max_dis)
				max_dis = dis; //注意！没必要把所有距离都保存，只需要算出当下来不断更新最大距离 
		}						//因为即使保存距离，最后输出的是num，仍然无法将每个距离跟num关联！

	} //这个循环是为了找到最大距离
	for (int i = 1; i < m; i++) {
		for (int j = i + 1; j <= m; j++) {
			double dx = point[j].x - point[i].x;
			double dy = point[j].y - point[i].y;
			double distance = sqrt(dx * dx + dy * dy);
			if (distance == max_dis) {
				cout << point[i].num << ' ' << point[j].num << endl;
			}  //每一次循环重新定义变量dx，dy和distance。唯有max_dis是宏观变量
		}
	}
}
