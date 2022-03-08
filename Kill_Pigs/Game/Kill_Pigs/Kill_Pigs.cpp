#include"Kill_Pigs.h"
#include"../GameConfig/GameConfig.h"


CREATE_OBJECT(CKill_Pigs)
WINDOW_PARAM(PARAM_WND_POSITION_X,PARAM_WND_POSITION_Y,
PARAM_WND_WIDTH,PARAM_WND_HEIGH,PARAM_WND_TITILE)


CKill_Pigs::CKill_Pigs(){

}
CKill_Pigs::~CKill_Pigs(){

}
void CKill_Pigs::OnCreate(){
	::PlaySound("res\\back.wav", m_hIns, SND_LOOP | SND_ASYNC);
	m_back.InitBackGround(this->m_hIns,0,0);
	m_brid.InitBrid(this->m_hIns);
	m_wallbox.InitAllWall(this->m_hIns);
	m_pigbox.InitAllPig(this->m_hIns);
	m_boombox.InitAllBoom(this->m_hIns);
	SetTimer();
}
void CKill_Pigs::OnDraw(){
	//---------------������ˢ�ṹ��-----------------
	PAINTSTRUCT ps={0};
	//---------------��������DC-----------------
	HDC hdc = ::BeginPaint(m_hWnd,&ps);
	//-----------���������DC��Ҳ�Ǽ�����DC)----------
	HDC cacheDC = ::CreateCompatibleDC(hdc);
	//------------����������λͼ-------------------
	HBITMAP cachemap = ::CreateCompatibleBitmap(hdc , SIZE_BACKGROUND_WIDTH , SIZE_BACKGROUND_HEIGH);
	//------------ѡ��λͼ���������DC��
	::SelectObject(cacheDC,cachemap);
	//-------------��������DC�ļ�����DC------------
	HDC compDC = ::CreateCompatibleDC(cacheDC);

	//--------------λͼ�ŵ�������DC�в��Ѽ�����DC��������DC�� �������Show����-----------

	//---------��ʾ����-------------
	m_back.ShowBackGround(cacheDC,compDC);
	//---------��ʾ��----------------
	m_brid.ShowBrid(cacheDC,compDC);
	//---------��ʾ����ǽ----------
	m_wallbox.ShowAllWall(cacheDC,compDC);
	//----------��ʾ����------------
	m_pigbox.ShowAllPig(cacheDC,compDC);
	//----------��ʾը��--------------
	m_boombox.ShowAllBoom(cacheDC,compDC);
	//----------��ʾ��ը��ը��---------
	m_boombox.ShowAllBooming(cacheDC,compDC);
	//--------------�ӻ���DCһ���Դ���HDC�о��Ǵ����� �������������---------------------
	::BitBlt(hdc,0,0,SIZE_BACKGROUND_WIDTH,SIZE_BACKGROUND_HEIGH,cacheDC,0,0,SRCCOPY);
	//--------------ȫ��ɾ�� ����DC �����Ժͻ��� һ������λͼ---------------------------------
	//ɾ��������DC
	::DeleteDC(compDC);
	compDC=NULL;

	//ɾ��������λͼ
	::DeleteObject(cachemap);
	cachemap =NULL;

	//ɾ�������DC
	::DeleteDC(cacheDC);
	cacheDC=NULL;

	//������ˢ
	::EndPaint(m_hWnd , &ps);

}
void CKill_Pigs::OnKeyDown(WPARAM w){
	
}
#define RANGE_BEGIN_BOOM\
	list<CBoom*> :: iterator iteb = m_boombox.m_lstboom.begin();\
			while(iteb != m_boombox.m_lstboom.end()){
#define RANGE_EDN_BOOM\
	iteb++;\
				}
#define RANGE_BEGIN_PIG\
		list<CPig*> :: iterator itep = m_pigbox.m_lstpig.begin();\
		while(itep != m_pigbox.m_lstpig.end()){


#define RANGE_END_PIG\
		itep++;\
					}

#define RANGE_BEGIN_BOOMING\
		list<CBoom*> :: iterator itebing = m_boombox.m_lstbooming.begin();\
		while(itebing != m_boombox.m_lstbooming.end()){


#define RANGE_END_BOOMING\
		itebing++;\
					}

