# Мини "Библиотечна система"
Това е малка библиотечна система на C++, направена по заданието от господин Владов.

# Компилиране
1. Използвайте тази команда (трябва ви g++ 17 или по-нов):
   ```
   g++ -std=gnu++17 -Wall -Wextra -O2 -o library library.cpp
   ```
или

2. Използвайте среда за разработка( например CodeBlocks)

# Класове 
- Author – Автор (име, година на раждане)
- Book – Книга (заглавие, автор, година, цена, ISBN)
- Member – Читател (име, членски номер, година на присъединяване)
- Loan – Заем (ISBN, членски номер, начална и крайна дата, дали е върната)
- Library – Система (вектор от книги, членове и заеми)

# Примерен изход
```
===== Library =====
Library Summary:
  Books:        2
  Members:      1
  Active loans: 0

Members:
Petar Petrov      M001    Joined: 2023

Books:
Title               Author                Year    Price      ISBN
Pod igoto           Ivan Vazov (1850)      1894      25.50       ISBN-001
Nema zemya          Ivan Vazov (1850)      1900      18.90       ISBN-002

Creating loan for ISBN-001...
Loan created.

Active loans:
ISBN: ISBN-001    | Member: M001   | 2025-11-03 - 2025-11-17 [active]

Availability check for ISBN-001:
Not available

Returning ISBN-001...
Returned successfully

Books by author containing 'Vazov':
Pod igoto           Ivan Vazov (1850)      1894      25.50       ISBN-001
Nema zemya          Ivan Vazov (1850)      1900      18.90       ISBN-002

```
