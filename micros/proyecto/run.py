from flask import Flask
from flask import request
app = Flask(__name__)

@app.route('/get',methods=['GET'])
def get():
    with open('colors.txt', 'r') as f:
        return f.read()

@app.route('/post',methods=['POST'])
def post():
    params = request.get_json(force=True)
    with open('colors.txt', 'w') as f:
        f.write(params["color"])
    return params["color"]