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

state_t start_state;
void parse_input()
{
    state_t state;
    int i;

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
        add_state(state, suffix);
        for (i = 0; i < prefix_len - 1; ++i)
            state.x[i] = state.x[i + 1];
        state.x[prefix_len - 1] = suffix;
        suffix = read_word();
    }
}

void gen_output() 
{
    state_t state = start_state;
    int i, k;

    for (i = 0; i < prefix_len; ++i) {
        printf("%d %d %s\n", -1, state.x[i], get_word(state.x[i]));
    }

    for (k = 0; k < 100; ++k) {
        vector_t *v = get_suffixes(state);
        if (!v) break;
        int rand_item = abs(rand()*RAND_MAX + rand()) % v->size;
        int w = V_INT(v)[rand_item];
        printf("%d %d %s\n", rand_item, w, get_word(w));

        for (i = 0; i < prefix_len - 1; ++i)
            state.x[i] = state.x[i + 1];
        state.x[prefix_len - 1] = w;
    }
}

int main(int argc, char **argv)
{
//    freopen("../../tests/01.tst", "r", stdin);
    parse_cmdl_arguments(argc, argv);
    wordreader_init();
    preftable_init(prefix_len);
    parse_input();

    //show_table();

    gen_output();

    return 0;
}
