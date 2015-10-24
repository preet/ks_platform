INCLUDEPATH += $${PWD}

# ks
PATH_KS_PLATFORM = $${PWD}/ks/platform

count(PATH_SDL_LIB,0) {
    error("Error: PATH_SDL_LIB must be set to build ks_platform")
}
count(PATH_SDL_INCLUDE,0) {
    error("Error: PATH_SDL_INCLUDE must be set to build ks_platform")
}

HEADERS += \
    $${PATH_KS_PLATFORM}/KsPlatformOpts.hpp \
    $${PATH_KS_PLATFORM}/KsPlatformMain.hpp

SOURCES += \
    $${PATH_KS_PLATFORM}/sdl/KsGuiPlatformSDL.cpp

linux {
    !android {
        # sdl
        INCLUDEPATH += $${PATH_SDL_INCLUDE}
        DEFINES += _REENTRANT
        LIBS += -L$${PATH_SDL_LIB} -lSDL2
        QMAKE_RPATHDIR += $${PATH_SDL_LIB} # So that libs in /usr/lib aren't prioritized
    }
}

android {
    # sdl
    SOURCES += $${PATH_KS_PLATFORM}/sdl/SDL_android_main.c

    INCLUDEPATH += $${PATH_SDL_INCLUDE}
    DEFINES += KS_ENV_ANDROID_SDL
    DEFINES += _REENTRANT
    LIBS += -L$${PATH_SDL_LIB} -lSDL2
    LIBS += -lGLESv2 -lEGL
}
