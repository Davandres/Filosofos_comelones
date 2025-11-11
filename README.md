#  Problema de los Filósofos Comelones - Solución en C

Una implementación robusta y educativa del clásico problema de concurrencia **"Dining Philosophers"**, escrita en C con pthreads y semáforos.

##  Objetivo

Resolver el problema garantizando:
- **Ausencia de race conditions**
- **Prevención de deadlock**
- **Minimización de starvation**

##  Características de la solución

- **5 filósofos** y **5 tenedores** (uno entre cada par).
- Cada filósofo **come un número limitado de veces** (`MAX_MEALS = 3`) para terminar limpiamente.
- Uso de:
  - **Semáforos binarios** para modelar los tenedores.
  - **Mutex global** para evitar deadlock durante la toma de tenedores.
- Salida clara en consola para facilitar la depuración y verificación.

##  Compilación y ejecución

```bash
gcc -pthread filosofos_comelones.c -o filosofos_comelones
./filosofos_comelones
