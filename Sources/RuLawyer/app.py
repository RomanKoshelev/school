#!/usr/bin/env python3
"""
РуЮрист — веб-сервис ИИ-юриста РФ.

Запуск:
    export ANTHROPIC_API_KEY="ваш-ключ"
    python app.py
"""

import sys
import uuid

from flask import Flask, jsonify, render_template, request, session

from config import ANTHROPIC_API_KEY
from lawyer import LawyerBot

app = Flask(__name__)
app.secret_key = uuid.uuid4().hex

# Хранилище сессий: session_id -> LawyerBot
bots: dict[str, LawyerBot] = {}


def get_bot() -> LawyerBot:
    sid = session.get("sid")
    if not sid or sid not in bots:
        sid = uuid.uuid4().hex
        session["sid"] = sid
        bots[sid] = LawyerBot()
    return bots[sid]


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/api/ask", methods=["POST"])
def ask():
    data = request.get_json(silent=True) or {}
    question = (data.get("question") or "").strip()
    if not question:
        return jsonify({"error": "Пустой вопрос"}), 400

    bot = get_bot()
    try:
        answer = bot.ask(question)
        return jsonify({"answer": answer})
    except Exception as e:
        return jsonify({"error": f"Ошибка API: {e}"}), 500


@app.route("/api/clear", methods=["POST"])
def clear():
    bot = get_bot()
    bot.clear_history()
    return jsonify({"ok": True})


if __name__ == "__main__":
    if not ANTHROPIC_API_KEY:
        print("Ошибка: не задан ANTHROPIC_API_KEY.")
        print('  export ANTHROPIC_API_KEY="sk-ant-..."')
        sys.exit(1)

    app.run(host="0.0.0.0", port=5000, debug=False)
