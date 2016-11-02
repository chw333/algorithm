// 2002. 4 "Salary"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_N 100 * 2
#define MIN_WAGE 1
#define MAX_WAGE 99999

int T, N;
int num;
int name_n;
char name[MAX_N][10];
int relation[MAX_N][MAX_N];
int wage_max[MAX_N], wage_min[MAX_N];
bool ok;
bool visited[MAX_N][2];
FILE *inf, *outf;

void initialize_relation()
{
	for (int i=0; i<N*2; i++) 
		for (int j=0; j<N*2; j++)
			relation[i][j] = -1;
}

int find_name(char name_[10])
{
	int wage;

	for (int i=0; i<name_n; i++)
		if (!strcmp(name[i], name_)) return i;

	strcpy(name[name_n], name_);
	if (name_[0] >= '0' && name_[0] <= '9') 
	{
		wage = atoi(name_);
		wage_min[name_n] = wage;
		wage_max[name_n] = wage;
	}
	else 
	{
		wage_min[name_n] = MIN_WAGE;
		wage_max[name_n] = MAX_WAGE;
	}
	return name_n++;
}

int find_relation(char rel[])
{
	if (!strcmp(rel, "<")) return 0;
	if (!strcmp(rel, "<=")) return 1;
	if (!strcmp(rel, "=")) return 2;
	if (!strcmp(rel, ">=")) return 3;
	if (!strcmp(rel, ">")) return 4;
	return -1;
}

void insert(int name1_num, int name2_num, int rel_num)
{
	if (name1_num == name2_num && (rel_num == 0 || rel_num == 4))
		ok = false;
	if (relation[name1_num][name2_num] != -1)
	{
		if (relation[name1_num][name2_num] == 0 && rel_num > 1) ok = false;
		else if (relation[name1_num][name2_num] == 1 && rel_num == 0) relation[name1_num][name2_num] = 0;
		else if (relation[name1_num][name2_num] == 1 && rel_num == 2) relation[name1_num][name2_num] = 2;
		else if (relation[name1_num][name2_num] == 1 && rel_num > 2) ok = false;
		else if (relation[name1_num][name2_num] == 2 && rel_num != 2) ok = false;
		else if (relation[name1_num][name2_num] == 3 && rel_num == 4) relation[name1_num][name2_num] = 4;
		else if (relation[name1_num][name2_num] == 3 && rel_num == 2) relation[name1_num][name2_num] = 2;
		else if (relation[name1_num][name2_num] == 3 && rel_num < 3) ok = false;
		else if (relation[name1_num][name2_num] == 4 && rel_num < 4) ok = false;
	}
	else {
		relation[name1_num][name2_num] = rel_num;
		relation[name2_num][name1_num] = 4 - rel_num;
	}
}

void input_data()
{
	int i;
	char name1[10], name2[10], rel[3];	
	int name1_num, name2_num, rel_num;

	ok = true;

	fscanf(inf, "%d\n", &N);

	name_n = 0;
	initialize_relation();	

	for (i=0; i<N; i++)
	{
		fscanf(inf, "%s\n", name1);
		fscanf(inf, "%s\n", rel);
		fscanf(inf, "%s\n", name2);

		name1_num = find_name(name1);
		name2_num = find_name(name2);
		rel_num = find_relation(rel);

		insert(name1_num, name2_num, rel_num);
	}
}

void search(int k, int min, int max, bool first)
{
	int i, temp;
	bool change1 = false, change2 = false;

	if (wage_min[k] < min) {
		wage_min[k] = min;	change1 = true;
		if (visited[k][0])	{
			ok = false;		return;
		}
		else visited[k][0] = true;
	}
	if (wage_max[k] > max) {
		wage_max[k] = max;	change2 = true;
		if (visited[k][1])	{
			ok = false;		return;
		}
		else visited[k][1] = true;
	}

	if (wage_min[k] > wage_max[k]) {
		ok = false;		return;
	}
		
	if (!first && (name[k][0] <= '9' || (!change1 && !change2))) return;

	for (i=0; i<name_n; i++)
	{
		if (relation[k][i] != -1) {
			temp = relation[k][i];
			relation[i][k] = -1;

			switch(temp) 
			{
				case 0 : search(i, min+1, MAX_WAGE, false);		break;
				case 1 : search(i, min, MAX_WAGE, false);		break;	
				case 2 : search(i, min, max, false);			break;
				case 3 : search(i, MIN_WAGE, max, false);		break;
				case 4 : search(i, MIN_WAGE, max-1, false);		break;
			}

			relation[i][k] = 4 - temp;
		}
		if (!ok) return;
	}

	if (change1) visited[k][0] = false;
	if (change2) visited[k][1] = false;
}

void solve()
{
	int i;
	
	for (i=0; i<name_n; i++) {
		visited[i][0] = false;		visited[i][1] = false;
	}

	for (i=0; i<name_n; i++) {
		search(i, wage_min[i], wage_max[i], true);
		if (!ok) break;
	}
}

void output_result()
{
	int i, j;
	int index[MAX_N], temp;

	if (ok) fprintf(outf, "OK\n");
	else {
		fprintf(outf, "No solution\n\n");
		return;
	}

	for (i=0; i<name_n; i++)
		index[i] = i;

	for (i=0; i<name_n-1; i++)
		for (j=i+1; j<name_n; j++)
			if (strcmp(name[index[i]], name[index[j]]) == 1)
			{
				temp = index[i];
				index[i] = index[j];
				index[j] = temp;
			}

	for (i=0; i<name_n; i++)
		if (name[index[i]][0] > '9')
			fprintf(outf, "%s %d %d\n", name[index[i]], wage_min[index[i]], wage_max[index[i]]);

	fprintf(outf, "\n");
}

void main()
{	
	inf = fopen(INPUT_FILE, "r");
	outf = fopen(OUTPUT_FILE, "w");

	fscanf(inf, "%d\n", &T);
	
	for(int i=0; i<T; i++) {
		input_data();
		if (ok) solve();
		output_result();
	}

	fclose(inf);
	fclose(outf);
}