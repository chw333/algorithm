/*
ID: lge1435001
PROB: poly1
*/
#include<stdio.h>
#include<string.h>

#define MAX 201

short int expp[3][MAX][MAX];
int spc = 0;
FILE *fp;

int abs(int a)
{
	if (a < 0) return -a;
	      else return a;
}

void ss()
{
	int i;
	for (i = 0; i < spc; i++)
		fprintf(fp, " ");
	spc = 0;
}

void pp(int ww, char *pr)
{
	if (ww) fprintf(fp, "%s", pr);
		else spc++;
}

void print(int bigi, int ww)
{
	int i, j, k, first = 1;
	int lasti, lastj;
	spc = 0;
	for (i = MAX - 1; i > -1; i--)
		for (j = 0; j < MAX; j++)
			if (expp[bigi][i][j] != 0)
			{
				lasti = i;
				lastj = j;
			}
	for (i = MAX - 1; i > -1; i--)
		for (j = 0; j < MAX; j++)
			if (expp[bigi][i][j] != 0)
			{
				if (!first) pp(ww," ");
				if( expp[bigi][i][j] < 0 )
					pp(ww, "-");
				else
				{
					if(!first)
						pp(ww, "+");
				}
				if (!first) pp(ww," ");
				first = 0;
				if (abs(expp[bigi][i][j]) != 1 || (i == 0 && j ==0))
				{
					char temp[10];
					sprintf(temp, "%d",abs(expp[bigi][i][j]));
					if(ww) fprintf(fp, "%s",temp);
					else
						spc += strlen(temp);
				}
				if(i!= 0)
				{
					pp(ww,"x");
					if(i!=1)
					{
						char temp[10];
						sprintf(temp, "%d",abs(i));
						ss();
						if(!ww) fprintf(fp, "%s",temp);
						else
						{
							if (i != lasti || j != lastj || j != 0)
							for (k = 0 ; k < strlen(temp); k++)
								fprintf(fp, " ");
						}
					}
				}
				if(j!= 0)
				{
					pp(ww,"y");
					if(j!=1)
					{
						char temp[10];
						sprintf(temp, "%d",abs(j));
						ss();
						if(!ww) fprintf(fp, "%s",temp);
						else
						{
							//spc += strlen(temp);
							if (i != lasti || j != lastj)
							for (k = 0 ; k < strlen(temp); k++)
								fprintf(fp, " ");
						}
					}
				}
			}
	fprintf(fp, "\n");
}

void process(char *input, int bigi)
{
	int coeff = 1 , xexp = 0 , yexp = 0 , num = 0;
	int state = 0, i;

	for(i=0; ; i++)
	{
		switch(input[i])
		{
			case '-':
			case '+':
			case '\n':
				if(num!=0)
				{
					if(state == 1)
						xexp = num;
					else if(state == 2)
						yexp = num;
					else
						coeff = coeff * num;
				}
				if(i!= 0)
				{
					expp[bigi][xexp][yexp] += coeff;
				}
				if(input[i] == '\0')break;
				if(input[i] == '-' ) coeff = -1;
				if(input[i] == '+' ) coeff = 1;

				state = 0;
				xexp = 0;
				yexp = 0;
				num = 0;
				break;
			case 'x':
				if(num!=0)
				{
					if(state == 0)
						coeff = coeff * num;
					else    // state 2 (y)
						yexp = num;
				}
				state = 1;
				xexp = 1;
				num = 0;
				break;
			case 'y':
				if(num!= 0)
				{
					if(state == 0)
						coeff = coeff * num;
					else
						xexp = num;
				}
				yexp = 1;
				state = 2;
				num = 0;
				break;
			default:
				num = num * 10 + ((int) (input[i] - '0'));
				break;
			}
		if (input[i] == '\n') break;
	}

}

main()
{
	int i, j,k,l;
	char ip1[200],ip2[200];
	fp = fopen("poly1.in","r");
		fgets(ip1, 200, fp);
		fgets(ip2, 200, fp);
	fclose(fp);

	process(ip1, 0);
	process(ip2, 1);

	for(i=0;i<MAX;i++)
		for(j=0;j<MAX;j++)
			if(expp[0][i][j]!=0)
				for(k=0;k<MAX;k++)
					for(l=0;l<MAX;l++)
						if(expp[1][k][l]!=0){
							expp[2][i+k][j+l] += expp[0][i][j] * expp[1][k][l];
						}




	fp = fopen("poly1.out", "w");
	print(2, 0);
	print(2, 1);
	fclose(fp);
}