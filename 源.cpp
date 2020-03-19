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

