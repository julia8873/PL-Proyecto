# Práctica 2 - PL

### 0. Instalación previa (solo si no tenéis flex)
```bash
sudo apt update && sudo apt install -y flex gcc
```

### 1. Compilar
Con Makefile:
```bash
make comp
```

*(O a mano paso a paso sin make)*:
```bash
flex -l lexico.l
gcc -o lexico lex.yy.c
```

### 2. Ejecutar
Con el archivo de prueba:
```bash
./lexico prueba.babad
```

O con cualquier otro archivo:
```bash
./lexico <nombre_archivo>
```

### 3. Limpiar
```bash
make clean
```
