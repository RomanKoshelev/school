import anthropic
from config import MODEL, SYSTEM_PROMPT


class LawyerBot:
    """Чат-бот юрист РФ на основе Claude API."""

    def __init__(self, api_key: str):
        self.client = anthropic.Anthropic(api_key=api_key)
        self.history: list[dict] = []

    def ask(self, question: str) -> str:
        """Отправить вопрос юристу и получить ответ."""
        self.history.append({"role": "user", "content": question})

        response = self.client.messages.create(
            model=MODEL,
            max_tokens=4096,
            system=SYSTEM_PROMPT,
            messages=self.history,
        )

        answer = response.content[0].text
        self.history.append({"role": "assistant", "content": answer})
        return answer

    def clear_history(self):
        """Очистить историю диалога."""
        self.history.clear()
