/*Problem: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
*Given an character s that point to an array. Remove the duplicate of two same letter that adjacent. Repeat the process after the same adjacent couple disappear until all adjacent was deleted.
*
*Approach: There are 2 main way to solve this problem, using stack and 2 pointer. With stack, using the fundamental concept of stack should do the math.
*
*Time: O(n)
*Space: O(n)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeDuplicates(char* s){
    int top = -1;
    for(int i = 0; s[i] != '\0'; i ++){
        if(top >= 0 && s[i] == s[top]){
            top--;
        }
        else{
            top++;
            s[top] = s[i];
        }
    }

    s[top + 1] = '\0';
    return s;
}

/*This solution optimize the memory that given by char *s so the machine don't have to give extra memory for heap
*/

int main(){
    char s1[] = "abbaca";
    assert(strcmp(removeDuplicates(s1), "ca") == 0);

    char s2[] = "azxxzy";
    assert(strcmp(removeDuplicates(s2), "ay") == 0);

    char s3[] = "aaaa";
    assert(strcmp(removeDuplicates(s3), "") == 0);

    char s4[] = "abc";
    assert(strcmp(removeDuplicates(s4), "abc") == 0);

    char s5[] = "aababaab";
    assert(strcmp(removeDuplicates(s5), "ba") == 0);

    printf("All test cases passed!\n");

    return 0;
}