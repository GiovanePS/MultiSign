# Desafio LabSEC - MultiSign - Giovane Pimentel de Sousa

## 1. Como usar:
[Relatório sobre o MultiSign](https://giovaneps.notion.site/Relat-rio-sobre-o-MultiSign-5e2f57788b004607ab7011f1547955a9?pvs=4)

## 2. Dependências:
-  LibSSL: `libssl-dev`
-  Libp11: `libp11-dev`
-  [OpenSSL v1.0.2](https://www.openssl.org/source/old/1.0.2/)
-  [LibCryptoSEC](https://github.com/LabSEC/libcryptosec)

### Instalação automatizada das dependências:
- OpenSSL 1.0.2:
```
wget https://www.openssl.org/source/old/1.0.2/openssl-1.0.2k.tar.gz \
&& tar -xvf openssl-1.0.2k.tar.gz \
&& cd openssl-1.0.2k/ \
&& ./config shared -Wl,-rpath -Wl,/usr/local/ssl/lib -L/usr/local/ssl/lib -I/usr/local/ssl/include \
&& make \
&& make install
```
- Libp11:
```
wget https://github.com/OpenSC/libp11/releases/download/libp11-0.4.7/libp11-0.4.7.tar.gz \
&& tar -xvf libp11-0.4.7.tar.gz \
&& cd libp11-0.4.7/ \
&& export OPENSSL_CFLAGS=-I/usr/local/ssl/include \
&& export OPENSSL_LIBS="-Wl,-rpath -Wl,/usr/local/ssl/lib -L/usr/local/ssl/lib -lcrypto -ldl" \
&& ./configure --prefix=/opt/libp11 \
&& make \
&& make install
```
- LibCryptoSEC:
```
git clone https://github.com/LabSEC/libcryptosec.git \
&& cd libcryptosec/ \
&& export OPENSSL_PREFIX=/usr/local/ssl \
&& export OPENSSL_LIBDIR=$OPENSSL_PREFIX/lib \
&& export LIBP11_PREFIX=/opt/libp11 \
&& export LIBP11_LIBDIR=$LIBP11_PREFIX/lib \
&& make \
&& make install
```

## 3. Build:
Estando na raíz do projeto, onde está localizado o arquivo _Makefile_.

Execute: `make all`

Os binários resultantes estarão no diretório _bin/_
