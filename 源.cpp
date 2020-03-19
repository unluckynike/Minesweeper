#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#define ROW 10
#define COL 10
#define LEI 25
#define SIZE 50

int map[ROW+2][COL+2];
int num = 0;
IMAGE img[12];

void LoadImage() {
	loadimage(&img[0], L"img/0.jpg", SIZE, SIZE);
	loadimage(&img[1], L"img/1.jpg", SIZE, SIZE);
	loadimage(&img[2], L"img/2.jpg", SIZE, SIZE);
	loadimage(&img[3], L"img/3.jpg", SIZE, SIZE);
	loadimage(&img[4], L"img/4.jpg", SIZE, SIZE);
	loadimage(&img[5], L"img/5.jpg", SIZE, SIZE);
	loadimage(&img[6], L"img/6.jpg", SIZE, SIZE);
	loadimage(&img[7], L"img/7.jpg", SIZE, SIZE);
	loadimage(&img[8], L"img/8.jpg", SIZE, SIZE);
	loadimage(&img[9], L"img/9.jpg", SIZE, SIZE);
	loadimage(&img[10], L"img/10.jpg", SIZE, SIZE);
	loadimage(&img[11], L"img/11.jpg", SIZE, SIZE);
}

void InitGame() {
	//mciSendString(L"open ./start.mp3", 0, 0, 0);
	//mciSendString(L"play ./start.mp3", 0, 0, 0);
	srand(time(NULL));
	for (int i = 0; i < ROW + 2; i++)//���ܸ�����
	{
		for (int j = 0; j < COL + 2; j++)
		{
			map[i][j] = 0;
		}
	}
	/*for (int i = 0; i < ROW + 2; i++)
        {
	      map[0][i] = 0;
	      map[ROW + 2][i] = 0;
         }
     for (int j = 0; j < COL + 2; j++)
          {
	         map[j][0] = 0;
	         map[j][COL + 2] = 0;
          }*/
	int R, C;
	for (int i = 0; i < LEI;)
	{  //����
		R = rand() % ROW + 1;
		C = rand() % COL + 1;
		if (map[R][C] == 0 )
		{
			map[R][C] = -1;
			i++;
		}
    }
	for (int i = 1; i < ROW + 1; i++)
	{
		for (int j = 1; j < COL + 1; j++)
		{
			if (map[i][j] == 0)
			{
				for (int ii = i - 1; ii < i + 2; ii++)
				{
					for (int jj = j - 1; jj < j + 2; jj++)
					{   //�����Ź���
						if (map[ii][jj] == -1)
						{
							map[i][j]++;//����   �������0 �Ӽӵõ����ֱ��Ϊ��Χ����Ŀ 0-8
						}
					}
				}
			}
		}
	}
	//����
	for (int i = 1; i < ROW + 1; i++)
	{
		for(int j = 1; j < COL + 1; j++)
		{
			map[i][j] += 20;
		}
	}
}

void ShowMap() {
	system("cls");
	for (int i = 0; i < ROW + 2; i++)
	{
		for (int j = 0; j < COL + 2; j++)
		{
			printf("%2d ", map[i][j]);
		}
		printf("\n");
	}

	for (int i = 1; i < ROW + 1; i++)
	{
		for (int j = 1; j < COL + 1; j++)
		{
			if (map[i][j] == -1)
			{     //��
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[9]);
			}
			if (map[i][j] >= 0 && map[i][j] < 9)
			{    //����
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);
			}
			if (map[i][j] > 18 && map[i][j] < 29)
			{   //����
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);
			}
			if (map[i][j] > 30)
			{   //���
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);
			}
		}
		printf("\n");
	}
}

void Open(int r, int c) {//PlayGam �������� 
	map[r][c] -= 20;
	num++;
	for (int i = r - 1; i < r + 2; i++)
	{
		for (int j = c - 1; j < c + 2; j++)
		{   //�����Ź���
			if ((i >= 1 && i <= ROW && j >= 1 && j <= COL)&&(map[i][j] > 19 && map[i][j] < 29))
			{  //����Ϸ�����Ҽ���
					if (map[i][j] != 20)//����0
					{
						map[i][j] -= 20;
						num++;
					}
					else
					{
						Open(i, j);
					}
			}
		}
	}
}

