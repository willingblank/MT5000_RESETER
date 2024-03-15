import time
import os
from datetime import datetime
import pyscreeze
import pyautogui
import win32gui
import win32con

print("Hello this is MT5000 Build Process from willingblank.")

def buildProcess():
    with open(r'cmdLog.txt','w') as cmdlog:
        cmdlog.write(str(datetime.now()))
        cmdlog.write("\r\n")

    # Build App
    os.chdir("../1603s_app/")
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


try:   
    hwnd = win32gui.FindWindow(None, 'QFlash_V6.9')
    left, top, right, bottom = win32gui.GetWindowRect(hwnd)
except Exception as error:
    print("QFlash is not Running Now.")
else:
    print("QFlash is Already Existed.")
    win32gui.PostMessage(hwnd, win32con.WM_CLOSE, 0, 0)
    time.sleep(1)
   
if(buildProcess()):
    os.chdir("../../../../pythonBuild")
    os.system("QflashLaunch.bat")
    time.sleep(2)
    hwnd = win32gui.FindWindow(None, 'QFlash_V6.9')
    left, top, right, bottom = win32gui.GetWindowRect(hwnd)
    x_record,y_record = pyautogui.position()
    pyautogui.click(left+250, top+550)
    pyautogui.moveTo(x_record, y_record)


detect_counter = 0
while 1:
    try:
        if(detect_counter%2 == 0):
            pyscreeze.locateOnScreen('passPic.jpg',confidence=0.9)
        else:
            pyscreeze.locateOnScreen('succeedPic.jpg',confidence=0.9)
    except Exception as error:
        print('|',end='',flush=True)
        detect_counter * detect_counter + 1
        time.sleep(1)
    else:
        print("Download SUCCESS.")
        win32gui.PostMessage(hwnd, win32con.WM_CLOSE, 0, 0)
        break



