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

/* No debug output */
#define NO_TRACE_OUTPUT

#include <stdlib.h>

#include "log.h"
#include "vector.h"

vector_t *vector_init(int type_size)
{
    vector_t *vector = malloc(sizeof(vector_t));
    memset(vector, 0, sizeof(vector_t));
    
    vector->type_size = type_size;
    return vector;
}

void vector_inc_size(vector_t *vector)
{
    if (!vector) return;
    
    ++(vector->size);
    
    if (vector->capacity < vector->size) {
        if (!vector->capacity)
            vector->capacity = 1;
        else
            vector->capacity *= 2;

        if (vector->capacity > 100)
            TRACE("resize to %d elems, %d bytes of memory", vector->capacity, (vector->capacity) * (vector->type_size));
        
        vector->data = realloc(vector->data, (vector->capacity) * (vector->type_size));
    }
}

vector_t *vector_init_int()
{
    return vector_init(sizeof(int));
}

vector_t *vector_init_str()
{
    return vector_init(sizeof(char *));
}

void vector_pb_int(vector_t *v, int i)
{
    vector_inc_size(v);
    V_INT(v)[v->size - 1] = i;
}

void vector_pb_str(vector_t *v, char *s)
{
    vector_inc_size(v);
    V_STR(v)[v->size - 1] = s;
}
