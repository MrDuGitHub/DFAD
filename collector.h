#ifndef DFAD_COLLECTOR_H
#define DFAD_COLLECTOR_H

#define num_X 3

typedef enum Mode{Switch,Controller} Mode;

void init();
FILE* send_order();
void get_flow_data(char* s);
void get_X(int X[]);
void setMode(char c);

#endif /*collector.h*/
