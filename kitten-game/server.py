from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

# Server-side leaderboard (in-memory)
scores = {}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/score', methods=['POST'])
def save_score():
    data = request.get_json()
    name = data.get('name', 'Аноним')[:30]
    count = int(data.get('count', 0))
    scores[name] = max(scores.get(name, 0), count)
    return jsonify({'ok': True})

@app.route('/api/leaderboard')
def leaderboard():
    top = sorted(scores.items(), key=lambda x: x[1], reverse=True)[:10]
    return jsonify([{'name': n, 'count': c} for n, c in top])

if __name__ == '__main__':
    print("Сервер запущен: http://localhost:5000")
    app.run(host='0.0.0.0', port=5000, debug=False)
