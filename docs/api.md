# Lab 4 B1 — objective і gradient API

typedef double (*miniai_objective_function)(const double x[], size_t n, void *context);

Callback:
- x тільки читається (const), n > 0
- context не змінюється і не звільняється; NULL можна, якщо callback його не використовує
- NAN або Inf у результаті = помилка

Status codes:
- 0 OK
- 1 INVALID_ARGUMENT — NULL, n == 0, h <= 0 або не скінченне
- 2 NONFINITE_OBJECTIVE — callback повернув NAN/Inf
- 3 NO_MEMORY — не вдалося виділити пам'ять

Пам'ять:
- x не змінюється, координати міняються в копії
- результат спочатку в тимчасовому масиві, у gradient копіюється тільки при успіху
- при помилці gradient не змінюється