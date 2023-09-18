# Havnesystemet

Du skal finde ud af hvilken af havnens servere der kører. Du kan se der hænger et opslag med 5 IP-adresser på opslagstavlen:

 - 192.168.1.223
 - 192.168.1.133
 - 192.168.1.2
 - 192.168.1.44
 - 192.168.1.34
 
Ligesom ubåde kan bruge sonar, så kan du sende et ping til en computer på netværket for at se om den svarer. Brug kommandoen `ping` efterfulgt at IP-adressen.

F.eks.: `ping 123.123.123.123`. En IP-adresse består altid af 4 tale adskilt af punktum.

Du afbryder ping med CTRL-C.

Når du har fundet IP-adressen skal du gemmen den i variablen `IP` med kommandoen `export IP=` efterfulgt af IP-adressen uden mellemrum. Kom videre med hvadnu.
