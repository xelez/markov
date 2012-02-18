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
#include <string.h>
#include <math.h>

#include "log.h"
#include "htable.h"

const int RANDOM_BIG_PRIME = 9369319;
const int RANDOM_SMALL_PRIME = 997;

/**
 * htable_hash_str - считает хэш строки key
 *
 * @return число от 0 до MAX_INT
 */
int htable_hash_str(void *key)
{
    int h = 0;
    char *c = (char *)key;
    while (*c) {
        h = h * RANDOM_SMALL_PRIME + (*c);
        ++c;
    }
    return abs(h);
}

int htable_equal_str(void *key1, void *key2)
{
    return !(strcmp((char *)key1, (char *)key2));
}


/**
 * htable_init - создать новую хеш-таблицу, хранящую указатели.
 *
 * Разрешение коллизий на основе аналога открытой адресации.
 * (http://ru.wikipedia.org/wiki/%D0%A5%D0%B5%D1%88-%D1%82%D0%B0%D0%B1%D0%BB%D0%B8%D1%86%D0%B0)
 * 
 * @param size размер хеш-таблицы, желательно брать примерно 2*N,
 *             где N - максимально возможное количество элементов в хеш-таблице
 *
 * @param data указатель на массив для хранения данных,
 *             если NULL, то память будет выделенна автоматически.
 * 
 * @param hash_key ф-ия для хеширования ключей
 *
 * @param key_equal ф-ия для сравнения ключей
 *
 * @return указатель на htable_t
 */
htable_t* htable_init(int size, htable_data *data,
            hash_key_func hash_key, key_equal_func key_equal)
{
    htable_t *htable = malloc(sizeof(htable_t));

    if (!data) {
        data = (htable_data *) malloc(sizeof(htable_data) * size);
    }
    memset(data, 0, sizeof(htable_data) * size);

    htable->size = size;
    htable->data = data;
    htable->hash_key  = hash_key;
    htable->key_equal = key_equal;
    
    return htable;
}

/**
 * htable_find - найти соответствующую данному ключу строчку в хеш-таблице
 *
 * @return указатель на htable_data, соответствующий строке в таблице.
 *         Изменяя структуру по этому указателю можно добавлять или удалять данные из таблицы.
 */
htable_data *htable_find(htable_t *htable, void *key)
{
    if (!htable || !key)
        return NULL;

    long long h = htable->hash_key(key) % htable->size;
    htable_data *row = &(htable->data[h]);
    
    while ( (row->key) && !(htable->key_equal(key, row->key)) ) {
        h = ( (h + 123) * RANDOM_BIG_PRIME) % htable->size;
        row = &(htable->data[h]);
    }

    return row;
}
