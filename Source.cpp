#include<Windows.h>
#include<graphics.h>
//#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string.h>
#include<ctime>
using namespace std;

int sc,yyyy = getmaxheight() - 100, xxxx = getmaxheight() - 100, cx, cy, choic = 0, ennd = 0, pause = 0, score = 0, choicc = 0, semaphore = 1, scsema = 1,dl;
double bx = xxxx / 10.0, by = yyyy / 10.0;
int data[10][10];
int col,le,ccount;

void start();
void help();
void wait()
{
	while (semaphore <= 0);
	while (semaphore <= 0);
	semaphore--;
}
void rel()
{
	semaphore++;
}
void wait1()
{
	while (scsema <= 0);
	while (scsema <= 0);
	scsema--;
}
void rel1()
{
	scsema++;
}
void create_block(int x, int y,int i)
{
//	wait1();
//	cout << ccount <<"displaying "<<i<< endl;
	x++;
	//cout << "over=" << ennd << " " << ccount << endl;
	if (i == 15)
	{
		ccount++;
	}
	else
	{
		ccount--;
		col %= 15;
		i = (14-(i+col-2))%15;
		//cout << "i=" << i << endl;
	}
	int arr[8];
	arr[0] = by*y;
	arr[1] = bx*x;
	arr[2] = by*y + by;
	arr[3] = bx*x;
	arr[4]=by*y+by;
	arr[5]=bx*x+bx;
	arr[6]=by*y;
	arr[7]=bx*x+bx;
	arr[0] += 5;
	arr[1] += 5;
	arr[2] -= 5;
	arr[3] += 5;
	arr[4] -= 5;
	arr[5] -= 5;
	arr[6] += 5;
	arr[7] -= 5;
	if (i == 15)
	{
		arr[0] -= 3;
		arr[1] -= 3;
		arr[2] += 3;
		arr[3] -= 3;
		arr[4] += 3;
		arr[5] += 3;
		arr[6] -= 3;
		arr[7] += 3;
	}
//	cout << "waitinggggg " << semaphore << endl;
	wait();
	//cout << "entered???????";
	setfillstyle(1, i);
	setcolor(i);
	fillpoly(4, arr);
	//fillpoly()
	rel();
	//cout << "came outt....";
	//static int  count;
	//count++;
//	for (int a = 0; a < 9; a++)
	//{
	//	for (int b = 0; b < 10; b++)
	//	{
	//		cout << data[a][b] << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//char c;
//	cin >> c;
//	if (count == 5)
//	{
//	//	Sleep(800);
//		count = 0;
//	}
//	rel1();
	if (i == 15)
	{
		data[x - 1][y] = 0;
	}
	else
	{
		data[x - 1][y] = 1;
	}
}
void create_error_block(int x, int y)
{
//	cout << "entered";
//	wait1();
	//cout << "waiting";
	create_block(x , y, 2);
	data[x][y] = 1;
	if (x < 8)
	{
		if (data[x + 1][y] == 1)
			ccount--;
		wait1();
		create_block(x + 1, y, 2);
		rel1();
		//data[x + 1][y-1] = 1;
	}
	if (y < 9)
	{
		if (data[x][y+1] == 1)
			ccount--;
		wait1();
		create_block(x, y + 1, 2);
		rel1();
		//	data[x ][y+1-1] = 1;
	}
	if (x > 0)
	{
		if (data[x - 1][y] == 1)
			ccount--;
		wait1();
		create_block(x - 1, y, 2);
		rel1();
		//	data[x - 1][y-1] = 1;
	}
	if (y > 0)
	{
		if (data[x ][y-1] == 1)
			ccount--;
		wait1();
		create_block(x, y - 1, 2);
		rel1();
		//	data[x][y-1-1] = 1;
	}
//	cout << "comming";
	//rel1();
	//cout << "out";
}
DWORD WINAPI display_block(LPVOID param)
{
	//while (1);
	srand(time(NULL));
	int x, y,t;
//	cout << "entering displayblock" << endl;
	while (ennd == 0 && pause==0)
	{
		if (ccount <= 15)
		{
			for (int i = 0; i < 90 && ennd==0 && pause==0; i++)
			{
				if (data[i / 10][i % 10] == 0 && ennd==0 && pause==0)
				{
					create_block(i / 10, i % 10, 2);
					break;
				}
			}
		}
		else
		{
			t = rand() % 90;
			x = t / 10;
			y = t % 10;
			while (data[x][y] != 0 && ennd == 0 && pause == 0)
			{
				//cout << "already done" << endl;
				t = rand() % 90;
				x = t / 10;
				y = t % 10;
			}
			//if (x > 8 || y > 9)
			//{
			//		cout << "error" << endl;
			//	}
			if (ennd == 0 && pause == 0)
			{
				create_block(x, y, 2);
				//	data[x][y + 1] = 1;
				delay(dl);
			}
		}
	}
//	cout << "exiting displayblock" << endl;
	return 0;
}
DWORD WINAPI handle_control(LPVOID param)
{
//	cout << "entering control handler" << endl;
	int x, y;
	while (ennd == 0 && pause==0)
	{
		
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, y, x);
//			wait1();
			if (x > bx && (data[(int)(x/bx)-1][(int)(y/by)])==0)
			{
	//			cout << "oops" << endl;
				//data[(int)(x / bx)][(int)(y / by)-1] = 1;
	//			rel1();
				create_error_block(x/bx-1,y/by);
	//			wait1();
				while (ismouseclick(WM_LBUTTONUP));
			}
			else if (x>by)
			{
	//			wait1();
				sc = score;
				score += 10;
//				cout << "score "<<score << endl;
				data[(int)(x / bx)-1][(int)(y / by)] = 0;
	//			cout << "yeah" << endl;
				wait1();
				create_block(x/bx-1, y/by, 15);
				rel1();
			}
//			rel1();
		}

	}
	//cout << "exiting control handler" << endl;
	return 0;
}
DWORD WINAPI display_header(LPVOID param)
{
//	cout << "......................................................displaying header" << endl;
	char abc[25] ="score : 00000";
	//char *abc = new char[500];
	//str="score : ";
	// sc = score;
	int arr[8];
	arr[0] = bx * 8; arr[1] = 0; arr[2] = bx*10; arr[3] =0;
	arr[4] = bx * 10; arr[5] = by; arr[6] = bx * 8; arr[7] = by;
	while (ennd == 0 && pause==0)
	{
		
		int temp,temp1;
		//cout << "entering score" << endl;
		if (sc != score || le!=col)
		{
			sc = score;
			temp = score;
			temp1=le = col;

		}
		else
		{
	//		cout << "exiting score" << endl;
			continue;
		}
		for (int i = 0; i < 5; i++)
		{
			//cout << (10 - i + 3) <<abc[9]<< endl;
		//	getch();
			abc[13-i] = ('0'+sc % 10);
			sc=sc/ 10;
		}
		/*for (int i = 0; i < 2; i++)
		{
			abc[22-i] = ('0' + le % 10);
			le = le / 10;
		}*/
		//abc[20] = '/n';
	//	cout << "displaying score" << endl;
		wait();
		setbkcolor(15);
		setcolor(le);
		settextstyle(10, 0, 2);
		outtextxy(bx*3, bx*0.3, "press any key to pause");
		setcolor(2);
		setfillstyle(1,15);
		setbkcolor(15);
		setcolor(15);
		fillpoly(4, arr);
		setcolor(2);
		setbkcolor(15);
		setcolor(le);
		outtextxy(bx*8, bx*0.3, abc);
		setcolor(2);
		rel();
		if (temp == score)
		{
			sc = score;
		}
		if (temp1 == col)
		{
			le = col;
		}
		delay(20);
	//	abc = str;
	}
//	cout << ".....................displayed header" << endl;
	return 0;
}
DWORD WINAPI over(LPVOID param)
{
	while (!ennd)
	if (ccount < 5)
	{
		ennd = 1;
	}
	return 0;
}
void display_pause_menu()
{
//	cout << "displaying paused menu" << endl;
	setlinestyle(0, 0, 2);
	setcolor(2);
	rectangle(bx * 2, bx * 2, bx * 8, bx * 4);
	//rectangle(bx * 2, bx*4.5, bx * 8, bx*6.5);
	rectangle(bx * 2, bx * 7, bx * 8, bx * 9);
	settextjustify(1, 1);
	settextstyle(3, 0, 2);
	outtextxy(bx * 5, bx * 3, "RESUME");
	outtextxy(bx * 5, bx * 5.5,"| |");
	outtextxy(bx * 5, bx * 8, "CAN'T TAKE ANY MORE ...");
	//setlinestyle(0, 0, 5);
	rectangle(bx * 0.5, bx * 0.5, bx * 9.5, bx * 9.5);
	setlinestyle(0, 0, 2);
	clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_LBUTTONUP);
