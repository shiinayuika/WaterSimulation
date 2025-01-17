#pragma once
#include "Scene.h"
#include<GLFW\glfw3.h>

void MyScene::Init()
{
	//初始化glew
	glewInit();
	//初始化Renderer中的program
	//UE4Renderer::GetRenderer()->InitProgram("UE4ShaderFile.vert", "UE4ShaderFile.frag");
	//SimpleRenderer::GetRenderer()->InitProgram("SimpleShaderFile.vert", "SimpleShaderFile.frag");
	VCRenter::GetRenderer()->InitProgram("SF_VertexColor.vert", "SF_VertexColor.frag");

	//pShadowTex.SetShader("shadowTex.v", "shadowTex.f");


	//指定光源参数
	lightPos = vec3(-3, 5, 3);
	lightColor = vec3(400.f, 400.f, 400.f);

	//初始化主相机
	//mainCamera = new Camera();
	MainCamera::GetInstance()->Init(vec3(0, 0, 2), vec3(0, 0, 0));

	//SetDrawMode(drawMode.isLine, false);
	drawMode.isLine = false;

	
	

	//指定物体PBR材质
	//MeshObject* cow = new MeshObject();
	//cow->SetName("cow");
	//cow->readObjFile("OBJ\\cow.obj");
	//cow->SetRenderer(SIMPLERENDER);
	//cow->InitBufferData();
	//cow->GetTransform().SetPosition(vec3(0, 0, 0));
	//cow->GetTransform().SetScaler(vec3(3.0));
	//dynamic_cast<SimpleShaderData*>(cow->GetShaderData())->SetColor(vec3(255, 0, 0));
	//objects.insert(pair<string, Object*>(cow->GetName(), cow));

	MPSWaterParticleGroup* water = new MPSWaterParticleGroup();
	water->SetName("water");
	water->SetRenderer(VC);
	water->GetTransform().SetPosition(vec3(0, 0, 0));
	//water->SetDiameter(0.01);
	//water->SetViscosity(0.000001);
	water->InitParticles();
	water->InitBufferData();
	//dynamic_cast<SimpleShaderData*>(water->GetShaderData())->SetColor(vec3(0, 0, 200));
	objects.insert(pair<string, Object*>(water->GetName(), water));


	//Metaball* balls = new Metaball();
	//balls->SetName("Metaball");
	//balls->SetRenderer(SIMPLERENDER);
	//balls->InitBufferData();
	//balls->GetTransform().SetPosition(vec3(-0.5, -0, 0));
	//balls->SetSourcePoints(vec3(0.1), 2, 1, 2);
	//balls->SetRadius(0.005);
	////balls->GetTransform().SetScaler(vec3(3.0));
	//dynamic_cast<SimpleShaderData*>(balls->GetShaderData())->SetColor(vec3(0, 0, 255));
	//objects.insert(pair<string, Object*>(balls->GetName(), balls));


	//myBox.InitDirectBox(1, 1, 1);					//顶点、索引信息初始化
	//myBox.InitBuffers();							//缓冲初始化
	//myBox.CoorDataInit(vec3(-0.5, 0.5, 1.0)/*, vec3(3.0, 0.1, 3.0)*/);
	//myBox.TextureUseInfo(true, true, true, true, true, true);				//纹理使用信息初始化
	//myBox.InitTexture(myBox.TAlbedo, "Material\\metalgrid2-dx\\metalgrid2_basecolor.png");		//生成需要的纹理
	//myBox.InitTexture(myBox.TNormal, "Material\\metalgrid2-dx\\metalgrid2_normal-dx.png");
	//myBox.InitTexture(myBox.TAo, "Material\\metalgrid2-dx\\metalgrid2_AO.png");
	//myBox.InitTexture(myBox.TRoughness, "Material\\metalgrid2-dx\\metalgrid2_roughness.png");
	//myBox.InitTexture(myBox.TMetallic, "Material\\metalgrid2-dx\\metalgrid2_metallic.png");
	//myBox.LightUseInfo(true);						//设置是否接收光照
	//myBox.InitMaterial(vec4(0.5f, 0.5f, 0.5f, 1.0f), vec4(0.5, 0.5, 0.5, 1.0f), vec4(0.7f, 0.7f, 0.7f, 1.0f), 7.0f);


	//STInit();
}

void MyScene::InitKeys()
{
	keys.insert(pair<KEYNAME, Key>(BTNW, Key(BTNW)));
	keys.insert(pair<KEYNAME, Key>(BTNA, Key(BTNA)));
	keys.insert(pair<KEYNAME, Key>(BTNS, Key(BTNS)));
	keys.insert(pair<KEYNAME, Key>(BTND, Key(BTND)));
	keys.insert(pair<KEYNAME, Key>(BTN1, Key(BTN1)));
	//keys.push_back(Key(BTNW));
}

void MyScene::Update(float dt)
{

	//计算视角矩阵
	MainCamera::GetInstance()->SetView();
	//计算投影矩阵
	MainCamera::GetInstance()->SetPro();

	//遍历所有object更新矩阵
	map<string, Object*>::iterator objs_it;
	for (objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
	{
		(*objs_it).second->Update(dt);
	}

	//cow.UpdateMatrix(mainCamera);
	//myBox.SetObjMat(camera.view, camera.pro);
	//myBucket.SetObjMat(camera.view, camera.pro);
	//myGrid.SetObjMat(camera.view, camera.pro);

	//遍历所有key，并执行key当前绑定的事件
	map<KEYNAME, Key>::iterator keys_it;
	for (keys_it = keys.begin(); keys_it != keys.end(); keys_it++)
	{
		keys_it->second.Execute();
	}
}

void MyScene::Draw()
{

	//NormalShadowMap();

	//绘制每一个物体时，先将类中的该物体的所有相关矩阵，材质等信息传入shader中


	//绘制,包含缓冲区的清空，各种效果的开启（blend、 cull之类的）
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);					//三维物体要开启背面剔除

	if (drawMode.isLine)
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//glFrontFace(GL_CW);
	//glCullFace(GL_FRONT);

	//glUseProgram(p1.p);						//启用着色器程序

	map<string, Object*>::iterator objs_it;
	for (objs_it = objects.begin(); objs_it != objects.end(); objs_it++)
	{
		(*objs_it).second->Draw();
	}

}