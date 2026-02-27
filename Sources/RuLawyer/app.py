#!/usr/bin/env python3
"""
РуЮрист — веб-сервис ИИ-юриста РФ.

Запуск:
    python app.py
"""

import os
import uuid

from flask import Flask, jsonify, render_template, request, session

from lawyer import LawyerBot

app = Flask(__name__)
app.secret_key = uuid.uuid4().hex

# Хранилище сессий: session_id -> LawyerBot
bots: dict[str, LawyerBot] = {}


def get_bot(api_key: str) -> LawyerBot:
    sid = session.get("sid")
    if not sid or sid not in bots:
        sid = uuid.uuid4().hex
        session["sid"] = sid
        bots[sid] = LawyerBot(api_key)
    return bots[sid]


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/api/ask", methods=["POST"])
def ask():
    data = request.get_json(silent=True) or {}
    question = (data.get("question") or "").strip()
    api_key = (data.get("api_key") or "").strip()

    if not api_key:
        return jsonify({"error": "Введите API-ключ Anthropic"}), 400
    if not question:
        return jsonify({"error": "Пустой вопрос"}), 400

    bot = get_bot(api_key)
    try:
        answer = bot.ask(question)
        return jsonify({"answer": answer})
    except Exception as e:
        return jsonify({"error": f"Ошибка API: {e}"}), 500


@app.route("/api/clear", methods=["POST"])
def clear():
    sid = session.get("sid")
    if sid and sid in bots:
        del bots[sid]
    session.pop("sid", None)
    return jsonify({"ok": True})


if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    app.run(host="0.0.0.0", port=port, debug=False)
