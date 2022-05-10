// Algorithm: 
// 1. Start.  
// 2. Get the input program from the file program.txt.  
// 3. Read the program line by line and check if each word in a line is a keyword, identifier, math  operator, logical operator, numerical value or others symbol.  
// 4. For each lexeme read, generate a token as follows: a. If the lexeme is a keyword, then the token is  the keyword itself. b. If the lexeme is an identifier, then the token generated is printed on the  console as identifier. c. In the same way the math operator, logical operator, numerical values and  others symbol are printed on the console.  
// 5. The stream of tokens generated are displayed in the console output.  
// 6. Stop 



#include <stdio.h> 
#include <ctype.h> 
#include <string.h> 
#include <stdlib.h> 
void keyw(char *p); 
int i = 0, id = 0, kw = 0, num = 0, op = 0; 
char keys[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",  "do", "double", "else", "enum", "extern", "float", "for", "goto", 
 "if", "int", "long", "register", "return", "short", "signed", 
 "sizeof", "static", "struct", "switch", "typedef", "union", 
 "unsigned", "void", "volatile", "while"};
int main() 
{ 
 char ch, str[25], seps[15] = " \t\n,;(){}[]#\"<>", oper[] = "!%^&*-+=~|.<>/?";  int j; 
 char fname[50]; 
 FILE *f1; 
 printf("enter file path (drive:\\fold\\filename)\n"); 
 scanf("%s", fname); 
 f1 = fopen(fname, "r"); 
 if (f1 == NULL) 
 { 
 printf("file not found"); 
 exit(0); 
 } 
 while ((ch = fgetc(f1)) != EOF) 
 { 
 for (j = 0; j <= 14; j++) 
 { 
 if (ch == oper[j]) 
 { 
 printf("%c is anoperator\n", ch); 
 op++; 
 str[i] = '\0'; 
 keyw(str); 
 } 
 } 
 for (j = 0; j <= 14; j++) 
 { 
 if (i == -1) 
 break; 
 if (ch == seps[j])
 { 
 if (ch == '#') 
 { 
 while (ch != '>') 
 { 
 printf("%c", ch); 
 ch = fgetc(f1); 
 } 
 printf("%c is a header file\n", ch);  i = -1; 
 break; 
 } 
 if (ch == '"') 
 { 
 do 
 { 
 ch = fgetc(f1); 
 printf("%c", ch); 
 } while (ch != '"'); 
 printf("\b is an argument\n");  i = -1; 
 break; 
 } 
 str[i] = '\0'; 
 keyw(str); 
 } 
 } 
 if (i != -1) 
 { 
 str[i] = ch; 
 i++;
 } 
 else 
 i = 0; 
 } 
 printf("Keywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\n", kw, id, op, num); } 
void keyw(char *p) 
{ 
 int k, flag = 0; 
 for (k = 0; k <= 31; k++) 
 { 
 if (strcmp(keys[k], p) == 0) 
 { 
 printf("%s is a keyword\n", p); 
 kw++; 
 flag = 1; 
 break; 
 } 
 } 
 if (flag == 0) 
 { 
 if (isdigit(p[0])) 
 { 
 printf("%s is a number\n", p); 
 num++; 
 } 
 else 
 { 
 if (p[0] != '\0') 
 { 
 printf("%s is an identifier\n", p);
 id++; 
 } 
 } 
 } 
 i = -1; 
} 
Input.txt: 
Hello everyone 
My name is Abishek 
#include <stdio.h> 
int main()  
{  
printf("Hello all");  
return 0;  
} 
