#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = SandBox_Unity

#--- Inputs ----#
PROJECT_HOME_DIR = .
UNITY_HOME = ../code/unity.framework
CPP_PLATFORM = Gcc
UNITY_BUILD_HOME = ../code/unity.framework/extras/fixture/build

UNITY_CFLAGS += -DUNITY_OUTPUT_CHAR=UnityOutputCharSpy_OutputChar

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/LedDriver\
  $(PROJECT_HOME_DIR)/src/CircularBuffer\
  $(PROJECT_HOME_DIR)/src/HomeAutomation\
  $(PROJECT_HOME_DIR)/src/AlarmClock\
  $(PROJECT_HOME_DIR)/src/WhoIsHome\
  $(PROJECT_HOME_DIR)/src/Util\
  $(PROJECT_HOME_DIR)/src/IO\
  $(PROJECT_HOME_DIR)/src/devices\

TEST_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/unity\
	$(PROJECT_HOME_DIR)/unity/LedDriver\
  $(PROJECT_HOME_DIR)/unity/CircularBuffer\
  $(PROJECT_HOME_DIR)/unity/AlarmClock\
  $(PROJECT_HOME_DIR)/unity/WhoIsHome\
  $(PROJECT_HOME_DIR)/unity/Util\
  $(PROJECT_HOME_DIR)/unity/IO\
  $(PROJECT_HOME_DIR)/unity/devices\
	$(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
  ##$(PROJECT_HOME_DIR)/unity/HomeAutomation\

MOCKS_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/mocks\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
  $(PROJECT_HOME_DIR)/include/LedDriver\
  $(PROJECT_HOME_DIR)/include/CircularBuffer\
  $(PROJECT_HOME_DIR)/include/HomeAutomation\
  $(PROJECT_HOME_DIR)/include/AlarmClock\
  $(PROJECT_HOME_DIR)/include/WhoIsHome\
  $(PROJECT_HOME_DIR)/include/Util\
  $(PROJECT_HOME_DIR)/include/IO\
  $(PROJECT_HOME_DIR)/include/devices\
  $(PROJECT_HOME_DIR)/mocks\

include $(UNITY_BUILD_HOME)/MakefileWorker.mk
