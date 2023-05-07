import socket
import time
import json
import struct

LOGIN_REQUEST = 101
SIGNUP_REQUEST =100

def send_packet(sock,code,json_object):
    data = json.dumps(json_object)    #convert to string
    length = len(data)
    sock.sendall(struct.pack('!B', code)) #send to socket msg code encoded to binary using unsigned char format
    sock.sendall(struct.pack('!I', length)) #send to socket the length encoded to binary with unsigned int format
    sock.sendall(data.encode('utf-8')) #send to socket the length encoded in normal binary
    response = json.loads(sock.recv(1024).decode('utf-8'))#recieve and decode data
    return(response)

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
        

def test_server_login(client_socket):
    #json object
    login_request = {
        "username": "test",
        "password": "admin"
    }
    print("Server Response to test login: "+ send_packet(client_socket,LOGIN_REQUEST,login_request))

if __name__ == "__main__":
    #server info
    server_ip = "127.0.0.1" 
    server_port = 888  
    inp = ""
    while(inp!="EXIT"):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((server_ip, server_port))
        inp = input("how many times do you want the test to happen?(1 sec delay each try. EXIT to close program.)")
        if(inp=="EXIT"):
            pass
        func = input("choose what to check(login,basic,more in future)")
        for i in range(1,int(inp)):
            exec("test_server_"+func+"(sock)")
            time.sleep(1)
        sock.close()
