//stamp:074b7c502ac62db0
/*<------------------------------------------------------------------------------------------------->*/
/*该文件由uiresbuilder生成，请不要手动修改*/
/*<------------------------------------------------------------------------------------------------->*/
#pragma once
#include <res.mgr/snamedvalue.h>
#define ROBJ_IN_CPP \
namespace SOUI \
{\
    const _R R;\
    const _UIRES UIRES;\
}
namespace SOUI
{
	class _UIRES{
		public:
		class _UIDEF{
			public:
			_UIDEF(){
				XML_INIT = _T("UIDEF:XML_INIT");
			}
			const TCHAR * XML_INIT;
		}UIDEF;
		class _LAYOUT{
			public:
			_LAYOUT(){
				XML_MAINWND = _T("LAYOUT:XML_MAINWND");
				PAGE_LOGIN = _T("LAYOUT:PAGE_LOGIN");
			}
			const TCHAR * XML_MAINWND;
			const TCHAR * PAGE_LOGIN;
		}LAYOUT;
		class _values{
			public:
			_values(){
				string = _T("values:string");
				color = _T("values:color");
				skin = _T("values:skin");
			}
			const TCHAR * string;
			const TCHAR * color;
			const TCHAR * skin;
		}values;
		class _ICON{
			public:
			_ICON(){
				ICON_LOGO = _T("ICON:ICON_LOGO");
			}
			const TCHAR * ICON_LOGO;
		}ICON;
		class _layout{
			public:
			_layout(){
			}
		}layout;
		class _icon{
			public:
			_icon(){
			}
		}icon;
		class _imgx{
			public:
			_imgx(){
			}
		}imgx;
		class _image{
			public:
			_image(){
				avatars = _T("image:avatars");
				getpswback = _T("image:getpswback");
				head_mask = _T("image:head_mask");
				keyboard = _T("image:keyboard");
				login = _T("image:login");
				login2 = _T("image:login2");
				login_2dcode = _T("image:login_2dcode");
				login_border = _T("image:login_border");
				login_setting = _T("image:login_setting");
				register_cpp = _T("image:register");
				soui = _T("image:soui");
				user_list_closr = _T("image:user_list_closr");
			}
			const TCHAR * avatars;
			const TCHAR * getpswback;
			const TCHAR * head_mask;
			const TCHAR * keyboard;
			const TCHAR * login;
			const TCHAR * login2;
			const TCHAR * login_2dcode;
			const TCHAR * login_border;
			const TCHAR * login_setting;
			const TCHAR * register_cpp;
			const TCHAR * soui;
			const TCHAR * user_list_closr;
		}image;
	};
	const SNamedID::NAMEDVALUE namedXmlID[]={
		{L"btn_close",65539},
		{L"btn_login",65544},
		{L"btn_min",65540},
		{L"btn_setting",65541},
		{L"cbx_account",65543},
		{L"flash_bkgnd",65538},
		{L"img_avatar",65542},
		{L"tab_main",65536},
		{L"turn3d",65537}		};
	class _R{
	public:
		class _name{
		public:
		_name(){
			btn_close = namedXmlID[0].strName;
			btn_login = namedXmlID[1].strName;
			btn_min = namedXmlID[2].strName;
			btn_setting = namedXmlID[3].strName;
			cbx_account = namedXmlID[4].strName;
			flash_bkgnd = namedXmlID[5].strName;
			img_avatar = namedXmlID[6].strName;
			tab_main = namedXmlID[7].strName;
			turn3d = namedXmlID[8].strName;
		}
		 const wchar_t * btn_close;
		 const wchar_t * btn_login;
		 const wchar_t * btn_min;
		 const wchar_t * btn_setting;
		 const wchar_t * cbx_account;
		 const wchar_t * flash_bkgnd;
		 const wchar_t * img_avatar;
		 const wchar_t * tab_main;
		 const wchar_t * turn3d;
		}name;

		class _id{
		public:
		const static int btn_close	=	65539;
		const static int btn_login	=	65544;
		const static int btn_min	=	65540;
		const static int btn_setting	=	65541;
		const static int cbx_account	=	65543;
		const static int flash_bkgnd	=	65538;
		const static int img_avatar	=	65542;
		const static int tab_main	=	65536;
		const static int turn3d	=	65537;
		}id;

		class _string{
		public:
		const static int title	=	0;
		const static int ver	=	1;
		}string;

		class _color{
		public:
		const static int blue	=	0;
		const static int gray	=	1;
		const static int green	=	2;
		const static int red	=	3;
		const static int white	=	4;
		}color;

	};

#ifdef R_IN_CPP
	 extern const _R R;
	 extern const _UIRES UIRES;
#else
	 extern const __declspec(selectany) _R & R = _R();
	 extern const __declspec(selectany) _UIRES & UIRES = _UIRES();
#endif//R_IN_CPP
}
