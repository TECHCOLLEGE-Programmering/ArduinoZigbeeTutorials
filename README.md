# ArduinoZigbeeTutorials (Danish)

## Raspberry / Linux instructions

Denne guide antager at man allerede har et XBee module der er konfigureret og at man har XCTU fra Digi til at virke.

For opsætning af XBee moduler se moodle rummet for IoT og embedded systemer 1.

### Opsætning af Raspberry Pi
[Download Raspberry Pi Imager](https://www.raspberrypi.com/software/).

Sæt SD kort i din computer og brug imager til at opsætte Raspberrien i headless mode, således at den har adgang til en router og at SSH er slået til.

Sørg for at inkluder et unik navn i hostname, så du ikke kommer i konflikt med andre i klassen, når du skal SSH til den.

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/fee3c7ff-08ff-48d8-adef-03ffd84aa437)

Login med SSH og PuTTY

Hvis ikke du har PuTTY eller lignede på din computer, så er der her et [download link](https://www.putty.org/)

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/4b7f5aba-5486-4b3c-ad26-df804476be23)

Sørg har for at opdatere OS'et og apt-get før du fortsætter.
### Opsætning af minicom og Serial kommunikation

For at bruge Linux konsol til at læse serial kommunikation, bliver vi nød til at installere et værktøj til dette, ligesom på andre OS'er.

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/76bcdf54-9457-46cd-b75d-5dac770dfb0c)

Før vi forsætter med minicom, skal vi finde ud af hvilken Serial port XBee modulet er på. I Linux kan alle devices findes i en mappe.

Kør kommandoen før du sætter USB modulet med XBee'en i. Når man så kør kommandoen igen, så kan man se forskellen på de 2 lister. For at filtrer lidt nemmere kunne man bruge < ls /dev/tty* >
I stedet for:

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/b84855ce-28ea-4e83-a3b0-9618da1ddaa4)

For at komme ind i indstillinger for minicom:

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/23f3c9f0-d24b-4fec-a95d-a6334410d8e7)

Brug indstillinger til at rette < Serial Device > og < Bps/Par/Bits >. Konsulter indstillingerne fra XCTU, hvis du er tvivl om disse.

Husk at gemmen ændringerne fra hovedmenuen af.

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/f33af545-99b2-4d18-8ce2-270830dee1cc)

[Billed Kilde](https://wiki.emacinc.com/wiki/Getting_Started_With_Minicom)
Test af forbindelse

Arbejd i grupper af 2 eller 3 for at teste opsætningen er korrekt, del IP adresserne på XBee modulerne med hinanden og brug XCTU til at sende pakker til den der sidder i raspberrien.

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/0fa1ed0b-fd2e-4abb-9a03-1628e3eeed5b)

Se serial kommunikation i minicom på raspberrien.

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/f5ac32b3-8297-4e21-a86d-965e7fa9199a)

Hvis opsætningen er lavet korrekt, så vil i kunne se en Mac adressen i ASCII og den besked der bliver sendt.

![billede](https://github.com/lkri-dev/ArduinoZigbeeTutorials/assets/59120028/09365a2c-add7-43f0-8030-c60af0bb0cd4)
