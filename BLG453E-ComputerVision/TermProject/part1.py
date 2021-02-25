
import pyautogui
import time
import numpy as np
import cv2
import matplotlib.pyplot as plt

def playPart1():
    
    myScreenshot = pyautogui.screenshot()
    img = np.array(myScreenshot)
    
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    _, thresh_img = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
    thresh_img = cv2.GaussianBlur(thresh_img,(5,5),0)
    #edges = cv2.Canny(thresh_img, 72.5, 145)
    
    contours, hierarchy = cv2.findContours(thresh_img.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    edgeCount = 0
    
    #if len(contours) > 1:
        #cv2.drawContours(img, contours, -1, (0, 255, 0), 3)
    
    detectedEdges = []
    for contour in contours:
        approx = cv2.approxPolyDP(contour, 0.01* cv2.arcLength(contour, True), True)
        edgeCount = len(approx)
        if edgeCount == 4:
            detectedEdges.append(approx)
    
    
    circlesList = []        
    for item in detectedEdges:
            cv2.drawContours(img, [item], -1, (0, 255, 0), 3)
            xMax = np.amax(item[:, :, 0])
            xMin = np.amin(item[:, :, 0])
            yMax = np.amax(item[:, :, 1])
            yMin = np.amin(item[:, :, 1])
          #  print([xMax, xMin, yMax, yMin])
            dieImg = thresh_img[yMin:yMax, xMin:xMax]
     #       plt.imshow(dieImg)
      #      plt.show()
            
            circles = cv2.HoughCircles(dieImg, cv2.HOUGH_GRADIENT, 1, 20, param1 = 50, param2 = 30, minRadius = 1, maxRadius = 40) 
            circlesList.append(circles.shape[1])
    if np.argmax(circlesList) == 0:
        pyautogui.keyDown('d')
        time.sleep(0.05)
        pyautogui.keyUp('d')
    elif np.argmax(circlesList) == 1:
        pyautogui.keyDown('s')
        time.sleep(0.05)
        pyautogui.keyUp('s')
        
    elif np.argmax(circlesList) == 2:
        pyautogui.keyDown('a')
        time.sleep(0.05)
        pyautogui.keyUp('a')
    else:
        print("Something went wrong")
    return dieImg



def playPart2():
                
    myScreenshot = pyautogui.screenshot()
    img = np.array(myScreenshot)
    
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    _, thresh_img = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
    thresh_img = cv2.GaussianBlur(thresh_img,(5,5),0)
    #edges = cv2.Canny(thresh_img, 72.5, 145)
    
    contours, hierarchy = cv2.findContours(thresh_img.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    edgeCount = 0
    
    #if len(contours) > 1:
        #cv2.drawContours(img, contours, -1, (0, 255, 0), 3)
    
    data = []
    for contour in contours:
        approx = cv2.approxPolyDP(contour, 0.01* cv2.arcLength(contour, True), True)
        edgeCount = len(approx)
        if edgeCount == 4:
            data.append((cv2.contourArea(contour), approx))
            
    sortedData = sorted(data, key = lambda x: x[0])
    sortedData.reverse()
    
    
    circlesList = np.zeros(3)
    results = []  
    
    for i in range(3):
        item = sortedData[i][1];
        #cv2.drawContours(img, [item], -1, (0, 255, 0), 3)
        xMax = np.amax(item[:, :, 0])
        xMin = np.amin(item[:, :, 0])
        yMax = np.amax(item[:, :, 1])
        yMin = np.amin(item[:, :, 1])
      #  print([xMax, xMin, yMax, yMin])
        dieImg = thresh_img[yMin:yMax, xMin:xMax]
     
       
        mapping = np.float32([[0, 0], [283, 0], [283, 283], [0, 283]])
        
        item = np.float32(item).reshape([4,-1])
        sortedItem = np.sort(item,axis = 0)
        if sortedItem[0][1] < sortedItem[1][1]:
            tmp = sortedItem[0].copy()
            sortedItem[0] = sortedItem[1].copy()
            sortedItem[1] = tmp
        if sortedItem[2][1] < sortedItem[3][1]:
            tmp = sortedItem[2].copy()
            sortedItem[2] = sortedItem[3].copy()
            sortedItem[3] = tmp
            
        pointImage = img.copy()
        for val in item:
            cv2.circle(pointImage,(val[0],val[1]),5,(0,255,0),-1)
   #     plt.title((cv2.contourArea(contour)))
     #   plt.imshow(pointImage)
     #   plt.show()
        
       # print(mapping)
       # print(sortedItem)
        
     
        matrix = cv2.getPerspectiveTransform(item, mapping)
        result = cv2.warpPerspective(img, matrix, (283, 283))
      #  plt.imshow(result)
     #   plt.show()
        results.append(result)
        
        dieImg = result
        dieImg = cv2.cvtColor(dieImg, cv2.COLOR_BGR2GRAY)
        _, dieImg = cv2.threshold(dieImg, 200, 255, cv2.THRESH_BINARY)
        dieImg = cv2.GaussianBlur(dieImg,(5,5),0)
        
        
        circles = cv2.HoughCircles(dieImg, cv2.HOUGH_GRADIENT, 1, 20, param1 = 50, param2 = 15, minRadius = 1, maxRadius = 50)
        
        if item[0,0] > 1250:
            circlesList[0] = circles.shape[1]
        elif item[0,0] > 700:
            circlesList[1] = circles.shape[1]
        elif item[0,0] > 0:
            circlesList[2] = circles.shape[1]
        
    
    if np.argmax(circlesList) == 0:
        pyautogui.keyDown('d')
        time.sleep(0.05)
        pyautogui.keyUp('d')
    elif np.argmax(circlesList) == 1:
        pyautogui.keyDown('s')
        time.sleep(0.05)
        pyautogui.keyUp('s')
        
    elif np.argmax(circlesList) == 2:
        pyautogui.keyDown('a')
        time.sleep(0.05)
        pyautogui.keyUp('a')
    else:
        print("Something went wrong")
        
    return

while True:
    playPart2()
 
   







   