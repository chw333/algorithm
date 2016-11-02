#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>

int x=1,y=1,last_x=0,last_y=0,temp=1,turn=1,mark[16][16];
int time_=0;

void set_driver(void)
{
	int gdriver=DETECT, gmode;
	initgraph(&gdriver,&gmode," ");
	cleardevice();
}

void draw_map(void)
{
	int i,j;
	setcolor(15);
	for(i=1; i<=15; i++)
	{
		line(25,i*25,25*15,i*25);
		line(i*25,25,i*25,25*15);
	}
}

void cursor(void)
{
	setcolor(0);
	circle(last_x*25,last_y*25,9);
	setcolor(15);
	circle(x*25,y*25,9);
	last_x=x; last_y=y;
}

void draw_ball(void)
{
	if(mark[x][y]==0)
	{
		if(turn==1)
		{
			setcolor(9);
			circle(x*25,y*25,10);
			mark[x][y]=1;
			turn*=-1;
		}

		else
		{
			setcolor(12);
			circle(x*25,y*25,10);
			mark[x][y]=-1;
			turn*=-1;
		}
	}
}

void decision(void)
{
	int x,y,temp;
	for(x=1; x<=15; x++)
		for(y=1; y<=15; y++)
			if(mark[x][y]!=0)
			{
				temp=mark[x][y];
				if(mark[x-3][y]!=temp && mark[x-2][y]==temp && mark[x-1][y]==temp && mark[x+1][y]==temp && mark[x+2][y]==temp && mark[x+3][y]!=temp)
					exit(1);
				if(mark[x][y-3]!=temp && mark[x][y-2]==temp && mark[x][y-1]==temp && mark[x][y+1]==temp && mark[x][y+2]==temp && mark[x][y+3]!=temp)
					exit(1);
				if(mark[x-3][y-3]!=temp && mark[x-2][y-2]==temp && mark[x-1][y-1]==temp && mark[x+1][y+1]==temp && mark[x+2][y+2]==temp && mark[x+3][y+3]!=temp)
					exit(1);
				if(mark[x-3][y+3]!=temp && mark[x-2][y+2]==temp && mark[x-1][y+1]==temp && mark[x+1][y-1]==temp && mark[x+2][y-2]==temp && mark[x+3][y-3]!=temp)
					exit(1);
			}
}

void main(void)
{
	int i,j;
	char *string;

	set_driver();
	draw_map();
	while(1)
	{
		draw_map();
		if(kbhit())
		{
			switch(getch())
			{
				case 'H' : y--; break;
				case 'P' : y++; break;
				case 'K' : x--; break;
				case 'M' : x++; break;
				case 27  : exit(1);
				case 32  : draw_ball(); time_=0; break;
			}
			cursor();
			decision();
		}
		time_+=1;
		moveto(25*15+10,25);
		setcolor(16);
		outtext(string);

		setcolor(15);
		itoa(time_,string,10);
		moveto(25*15+10,25);
		outtext(string);
		if(time_>500)
		{
			sound(850);
			delay(100);
			nosound();
			turn*=-1;
			time_=0;
		}
	}
}