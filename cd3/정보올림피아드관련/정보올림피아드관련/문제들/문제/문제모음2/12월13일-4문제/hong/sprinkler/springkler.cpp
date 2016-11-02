#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream.h>

ifstream in("sprinkler05.in");
ofstream out("sprinkler05.out");

double horizCoverage(double radius, double lawnWidth) {
    if (2 * radius < lawnWidth) return 0.0;
    return sqrt(radius * radius - lawnWidth * lawnWidth / 4.0);
}

typedef struct {
    double leftcover, rightcover;
} sprinkler;

int cmp_sprinklers(const void *a, const void *b) {
    const sprinkler *x = (const sprinkler *)a;
    const sprinkler *y = (const sprinkler *)b;
    double leftDiff = x->leftcover - y->leftcover;
    double rightDiff = y->rightcover - x->rightcover;
    if (leftDiff < 0) return -1;
    else if (leftDiff > 0) return 1;
    else if (rightDiff < 0) return -1;
    else if (rightDiff > 0) return 1;
    return 0;
}

int numSprinklers, length, width;
sprinkler sprinklers[20000];

int findNextSprinkler(double coverage) {
    int n, best = -1;
    double rightmost = -1;
    for (n = 0; n < numSprinklers; n++) {
        if ((sprinklers[n].leftcover <= coverage) &&
            (sprinklers[n].rightcover > coverage) &&
            (sprinklers[n].rightcover > rightmost)) {
            best = n;
            rightmost = sprinklers[n].rightcover;
        }
    }

    return best;
}

void main() {
    int n, ndx, position, radius, numChosen, next;
    double rightcovered;
    double hcover;

	in >> numSprinklers >> length >> width;

        ndx = 0;
        for (n = 0; n < numSprinklers; n++) {
			in >> position >> radius;

            hcover = horizCoverage(radius, width);
            /* if this sprinkler doesn't even reach the width of the lawn, it's no good... */
            if (hcover > 0.0) {
                sprinklers[ndx].leftcover = position - hcover;
                if (sprinklers[ndx].leftcover < 0) { sprinklers[ndx].leftcover = 0; } 
                else if (sprinklers[ndx].leftcover > length) { sprinklers[ndx].leftcover = length; }

                sprinklers[ndx].rightcover = position + hcover;
                if (sprinklers[ndx].rightcover < 0) { sprinklers[ndx].rightcover = 0; } 
                else if (sprinklers[ndx].rightcover > length) { sprinklers[ndx].rightcover = length; }
                ndx++;
            }
        }

        numSprinklers -= (numSprinklers - ndx);

        qsort(sprinklers, numSprinklers, sizeof(sprinkler), cmp_sprinklers);

        if ((numSprinklers == 0) || (sprinklers[0].leftcover > 0)) {
			out << -1 << endl;
        } else {
            numChosen = 1;
            rightcovered = sprinklers[0].rightcover;
            next = 0;
            while ((rightcovered < length) && (next >= 0)) {
                next = findNextSprinkler(rightcovered);
                if (next != -1) {
                    rightcovered = sprinklers[next].rightcover;
                }
                numChosen++;
            }

            if (rightcovered < length) {
				out << -1 << endl;
            } else {
				out << numChosen << endl;
            }
        }
}

