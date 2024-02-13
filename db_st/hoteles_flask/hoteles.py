from flask import Flask, render_template

hoteles = Flask(__name__)

@hoteles.route("/") #For default route
def main():
    return render_template("hoteles.html")

if(__name__ == "__main__"):
    hoteles.run()