# Лабораторная работа 2

**Название:** "Разработка драйверов блочных устройств"

**Вариант 9**

**Цель работы:** Получить знания и навыки разработки драйверов блочных устройств для операционной системы Linux.

## Описание функциональности драйвера

Три первичных раздела с размерами 8Мбайт, 27Мбайт и
15Мбайт. Каждый записываемый байт должен возводиться в куб.

## Инструкция по сборке

- `make` - собрать модуль
- `make load` - загрузить модуль
- `make uload` - выгрузить модуль
- `make lcheck` - проверить загружен ли модуль
- `make clean` - очистить сборочную директорию

## Инструкция пользователя

1. `make` - сборка модуля
2. `make load` - загрузка модуля
3. Драйвер готов к работе

## Примеры использования
Информация о дисках:
```
Disk /dev/mydisk: 30 MiB, 31457280 bytes, 61440 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x36e5756d

Device       Boot Start   End Sectors Size Id Type
/dev/mydisk1          1 16384   16384   8M 83 Linux
/dev/mydisk2      20480 75775   55296  27M  5 Extended
/dev/mydisk3          1 30720   30720  15M 83 Linux
```
### Запись на диск
```
osboxes@osboxes:~/lab2/itmo_io/lab2$ sudo hexdump -C /dev/mydisk
00000000  40 9d eb 40 00 21 88 3b  61 e8 00 00 00 00 00 00  |@..@.!.;a.......|
```
