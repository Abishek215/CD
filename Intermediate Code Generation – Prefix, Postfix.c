// Algorithm:
// 1. Declare a set of operators 
// 2. Initialize an empty stack 
// 3. To convert INFIX to POSTFIX follow the following steps 
// 4. Scan the infix expression from left to right 
// 5. If the scanned character is an operand, output it. 
// 6. Else, If the precedence of the scanned operator is greater than the precedence of the operator in the stack(or the stack is empty or the stack contains a ‘(‘ ), push it. 
// 7. Else, Pop all the operators from the stack which are greater than or equal to in precedence than that of the scanned operator. After doing that Push the scanned operator to the stack 
// 8. If the scanner character is an ‘(‘ . Push it to the Stack 
// 9. If the scanned character is an ‘)’, pop the stack and output it until a ‘(‘ is encountered, and discard both the parenthesis 
// 10.Pop and Output the stack until it is not empty. 
// 11. To convert INFIX to PREFIX follow the following steps 
// 12.Reverse the infix expression in the problem first. 
// 13.Scan the expression from left to right. 
// 14.Whenever the operands arrive, print them 
// 15.If the operator arrives and the stack is found to be empty, then simply push the operator into the stack. 
// 16.Repeat Steps 6 to 9 until the Stack is Empty. 




