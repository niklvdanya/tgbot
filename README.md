# Telegram Bot на C++ (учебный проект)

Проект создан для изучения современных возможностей C++ с акцентом на ООП, паттерны проектирования (MVC, SOLID), работу с сетью (HTTP через libcurl), JSON, Docker, GTest, внешние API. (сам бот не являлся целью изучения)

Телеграм-бот предоставляет расписание занятий СПбГУ.

## 🛠 Сборка и запуск

```bash
# 1. Клонирование репозитория
git clone https://github.com/niklvdanya/tgbot.git
cd tgbot

# 2. Настройка конфигурации
cp .env.example .env
nano .env 

# 3. Сборка и запуск с помощью Docker Compose
docker-compose up --build

# 4. (Опционально) Запуск юнит-тестов
docker-compose run telegram-bot /app/build/bin/run_tests