int m_bridhit1 = 0;
int m_bridhit2 = 0;
int m_bridhit3 = 0;
int m_bridhit4 = 0;

void CKill_Pigs::OnRun(WPARAM w){
	switch (w)
	{
	case TIMER_BRID_ID:
		{
			//�ж� VK_LEFT �Ƿ���
			if(::GetAsyncKeyState(VK_LEFT) && m_bridhit3 != 3){
				m_brid.MoveBrid(VK_LEFT,BRID_STEP);
			}
			if(::GetAsyncKeyState(VK_UP) && m_bridhit1 != 1){
				m_brid.MoveBrid(VK_UP,BRID_STEP);
			}
			if(::GetAsyncKeyState(VK_RIGHT) && m_bridhit4 != 4){
				m_brid.MoveBrid(VK_RIGHT,BRID_STEP);
			}
			if(::GetAsyncKeyState(VK_DOWN) && m_bridhit2 != 2){
				m_brid.MoveBrid(VK_DOWN,BRID_STEP);
			}		   			  					   
		}
		break;
	case TIMER_HIT_BAB_ID:
		{
			RANGE_BEGIN_BOOM
				if((*iteb)!= NULL)
					(*iteb)->MoveBoom((*iteb)->IsHitBrid(m_brid),BOOM_STEP);
			RANGE_EDN_BOOM	
		}
		break;
	case TIMER_HIT_BAP_ID:
		{
			bool booming = false;
			RANGE_BEGIN_BOOM//ѭ��ը��
				booming = false;
				if((*iteb)!= NULL)
				{
					RANGE_BEGIN_PIG//ѭ������
						booming = false;		//ѭ����ʼǰ���¸�ֵ
						if((*itep)!=NULL){
							if((*iteb)->IsHitPig((*itep)))//�ж��Ƿ���ײ
							{   
								m_boombox.m_lstbooming.push_back((*iteb));//����ըը����ӵ�booming����
								iteb = m_boombox.m_lstboom.erase(iteb);//ɾ��ԭ���Ľڵ�
								booming = true;
								itep = m_pigbox.m_lstpig.erase(itep);//ɾ��������Ľڵ�
								break; //��ʱ���� ��ֹiteָ��end��Ч�ڵ�
							}
						}
						//if(!booming){
					RANGE_END_PIG		//�����ը�ɹ��Ͳ��ظ�++���������
						//}
				}

				if(!booming){			//�����ը�ɹ��Ͳ��ظ�++ը��������
			RANGE_EDN_BOOM
				}
		}
		break;
	case TIMER_BOOMING_ID:
		{
			RANGE_BEGIN_BOOMING
				if((*itebing)){
					(*itebing)->~CBoom();
					itebing = m_boombox.m_lstbooming.erase(itebing);
					continue;
				}
			RANGE_END_BOOMING
		}
		break;

#define RANGE_WALL_BEGIN\
	list<CWall *>::iterator itew = m_wallbox.m_lstwall.begin();\
			while(itew !=  m_wallbox.m_lstwall.end()){

#define RANGE_WALL_END\
		itew++;\
			}

	case TIMER_HIT_WAB_ID:
		{
			 m_bridhit1 = 0;
			 m_bridhit2 = 0;
			 m_bridhit3 = 0;
			 m_bridhit4 = 0;
			 
				RANGE_WALL_BEGIN
					if(m_brid.m_y >= (*itew)->m_y && m_brid.m_y <= (*itew)->m_y+SIZE_WALL_HIGTH && m_brid.m_x+(SIZE_BOOM_HIGTH/2)>= (*itew)->m_x && m_brid.m_x+(SIZE_BOOM_HIGTH/2) <= (*itew)->m_x+SIZE_WALL_HIGTH)
						m_bridhit1 = 1;
					if(m_brid.m_y+SIZE_WALL_HIGTH >= (*itew)->m_y && m_brid.m_y+SIZE_WALL_HIGTH <= (*itew)->m_y+SIZE_WALL_HIGTH && m_brid.m_x+(SIZE_BOOM_HIGTH/2) >= (*itew)->m_x && m_brid.m_x+(SIZE_BOOM_HIGTH/2) <= (*itew)->m_x+SIZE_WALL_HIGTH)
						m_bridhit2 = 2;
					if(m_brid.m_y+(SIZE_BOOM_HIGTH/2) >= (*itew)->m_y && m_brid.m_y+(SIZE_BOOM_HIGTH/2) <= (*itew)->m_y+SIZE_BOOM_HIGTH && m_brid.m_x <= (*itew)->m_x+SIZE_BOOM_HIGTH && m_brid.m_x >= (*itew)->m_x)
						m_bridhit3 = 3;
					if(m_brid.m_y+(SIZE_BOOM_HIGTH/2) >= (*itew)->m_y && m_brid.m_y+(SIZE_BOOM_HIGTH/2) <= (*itew)->m_y+SIZE_BOOM_HIGTH && m_brid.m_x+SIZE_BOOM_HIGTH+10 <= (*itew)->m_x+SIZE_BOOM_HIGTH && m_brid.m_x+SIZE_BOOM_HIGTH+10 >=(*itew)->m_x)
						m_bridhit4 = 4;
				RANGE_WALL_END
		}
		break;

#define RANGE_WALL_BEGIN_BOOM\
	list<CWall *>:: iterator ite1   = m_wallbox.m_lstwall.begin();\
				list<CWall *>::	iterator ite   = m_wallbox.m_lstwall.begin();\
	while(ite != m_wallbox.m_lstwall.end()){

#define RANGE_WALL_END_BOOM\
		ite++;\
	}

#define RANGE_BEGIN_BOOM_TWO\
	list<CBoom*> :: iterator iteb2 = m_boombox.m_lstboom.begin();\
			while(iteb2 != m_boombox.m_lstboom.end()){

#define RANGE_EDN_BOOM_TWO\
	iteb2++;\
				}

	case TIMER_HIT_BAW_ID:
		{
			RANGE_BEGIN_BOOM_TWO
				if((*iteb2) != NULL)
					(*iteb2)->m_boomhit1 = 0;
					(*iteb2)->m_boomhit2 = 0;
					(*iteb2)->m_boomhit3 = 0;
					(*iteb2)->m_boomhit4 = 0;
				RANGE_WALL_BEGIN_BOOM			
					if((*iteb2)->m_x+(SIZE_BOOMING_WIDTH/2)>=(*ite)->m_x && (*iteb2)->m_x+(SIZE_BOOMING_WIDTH/2)<=(*ite)->m_x+SIZE_BOOMING_WIDTH && (*iteb2)->m_y <= (*ite)->m_y+SIZE_BOOM_HIGTH && (*iteb2)->m_y >= (*ite)->m_y)
						(*iteb2)->m_boomhit1 = 1;
					if((*iteb2)->m_x+(SIZE_BOOMING_WIDTH/2)>=(*ite)->m_x && (*iteb2)->m_x+(SIZE_BOOMING_WIDTH/2)<=(*ite)->m_x+SIZE_BOOMING_WIDTH && (*iteb2)->m_y + SIZE_BOOMING_WIDTH >= (*ite)->m_y && (*iteb2)->m_y + SIZE_BOOMING_WIDTH <= (*ite)->m_y+SIZE_BOOMING_WIDTH)
						(*iteb2)->m_boomhit2 = 2;
					if((*iteb2)->m_x <= (*ite)-> m_x+SIZE_BOOMING_WIDTH && (*iteb2)->m_x >= (*ite)->m_x && (*iteb2)->m_y + (SIZE_BOOMING_WIDTH/2) >= (*ite)->m_y && (*iteb2)->m_y + (SIZE_BOOMING_WIDTH/2)<= (*ite)->m_y+SIZE_BOOMING_WIDTH)
						(*iteb2)->m_boomhit3 = 3;
					if((*iteb2)->m_x +SIZE_BOOMING_WIDTH<= (*ite)->m_x+SIZE_BOOMING_WIDTH && (*iteb2)->m_x +SIZE_BOOMING_WIDTH >= (*ite)->m_x && (*iteb2)->m_y + (SIZE_BOOMING_WIDTH/2) >= (*ite)->m_y && (*iteb2)->m_y + (SIZE_BOOMING_WIDTH/2)<= (*ite)->m_y+SIZE_BOOMING_WIDTH )
						(*iteb2)->m_boomhit4 = 4;
				RANGE_WALL_END_BOOM
			RANGE_EDN_BOOM_TWO
		}
		break;
	case TIMER_DEATH_ID:
		{
			list<CPig*> ::iterator ite = m_pigbox.m_lstpig.begin();
			while(ite != m_pigbox.m_lstpig.end()){
				if(*ite != NULL)
				{
					if(m_brid.DeathBrid((*ite)))
						{
							::KillTimer(this->m_hWnd,TIMER_DEATH_ID);
							GameOver();
							MessageBox(this->m_hWnd,"you are dead","��ʾ",MB_OK);					
						}
				}
				ite++;
			}
		}
		break;
	case TIMER_WIN_ID:
		{
			if(m_pigbox.m_lstpig.empty()){
				::KillTimer(this->m_hWnd,TIMER_WIN_ID);
				MessageBox(this->m_hWnd,"YOU WIN!","��ʾ",MB_OK);
				GameOver();
			}
		}
		break;
	default:
		break;
	}
	//�κ�WPARAM��Ϣ���ᴥ����ʱ�� ������Ч��ˢ���ػ�
	RECT rect={0,0,SIZE_BACKGROUND_WIDTH,SIZE_BACKGROUND_HEIGH};
	::InvalidateRect(this->m_hWnd,&rect,FALSE);
}

