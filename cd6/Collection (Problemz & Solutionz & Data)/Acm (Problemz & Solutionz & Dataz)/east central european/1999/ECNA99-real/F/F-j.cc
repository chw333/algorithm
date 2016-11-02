/* Copyright John Bonomo (ACM ICPC ECNA 1999) */

#include <iostream>
 
main()
{
	int p, e, i, d, cases=0;

	cin >> p >> e >> i >> d;
	while (p != -1) {
		cases++;
	   	while ((p-e)%28 != 0)
		      	p += 23;
		while ((p-i)%33 != 0)
			p+= 23*28;
		while (p > d)
			p -= 23*28*33;
		while (p <= d)
		      	p += 23*28*33;
		cout << "Case " << cases << ": the next triple peak occurs in ";
		cout << (p-d) << " days." << endl;
		cin >> p >> e >> i >> d;
	}
}

