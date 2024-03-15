Please make sure you have `gcc`, `make` and `autotools` installed

Build cpputest first:
```shell
cd cpputest
autoreconf . -i
./configure
make tdd
```

Build and run the test:
```shell
make all
```
