import socket
import time
def test_server(ip, port):
    
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to the server
    client_socket.connect((ip, port))

    # Send a test message to the server
    test_message = "HELLO"
    for i in range(1,10):
        client_socket.send(test_message.encode())

        # Receive the response from the server
        response = client_socket.recv(1024).decode()

        # Check if the response is as expected
        if response == test_message:
            print("The server is working as expected.")
        else:
            print("The server is not working as expected. Received:", response)
        time.sleep(1)
    # Close the socket
    client_socket.close()

if __name__ == "__main__":
    server_ip = "127.0.0.1" 
    server_port = 888  
    test_server(server_ip, server_port)
