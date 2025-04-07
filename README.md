# Telegram Bot на C++ (учебный проект)

Проект создан для изучения современных возможностей C++ с акцентом на ООП, паттерны проектирования (MVC, SOLID), работу с сетью (HTTP через libcurl), JSON (сам бот не являлся целью изучения)

Телеграм-бот предоставляет расписание занятий СПбГУ.

## 🛠 Сборка и запуск

```bash
# 1. Установка зависимостей (Ubuntu/Debian)
sudo apt update && sudo apt install -y \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    libssl-dev \
    libboost-system-dev

# 2. Клонирование репозитория
git clone https://github.com/niklvdanya/tgbot.git
cd tgbot

# 3. Настройка конфигурации
cp .env.example .env
nano .env  # вставьте ваш токен бота

# 4. Сборка проекта
mkdir build && cd build
cmake .. && make

# 5. Запуск
./bin/telegram_bot