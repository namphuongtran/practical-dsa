/*Problem: https://leetcode.com/problems/crawler-log-folder/?envType=problem-list-v2&envId=stack
*
*
*Approach: Using an value to plus and minus one every time it gone through an element.
*
*Time: O(n)
*Space: O(n)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int minOperations(char** logs, int logsSize) {
    int depth = 0;

    for (int i = 0; i < logsSize; i++) {
        if (logs[i][0] == '.' && logs[i][1] == '.') {
            if (depth > 0) {
                depth--;
            }
        } else if (logs[i][0] == '.') {
            continue;
        } else {
            depth++;
        }
    }

    return depth;
}

int minOperations(char** logs, int logsSize);

void run_test(char** logs, int n, int expected) {
    int result = minOperations(logs, n);
    assert(result == expected);
}

int main() {
    {
        char* logs[] = {"d1/", "d2/", "../", "d21/", "./"};
        run_test(logs, 5, 2);
    }

    {
        char* logs[] = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
        run_test(logs, 6, 3);
    }

    {
        char* logs[] = {"d1/", "../", "../", "../"};
        run_test(logs, 4, 0);
    }

    {
        char* logs[] = {"./", "./", "./"};
        run_test(logs, 3, 0);
    }

    {
        char* logs[] = {"d1/", "d2/", "d3/"};
        run_test(logs, 3, 3);
    }

    {
        char* logs[] = {"../", "../", "../"};
        run_test(logs, 3, 0);
    }

    printf("All tests passed!\n");
    return 0;
}