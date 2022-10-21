#include <stdio.h>
#include <stdlib.h>
#define RECORD "entries"
#define MAX_ENTRY 100

/* * @about: an accountant journal entry program features like search, edit,
   delete of entry
*/

FILE *entryfile;				// main record file
struct date
{								// date format
	short int day, month, year;
};								// 6 bytes
struct entry
{								// entry format
	int SL;
	char DEBIT[80], CREDIT[80], NARRATION[80];
	struct date d;
	float AMOUNT;
};								// 256 bytes
int prompt(void);				// start of program
void entryReader(FILE *);		// reads max entrie(s) from file
void entryReaderX(struct entry);	// reads entry to output
void entryReaderRaw(struct entry);	// one line entry output
// readers
struct entry makeEntry(void);	// create an entry and add to file, returns
								// data written
char *newlineRem(char *);
// int deleteEntries(char *);
int validator_sl();				// data validators: serial, date, amount
int validator_dt(short int *, short int *, short int *);	// pass by
															// reference
float validator_am(float);
// data entry
void modify(int, int);
// 
void searchEntry(int);
// 
void deleteEntry(int);
// 
int main(void)
{
	while (prompt() != 1);
	return 0;
}

int prompt(void)
{
	char choice = 0;
	puts("Hello, accountant!");
	puts("What would you like to do?");
	puts("1. Create new entry\
	\n2. Modify an entry\
	\n3. Search an entry\
	\n4. Delete an entry\
	\n5. View all entries\n");
	printf("Choose: ");
	scanf("%c", &choice);
	while (getchar() != '\n')
		;						// works like magic! clear buffer until
								// newline reached
	int i, j;
	i = j = 0;
	switch (choice)
	{
	case '1':
		makeEntry();
		break;
	case '2':
		puts("1. SL\n2. Date<dd/mm/yyyy>\n3. Debit\n4. Credit\n\
5. Amount\n6. Narration\n\
Enter in <SL>,<what_to_alter>:");
		scanf("%d%*c%d", &i, &j);
		while (getchar() != '\n')
			;
		modify(i, j);
		break;
	case '3':
		printf("Enter Serial No of entry: ");
		scanf("%d", &i);
		while (getchar() != '\n')
			;
		searchEntry(i);
		break;
	case '4':
		printf("Enter Serial No of entry to delete: ");
		scanf("%d", &i);
		while (getchar() != '\n')
			;
		deleteEntry(i);
		break;
	case '5':
		entryReader(entryfile);
		break;
	default:
		puts("Invalid input.");
		return 1;
	}
	return 0;
}

void entryReader(FILE * rdfrom)
{
	struct entry ent[MAX_ENTRY];	// array of all entries
	rdfrom = fopen(RECORD, "rb");
	if (rdfrom == NULL)
	{
		puts("Error: File not found.\n");
		exit(1);
	}
	int i = 0;
	while (i < MAX_ENTRY)
	{
		if (fread(&ent[i], sizeof(struct entry), 1, rdfrom) != 1)
		{
			printf("\n%d entrie(s) read.\n", i);
			return;
		}
		printf("SN: %d\n", ent[i].SL);
		printf("Date: %d/%d/%d\n", ent[i].d.day, ent[i].d.month, ent[i].d.year);
		printf("Debit: %s\n", ent[i].DEBIT);
		printf("Credit: %s\n", ent[i].CREDIT);
		printf("Amount: %f\n", ent[i].AMOUNT);
		printf("Narration: %s\n\n", ent[i].NARRATION);
		i++;
	}
	fclose(rdfrom);
}

void entryReaderX(struct entry ent)
{
	printf("SN: %d\n", ent.SL);
	printf("Date: %d/%d/%d\n", ent.d.day, ent.d.month, ent.d.year);
	printf("Debit: %s\n", ent.DEBIT);
	printf("Credit: %s\n", ent.CREDIT);
	printf("Amount: %f\n", ent.AMOUNT);
	printf("Narration: %s\n\n", ent.NARRATION);
}

void entryReaderRaw(struct entry ent)
{
	printf("%d,%d/%d/%d,%s,%s,%f,%s\n\n",
		   ent.SL, ent.d.day, ent.d.month, ent.d.year,
		   ent.DEBIT, ent.CREDIT, ent.AMOUNT, ent.NARRATION);
}

struct entry makeEntry(void)
{
	struct entry ent;
	ent.SL = validator_sl();	// auto serial

	printf("Date[dd/mm/yyyy]: ");
	scanf("%d%*c%d%*c%d", &ent.d.day, &ent.d.month, &ent.d.year);
	while (getchar() != '\n')
		;						// clear buffer
	validator_dt(&ent.d.day, &ent.d.month, &ent.d.year);
	// date validator
	printf("Debit: ");

	fgets(ent.DEBIT, 80, stdin);
	newlineRem(ent.DEBIT);		// fgets take /n in string
	// getchar not needed as nothing left

	printf("Credit: ");
	fgets(ent.CREDIT, 80, stdin);
	newlineRem(ent.CREDIT);

