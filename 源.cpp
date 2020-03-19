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
	for (int i = 0; i < ROW + 2; i++)//四周辅助区
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
	{  //埋雷
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
					{   //遍历九宫格
						if (map[ii][jj] == -1)
						{
							map[i][j]++;//数字   本身就是0 加加得到结果直接为周围雷数目 0-8
						}
					}
				}
			}
		}
	}
	//加密
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
			{     //雷
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[9]);
			}
			if (map[i][j] >= 0 && map[i][j] < 9)
			{    //数字
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);
			}
			if (map[i][j] > 18 && map[i][j] < 29)
			{   //加密
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);
			}
			if (map[i][j] > 30)
			{   //标记
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);
			}
		}
		printf("\n");
	}
}

void Open(int r, int c) {//PlayGam 辅助函数 
	map[r][c] -= 20;
	num++;
	for (int i = r - 1; i < r + 2; i++)
	{
		for (int j = c - 1; j < c + 2; j++)
		{   //遍历九宫格
			if ((i >= 1 && i <= ROW && j >= 1 && j <= COL)&&(map[i][j] > 19 && map[i][j] < 29))
			{  //在游戏区并且加密
					if (map[i][j] != 20)//不是0
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
	MOUSEMSG msg = { 0 };//定义鼠标消息
	msg = GetMouseMsg();//获取鼠标信息

	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN://鼠标左键
		r = msg.y / SIZE + 1;
		c = msg.x / SIZE + 1;//点击获取元素
		if (map[r][c] > 18 && map[r][c] < 29)//加密格子
		{
			if (map[r][c] == 20)//加密的0
			{
				Open(r, c);//把0全部打开
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

	case WM_RBUTTONDOWN://鼠标右键
		r = msg.y / SIZE + 1;
		c = msg.x / SIZE + 1;
		if (map[r][c] > 18 && map[r][c] < 29)
		{//标记
			map[r][c] += 100;
			//PlaySound(L"rightClick.wav", NULL, SND_ASYNC | SND_FILENAME);
			//PlaySound(L"./rightClick.wav", NULL, SND_ASYNC | SND_FILENAME);
		}
		else if (map[r][c] > 30)
		{//取消
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
	    //HWND hwnd = initgraph(ROW * SIZE, COL * SIZE, SHOWCONSOLE);//作弊
	    HWND hwnd = initgraph(ROW * SIZE, COL * SIZE);
		LoadImage();
		PlaySound(L"bgm/岸部眞明 - 奇迹の山.wav", NULL,SND_LOOP| SND_FILENAME || SND_ASYNC);

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
					MessageBox(hwnd, L"你输了", L"", MB_OK);//
					break;
				}
				if (LEI + num == ROW * COL)//雷数+空白 =  所有格子
				{
					Show();
					ShowMap();
					MessageBox(hwnd, L"棒", L"", MB_OK);
					num = 0;//赢了重置num
					break;
				}
			}
			if (MessageBox(hwnd, L"再来一次？", L"", MB_RETRYCANCEL) == IDCANCEL)
			{    // 重试 0  取消 1
				break;
			}
		}
	return 0;
}

/*
  function MessageBox(hWnd: HWND; Text, Caption: PChar; Type: Word): Integer;
　hWnd：对话框父窗口句柄，对话框显示在Delphi窗体内，可使用窗体的Handle属性，否则可用0，使其直接作为桌面窗口的子窗口。
　Text：欲显示的信息字符串。
　Caption：对话框标题字符串。
　Type：对话框类型常量。
　该函数的返回值为整数，用于对话框按钮的识别。
　2、类型常量
　对话框的类型常量可由按钮组合、缺省按钮、显示图标、运行模式四种常量组合而成。
　（1）按钮组合常量
　MB_OK = $00000000;　　　　　　　　　//一个确定按钮
　MB_OKCANCEL = $00000001;　　　　　　//一个确定按钮，一个取消按钮
　MB_ABORTRETRYIGNORE = $00000002;　　//一个异常终止按钮，一个重试按钮，一个忽略按钮
　MB_YESNOCANCEL = $00000003;　　　　 //一个是按钮，一个否按钮，一个取消按钮
　MB_YESNO = $00000004;　　　　　　　 //一个是按钮，一个否按钮
　MB_RETRYCANCEL = $00000005;　　　　 //一个重试按钮，一个取消按钮
　（2）缺省按钮常量
　MB_DEFBUTTON1 = $00000000;　　　　　//第一个按钮为缺省按钮
　MB_DEFBUTTON2 = $00000100;　　　　　//第二个按钮为缺省按钮
　MB_DEFBUTTON3 = $00000200;　　　　　//第三个按钮为缺省按钮
　MB_DEFBUTTON4 = $00000300;　　　　　//第四个按钮为缺省按钮
　（3）图标常量
　MB_ICONHAND = $00000010;　　　　　　　 //“×”号图标
　MB_ICONQUESTION = $00000020;　　　　　 //“？”号图标
　MB_ICONEXCLAMATION = $00000030;　　　　//“！”号图标
　MB_ICONASTERISK = $00000040;　　　　　 //“i”图标
　MB_USERICON = $00000080;　　　　　　　 //用户图标
　MB_ICONWARNING = MB_ICONEXCLAMATION;　 //“！”号图标
　MB_ICONERROR = MB_ICONHAND;　　　　　　//“×”号图标
　MB_ICONINFORMATION = MB_ICONASTERISK;　//“i”图标
　MB_ICONSTOP = MB_ICONHAND;　　　　　　 //“×”号图标
　（4）运行模式常量
　MB_APPLMODAL = $00000000;　　　　//应用程序模式，在未结束对话框前也能切换到另一应用程序
　MB_SYSTEMMODAL = $00001000;　　　//系统模式，必须结束对话框后，才能做其他操作
　MB_TASKMODAL = $00002000;　　　　//任务模式，在未结束对话框前也能切换到另一应用程序
　MB_HELP = $00004000;　　　　　　 //Help Button
　3、函数返回值
　0　　　　　　　　　　　 //对话框建立失败
　IDOK = 1　　　　　　　　//按确定按钮
　IDCANCEL = 2　　　　　　//按取消按钮
　IDABOUT = 3　　　　　　 //按异常终止按钮
　IDRETRY = 4　　　　　　 //按重试按钮
　IDIGNORE = 5　　　　　　//按忽略按钮
　IDYES = 6　　　　　　　 //按是按钮
　IDNO = 7　　　　　　　　//按否按钮
二 用法

1. MessageBox("这是一个最简单的消息框！");
2. MessageBox("这是一个有标题的消息框！","标题");
3. MessageBox("这是一个确定 取消的消息框！","标题", MB_OKCANCEL );
4. MessageBox("这是一个警告的消息框！","标题", MB_ICONEXCLAMATION );
5. MessageBox("这是一个两种属性的消息框！","标题",
			  MB_ICONEXCLAMATION|MB_OKCANCEL );
6. if(MessageBox("一种常用的应用","标题
			  " ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
		 return;
注意：
以上消息框的用法是在CWnd的子类中的应用，如果不是，则要MessageBox(NULL,"ddd","ddd",MB_OK); 
或MessageBox(hWnd,"ddd","ddd",MB_OK); hWnd为某窗口的句柄，或者直接用AfxMessageBox。

二、在MessageBox中显示变量的值

	 CString string;

	  string.format("%d%s",m_age, m_address); //将变量组装到字符串中

	   MessageBox(string,"消息框标题",消息框类型);
*/