import socket
import json
import struct
from collections import deque
from random import shuffle
from threading import Thread, Lock

GET_GAME_STATE = 777
PREMISION_TO_PLACE_CARD = 700
CARD_BANK_PREMISION = 701

class Player:
    def __init__(self, name, sock):
        self.name = name
        self.cards = []
        self.sock = sock

class Game:
    def __init__(self):
        self.players = []
        self.cards = [f"{color}{number}" for color in ["Red", "Green", "Blue", "Yellow"] for number in range(0, 10)] + \
                     [f"{color}{symbol}" for color in ["Red", "Green", "Blue", "Yellow"] for symbol in ["Skip", "Draw"]] * 2
        self.current_card = None
        self.last_card = None
        self.current_player = 0

    def add_player(self, player):
        self.players.append(player)
        shuffle(self.cards)
        for _ in range(7):
            player.cards.append(self.cards.pop())

class UnoServer:
    def __init__(self, ip='127.0.0.1', port=888):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.bind((ip, port))
        self.game = Game()
        self.lock = Lock()
        
    def start(self):
        self.sock.listen(1)
        print("Server is listening...")
        while len(self.game.players) <2:
            client_sock, _ = self.sock.accept()
            Thread(target=self.handle_client, args=(client_sock,)).start()

    def send_packet(self, sock, code, json_object):
        data = json.dumps(json_object).encode('utf-8')
        length = len(data)
        sock.sendall(struct.pack('!I', code))
        sock.sendall(struct.pack('!I', length))
        sock.sendall(data)

    def receive_packet(self, sock):
        code = int(sock.recv(4),16)
        reversed_bytes = bytes.fromhex(sock.recv(8).decode())[::-1]
        length = struct.unpack('<I', reversed_bytes)[0]
        if length == 0:
            return code, json.loads("{}")
        data = sock.recv(length).decode('utf-8')
        json_object = json.loads(data)
        return code, json_object
    def getWhat(self, card):
        full = str(card)
        for color in ["Red", "Green", "Blue", "Yellow"]:
            full = full.replace(color, "")
        return full
    def getColor(self, card):
        full = str(card)
        for color in ["Red", "Green", "Blue", "Yellow"]:
            if  not full.find(color) == -1:
                return color
    def handle_get_game_state(self, sock):
        other_players = []
        name_temp = self.game.players[self.game.current_player].name
        for plr in (self.game.players):
            if plr.sock.getpeername()[1] == sock.getpeername()[1]:
                if(plr.name ==self.game.players[self.game.current_player].name):
                    name_temp = "You"
                crds = plr.cards
            else:
                other_players.append(plr)

        response_data = {
        "players" : [{"name": player.name, "card_count": len(player.cards)} for player in other_players ],#if not player.sock.getpeername()[1] == player.sock.getpeername()[1]],
        "cards" : [{"color":self.getColor(card), "what": self.getWhat(card)} for card in crds],
        "turn" : (name_temp),
        "placed_card" : {"color": self.getColor(self.game.current_card), "what": self.getWhat(self.game.current_card)} if self.game.current_card else {"color": "none", "what": ""}
        }
       
        self.send_packet(sock, 200, response_data)  

    def handle_card_bank_request(self, sock):
        if self.game.players[self.game.current_player].sock.getpeername()[1] == sock.getpeername()[1]:
            if not self.game.cards:
                self.game.cards = [f"{color}{number}" for color in ["Red", "Green", "Blue", "Yellow"] for number in range(0, 10)] + \
                                [f"{color}{symbol}" for color in ["Red", "Green", "Blue", "Yellow"] for symbol in ["Skip",  "Draw"]] * 2
                shuffle(self.game.cards)
            card = self.game.cards.pop()
            self.game.players[self.game.current_player].cards.append(card)
            if self.getWhat(self.game.current_card) == "Draw":
                    card = self.game.cards.pop()
                    self.game.players[self.game.current_player].cards.append(card)
            response_data = {"status": 100}
            self.send_packet(sock, 100, response_data)
            self.game.last_card = self.game.current_card
            self.game.current_card = None
            self.game.current_player = (self.game.current_player + 1) % len(self.game.players)
        else:
            response_data = {"status": 666}
            self.send_packet(sock, 666, response_data)


    def handle_card_place_request(self, sock, json_object):
        card = json_object.get("picture_tag")
        if self.game.players[self.game.current_player].sock.getpeername()[1] == sock.getpeername()[1] and not self.getWhat(self.game.current_card) == "Draw":
            if self.game.current_card is None and self.game.last_card is None:
                self.game.current_card = card
                self.game.players[self.game.current_player].cards.remove(card)
                if self.getWhat(card) == "Skip":
                    self.game.current_player = (self.game.current_player + 2) % len(self.game.players)
                else:
                    self.game.current_player = (self.game.current_player + 1) % len(self.game.players)
            elif (not self.game.current_card is None) and self.getWhat(self.game.current_card) == self.getWhat(card) or self.getColor(self.game.current_card) == self.getColor(card):
                self.game.current_card = card
                self.game.players[self.game.current_player].cards.remove(card)
                if self.getWhat(card) == "Skip":
                    self.game.current_player = (self.game.current_player + 2) % len(self.game.players)
                else:
                    self.game.current_player = (self.game.current_player + 1) % len(self.game.players)
                response_data = {"status": 100}
                self.send_packet(sock, response_data["status"], response_data)
                if not self.game.cards:
                    self.game.cards = [f"{color}{number}" for color in ["Red", "Green", "Blue", "Yellow"] for number in range(0, 10)] + \
                                [f"{color}{symbol}" for color in ["Red", "Green", "Blue", "Yellow"] for symbol in ["Skip", "Reverse", "DrawTwo"]] * 2
                self.game.cards.append(card)
                shuffle(self.game.cards)
            elif (not self.game.last_card is None) and self.getWhat(self.game.last_card) == self.getWhat(card) or self.getColor(self.game.last_card) == self.getColor(card):
                self.game.last_card = card
                self.game.players[self.game.current_player].cards.remove(card)
                if self.getWhat(card) == "Skip":
                    self.game.current_player = (self.game.current_player + 2) % len(self.game.players)
                else:
                    self.game.current_player = (self.game.current_player + 1) % len(self.game.players)
                response_data = {"status": 100}
                self.send_packet(sock, response_data["status"], response_data)
                if not self.game.cards:
                    self.game.cards = [f"{color}{number}" for color in ["Red", "Green", "Blue", "Yellow"] for number in range(0, 10)] + \
                                [f"{color}{symbol}" for color in ["Red", "Green", "Blue", "Yellow"] for symbol in ["Skip", "Reverse", "DrawTwo"]] * 2
                self.game.cards.append(card)
                shuffle(self.game.cards)
        response_data = {"status": 101}
        self.send_packet(sock, response_data["status"], response_data)
        

    def handle_client(self, sock):

        self.name = f"Player{len(self.game.players)}"
        player = Player(self.name, sock)
        with self.lock:
            self.game.add_player(player)
        while len(self.game.players) <2:
            print("",end="")
        while True:
            code, json_object = self.receive_packet(sock)
            if code == GET_GAME_STATE:
                self.handle_get_game_state(sock)
            elif code == PREMISION_TO_PLACE_CARD:
                self.handle_card_place_request(sock, json_object)
            elif code == CARD_BANK_PREMISION:
                self.handle_card_bank_request(sock)

if __name__ == "__main__":
    UnoServer().start()
