#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// test: fopen, close, seek, putget, seektell, eof,
// error, rewind, remove, flush
// macros: fpos_t, size_t, FOPEN_MAX, SEEK_SET, SEEK_CUR END
// modes: rwa, rbwbab, r+w+a+, r+bw+ba+b

void routine_read(FILE*);
void routine_write(FILE*);
void routine_append(FILE*);

int main(int argc, char* argv[]) {
	FILE* fp;
	if (argc == 1) exit(1);
	if ((fp = fopen(argv[1], "r")) == NULL)
		printf("Error: reading %s.\n", argv[1]);
	routine_read(fp);

	if ((fp = fopen(argv[1], "w")) == NULL)
		printf("Error: writing %s.\n", argv[1]);

	routine_write(fp);

	if ((fp = fopen(argv[1], "a")) == NULL)
		printf("Error: appending %s.\n", argv[1]);

	routine_append(fp);
	return 0;
}


// function definitions
void routine_read(FILE* fp) {
	if (fclose(fp) == EOF) puts("Error: Read file not closed!");
	else puts("Read file closed.");
}
void routine_write(FILE* fp) {
	if (!fclose(fp) == EOF) puts("Error: Write file not closed!");
	else puts("Write file closed.");
}
void routine_append(FILE* fp) {
	if (!fclose(fp) == EOF) puts("Error: Append file not closed!");
	else puts("Append file closed.");
}