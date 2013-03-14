[tij4] Gândind în Java, ediția a 4-a de Bruce Eckel
===================================================


Introducere la obiecte
----------------------

Toate limbajele de programare furnizează o formă de abstracție.
Alan Kay a sumarizat 5 caracteristici de bază a OOP:

* totul este un obiect
* un program este o grămadă de obiecte ce își spun unele altora ce să facă prin diferite mesaje
* fiecare obiect are propria memorie făcută din alte obiecte
* fiecare obiect are un tip
* toate obiectele de același tip primi aceleași mesaje 

Booch a oferit o descriere mai succintă a unui obiect: _un obiect are stare, comportament și identitate._

### Un obiect are o interfață

Obiectele care sunt identice cu excepția propriei stări din timpul execuției programului, sunt grupate împreună în „clase de obiecte” — cuvântul cheie `class`. Tipurile de date abstracte sunt aproape exact ca tipurile primare: poți crea variabile (numite *obiecte* sau *instanțe* ale clasei) și manipula aceste variabile (prin trimiterea de *mesaje* sau *cereri*).

Ceea ce facem cu adevărat în programarea OO (orientată-obiect) este să creăm noi tipuri de date. O clasă descrie un set de obiecte ce au caracteristici identice și comportament. Cererile pe care le poți face către un obiect sunt definite de propria interfață, iar tipul este cel care determină interfața.

### Implementarea ascunsă

Putem împărți programatorii în creatorii de clase (cei care adaugă noi tipuri de date) și clienții (consumatorii care folosesc tipurile de date în aplicațiile lor).

Scopul programatorului client este să colecteze un set de unelte (clase) pentru o dezvoltare rapidă a aplicației. Scopul creatorului de clase este să creeze o clasă care să expună doar ce este *necesar* clientului și să păstreze restul ascuns. De ce? Pentru că tot ce a fost ascuns nu poate fi accesat de clientul programator, deci creatorul de clasă poate modifica partea ascunsă fără să-și facă griji despre impactul asupra celorlalți.

Java folosește 3 cuvinte cheie explicite pentru controlul accesului într-o clasă: public, private și protected.

* `public` — elementul (câmp sau metodă) poate fi accesat de oriunde în program
* `private` — elementul poate fi accesat doar în interiorul metodelor clasei
* `protected` — la fel ca *private*, în plus poate fi accesat în interiorul metodelor din clasa moștenitoare
* `default` (numit și *acces în pachet*) — metodele claselor din același pachet pot accesa elementele ce nu au un specificator de acces.

### Reutilizarea codului

Cea mai simplă metodă de reutilizare a unei clase este să utilizezi un obiect din acea clasă direct, dar poți pune obiectul într-o clasă nouă — crearea unui membru obiect. Deoarece compui o nouă clasă din clase existente, acest concept este numit **compoziție** — o relație de tipul **are-o** sau **are-un**.

### Moștenirea

Prin **moștenire** putem clona o clasă existentă și să adăugăm noi câmpuri sau modificări în funcționalitate. Toate modificările din clasa de bază (numită și *clasa părinte* sau *superclasă*) sunt reflectate automat în noua clasă.

Când moștenești un tip existent, creezi un nou tip. Acesta conține nu doar membrii tipului de bază ci mai important duplică interfața clasei de bază — toate mesajele ce pot fi trimise obiectelor din clasa de bază pot fi trimise și obiectelor din clasa derivată.

Ai la dispoziție două căi pentru a diferenția clasa de bază de clasa derivată.

* adaugi noi metode în clasa derivată
* modifici comportamentul unei metode din clasa de bază — numită **suprascriere** a metodei.


Totul este un obiect
--------------------

Java tratează totul ca un obiect. De fapt identificatorul pe care îl manipulezi este o **referință** la un obiect.

Când creezi o referință, vrei să o conectezi cu un obiect. Asta se face în general cu operatorul `new`:

    String s = new String("asdf");

Este util să vizualizezi cum este aranjată memoria. Există 5 locuri diferite pentru stocare date:

* **regiștrii**: localizați în procesor. Nu ai control direct nici nu ai vreo dovadă în program că ei ar exista.
* **stiva**: localizată în general în zona RAM cu acces direct de la procesor via registrul SP — „stack pointer”. Referințele la obiecte sunt plasate pe stivă, în schimb obiectele nu.
* **movila**: localizată tot în RAM este o zonă de memorie unde sunt stocate toate obiectele Java. Compilatorul nu trebuie să știe pentru cât timp datele trebuie să rămână în movilă.
* date **constante**: localizate direct în codul program.
* stocare non-RAM: datele rămân persistente chiar și atunci când programul a terminat executația, de exemplu o bază de date.

### Tipurile primitive

Crearea obiectelor cu `new` nu este foarte eficientă deoarece sunt plasate în movilă.
Pentru tipurile primitive o variabilă este creată automat — nu este o referință — ce reține valoarea direct și este memorată pe stivă, deci mult mai eficient.

