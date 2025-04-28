# Processor

Реализация эмулятора процессора на чистом C (стандарт C11).

## Особенности
- Полноценная эмуляция процессора
- Поддержка оперативной памяти
- Система регистров
- Терминальный интерфейс

## Использование
```c
#include "processor.h"

Processor proc = {};
ProcessorCtor(&proc);

ExecuteProgram(&proc, "code.bin");  // Выполнение программы
ProcessorDump(&proc);               // Состояние процессора

ProcessorDtor(&proc);               // Очистка

## Сборка
gcc -std=c11 processor.c main.c -o processor
