#include<iostream>
#include<vector>
#include<cmath>
#include <chrono>   // 计时用 
#include <algorithm>
using namespace std;
using namespace chrono; 
using namespace std;
//cache优化2：递归算法 
int sumfunc(vector<int>&a,int left,int right)
	{
		if(left==right)//最小节点 
			return a[left];
		else
		{
			int mid=(left+right)/2;//取中间节点 
			return sumfunc(a,left,mid)+sumfunc(a,mid+1,right);
		}
	} 
int main()
{
	int con;
	cin>>con;//算法控制符，0为平凡，1为改进1，2为改进2 
	srand(12345);
	int n=10000000;//数据规模
	vector<int> a(n);
	int sum=0;
	for(int i=0;i<n;i++)
	{
		a[i]=rand()%100;
	 } 	
	//算法开始时计时 
	auto start = high_resolution_clock::now();
	//平凡算法 
	if(con==0) 
	for(int i=0;i<n;i++)
	{
		sum+=a[i];
	}

	//cache优化1：两路并行，奇数下标给sum1，偶数下标给sum2
	if(con==1)
	{
	int sum1=0;int sum2=0;
	for(int i=0;i<n;i+=2)
	{
		sum1+=a[i] ;
		sum2+=a[i+1];
	} 
	sum=sum1+sum2; 
	}

	//cache优化2：递归算法，子节点两两相加返回父节点，递归往复 
	if(con==2)
	{
		sum=sumfunc(a,0,n-1);
	}

	
	//输出环节 
	cout<<sum;
	cout<<endl;
	cout<<endl;
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "算法耗时" <<duration.count() << " 微秒" << endl;
	return 0;
}
