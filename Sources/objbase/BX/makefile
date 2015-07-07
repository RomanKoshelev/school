TARGNAME = db
TMP      = tmp/
BIN      = bin/
#cc       = /usr/local/bin/gcc
cc       = g++295
PROBLEM  = PROBLEM_FORME
OPTS     = -march=i586 -g0 -O3 -D$(PROBLEM)


OBJS = 									$(TMP)UserAgent.o \
											$(TMP)URL.o \
											$(TMP)ServerDebug.o \
											$(TMP)ObjDriver_CASE.o \
											$(TMP)ObjDriver.o \
											$(TMP)OBServer_Interface.o \
											$(TMP)OBServer.o \
											$(TMP)OBD.o \
											$(TMP)MemoryManager.o \
											$(TMP)Lay_Stubs.o \
											$(TMP)Lay_ObjData.o \
											$(TMP)Lay_ObjController.o \
											$(TMP)FileDriver.o \
											$(TMP)EventMonitor.o \
											$(TMP)Interface_Dispatch.o \
											$(TMP)Interface_Auto.o \
											$(TMP)BX_Viewer.o \
											$(TMP)BX_VBN.o \
											$(TMP)BX_Utils.o \
											$(TMP)BX_User.o \
											$(TMP)BX_TimeStats.o \
											$(TMP)BX_Stats.o \
											$(TMP)BX_SiteProfile.o \
											$(TMP)BX_Site.o \
											$(TMP)BX_SingleObject.o \
											$(TMP)BX_Rating.o \
											$(TMP)BX_Main.o \
											$(TMP)BX_Language.o \
											$(TMP)BX_Keyword.o \
											$(TMP)BX_IPRecord.o \
											$(TMP)BX_Events.o \
											$(TMP)BX_Date.o \
											$(TMP)BX_Counter.o \
											$(TMP)BX_Concept.o \
											$(TMP)BX_BannerProfile.o \
											$(TMP)BX_Banner.o \
											$(TMP)BX_Admin.o

$(BIN)$(TARGNAME):					$(OBJS)
											@echo Linking ...
											time $(cc) $(OPTS) -o $@ $(OBJS) -lstdc++



$(TMP)BX_Admin.o: BX_Admin.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h BX_Errors.h \
		 BX_Concept.h BX_Site.h BX_User.h BX_Utils.h BX_Macros.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_Admin.cpp -o $@	

$(TMP)BX_Banner.o: BX_Banner.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h BX_Errors.h \
		 BX_Concept.h BX_Banner.h BX_VBN.h BX_Utils.h BX_Macros.h
		 time $(cc) $(OPTS) -c BX_Banner.cpp -o $@	

$(TMP)BX_BannerProfile.o: BX_BannerProfile.cpp BX.h Lay_ObjController.h \
		 ./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 BX_SingleObject.h BX_Errors.h BX_Concept.h BX_BannerProfile.h \
		 BX_VBN.h BX_Utils.h BX_Macros.h
		 time $(cc) $(OPTS) -c BX_BannerProfile.cpp -o $@	

$(TMP)BX_Concept.o: BX_Concept.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/OB_System.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ../bcc/ArgResCache.h ../bcc/OBServer_Interface.h ./../bcc/OBD.h \
		 ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h \
		 BX_Errors.h BX_Concept.h BX_Utils.h BX_Macros.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_Concept.cpp -o $@	

$(TMP)BX_Counter.o: BX_Counter.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/URL.h ./../bcc/OBD.h \
		 ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h \
		 BX_Errors.h BX_Concept.h BX_Events.h BX_Counter.h BX_IPRecord.h \
		 BX_Viewer.h BX_TimeStats.h BX_Utils.h BX_Macros.h
		 time $(cc) $(OPTS) -c BX_Counter.cpp -o $@	

$(TMP)BX_Date.o: BX_Date.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 BX_Date.h
		 time $(cc) $(OPTS) -c BX_Date.cpp -o $@	

$(TMP)BX_Events.o: BX_Events.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 BX_Errors.h BX_Events.h BX_Utils.h
		 time $(cc) $(OPTS) -c BX_Events.cpp -o $@	

$(TMP)BX_IPRecord.o: BX_IPRecord.cpp BX.h Lay_ObjController.h \
		 ./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 BX_SingleObject.h BX_Errors.h BX_Concept.h BX_IPRecord.h \
		 BX_TimeStats.h BX_Utils.h BX_Macros.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_IPRecord.cpp -o $@	

$(TMP)BX_Keyword.o: BX_Keyword.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/OB_System.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ../bcc/ArgResCache.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_Errors.h BX_Keyword.h BX_Utils.h \
		 BX_Macros.h
		 time $(cc) $(OPTS) -c BX_Keyword.cpp -o $@	

$(TMP)BX_Language.o: BX_Language.cpp BX.h Lay_ObjController.h \
		 ./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 BX_SingleObject.h BX_Errors.h BX_Language.h BX_Utils.h BX_Macros.h \
		 BX_Admin.h
		 time $(cc) $(OPTS) -c BX_Language.cpp -o $@	