int PlayGame() {
	int r, c;
	MOUSEMSG msg = { 0 };//���������Ϣ
	msg = GetMouseMsg();//��ȡ�����Ϣ

	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN://������
		r = msg.y / SIZE + 1;
		c = msg.x / SIZE + 1;//�����ȡԪ��
		if (map[r][c] > 18 && map[r][c] < 29)//���ܸ���
		{
			if (map[r][c] == 20)//���ܵ�0
			{
				Open(r, c);//��0ȫ����
				//num++;
				//PlaySound(L"search.wav", NULL, SND_ASYNC || SND_FILENAME);
			}
			else
			{
				map[r][c] -= 20;
				num++;
			}
		}   
		return map[r][c];
		break;

	case WM_RBUTTONDOWN://����Ҽ�
		r = msg.y / SIZE + 1;
		c = msg.x / SIZE + 1;
		if (map[r][c] > 18 && map[r][c] < 29)
		{//���
			map[r][c] += 100;
			//PlaySound(L"rightClick.wav", NULL, SND_ASYNC | SND_FILENAME);
			//PlaySound(L"./rightClick.wav", NULL, SND_ASYNC | SND_FILENAME);
		}
		else if (map[r][c] > 30)
		{//ȡ��
			map[r][c] -= 100;
			//PlaySound(L"click.wav", NULL, SND_ASYNC | SND_FILENAME);
			//PlaySound(L"./click.wav", NULL, SND_ASYNC | SND_FILENAME);
		}
		break;
		return 0;
	}
}

void Show() {
	for (int i = 1; i < ROW + 1; i++)
	{
		for (int j = 1; j < COL + 1; j++)
		{
			map[i][j] -= 20;
		}
	}
}
int main() {
	    system("color 3f");
		system("mode con cols=78 lines=45");
	    //HWND hwnd = initgraph(ROW * SIZE, COL * SIZE, SHOWCONSOLE);//����
	    HWND hwnd = initgraph(ROW * SIZE, COL * SIZE);
		LoadImage();
		PlaySound(L"bgm/�����w�� - �漣��ɽ.wav", NULL,SND_LOOP| SND_FILENAME || SND_ASYNC);

		while (1)
		{
			InitGame();
			while (1)
			{
				ShowMap();
				if (PlayGame() == -1)
				{
					Show();
					ShowMap();
					MessageBox(hwnd, L"������", L"", MB_OK);//
					break;
				}
				if (LEI + num == ROW * COL)//����+�հ� =  ���и���
				{
					Show();
					ShowMap();
					MessageBox(hwnd, L"��", L"", MB_OK);
					num = 0;//Ӯ������num
					break;
				}
			}
			if (MessageBox(hwnd, L"����һ�Σ�", L"", MB_RETRYCANCEL) == IDCANCEL)
			{    // ���� 0  ȡ�� 1
				break;
			}
		}
	return 0;
}

