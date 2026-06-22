/*Problem: https://leetcode.com/problems/valid-parentheses/description/?envType=problem-list-v2&envId=stack
*Given a string contain parentheses, if the string open and close every couple of parentheses in correct order, return true, else, return false.
*
*Approach: Loop through the string, using stack to store the most recent open parenthes and compare with the current close parenthes. If they're the same, continue, else return false. After loop through the string, if there are any left parenthes, return false
*
*Space: O(n)
*Time: O(n)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TEST(str, expected) do {        \
    char s[] = str;                     \
    assert(isValid(s) == expected);     \
} while (0)

bool isValid(char* s) {
    int top = -1;

    for(int i = 0; s[i] !='\0'; i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            top++;
            s[top] = s[i];
        }
        if(s[i] == ')' || s[i] == '}' || s[i] == ']'){
            if(top <0){
                return false;
            }
            if(s[i] == ')' && s[top] == '('){
                top--;
            }
            else if(s[i] == ']' && s[top] == '['){
                top--;
            }           
            else if(s[i] == '}' && s[top] == '{'){
                top--;
            }
            else{
                return false;
            }
        }
    }
    if(top != -1){
        return false;
    }
    return true;
}

int main() {
    TEST("()", true);
    TEST("[]", true);
    TEST("{}", true);
    TEST("()[]{}", true);
    TEST("({[]})", true);
    TEST("{{[[(())]]}}", true);

    TEST(")", false);
    TEST("]", false);
    TEST("}", false);
    TEST(")(", false);

    TEST("(]", false);
    TEST("(}", false);
    TEST("([)]", false);
    TEST("{[}]", false);

    TEST("(", false);
    TEST("(()", false);
    TEST("(((", false);

    printf("All tests passed!\n");
    return 0;
}