	printf("Amount: ");
	scanf("%f", &ent.AMOUNT);	// leaves newline hanging
	while (getchar() != '\n')
		;
	ent.AMOUNT = validator_am(ent.AMOUNT);

	printf("Narration: ");
	fgets(ent.NARRATION, 80, stdin);
	newlineRem(ent.NARRATION);

	entryfile = fopen(RECORD, "ab");
	if (entryfile == NULL)
	{
		puts("Error opening file.");
		exit(1);
	}
	if (fwrite(&ent, sizeof(struct entry), 1, entryfile) != 1)
	{
		puts("Error write. Data lost.");
		exit(1);
	}
	fclose(entryfile);
	entryReaderRaw(ent);
	return ent;
}

char *newlineRem(char *s)
{
	int i = 0;
	while (s[i++] != '\0')
		;
	i -= 2;
	s[i] = '\0';
}

int deleteEntries(char *f)
{
	return remove(f) ? 0 : 1;
}

int validator_sl()
{
	entryfile = fopen(RECORD, "rb");
	struct entry ent;
	if (entryfile == NULL || fseek(entryfile, -sizeof(struct entry), SEEK_END))
		return 1;
	fread(&ent, sizeof(struct entry), 1, entryfile);	// to read only last
														// entry
	fclose(entryfile);
	return ent.SL < 0 ? -1 : ent.SL + 1;
}

int validator_dt(short int *val, short int *val1, short int *val2)
{
	if (*val2 < 2001 | *val2 > 2022)
		*val2 = 2022;
	if (*val1 > 12 | *val1 < 1)
		*val1 = 1;
	if (*val1 == 2)
	{
		if (!*val2 % 4)
			if (*val > 29 | *val < 1)
				*val = 29;
			else if (*val > 28 | *val < 1)
				*val = 28;
	}
	if (!*val1 % 2 | *val1 == 8)
	{
		if (*val > 31 | *val < 1)
			*val = 1;
	}
	else if (*val > 31 | *val < 1)
		*val = 1;
}

float validator_am(float d)
{
	return (d > 0.0 & d < 99999.99) ? d : 1.0;
}

void modify(int sl, int which)
{
	struct entry t;
	FILE *con = fopen(RECORD, "rb+");
	if (con == NULL || which < 1 || which > 6)
	{
		puts("File/input error.");
		return;
	}
	while (1)
	{
		if (fread(&t, sizeof(struct entry), 1, con) != 1)
			break;
		if (t.SL == sl)
		{
			switch (which)
			{
			case 1:
				printf("SL: ");
				scanf("%d", &t.SL);
				while (getchar() != '\n')
					;
				break;
			case 2:
				printf("Date[dd/mm/yyyy]: ");
				scanf("%d%*c%d%*c%d", &t.d.day, &t.d.month, &t.d.year);
				while (getchar() != '\n')
					;			// clear buffer
				validator_dt(&t.d.day, &t.d.month, &t.d.year);
				// date validator
				break;
			case 3:
				printf("Debit: ");

				fgets(t.DEBIT, 80, stdin);
				newlineRem(t.DEBIT);	// fgets take /n in string
				break;
			case 4:
				printf("Credit: ");
				fgets(t.CREDIT, 80, stdin);
				newlineRem(t.CREDIT);
				break;
			case 5:
				printf("Amount: ");
				scanf("%f", &t.AMOUNT);	// leaves newline hanging
				while (getchar() != '\n')
					;
				t.AMOUNT = validator_am(t.AMOUNT);
				break;
			case 6:
				printf("Narration: ");
				fgets(t.NARRATION, 80, stdin);
				newlineRem(t.NARRATION);
			}
			fseek(con, -sizeof(struct entry), SEEK_CUR);
			// without this position points to end of file
			fwrite(&t, sizeof(struct entry), 1, con);	// altered
		}
	}

	fclose(con);
}

void searchEntry(int tofind)
{
	struct entry t;
	FILE *con = fopen(RECORD, "rb");
	if (con == NULL)
	{
		puts("File/input error.");
		return;
	}
	while (1)
	{
		if (fread(&t, sizeof(struct entry), 1, con) != 1)
			break;
		if (t.SL == tofind)
			entryReaderX(t);
		//else
			//puts("Not Found");
	}
	fclose(con);
}

void deleteEntry(int tofind)
{
	struct entry t[MAX_ENTRY];
	FILE *con = fopen(RECORD, "rb");
	int i, j;
	i = j = -1;
	if (con == NULL)
	{
		puts("File/input error.");
		return;
	}
	while (i++ < MAX_ENTRY)
	{
		if (fread(&t[i], sizeof(struct entry), 1, con) != 1)
			break;
		if (t[i].SL == tofind)
			--i;
	}
	j = i;						// i is 1 extra, if 0 based
	fclose(con);
	remove(RECORD);
	i = 0;
	con = fopen(RECORD, "wb+");
	if (con == NULL)
	{
		puts("File/input error.");
		return;
	}
	while (i < j)
	{
		if (fwrite(&t[i], sizeof(struct entry), 1, con) != 1)
			break;
		else
			i++;
	}
	fclose(con);
}