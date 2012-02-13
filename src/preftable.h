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

#ifndef _PREFTABLE_H
#define _PREFTABLE_H

#include "vector.h"

#define MAX_PREFIX_COUNT (10*1000*1000)
#define MAX_PREFIX_LEN 10
#define DEFAULT_PREFIX_LEN 2

typedef struct state_t {
    int x[MAX_PREFIX_LEN];
} state_t;

void preftable_init(int prefix_length);
void add_state(state_t state, int suffix);
vector_t *get_suffixes(state_t state);

void show_state(state_t *state, FILE *f);

#endif /* _PREFTABLE_H */
