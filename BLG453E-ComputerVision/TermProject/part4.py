import numpy as np
import nibabel as nib
import matplotlib.pyplot as plt
import cv2 


def diceScore(guess, truth):
    intersect = np.logical_and(guess, truth)
    return 2 * np.count_nonzero(intersect) / (np.count_nonzero(guess) + np.count_nonzero(truth))


data = nib.load("V.nii")
truth = nib.load("V_seg.nii")
truth = truth.get_fdata()



arr = data.get_fdata()



########################   TASK 1  ###################################################

neighbours = [[0, 1],
              [0, -1],
              [1, 0],
              [-1, 0],
              [1, 1],
              [-1, 1],
              [1, -1],
              [-1, -1]]

results = np.zeros_like(arr)
threshold = 0.693
for i in range(arr.shape[2]):
#for i in range(50,52):
    
    img = arr[:,:,i]

    segMap = np.zeros(img.shape)
    seedPoints = [[10, 30],
                  [50, 60],
                  [120, 90],
                  [45, 65],
                  [38, 98],
                  [110, 65],
                  [150, 86],
                  [130, 10],
                  [60, 70],
                  [98, 63],
                  [58, 35],
                  [190, 70],
                  [60,30],
                  [40, 31],
                  [78, 13]]
    
    while len(seedPoints) > 0:
      #  print(len(seedPoints))
        nextPoints = []
        for point in seedPoints:
            for neg in neighbours:
                if 0 <= point[0] + neg[0] < img.shape[0] and 0 <= point[1] + neg[1] < img.shape[1]: 
                    if segMap[point[0] + neg[0], point[1] + neg[1]] == 0:
                        if img[point[0] + neg[0], point[1] + neg[1]] > threshold:
                            segMap[point[0] + neg[0], point[1] + neg[1]] = 1
                            nextPoints.append([point[0] + neg[0], point[1] + neg[1]])
        seedPoints = nextPoints.copy()                
    results[:,:,i]= segMap


score = diceScore(results, truth)
print("Task 1 Score: ", score)
results = nib.Nifti1Image(results, np.eye(4))
nib.save(results, "task_1")


########################   TASK 2  ###################################################



neighbours = [[0, 1],
              [0, -1],
              [1, 0],
              [-1, 0]]

results = np.zeros_like(arr)
for i in range(arr.shape[2]):
#for i in range(50,52):
    
    img = arr[:,:,i]

    segMap = np.zeros(img.shape)
    seedPoints = [[10, 30],
                  [50, 60],
                  [120, 90],
                  [45, 65],
                  [38, 98],
                  [110, 65],
                  [150, 86],
                  [130, 10],
                  [60, 70],
                  [98, 63],
                  [58, 35],
                  [190, 70],
                  [60,30],
                  [40, 31],
                  [78, 13]]
    
    while len(seedPoints) > 0:
      #  print(len(seedPoints))
        nextPoints = []
        for point in seedPoints:
            for neg in neighbours:
                if 0 <= point[0] + neg[0] < img.shape[0] and 0 <= point[1] + neg[1] < img.shape[1]: 
                    if segMap[point[0] + neg[0], point[1] + neg[1]] == 0:
                        if img[point[0] + neg[0], point[1] + neg[1]] > threshold:
                            segMap[point[0] + neg[0], point[1] + neg[1]] = 1
                            nextPoints.append([point[0] + neg[0], point[1] + neg[1]])
        seedPoints = nextPoints.copy()                
    results[:,:,i]= segMap


score = diceScore(results, truth)
print("Task 2 Score: ", score)
results = nib.Nifti1Image(results, np.eye(4))
nib.save(results, "task_2")


########################   TASK 3  ###################################################



neighbours = [[0, 0, 1],
              [0, 0, -1],
              [0, 1, 0],
              [0, -1, 0],
              [1, 0, 0],
              [-1, 0, 0],
              
              [0, 1, 1],
              [0, 1, -1],
              [0, -1, 1],
              [0, -1, -1],
              [1, 1, 0],
              [1, -1, 0],
              [-1, 1, 0],
              [-1, -1, 0],
              [1, 0, 1],
              [-1, 0, 1],
              [1, 0, -1],
              [-1, 0, -1],
              
              [1, 1, 1],
              [-1, 1, 1],
              [1, -1, 1],
              [1, 1, -1],
              [-1, -1, 1],
              [-1, 1, -1],
              [1, -1, -1],
              [-1, -1, -1]]
             

img = arr
    

segMap = np.zeros_like(img)
seedPoints = [[10, 30, 50],
              [70, 20, 50],
              [120, 90, 50],
              [100, 46, 50],
              [30, 15, 50]]

while len(seedPoints) > 0:
    nextPoints = []
    for point in seedPoints:
        for neg in neighbours:
            if 0 <= point[0] + neg[0] < img.shape[0] and 0 <= point[1] + neg[1] < img.shape[1] and 0 <= point[2] + neg[2] < img.shape[2]: 
                if segMap[point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]] == 0:
                    if img[point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]] > threshold:
                        segMap[point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]] = 1
                        nextPoints.append([point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]])
    seedPoints = nextPoints.copy()                
results = segMap


score = diceScore(results, truth)
print("Task 3 Score: ", score)
results = nib.Nifti1Image(results, np.eye(4))
nib.save(results, "task_3")




########################   TASK 4  ###################################################



neighbours = [[0, 0, 1],
              [0, 0, -1],
              [0, 1, 0],
              [0, -1, 0],
              [1, 0, 0],
              [-1, 0, 0]]
             

img = arr
    

segMap = np.zeros_like(img)
seedPoints = [[10, 30, 50],
              [70, 20, 50],
              [120, 90, 50],
              [100, 46, 50],
              [30, 15, 50]]

while len(seedPoints) > 0:
    nextPoints = []
    for point in seedPoints:
        for neg in neighbours:
            if 0 <= point[0] + neg[0] < img.shape[0] and 0 <= point[1] + neg[1] < img.shape[1] and 0 <= point[2] + neg[2] < img.shape[2]: 
                if segMap[point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]] == 0:
                    if img[point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]] > threshold:
                        segMap[point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]] = 1
                        nextPoints.append([point[0] + neg[0], point[1] + neg[1], point[2] + neg[2]])
    seedPoints = nextPoints.copy()                
results = segMap


score = diceScore(results, truth)
print("Task 4 Score: ", score)
results = nib.Nifti1Image(results, np.eye(4))
nib.save(results, "task_4")
