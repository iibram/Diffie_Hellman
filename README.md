# Diffie_Hellman

Ein weiteres Projekt während meines Studiums der Informatik (B.Sc.) mit dem Zweck:
* generell meine praktische Programmiererfahrung und konkret in C++ zu steigern,
* die erlernten Algorithmen mit meiner Auffassung in Code zu gießen und
* um zu sehen, ob meine Auffassung ebenfalls die zugrundeliegende Mathematik widerspiegelt

---

## Das "Diffie Hellman Verfahren"

Das **Diffie Hellman Verfahrens** ist ein essentielles Verfahren in der elektronischen Kryptographie, welches im Zeitalter des Internets ihren festen Sitz hat und weiterhin haben wird.

Die Besonderheit und der Einsatzzweck dieses Verfahrens ist, das sich zwei Seiten einen absolut sicheren gemeinsamen Schlüssel generieren lassen können, wobei beide Seiten zur Findung dieses gemeinsamen Schlüssels, ihre privaten Schlüssel benutzen. Eine Nachricht - chiffriert mit dem gemeinsamen Schlüssel -  können beide Seiten wiederum nur mit ihren privaten Schlüssel dechiffrieren. Der gemeinsame Schlüssel kann derweil frei übers Internet versandt werden, da sonst niemand was damit anfangen kann. Also ein erstklassiges Tool zum gegenseitigen versenden von chiffrierten Nachrichten, wobei nur die public Schlüssel übers Internet geschickt werden müssen. Also auch bei einem **"man in the middle"** Angriff, gibt es keinen Schwachpunkt das preisgegeben wäre.
