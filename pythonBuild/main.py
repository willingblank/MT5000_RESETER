import time
import os
from datetime import datetime
import pyscreeze
import pyautogui
import win32gui
import win32con
import winsound

from multiprocessing import Process

print("Hello this is MT5000 Build Process from willingblank.")


def buildProcess():
    with open(r'cmdLog.txt','w') as cmdlog:
        cmdlog.write(str(datetime.now()))
        cmdlog.write("\r\n")

    # Build App
    os.chdir("../1603s_app/libapp")
    os.system("make")   
    os.chdir("./out")
    os.system("xcopy /y libapp.a ..\..\ ")

    # Build App
    os.chdir("../../")
    os.system("build.bat>>../pythonBuild/cmdLog.txt")   

    os.chdir("../pythonBuild/")
    buildSuccessFlag = 0
    with open('cmdLog.txt') as cmdlog:
        cmdLog_data = cmdlog.readlines()
        for line in cmdLog_data:
            if "SUCCESS" in line:
                buildSuccessFlag = 1

    if(buildSuccessFlag == 0):  
        result = " Applicaiotn Build ERROR-S "
        print(">===========================<")
        print(f" \033[7;31m{result}\033[0m")
        print(">===========================<")

    if(buildSuccessFlag == 1): 
        os.chdir("../ATEL_SRC/tavor/Arbel/build")
        os.system("build_package.bat")

        result = " Applicaiotn Build SUCCESS "
        print(">===========================<")
        print(f" \033[7;32m{result}\033[0m")
        print(">===========================<")
    return buildSuccessFlag

   
# =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    
buildProcess()
os.chdir("../../../../pythonBuild")
os.system("adownload.exe -u -a -q -s 115200 ../ATEL_SRC/AbootTool/releasepackage/ASR1603_LTEGSM_DataModule_16MB.zip ")

print("Download Process End.")
#         FREQ(HZ) DURATION(MS)
winsound.Beep(440, 500) 