/*
  function MessageBox(hWnd: HWND; Text, Caption: PChar; Type: Word): Integer;
��hWnd���Ի��򸸴��ھ�����Ի�����ʾ��Delphi�����ڣ���ʹ�ô����Handle���ԣ��������0��ʹ��ֱ����Ϊ���洰�ڵ��Ӵ��ڡ�
��Text������ʾ����Ϣ�ַ�����
��Caption���Ի�������ַ�����
��Type���Ի������ͳ�����
���ú����ķ���ֵΪ���������ڶԻ���ť��ʶ��
��2�����ͳ���
���Ի�������ͳ������ɰ�ť��ϡ�ȱʡ��ť����ʾͼ�ꡢ����ģʽ���ֳ�����϶��ɡ�
����1����ť��ϳ���
��MB_OK = $00000000;������������������//һ��ȷ����ť
��MB_OKCANCEL = $00000001;������������//һ��ȷ����ť��һ��ȡ����ť
��MB_ABORTRETRYIGNORE = $00000002;����//һ���쳣��ֹ��ť��һ�����԰�ť��һ�����԰�ť
��MB_YESNOCANCEL = $00000003;�������� //һ���ǰ�ť��һ����ť��һ��ȡ����ť
��MB_YESNO = $00000004;�������������� //һ���ǰ�ť��һ����ť
��MB_RETRYCANCEL = $00000005;�������� //һ�����԰�ť��һ��ȡ����ť
����2��ȱʡ��ť����
��MB_DEFBUTTON1 = $00000000;����������//��һ����ťΪȱʡ��ť
��MB_DEFBUTTON2 = $00000100;����������//�ڶ�����ťΪȱʡ��ť
��MB_DEFBUTTON3 = $00000200;����������//��������ťΪȱʡ��ť
��MB_DEFBUTTON4 = $00000300;����������//���ĸ���ťΪȱʡ��ť
����3��ͼ�곣��
��MB_ICONHAND = $00000010;�������������� //��������ͼ��
��MB_ICONQUESTION = $00000020;���������� //��������ͼ��
��MB_ICONEXCLAMATION = $00000030;��������//��������ͼ��
��MB_ICONASTERISK = $00000040;���������� //��i��ͼ��
��MB_USERICON = $00000080;�������������� //�û�ͼ��
��MB_ICONWARNING = MB_ICONEXCLAMATION;�� //��������ͼ��
��MB_ICONERROR = MB_ICONHAND;������������//��������ͼ��
��MB_ICONINFORMATION = MB_ICONASTERISK;��//��i��ͼ��
��MB_ICONSTOP = MB_ICONHAND;������������ //��������ͼ��
����4������ģʽ����
��MB_APPLMODAL = $00000000;��������//Ӧ�ó���ģʽ����δ�����Ի���ǰҲ���л�����һӦ�ó���
��MB_SYSTEMMODAL = $00001000;������//ϵͳģʽ����������Ի���󣬲�������������
��MB_TASKMODAL = $00002000;��������//����ģʽ����δ�����Ի���ǰҲ���л�����һӦ�ó���
��MB_HELP = $00004000;������������ //Help Button
��3����������ֵ
��0���������������������� //�Ի�����ʧ��
��IDOK = 1����������������//��ȷ����ť
��IDCANCEL = 2������������//��ȡ����ť
��IDABOUT = 3������������ //���쳣��ֹ��ť
��IDRETRY = 4������������ //�����԰�ť
��IDIGNORE = 5������������//�����԰�ť
��IDYES = 6�������������� //���ǰ�ť
��IDNO = 7����������������//����ť
�� �÷�

1. MessageBox("����һ����򵥵���Ϣ��");
2. MessageBox("����һ���б������Ϣ��","����");
3. MessageBox("����һ��ȷ�� ȡ������Ϣ��","����", MB_OKCANCEL );
4. MessageBox("����һ���������Ϣ��","����", MB_ICONEXCLAMATION );
5. MessageBox("����һ���������Ե���Ϣ��","����",
			  MB_ICONEXCLAMATION|MB_OKCANCEL );
6. if(MessageBox("һ�ֳ��õ�Ӧ��","����
			  " ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
		 return;
ע�⣺
������Ϣ����÷�����CWnd�������е�Ӧ�ã�������ǣ���ҪMessageBox(NULL,"ddd","ddd",MB_OK); 
��MessageBox(hWnd,"ddd","ddd",MB_OK); hWndΪĳ���ڵľ��������ֱ����AfxMessageBox��

������MessageBox����ʾ������ֵ

	 CString string;

	  string.format("%d%s",m_age, m_address); //��������װ���ַ�����

	   MessageBox(string,"��Ϣ�����",��Ϣ������);
*/