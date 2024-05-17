# YADROTestTask
Тестовое задание для вакансии C++ стажёра в компанию YADRO. Для тестирования использовалась библиотека GoogleTest.

# Описание

Прототип системы, которая следит за работой компьютерного клуба, обрабатывает события и подсчитывает выручку за день и время занятости каждого стола.

# Сборка проекта

Для сборки проекта введите команду в терминал:
```bash
cmake . && cmake --build .
```

# Запуск

Для запуска необходимо собрать проект. После этого достаточно ввести команду:
```bash
./test_task имя_файла.txt
```

# Тестирование

После сборки проекта необходимо выполнить следующую команду:
```bash
ctest
```