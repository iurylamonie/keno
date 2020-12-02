# 1. Introdução:

Este projeto contém programa que reproduz um jogo Keno em uma versão simples de texto.

# 2. Makefile/Compiling:

Verifica se o setup está configurado, caso contrario, fará um novo setup chamando "make dir" e compila. Ele chama "make all" internamente.

```
make
```

Você também pode passar argumentos para o compilador. Como o exemplo abaixo:
```
make args="-D something=212"
```
Para ativar o modo debug, faça:

```
make args="-D DEBUG"
```

Fará tods os diretórios de trabalho. Você pode fazer isso manualmente ou automaticamente se você usar "make".
```
make dir
```

Limpa todo o diretorio de trabalho, irá apagar todos os arquivos contidos em bin e docs
```
make clean
```

Fará a documentação para o projeto atual.
```
make doxy
```

Irá chamar "make clear" e "make dir"
```
make fresh
```

# 3. Rodando o Keno:

1. É recomendavel colocar o seu arquivo de apostas na pasta doc. O arquivo deve está no formado ".dat". Por exemplo:
```
bet.dat
```

2. Para rodar o executável, faça:
```
./bin/main
```

3. É necessario informar a localização e o nome do arquivo de apostas para inicializar o jogo corretamente.
```
./bin/main doc/bet.dat
```
