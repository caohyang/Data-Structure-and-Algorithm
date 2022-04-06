/*
// poisson_distribution
#include <iostream>
#include <random>

int main()
{
  const int nrolls = 10000; // number of experiments
  const int nstars = 100;   // maximum number of stars to distribute

  std::default_random_engine generator;
  std::poisson_distribution<int> distribution(4.1);

  int p[10]={};

  for (int i=0; i<nrolls; ++i) {
    int number = distribution(generator);
    if (number<10) ++p[number];
  }

  std::cout << "poisson_distribution (mean=4.1):" << std::endl;
  for (int i=0; i<10; ++i)
    std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << std::endl;

  return 0;
}
*/
#include<random>
#include<cstdio>
#include<iostream>

int main() {
	std::random_device id;
	std::default_random_engine time(id());//随机数种?
	std::poisson_distribution<int>Generator(5);//5是泊松分布均值
	int Poisson_Data[100],Sum=0;
	for (int i = 0; i < 100; i++)
	{
	Poisson_Data[i] = Generator(time);//?成服从泊松分布的数据
	printf("%2d ", Poisson_Data[i]);
	if((i+1)%10==0)
	std::cout << std::endl;
	Sum += Poisson_Data[i];
	}
	std::cout << "Avg:" << float(Sum / 100.0 )<< std::endl;
	getchar();
}
