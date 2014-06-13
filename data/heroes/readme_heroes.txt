Drzewo katalog�w

1. data/ - g��wny folder plik�w zewn�trznych
	1.1. data/maps/ - folder zawieraj�cy pliki map
	1.2. data/heroes/ - katalog bohater�w
		1.2.1. heroeslist.xml - zawiera list� heros�w dost�pnych w grze zapisane w standardzie xml
		1.2.2. Imi�bohatera - zawiera wszystkie pliki sk�adaj�ce si� na herosa
			1.2.2.1 Imi�bohatera.xml - plik zawieraj�cy informacje o konkretnym bohaterze zapisane w standardzie xml
			1.2.2.2 /data/heroes/Imi�bohatera/graphics/ - folder zawieraj�cy katalogi z plikami graficznymi. Ka�da klatka zapisana jest w postaci Imi�bohateraNumerklatki.png
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/going/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji chodzenia. UWAGA: chodzenie do przodu i do ty�u to ta sama animacja jedynie realizowana od przodu/od ty�u
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/standing/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji stania
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/kneeling/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji kl�czenia
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/jumping/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji skakania
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/highpunch/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji highpuncha
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/lowpunch/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji lowpuncha
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/highkick/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji highkicka
				1.2.2.2.1 /data/heroes/Imi�bohatera/graphics/lowkick/ - folder zawieraj�cy pliki b�d�ce poszczeg�lnymi klatkami animacji lowkicka




Dost�pne stany bohatera (do tej pory)

going, standing, kneeling, jumping, highpunch, lowpunch, highkick, lowkick

UWAGA: Aby doda� nowego bohatera do bazy gry nale�y doda� jego dane do pliku data/heroes/heroeslist.xml


Edycja pliku Imi�bohatera.xml

Dla ustalenia hitbox�w oraz animacji nale�y w folderze /data/heroes/Imi�bohatera/ stworzy� plik Imi�bohatera.xml . J�zyk ten jest bardzo restrykcyjny dlatego nie wolno zostawia� pustych wierszy, a struktura dokumentu musi by� zachowana.

Dokument nale�y przygotowa� w podany spos�b:

1. Skopiowa� nag��wek:
<?xml version="1.0" encoding="UTF-8"?>
<document>

2. Otworzy� rodzica w zale�no�ci od celu:
<action>
<basic>
<special>

2. Stworzy� potomka <standing multipier="x" repeat="1" length="1" damage="1">, gdzie w miejsce x wstawi� mno�nik odwrotno�ci szybko�ci dzia�ania (im wi�kszy mno�nik tym wolniesza animacja). Nale�y zauwa�y�, �e ka�dy z nas zrobi animacje o r�nych "skokach" czasowych, dlatego mno�nik pozwala na dopasowanie szybko�ci dzia�ania do konkretnej animacji. S�owo "standing" odpowiada za stan bohatera kt�rego hitboxy chcemy opisywa�. Argument repeat jest opcjonalny. Odpowiada on za to, czy podczas przytrzymania przycisku akcja b�dzie wykonywana wielokrotnie. Argument length(opcjonalny) odpowiada za d�ugo�� animacji, je�li chcemy aby by�a wykonywana d�u�ej ni� d�ugo�� animacji. Argument damage obs�ugiwany jest jedynie w rodzicach basic i special, odpowiada za warto�� obra�e� zadawanych przez ataki. W specjalach istnieje tak�e potomek "component", kt�ry odpowiada za jeden przycisk kombinacji. Argument state odpowiada za stan bohatera (0-action, 1-basic), natomiast warto�� umieszczona w tagu za warto�� stanu (dla state="0" warto�� 0 to stanie, 1 to krok do przodu, 2 krok do ty�u, 3 kucanie, 4 skakanie, 5 blok).

3. Stworzy� subpotomka <hitbox x="" y="" w="" h="" startframe="" finishframe="" defensive="1"/>. Warto�� x to wsp�rz�dna x(ro�nie w prawo) analogicznie dla y(ro�nie w d�). Pocz�tek uk�adu wsp�rz�dnych znajduje si� w lewym g�rnym rogu klatki postaci. Argument "w" odpowiada za szeroko�� prostok�ta, natomiast "h" za wysoko��. "startframe" to atrybut kt�ry oznacza numer klatki, w kt�rej hitbox ma si� 'w��czy�', "finishframe" to czas jego ko�ca. Argument defensive/offensive odpowiada za rodzaj hitboxa. Inb4 dajecie jedno i drugie o warto�ci 1, nie zadzia�a. UWAGA: PAMI�TA� O ZAMKNI�CIU ZNACZNIKIEM "/>", jak jest to dane w przyk�adzie.

4. Zamkn�� rodzica </standing>

5. W tym momencie mo�na powtarza� kroki 2,3,4 z r�nymi stanami bohatera.

6. Zamkn�� </document>