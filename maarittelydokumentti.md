# Reitinhaku kaksiulotteiseen tasohyppelypeliin - Määrittelydokumentti

## Ohjelmointikielet

Harjoitustyö toteutetaan C++:lla. Lisäksi osaan jossain määrin C:tä, C#:ia sekä Pythonia

## Algoritmit

Harjoituksessa toteutetaan neuroverkkoja geneettisen algoritmin kautta opettava järjestelmä.

Harjoituksen sovelluksessa simuloidaan populaatiota virtuaalisia eläimiä, jotka liikkuvat simulaatiomaailmassa neuroverkkojensa ohjastamina. Neuroverkkojen syöteneuronit saavat tietoa eläimen ympäristöstä, ja ulostuloneuronit kontrolloivat eläimen liikkumista ja toimintaa. Syöteneuronit mittaavat eläimen lähiympäristöstä, mitä kaikkea siellä on ja millä etäisyydellä. Erilaisia vastaantulevia asioita ovat: toiset normaalit eläimet, toiset lisääntymiskykyiset eläimet sekä ruoka. Mahdollisesti simulaatioon voidaan lisätä myös lihansyöjiä, jotka syövät näitä eläimiä.  Ulostuloneuronit vastaavat seuraavista toiminnoista: liiku eteen, käänny vasemmalle, käänny oikealle, pysy paikallasi. Neuroverkkojen tarkka toteutus esimerkiksi sisempien tasojen (hidden layers) osalta tarkentunee kokeilemalla erilaisia vaihtoehtoja. Vanhemmat palaavat takaisin lisääntymiskyvyttömiksi, kunes ovat syöneet jälleen lisääntymiseen vaadittavan määrän ruokaa.

Eläinten neuroverkot kehittyvät pääsääntöisesti geneettisen algoritmin kautta. Mikäli eläin on saanut syötyä jonkin mielivaltaisen määrän ruokaa (esim 5 annosta), siitä tulee lisääntymiskelpoinen. Lisääntymiskelpoiset eläimet voivat lisääntyä keskenään liikkumalla toitensa päälle. Tällöin syntyy uusia eläimiä, joiden neuroverkot ovat geneettisen algoritmin mukaisesti yhdistelmä vanhempien neuroverkkoja, sekä joitain mutaatioita.

Mikäli eläin on jonkin määritellyn ajan syömättä, se nälkiintyy ja kuolee. Eläimet voivat kuolla myös mahdollisten lihansyöjien saaliina. Eläimen ikä näkyy simulaatiossa muuttuvana värinä.

Simulaation graafinen käyttöliittymä toteutetaan SDL-multimediakirjastolla.

## Ratkaistava ongelma

Simulaation avulla pyritään löytämään keino kouluttaa virtuaalieläinten neuroverkkoja pelkän simuloidun luonnonvalinnan kautta siten, että tuloksena on neuroverkkoja, joiden ohjastamina virtuaalieläimet kykenevät tekemään järkeviä päätöksiä liittyen ravinnon etsintään, lisääntymiseen sekä petojen välttelyyn.

## Syötteet ja niiden käyttö

Syötteinä neuroverkoilla toimii ympäristö, jossa niitä ohjastavat eläimet liikkuvat. 

## Aika- ja tilavaativuudet

Tässä harjoitustyössä toteutettavat neuroverkot eivät lähtökohtaisesti käytä hyväkseen takaisinsyöttöä(backpropagation). Aikavaatimusta laskettaessa on siis oteettava huomioon ainoastaan syöttövaihe. Syöttövaiheen aikavaativuus on O(n*m*L), jossa n = syöteneuronien määrä, m = sisempien neuronien määrä per taso, ja L = sisempien neuronitasojen määrä.

Mikäli neuroverkkojen laskennassa ei käytetä hyväksi rinnakkaislaskentaa, on otettava huomiion myös populaation koko P, jolloin aikavaativuus on O(n*m*L*P). Tilavaativuus neuroverkoilla on niin ikään O(n*m*L) yhden neuroverkon osalta, ja O(n*m*L*P) koko populaation osalta.

## Harjoitustyön ydin

Harjoitustyön ydin on neuroverkon toteuttaminen itse ilman valmiita kirjastoja, sekä geneettisen algoritmin soveltaminen neuroverkkojen oppimisprosessissa.
