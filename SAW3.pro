#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T09:18:17
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SAW3
CONFIG   += console
CONFIG   -= app_bundle
#CONFIG += std=c++11

TEMPLATE = app


SOURCES += main.cpp \
    crypto.cpp \
    file_handler.cpp \
    secureobjstorage.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/block_cipher.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/crypto_hash.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/hmac.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/kuznyechik.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/pbkdf2.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/sha256.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/camellia.cpp \
    ../../../Dev/libs/cppcrypto/cppcrypto-0.17-src/cppcrypto/mars.cpp

HEADERS += \
    crypto.h \
    file_handler.h \
    secureobjstorage.h
