# Содержание

- [Задание](#задание)
- [Пояснения к решению](#пояснения-к-решению)
- [Как запустить](#как-запустить)

# Задание

Есть некоторый набор из N строк (N > 0). Все они уникальные. Есть набор из M контейнеров строк (0 < M < N).
Числа M и N читаются из стандартного ввода. Данные числа представимы беззнаковым целочисленным типом данных с размером
64 бита.

Требуется по заданной строке найти контейнер, её содержащий. Искомой строки может в контейнере и не быть.
Программа должна выводить информацию о начальном наполнении контейнеров строками, запрашивать искомую строку и выводить
какой-нибудь идентификатор контейнера.

# Пояснения к решению

Это задание на С++, но на конференции у стойки сказали решить его на С.
Решил применить AVL дерево для оптимального поиска за `O(log2n)` и наличия свойства сбалансированности.
Реализована примитивная функция хэширования на больших наборах данных будут коллизии. В этом примере их нет. Так же
могут быть ложно положительные срабатывания поиска при такой простой функции хэширования.

# Как запустить

Linux

```shell
gcc main.c && ./a.out
```
 
