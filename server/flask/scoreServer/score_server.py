from flask import Flask, render_template, make_response, request
import mysql.connector
import re
import json

app = Flask(__name__)


def edit_db(query, pattern):
    settings = read_db_settings()

    host_ = settings[0]["db"][0]["host"]
    data_base = settings[0]["db"][0]["database"]
    user_ = settings[0]["db"][0]["user"]
    password_ = settings[0]["db"][0]["pw"]
    connection = mysql.connector.connect(user=user_, password=password_, host=host_, database=data_base)
    cursor = connection.cursor(dictionary=True)
    cursor.execute(query)
    if pattern == "get":
        result = cursor.fetchall()
    elif pattern == "set":
        connection.commit()
    cursor.close()
    connection.close()
    if pattern == "get":
        return result


def read_db_settings():
    with open("./etc/settings.json", "r") as f:
        settings = json.load(f)
    return settings


def validate(score):
    result = re.fullmatch("[0-9]+", str(score))
    if result is None:
        return False
    return True


@app.route('/')
def index():
    return "index"


@app.route('/api/score')
def set_score():
    usrname = request.args.get('usrname', type=str)
    score = request.args.get('score', type=int)
    # print(usrname + score)
    if validate(score):
        edit_db("INSERT into score(score, usrname) values('" + str(score) + "' , '" + usrname + "')", "set")
    else:
        print("Validate Error")
    return str()


@app.route('/api/score/list')
def get_score():
    # 降順ソートして上位10個取得
    result = edit_db("SELECT usrname, score FROM score ORDER BY score DESC LIMIT 10", "get")
    print(result[0]['score'])
    for val in result:
        print(val['usrname'] + ": " + str(val['score']))

    return json.dumps(result)


if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0")
