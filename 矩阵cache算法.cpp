#include<iostream>
#include<vector>
#include<cmath>
#include <chrono>   // 计时用 
#include <algorithm>
using namespace std;
using namespace chrono; 
using namespace std;
int main()
{
//	int n;cin>>n;
//	vector<vector<int>> a;
//	//给定输入n*n矩阵 
//	for(int i=0;i<n;i++)
//	{
//		vector<int> row;
//		for(int j=0;j<n;j++)
//		{
//			
//			int k;cin>>k;
//			row.push_back(k);
//		}
//		a.push_back(row);
//	}
	//大规模输入
	//计时器 
	auto start = high_resolution_clock::now();
	srand(12345);
	int n=4096; // 固定大小方便测试
	vector<vector<int>> a(n, vector<int>(n));
	vector<int> b(n);
	
	// 生成随机数
	for(int i=0;i<n;i++)
	{
   	 	b[i] = rand() % 100;
    	for(int j=0;j<n;j++)
		{
        	a[i][j] = rand() % 100;
    	}
	}	
	//给定输入向量b
//	vector<int> b;
//	for(int i=0;i<n;i++)
//	{
//		int p;cin>>p;
//		b.push_back(p);
//	}
	//定义每一列的内积结果数组c 
	int con;cin>>con; //con==0表示平凡 ，1表示优化1，2表示优化2; 
	vector<int> c(n,0);
//	//平凡算法 
	if(con==0)
	{
		for(int j=0;j<n;j++)
	{
		for(int i=0;i<n;i++)
		{
			c[i]+=a[i][j]*b[i];//显然，把每一列和这个向量相乘 
		}
	}	
	}

	//cache优化算法1：按照计算机的行优先访问，把循环交换为符合访问方式的逻辑
	if(con==1)
	{
	for(int i=0; i<n; i++)
	{        // 行在外
  		for(int j=0; j<n; j++)
		{      // 列在内
    		c[j] += a[i][j] * b[i];
  		}
	}	
	}
	//cache优化算法2： 循环分块
	if(con==2)
	{
		const int block=64;//地址偏向16，32，64字节对齐 
	for(int i0=0;i0<n;i0+=block)
	{
		for(int j0=0;j0<n;j0+=block)
		{
			for(int i=i0;i<min(i0+block,n);i++)//看能整块放进小矩阵里面吗
			{
				for(int j=j0;j<min(j0+block,n);j++)
				{
					c[j]+=a[i][j]*b[i];
				}
			}
		}
	}
	}
	//输出模块 
//	for(int i=0;i<n;i++)
//	{
//		cout<<" "<<c[i];
//	}
	cout<<endl;
	cout<<endl;
	cout<<endl;
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "耗时" <<duration.count() << " 微秒" << endl; 
	return 0;
 } 
