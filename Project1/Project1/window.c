#include <windows.h>//�ײ�ʵ�ִ��ڵ�ͷ�ļ�


//6.������Ϣ�����ڹ��̣�
	//��Ϣ�����Ĵ��ھ��//�������Ϣ���� WM_XXXX��Ϣ��//���̸�����Ϣ //��긽����Ϣ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);//DestroyWindow ������һ����Ϣ WM_DESTROY
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN://���������²���
	{
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		char buf[1024];
		wsprintf(buf,TEXT("x=%d,y=%d"),xPos,yPos);
		MessageBox(hwnd, buf, TEXT("����������"), MB_OK);
		break;
	}
	case WM_KEYDOWN:
		MessageBox(hwnd, TEXT("���̰���"), TEXT("���̰���"), MB_OK);
		break;
	case WM_PAINT: 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc,100,100,TEXT("HELLO"),strlen("HELLO"));
		EndPaint(hwnd, &ps);
	}
		
	}
	//����ֵ��Ĭ�ϴ���ʽ
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//WINAPI ����_stdcall �����Ĵ���˳�򣬴��ҵ��� �Դ���ջ�������ں�������ǰ��ն�ջ
int WINAPI WinMain(
	HINSTANCE hInstance,//Ӧ�ó���ʵ�����
	HINSTANCE hPrevInstance,//��һ��Ӧ�ó���������win32�����£�����һ��ΪNULL����������
	LPSTR lpCmdLine,////char * argv[]
	int nShowCmd) //��ʾ���� �����С������
{
	//1.��ƴ���
	//2.ע�ᴰ��
	//3.��������
	//4.��ʾ�͸��´���
	//5.ͨ��ѭ��ȡ��Ϣ
	//6.������Ϣ�����ڹ��̣�

	//1.��ƴ���
	WNDCLASS wc;
	wc.cbClsExtra = 0;//��Ķ����ڴ�
	wc.cbWndExtra = 0;//���ڵĶ����ڴ�
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ñ���
	wc.hCursor = LoadCursor(NULL,IDC_HAND);//���ù�꣬�����һ������ΪNULL��ʾʹ��ϵͳ�ṩ�Ĺ��
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);//����ͼ��
	wc.hInstance = hInstance;//Ӧ�ó����ʵ����� ����WinMain�е��βμ���
	wc.lpfnWndProc = WindowProc;   //���ڹ��� �ص�����
	wc.lpszClassName =TEXT("WIN");//ָ������������
	wc.lpszMenuName = NULL;//�˵�����
	wc.style = 0;//��ʾ��� 0����Ĭ�Ϸ��

	//2.ע�ᴰ��
	RegisterClass(&wc);

	//3.��������
	/*
	lpClassName ����, lpWindowName ������, dwStyle ��WS_OVERLAPPEDWINDOW ���, x ��ʾ����, y ��ʾ����,
		nWidth ���, nHeight �߶�, hWndParent ������, hMenu �˵�, hInstance ʵ�����, lpParam ����ֵ
	*/
	HWND hWnd=CreateWindow(wc.lpszClassName, TEXT("WINDOWS"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	
	//4.��ʾ�͸��´���
	ShowWindow(hWnd,SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	
	//5.ͨ��ѭ��ȡ��Ϣ
	/*
	HWND        hwnd;�����ھ��
    UINT        message;������Ϣ����
    WPARAM      wParam;������Ϣ ������Ϣ
    LPARAM      lParam;������Ϣ �����Ϣ �ж����Ҽ�
    DWORD       time;��Ϣ����ʱ��
    POINT       pt;������Ϣ �����Ϣ ����������
	*/
	MSG msg;
	while (1)
	{
		/*GetMessage����
	    _Out_ LPMSG lpMsg,��Ϣ
		_In_opt_ HWND hWnd,���񴰿� ��NULL���������д���
		_In_ UINT wMsgFilterMin,��С�����Ĺ�����Ϣ һ������0
		_In_ UINT wMsgFilterMax ��0������������Ϣ
		*/
		if (GetMessage(&msg,NULL,0,0)==FALSE)
		{
			break;
		}
		//������Ϣ
		TranslateMessage(&msg);
		//��ΪFALSE �ַ���Ϣ
		DispatchMessage(&msg);
	}

	


	return 0;
}
