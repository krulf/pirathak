# Åben simons kiste

### Gå på rov efter ord og tal på en hjemmeside
- Til dette skal vi bruge en kommando der hedder ```cewl```.
- ```cewl```: skal bruge nogle informationer, der skrives bagefter: 
  1. hvis man skriver ```-d [tal]```, kan man angive hvor dybt der skal søges på hjemmesiden, et lavt tal er hurtigt men man får ikke så mange ord. Her skal man prøve sig frem.
     - måske er det nok med ```-d 1```, så bliver man hurtigt færdig og ellers må man prøve med et større tal.
  2. til sidst skriver man ```-w [filnavn]``` som fortæller hvor alle ord og tal skal gemmes.

***Eksempel***
- Her er et eksempel, hvor der oprettes en fil ***minOrdbog***, der søger hurtigt.
<br>
```cewl https://simonmilfred.dk/ -d 1 -w minOrdbog```
<br>
- Nu er det din opgave at oprette en fil udfra hjemmesiden.
- Prøv at læse den fil du har oprettet, så kan du se hvor mange muligheder der skal prøves af, for at gætte koden..!

### For at åbne simons kiste skal vi bruge en lidt sværere kommando: 
- **Denne kommando hedder ```fcrackzip```.**
- Nedenfor kan ses et eksempel, hvor der bruges minOrdbog, fra eksempelt ovenfor, til at åbne en fil der hedder ***låst.zip***:

```fcrackzip -u -D -p minOrdbog -v låst.zip```

- Efter man har kørt kommandoen til ```fcrackzip```, vil der stå hvis den har fundet passwordet. eks:


```PASSWORD FOUND!!!!: pw == afb```

- Passwordet, der skal bruges til at ```unzip låst.zip``` er de sidste tegn efter de to *==* tegn. i eksempelt er koden ```afb```.
- Åbn guldkisten og se hvad der gemmer sig i den. 