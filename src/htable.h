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

#ifndef _HTABLE_H
#define _HTABLE_H

#define INT(a) ( *((int *)(a)) )

/** Тип ф-ии для сравнения ключей */
typedef int ( *key_equal_func ) (void *, void *);

/** Тип ф-ии для хешерования ключа */
typedef int ( *hash_key_func ) (void *);

/** Строка хеш-таблицы */
typedef struct htable_data {
    void *key;  /**< указатель на ключ */
    void *data; /**< указатель на значение */
} htable_data;

/** Хеш-таблица */
typedef struct htable_t {
    htable_data *data; /**< указатель на массив строк хеш-таблицы */
    int size;          /**< размер таблицы */
    
    hash_key_func  hash_key;  /**< ф-ия хеширования ключа */
    key_equal_func key_equal; /**< ф-ия сравнения двух ключей */
} htable_t;

int htable_hash_str(void *key);
int htable_equal_str(void *key1, void *key2);

htable_t* htable_init(int size, htable_data *data,
            hash_key_func hash_key, key_equal_func key_equal);

htable_data *htable_find(htable_t *htable, void *key);

#endif /*_HTABLE_H*/

