#pragma once
#include "stdafx.h"
#include "MainDlg.h"
#include "LoginDlg.h"

//#define RES_TYPE 0      //���ļ��м�����Դ������ʧ���ٴ�PE����
#define RES_TYPE 1   //��PE��Դ�м���UI��Դ
// #define RES_TYPE 2   //��zip���м�����Դ

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

	//��ʼ���������
	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

	//ִ�н��
	int nRet = 0;

	//����SouiCom������������
	SComMgr *pComMgr = new SComMgr;

	//���ؽ����ʶ
	BOOL bLoaded = FALSE;
	//����һ����SOUIϵͳ��ʹ�õ���COM���  CAutoRefPtr��һ��SOUIϵͳ��ʹ�õ�����ָ����
	CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;			//UI��Ⱦģ�飬��render-gdi.dll����render-skia.dll�ṩ
	CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;	//ͼƬ����������imagedecoder - wid.dllģ���ṩ

																//��ʼ��UI��Ⱦģ��
	bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory);
	SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
	//��ʼ��ͼƬ���������ģ��
	bLoaded = pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));
	//Ϊ��Ⱦģ����������Ҫ���õ�ͼƬ����ģ��
	pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

	//����SOUIӦ�ó���ʵ��
	SApplication *theApp = new SApplication(pRenderFactory, hInstance);
	//��SApplicationϵͳ��ע�����ⲿ��չ�Ŀؼ���SkinObj��
	//.......
	//��DLL����ϵͳ��Դ
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
#if (RES_TYPE == 0)//���ļ�����
	CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
	if(!pResProvider->Init((LPARAM)_T("uires"), 0))
	{
		SASSERT(0);
		return 1;
	}
#elif (RES_TYPE==1)//��EXE��Դ����
	CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
	bLoaded = pResProvider->Init((WPARAM)hInstance, 0);
#elif (RES_TYPE==2)//��ZIP������
	bLoaded = pComMgr->CreateResProvider_ZIP((IObjRef**)&pResProvider);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));

	ZIPRES_PARAM param;
	param.ZipFile(pRenderFactory, _T("uires.zip"), "souizip");
	bLoaded = pResProvider->Init((WPARAM)&param, 0);
	SASSERT(bLoaded);
#endif

	//�����Ҫ�ڴ�����ʹ��R::id::namedid���ַ�ʽ��ʹ�ÿؼ�����Ҫ��һ�д��룺2016��2��2�գ�R::id::namedXmlID����uiresbuilder ����-h .\res\resource.h idtable ��3�����������ɵġ�
	theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);
	//��������IResProvider����SApplication����
	theApp->AddResProvider(pResProvider);

	//�������Ի�����ʾ
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

	//�ͷ�������������
	delete pComMgr;

	//ɾ���������
	OleUninitialize();
	return 0;
}