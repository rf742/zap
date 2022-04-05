#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define K 8.988E+9
#define ELECTRON_CHARGE -1.60221766E-19

struct pointCharge {
	char name;
	long double x;
	long double y;
	long double q;
	long double fx;
	long double fy;
	long double magf;
	long double netangle;
};

int main(int argc, char *argv[])
{
	struct pointCharge p[3];
	struct pointCharge a = {.name = 'a', .x = 0.0, .y = 4.0, .q = -6E-06};
	struct pointCharge b = {.name = 'b', .x = 0.0, .y = 0.0, .q = 4E-06};
	struct pointCharge c = {.name = 'c', .x = 3.0, .y = 0.0, .q = 2E-06};
	p[0] = a;
	p[1] = b;
	p[2] = c;
	size_t elems = sizeof(p)/sizeof(p[0]);
	// variables to be used in loops
	long double x_dist, y_dist, dist, totalforce, angle, fx, fy;
	//

	for (int i = 0; i < elems; ++i) {
		for (int j = 0; j < elems; ++j) {
			if (i != j) {
				x_dist = fabsl(p[i].x - p[j].x);
				y_dist = fabsl(p[i].y - p[j].y);
				dist = sqrt((x_dist*x_dist)+(y_dist*y_dist));
				totalforce = (K*p[i].q*p[j].q)/(dist*dist);
				angle = atan2(y_dist,x_dist);
				fx = fabsl(totalforce*cosl(angle));
				fy = fabsl(totalforce*sinl(angle));
				if ((p[j].x < p[i].x) && (p[i].q * p[j].q <0)) {fx=-fx;}
				if ((p[j].x > p[i].x) && (p[i].q * p[j].q >0)) {fx=-fx;}
				if ((p[j].y < p[i].y) && (p[i].q * p[j].q <0)) {fy=-fy;}
				if ((p[j].y > p[i].y) && (p[i].q * p[j].q >0)) {fy=-fy;}
				p[i].fx = p[i].fx + fx;
				p[i].fy = p[i].fy + fy;
			}
		}
	}
	for (int k = 0; k < elems; ++k) {
		p[k].magf = sqrt((p[k].fx*p[k].fx)+(p[k].fy*p[k].fy));
		p[k].netangle = atan2(p[k].fy, p[k].fx);
		printf("For the %f C charge @ %e, %e\n", p[k].q, p[k].x, p[k].y);
		printf(" |Fnet| =  %e N\n", p[k].magf);
		printf("  Fnet  =  %e i + %e j\n", p[k].fx, p[k].fy);
		printf("  Angle =  %f rads, (%f deg)\n", p[k].netangle, p[k].netangle*180.00/PI);
	}
	return 0;
}
