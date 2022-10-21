#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// modules
int read_routine(char*);
int write_routine(char*);
int append_routine(char*);
int delete_routine(char*);
void read_str(char*);
//

int main(int argc, char *argv[]){
	char ans=0, file[80];

	//prompt
	puts("What would you do today?");
	puts("0. Read a file\n1. Write a file\n2. Continue write a file\n3. Delete a file");
	puts("\nEnter an option: <choice> <filename>");
	scanf("%c%*c%s", &ans, file);
	if(ans<'0' || ans>'3' || file==NULL) {
		puts("Invalid input.");
		exit(1);
	}
	//
	switch(ans){
		case '0':
		read_routine(file);
		break;
		case '1':
		write_routine(file);
		break;
		case '2':
		append_routine(file);
		break;
		case '3':
		delete_routine(file);
		break;
		default:
		puts("Invalid input.");
	}
	return 0;
}

//module definitions
int read_routine(char* file){
	FILE *fp;
	if((fp=fopen(file, "r+"))==NULL){
		puts("Sorry, operation failed.");
		exit(1);
	}
	printf("\n%s: \n", file);
	char ch=0;
	while(!feof(fp)){
		ch=fgetc(fp);
		if(!feof(fp)) putc(ch, stdout);
	}
	if(!fclose(fp)) puts("\n\nReading complete.");
	else puts("\n\nError closing file.");
	return 0;
}
int write_routine(char* f){
	FILE *fp;
	if((fp=fopen(f, "w"))==NULL){
		puts("Sorry, operation failed.");
		exit(1);
	}
	printf("\n%s: (Enter two times to quit)\n", f);
	char ch[80];
	getchar(); // flush stdin
	while(strcmp(ch, "\n\0")){
		fgets(ch, 80, stdin);
		if(strcmp(ch, "\n\0"))fputs(ch, fp);
	}
	if(!fclose(fp)) puts("\n\nEditing complete.");
	else puts("\n\nError closing file.");
	return 0;
}
int append_routine(char* f){
	FILE *fp;
	if((fp=fopen(f, "a"))==NULL){
		puts("Sorry, operation failed.");
		exit(1);
	}
	printf("\n%s: \n", f);
	read_routine(f);
	char ch[80];
	getchar();
	while(strcmp(ch, "\n\0")){
		fgets(ch, 80, stdin);
		if(strcmp(ch, "\n\0"))fputs(ch, fp);
	}

	if(!fclose(fp)) puts("\n\nEditing complete.");
	else puts("\n\nError closing file.");
	return 0;
}
int delete_routine(char* f){
	if(remove(f)) {puts("Couldn't delete file."); exit(1);}
	else printf("%s deleted successfully.", f);
	return 0;
}
void read_str(char *f){
	char ch=0;
	while(*f!='\0'){
		ch=*f++;
		printf("%d %c  ", ch, ch);
	}
	printf("%d %c\n", *f, *f);
}