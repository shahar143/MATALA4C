from scapy.layers.dns import DNS, IP, UDP, DNSQR

ip = IP(src='1.4.3.7', dst='10.9.0.53')
udp = UDP(sport=76485, dport=53, chksum=0)

Qdsec = DNSQR(qname='shahr.example.com')
dns = DNS(id=0xAAAA, qr=0, qdcount=1, qd=Qdsec)
query = ip / udp / dns

with open("ip_req.bin", 'wb') as f:
    f.write(bytes(query))
