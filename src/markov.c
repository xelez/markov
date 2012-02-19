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
#include "vector.h"
#include "wordreader.h"
#include "preftable.h"

#define DEFAULT_PREFIX_LEN 2
#define DEFAULT_OUTPUT_LEN 1000


/* global parameters */
int prefix_len; /**< количество слов в префиксе, параметр командной строки */
int output_len; /**< максимальное количество слов в генерируемом тексте, параметр командной строки */

void usage(char *program_name)
{
    fprintf(stderr, "usage: %s [output_length] [prefix_length]\n", program_name);
    fprintf(stderr, "Program reads text from standard input and writes to standard output.\n", DEFAULT_OUTPUT_LEN);
    fprintf(stderr, "output_length - maximum number of words in output (default is %d)\n", DEFAULT_OUTPUT_LEN);
    fprintf(stderr, "prefix_length - number of words in prefix (from 1 to %d, default is %d)\n",
            MAX_PREFIX_LEN, DEFAULT_PREFIX_LEN);

    exit(1);
}

inline void parse_cmdl_arguments(int argc, char **argv)
{
    if (argc > 3)
        usage(argv[0]);

    output_len = DEFAULT_OUTPUT_LEN;
    prefix_len = DEFAULT_PREFIX_LEN;
    
    if (argc == 3)
        prefix_len = atoi(argv[2]);
    if (argc >= 2)
        output_len = atoi(argv[1]);

    if (output_len < 1 || prefix_len < 1 || prefix_len > MAX_PREFIX_LEN)
        usage(argv[0]);
}

state_t start_state;

void parse_input()
{
    state_t state;
    int i;

    // read starting state
    for (i = 0; i < prefix_len; ++i) {
        state.x[i] = read_word();
        if (state.x[i] < 1) {
            ERROR("Need more words");
            exit(1);
        }
    }
    
    start_state = state;

    int suffix = read_word();
    while (suffix > 0) {
        add_state(&state, suffix);

        for (i = 0; i < prefix_len - 1; ++i)
            state.x[i] = state.x[i + 1];
        state.x[prefix_len - 1] = suffix;

        suffix = read_word();
    }
}

void gen_output() 
{
    state_t state = start_state;
    int i = 0, k = 0;

    for (; i < prefix_len && k < output_len; ++i, ++k)
        printf("%s ", get_word(state.x[i]));
        //printf("%d %d %s\n", -1, state.x[i], get_word(state.x[i]));

    for (; k < output_len; ++k) {
        vector_t *v = get_suffixes(&state);
        if (!v) break;

        unsigned int rand_item = (unsigned int)(rand()*RAND_MAX + rand()) % (v->size);
        int w = V_INT(v)[rand_item];
        printf("%s ", get_word(w));
        //printf("%u from [0, %d): word[%d] =  %s\n", rand_item, v->size, w, get_word(w));

        for (i = 0; i < prefix_len - 1; ++i)
            state.x[i] = state.x[i + 1];
        state.x[prefix_len - 1] = w;
    }
}

int main(int argc, char **argv)
{
    parse_cmdl_arguments(argc, argv);
    wordreader_init();
    preftable_init(prefix_len);
    parse_input();

    gen_output();

    return 0;
}
