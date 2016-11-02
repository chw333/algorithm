#include <stdio.h>
#include <math.h>

#define MAX_SIZE 30

const long int masks[] = {0x0, 
                     0x01, 0x02, 0x04, 0x08, 
                     0x10, 0x20, 0x40, 0x80, 
                     0x100, 0x200, 0x400, 0x800, 
                     0x1000, 0x2000, 0x4000, 0x8000, 
                     0x10000, 0x20000, 0x40000, 0x80000, 
                     0x100000, 0x200000, 0x400000, 0x800000, 
                     0x1000000, 0x2000000, 0x4000000, 0x8000000,
                     0x10000000, 0x20000000, 0x40000000, 0x80000000};
                      

// for best solution
long int max_mask = 0;
long int max_profit = 0;
long int f_in_best = 0;
long int c_in_best = 0;
long int max_sales = 0;
long int customers = 0;
long int features = 0;

// input the limits
long int limit_hi;
long int limit_low;
long int num_cust;
long int num_features;
long int num_req;
long int sets;

long int f_cost[MAX_SIZE + 1];
long int c_sales[MAX_SIZE + 1];
long int c_mask[MAX_SIZE + 1];

long int temp_sales = 0; 
long int temp_mask = 0;
long int temp_sat = 0;
long int temp_feat = 0;
long int temp_cost = 0;
long int temp_profit = 0;

long int i, j, k;

long int max_pi;
long int temp_pi;

void print_it (long int mask)
{
	long int a;

	for (a = 1; a <= MAX_SIZE+1; a++)
	{
		if (masks[a] & mask)
  			printf("%d ", a);
	}

}

long int cost_it (long int mask)
{
	long int local;
	long int a;

	local = 0;
	for (a = 1; a <= MAX_SIZE+1; a++)
	{
		if (masks[a] & mask)
			local += f_cost[a];
	}

	return local;

}

long int count_it (long int mask)
{
	long int local;
	long int a;

	local = 0;
	for (a = 1; a <= MAX_SIZE+1; a++)
	{
		if (masks[a] & mask)
			local++;
	}

	return local;

}


void main(void)
{
long int z;
scanf("%d", &sets);
for (z = 0; z < sets; z++)
{
max_mask = 0;
max_profit = 0;
f_in_best = 0;
c_in_best = 0;
max_sales = 0;
customers = 0;
features = 0;

	printf("Feature Set %d\n", z+1);
	max_mask = 0;
	scanf("%d %d %d %d", &limit_low, &limit_hi, &num_features, &num_cust);

// Read in feature costs
	for (i = 1; i <= num_features; i++)
	{
		max_mask |= masks[i];
		scanf("%d", &f_cost[i]);
	}

// Read in customer information - #features requested, which features, sales dollars
	for (i = 1; i <= num_cust; i++)
	{
		c_mask[i] = 0;
		scanf("%d", &num_req);
		for (j = 0; j < num_req; j++)
		{
			scanf("%d", &k);
			c_mask[i] |= masks[k];
		}
		scanf("%d", &c_sales[i]);
	}

	max_pi = 0;
	for (i = 1; i <= max_mask; i++)
	{
		temp_cost = cost_it(i);

		if ((temp_cost > limit_hi) || (temp_cost < limit_low))
			continue;

		temp_sales = 0;
		temp_mask = 0;
		temp_sat = 0;
		temp_feat = count_it(i);

		for (j = 0; j <= num_cust; j++)
		{
			if ((i & c_mask[j]) == c_mask[j])
			{
				temp_sales += c_sales[j];
				temp_mask |= masks[j];
				temp_sat++;
			}					 
		}

		temp_pi = (1000.0 * temp_sales / temp_cost + 0.5);
		temp_profit = temp_sales - temp_cost;
		if ((max_pi < temp_pi) ||
		    ((max_pi == temp_pi) && (max_profit < temp_profit)) ||
		    ((max_pi == temp_pi) && (max_profit == temp_profit) && (f_in_best > temp_feat)) ||
		    ((max_pi == temp_pi) && (max_profit == temp_profit) && (f_in_best == temp_feat) && (c_in_best < temp_sat)))

		{
			max_profit = temp_profit;
			f_in_best = temp_feat;
			c_in_best = temp_sat;
			max_sales = temp_sales;
			max_pi = temp_pi;
			features = i;
			customers = temp_mask;
		}

	}

	printf("%.3f\n", max_pi / 1000.0);
	printf("%d\n", max_sales);
	printf("%d\n", cost_it(features));
	print_it(features); printf("\n");
	print_it(customers); printf("\n");
}
}
