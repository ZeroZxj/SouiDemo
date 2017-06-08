#pragma once
#include "stdafx.h"
#include "MainDlg.h"
#include "LoginDlg.h"

//#define RES_TYPE 0      //从文件中加载资源，加载失败再从PE加载
#define RES_TYPE 1   //从PE资源中加载UI资源
// #define RES_TYPE 2   //从zip包中加载资源

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR    lpCmdLine,
						_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//初始化组件环境
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

	//执行结果
	int nRet = 0;

	//声明SouiCom组件管理类对象
	SComMgr *pComMgr = new SComMgr;

	//加载结果标识
	BOOL bLoaded = FALSE;
	//定义一组类SOUI系统中使用的类COM组件  CAutoRefPtr是一个SOUI系统中使用的智能指针类
	CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;			//UI渲染模块，由render-gdi.dll或者render-skia.dll提供
	CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;	//图片解码器，由imagedecoder - wid.dll模块提供

																//初始化UI渲染模块
	bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory);
	SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
	//初始化图片解码管理类模块
	bLoaded = pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));
	//为渲染模块设置它需要引用的图片解码模块
	pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

	//创建SOUI应用程序实例
	SApplication *theApp = new SApplication(pRenderFactory, hInstance);
	//向SApplication系统中注册由外部扩展的控件及SkinObj类
	//.......
	//从DLL加载系统资源
	HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
	if (hModSysResource)
	{
		CAutoRefPtr<IResProvider> sysResProvider;
		CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
		sysResProvider->Init((WPARAM)hModSysResource, 0);
		theApp->LoadSystemNamedResource(sysResProvider);
		FreeLibrary(hModSysResource);
	}
	else
	{
		SASSERT(0);
	}
	CAutoRefPtr<IResProvider>   pResProvider;
#if (RES_TYPE == 0)//从文件加载
	CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
	if(!pResProvider->Init((LPARAM)_T("uires"), 0))
	{
		SASSERT(0);
		return 1;
	}
#elif (RES_TYPE==1)//从EXE资源加载
	CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
	bLoaded = pResProvider->Init((WPARAM)hInstance, 0);
#elif (RES_TYPE==2)//从ZIP包加载
	bLoaded = pComMgr->CreateResProvider_ZIP((IObjRef**)&pResProvider);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));

	ZIPRES_PARAM param;
	param.ZipFile(pRenderFactory, _T("uires.zip"), "souizip");
	bLoaded = pResProvider->Init((WPARAM)&param, 0);
	SASSERT(bLoaded);
#endif

	//如果需要在代码中使用R::id::namedid这种方式来使用控件必须要这一行代码：2016年2月2日，R::id::namedXmlID是由uiresbuilder 增加-h .\res\resource.h idtable 这3个参数后生成的。
	theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);
	//将创建的IResProvider交给SApplication对象
	theApp->AddResProvider(pResProvider);

	//创建主对话框并显示
	{
		CLoginDlg dlgLogin;
		dlgLogin.Create(GetActiveWindow(), 0, 0, 0, 0);
		dlgLogin.SendMessage(WM_INITDIALOG);
		dlgLogin.CenterWindow(dlgLogin.m_hWnd);
		dlgLogin.AnimateHostWindow(200, AW_CENTER);
		nRet = theApp->Run(dlgLogin.m_hWnd);

//		if (dlgLogin.GetReturnCode() == 0)
		{

		}

	}

	//释放组件管理类对象
	delete pComMgr;

	//删除组件环境
	OleUninitialize();
	return 0;
}