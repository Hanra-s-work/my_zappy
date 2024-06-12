##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# tcp_udp_combined.py
##

import socket
import threading


def start_tcp_server(host='127.0.0.1', port=65432):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        print(f"TCP server listening on {host}:{port}")

        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received {data.decode()}")
                conn.sendall(data)
                if data.decode() == "exit\n":
                    print("TCP Stopping")
                    break


def start_udp_server(host='127.0.0.1', port=65433):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((host, port))
        print(f"UDP server listening on {host}:{port}")

        while True:
            data, addr = s.recvfrom(1024)
            print(f"Received {data.decode()} from {addr}")
            s.sendto(data, addr)
            if data.decode() == 'exit\n':
                print("UDP stopping")
                break


if __name__ == "__main__":
    tcp_thread = threading.Thread(target=start_tcp_server)
    udp_thread = threading.Thread(target=start_udp_server)

    tcp_thread.start()
    udp_thread.start()

    tcp_thread.join()
    udp_thread.join()
