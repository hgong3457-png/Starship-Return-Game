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