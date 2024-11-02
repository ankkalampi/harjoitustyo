# Reitinhaku kaksiulotteiseen tasohyppelypeliin - Määrittelydokumentti

## Ohjelmointikielet

Harjoitus toteutetaan Pythonilla. Pythonin lisäksi osaan jonkin verran myös C:tä sekä C++:aa.

## Algoritmit

Harjoitustyössä käytetään kolmea eri algoritmia:

- Pelikentän analysoiva algoritmi, joka toimii seuraavasti:
    1. Jokaista tasopalasta kohden muodostetaan solmu suunnistusverkkoon ja liikkumisverkkoon. Liikkumisverkkoon tallennetaan solmun koordinaatit.
    2. Tarkistetaan jokaisen solmun kohdalla, muodostuuko siitä suora kaari johonkin toiseen solmuun. Kaikki solmut tarkistetaan jokaisen solmun kohdalla. Kaari muodostetaan, jos:
    - tasopalaset ovat naapureita, eli muodostavat yhtenäisen tason. Kaaren tyyppi on "Juokse"
    - tasopalasten välillä on portaikko. Kaaren tyyppi on "Kiipeä"
    - toinen taso on toisen tason alapuolella siten, että sen päälle on mahdollista tiputtautua (tähän kovakoodataan jokin etäisyysarvo) Kaaren tyyppi on "Tiputtaudu"
    - toinen taso on toisen tason kanssa samalla korkeudella siten, että tasolta toiselle voi hypätä (tähän kovakoodataan jokin etäisyysarvo) Kaaren tyyppi on "Hyppää"
    3. Liikkumisverkon perusteella muodostetaan suunnistuverkon kaaret. Suunnistusverkon kaarilla ei ole mitään tyyppiä, mutta verkko on suunnattu.

- Hirviön reitinhaun toteuttava algoritmi. Tähän käytetään Dijkstran algoritmia tai A*-algoritmia.

- Hirviön liikkumisen mahdollistava algoritmi, joka toimii seuraavasti:
    1. Tarkisteaan, ollaanko koordinaattien perusteella todella liikkumissolmun kuvaamalla tämänhetkisellä solmulla. Jos ei olla, ajetaan reitinhakualgoritmialgoritmi uudestaan. Tämä ristiriita voi johtua esimerkiksi virheellisesti suoritetusta hypystä, tai, mikäli peliä kehitetään pidemmälle, esimerkiksi jostain pelaajan toiminnasta.
    2. Otetaan suunnistusalgoritmista seuraava tavoitesolmu ja siihen johtava kaari. Otetaan talteen kaaren id sekä tavoitekaaren id.
    3. Tarkistetaan id:tä vastaava kaaren tyyppi liikkumisverkosta, sekä haetaan tavoitesolmun id:n mukainen koordinaatti liikkumisverkosta.
    4. Kaaren tyypin sekä tavoitesolmun koordinaatin perusteella muodostetaan liikkumisstrategia seuraavasti:
    - mikäli tyyppi on "Juokse" , katsotaan onko tavoitesolmu sen koordinaatin perusteella oikealla vai vasemmalla puolella. Jos oikealla, niin liikutaan oikealle, kunnes saavutetaan tavoitesolmu, tai jos vasemmalla, niin liikutaan vasemmalle, kunnes saavutetaan tavoitesolmu.
    - mikäli tyyppi on "Kiipeä", katsotaan onko tavoitesolmu sen koordinaatin perusteella ylä- vai alapuolella. Jos yläpuolella, niin kiivetään ylöspäin, kunnes tavoitetaan tavoitesolmu, ja jos alapuolella, niin kiivetään alaspäin, kunnes tavoitetaan tavoitesolmu.
    - mikäli tyyppi on "Tiputtaudu", katsotaan tavoitesolmun etäisyys vaaka- ja pystysuunnassa ja suunnataan hyppy tämän perusteella.
    - mkäli tyyppi on "Hyppää", katsotaan tavoitesolmun etäisyys vaakasuunnassa, ja muodostetaan hyppy tämän perusteella.

    Hyppyjen suorittamiseen liittyvä logiikka suoritetaan yksinkertaisella laskutoimiuksella, jonka lopullinen sisältö muodostunee yrityksen ja erehdyksen kautta.



## Ratkaistava ongelma

Valmiina on yksinkertainen, Pygame-kirjastolla toteutettu tasohyppelypeli. Tasohyppelypelissä hirviöt seuraavat pelaajahahmoa yrittäen saada tämän kiinni. Sekä pelaaja että hirviöt voivat liikkua sivusuunnassa, hypätä sekä kiivetä portaita. Hirviöt eivät kuitenkaan osaa suunnitella reittiä pelaajan luokse.

Tavoitteena on rakentaa ohjelma, joka pelin alkaessa analysoi pelikentän, ja rakentaa siitä suunnistusverkon (navigation mesh). Pelin edetessä hirviöiden ohjausalgoritmi soveltaa jokaisen hirviön kohdalla tietyin väliajoin esimerkiksi dijkstran algoritmia tai A*-algoritmia reitinhakuun suunnistusverkossa.

Lisäksi muodostetaan liikkumisverkko, joka vastaa suunnistusverkkoa, ja joka kertoo hirviölle, miten jostain solmusta sen naapurisolmuun liikutaan (hyppy, juoksu, kiipeäminen)

## Syötteet ja niiden käyttö

Syötteenä toimii suunnistusverkon muodostamisessa pelikenttä. Pelikenttä muodostetaan tekstitiedostosta, jossa välilyönnit tarkoittavat tyhjää tilaa, #-merkki seinää, P-merkki tasoa S-merkki porrasta, M-merkki hirviön aloituspaikkaa, H-merkki pelaajahahmon aloituspaikkaa, ja W-merkki pelikentän maalia, jonka saavuttamalla pelaaja voittaa pelin. Pelikentän generoiva järjestelmä on jo olemassa.

Varsinaisessa reitinhaussa syötteenä toimii pelaajan liikkuminen. Tasopalanen, jonka päällä pelaaja on, kuvaa jotain suunnistusverkon solmua. Pelaajan liikkuessa pelaajan sijaintisolmu muuttuu siten, että pelaajan alla oleva solmu otetaan pelaajan sijaintisolmuksi. Jos pelaajahahmo on siis ilmassa, suoraan pelaajan alla oleva solmu on tämän sijaintisolmu riippumatta etäisyydestä. Sijaintisolmun vaihtuessa myös hirviöiden reitinhakualgoritmi ajetaan uudestaan. 

## Aika- ja tilavaativuudet

## Harjoitustyön ydin