# Steps to make the pcap

## Client side

Use a slightly modified version of [Kevin's zgrab2 for IKE](https://github.com/kevin-he-01/zgrab2)

- Use DH exponent 4
- The identity payload of the client carries ASN.1 distinguished name: `CN=<flag>`

```bash
zgrab2 ike --ike-identity=asn1dn:CN -p $PORT <<< $SERVER_IP
```

## Server side

Strongswan version `5.9.5-2ubuntu2.1`

```text
$ sudo tcpdump -i any port 500 -w yikes.pcap -v
tcpdump: data link type LINUX_SLL2
tcpdump: listening on any, link-type LINUX_SLL2 (Linux cooked v2), snapshot length 262144 bytes
5 packets captured
9 packets received by filter
0 packets dropped by kernel
```
