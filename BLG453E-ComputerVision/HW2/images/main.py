import dlib
from google.colab.patches import cv2_imshow
import cv2
import numpy as np

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
humans = []
animals = []
humanPoints = []
animalPoints = []
image = cv2.imread("deniro.jpg")
humans.append(image)
image = cv2.imread("kimbodnia.png")
humans.append(image)
image = cv2.imread("aydemirakbas.png")
humans.append(image)

image = cv2.imread("cat.jpg")
animals.append(image)
image = cv2.imread("gorilla.jpg")
animals.append(image)
image = cv2.imread("panda.jpg")
animals.append(image)

points = np.load("cat_landmarks.npy")
animalPoints.append(points)
points = np.load("gorilla_landmarks.npy")
animalPoints.append(points)
points = np.load("panda_landmarks.npy")
animalPoints.append(points)

green = (0, 255, 0)


for image in humans:
    
  gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
  rectangles = detector(gray)
  rectCount = 0
  for rect in rectangles:
    rectCount += 1

  if rectCount == 1:
    topLeft =  (int(rectangles[0].tl_corner().x), int( rectangles[0].tl_corner().y))
    bottomRight = (int(rectangles[0].br_corner().x), int(rectangles[0].br_corner().y))
    image_withRect = image.copy()
    image_withRect = cv2.rectangle(image_withRect, topLeft, bottomRight , color = green , thickness = 2) 
    cv2_imshow(image_withRect)
    points = predictor(gray, rectangles[0])
    humanPoints.append(points) 
  else:
    print("Wrong Rectangle Count")



animalsPointed = []
for image, points in zip(animals, animalPoints):
    image_withPoints = image.copy()
    for i in range(68):
     # point = (points.part(i).x, points.part(i).y)
      point = (points[i, 0], points[i, 1])
      image_withPoints = cv2.circle(image_withPoints, point, radius=2, color = green, thickness = -1)
    animalsPointed.append(image_withPoints)

humansPointed = []
for image, points in zip(humans, humanPoints):
    image_withPoints = image.copy()
    for i in range(68):
      point = (points.part(i).x, points.part(i).y)
     # point = (points[i, 0], points[i, 1])
      image_withPoints = cv2.circle(image_withPoints, point, radius=2, color = green, thickness = -1)
    humansPointed.append(image_withPoints)

animalsStack = np.hstack(animalsPointed)
humansStack = np.hstack(humansPointed)
cv2_imshow(np.vstack((animalsStack, humansStack)))