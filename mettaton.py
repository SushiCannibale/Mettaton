import os.environ
import datetime
import requests

from discord import Intents
from discord.ext.commands import Bot
from discord.ext import tasks

from random import randint 

midnight_uwu = datetime.time(hour=23, minute=0, second=0)

# The neko channel
URL = 'https://api.thecatapi.com/v1/images/search'

class Mettaton:
    def __init__(self):
        intents = Intents.default()
        intents.message_content = True
        
        self.bot = Bot(command_prefix="$", intents=intents)

        self.neko_channels : set[int] = [ ]
        self.cmds_channels : set[int] = [ ]
        self.next_neko = 0

        self.register_commands()

        self.bot.event(self.on_ready)

    def run(self, token: str):
        self.bot.run(token)

    def register(self, chan : int):
        self.channels.add(chan)

    def unregister(self, chan : int):
        self.channels.remove(chan)

    def request_nekos(self, limit : int, url : str):
        buf = environ.get("NEKOS")
        req = requests.get(URL + "?limit=10")# + type)
        print(req)
        if (req.status_code == 200):
            data = req.json()
            print(data)
            
    async def on_ready(self):
        print(f"{self.bot.user} ready")

    def register_commands(self):
        @self.bot.command(name="ping", description="pings me >:3")
        async def ping(ctx):
            await ctx.send("pong")

        @self.bot.command(name="listens")
        async def listens(ctx):
            await ctx.send(ctx.message)

        @self.bot.command(name="neko", description="Fetch a neko from out of bound")
        async def neko(ctx):
            req = requests.get(URL + "?limit=10")# + type)
            print(req)
            if (req.status_code == 200):
                data = req.json()
                print(data)
            #     for channel in self.neko_channels:
            #         await self.get_channel(channel).send(content=data[0]['url'])
