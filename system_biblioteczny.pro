TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    funkcje.cpp \
    loan.cpp \
    obsluga_pliku.cpp \
    obsluga_programu.cpp \
    uzytkownicy.cpp \
    zasoby.cpp

HEADERS += \
    funkcje.hpp \
    loan.hpp \
    obsluga_pliku.hpp \
    obsluga_programu.hpp \
    uzytkownicy.hpp \
    zasoby.hpp

# Nowe ścieżki do plików nagłówkowych OpenSSL z instalacji MSYS2 (64-bit)
INCLUDEPATH += "C:/msys64/mingw64/include"

# Nowe ścieżki do plików bibliotek OpenSSL z instalacji MSYS2 (64-bit) oraz nazwy bibliotek
LIBS += -L"C:/msys64/mingw64/lib" -lcrypto -lssl
