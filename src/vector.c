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
#include "vector.h"

/*
 * TODO: add documentation and add more error checks on memory allocation
 */

vector_t *vector_init(vector_t *vector, int type_size)
{
    vector = malloc(sizeof(vector_t));
    vector->data = NULL;
    vector->size = vector->capacity = 0;

    vector->type_size = type_size;
    return vector;
}

void vector_inc_size(vector_t *vector)
{
    if (!vector) return;
    
    vector->size += 1;
    
    if (!vector->capacity)
        vector->capacity = 1;

    if (vector->capacity < vector->size)
        vector->capasity *= 2;
    
    vector->data = realloc(vector->data, vector->capacity);
}
