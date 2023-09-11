# Velkommen på Skibsværftet

### Her skal du åbne en guldkiste

 - Desværre er den låst med en kode der ikke findes nogen steder, derfor bliver vi nød til at bruge noget der hedder ***brute-force***. Hvilket egentlig bare betyder at prøve alle muligheder af.
 - Heldigvis ved vi lidt om kodeordet, kodeordets længde er mellem 3 og 4 bogstaver eller tal.

## Brute-force
### Først skal vi have oprettet en fil med alle mulige kombinationer, vi behøver heldigvis ikke skrive dem alle selv.
- Til dette skal vi bruge en kommando der hedder ```crunch```.
- ```crunch```: skal bruge nogle informationer, der skrives bagefter: 
  1. skriver man minimumslængden på koden
  2. skriver man maksimumslængden på koden
  3. til sidst skriver man ```-o [filnavn]``` som fortæller hvor alle kombinationerne skal gemmes.

***Eksempel***
- Her er et eksempel, hvor der oprettes en fil ***minOrdbog***, der indeholder alle kombinationer med 2-3 bogstaver.
<br>
```crunch 2 3 -o minOrdbog```
<br>
- Nu er det din opgave at oprette en fil, udfra beskrivelsen i toppen af denne fil.
- Prøv at læse den fil du har oprettet, så kan du se hvor mange muligheder der skal prøves af, for at gætte koden..!

<br>

### For at åbne guldkisten skal vi bruge en lidt svære kommando: 
- **Denne kommando hedder ```fcrackzip```.**
- Nedenfor kan ses et eksempel, hvor der bruges minOrdbog, fra eksempelt ovenfor, til at åbne en fil der hedder ***låst.zip***:

```fcrackzip -u -D -p minOrdbog -v låst.zip```

- Efter man har kørt kommandoen til ```fcrackzip```, vil der stå hvis den har fundet passwordet. eks:


```PASSWORD FOUND!!!!: pw == afb```

- Passwordet, der skal bruges til at ```unzip låst.zip``` er de sidste tegn efter de to *==* tegn. i eksempelt er koden ```afb```.
- Åbn guldkisten og se hvad der gemmer sig i den. 