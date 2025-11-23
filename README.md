# 21
Gra inspirowana częścią DLC z Resident Evil 7 o nazwie Banned Footage vol.2 w którym znajduje się gra karciana 21.

- Aby rozpocząć grę należy w lobby kliknąć przycisk rozpocznij.
<img src="zdjecia dla readme/lobby.png" height="320">

## Gameplay
- Grasz przeciwnko botowi sterowanemu prostym algorytmem który dokonuje ruchów za niego (niejest to AI).
- Wygrywa osoba która jest najbliżej limitu wyniku gry, ale nieprzekracza go.
- Gdy obaj gracze przekroczą limit wyniku gry, wygrywa osoba mająca mniejszą sumę wartości kart.
- Jeżeli obaj gracze mają taką samą sumę wartości kart, jest remis.
- Co każde zwycięstwo gracza, jego przeciwnik traci zdrowie o zadane przez gracza obrażenia.
- Karty można dobierać klawiszem '1' z talii składającej się z kart ponumerowanych od 1 do 11.
- Karty w talii niepowtarzają się.
- Aby niedobrać dobrać karty w swojej turze, należy wcisnąć klawisz '2'.
- Nad swoimi kartami widoczna jest suma ich wartości, ilość zadawanych obrażeń oraz poziom zdrowia (u przeciwnika też).
- Niewidzisz pierwszej karty przeciwnika oraz nieznasz jej wartości do momentu zakończenia rundy.
- W każdym momencie można zatrzymać grę klawiszem 'ESC'.
- Gra trwa do momentu w którym jeden z graczy straci całe zdrowie.
<img src="zdjecia dla readme/rozgrywka.png" height="320">

## Karty specjalne
- Na początku każdej rundy obaj gracze dobierają po dwie karty oraz jedną kartę specjalną.
- Jeżeli jest to pierwsza runda, obaj gracze dobierają jeszcze jedną kartę specjalną.
- W każdym momencie zarówno gracz jak i przeciwnik mogą użyć kart specjalnych:
  - Dostępne karty specjalne są widoczne w ekwipunku (dostępny pod klawiszem 'E').
  - Każda karta specjalna powoduje coś innego (np. zwiększa atak, zmniejsza atak przeciwnika, zamiana ostatnimi kartami z przeciwnikiem itp.).
  - Wszystkie karty specjalne mają swój opis.
  - Niektóre karty specjalne muszą zostać położone na stół (zwiększanie ataku oraz zmniejszanie ataku przeciwnika).
  - Limit kart specjalnych na stole dla każdego gracza wynosi 5.
  - Limit kart specjalnych w ekwipunku dla każdego gracza wynosi 20.
  - Co każdą turę karty specjalne ze stołu znikają po obu stronach.
  <img src="zdjecia dla readme/ekwipunek.png" height="320">

## Ustawienia
- W ustawieniach można zmienić głośność muzyki która jest odtwarzana cały czas w tle.
- Jeżeli nieudało się załadować muzyki, pasek zmieniania głośności będzie niedostępny.
<img src="zdjecia dla readme/ustawienia.png" height="320">

## Informacje techniczne
Projekt korzysta z zewnętrznej biblioteki <a href="https://github.com/SFML/SFML" target="_blank">SFML</a> która jest zlinkowana statycznie wraz ze wszystkimi funkcjami i klasami z biblioteki standardowej rownież zlinkowanymi statycznie. Jeżeli chcesz skompilować projekt u siebie używając kompilatora MSVC, będziesz musiał skompilować na nowo bibliotekę sfml wraz z opcją "biblioteka środowiska uruchomieniowego: wielowątkowa (MT)" dla każdej potrzebnej biblioteki a następnie w Visual Studio w ustawienia projektu ustawić odpowiednie ścieżki do plików nagłówkowych oraz bibliotek statycznych. W przypadku kompilacji z innym kompilatorem, należy zmienić też dodatkowe atrybuty funckji z __forceinline na inny w zależności od kompilatora, który będzie również wymuszać inlinowanie funkcji (bądź wogóle niewymuszać inlinowania tych funkcji).

### Hierarchia katalogów w projekcie
<img src="zdjecia dla readme/hierarchia%20katalogow.png">

## Zasoby
- Grafika do wszystkich kart wykonana przeze mnie.
- Muzyka w tle pochodzi z epki zespołu <a href="https://open.spotify.com/artist/6Go3NbvoYrjs74biJvpPqd" target="_blank">septemberistheonlytimeidontthinkofyou</a>.
- Czcionka autorstwa Riciery Leal ze strony <a href="https://www.dafont.com/vcr-osd-mono.font" target="_blank">dafont</a>.
