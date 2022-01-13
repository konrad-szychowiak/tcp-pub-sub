# Sprawozdanie z projektu

> Konrad Szychowiak 144564
> Julia Auguścik 145172

## Temat: System wymiany komunikatów publish/subscribe

### Opis protokołu komunikacyjnego

Wiadomości przesyłane przez tcp mają następującą postać:

* Każda wiadomość zaczyna się od symbolu typu komunikatu i kończy znakiem `;`
    ```
    <wiadomość> := <symbol-typu> <lista-argumentów> ;
    ```

* Po symbolu znajdują się argumenty, zależne of typu:
  ```
  <lista-argumentów> := \t string 
                      | \t string <lista-argumentów>
    ```
  argumenty są ciągami znaków oddzielonymi od siebie znakiem tabluacji `\t`

#### Typy komunikatów

| symbol | rozwinięcie                 | argumenty                                                                                                                               | wysyła |
|:------:|-----------------------------|-----------------------------------------------------------------------------------------------------------------------------------------|--------|
|  `C`   | _**C**reate conversation_   | `name: string` – tytuł konwersacji, `uuid: string` – identyfikator nadany przez autora                                                  | klient |
|  `D`   | _**D**elete conversation_   | `id: int` – identyfikator konwersacji                                                                                                   | klient |
|  `S`   | _**S**ubscribe_             | `id: int` – identyfikator konwersacji                                                                                                   | klient |
|  `U`   | _**U**nsubscribe_           | `id: int` – identyfikator konwersacji                                                                                                   | klient |
|  `P`   | _**P**ost message_          | `id: int` – identyfikator konwersacji, `content: string` – treść wiadomości                                                             | klient |
|  `N`   | _**N**ew message_ (created) | `id: int` – identyfikator konwersacji, `content: string` – treść wiadomości                                                             | serwer |
|  `L`   | _**L**ist of conversations_ | **ciąg następujących po sobie trójek:** `id: int` – identyfikator konwersacji, `name: string` – tytuł konwersacji, `uuid: string` (j/w) | serwer |

* `id` oznacza identyfikator taki, jaki trzyma i używa serwer
* `int` oznacza, że przesłany ciąg znaków interpretowany będzie jako liczba

---

* po stronie klienta interpretacja przychodzących wiadomości ma miejsce w `TcpMiddleware.onData()` w pliku `client/src/tcp/TcpMiddleware.ts` a wiadomości tworzone są przez `Pack(.ts)`
* po stronie klienta wiadomosci odbiera `ThreadBehaviour` w `server/src/main.cpp` a wysyłają klasy oparte na klasie `Listener` na podstawie wiadomości stworzonych przez `Visitor`-ów.

### Struktura projektu - opis implementacji

#### Serwer

> serwer oparty na C++20

1. wątek główny (funkcja `main`) uruchamia serwer i rozpoczyna nasłuchiwanie.
   + serwer tworzony jest przez klasę `Server` opartą na klasie `Socket`
   + serwer odbiera połącznie używając funkcji `accept()` i przekazuje sterowanie do funkcji `connectionHandlerFactory`
2. `connectionHandlerFactory` zapisuje do struktury `thread_data_t` deskryptor gniazda połączenia a następnie uruchamia funkcję `ThreadBehavior` w nowym wątku
3. `ThreadBehavior` odpowiada za obsługę operacji wykonywanych przez pojedynczego klienta:
   + rejestruje `ConversationsListener`, który zostanie powiadomiony przy każdej zmainie w liście konwersacji (dodanie/usunięcie)
   + nasłuchuje w pętli na komunikaty przychodzące na socket używając funckji `read()` a następnie wykonuje odpowiednie akcje:
     - _**S**ubscribe_: wyszukuje rządaną konwersację i tworzy dla niej `MessagesListener` – klasę która zostaje powiadomiona przy publikacjii wiadomości
     - _**U**nsubscribe_: usuwa `MessagesListener` dla podanej konwersacji 
     - _**P**ost message_: dodaje wiadomość do wskazanej konwersacji i powiadamia o tym wszystkich `MessagesListener`-ów.
     - _**C**reate conversation_: jeżli klient utworzy konwersację, `ThreadBehaviour` dodaje ją do globalnego stanu przechowującego konwersacje i powiadamia wszystkich podłączonych klientów
     - _**D**elete conversation_: usuwa wskazaną konwersację i powiadamia o tym
4. Po zakończeniu połączenia `ThreadBehavior` usuwa wszystkie stworzone przez siebie konwersacje i `Listener`-y oraz zamyka gniazdo połączenia
   + stworzone konwersacje są pamiętane w `createdConversations: vector<Conversation *>`
   + zarejestrowane `Listener`-y są pamiętane w `createdListeners: map<int, MessagesListener *>` oraz w `conversationsListener: ConversationsListener*`
  
#### Klient
> klient oparty na Electron (NodeJS + Chromium) oraz Typescript

1. `src/main.ts` uruchomiony zostaje w głównym procesie Electrona.
2. `src/renderer/renderer.js` zostaje uruchomiony w osobnym procesami odpowiedzialnym za wyrenderowanie strony w html stanowiącej interfejs graficzny
3. komunikacja między tymi dwoma procesami odbywa się za pomocą `Event`-ów (jest to mechanizm wbudowany w Electrona).
4. gdy użytkownik poda dane połączenia (w procesie renderera) generowany jest odpowiedni event i proces główny nawiązuje połączenie [poprzez `net.Socket`](https://nodejs.org/api/net.html#class-netsocket).
5. za każdym razem gdy użytkownik chce wykonać jakąś akcję generowany jest w rendererze event, na podstawie którego wysyłany jest komunikat poprzez `net.Socket.write()`
   1. komunikaty tworzone są przez klasę `Pack`
6. za każdym razem gdy serwer wysyła jakieś dane
generowany jest [event `'data'`](https://nodejs.org/api/net.html#event-data)
który następnie zostaje obsłużony przez klasę `TcpMiddleware`
   1. `TcpMiddleware` używa dekoratora `@reEmmit('event')` który powoduje przesłanie do renderera eventu o nazwie
   `'event'` i danymi takimi jakie zwraca metoda – ułatwia to przekazanie rendererowi odpowiednio przetworzonych
   2. stan konwersacji jest przechowywany w klasie `Store` (src/main/Store.ts), tam zapisywana jest lista konwersacji przekazana przez serwer i z tamtąd jest odczytywana

### Sposób kompilacji i uruchomienia programu

#### Serwer
> Serwer wymaga `cmake` oraz kompilatora C++20, np. gnu `g++`

```shell
# server/
cmake . 
cmake --build .
# wygeneruje plik wykonywalny o nazwie `server`
./server
```

> Serwer można także skompilować i uruchomić jako kontener dokerowy, 
> używając pliku `Dockerfile` dostępnego w katalogu `server/`.

```shell
# server/
docker build -t tcp-server .
```

#### Klient
> Klient bazuje na frameworku [Electron](https://www.electronjs.org/docs/latest/tutorial/quick-start),
> który jest wymagany do uruchomienia projektu.
> Dodatkowo wymagany jest nodeJS oraz npm.

```shell
# client/
npm install # instaluje wymagane zależności
npm start # uruchomi projekt na podstawie skryptu zawartego w package.json
          # oraz stworzy katalog client/build/ zawierający skompilowany javascript
```

> Projekt może zostać skompilowany do plików wykonywalnych 
> używając np. [electron forge](https://www.electronforge.io/) lub [electron builder](https://www.electron.build/).
> Skompilowane pliki wykonywalne znajdują się w repozytorium GitHub.
