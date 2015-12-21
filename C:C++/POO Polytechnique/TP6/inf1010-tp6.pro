QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test

RESOURCES += \
    images.qrc

HEADERS += \
    Aliment.h \
    Cellulaire.h \
    Chauffage.h \
    enumTypes.h \
    Frigo.h \
    gps.h \
    mainwindow.h \
    Maison.h \
    memeAliment.h \
    Message.h \
    MessageEnvoiePersonne.h \
    Meteo.h \
    ObjetConnecte.h \
    Observable.h \
    Observateur.h \
    Personne.h \
    RestrictionAlimentaire.h \
    Routeur.h \
    voiture.h

SOURCES += \
    Aliment.cpp \
    Cellulaire.cpp \
    Chauffage.cpp \
    gps.cpp \
    main.cpp \
    mainwindow.cpp \
    Maison.cpp \
    memeAliment.cpp \
    Message.cpp \
    MessageEnvoiePersonne.cpp \
    Meteo.cpp \
    ObjetConnecte.cpp \
    Observable.cpp \
    Personne.cpp \
    RestrictionAlimentaire.cpp \
    Routeur.cpp
