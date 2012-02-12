/*
 *  Copyright 2012 Alexander Ankudinov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

#define IS_DELIMETER(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')

#define MAX_WORD_LEN 100
static const int DEFAULT_PREFIX_LEN = 2;
static const int MAX_PREFIX_LEN = 10;

int prefix_len;

void usage(char *program_name)
{
    fprintf(stderr, "usage: %s [prefix_length]\n", program_name);
    fprintf(stderr, "prefix_length - number of words in prefix (from 1 to %d)\n", MAX_PREFIX_LEN);
    exit(1);
}

inline void parse_cmdl_arguments(int argc, char **argv)
{
    if (argc > 2)
        usage(argv[0]);
    
    if (argc == 2) {
        prefix_len = atoi(argv[1]);
        if (prefix_len < 1 || prefix_len > MAX_PREFIX_LEN)
            usage(argv[0]);
    } else {
        prefix_len = DEFAULT_PREFIX_LEN;
    }
}
/*
 * parse_word() - reads input and returns string containing one word
 *
 * Returns NULL if reaches the end of input.
 * You must free memory allocated by this function when you don`t need it anymore.
 */
char *parse_word()
{
    static char s[MAX_WORD_LEN];
    int l = 0;
    int c;
    do {
        c = fgetc(stdin);
    } while ( c != EOF && IS_DELIMETER(c) );

    if (c == EOF)
        return NULL;

    while ( c != EOF && !IS_DELIMETER(c)) {
        s[l++] = c;
        if (l >= MAX_WORD_LEN)
            break;
        c = fgetc(stdin);
    }

    char *result = (char *) malloc((l+1) * sizeof(char));
    memcpy(result, s, l);
    result[l] = '\0';
    return result;
}

int read_word()
{
    char *w = parse_word();

}

void parse_input()
{
    char *t;
    t = parse_word();
    while (t != NULL) {
        DEBUG("%s", t);
        t = parse_word();
    }
}

int main(int argc, char **argv)
{
    parse_cmdl_arguments(argc, argv);
    parse_input();

    return 0;
}
