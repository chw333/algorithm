/* ACM International Collegiate Programming Contest
   Central European Regional Contest 2000
   
   Problem B - The Bulk
   Michal Sevcenko
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SURFACES 1000
#define MAX_EDGES 1000

#define bool int
#define false 0
#define true 1

struct SurfaceIndex {
	int Level;
	int Index;
} SurfaceIndexes[MAX_SURFACES];

struct {
	bool Clockwise;
/*  for optimization
	int MinX, MinY, MaxX, MaxY;*/
	int Area;
	int InnerX, InnerY;
	int EdgeCount;
	bool TopInner;
	struct {
		int X, Y;
	} Edges[MAX_EDGES];
} Surfaces[MAX_SURFACES];

int SurfaceCount;

/* helper function for qsort */
int Compare(const void *e1, const void *e2)
{
	const struct SurfaceIndex *si1 = (struct SurfaceIndex*)e1;
	const struct SurfaceIndex *si2 = (struct SurfaceIndex*)e2;
	if (si1->Level == si2->Level)
		return si1->Index < si2->Index  ? -1 : 1;
	return si1->Level < si2->Level ? -1 : 1;
}

#ifndef min
#define min(a,b) ( (a) < (b) ? (a) : (b) )
#define max(a,b) ( (a) > (b) ? (a) : (b) )
#endif

/* returns true if surface with index 'index' contains given point */
bool SurfaceHit(int index, int innerx, int innery)
{
	int i;
	int maxy = -2000000000;
	bool result = false;

	for (i=0; i<Surfaces[index].EdgeCount; i++)
	{
		int last = (i == Surfaces[index].EdgeCount-1) ? 0 : i+1;
		int minx, maxx, y;
		/* skip vertical edge */
		if (Surfaces[index].Edges[i].X ==
			Surfaces[index].Edges[last].X) continue;
		y = Surfaces[index].Edges[i].Y;
		minx = min(Surfaces[index].Edges[i].X, Surfaces[index].Edges[last].X);
		maxx = max(Surfaces[index].Edges[i].X, Surfaces[index].Edges[last].X);
		if (innery < y || y < maxy || innerx < minx || innerx >= maxx)
			continue;
		result = (Surfaces[index].Edges[i].X < Surfaces[index].Edges[last].X)
			^ Surfaces[index].Clockwise;
		maxy = y;
	}
	return result;
}

/* returns index of closest surface that contains given point; start
   searching at 'startindex' (index of current surface) and continue
   to lower levels */
int FindSurface(int innerx, int innery, int startindex)
{
	int i;
	int level = SurfaceIndexes[startindex].Level;

	/* skip surfaces with same level */
	for (i=startindex; i>=0 && SurfaceIndexes[i].Level == level; i--);

	/* go through surfaces from top to down and find first that
		overlaps with given one */
	for (; i>=0; i--)
	{
		int index = SurfaceIndexes[i].Index;
		if (SurfaceHit(index, innerx, innery)) return index;
	}
	return -1;
}

void DoIt()
{
	int i, j, surfaces, edges;
	int deltax, deltay, x, y;
	int level, volume;
	bool skip;

	scanf("%i", &surfaces);
	SurfaceCount = 0;
	for (i=0; i<surfaces; i++)
	{
		scanf("%i", &edges);
		
		skip = false;
		for (j=0; j<edges; j++)
		{
			scanf("%i %i %i", &Surfaces[SurfaceCount].Edges[j].Y,
				&Surfaces[SurfaceCount].Edges[j].X,
				&level);
//			scanf("%i %i %i", &Surfaces[SurfaceCount].Edges[j].X,
//				&level,
//				&Surfaces[SurfaceCount].Edges[j].Y);
//			scanf("%i %i %i", &level,
//				&Surfaces[SurfaceCount].Edges[j].Y,
//				&Surfaces[SurfaceCount].Edges[j].X);

			if (j == 0)
				SurfaceIndexes[SurfaceCount].Level = level;
			else
			if (level != SurfaceIndexes[SurfaceCount].Level)
				skip = true;
		}

		/* not a horizontal surface, continue */
		if (skip) continue;

		Surfaces[SurfaceCount].EdgeCount = edges;
		SurfaceIndexes[SurfaceCount].Index = SurfaceCount;

		/* calculate area */
		Surfaces[SurfaceCount].Area = 0;
		for (j=0; j<edges; j++)
		{
			int last = (j == edges-1) ? 0 : j+1;
			/* skip vertical edge */
			if (Surfaces[SurfaceCount].Edges[j].X ==
				Surfaces[SurfaceCount].Edges[last].X) continue;
			Surfaces[SurfaceCount].Area +=
				Surfaces[SurfaceCount].Edges[j].Y *
				(Surfaces[SurfaceCount].Edges[last].X - 
				Surfaces[SurfaceCount].Edges[j].X);
		}
		/* and determine orientation */
		if (Surfaces[SurfaceCount].Area > 0)
			Surfaces[SurfaceCount].Clockwise = true;
		else
		{
			Surfaces[SurfaceCount].Clockwise = false;
			Surfaces[SurfaceCount].Area = -Surfaces[SurfaceCount].Area;
		}

		/* find inner point of surface */
		x = Surfaces[SurfaceCount].Edges[0].X;
		deltax = Surfaces[SurfaceCount].Edges[1].X - x;
		y = Surfaces[SurfaceCount].Edges[0].Y;
		deltay = Surfaces[SurfaceCount].Edges[1].Y - y;
		Surfaces[SurfaceCount].InnerX = x;
		Surfaces[SurfaceCount].InnerY = y;
		if (Surfaces[SurfaceCount].Clockwise)
		{
			if (deltay < 0)
			{
				Surfaces[SurfaceCount].InnerX--;
				Surfaces[SurfaceCount].InnerY--;
			}
			else
			if (deltax < 0)
				Surfaces[SurfaceCount].InnerX--;
			else
			if (deltax > 0)
				Surfaces[SurfaceCount].InnerY--;
		}
		else
		{
			if (deltax < 0)
			{
				Surfaces[SurfaceCount].InnerX--;
				Surfaces[SurfaceCount].InnerY--;
			}
			else
			if (deltay > 0)
				Surfaces[SurfaceCount].InnerX--;
			else
			if (deltay < 0)
				Surfaces[SurfaceCount].InnerY--;
		}

		SurfaceCount++;

	}
	/* sort surfaces according their levels */
	qsort(SurfaceIndexes, SurfaceCount, sizeof(struct SurfaceIndex), Compare);

	/* determine surface orientation */
	for (i=0; i<SurfaceCount; i++)
	{
		int index = SurfaceIndexes[i].Index;
		int hit = FindSurface(Surfaces[index].InnerX,
			Surfaces[index].InnerY, i);
		if (hit == -1)
			Surfaces[index].TopInner = true;
		else
			Surfaces[index].TopInner = !Surfaces[hit].TopInner;
	}

	/* compute the volume */
	volume = 0;
	for (i=0; i<SurfaceCount; i++)
	{
		int index = SurfaceIndexes[i].Index;
		if (Surfaces[index].TopInner)
			volume -= Surfaces[index].Area * SurfaceIndexes[i].Level;
		else
			volume += Surfaces[index].Area * SurfaceIndexes[i].Level;
	}
	printf("The bulk is composed of %i units.\n", volume);
}

int main()
{
	int i, n;
	scanf("%i", &n);

	for (i=0; i<n; i++)
		DoIt();

	return 0;
}

