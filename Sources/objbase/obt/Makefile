all: obt

obt: Lay_ObjData.cpp OBT_Main.cpp  OBT_Test.cpp
	egcs Lay_ObjData.cpp ./../bcc/FileDriver.cpp ./../bcc/ObjDriver.cpp ./../bcc/ServerDebug.cpp ./../bcc/OBD.cpp ./../bcc/EventMonitor.cpp OBT_Main.cpp  OBT_Test.cpp -o bcc -lstdc++ -DLAY_COMPILER_PROJECT

	