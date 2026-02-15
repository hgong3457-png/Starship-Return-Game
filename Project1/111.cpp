//#include <iostream>
//using namespace std;
//int main()
//{
// 
//	int num;
//	int result = 0;
//	cin >> num;
	/*int a;
	a < num;
	a % 5 == 0;*/
	//for (int i = 0; i < num; i++)             //for指的循环遍历，括号里两个；间隔三个量，
	//    if(i%5==0)                            //先是循环量初始值，再是可循环的条件，最后是循环一次!后!进行的操作
 //          result +=i;
	//	
	//int i = 0;
	//while (i < num / 5) {      //while 括号里只写条件  //整数之间运算结果全是整数，所得若为小数，向零取整，直接切断小数，不四舍五入
	//	result += i * 5;
	//	i++;

	//}
	//cout << result;
	/*for (int i = 9; i >= num; i --) {
		for (int j = 1; j <= i; j ++) {
			cout << j << "*" << i << "=" << i * j;
		}
		cout << endl;*/
//}

		/*  //如何在一个文件中写多个函数题
			void task1()
		{
		
		}
		void task2()
		{

		}
		int main()
		{
			task1();
		}
	*/


while ((int(i) % 10 == 0) && (i / 10 <= T / 10)) {
	if (s1 <= s2) {
		s1 += 90;
		i += 30;
	}
	else {
		s1 += 30;
		s2 += 90;
		i += 10;
	}
}
while ((i / 10 >= T / 10) && (i <= T)) {
	s1 += (T - i) * 3;
	s2 += (T - i) * 9;






