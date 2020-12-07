# from flask import Flask
import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import itertools
import re
from helpers import apology, login_required, lookup, usd
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker

app = Flask(__name__)

app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
	response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
	response.headers["Expires"] = 0
	response.headers["Pragma"] = "no-cache"
	return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Set up database
engine = create_engine(os.getenv("DATABASE_URL"))
db = scoped_session(sessionmaker(bind=engine))

# db = SQL(os.environ["DATABASE_URL"])
@app.route("/")
@login_required
def index():
#Show portfolio of stocks
	user_id = session["user_id"]
	# history = db.execute("SELECT user_id, symbol, shares, price, datetime, SUM (shares) AS total_shares from history WHERE user_id = :user_id GROUP BY symbol ORDER BY datetime", user_id = user_id)
	history = db.execute('SELECT user_id, symbol, shares, price, datetime, SUM (shares) AS total_shares FROM history WHERE user_id = :user_id GROUP BY symbol ORDER BY datetime', {"user_id": user_id}).fetchall()

	history2 = []
	for i in history:
		if i["total_shares"] > 0:
			history2.append(i)

	quote = []
	for i in history2:
		if i["total_shares"] > 0:
			quote.append(lookup(i['symbol']))

	rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id = user_id)
	remaining_cash = usd(rows[0]["cash"])

	portfolio_value = []
	for i in history2:
		for j in quote:
			if i["symbol"].upper() == j["symbol"].upper():
				portfolio_value.append(float(i["total_shares"]) * float(j["price"]))
	portfolio_value = usd(sum(portfolio_value) + rows[0]["cash"])

    # price = lookup(symbol)["price"] * shares
	return render_template("index.html", history = history2, quote = quote, remaining_cash = remaining_cash, portfolio_value = portfolio_value)
    # return render_template("index.html", history = zip(history, quote))


@app.route("/login", methods=["GET", "POST"])
def login():
    #Log user in
    # Forget any user_id
	session.clear()

    # User reached route via POST (as by submitting a form via POST)
	if request.method == "POST":

        # Ensure username was submitted
		if not request.form.get("username"):
			return apology("must provide username", 403)

        # Ensure password was submitted
		elif not request.form.get("password"):
			return apology("must provide password", 403)

        # Query database for username
        # rows = db.execute("SELECT * FROM users WHERE username = :username",
        #                   username=request.form.get("username"))
		rows = db.execute("SELECT * FROM users WHERE username = :username",{"username":request.form.get("username")}).fetchall()

        # Ensure username exists and password is correct
        # if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
        #     return apology("invalid username and/or password", 403)
		if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
			return "Invalid username and/or password."

        # Remember which user has logged in
		session["user_id"] = rows[0]["id"]
		session["username"] = rows[0]["username"]

        # Redirect user to home page
		return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
	else:
		return render_template("login.html")

# @app.route("/")
# def index():
# 	return 'OK!'

if __name__ == "__main__":
	app.run()