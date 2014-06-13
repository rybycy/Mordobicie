Drzewo katalogów

1. data/ - g³ówny folder plików zewnêtrznych
	1.1. data/maps/ - folder zawieraj¹cy pliki map
	1.2. data/heroes/ - katalog bohaterów
		1.2.1. heroeslist.xml - zawiera listê herosów dostêpnych w grze zapisane w standardzie xml
		1.2.2. Imiêbohatera - zawiera wszystkie pliki sk³adaj¹ce siê na herosa
			1.2.2.1 Imiêbohatera.xml - plik zawieraj¹cy informacje o konkretnym bohaterze zapisane w standardzie xml
			1.2.2.2 /data/heroes/Imiêbohatera/graphics/ - folder zawieraj¹cy katalogi z plikami graficznymi. Ka¿da klatka zapisana jest w postaci ImiêbohateraNumerklatki.png
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/going/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji chodzenia. UWAGA: chodzenie do przodu i do ty³u to ta sama animacja jedynie realizowana od przodu/od ty³u
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/standing/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji stania
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/kneeling/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji klêczenia
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/jumping/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji skakania
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/highpunch/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji highpuncha
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/lowpunch/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji lowpuncha
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/highkick/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji highkicka
				1.2.2.2.1 /data/heroes/Imiêbohatera/graphics/lowkick/ - folder zawieraj¹cy pliki bêd¹ce poszczególnymi klatkami animacji lowkicka




Dostêpne stany bohatera (do tej pory)

going, standing, kneeling, jumping, highpunch, lowpunch, highkick, lowkick

UWAGA: Aby dodaæ nowego bohatera do bazy gry nale¿y dodaæ jego dane do pliku data/heroes/heroeslist.xml


Edycja pliku Imiêbohatera.xml

Dla ustalenia hitboxów oraz animacji nale¿y w folderze /data/heroes/Imiêbohatera/ stworzyæ plik Imiêbohatera.xml . Jêzyk ten jest bardzo restrykcyjny dlatego nie wolno zostawiaæ pustych wierszy, a struktura dokumentu musi byæ zachowana.

Dokument nale¿y przygotowaæ w podany sposób:

1. Skopiowaæ nag³ówek:
<?xml version="1.0" encoding="UTF-8"?>
<document>

2. Otworzyæ rodzica w zale¿noœci od celu:
<action>
<basic>
<special>

2. Stworzyæ potomka <standing multipier="x" repeat="1" length="1" damage="1">, gdzie w miejsce x wstawiæ mno¿nik odwrotnoœci szybkoœci dzia³ania (im wiêkszy mno¿nik tym wolniesza animacja). Nale¿y zauwa¿yæ, ¿e ka¿dy z nas zrobi animacje o ró¿nych "skokach" czasowych, dlatego mno¿nik pozwala na dopasowanie szybkoœci dzia³ania do konkretnej animacji. S³owo "standing" odpowiada za stan bohatera którego hitboxy chcemy opisywaæ. Argument repeat jest opcjonalny. Odpowiada on za to, czy podczas przytrzymania przycisku akcja bêdzie wykonywana wielokrotnie. Argument length(opcjonalny) odpowiada za d³ugoœæ animacji, jeœli chcemy aby by³a wykonywana d³u¿ej ni¿ d³ugoœæ animacji. Argument damage obs³ugiwany jest jedynie w rodzicach basic i special, odpowiada za wartoœæ obra¿eñ zadawanych przez ataki. W specjalach istnieje tak¿e potomek "component", który odpowiada za jeden przycisk kombinacji. Argument state odpowiada za stan bohatera (0-action, 1-basic), natomiast wartoœæ umieszczona w tagu za wartoœæ stanu (dla state="0" wartoœæ 0 to stanie, 1 to krok do przodu, 2 krok do ty³u, 3 kucanie, 4 skakanie, 5 blok).

3. Stworzyæ subpotomka <hitbox x="" y="" w="" h="" startframe="" finishframe="" defensive="1"/>. Wartoœæ x to wspó³rzêdna x(roœnie w prawo) analogicznie dla y(roœnie w dó³). Pocz¹tek uk³adu wspó³rzêdnych znajduje siê w lewym górnym rogu klatki postaci. Argument "w" odpowiada za szerokoœæ prostok¹ta, natomiast "h" za wysokoœæ. "startframe" to atrybut który oznacza numer klatki, w której hitbox ma siê 'w³¹czyæ', "finishframe" to czas jego koñca. Argument defensive/offensive odpowiada za rodzaj hitboxa. Inb4 dajecie jedno i drugie o wartoœci 1, nie zadzia³a. UWAGA: PAMIÊTAÆ O ZAMKNIÊCIU ZNACZNIKIEM "/>", jak jest to dane w przyk³adzie.

4. Zamkn¹æ rodzica </standing>

5. W tym momencie mo¿na powtarzaæ kroki 2,3,4 z ró¿nymi stanami bohatera.

6. Zamkn¹æ </document>