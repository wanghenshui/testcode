#!/usr/bin/python3
from flask import Flask, render_template
app = Flask(__name__)

#from flask import request



@app.route('/')#user/<name>')
def index():
	return render_template('index.html')
    #user_agent = request.headers.get('User-Agent')
    #return '<h1>browser is %s </h1>' % user_agent
    #from flask import redirect
    #redirect('url')

@app.route('/user/<name>')
def user(name):
    return render_template('user.html',name=name)
    #return '<h1>hello %s !</h1>' % name

@app.errorhandler(404)
def page_not_found(e):
	return render_template('404.html')

if __name__ == '__main__':
    app.run(debug=True)
