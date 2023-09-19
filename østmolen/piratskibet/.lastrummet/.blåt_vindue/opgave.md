# Angrib det grønne skib

Til denne opgave skal vi bruge de wifi informationer der blev fundet på havnekontorets computer.

---

- For at komme ombord på det grønne skib i horisonten, skal vi bruge wifi og en ny kommando der hedder ```nmcli```.
- ```nmcli```: er et fedt værktøj, den kan vise hvilke netværks enheder man kan bruge til at forbinde til forskellige netværk.
  - ```nmcli```: står for ***netværk manager commandline interface***, commandline interface, er bare navnet på de porgrammer vi bruger i vores terminal.

### Check og start wifi enheden på computeren:

- For at tjekke om der er tændt for wifi, kan man skrive ```nmcli radio wifi```. Her er det vigtig at der står *enabled*, hvis der står *disabled*, skal vi tænde for enheden.
  - Tænde for wifi enheden gøres med: ```nmcli radio wifi on```. nu skulle der gerne stå *enabled*.

### Login på WiFi

- Først skal tjekke om vi kan se det wifi vi skal logge på. For at tjekke tilgængelige wifi, bruger vi kommandoen ```nmcli dev wifi list```, så skrives der en liste af tilgængelige wifi. når man har læst listen, trykker man på ***q*** for at afslutte kommandoen, så man kan bruge terminalen igen.
- For at forbinde til et wifi, skal vi bruge en ***connect*** kommando: ```nmcli dev wifi connect 'Green Ship'```, herefter kommer der et vindue op, hvor der skal skrives det password du fandt på havnekontorets computer.