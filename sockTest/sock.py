import socket
 
if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('118.244.239.199', 9800))
    sock.send('''GET / HTTP/1.1
Upgrade: websocket
Connection: Upgrade
Host: 118.244.239.199:9800
Origin: null
Pragma: no-cache
Cache-Control: no-cache
Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==
Sec-WebSocket-Version: 13
Sec-WebSocket-Extensions: x-webkit-deflate-frame''')
    bf = sock.recv(200)
    print "size: " + str(len(bf))
    print bf