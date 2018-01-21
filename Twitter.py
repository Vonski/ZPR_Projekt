def tweet(msg):
	import tweepy
	import time
	import sys
	import threading

	consumer_key = 'dIJ0TzumIEpvSPHkmBH4EZcZK'
	consumer_secret = '9xZ7wlxAE58gReJKDQNPECBdtvZ4pLvA75aFJk8BJumFHikLUu'
	access_token = '915826314644529153-y5LqbX3R07wGkfOWEE0l9jSH1YTTqxX'
	access_token_secret = 'eJYSoA3nyzKQXy2YOC1C67PK8hat180eFu9G7joEehPiU'

	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
	auth.set_access_token(access_token, access_token_secret)
	api = tweepy.API(auth)
	api.update_status(msg)
