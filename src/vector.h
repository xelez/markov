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

#ifndef _VECTOR_H
#define _VECTOR_H

#define V_INT(a) ((int *)( (a).data ))
#define V_STR(a) ((char **)( (a).data ))

typedef struct vector_t {
    int type_size;
    int size;
    int capacity;
    void *data;
} vector_t;

#endif /*_VECTOR_H*/

