# Описание алгоритма:
Парсим строку, далее идем по дереву операций от корня к детям через dfs и насчитываем пару значений для слов, которые соответсвуют данной вершине: 

1) Сколько максимум букв "x" стоит в конце слова, где перед этими буквами стоит буква, отличная от "x" (имеет значение -1, если там только слова стостоящие только из букв "x", в том числе пустое слово).

2) Максимальная длина слова, состоящая полностью из букв "x" (имеет значение -1, если там только слова не нулевой длины полностью не состоящие из букв "x").

Далее поднимаясь по дереву снизу вверх обновляем эти два значения.

# Запуск программы:
```
 mkdir build
 ```
 ```
 cd build
 ```
 ```
 cmake ..
 ```
 ```
 make
 ```
 ```
 ./formal_prac
 ```