#pragma once
#include<vector>
#include<glm.hpp>
using namespace glm;
using namespace std;

class MPSToolFun
{
private:
	static MPSToolFun* mpsTool;


	float Ds;				//维数
	float reForDG;			//计算密度和梯度的re
	float reForL;			//计算拉普拉斯的re
	float viscosity;		//粘度系数
	float g;				//重力加速度
	float gama;				//
	MPSToolFun()
	{
		Ds = 3;
		reForDG = 0;
		reForL = 0;
		viscosity = 0;
		g = 9.8;
		gama = 0.01;
	}

public:
	//内部私有计算函数
	//Lambda函数
	float Lambda(vector<vec3> r, int currentIndex);
	//计算权重的方程
	float WeightFun(float dis, float re);
	//计算临时值u* (时间差，u的拉普拉斯结果，当前粒子的u)
	vec3 TempU(float deltaT, vec3 resLU, vec3 uNow);
	//计算隐式拉普拉斯的右端项(初始密度，u*的散度，时间差，n0，n*)
	vec3 ImplicitLaplacianRight(float rho0, vec3 resDu, float deltaT, float n0, float tempN);
	float OldImplicitLaplacianRight(float rho0, float deltaT, float n0, float tempN);
public:
	//外部接口
	static MPSToolFun* GetMPSTool()
	{
		if (mpsTool == NULL)
			mpsTool = new MPSToolFun();
		return mpsTool;
	}

	//void SetN0()
	void SetRe(float l0)
	{
		reForDG = 2.1 * l0;
		reForL = 3.1 * l0;
	}

	void SetViscosity(float v)
	{
		viscosity = v;
	}

	//显式散度
	template<typename T>
	T ExplicitDivergence(vector<T>& phi, vector<vec3>& r, int currentIndex, float n0);
	//显式拉普拉斯
	template<typename T>
	T ExplicitLaplacian(vector<T>& phi, vector<vec3>& r, int currentIndex, float n0);
	//显式梯度
	template<typename T>
	T ExplicitGradient(vector<T> phi, vector<vec3> r, int currentIndex);

	//MPS中密度的计算
	float DensityN(vector<vec3> r, int currentIndex);
	//根据速度量u计算新的位置
	vec3 NewPosR(vec3 nowPos, vec3 u);
};

template<typename T>
inline T MPSToolFun::ExplicitDivergence(vector<T>& phi, vector<vec3>& r, int currentIndex, float n0)
{
	T res = T();
	for (int i = 0; i < phi.size(); i++)
	{
		if (i != currentIndex)
		{
			res += ((phi[i] - phi[currentIndex]) * (r[i] - r[currentIndex]) / pow(distance(r[i], r[currentIndex]), 2))
				* WeightFun(distance(r[i], r[currentIndex]), reForDG);
		}
	}
	res *= (Ds / n0);
	return res;
}

template<typename T>
inline T MPSToolFun::ExplicitLaplacian(vector<T>& phi, vector<vec3>& r, int currentIndex, float n0)
{
	T res = T();
	for (int i = 0; i < phi.size(); i++)
	{
		if (i != currentIndex)
		{
			res += (phi[i] - phi[currentIndex]) * WeightFun(distance(r[i], r[currentIndex]), reForL);
		}
	}

	float lambda = Lambda(r, currentIndex);

	res *= (2 * Ds / n0 * lambda);
	return res;
}

template<typename T>
inline T MPSToolFun::ExplicitGradient(vector<T> phi, vector<vec3> r, int currentIndex)
{
	return T();
}