$(TMP)BX_Main.o: BX_Main.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/OB_System.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ../bcc/ArgResCache.h ../bcc/OBServer_Interface.h ../bcc/URL.h \
		 ../bcc/UserAgent.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h
		 time $(cc) $(OPTS) -c BX_Main.cpp -o $@	

$(TMP)BX_Rating.o: BX_Rating.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h BX_Errors.h \
		 BX_Concept.h BX_TimeStats.h BX_Utils.h BX_Macros.h BX_Rating.h
		 time $(cc) $(OPTS) -c BX_Rating.cpp -o $@	

$(TMP)BX_SingleObject.o: BX_SingleObject.cpp BX.h Lay_ObjController.h \
		 ./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ../bcc/OBServer_Interface.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h BX_Errors.h \
		 BX_Language.h BX_Concept.h BX_Site.h BX_VBN.h BX_User.h BX_Events.h \
		 BX_Counter.h BX_Viewer.h BX_Utils.h BX_Macros.h BX_Stats.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_SingleObject.cpp -o $@	

$(TMP)BX_Site.o: BX_Site.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/URL.h ./../bcc/OBD.h \
		 ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h \
		 BX_Errors.h BX_Concept.h BX_Site.h BX_VBN.h BX_Events.h BX_IPRecord.h \
		 BX_Keyword.h BX_TimeStats.h BX_Utils.h BX_Macros.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_Site.cpp -o $@	

$(TMP)BX_SiteProfile.o: BX_SiteProfile.cpp BX.h Lay_ObjController.h \
		 ./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 BX_SingleObject.h BX_Errors.h BX_Concept.h BX_SiteProfile.h BX_VBN.h \
		 BX_Utils.h BX_Macros.h
		 time $(cc) $(OPTS) -c BX_SiteProfile.cpp -o $@	

$(TMP)BX_Stats.o: BX_Stats.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/URL.h ./../bcc/OBD.h \
		 ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h \
		 BX_Errors.h BX_Concept.h BX_TimeStats.h BX_Utils.h BX_Macros.h \
		 BX_Stats.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_Stats.cpp -o $@	

$(TMP)BX_TimeStats.o: BX_TimeStats.cpp BX.h Lay_ObjController.h \
		./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		BX_SingleObject.h BX_Errors.h BX_TimeStats.h BX_Date.h BX_Utils.h \
		BX_Macros.h BX_Stats.h BX_Admin.h
		time $(cc) $(OPTS) -c BX_TimeStats.cpp -o $@	

$(TMP)BX_User.o: BX_User.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/URL.h ./../bcc/OBD.h \
		 ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h \
		 BX_Errors.h BX_Concept.h BX_Site.h BX_SiteProfile.h BX_Banner.h \
		 BX_BannerProfile.h BX_VBN.h BX_User.h BX_Utils.h BX_Macros.h \
		 BX_Admin.h
		 time $(cc) $(OPTS) -c BX_User.cpp -o $@	

$(TMP)BX_Utils.o: BX_Utils.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h BX_Errors.h \
		 BX_Concept.h BX_Utils.h BX_Macros.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_Utils.cpp -o $@	

$(TMP)BX_VBN.o: BX_VBN.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ./../bcc/OBD.h ./../bcc/Object.h \
		 ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h BX_Errors.h \
		 BX_Concept.h BX_VBN.h BX_Utils.h BX_Macros.h BX_Admin.h
		 time $(cc) $(OPTS) -c BX_VBN.cpp -o $@	

$(TMP)BX_Viewer.o: BX_Viewer.cpp BX.h Lay_ObjController.h ./../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h \
		 ../bcc/EventMonitor.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/UserAgent.h ./../bcc/OBD.h \
		 ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h BX_SingleObject.h \
		 BX_Errors.h BX_Concept.h BX_Events.h BX_Counter.h BX_IPRecord.h \
		 BX_Viewer.h BX_Utils.h BX_Macros.h
		 time $(cc) $(OPTS) -c BX_Viewer.cpp -o $@	

$(TMP)Interface_Auto.o: Interface_Auto.cpp BX_Interface.h BX.h \
		Lay_ObjController.h ./../bcc/main.h ../bcc/config.h \
		../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h \
		../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h ../bcc/FileDriver.h \
		../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		../bcc/OBServer_Interface.h ./../bcc/OBD.h ./../bcc/Object.h \
		../bcc/SmartField.h Lay_ObjData.h BX_Errors.h BX_Language.h \
		BX_Concept.h BX_Site.h BX_SiteProfile.h BX_Banner.h \
		BX_BannerProfile.h BX_VBN.h BX_User.h BX_Events.h BX_Counter.h \
		BX_IPRecord.h BX_Viewer.h BX_TimeStats.h BX_Stats.h BX_Rating.h \
		BX_Admin.h Interface_Auto.h
		time $(cc) $(OPTS) -c Interface_Auto.cpp -o $@	

