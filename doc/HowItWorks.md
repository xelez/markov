## Принцип
Читаем текст на входе, заполняем табличку вида
    
    <prefix> | <suffix1>, <suffix2>, ...

Где `prefix` - набор из K (обычно K = 2) идущих подряд слов в тексте,
а `suffix` - слово, идущее в тексте за префиксом.

На основе её и генератора случайных чисел создаём какой-нибудь бессмысленный текст.

## Используются
 * [Хеш-таблица с открытой адресацией](http://ru.wikipedia.org/wiki/Хеш-таблица) - для
   сопоставления слов числам и префиксов возможным суффиксам.
 * Обычное хеширование строк - для сопоставления слов числам.
 * Хеш функцииии для чисел.
 * Умные динамические массивы на C (добавление N элементов суммарно за O(N), а не за O(N^2))
 * Вместо обычной хеш-таблицы с открытой адресацией можно использовать
   [Куку-хеш](https://en.wikipedia.org/wiki/Cuckoo_hashing)

## Хеш-функции

### Обозначения
 * `m` - какое-то достаточно большое простое число
 * `n` - размер хеш таблицы
 * `x` - хешируемое число

### Для хранения хешей в хеш-таблице - используется для хранения хешей от строк
 1. `(x % m) % n`
 2. `(x * RANDOM_PRIME) % n` , где `RANDOM_PRIME` - какое-то достаточно большое простое число.
 2. Что-нибудь ещё, более оригинальное

### Универсальное хеширование - используется для префиксов
    `H(x1,...,x_k) = ((a1*x1+a2*x2+...+a_k*x_k) mod p) mod m.`
где `m` - размер таблицы,
`p >> m` - простое число,
`a1, ... ,a_k` - случайные числа от `0..p-1`.

Коллизии в этом случае будут определяться уже не самими ключами, а распределением случайных чисел `a1..a_k`,
так что получится в среднем хорошее равномерное хеширование.

### Хеш 4х чисел - не используется
Если первые 4 числа генерируются достаточно хорошими хеш-функциями и независимы от друг друга,
то можно просто отксорить вместе все эти 4 числа.


## Эффективные динамические массивы на C
Можно использовать ф-ию [realloc()](http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/), но она медленная,
так что не стоит вызывать её слишком часто.

Поэтому пусть длина нашего массива всегда равняется степени 2-ки, либо нулю.
И соответственно увеличивать и уменьшать реальную длину будем только в 2 раза,
когда места будет слишком мало или слишком много.

Единственное о чём нужно заботиться - это об отдельных переменных для количества элементов в массиве
и для его реальной длины.

## Cсылки
 * <http://en.wikipedia.org/wiki/Jenkins_hash_function>
 * <http://algolist.manual.ru/ds/s_has.php>
 
