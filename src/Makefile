OGRE_INCDIR=-I/usr/local/include

OGRE_PLUGIN_PATH = $(shell pkg-config --variable=plugindir OGRE)
OGRE_RENDERER=$(OGRE_PLUGIN_PATH)/RenderSystem_GL.so

SMC_DIR = ../smc

# flag to compile in 32-bit mode
#CFLAGS += -m32
ifdef USEMOCKFLIP
  COINFLIPLOGIC = mockcoinfliplogic.o resultreader.o
else
  COINFLIPLOGIC = coinfliplogic.o
endif

ENGINE = engine
ENGINE_OBJS = $(ENGINE)/headsortailsgame.o
UI_UTIL_OBJS = timer.o $(COINFLIPLOGIC)
UI_LOGIC_OBJS = controller.o inputhandler.o oisinputmanager.o
UI_LAYER_OBJ = view.o graphics.o layerfactory.o backgroundlayer.o gamelayer.o doubleuplayer.o graphicselement.o
UI_OBJS = $(UI_UTIL_OBJS) $(UI_LOGIC_OBJS) $(UI_LAYER_OBJ)  tripleflip.o gorilla.o
EXECUTABLE = tripleflip

LIBS=-lOgreMain -lOIS
CXXFLAGS= -g -I. -I$(ENGINE) -I$(SMC_DIR)/lib/C++ $(OGRE_INCDIR) -DOGRE_RENDERER="\"$(OGRE_RENDERER)\""

vpath %.cpp .

.PHONY: $(EXECUTABLE) $(ENGINE) clean
all:	$(EXECUTABLE) 
	$(MAKE) --directory=apptests; done

test:
	cd apptests; $(MAKE) test; cd .. done
	cd $(ENGINE); $(MAKE) test; cd .. done

valgrind:
	cd apptests; $(MAKE) valgrind; cd .. done
	cd $(ENGINE); $(MAKE) valgrind; cd .. done

clean:
	-rm $(EXECUTABLE)
	-rm *.o 
	$(MAKE) --directory=apptests clean; done
	$(MAKE) --directory=$(ENGINE) clean; done

distclean: clean

$(ENGINE_OBJS): $(ENGINE)/*.cpp $(ENGINE)/*.h
	$(MAKE) --directory=$(ENGINE); done

$(EXECUTABLE): $(ENGINE_OBJS) $(UI_OBJS) main.o 
	${CXX} $^ ${LIBS} -o $@
