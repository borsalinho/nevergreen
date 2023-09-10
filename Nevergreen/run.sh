#!/bin/bash

# Проверяем, установлены ли необходимые зависимости
if ! command -v streamlit &>/dev/null; then
    echo "Ошибка: Streamlit не установлен. Установите его с помощью 'pip install streamlit'."
    exit 1
fi

if ! command -v folium &>/dev/null; then
    echo "Ошибка: Folium не установлен. Установите его с помощью 'pip install folium'."
    exit 1
fi

if ! command -v plotly &>/dev/null; then
    echo "Ошибка: Plotly не установлен. Установите его с помощью 'pip install plotly'."
    exit 1
fi

if ! command -v pandas &>/dev/null; then
    echo "Ошибка: Pandas не установлен. Установите его с помощью 'pip install pandas'."
    exit 1
fi

# Запускаем приложение Streamlit
streamlit run app.py
