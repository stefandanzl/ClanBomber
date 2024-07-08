noinst_LIBRARIES = libcbe.a

libcbe_a_CXXFLAGS = \
	$(BOOST_CPPFLAGS) \
	$(OPENAL_CPPFLAGS) \
	$(PTHREAD_CFLAGS) \
	$(SDL_CFLAGS) \
	$(SDL_GFX_CFLAGS) \
	$(SDL_IMAGE_CFLAGS) \
	$(SDL_MIXER_CFLAGS) \
	$(SDL_TTF_CFLAGS)

libcbe_a_SOURCES = \
	Font.hpp \
	Surface.hpp \
	AudioSimple.hpp \
	AudioBuffer.hpp \
	SDL/AudioBufferSDL.cpp \
	SDL/AudioBufferSDL.hpp \
	SDL/AudioSimpleSDL.cpp \
	SDL/AudioSimpleSDL.hpp \
	SDL/FactoriesSDL.hpp \
	SDL/FontSDL.cpp \
	SDL/FontSDL.hpp \
	SDL/SurfaceSDL.cpp \
	SDL/SurfaceSDL.hpp \
	SDL/GraphicsSDL.cpp \
	SDL/GraphicsSDL.hpp \
	SDL/ScreenSDL.cpp \
	SDL/ScreenSDL.hpp \
	SDL/SurfaceMapSDL.cpp \
	SDL/SurfaceMapSDL.hpp \
	Factories.hpp \
	PluginManager.hpp \
	PluginManager.cpp \
	Graphics.hpp \
	Screen.hpp \
	SurfaceMap.hpp \
	Exceptions.cpp \
	Exceptions.hpp \
	SurfaceCollection.cpp \
	SurfaceCollection.hpp

if ENABLE_OPENAL
libcbe_a_SOURCES += \
	OAL/AudioBufferOAL.cpp \
	OAL/AudioBufferOAL.hpp \
	OAL/AudioSimpleOAL.cpp \
	OAL/AudioSimpleOAL.hpp \
	OAL/FactoriesOAL.hpp
endif
