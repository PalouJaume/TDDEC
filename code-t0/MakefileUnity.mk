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
UNITY_ADDITIONAL_LDFLAGS += -lpthread

SRC_DIRS = \
  $(PROJECT_HOME_DIR)/src/HomeAutomation\

TEST_SRC_DIRS = \
	$(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
	$(PROJECT_HOME_DIR)/unity\
	$(PROJECT_HOME_DIR)/unity/util\
  $(PROJECT_HOME_DIR)/unity/HomeAutomation\

MOCKS_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/mocks\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
  $(PROJECT_HOME_DIR)/include/HomeAutomation\
  $(PROJECT_HOME_DIR)/include/util\
  $(PROJECT_HOME_DIR)/mocks\

include $(UNITY_BUILD_HOME)/MakefileWorker.mk
