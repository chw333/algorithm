#include <iostream>
#include <stdio.h>

double bestPI=0;
double bestMargin=0;
double bestSales;
double bestCost;
int bestNfeatures=0;
int bestNcusts;
bool* bestCust;
bool* bestFeatures;

int Nfeatures;


int minCost, maxCost, Ncust;

double* featureCost;
bool** required;
int* salesUnits;

void evaluate(bool* featureSet){
  double pi, margin, sales, cost;
  int featureCount=0;
  int custcount=0;
  bool custs[Ncust];


  cost = 0;
  for(int f=0;f<Nfeatures;f++)
    if(featureSet[f]){
      cost+=featureCost[f];
      featureCount++;
    }

  if (cost < minCost || cost > maxCost)
    return;

  sales = 0;
  for(int c = 0;c<Ncust;c++){
    bool isOK = true;
    for(int f = 0;f<Nfeatures && isOK;f++)
      if(required[c][f] && !featureSet[f])
	isOK = false;
    custs[c] = isOK;
    if(isOK){
      sales += salesUnits[c];
      custcount++;
    }
  }

  pi = sales / cost;

  margin = sales - cost;

  int ipi = (int) (pi * 1000+0.5);

  pi = ipi / 1000.0;

  if(pi < bestPI)
    return;

  if(pi == bestPI){
    if(margin < bestMargin)
      return;
    if(margin == bestMargin){
      if(featureCount < bestNfeatures)
	return;
      if(featureCount == bestNfeatures){
	if(custcount <= bestNcusts)
	  return;
      }
    }
  }

  bestPI = pi;
  bestMargin = margin;
  bestCost = cost;
  bestSales = sales;
  bestNfeatures = featureCount;
  bestNcusts = custcount;
  for(int c = 0;c<Ncust;c++)
    bestCust[c] = custs[c];
  for(int f = 0;f<Nfeatures;f++)
    bestFeatures[f] = featureSet[f];

}
	    
      

void check(bool* featureSet, int f){
  if(f < Nfeatures){
    featureSet[f] = false;
    check(featureSet, f+1);
    featureSet[f] = true;
    check(featureSet, f+1);
  }
  else
    evaluate(featureSet);
}



int main(int argc, char* argv[]){
  int nInput;

  cin >> nInput;

  for(int inputCount = 1;inputCount <= nInput; inputCount++){
    printf ("Feature Set %i\n", inputCount);
    bestPI = 0;
    cin >> minCost >> maxCost >> Nfeatures >> Ncust;
    
    featureCost = new double[Nfeatures];
    
    for(int i=0;i<Nfeatures;i++)
      cin >> featureCost[i];

    required = new bool*[Ncust];
    salesUnits = new int[Ncust];
    for(int i=0;i<Ncust;i++){
      int nfr;

      cin >> nfr;

      required[i] = new bool[Nfeatures];
      for(int j=0;j<Nfeatures;j++)
	required[i][j] = false;

      for(int j=0;j<nfr;j++){
	int fnum;
	cin >> fnum;
	fnum--;
	required[i][fnum] = true;
      }

      cin >> salesUnits[i];
    }
  
    bool isFeature[Nfeatures];
    bestFeatures = new bool[Nfeatures];
    bestCust = new bool[Ncust];
    for(int i=0;i<Nfeatures;i++)
      isFeature[i] = bestFeatures[i] = false;

    check(isFeature, 0);

    printf("%.3f\n", bestPI);
    printf("%i\n", (int) bestSales);
    printf("%i\n", (int) bestCost);
    for(int i=0;i<Nfeatures;i++)
      if(bestFeatures[i])
	printf("%i ", i+1);
    printf ("\n");

    for(int i=0;i<Ncust;i++)
      if(bestCust[i])
	printf("%i ", i+1);
    printf("\n");
  }
}


    
  
