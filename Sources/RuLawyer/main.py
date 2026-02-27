#!/usr/bin/env python3
"""
РуЮрист — ИИ-помощник по законодательству Российской Федерации.

Консольное приложение для получения юридических консультаций
на основе Claude API от Anthropic.

Использование:
    export ANTHROPIC_API_KEY="ваш-ключ"
    python main.py
"""

import sys
from config import ANTHROPIC_API_KEY
from lawyer import LawyerBot

BANNER = """
╔══════════════════════════════════════════════════════╗
║              РуЮрист — ИИ Юрист РФ                  ║
║                                                      ║
║  Задавайте вопросы по законодательству РФ.           ║
║                                                      ║
║  Команды:                                            ║
║    /новый  — начать новый диалог                     ║
║    /выход  — выйти из программы                      ║
╚══════════════════════════════════════════════════════╝
"""

DISCLAIMER = (
    "⚠  Ответы носят информационный характер и не являются "
    "официальной юридической консультацией.\n"
)


def main():
    if not ANTHROPIC_API_KEY:
        print("Ошибка: не задан ANTHROPIC_API_KEY.")
        print("Установите переменную окружения:")
        print('  export ANTHROPIC_API_KEY="sk-ant-..."')
        sys.exit(1)

    print(BANNER)
    print(DISCLAIMER)

    bot = LawyerBot()

    while True:
        try:
            question = input("Вы: ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\nДо свидания!")
            break

        if not question:
            continue

        if question.lower() in ("/выход", "/exit", "/quit"):
            print("До свидания!")
            break

        if question.lower() in ("/новый", "/new", "/clear"):
            bot.clear_history()
            print("— Диалог очищен. Задавайте новый вопрос.\n")
            continue

        try:
            print("\nЮрист: ", end="", flush=True)
            answer = bot.ask(question)
            print(answer)
            print()
        except Exception as e:
            print(f"\nОшибка при обращении к API: {e}\n")


if __name__ == "__main__":
    main()
