// 길찾기 문제

#include <stdio.h>
#include <process.h>

int lng[101][101], mny[101][101];
int mxm[101];
int k,n,r;
int pth[101],all,cnt;

Output_(int yn) {
	FILE *fp=fopen("road.out","w");
		
	if (yn==-1) 
		fprintf (fp,"-1");
	else {
		fprintf (fp,"%d\n",all);
		for (int i=cnt;i>0;i--) 
			fprintf (fp,"%d\n",pth[i]);
	}
	fclose(fp);
	exit(0);
}		

Process_() {
	int tab[3][101]={0,};
	int chk[101]={0,};
	int min,sw,now;
	for (int i=1;i<=n;i++) tab[0][i]=10001;
	tab[0][1]=0;
	do {
		min=10001; sw=-1;
		for (int i=1;i<=n;i++) 
			if (chk[i]==0 && min>tab[0][i]) {
				min=tab[0][i]; sw=i;
			}
		if (sw==-1) Output_(-1);
		chk[sw]=1;
		for (int j=1;j<=n;j++) 
			if (chk[i]==0 && lng[sw][j]>0 && tab[0][j]>min+lng[sw][j] && tab[2][sw]+mny[sw][j]<=mxm[j]) {
				tab[0][j]=min+lng[sw][j];
				tab[1][j]=sw;
				tab[2][j]=tab[2][sw]+mny[sw][j];
	
			}
	
	} while (chk[n]==0);
	
	all=tab[0][n]; now=n;
	do {
		pth[++cnt]=now;
		now=tab[1][now];
	} while (now>0);
}

Sett_() {
	int chk[101],ok;
	chk[n]=1; mxm[n]=k;
	do {
		ok=0;
		for (int i=1;i<=n;i++) {
			if (chk[i]==1) {
				chk[i]=0;
				for (int j=1;j<=n;j++) 
					if (lng[j][i]>0) 
						if (mxm[j]<mxm[i]-mny[j][i]) {
							mxm[j]=mxm[i]-mny[j][i];
							chk[j]=1;
							ok=1;
						}
			}
		}
	} while (ok==1);

	for (int i=2;i<=n;i++) 
		for (int j=1;j<=n;j++) 
			if (lng[j][i]>0 && mny[j][i]>mxm[i]) lng[j][i]=0;

}

Input_() {
	int t1,t2,t3,t4;
	FILE *fp=fopen("road.inp","rt");
	fscanf (fp,"%d",&k);
	fscanf (fp,"%d",&n);
	fscanf (fp,"%d",&r);
	for (int i=1;i<=r;i++) {
		fscanf (fp,"%d %d %d %d",&t1,&t2,&t3,&t4);
		if (t1!=n && t2!=1) {
			lng[t1][t2]=t3;
			mny[t1][t2]=t4;
		}
	}
//	for (i=1;i<=n;i++) mxm[i]=10001;
	fclose(fp);
}

main() {
	Input_();
	Sett_();
	Process_();
	Output_(1);
}