#pragma once
#include<windows.h>


class CGameApp{
public:
	HINSTANCE m_hIns;  //ʵ�����
	HWND m_hWnd;       //���ھ��
public:
	void SetHandle(HINSTANCE hins,HWND hwnd){
		m_hIns =hins;
		m_hWnd = hwnd;
	}

public:
	CGameApp(){
		m_hIns = NULL;
		m_hWnd = NULL;
	}
	virtual ~CGameApp(){}
public:
	//�޷��������ⲿ���� "public: static class CGameApp * __cdecl CGameApp::GetChildObject(void)"
	static CGameApp* GetChildObject();
public:
	//case WM_CREATE: //���ڴ�����Ϣ
	virtual void OnCreate(){};


	//case WM_PAINT:  //�ػ���Ϣ
	virtual void OnDraw(){};


	//case WM_TIMER:   //��ʱ������Ҫ�������������ֶ���Ӷ�ʱ�������ô������
	virtual void OnRun(WPARAM){}


	//case WM_KEYDOWN:  //���̰��´�����Ϣ
	virtual void OnKeyDown(WPARAM){}


	//case WM_KEYUP:  //����̧�𴥷���Ϣ
	virtual void OnKeyUp(WPARAM){}


	//case WM_LBUTTONDOWN: //���������´�����Ϣ
	virtual void OnLButtonDown(POINT &po){}


	//case WM_LBUTTONUP: //������̧�𴥷���Ϣ
	virtual void OnLButtonUp(POINT &po){}


	//case WM_MOUSEMOVE:  //����ƶ�
	virtual void OnMouseMove(POINT &po){}


};

#define CREATE_OBJECT(CHILD_CLASS)\
CGameApp* CGameApp::GetChildObject(){\
	return new CHILD_CLASS;\
}

#define WINDOW_PARAM(PARAM_X,PARAM_Y,PARAM_WIDTH,PARAM_HEIGH,PARAM_TITLE)\
	int nx=PARAM_X;\
	int ny=PARAM_Y;\
	int nwidth=PARAM_WIDTH;\
	int nheigh=PARAM_HEIGH;\
	const CHAR * strTitle=PARAM_TITLE;