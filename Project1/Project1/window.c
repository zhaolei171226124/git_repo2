#include <windows.h>//底层实现窗口的头文件


//6.处理消息（窗口过程）
	//消息所属的窗口句柄//具体的消息名称 WM_XXXX消息名//键盘附加消息 //鼠标附加消息
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//DestroyWindow 发送另一个消息 WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN://鼠标左键按下操作
	{
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		char buf[1024];
		wsprintf(buf,TEXT("x=%d,y=%d"),xPos,yPos);
		MessageBox(hwnd, buf, TEXT("鼠标左键按下"), MB_OK);
		break;
	}
	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘按下"), MB_OK);
		break;
	case WM_PAINT: 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc,100,100,TEXT("HELLO"),strlen("HELLO"));
		EndPaint(hwnd, &ps);
	}
		
	}
	//返回值用默认处理方式
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//WINAPI 代表_stdcall 参数的传递顺序，从右到左 以此入栈。并且在函数返回前清空堆栈
int WINAPI WinMain(
	HINSTANCE hInstance,//应用程序实例句柄
	HINSTANCE hPrevInstance,//上一个应用程序句柄，在win32环境下，参数一般为NULL，不起作用
	LPSTR lpCmdLine,////char * argv[]
	int nShowCmd) //显示命令 最大化最小化正常
{
	//1.设计窗口
	//2.注册窗口
	//3.创建窗口
	//4.显示和更新窗口
	//5.通过循环取消息
	//6.处理消息（窗口过程）

	//1.设计窗口
	WNDCLASS wc;
	wc.cbClsExtra = 0;//类的额外内存
	wc.cbWndExtra = 0;//窗口的额外内存
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//设置背景
	wc.hCursor = LoadCursor(NULL,IDC_HAND);//设置光标，如果第一个参数为NULL表示使用系统提供的光标
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);//设置图标
	wc.hInstance = hInstance;//应用程序的实例句柄 传入WinMain中的形参即可
	wc.lpfnWndProc = WindowProc;   //窗口过程 回调函数
	wc.lpszClassName =TEXT("WIN");//指定窗口类名称
	wc.lpszMenuName = NULL;//菜单名称
	wc.style = 0;//显示风格 0代表默认风格

	//2.注册窗口
	RegisterClass(&wc);

	//3.创建窗口
	/*
	lpClassName 类名, lpWindowName 窗口名, dwStyle 用WS_OVERLAPPEDWINDOW 风格, x 显示坐标, y 显示坐标,
		nWidth 宽度, nHeight 高度, hWndParent 父窗口, hMenu 菜单, hInstance 实例句柄, lpParam 附加值
	*/
	HWND hWnd=CreateWindow(wc.lpszClassName, TEXT("WINDOWS"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	
	//4.显示和更新窗口
	ShowWindow(hWnd,SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	
	//5.通过循环取消息
	/*
	HWND        hwnd;主窗口句柄
    UINT        message;具体消息名称
    WPARAM      wParam;附加消息 键盘消息
    LPARAM      lParam;附加消息 鼠标消息 判断左右键
    DWORD       time;消息产生时间
    POINT       pt;附加消息 鼠标消息 点击的坐标点
	*/
	MSG msg;
	while (1)
	{
		/*GetMessage参数
	    _Out_ LPMSG lpMsg,消息
		_In_opt_ HWND hWnd,捕获窗口 填NULL代表捕获所有窗口
		_In_ UINT wMsgFilterMin,最小和最大的过滤消息 一般填入0
		_In_ UINT wMsgFilterMax 填0代表捕获所有消息
		*/
		if (GetMessage(&msg,NULL,0,0)==FALSE)
		{
			break;
		}
		//翻译消息
		TranslateMessage(&msg);
		//不为FALSE 分发消息
		DispatchMessage(&msg);
	}

	


	return 0;
}
