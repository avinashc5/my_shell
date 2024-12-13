#include <unistd.h>

void Spin(int time){
	usleep(time * 1000000);
}