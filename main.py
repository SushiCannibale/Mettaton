import discord
from mettaton import Mettaton

token: str
with open('secret', 'r') as file:
    token = file.readline()

victims: list[int] = []
with open('victims', 'r') as file:
    victims = [ int(line) for line in file.readlines() ]

intents = discord.Intents.default()
intents.members = True

client = Mettaton(intents, victims)
client.run(token=token)