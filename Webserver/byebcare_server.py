from SimpleWebSocketServer import SimpleWebSocketServer, WebSocket
import json
from urllib.request import urlopen
from bs4 import BeautifulSoup
import time

class SimpleEcho(WebSocket):

    def handleMessage(self):
        html = urlopen("http://192.168.43.214")
        bsObject = BeautifulSoup(html, "html.parser")
        content = bsObject.html.text.strip().strip('}{')
        print(content)
        requestString = json.dumps(self.data)
        print(requestString)
        responseString = '{"msg_type":"result","device_id" : "IFX001", "command":"ON", "result": "TRUE",'+ content +'}'
        self.sendMessage(responseString)
        print(responseString)

   
    def handleConnected(self):
        print(self.address, 'connected')

    def handleClose(self):
        print(self.address, 'closed')

  
server = SimpleWebSocketServer('192.168.43.213',9999, SimpleEcho)
server.serveforever()