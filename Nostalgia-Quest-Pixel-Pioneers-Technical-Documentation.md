# Dokumentacja Techniczna: Nostalgia Quest: Pixel Pioneers

## Spis Treści
1. [Wprowadzenie](#wprowadzenie)
2. [Architektura Systemu](#architektura-systemu)
3. [Szczegóły Implementacji](#szczegóły-implementacji)
   3.1 [System ECS](#system-ecs) 
   3.2 [System Renderowania](#system-renderowania)
   3.3 [Generowanie Mapy](#generowanie-mapy)
   3.4 [System Walki](#system-walki)
   3.5 [System Zapisu i Wczytywania](#system-zapisu-i-wczytywania)
   3.6 [Interfejs Użytkownika](#interfejs-użytkownika)
4. [Zależności](#zależności)
5. [Procedury Budowania i Wdrażania](#procedury-budowania-i-wdrażania)
6. [Testowanie](#testowanie)
7. [Przykłady Użycia](#przykłady-użycia)
8. [Licencja](#licencja)
9. [Autorzy](#autorzy)
10. [Podziękowania](#podziękowania)

## Wprowadzenie
Niniejsza dokumentacja zawiera zarys systemów zaimplementowanych oraz 
wykorzystanych do realizacji projektu. 

## Architektura Systemu
Projekt "Nostalgia Quest: Pixel Pioneers" opiera się na modularnej i rozszerzalnej architekturze, wykorzystującej wzorce projektowe, takie jak Entity Component System (ECS), aby zapewnić elastyczność i łatwość w rozbudowie. Poniżej znajduje się opis kluczowych komponentów systemu:

### Menedżer Stanów
Menedżer Stanów jest odpowiedzialny za zarządzanie różnymi stanami gry, takimi jak menu główne, gra, pauza i inne. Każdy stan jest oddzielnym modułem, umożliwiającym łatwą zmianę i dodawanie nowych stanów do gry.

### Menedżer Zdarzeń
Menedżer Zdarzeń obsługuje wszystkie zdarzenia wewnątrz gry, takie jak input od gracza, zdarzenia systemowe i niestandardowe zdarzenia generowane przez inne komponenty gry. Jest to kluczowy element umożliwiający komunikację między różnymi częściami gry.

### Menedżer Scen
Menedżer Scen zarządza różnymi scenami w grze, w tym ich ładowaniem i przełączaniem. Każda scena reprezentuje różne części gry, takie jak poszczególne poziomy, menu lub ekrany końcowe.

#### System ECS
W ramach każdej sceny, System ECS jest stosowany do zarządzania bytami (entities) i ich komponentami. System ten pozwala na dekompozycję obiektów w grze na mniejsze, niezależne części, co zwiększa modularność i elastyczność.

##### Komponenty
Komponenty, takie jak Pozycja, Zdrowie, Grafika, Ekwipunek, Teren, itp., definiują właściwości i stan bytów. Są one wykorzystywane przez różne systemy, aby wpływać na zachowanie i prezentację bytów w grze.

##### Systemy
Systemy, takie jak Ruch, Kolizja, Renderowanie, Walka, Crafting, Generowanie Terenu i Interakcje Terenowe, działają na bytach, które posiadają odpowiednie komponenty, wykonując logikę gry, renderowanie grafiki, obsługę kolizji i inne zadania.

## Zależności
(Wykaz zewnętrznych bibliotek i narzędzi używanych w projekcie)

## Procedury Budowania i Wdrażania
(Instrukcje dotyczące budowania i uruchamiania aplikacji, w tym konfiguracja CMake)

## Testowanie
(Opis strategii testowania, w tym testy jednostkowe i integracyjne)

## Przykłady Użycia
(Przykłady, jak korzystać z gry, w tym komendy do uruchomienia)
