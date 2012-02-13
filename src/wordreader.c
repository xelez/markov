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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "log.h"
#include "vector.h"
#include "htable.h"
#include "wordreader.h"

#define IS_DELIMETER(c) ((c) == ' ' || (c) == '\t' || (c) == '\n')
#define MAX_WORD_LEN 100
#define MAX_WORD_K (10*1000*1000)

static htable_data _mem[MAX_WORD_K];
vector_t *words;
htable_t *word_num;
int words_k;

void wordreader_init()
{
    words_k = 1;
    words = vector_init_str();
    vector_pb_str(words, NULL);
    word_num = htable_init(MAX_WORD_K, _mem, &htable_hash_str, &htable_equal_str);
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

    char *result = (char *) malloc((l + 1) * sizeof(char));
    memcpy(result, s, l);
    result[l] = '\0';
    return result;
}

int read_word()
{
    char *w = parse_word();
    if (!w)
        return -1;

    htable_data *d = htable_find(word_num, w);
    if (d->key) {
        free(w);
        return INT(d->data);
    } else {
        vector_pb_str(words, w);
        d->key = w;
        d->data = malloc(sizeof(int));
        INT(d->data) = words_k;
        
        return words_k++;
    }
}

char *get_word(int num)
{
    return V_STR(words)[num];
}
