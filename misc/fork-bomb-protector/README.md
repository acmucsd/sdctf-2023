# Fork bomb protector

We built a playground for people to try out Linux. We are tired of customer complaints about malicious fork bombs rummaging the server, hogging system resources, and bringing everything down to a crawl, so we built our own proprietary fork-bomb protector.
As an "unintended" consequence of that, people cannot run commands normally. Our genius head of the engineering team suggests this to be a security "feature", not a bug, since this essentially turns our product into a restricted shell. Bye bye, RCEs!

Connect via:

```bash
socat FILE:`tty`,raw,echo=0 TCP:nofork.sdc.tf:1337
```

Attachments:
[nofork.py](./challenge/nofork.py)
