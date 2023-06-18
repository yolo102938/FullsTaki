import socket
import json
import struct
import keyboard
GET_ROOMS_REQUEST = 777

def receive_packet(sock):
    5
    code =  int(sock.recv(4),16) #int.from_bytes(bytes.fromhex(sock.recv(4).decode()), byteorder='little')
    print("code:", code, end=" ")
    
    reversed_bytes = bytes.fromhex(sock.recv(8).decode())[::-1]
    length = struct.unpack('<I', reversed_bytes)[0]
    #length =  int(sock.recv(4)) #struct.unpack('!I', sock.recv(4))[0]  # Get the message length
    print("length:", length, end=" ")
    if length == 0:
        print("", end="\n")
        return code, json.loads("{}")
    data = sock.recv(length).decode('utf-8')  # Receive and decode the data
    json_object = json.loads(data)
    print("json:", data, end="\n")
    return code, json_object

def send_packet(sock, code, json_object):
    data = json.dumps(json_object).encode('utf-8')  # Convert the JSON object to bytes
    length = len(data)
    sock.sendall(struct.pack('!I', code))  # Send the message code
    sock.sendall(struct.pack('!I', length))  # Send the message length
    sock.sendall(data)  # Send the data

def handle_get_rooms_request(sock, json_object):
    response_code = 200
    response_data = {
        "players": [
            {"name": "Thomas", "card_count": int(input("Thomas card count?"))},
            {"name": "Timmy", "card_count": int(input("Timmy card count?"))},
        ],
        "cards": [
            {"color": "Red", "what": "2"},
            {"color": "Blue", "what": "Skip"},
            {"color": "Green", "what": "8"}
        ],
        "turn": input("Turn? (Timmy, Thomas, You)"),
        "placed_card": {"color": "Red", "what": "5"}
    }
    send_packet(sock, response_code, response_data)

    print("sending the same packet, press d to send diffrent")
    while  not keyboard.is_pressed('d'):
        code, json_object = receive_packet(sock)
        if code == GET_ROOMS_REQUEST:
            send_packet(sock, response_code, response_data)
    print("Please enter new things")


def handle_login_request(sock, json_object):
    # Implement your login logic here
    # Process the username and password from json_object
    # Send the appropriate response code and JSON data back to the client
    response_code = 200  # Replace with your own response code
    response_data = {"message": "Login successful"}  # Replace with your own response data
    send_packet(sock, response_code, response_data)

def main():
    server_ip = "127.0.0.1"
    server_port = 888

    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.bind((server_ip, server_port))
    server_sock.listen(1)
    print("Server is listening on {}:{}".format(server_ip, server_port))

    while True:
        client_sock, client_addr = server_sock.accept()
        print("Accepted connection from:", client_addr)
        try:
            while True:
                code, json_object = receive_packet(client_sock)
                if code == GET_ROOMS_REQUEST:
                    handle_get_rooms_request(client_sock, json_object)
                elif code == 101:  # LOGIN_REQUEST code
                    handle_login_request(client_sock, json_object)
                    client_sock.close()
        except Exception as e:
            print(e)

if __name__ == "__main__":
    main()
