# Лабораторная работа 2

**Название:** "Разработка драйверов блочных устройств"

**Вариант 9**

**Цель работы:** Получить знания и навыки разработки драйверов блочных устройств для операционной системы Linux.

## Описание функциональности драйвера

...

## Инструкция по сборке

...

## Инструкция пользователя

...

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
...
