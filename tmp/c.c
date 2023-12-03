#include<stdio.h>
#include<string.h>
#include"helper.h"
// @author: codeGeek1409
// error: segmentaion fault in end
int main(void) {
  // vars
  FILE* fp; // file stream
  char* source_file_name = "tree_out.txt"; // sample hard coded file
  char line_reader[500]; // line holder
  // main data
  char VOL_LBL[20];
  char VOL_NUM[20];
  char DRV;
  char DIR_STK[20][100];
  // debug
  int STK_LVL = 0; // directory stack
  //
  // open file safely
  if ((fp = fopen(source_file_name, "r")) == NULL) {
    puts("File not found.");
    return 1;
  }
  // final loop
  do {
    // local vars
    int i = 0; // line reader index
    int j = 0; // STK index
    int isDir = 0; // dir check
    int isEnd = 0; // level out check
    char FL[200]; // file holder
    //
    // process one line at a time
    read_line(fp, line_reader);
    if(feof(fp)) break; // get out on eof
    //
    // drive change sequence
    if (line_reader[i] == 'F') { // in case of joined outputs
      STK_LVL=0; // reset after first round
      extract_last_word(line_reader, VOL_LBL);
      read_line(fp, line_reader);
      extract_last_word(line_reader, VOL_NUM);
      read_line(fp, DIR_STK[STK_LVL]);
      filter_drive_path(DIR_STK[STK_LVL]);
      continue;
    }
    //
    // parameter processor loop
    while (line_reader[i] == '|' || line_reader[i] == ' ' ||
      line_reader[i] == '-' || line_reader[i] == '+' || line_reader[i] == '\\') {
      switch (line_reader[i]) {
      case '|': // level indicator
        i += 4;
        break;
      case '+' :
      case '\\': // directory indicators
        isDir = 1;
        i += 4;
        break;
      default: // for extra space
        i++;
      }
    }
    //
    // level out catcher
    if (line_reader[i] == '\r') {
      isEnd = 1;
      if (STK_LVL > 0) STK_LVL--;
      continue;
    }
    //
    // dir caught sequence
    if (isDir) {
      STK_LVL++;
      while (line_reader[i]!='\0' && line_reader[i] != '\r') 
        DIR_STK[STK_LVL][j++] = line_reader[i++]; 
      DIR_STK[STK_LVL][j] = '\0';
    }
    //
    // file caught sequence
    else {
      while (line_reader[i]!='\0' && line_reader[i] != '\r') 
        FL[j++] = line_reader[i++];
      FL[j] = '\0';
    }
    //
    // printer- directory
    printf("\""); // stringify
    for (int i = 0;i <= STK_LVL;i++) {
        printf("%s", DIR_STK[i]);
        putchar('\\');
    }
    // printer- file
    if (!isDir) printf("%s", FL);
    printf("\""); // stringify
    putchar('\n');
    //
  } while (!feof(fp));
  fclose(fp);
  return 0;
}