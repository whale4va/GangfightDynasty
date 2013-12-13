EXECUTABLE = GangfightDynasty

INCLUDES = -I.. -I../Classes

SOURCES = ../src/Common/String.cpp \
        ../src/View/ViewEventResponder.cpp \
        ../src/View/ViewFrame.cpp \
        ../src/View/TextView.cpp \
        ../src/View/PictureView.cpp \
        ../src/View/PureColorBar.cpp \
        ../src/View/CommonButton.cpp \
        ../src/View/ButtonGroupPopupView.cpp \
        ../src/View/RichTextView.cpp \
        ../src/View/TabView.cpp \
        ../src/View/TabGroupView.cpp \
        main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp 

COCOS_ROOT = ../../..
#include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx_NoWerr.mk

SHAREDLIBS += -lcocos2d
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
	
run:
	./bin/debug/$(EXECUTABLE)
