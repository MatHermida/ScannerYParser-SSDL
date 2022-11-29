#include <stdio.h>
#include "parser.h"

int lexerrs = 0;
int main() {

    switch (yyparse())
    {
    case 0:
        /* code */
        break;
    }

    return 0;

}