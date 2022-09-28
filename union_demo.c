#include <stdio.h>
const char *status_msgs[] = {
		"Printer Ready.",
		"Warming up.",
		"Paper empty.",
		"Paper jammed.",
		"Catridge low.",
		"Cleaning debris.",
		"No connection",
		"Memory error."};
// messages
int status_read(unsigned char dat)
{
	if (dat == 0)
		return printf("Invalid status.");
	for (int i = 128, j = 0; i <= 128; i /= 2)
		if ((dat & i) == i)
			printf("%d. %s\n", j + 1, status_msgs[j++]);
	return 0;
}
// read msg to stdout
unsigned char get_status(){
	unsigned char stat=0;
	printf("Enter value between 1-128: ");
	scanf("%d", &stat);
	return (stat<129) ? stat:0;
}
// user defined
struct printer_stat{
		unsigned Printer_Ready: 1,
		unsigned Warming_up: 1,
		unsigned Paper_empty: 1,
		unsigned Paper_jammed: 1,
		unsigned Catridge_low: 1,
		unsigned Cleaning_debris: 1,
		unsigned No_connection:1,
		unsigned Memory_error: 1
};
// union type

int main(void){
	status_read(get_status());
	return 0;
}