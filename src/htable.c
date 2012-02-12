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

#include <string.h>
#include <math.h>

#include "htable.h"

const int RANDOM_BIG_PRIME = 9369319;
const int RANDOM_SMALL_PRIME = 997;

int htable_hash_str(void *key)
{
    int h;
    char *c = (char *)key;
    while (c) {
        h = h * RANDOM_SMALL_PRIME + (*c);
        ++c;
    }
    return abs(h);
}

bool htable_equal_str(void *key1, void *key2)
{
    return !(strcmp((char *)key1, (char *)key2));
}

void htable_init(htable_s *htable, int size, htable_data *data,
            hash_key_func hash_key, key_equal_func key_equal)
{
    if (!htable)
        return;

    if (!data) {
        data = (htable_data *) malloc(sizeof(htable_data) * size);
        memset(data, 0, sizeof(htable_data) * size);
    }

    htable->size = size;
    htable->data = data;
    htable->hash_key  = hash_key;
    htable->key_equal = key_equal;
}

htable_data *htable_find(htable_s *htable, void *key)
{
    if (!htable || !hkey)
        return NULL;

    long long h = htable->hash_key(key) % htable->size;
    htable_data *r = htable->data[h];
    
    while (!r->key && !htable->key_equal(key, r->key)) {
        h = ( (h + 123) * RANDOM_BIG_PRIME) % htable->size;
        r = htable->data[h];
    }

    return r;
}