Java determină dimensiunea fiecărui tip primitiv. Aceste dimensiuni nu se schimbă de la o arhitectură la alta — programele Java sunt mai portabile decât programele scrise în alte limbaje.

    Tipul primitiv | Dimensiune | Minimul | Maximul | D.Membru | Clasă
    ----------------------------------------------------------------------
    boolean        |  -         | -       | -       | false    | Boolean
    char           |  16 biți   | Unicod 0| 2¹⁶-1   | '\u0000' | Character
    byte           |   8 biți   | -128    | +127    | (byte)0  | Byte
    short          |  16 biți   | -2¹⁵    | +2¹⁵-1  | (short)0 | Short
    int            |  32 biți   | -2³¹    | +2³¹-1  | 0        | Integer
    long           |  64 biți   | -2⁶³    | +2⁶³-1  | 0L       | Long
    float          |  32 biți   | IEEE754 | IEEE754 | 0.0f     | Float
    double         |  64 biți   | IEEE754 | IEEE754 | 0.0d     | Double
    void           |  -         | -       | -       | -        | Void

Toate tipurile numerice sunt **cu semn**. Dimensiunea tipului *boolean* nu este specificată — poate lua doar valorile literale `true` sau `false`.

### Numere de mare-precizie

Java include două clase pentru operații aritmetice de mare-precizie: `BigInteger` și `BigDecimal`. *BigInteger* suportă întregi de precizie arbitrară. *BigDecimal* suportă numere reale cu punct fix de precizie arbitrară.

### Vectori în Java

Un vector în Java este garantat să fie inițializat și nu poate fi accesat în afara limitelor sale. Verificarea limitelor vine cu un preț de memorie și penalizare a timpului de execuție.

Când creezi un vector de obiecte, de fapt este creat un vector de referințe ce sunt inițializate automat la valoarea specială `null`.

### Crearea de noi tipuri de date: «class»

La crearea unei clase poți pune două tipuri de elemente în clasa ta:

* **câmpuri** numite și date membru
* **metode** numite și funcții membru

Datele membru sunt accesate folosind operatorul `.`.

Când o variabilă primitivă este membru a unei clase, Java garantează inițializarea ei la o valoare implicită (dacă nu este inițializată explicit). Variabilele primitive declarate local **nu** sunt inițializate implicit.

### Metode, argumente și valori returnate

În Java metodele determină mesajele pe care un obiect le poate primi. Părțile fundamentale ale unei metode sunt: *nume*, *argumente* și *tipul returnat*. Aceasta este forma de bază:

    TipulReturnat numeMetoda( /* listă argumente */ ) {
      /* corpul metodei */
    }

Numele metodei și lista argumentelor (numită **semnătura** metodei) identifică în mod unic metoda.

Metodele sunt create numai ca parte a clasei. O metoda poate fi apelată doar pentru un obiect (cu excepția metodelor de clasă) prin folosirea operatorului `.` la fel ca datele membru:

    numeObiect.numeMetoda(arg1, arg2);

### Construirea unui program Java

Pentru a produce un nume neambiguu al librăriilor, creatorii Java vor ca tu să utilizezi domeniul tău Internet în ordine inversă deoarece numele de domeniu sunt unice (ex. ro.companie.produs). Punctele reprezintă subdirectoare ale proiectului. Tot numele pachetului se scrie doar cu litere mici.

Cuvântul cheie `import` spune compilatorului să utilizeze un pachet — o librărie de clase. Pentru a importa toate pachetele `util` din librăria standard Java se scrie așa:

    import java.util.*;

Librăria standard Java importată automat în orice program este `java.lang`.

Cuvântul cheie `static` poate fi folosit pentru a declara că anumite date sau funcții membru nu sunt asociate cu un anumit obiect ci sunt asociate clasei. Deci, chiar dacă nu ai creat nici un obiect de tipul clasei respective poți accesa un câmp static (*câmp de clasă*) sau apela o metodă statică (*metodă de clasă*). Datele și funcțiile statice pot fi adresate în două feluri, printr-o referință la un obiect sau direct prin numele clasei. Numele clasei este preferat atât pentru claritate cât și pentru optimizarea codului de către compilator.

### Documentația comentariu

Toate comenzile `javadoc` sunt scrise în comentarii `/** .. */`. Există două feluri principale de utilizare Javadoc: direct cod HTML sau etichete „doc”.
Etichetele *doc* independente sunt comenzi ce încep cu caracterul `@` plasat la începutul unei linii comentariu.
Etichetele *doc* interne pot apare oriunde într-un comentariu dar sunt înconjurate de acolade.

Sunt 3 tipuri de comentarii documentație ce corespund elementului pe care îl precede: clasă, câmp sau metodă. Javadoc procesează documentația comentariu doar pentru membrii „public” și „protected”.

    //: director/fișier.java
    
    /** comentariu clasă */
    public class numeClasă {
    
    /** comentariu câmp */
    public int i;
    
    /** comentariu metodă */
    public void f() {}
    } ///:~

Câteva etichete *doc* utilizate frecvent:

    @see fully-qualified-classname#method-name
    {@link package.class#member label}
    
    {@docRoot}
    {@inheritDoc}
    
    @author author-information
    @version version-information
    
    @since
    @param parameter-name description
    @return description
    @throws fully-qualified-class-name description
    @deprecated

Java recomandă un [stil de cod][2] descris în „Code Conventions for the Java Programming Language”.

[2]: http://java.sun.com/docs/codeconv/index.html
