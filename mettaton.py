import requests
import discord
from random import randint 
from discord.ext import tasks

# The neko channel
CHANNEL: int = 1326286426052231229
URL = 'https://nekos.best/api/v2/neko'
# TYPES = [ 
#     'baka', 'bite', 'blush', 'bored', 'cry', 'cuddle', 
#     'dance', 'facepalm', 'feed', 'handhold', 'handshake', 
#     'happy', 'highfive', 'hug', 'kick','kiss', 'laugh', 'lurk', 
#     'nod', 'nom', 'nope', 'pat', 'peck', 'poke', 'pout', 'punch', 
#     'shoot', 'shrug', 'slap', 'sleep', 'smile', 'smug', 'stare', 
#     'think', 'thumbsup', 'tickle', 'wave', 'wink', 'yawn', 'yeet' 
# ]

class Mettaton(discord.Client):
    def __init__(self, intents: discord.Intents):
        super().__init__(intents=intents)

    async def on_ready(self):
        print("Ready !")
        await self.send_neko.start()
        # for member in self.get_all_members():
        #     for id in self.victimsID:
        #         if member.id == id:
        #             self.victims.append(member)
        # await self.annoy.start()        

    @tasks.loop(hours=24)
    async def send_neko(self):
        # type = TYPES[randint(0, len(TYPES))]
        req = requests.get(URL)# + type)
        print(req)
        if (req.status_code == 200):
            data = req.json()
            print(data)
            await self.get_channel(CHANNEL).send(content=data['results'][0]['url'])