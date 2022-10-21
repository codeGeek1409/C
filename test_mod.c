#include <stdio.h>
#include <string.h>
/* to see if a part of a file
 * can be modified or not
 * result: modification works only with wb+ mode
 */
int main()
{
	struct test
	{
		int a;
		char b[80];
	} t[10]; // to fill the file 84 bytes x 10
	FILE *con = fopen("test", "rb+");
	if (con == NULL)
	{
		puts("File error.");
		return 1;
	}

	int i = 0; // for indexing
	while (i < 10)
	{
		t[i].a = i;
		strcpy(t[i].b, "Hello World.\n");
		fwrite(&t[i], sizeof(struct test), 1, con);
		i++;
	} // file filled with data
	rewind(con);
	// obj: to alter 5 in the file to 500 without affecting rest

	while (1)
	{
		if (fread(&t[0], sizeof(struct test), 1, con) != 1)
			break;
		printf("%d %s\n", t[0].a, t[0].b);
	} // read original
	puts("****Original*******");

	rewind(con);
	while (1)
	{
		if (fread(&t[0], sizeof(struct test), 1, con) != 1)
			break;
		if (t[0].a == 3)
		{
			t[0].a = 500;
			fseek(con, -sizeof(struct test), SEEK_CUR);
			// without this position points to end of file
			fwrite(&t[0], sizeof(struct test), 1, con);
		}
	}
	// altered
	rewind(con);
	while (1)
	{
		if (fread(&t[0], sizeof(struct test), 1, con) != 1)
			break;
		printf("%d %s\n", t[0].a, t[0].b);
	} // read modified
	puts("Modified*****");
	fclose(con);
	//remove("test");
	return 0;
}