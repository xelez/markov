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
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "htable.h"
#include "vector.h"
#include "preftable.h"

static htable_data _mem[MAX_PREFIX_COUNT];
static int prefix_len;
htable_t *prefix_table;

const long long BIG_PRIME_NUMBER = 1073676287;
const long long rand_num[] = {493840333, 281988407, 772593566, 640102565, 514641898,
                              566540301, 76837583, 523444473, 818546646, 876732988,
                              795443878, 15113677, 667205584, 100557482, 393265884,
                              355095385, 625786523, 21391585, 446742882, 571804125,
                              236016505, 535442116, 56480838, 572320172, 243967492};

static int hash_state(void *key)
{
    long long hash = 0;
    state_t *a = (state_t *)key;
    
    int i;
    for (i = 0; i < prefix_len; ++i)
        hash += rand_num[i] * a->x[i];
    
    return hash % BIG_PRIME_NUMBER;
}

static int equal_state(void *key1, void *key2)
{
    const state_t *a = (state_t *)key1;
    const state_t *b = (state_t *)key2;
    
    int i;
    for (i = 0; i < prefix_len; ++i)
        if (a->x[i] != b->x[i])
            return 0;
    return 1;
}

void preftable_init(int prefix_length)
{
    prefix_len = prefix_length;
    prefix_table = htable_init(MAX_PREFIX_COUNT, _mem, &hash_state, &equal_state);
}

void add_state(state_t *state, int suffix)
{
    htable_data *data = htable_find(prefix_table, state);

    if (!(data->key)) {
        data->key = malloc(sizeof(state_t));
        memcpy(data->key, state, sizeof(state_t));
        data->data = vector_init_int();
    }

    vector_pb_int((vector_t *)(data->data), suffix);
}

inline vector_t *get_suffixes(state_t *state)
{
    htable_data *data = htable_find(prefix_table, state);
    return (vector_t *)(data->data);
}

void show_state(state_t *state, FILE *f)
{
    fprintf(f, "state: ");
    int j;
    for (j = 0; j < prefix_len; ++j)
        fprintf(f, "%d ", state->x[j]);
}

void show_table()
{
    htable_data *d = prefix_table->data;
    const int size = prefix_table->size;
    int i, j;

    for (i = 0; i < size; ++i) {
        htable_data t = d[i];
        if (!t.key) continue;

        show_state((state_t *)t.key, stderr);
        
        fprintf(stderr, "= ");
        vector_t *v = (vector_t *)(t.data);
        for (j = 0; j < v->size; ++j)
            fprintf(stderr, "%d ", V_INT(v)[j]);
        fprintf(stderr, "\n");
    }
}