//	cout << "displayed pause menu" << endl;

}
DWORD WINAPI handle_pause_menu(LPVOID param)
{
//	cout << "pause menu colour handler entered..." << endl;
	int tx, ty, flag = 0;
	while (choicc == 0)
	{
		tx = mousex();
		ty = mousey();
		if (tx >= 0 && ty >= 0)
		{
			if (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 2 && ty <= by * 4)
			{
	//			cout << "hovered over resume" << endl;
				setcolor(3);
				rectangle(bx * 2, bx * 2, bx * 8, bx * 4);
				outtextxy(bx * 5, bx * 3, "RESUME");
				tx = mousex();
				ty = mousey();
				while (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 2 && ty <= by * 4 && choicc == 0)
				{
		//			delay(20);
					tx = mousex();
					ty = mousey();
				}
				setcolor(2);
				rectangle(bx * 2, bx * 2, bx * 8, bx * 4);
				outtextxy(bx * 5, bx * 3, "RESUME");
		//		cout << "came out of resume "<<choicc << endl;
			}
		/*	else if (tx >= bx * 2 && tx <= bx * 8 && ty >= by*4.5 && ty <= by*6.5)
			{
				setcolor(3);
				rectangle(bx * 2, bx*4.5, bx * 8, bx*6.5);
				outtextxy(bx * 5, bx * 5.5, "HELP");
				tx = mousex();
				ty = mousey();
				while (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 4.5 && ty <= by * 6.5 && choic == 0)
				{
					delay(20);
					tx = mousex();
					ty = mousey();
				}
				setcolor(2);
				setlinestyle(0, 0, 2);
				rectangle(bx * 2, bx*4.5, bx * 8, bx*6.5);
				outtextxy(bx * 5, bx * 5.5, "HELP");

			}*/
			else if (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 7 && ty <= by * 9)
			{
			//	cout << "entered exit hover" << endl;
				setcolor(3);
				rectangle(bx * 2, bx * 7, bx * 8, bx * 9);
				outtextxy(bx * 5, bx * 8, "CAN'T TAKE ANY MORE ...");
				tx = mousex();
				ty = mousey();
				while (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 7 && ty <= by * 9 && choicc == 0)
				{
				//	delay(20);
					tx = mousex();
					ty = mousey();
				}
				setcolor(2);
				rectangle(bx * 2, bx * 7, bx * 8, bx * 9);
				outtextxy(bx * 5, bx * 8, "CAN'T TAKE ANY MORE ...");
				//cout << "hover out of exit" << endl;
			}
		}
	//	delay(20);
	}
//	cout << "exiting colour sub-menu initiated" << endl;
	return 0;
}
void h_pause_menu()
{
//	cout << "handle to pause menu began" << endl;
	choicc = 0;
	DWORD threadid;
	HANDLE threadhandle;
	int param = atoi("10");
	int ft = 0;
	threadhandle = CreateThread(NULL, 0, handle_pause_menu, &param, 0, &threadid);
	while (1)
	{
		getmouseclick(WM_LBUTTONDOWN, cx, cy);
		if (cx >= 0 && cy >= 0)
		{
			if (cx >= bx * 2 && cx <= bx * 8 && cy >= by * 2 && cy <= by * 4)
			{
				ft = 1;
	//			cout << "play resumed" << endl;
				choicc = 1;
				WaitForSingleObject(threadhandle, INFINITE);
				CloseHandle(threadhandle);
		//		cout << "returned from thread color ...exiting" << endl;
				return;
			}
			/*else if (cx >= bx * 2 && cx <= bx * 8 && cy >= by*4.5 && cy <= by*6.5)
			{
				ft = 1;
				cout << "help" << endl;
				choic = 1;
				WaitForSingleObject(threadhandle, INFINITE);
				CloseHandle(threadhandle);
				help();
				start();
				return;
			}*/
			else if (cx >= bx * 2 && cx <= bx * 8 && cy >= by * 7 && cy <= by * 9)
			{
				if (ft == 0)
				{
					choicc = 1;
					WaitForSingleObject(threadhandle, INFINITE);
					CloseHandle(threadhandle);
				}
			//	cout << "exiting the process" << endl;
				ennd = 1;
				return ;
			}
		}
	}
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
}
void pause_menu()
{

//	cout << "displaying main pause menu:::::::::::" << endl;
	display_pause_menu();
	//cout << "comming from main pause menu...........::::" << endl;
	h_pause_menu();
//	cout << ennd << endl;	//cout << "done h_pause menu::::::::::" << endl;
}
DWORD WINAPI h_pause(LPVOID param)
{
//	cout << "pausing thread initiated" << endl;
	char ch;
	while (ennd == 0)
	{
		if (kbhit() && pause == 0)
		{
	//		cout << "pausing began" << endl;
			pause = 1;
			ch = getch();
	//		cout << ch << " pressed" << endl;
			int size;
			size = imagesize(0, 0, yyyy, xxxx);
			void *bitm = malloc(size * 8);
			getimage(0, 0, yyyy, xxxx, bitm);
			clearviewport();
			pause_menu();
			clearviewport();
			putimage(0, 0, bitm, 0);
			pause = 0;
		//	cout << ennd << endl;
			while (kbhit())
			{
				ch=getch();
		//		cout << "flushing ch "<<ch << endl;
			}
		}
	}
//	cout << "exiting pause menu" << endl;
	return 0;
}
DWORD WINAPI timerr(LPVOID param)
{
	while (!ennd)
	{
		while (!ennd && !pause)
		{
		//	cout <<endl<< dl << " timer " << endl;
			delay(dl*5);
			le = col;
			col++;
			if (dl > 300)
			dl = dl - 100;
			else
			{
				dl = 1000;
			}

		}
	}
	return 0;
}
void gameover()
{
	char str[50]="YOUR SCORE : 00000";
	for (int i = 0; i < 5; i++)
	{
		str[18 - i] = '0' + score % 10;
		score /= 10;
	}
	settextjustify(1, 1);
	settextstyle(3, 3, 5);
	outtextxy(bx*5,by*3,"GAME OVER !!!");
	outtextxy(bx*5,by*6,str);
	for (int i = 0; i < 1000; i++)
	{
		int temp = rand() % xxxx;
		int temp1 = rand() % yyyy;
		int temp2 = rand() % 15;
		putpixel(temp, temp1, temp2);
	}
	delay(2000);
}
void play()
{
	le = -10;
	col = 0;
	sc = -10;
	dl = 1000;
	ccount = 90;
	for (int a = 0; a < 10; a++)
	{
		for (int b = 0; b < 9; b++)
		{
			data[a][b] = 0;
		}
	}
	semaphore = 1;
	scsema = 1;
	score = 0; ennd = 0;
	clearviewport();
	DWORD thid1, thid2,thid3,thid4,thid5,thid6;
	HANDLE h1, h2,h3,h4,h5,h6;
	int param = atoi("10");
	h1 = CreateThread(NULL, 0, display_block, &param, 0, &thid1);
	h2 = CreateThread(NULL, 0, handle_control, &param, 0, &thid2);
	h3 = CreateThread(NULL, 0, display_header, &param, 0, &thid3);
	h4 = CreateThread(NULL, 0, h_pause, &param, 0, &thid4);
	h5 = CreateThread(NULL, 0, timerr, &param, 0, &thid5);
	h6 = CreateThread(NULL, 0, over, &param, 0, &thid6);
	while (ennd == 0)
	{
		while (pause == 0 && ennd==0)
		{
			WaitForSingleObject(h1, INFINITE);
			WaitForSingleObject(h2, INFINITE);
			WaitForSingleObject(h3, INFINITE);
			CloseHandle(h1);
			CloseHandle(h2);
			//WaitForSingleObject(h3, INFINITE);
			//WaitForSingleObject(h4, INFINITE);
			h1 = CreateThread(NULL, 0, display_block, &param, 0, &thid1);
			h2 = CreateThread(NULL, 0, handle_control, &param, 0, &thid2);
			h3 = CreateThread(NULL, 0, display_header, &param, 0, &thid3);
		}
	}
//	cout << "exiting game" << endl;
	WaitForSingleObject(h1, INFINITE);
	WaitForSingleObject(h2, INFINITE);
	WaitForSingleObject(h3, INFINITE);
	WaitForSingleObject(h4, INFINITE);
	WaitForSingleObject(h5, INFINITE);
	WaitForSingleObject(h6, INFINITE);
	CloseHandle(h1);
	CloseHandle(h2);
	CloseHandle(h3);
	CloseHandle(h4);
	CloseHandle(h5);
	CloseHandle(h6);
	clearviewport();
	gameover();
	clearviewport();
//	cout << "going back to main menu" << endl;
}
void help()
{
	clearviewport();
	outtextxy(bx * 5, by * 1, "The game consists of a board where block appears.");
	outtextxy(bx * 5, by * 3, "Destroy them before the board fills up.");
	outtextxy(bx * 5, by * 5, "You will be penalized fo hitting empty space.");
	outtextxy(bx * 5, by * 7, "Beware block with no colour and only border are not block.");
	outtextxy(bx*2,by*9,"press any key to continue");
	getch();
	clearviewport();
}
DWORD WINAPI handlecolor(LPVOID param)
{
	int tx, ty, flag = 0;
	while (choic == 0)
	{
		tx = mousex();
		ty = mousey();
		if (tx >= 0 && ty >= 0)
		{
			if (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 2 && ty <= by * 4)
			{
				setcolor(3);
				rectangle(bx * 2, bx * 2, bx * 8, bx * 4);
				outtextxy(bx * 5, bx * 3, "TAKE A SHOT !!!");
				tx = mousex();
				ty = mousey();
				while (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 2 && ty <= by * 4 && choic == 0)
				{
					tx = mousex();
					ty = mousey();
				}
				setcolor(2);
				rectangle(bx * 2, bx * 2, bx * 8, bx * 4);
				outtextxy(bx * 5, bx * 3, "TAKE A SHOT !!!");

			}
			else if (tx >= bx * 2 && tx <= bx * 8 && ty >= by*4.5 && ty <= by*6.5)
			{
				setcolor(3);
				rectangle(bx * 2, bx*4.5, bx * 8, bx*6.5);
				outtextxy(bx * 5, bx * 5.5, "CONFUSED");
				tx = mousex();
				ty = mousey();
				while (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 4.5 && ty <= by * 6.5 && choic == 0)
				{
					tx = mousex();
					ty = mousey();
				}
				setcolor(2);
				setlinestyle(0, 0, 2);
				rectangle(bx * 2, bx*4.5, bx * 8, bx*6.5);
				outtextxy(bx * 5, bx * 5.5, "CONFUSED");

			}
			else if (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 7 && ty <= by * 9)
			{
				setcolor(3);
				rectangle(bx * 2, bx * 7, bx * 8, bx * 9);
				outtextxy(bx * 5, bx * 8, "CAN'T TAKE ANY MORE ...");
				tx = mousex();
				ty = mousey();
				while (tx >= bx * 2 && tx <= bx * 8 && ty >= by * 7 && ty <= by * 9 && choic == 0)
				{
					tx = mousex();
					ty = mousey();
				}
				setcolor(2);
				rectangle(bx * 2, bx * 7, bx * 8, bx * 9);
				outtextxy(bx * 5, bx * 8, "CAN'T TAKE ANY MORE ...");
			}
		}
	}

	return 0;
}
void h_choice()
{
	choic = 0;
	DWORD threadid;
	HANDLE threadhandle;
	int param = atoi("10");
	int ft = 0;
	threadhandle = CreateThread(NULL, 0, handlecolor, &param, 0, &threadid);
	while (1)
	{
		getmouseclick(WM_LBUTTONDOWN, cx, cy);
		if (cx >= 0 && cy >= 0)
		{
			if (cx >=bx*2 && cx <=bx*8 && cy >=by*2 && cy <=by*4 )
			{
				ft = 1;
//				cout << "play" << endl;
				choic = 1;
				WaitForSingleObject(threadhandle, INFINITE);
				CloseHandle(threadhandle);
				play();
				//cout << "displaying start menu again" << endl;
				start();
				return;
			}
			else if (cx >=bx*2 && cx <=bx*8 && cy >=by*4.5 && cy <=by*6.5 )
			{
				ft = 1;
	//			cout << "help" << endl;
				choic = 1;
				WaitForSingleObject(threadhandle, INFINITE);
				CloseHandle(threadhandle); 
				help();
				start();
				return;
			}
			else if (cx >=bx*2 && cx <=bx*8 && cy >=by*7 && cy <=by*9 )
			{
				if (ft == 0)
				{
					choic = 1;
					WaitForSingleObject(threadhandle, INFINITE);
					CloseHandle(threadhandle);
				}
		//		cout << "exit" << endl;
				return;
			}
		}
	}
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
}
void show_main_menu()
{
	setlinestyle(0, 0, 2);
	setcolor(2);
	rectangle(bx*2,bx*2,bx*8,bx*4);
	rectangle(bx*2,bx*4.5,bx*8,bx*6.5);
	rectangle(bx*2,bx*7,bx*8,bx*9);
	settextjustify(1,1);
	settextstyle(3, 10, 3);
	setcolor(12);
	outtextxy(bx * 5, bx * 1.5, "BLOCK TACKLER");
	settextstyle(3, 0, 2);
	setcolor(2);
	outtextxy(bx*5,bx*3,"TAKE A SHOT !!!");
	outtextxy(bx * 5, bx * 5.5, "CONFUSED");
	outtextxy(bx * 5, bx * 8, "CAN'T TAKE ANY MORE ...");
	setlinestyle(0, 0, 5);
	rectangle(bx * 0.5, bx * 0.5, bx * 9.5, bx * 9.5);
	setlinestyle(0, 0, 2);
	clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_LBUTTONUP);
	
}
void start()
{
	//cout << "back to start" << endl;
		show_main_menu();
		//cout << "showed main menu" << endl;
		h_choice();
}
int main()
{
	initwindow(xxxx,yyyy, "",200,50);
	setbkcolor(WHITE);
	floodfill(1, 1, 1);
	start();
	//getch();
	return 0;
}