void CKill_Pigs::GameOver(){
	//���ƶ���ʱ��
	::KillTimer(this->m_hWnd,TIMER_BRID_ID);
	//��ʱ���ը������ײ��
	::KillTimer(this->m_hWnd,TIMER_HIT_BAB_ID);
	//Kill���ը������ײ��
	::KillTimer(this->m_hWnd,TIMER_HIT_BAP_ID);
	//Kill���ը���Ƿ�ը ɾ����ըͼƬ
	::KillTimer(this->m_hWnd,TIMER_BOOMING_ID);
	//Kill������Ƿ���ǽ����ײ
	::KillTimer(this->m_hWnd,TIMER_HIT_WAB_ID);
	//Kill���ը���Ƿ���ǽ����ײ
	::KillTimer(this->m_hWnd,TIMER_HIT_BAW_ID);
	//Kill������Ƿ�����
	
	
	//�����˳���Ϣ
	PostMessage(this->m_hWnd,WM_DESTROY,0,0);
}
void CKill_Pigs::SetTimer(){
	//���ƶ���ʱ��
	::SetTimer(this->m_hWnd,TIMER_BRID_ID,TIMER_BRID_INT,NULL);
	//��ʱ���ը������ײ��
	::SetTimer(this->m_hWnd,TIMER_HIT_BAB_ID,TIMER_HIT_BAB_INT,NULL);
	//��ʱ���ը������ײ��
	::SetTimer(this->m_hWnd,TIMER_HIT_BAP_ID,TIMER_HIT_BAP_INT,NULL);
	//��ʱ���ը���Ƿ�ը ɾ����ըͼƬ
	::SetTimer(this->m_hWnd,TIMER_BOOMING_ID,TIMER_BOOMING_INT,NULL);
	//��ʱ������Ƿ���ǽ����ײ
	::SetTimer(this->m_hWnd,TIMER_HIT_WAB_ID,TIMER_HIT_WAB_INT,NULL);
	//��ʱ���ը���Ƿ���ǽ����ײ
	::SetTimer(this->m_hWnd,TIMER_HIT_BAW_ID,TIMER_HIT_BAW_INT,NULL);
	//��ʱ������Ƿ�����
	::SetTimer(this->m_hWnd,TIMER_DEATH_ID,TIMER_DEATH_INT,NULL);
	//��ʱ�����Ϸ�Ƿ����
	::SetTimer(this->m_hWnd,TIMER_WIN_ID,TIMER_WIN_INT,NULL);
}