//#pragma once
//#include<vector>
//#include<glm.hpp>
//#include<iostream>
//using namespace glm;
//using namespace std;
//
//#include"Const.h"
//#include"MPSConst.h"
//#include<mkl.h>
//#include<algorithm>
//#include<omp.h>
//
////#include"MPSWaterParticleGroup.h"
//
//class MPSToolFun
//{
//private:
//	static MPSToolFun* mpsTool;
//
//
//	float Ds;				//维数
//	float reForDG;			//计算密度和梯度的re
//	float reForD;			//计算粒子数密度的re
//	float reForG;			//计算梯度的re
//	float reForL;			//计算拉普拉斯的re同时也是lambda计算时的取值
//	float viscosity;		//粘度系数
//	float fluidDenstiy;		//流体密度
//	float gama;				//
//	float deltaT;			//时间间隔直接给定，而不是按照每帧的间隔来确定
//
//
//
//
//	vec3 vG;				//重力加速度的向量形式
//
//	MPSToolFun()
//	{
//		Ds = DIMENSION;
//		reForD = RADIUS_FOR_NUMBER_DENSITY;
//		reForG = RADIUS_FOR_GRADIENT;
//		//reForDG = ;
//		reForL = RADIUS_FOR_LAPLACIAN;
//		viscosity = KINEMATIC_VISCOSITY;
//		fluidDenstiy = FLUID_DENSITY;
//		gama = RELAXATION_COEFFICIENT_FOR_PRESSURE;
//		vG = vec3(GRAVITY_X, GRAVITY_Y, GRAVITY_Z);
//		deltaT = DELTA_TIME;
//	}
//
//public:
//	float testLambda0;
//	//内部私有计算函数
//	//Lambda函数
//	float Lambda(vector<vec3> r, int currentIndex);
//	//计算权重的方程
//	float WeightFun(float dis, float re);
//	//计算临时值u* (时间差，u的拉普拉斯结果，当前粒子的u)
//	vec3 TempU(vec3 resLU, vec3 uNow);
//	//计算隐式拉普拉斯的右端项(初始密度，u*的散度，时间差，n0，n*)
//	float ImplicitLaplacianRight(float rho0, float resDu, float n0, float tempN);
//	float OldImplicitLaplacianRight(float rho0, float n0, float tempN);
//	//获取矩阵C
//	mat3 GetMaterixC(vector<vec3>& R, int currentIndex, float n0);
//
//	//和大型方程组相关的函数
//	//1.方程的构造
//	bool SolveEquation(vector<double>& a, vector<int>& ia, vector<int>& ja,
//		vector<double>& b, vector<double>& x, int nRhs);
//
//public:
//	//外部接口
//	static MPSToolFun* GetMPSTool()
//	{
//		if (mpsTool == NULL)
//			mpsTool = new MPSToolFun();
//		return mpsTool;
//	}
//
//	float GetDeltaT()
//	{
//		return deltaT;
//	}
//
//	//显式散度
//	float ExplicitDivergence(vector<vec3>& phi, vector<vec3>& r, int currentIndex, float n0);
//	//显式拉普拉斯
//	template<typename T>
//	T ExplicitLaplacian(vector<T>& phi, vector<vec3>& r, int currentIndex, float n0);
//	//显式梯度（新方法计算梯度）
//	vec3 ExplicitGradient(mat3 C, vector<double>& p, vector<vec3>& r, float n0, int currentIndex);
//
//	//MPS中密度的计算
//	float DensityN(vector<vec3>& r, int currentIndex);
//	//根据速度量u计算新的位置
//	vec3 NewPosR(vec3 nowPos, vec3 u);
//	//计算真实的u值
//	vec3 CalculateU(vec3 resLU, vec3 resGP, vec3 uNow, float tho);
//	//隐式计算P（解稀疏方程组）
//	vector<double> ImplicitCalculateP(vector<vec3>& r, float n0Array, vector<bool>& isSurface, vector<double> Right);
//
//	vec3 OldGradient(vector<vec3>& r, vector<double>& p, int currentIndex, float n0);
//};
//
//
//template<typename T>
//inline T MPSToolFun::ExplicitLaplacian(vector<T>& phi, vector<vec3>& r, int currentIndex, float n0)
//{
//	T res = T();
//	for (int i = 0; i < phi.size(); i++)
//	{
//		if (i != currentIndex)
//		{
//			res += (phi[i] - phi[currentIndex]) * WeightFun(distance(r[i], r[currentIndex]), reForL);
//		}
//	}
//
//	//float lambda = Lambda(r, currentIndex);
//
//	//res *= (2 * Ds / n0 * lambda);
//	res *= (2 * Ds / n0 * testLambda0);
//	//res *= (2 * Ds / DensityN(r, currentIndex) * testLambda0);
//	return res;
//}
