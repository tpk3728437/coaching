# Simple GNU make makefile
#
# Comment out / in the settings applicable to your system.

# Ogre 3d installed from source
OGRE_INCDIR=-I/usr/local/include
OGRE_RENDERER=/usr/local/lib/OGRE/RenderSystem_GL.so

SMC_DIR = ../smc


ifdef USEMOCKFLIP
  COINFLIPLOGIC = mockcoinfliplogic.o
else
  COINFLIPLOGIC = coinfliplogic.o
endif

ENGINE = engine
ENGINE_OBJS = $(ENGINE)/GameMachine_sm.o $(ENGINE)/HeadsOrTailsGame.o
UI_UTIL_OBJS = timer.o $(COINFLIPLOGIC)
UI_LOGIC_OBJS = controller.o doubleuplogic.o inputhandler.o oisinputmanager.o
UI_LAYER_OBJ = view.o graphics.o gamelayerresources.o backgroundlayer.o gamelayer.o doubleuplayer.o 
UI_OBJS = $(UI_UTIL_OBJS) $(UI_LOGIC_OBJS) $(UI_LAYER_OBJ)  tripleflip.o Gorilla.o
EXECUTABLE = tripleflip

# Ogre 3d installed from distro package
#OGRE_RENDERER=/usr/lib/OGRE/RenderSystem_GL.so

# Ogre 3d installed from 64bit distro package
#OGRE_RENDERER=/usr/lib64/OGRE/RenderSystem_GL.so

LIBS=-lOgreMain -lOIS
CXXFLAGS= -g -I. -I$(ENGINE) -I$(SMC_DIR)/lib/C++ $(OGRE_INCDIR) -DOGRE_RENDERER="\"$(OGRE_RENDERER)\""

vpath %.cpp .

.PHONY: $(EXECUTABLE) $(ENGINE) clean
all:	$(EXECUTABLE) 
	$(MAKE) --directory=apptests; done

test:
	cd apptests; $(MAKE) test; cd .. done
	cd $(ENGINE); $(MAKE) test; cd .. done

clean:
	-rm $(EXECUTABLE)
	-rm *.o 
	$(MAKE) --directory=apptests clean; done
	$(MAKE) --directory=$(ENGINE) clean; done

distclean: clean
	-rm $(ENGINE)/GameMachine_sm.*

$(ENGINE_OBJS): $(ENGINE)/*.cpp $(ENGINE)/*.h $(ENGINE)/*.sm
	$(MAKE) --directory=$(ENGINE); done

$(EXECUTABLE): $(ENGINE_OBJS) $(UI_OBJS) main.o 
	${CXX} $^ ${LIBS} -o $@
