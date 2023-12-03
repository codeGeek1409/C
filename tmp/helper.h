// @author: codeGeek1409
// @dep: stdio string
void read_file(FILE *fp){
  char ch=0;
  while(1){
    if((ch=fgetc(fp))==(char) EOF) break;
    putchar(ch);
  }
}
void read_line(FILE *fp, char tmp[]){
  char c=0;
  int i=0;
  while((c=fgetc(fp))!='\n')
    tmp[i++]=c;
  tmp[i]='\0';
}
void read_string(char str[]){
  for(int i=0; i<=strlen(str); i++){
    printf("%d) %c: %d\n", i, str[i], str[i]);
  }
}
void extract_last_word(char str[], char tmp[]){
  int i=0, till=0, from=0;
  i=strlen(str);
  while(str[i--]!=13) {} till = i;
  while(str[--i]!=32) {} from=i+1; i=0;
  while(i < till-from) tmp[i++] = str[from+i];
  tmp[i]='\0';
}
void filter_drive_path(char str[]){
  for(int i=0; i<strlen(str); i++) 
    if(str[i]=='\r') str[i]='\0';
}
void reset_string(char str[], int len){
  for(int i=0;i<len;i++){
    str[i]='\0';
  }
}
void print_infinit(int len){
  while(len-->0) puts("Testing Testing Testing");
}