import discord
from discord.ext import tasks

DELAY: float = 10.0
CHANNEL: int = 1177614879289528396

class Mettaton(discord.Client):
    def __init__(self, intents: discord.Intents, victims: list[int]):
        super().__init__(intents=intents)
        self.victimsID = victims
        self.victims: list[discord.Member] = []

    async def on_ready(self):
        for member in self.get_all_members():
            for id in self.victimsID:
                if member.id == id:
                    self.victims.append(member)
        await self.annoy.start()
        

    @tasks.loop(seconds=DELAY)
    async def annoy(self):
        print("Sent!")
        for user in self.victims:
            await self.get_channel(CHANNEL).send(content=user.mention + " =UwU=")