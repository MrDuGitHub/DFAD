#ifndef DFAD_DETECTION_H
#define DFAF_DETECTION_H

struct Count {int k;int m;int w;};

void init_work();
double get_H();
void update_E(double H[],int k);
void work();
void set_value(char x,int v0,int v1);
void get_log(int i);

#endif /*detection.h*/
