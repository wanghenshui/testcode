
#!/usr/bin/python 
  
import socket 
import struct 
import fcntl 
  
def getip(ethname): 
  
	s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
  
	return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ethname[:15])
    )[20:24])
if __name__=='__main__': 
	print getip('eth0')