#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#define MAX 15
int stack_top = -1;
char operators_stack[MAX]={'\0'}; // used in infix-postfix and infix-prefix conversions
char operands_stack[MAX][MAX]={'\0'}; // used in postfix-infix and prefix-infix conversions
char infix_exp[MAX]={'\0'};
char prefix_exp[MAX]={'\0'};
char postfix_exp[MAX]={'\0'};
int evaluate(char in[]);
int expressionType(char in[]);
int priority(char in);
int IsOpening(char in);
int IsClosing(char in);
int imbalancedParentheses(char in[]);
void clearStacks(void);
void pushOperator(char newTop);
void pushOperand(char newTop[]);
void pop(void);
void infixTOpostfix(char in[]);
void infixTOprefix(char in[]);
void postfixTOinfix(char in[]);
void prefixTOinfix(char in[]);
int main(){
 char inArray[MAX]={'\0'};
 char infix[MAX]={'\0'};
 char postfix[MAX]={'\0'};
 char prefix[MAX]={'\0'};
 int i, type, opening=0, closing=0;
 char choice, conversion_instruction;
 printf("Enter an expression: ");
 fgets(inArray, MAX, stdin);
 if (imbalancedParentheses(inArray))
 return 0;
 type = expressionType(inArray);
 while (choice!='C'){
 printf("\nSelect what you want to do:\n");
 printf("(A) Convert the expression.\n(B) Evaluate the expression.\n(C) Exit.\n");
 printf("Your choice: ");
 scanf(" %c", &choice);
 choice = toupper(choice); // for easier comparisons
 if (choice=='A'){ // if user asks for conversions
 if (type==1){ // if expression is infix
 printf("\nThis is an infix expression.\nChoose what you want the expression to be
converted to:\n");
 printf("(A) Postfix.\n(B) Prefix.\n(C) Both.\nYour choice: ");
 scanf(" %c", &conversion_instruction); // get user's choice of conversion
 conversion_instruction = toupper(conversion_instruction); // for easier comparisons
 if (conversion_instruction == 'A'){
 infixTOpostfix(inArray); // convert infix expression to postfix
 printf("\nPostfix expression: %s\n", postfix_exp); // output postfix expression
 clearStacks();
 }
 else if (conversion_instruction == 'B'){
 infixTOprefix(inArray); // convert infix expression to prefix
 printf("\nPrefix expression: %s\n", prefix_exp); // output prefix expression
 clearStacks();
 }
 else if (conversion_instruction == 'C'){
 infixTOpostfix(inArray); // convert infix expression to postfix
 printf("\nPostfix expression: %s\n", postfix_exp); // output postfix expression
 clearStacks();
 infixTOprefix(inArray); // convert infix expression to prefix
 printf("Prefix expression: %s\n", prefix_exp); // output prefix expression
 clearStacks();
 }
 break; // break to end the program
 }
 else if (type==2){ // if expression is prefix
 printf("\nThis is a prefix expression.\nChoose what you want the expression to be
converted to:\n");
 printf("(A) Infix.\n(B) Postfix.\n(C) Both.\nYour choice: ");
 scanf(" %c", &conversion_instruction); // get user's choice of conversion
 conversion_instruction = toupper(conversion_instruction); // for easier comparisons
 if (conversion_instruction == 'A'){
 prefixTOinfix(inArray); // convert prefix expression to infix
 printf("\nInfix expression: %s\n", infix_exp); // output infix expression
 clearStacks();
 }
 else if (conversion_instruction == 'B'){
 prefixTOinfix(inArray); // convert prefix expression to infix
 infixTOpostfix(infix_exp); // convert infix expression to postfix
 printf("\nPostfix expression: %s\n", postfix_exp); // output postfix expression
 clearStacks();
 }
 else if (conversion_instruction == 'C'){
 prefixTOinfix(inArray); // convert prefix expression to infix
 printf("\nInfix expression: %s\n", infix_exp); // output infix expression
 infixTOpostfix(infix_exp); // convert infix expression to postfix
 printf("Postfix expression: %s\n", postfix_exp); // output postfix expression
 clearStacks();
 }
 break; // break to end program
 }
 else if (type==3){ // if expression is postfix
 printf("\nThis is a postfix expression.\nChoose what you want the expression to be
converted to:\n");
 printf("(A) Infix.\n(B) Prefix.\n(C) Both.\nYour choice: ");
 scanf(" %c", &conversion_instruction); // get user's choice of conversion
 conversion_instruction = toupper(conversion_instruction); // for easier comparisons
 if (conversion_instruction == 'A'){
 postfixTOinfix(inArray); // convert postfix expression to infix
 printf("\nInfix expression: %s\n", infix_exp); // output infix expression
 clearStacks();
 }
 else if (conversion_instruction == 'B'){
 postfixTOinfix(inArray); // convert postfix expression to infix
 infixTOprefix(infix_exp); // convert infix expression to prefix
 printf("\nPrefix expression: %s\n", prefix_exp); // output prefix expression
 clearStacks();
 }
 else if (conversion_instruction == 'C'){
 postfixTOinfix(inArray); // convert postfix expression to infix
 printf("\nInfix expression: %s\n", infix_exp); // output infix expression
 infixTOprefix(infix_exp); // convert infix expression to prefix
 printf("Prefix expression: %s\n", prefix_exp); // output prefix expression
 }
 break; // break to end program
 } }
 else if (choice == 'B'){ // if user chose to evaluate the expression
 if (type==1){ // if expression is infix
 infixTOpostfix(inArray); // convert infix expression to postfix
 printf("\nResult = %d\n", evaluate(postfix_exp)); // output the evaluation result
 }
 else if (type==2){ // if expression is prefix
 prefixTOinfix(inArray); // convert prefix expression to infix
 infixTOpostfix(prefix_exp); // convert infix expression to postfix
 printf("\nResult = %d\n", evaluate(postfix_exp)); // output the evaluation result
 }
 else{ // if expression is postfix
 printf("\nResult = %d\n", evaluate(inArray)); // output the evaluation result
 }
 break; // break to end program
 }
 else if (choice == 'C'){ // if user chose to exit the program
 return 0; // end program
 }
 else{ // if input is invalid
 printf("Invalid input value.\n");
 break; // break to end program
 } }
 return 0; // indicates successful execution
}
void infixTOpostfix(char in[]){
 char outArray[MAX]={'\0'};
 int i, j=0;
 for (i=0; i<=MAX-1; i++){
 if (isalnum(in[i])){ // if character is an operand
 outArray[j++]=in[i]; // push operand into the output array
 }
 else if (IsOpening(in[i])){ // if character is an opening parenthesis
 pushOperator(in[i]); // push the parenthesis into the stack
 }
 else if (IsClosing(in[i])){ // if character is a closing parenthesis
 while (stack_top!=-1 && !IsOpening(operators_stack[stack_top])){
 outArray[j++]=operators_stack[stack_top]; // push stack top into the output array
 pop(); // pop the top of the stack
 }
 pop(); // pop the opening parenthesis
 }
 else if (!isspace(in[i])){ // if character is an operator
 while (stack_top!=-1 && priority(operators_stack[stack_top]) >= priority(in[i]) &&
!IsOpening(operators_stack[stack_top])){
 outArray[j++]=operators_stack[stack_top]; // push stack top into the output array
 pop(); // pop the top of the stack
 }
 pushOperator(in[i]); // push the operator into the stack
 } }
 while (stack_top!=-1){
 outArray[j++]=operators_stack[stack_top];
 pop();
 }
 for (i=0, j=0; outArray[i]!='\0'; i++){
 postfix_exp[j++]=outArray[i];
 postfix_exp[j++]=' ';
 postfix_exp[j++]=' ';
 }}
void infixTOprefix(char in[]){
 char tempArray[MAX]={'\0'};
 char outArray[MAX]={'\0'};
 int i=0, m, n, temp, j=0;
 strcpy(tempArray, in);
 for (m=MAX-1; m>=0; m--){
 if (tempArray[m]=='\0'){
 continue;
 }
 else {
 in[i++]=tempArray[m];
 } }
 for (i=0, j=0; i<=MAX-1; i++){
 if (isalnum(in[i])){ // if character is an operand
 outArray[j++]=in[i]; // push the operand into the output array
 }
 else if (IsClosing(in[i])){ // if character is a closing parenthesis
 pushOperator(in[i]); // push the parenthesis into the stack
 }
 else if (IsOpening(in[i])){ // if character is an opening parenthesis
 while (stack_top!=-1 && !IsClosing(operators_stack[stack_top])){
 outArray[j++]=operators_stack[stack_top]; // push the stack top into the output array
 pop(); // pop the top of the stack
 }
 pop(); // pop the closing parenthesis
 }
 else if (!isspace(in[i])){ // if character is an operator
 while (stack_top!=-1 && priority(operators_stack[stack_top]) >= priority(in[i]) &&
!IsClosing(operators_stack[stack_top])){
 outArray[j++]=operators_stack[stack_top]; // push the top of the stack into the output
array
 pop(); // pop the top of the stack
 }
 pushOperator(in[i]); // push the operator into the stack
 } }
 while (stack_top!=-1){
 outArray[j++]=operators_stack[stack_top];
 pop();
 }
 strcpy(tempArray, outArray);
 for (i=0; tempArray[i]!='\0'; i++);
 for (n=0, m=i; m>=0; m--){
 if (tempArray[m]!='\0' && !IsOpening(tempArray[m]) && !IsClosing(tempArray[m]))
 outArray[n++]=tempArray[m];
 }
 for (i=0, j=0; i<MAX-1; i++){
 prefix_exp[j++]=outArray[i];
 prefix_exp[j++]=' ';
 prefix_exp[j++]=' ';
 }}
void postfixTOinfix(char in[]){
 char outArray[MAX]={'\0'};
 char op1[MAX]={'\0'};
 char op2[MAX]={'\0'};
 char temp[MAX]={'\0'};
 char hold[2]={'\0'};
 char temp_string[2]={'\0'};
 int i, j=0, m, n, operand_count=0;
 for (i=0; in[i]!='\0'; i++){
 if (isalnum(in[i])){ // if character is an operand
 temp_string[0]=in[i]; // convert the operand into a string
 pushOperand(temp_string); // push the operand into the stack
 operand_count++;
 }
 else {
 if (operand_count>=2){ // if there are two operands in the stack
 for (m=1; operands_stack[stack_top][m]!='\0'; m++);
 strncpy(op2, operands_stack[stack_top], m);
 pop(); // pop the stack top
 for (m=1; operands_stack[stack_top][m]!='\0'; m++);
 strncpy(op1, operands_stack[stack_top], m);
 pop(); // pop the stack top
 for (m=0; op1[m]!='\0'; m++);
 strncat(temp, op1, m);
 hold[0] = in[i];
 hold[1] = '\0';
 strcat(temp, hold);
 for (n=1; op2[n]!='\0'; n++);
 strncat(temp, op2, n);
 temp[n+2]='\0'; // terminate temp array
 pushOperand(temp); // push temp array into the stack
 operand_count--;
 temp[0]='\0'; // clear array temp
 }
 operand_count = (operand_count) ? 0 : operand_count;
 } }
 strcpy(infix_exp, operands_stack[stack_top]);
}
void prefixTOinfix(char in[]){
 char outArray[MAX]={'\0'};
 char exp[MAX]={'\0'};
 char op1[MAX]={'\0'};
 char op2[MAX]={'\0'};
 char temp[MAX]={'\0'};
 char hold[2]={'\0'};
 char temp_string[2]={'\0'};
 int i, j, m, n, operand_count=0;
 for (j=0, i=strlen(in)-1; i>=0; i--){
 exp[j++]=in[i];
 }
 for (i=0; exp[i]!='\0'; i++){
 if (isalnum(exp[i])){ // if character is an operand
 temp_string[0]=exp[i]; // convert the operand into a string
 pushOperand(temp_string); // push the operand into the stack
 operand_count++;
 }
 else {
 if (operand_count>=2){ // if there are two operands in the stack
 for (m=1; operands_stack[stack_top][m]!='\0'; m++);
 strncpy(op1, operands_stack[stack_top], m);
 pop(); // pop the stack top
 strncpy(op2, operands_stack[stack_top], m);
 pop(); // pop the stack top
 for (m=0; op1[m]!='\0'; m++);
 strncat(temp, op1, m);
 hold[0] = exp[i];
 hold[1] = '\0';
 strcat(temp, hold);
 for (n=1; op2[n]!='\0'; n++);
 strncat(temp, op2, n);
 temp[n+2]='\0'; // terminate temp array
 pushOperand(temp); // push temp array into the stack
 operand_count--;
 temp[0]='\0'; // clear array temp
 }
 operand_count = (operand_count) ? 0 : operand_count;
 } }
 strcpy(infix_exp, operands_stack[stack_top]);
}
int imbalancedParentheses(char in[]){
 int i, opening=0, closing=0;
 int code = expressionType(in);
 for (i=0; i<MAX-1; i++){
 opening += (IsOpening(in[i]))? 1 : 0;
 closing += (IsClosing(in[i]))? 1 : 0;
 }
 if (code==1 && opening!=closing){ // if expression is infix and parentheses are imbalanced
 printf("Imbalanced parentheses.\nRestart the program.\n");
 return 1;
 }
 else if ((code==2 || code==3) && (opening!=0 || closing!=0)){ // if expression is postfix or
prefix and contains parentheses
 printf("Invalid input.\nPostfix and Prefix expressions should be parenthesis-free.\nRestart
the program.\n");
 return 1;
 }
 else // if parentheses are balanced
 return 0;
}
int evaluate(char in[]){
 int operands[MAX]={0};
 int op1=0, op2=0;
 int i, count=-1;
 for (i=0; in[i]!='\0'; i++){
 if (isdigit(in[i])){ // if character is an operand
 operands[++count]=in[i]-'0'; // convert character into integer and push it into the stack
 }
 else if (in[i]=='+' || in[i]=='-' || in[i]=='*' || in[i]=='/' || in[i]=='^'){ // if character is an operator
 op1 = operands[count--];
 op2 = operands[count--];
 switch (in[i]){
 case '+': // if addition, add the operands and push the result into the stack
 operands[++count] = op1 + op2;
 break;
 case '-': // if subtraction, subtract op1 from op2 and push the result into the stack
 operands[++count] = op2 - op1;
 break;
 case '*': // if multiplication, multiply the operands and push the result into the stack
 operands[++count] = op1 * op2;
 break;
 case '/': // if division, divide op2 by op1 and push the result into the stack
 operands[++count] = op2 / op1;
 break;
 case '^': // if power, raise op2 to the power of op1 and push the result into the stack
 operands[++count] = pow(op2,op1);
 break;
 } } }
 return operands[count];
}
int priority(char in){
 switch(in){
 case '(':
 return 1;
 case '+':
 case '-':
 return 2;
 case '*':
 case '/':
 return 3;
 case '^':
 return 4;
 }}
int expressionType(char in[]){
 char exp[5]={'\0'};
 int i, j=1, operand_counter=0;
 for (i=0; i<MAX-1; i++){
 if (in[i]!='\0' && !isspace(in[i]) && !IsOpening(in[i]) && !IsClosing(in[i])){
 exp[j++]=in[i];
 } }
 i=1;
 while (i<4){
 if (exp[1]=='*'||exp[1]=='/'||exp[1]=='+'||exp[1]=='-')
 return 2; // expression is prefix
 else if (isalnum(exp[1]) && (exp[2]=='*'||exp[2]=='/'||exp[2]=='+'||exp[2]=='-'))
 return 1; // expression is infix
 i++;
 }
 return 3; // expression is postfix
}
void pushOperator(char newTop){
 operators_stack[++stack_top] = newTop;
}
void pushOperand(char newTop[]){
 strcpy(operands_stack[++stack_top], newTop);
}
void pop(void){
 stack_top--;
}
int IsOpening(char in){
 return (in=='('||in=='['||in=='{')? 1 : 0;
}
int IsClosing(char in){
 return (in==')'||in==']'||in=='}')? 1 : 0;
}
void clearStacks(void){
 operands_stack[0][0]='\0';
 operators_stack[0]='\0';
 stack_top=-1;
 infix_exp[0]='\0';
 prefix_exp[0]='\0';
 postfix_exp[0]='\0';
}
