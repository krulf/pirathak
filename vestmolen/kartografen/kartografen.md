# Opgave: Skattejagt i Billedets Hemmeligheder

Arrr, I værdige skattejægere, klar til en mysterisk opgave? Hør nu godt efter, for her skal I bruge jeres Linux-terminal-færdigheder til at finde skatten gemt i et digitalt land.

## Del 1: Åbning af Billedet

**Mål:** At kunne åbne et billede fra en Linux-terminal.

1. Først og fremmest, sørg for at du har et billede klar til denne skattejagt. Du kan bruge et hvilket som helst billede, men lad det være med filtypen ```.jpg``` eller ```.png```. Lad os kalde dette billede for ```skattekort.png```.

2. Brug den passende kommandoen ```xdg-open``` til at åbne ```skattekort.png```. Der ligger en fil i denne mappe, få den vist på skærmen og se om du kan se noget mistænkeligt.

## Del 2: Find Koden i Billedet

**Mål:** At finde den skjulte kode i billedets data ved hjælp af terminalkommandoer.

4. Nu, her kommer det rigtig spændende! Det siges, at der gemmer sig en kode i billedet i denne mappe, som kan bruges som en ny terminal komando. Men den er ikke synlig for det blotte øje!

5. Brug kommandoen `cat` til at se indholdet af billedet, Hvad ser du? ***Hint:*** Du vil sandsynligvis se en masse uforståelig tekst.

6. Men frygt ej, vores skattekort indeholder et specielt ord, en kode, der vil afsløre skattens skjulested. Brug kommandoen `grep` til at søge efter ordet ```kode``` i billedets data. Dette gøres ved at bruge en *pibe* så komandoen ser ud som følger: ```cat billede.png | grep -a kode```. Hvad er resultatet? Findes koden?

7. Hvis du har fundet koden, skriv den ned. Hvis ikke, prøv igen med andre kommandoer eller undersøg, om du har skrevet kommandoerne korrekt.

## Del 3: Skattejagtens Afslutning

**Mål:** At afslutte skattejagten og afsløre skatten!

1. Brug den fundne kode. Hvad er det? Hvad vil du gøre med det?


