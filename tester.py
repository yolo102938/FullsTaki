import socket
import time
import json
import struct

LOGIN_REQUEST = 101
SIGNUP_REQUEST = 100
def send_packet(sock,code,json_object):
    data = json.dumps(json_object)    #convert to string
    data = data.encode('utf-8') # Convert to bytes
    length = len(data)
    sock.sendall(struct.pack('!I', code)) #send to socket msg code encoded to binary using unsigned int format
    sock.sendall(struct.pack('!I', length)) #send to socket the length encoded to binary with unsigned int format
    sock.sendall(data) #send to socket the data
    response_code = struct.unpack('!I', sock.recv(4))[0] # Get the response code
    print(response_code)
    response_length = struct.unpack('!I', sock.recv(4))[0] # Get the response length
    print(response_length)
    test = sock.recv(response_length).decode('utf-8')
    response = json.loads(test)#receive and decode data
    print(response)
    return response_code, response

def test_server_login(client_socket):
    #json object
    login_request = {
        "username": "test",
        "password": "admin"
    }
    response_code, response = send_packet(client_socket, LOGIN_REQUEST, login_request)
    print("Server Response Code to test login: " + str(response_code))
    print("Server Response to test login: " + str(response))

def test_server_signup(client_socket):
    #json object
    login_request = {
        "username": "test",
        "password": "admin",
        "email":"jonathan@anaki"
    }
    response_code, response = send_packet(client_socket, SIGNUP_REQUEST, login_request)
    print("Server Response Code to test login: " + str(response_code))
    print("Server Response to test login: " + str(response))

def test_server_basic(client_socket):
    # Send a test message to the server
    test_message = "HELLO"
    client_socket.send(test_message.encode())

    # Receive the response from the server
    response = client_socket.recv(1024).decode()

    # Check if the response is as expected
    if response == test_message:
        print("The server is working as expected.")
    else:
        print("The server is not working as expected. Received:", response)


if __name__ == "__main__":
    #server info
    server_ip = "127.0.0.1" 
    server_port = 888  
    func_dict = {"login": test_server_login, "basic": test_server_basic,"signup":test_server_signup}
    inp = ""
    while(inp!="EXIT"):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((server_ip, server_port))
        inp = input("how many times do you want the test to happen?(1 sec delay each try. EXIT to close program.)")
        if(inp=="EXIT"):
            break
        func_name = input("choose what to check(login,basic,signup)")
        for i in range(int(inp)):
            func_dict[func_name](sock)
            time.sleep(1)
        sock.close()
