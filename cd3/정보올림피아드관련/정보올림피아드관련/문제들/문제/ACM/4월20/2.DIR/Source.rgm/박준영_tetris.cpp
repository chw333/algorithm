#include<fstream.h>
int kn,km,ln,lm,i,j,k[300][300],l[300][300],max,cnt,o,d[300][300],flag;
char s;
void dfs(int v)
{
	if(max<v){max=v;}
	if(max==ln+kn){return;}
	for(i=0;i<=lm-km;i++){
		flag=0;
		for(j=v;j<v+kn;j++){
			for(o=i;o<i+km;o++){
				if(k[j-v][o-i]+l[j][o]==2){flag=1;break;}
			}
			if(k[j-v][o-i]+l[j][o]==2){flag=1;break;}
		}
		if(flag==0){
			for(j=v;j<v+kn;j++){
				for(o=i;o<i+km;o++){
					if(k[j-v][o-i]==1&&l[j+1][o]==1){flag=1;break;}
				}
				if(k[j-v][o-i]+l[j][o]==2){flag=1;break;}
			}
			if(flag==0){
				dfs(v+1);
				return;
			}
		}
	}
}
void main()
{
	ifstream in("tetris.in");
	in >> kn>>km;
	for(i=0;i<kn;i++){
		for(j=0;j<km;j++){
			in >> s;
			if(s=='#'){k[i][j]=1;}else{k[i][j]=0;}
		}
	}
	in >> ln>>lm;
	for(i=kn;i<kn+ln;i++){
		for(j=0;j<lm;j++){
			in >> s;
			if(s=='#'){l[i][j]=1;}else{l[i][j]=0;}
		}
	}
	dfs(0);
	ofstream out("tetris.out");
	if(max<ln+kn){out << max;}else{out << "pass";}
}