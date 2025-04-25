# import discord
# from mettaton import Mettaton
#
# token: str
# with open('secret', 'r') as file:
#     token = file.readline()
#
# intents = discord.Intents.default()
# intents.message_content = True
#
# client = Mettaton()
# client.run(token=token)
import nekolib

if __name__ == "__main__":
    nekolib.load_nekos('test.req')