$(TMP)Interface_Dispatch.o: Interface_Dispatch.cpp BX.h Lay_ObjController.h \
		 ./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/OBServer_Interface.h \
		 ./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h \
		 Interface_Auto.h
		 time $(cc) $(OPTS) -c Interface_Dispatch.cpp -o $@	

$(TMP)Lay_ObjController.o: Lay_ObjController.cpp Lay_ObjController.h \
		./../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		./../bcc/OBD.h ./../bcc/Object.h ../bcc/SmartField.h Lay_ObjData.h
		time $(cc) $(OPTS) -c Lay_ObjController.cpp -o $@	

$(TMP)Lay_ObjData.o: Lay_ObjData.cpp ../bcc/main.h ../bcc/config.h \
		../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h \
		../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h ../bcc/FileDriver.h \
		../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h ../bcc/OBD.h \
		Lay_ObjData.h
		time $(cc) $(OPTS) -c Lay_ObjData.cpp -o $@	

$(TMP)Lay_Stubs.o: Lay_Stubs.cpp ./../bcc/main.h ../bcc/config.h \
		 ../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h \
		 ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h ../bcc/FileDriver.h \
		 ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h ./../bcc/OBD.h \
		 Lay_ObjData.h
		 time $(cc) $(OPTS) -c Lay_Stubs.cpp -o $@	

$(TMP)EventMonitor.o: ./../bcc/EventMonitor.cpp ../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h
		 time $(cc) $(OPTS) -c ./../bcc/EventMonitor.cpp -o $@	

$(TMP)FileDriver.o: ./../bcc/FileDriver.cpp ../bcc/main.h ../bcc/config.h \
		 ../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h \
		 ../bcc/Ptr.h ../bcc/string.h ../bcc/FileDriver.h ../bcc/File.h
		 time $(cc) $(OPTS) -c ./../bcc/FileDriver.cpp -o $@	

$(TMP)MemoryManager.o: ./../bcc/MemoryManager.cpp ../bcc/MemoryManager.h
		 time $(cc) $(OPTS) -c ./../bcc/MemoryManager.cpp -o $@	

$(TMP)OBD.o: ./../bcc/OBD.cpp ../bcc/main.h ../bcc/config.h \
		 ../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h \
		 ../bcc/Ptr.h ../bcc/string.h ../bcc/AVTree.h ../bcc/EventMonitor.h \
		 ../bcc/FileDriver.h ../bcc/File.h ../bcc/key_arr.h ../bcc/ObjDriver.h \
		 ../bcc/OBD.h
		 time $(cc) $(OPTS) -c ./../bcc/OBD.cpp -o $@	

$(TMP)OBServer.o: ./../bcc/OBServer.cpp ../bcc/config.h
		 time $(cc) $(OPTS) -c ./../bcc/OBServer.cpp -o $@	

$(TMP)OBServer_Interface.o: ./../bcc/OBServer_Interface.cpp ../bcc/main.h \
		 ../bcc/config.h ../bcc/MemoryManager.h ../bcc/ServerDebug.h \
		 ../bcc/Ptr.h ../bcc/string.h ../bcc/OBServer_Interface.h
		 time $(cc) $(OPTS) -c ./../bcc/OBServer_Interface.cpp -o $@	

$(TMP)ObjDriver.o: ./../bcc/ObjDriver.cpp ../bcc/ObjDriver_inc.h \
		 ../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h
		 time $(cc) $(OPTS) -c ./../bcc/ObjDriver.cpp -o $@	

$(TMP)ObjDriver_CASE.o: ./../bcc/ObjDriver_CASE.cpp ../bcc/ObjDriver_inc.h \
		 ../bcc/main.h ../bcc/config.h ../bcc/MemoryManager.h \
		 ../bcc/ServerDebug.h ../bcc/STATIC_FILE_ID.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/AVTree.h ../bcc/FileDriver.h ../bcc/File.h \
		 ../bcc/key_arr.h ../bcc/ObjDriver.h
		 time $(cc) $(OPTS) -c ./../bcc/ObjDriver_CASE.cpp -o $@	

$(TMP)ServerDebug.o: ./../bcc/ServerDebug.cpp ../bcc/main.h ../bcc/config.h \
		 ../bcc/MemoryManager.h ../bcc/ServerDebug.h
		 time $(cc) $(OPTS) -c ./../bcc/ServerDebug.cpp -o $@	

$(TMP)URL.o: ./../bcc/URL.cpp ../bcc/main.h ../bcc/config.h \
		 ../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/URL.h
		 time $(cc) $(OPTS) -c ./../bcc/URL.cpp -o $@	

$(TMP)UserAgent.o: ./../bcc/UserAgent.cpp ../bcc/main.h ../bcc/config.h \
		 ../bcc/MemoryManager.h ../bcc/ServerDebug.h ../bcc/Ptr.h \
		 ../bcc/string.h ../bcc/UserAgent.h
		 time $(cc) $(OPTS) -c ./../bcc/UserAgent.cpp -o $@	
