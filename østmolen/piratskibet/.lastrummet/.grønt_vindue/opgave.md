## Se i horisonten, det grønne skib der sejler rundt derude...

- Hvis ikke jeg tager meget fejl, ligner det deres kaptajn, er en total kedelig og almindelig kaptajn. Han har helt sikkert de samme interesser og hobbyer som alle andre pirater.
- Her ved det grønne vindue, ligger en hjemmeside der indeholder de hobbyer som de fleste pirater har. Lad os bruge den hjemme side til at generer en ordbog, vi forhåbentlig kan bruge til at bryde ind på det grønne skib.
<br>
- Prøv at åbne siden med ```xdg-open http://localhost:3000/``` -> så kan du se hvad de bruger deres tid på når de er ude på verdens havene...


### Opret en ordbog....
- Nu skal vi bruge en kommando, vi har brugt før, for at hente informationer om Simon Milfred...
- - Det er nemlig kommandoen der hedder ```cewl```.
- ```cewl```: skal bruge nogle informationer, der skrives bagefter: 
  1. hvis man skriver ```-d [tal]```, kan man angive hvor dybt der skal søges på hjemmesiden, et lavt tal er hurtigt men man får ikke så mange ord. Her skal man prøve sig frem.
     - måske er det nok med ```-d 1```, så bliver man hurtigt færdig og ellers må man prøve med et større tal.
  2. til sidst skriver man ```-w [filnavn]``` som fortæller hvor alle ord og tal skal gemmes.

***Eksempel***
- Her er et eksempel, hvor der oprettes en fil ***minOrdbog***, der søger hurtigt.
<br>
```cewl http://localhost:3000/ -d 1 -w minOrdbog```
<br>
- Nu er det din opgave at oprette en fil udfra hjemmesiden.
- Prøv at læse den fil du har oprettet, så kan du se hvor mange muligheder der skal prøves af, for at gætte koden..!
