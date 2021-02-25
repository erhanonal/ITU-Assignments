#### Erhan Önal 150170713  ###############

import pyautogui
import time
import numpy as np
import cv2
import matplotlib.pyplot as plt
from scipy import ndimage

####################################################
###################   Part 1  ######################
def sobelFilter():

    
    mask_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], np.float32)
    mask_y = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]], np.float32)
    
    img = cv2.imread('test.png')
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img = cv2.GaussianBlur(img ,(3, 3), 0.5)
    conv_x =  ndimage.filters.convolve(img, mask_x)
    conv_y =  ndimage.filters.convolve(img, mask_y)
    
    result = np.hypot(conv_x , conv_y)
    result *= (255 / np.amax(result))
    
    result = result.astype('uint8')
    #result = result.astype('uint8')
    cv2.imwrite('sobel.png', result)
    return result
    

#####################################################
###################  Part 2  ########################
def cannyEdgeDetector():
    img = cv2.imread('test.png')
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    high, thresh_img = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    low = high * 0.5
    edges = cv2.Canny(img, low, high)
    
    contours, hierarchy = cv2.findContours(edges.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnt = cv2.drawContours(img, contours, -1, (0, 255, 0), 3)
    cv2.imwrite('canny.png', edges)
    return edges


#####################################################
#################  Part 3  ##########################

def minEigenvalueCornerDetector():
    
    
    img = cv2.imread('test.png')
    orig = cv2.imread('test.png')
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img = cv2.GaussianBlur(img ,(3, 3), 0.5).astype('float32')
    counter = 0
    corners = np.zeros_like(img)
    for i in range(0, img.shape[0]-3, 3):
        for j in range(0, img.shape[1]-3, 3):
            a = 0
            b = 0
            d = 0
            for k in range(3):
                for m in range (3):
                    x = (img[i + k + 1, j + m] - img[i + k -  1, j + m]) * 0.5
                    y = (img[i + k , j + m + 1] - img[i + k, j + m - 1]) * 0.5
                    a += x * x
                    b += x * y
                    d += y * y 
            lambda2 = ((a + d) - np.sqrt((a - d) * (a - d) + 4 * b * b)) * 0.5
            corners[i, j] = lambda2
            if lambda2 > 4000:
                radius = 2
                counter += 1  
                # Blue color in BGR
                color = (0, 255, 0)
                  
                # Line thickness of 2 px
                thickness = 2
                  
                # Using cv2.circle() method
                # Draw a circle with blue line borders of thickness of 2 px
                orig = cv2.circle(orig, (j, i), radius, color, thickness)        
   # print(counter)              
    cv2.imwrite('corners.png', orig)  
    return       
        


#####################################################
#################  Part 4   #########################
def playGame():
    while(True):
        myScreenshot = pyautogui.screenshot()
        img = np.array(myScreenshot)
    
        img = img[820:1200, 860:1150, :]
    
    
        
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        _, thresh_img = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY)
        thresh_img = cv2.GaussianBlur(thresh_img,(5,5),0)
        edges = cv2.Canny(thresh_img, 72.5, 145)
        correctTime = False
        if np.amax(edges[:, 50]) == 255:
            correctTime = True
        contours, hierarchy = cv2.findContours(edges.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        edgeCount = 0
        if len(contours) > 1:
            cv2.drawContours(img, contours, -1, (0, 255, 0), 3)
    
        for contour in contours:
            approx = cv2.approxPolyDP(contour, 0.01* cv2.arcLength(contour, True), True)
           # plt.imshow(thresh_img)
           # plt.title(len(approx))
           # plt.show()
           #print(len(approx))
            
            edgeCount = len(approx)
      # plt.imshow(img)
       # plt.title(edgeCount)
       # plt.show()
     #   plt.imshow(edges)
      #  plt.title(edgeCount)
        if correctTime:
            
            if edgeCount == 3 :
                pyautogui.keyDown('a')
              #  print('a')
                time.sleep(0.05)
                pyautogui.keyUp('a')
            elif edgeCount == 4 :
                pyautogui.keyDown('s')
               # print('s')
                time.sleep(0.05)
                pyautogui.keyUp('s')
            elif edgeCount == 10 :
                pyautogui.keyDown('d')
               # print('d')
                time.sleep(0.05)
                pyautogui.keyUp('d')
            elif edgeCount == 8 :
                pyautogui.keyDown('f')
               # print('f')
                time.sleep(0.05)
                pyautogui.keyUp('f')
        
    return


"""

time.sleep(5)

myScreenshot = pyautogui.screenshot()
myScreenshot.save('test.png')
"""
### Part 1######

#sobelFilter()

###################
#### Part 2 #######

#cannyEdgeDetector()

##### Part 3#######

#minEigenvalueCornerDetector()

#########################
######## Part 4 #########

playGame()

