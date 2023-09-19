# Brute force angreb på WiFi

For at knække koden på et WiFi-netværk skal du have tjek på:
 - WiFi-netværkets navn også kaldet `ESSID`. Husk: det er strafbart at få adgang til et WiFi som man ikke har en aftale om at få adgang til
 - En ide om hvad koden på netværket er - f.eks. en liste med ord
 - At have højeste privilegier på computeren, det betyder at du kan køre kommandoer som administrator

## wifite: et redskab der automatiserer WiFi-cracking

Kommando: `wifite -e [ESSID] --dict [filnavn-til-ordbog]`

I Linux terminale kan du køre kommandoer som om du var administrator - eller superuser. Kombineret med det engelske `do` (at gøre) bliver kommandoen for at gøre ting som superuser til: `sudo`

Når du skal køre wifite som sudo skriver du derfor:

`sudo wifite -e [ESSID] --dict [filnavn-til-ordbog]`

