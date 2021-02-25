#Erhan Önal 150170713

import numpy as np 
import os
import cv2
import moviepy.editor as mpy
import matplotlib.pyplot as plt

background = cv2.imread('Malibu.jpg')

background_height = background.shape[0]
background_width = background.shape[1]
ratio = 360 / background_height

background = cv2.resize(background, (int(background_width * ratio), 360)) 

main_dir = 'cat'

############## Part 1 #####################################
print('Part 1 is processing')
images_list = []

for i in range(180):
    image = cv2.imread(main_dir + '/cat_%d.png' %i)
    image_g_channel = image[:, :, 1]
    image_r_channel = image[:, :, 0]
    
    foreground = np.logical_or(image_g_channel < 180, image_r_channel > 150) 
    nonzero_x, nonzero_y = np.nonzero(foreground)
    nonzero_cat_values = image[nonzero_x, nonzero_y, :]
    new_frame = background.copy()
    new_frame[nonzero_x, nonzero_y, :] = nonzero_cat_values
    new_frame = new_frame[:, :, [2, 1, 0]]
    images_list.append(new_frame)
        
clip = mpy.ImageSequenceClip(images_list, fps = 25)
audio = mpy.AudioFileClip('selfcontrol_part.wav').set_duration(clip.duration)
clip = clip.set_audio(audioclip = audio)
clip.write_videofile('part1_video.mp4', codec= 'libx264')

############################################################

################ Part 2 ##################################
print('Part 2 is processing')
images_list = []

for i in range(180):
    image = cv2.imread(main_dir + '/cat_%d.png' %i)
    image_g_channel = image[:, :, 1]
    image_r_channel = image[:, :, 0]
    
    foreground = np.logical_or(image_g_channel < 180, image_r_channel > 150) 
    nonzero_x, nonzero_y = np.nonzero(foreground)
    nonzero_cat_values = image[nonzero_x, nonzero_y, :]
    new_frame = background.copy()
    new_frame[nonzero_x, nonzero_y, :] = nonzero_cat_values
    new_frame[nonzero_x,  925 - nonzero_y, :] = nonzero_cat_values
    new_frame = new_frame[:, :, [2, 1, 0]]
    images_list.append(new_frame)
        
clip = mpy.ImageSequenceClip(images_list, fps = 25)
audio = mpy.AudioFileClip('selfcontrol_part.wav').set_duration(clip.duration)
clip = clip.set_audio(audioclip = audio)
clip.write_videofile('part2_video.mp4', codec= 'libx264')

##############################################

################ Part 3 ##################################
print('Part 3 is processing')

def transform(img, g):
    img = img.astype(int)
    img -= 100
    img[img < 0] = 0
    return img

images_list = []

for i in range(180):
    image = cv2.imread(main_dir + '/cat_%d.png' %i)
    image_g_channel = image[:, :, 1]
    image_r_channel = image[:, :, 0]
    
    foreground = np.logical_or(image_g_channel < 180, image_r_channel > 150) 
    nonzero_x, nonzero_y = np.nonzero(foreground)
    nonzero_cat_values = image[nonzero_x, nonzero_y, :]
    new_frame = background.copy()
    dark = np.copy(nonzero_cat_values)
    dark = transform(dark, 200)
    new_frame[nonzero_x, nonzero_y, :] = nonzero_cat_values
    new_frame[nonzero_x,  925 - nonzero_y, :] = dark
    new_frame = new_frame[:, :, [2, 1, 0]]
    images_list.append(new_frame)
        
clip = mpy.ImageSequenceClip(images_list, fps = 25)
audio = mpy.AudioFileClip('selfcontrol_part.wav').set_duration(clip.duration)
clip = clip.set_audio(audioclip = audio)
clip.write_videofile('part3_video.mp4', codec= 'libx264')

##############################################

################ Part 4 ##################################
print('Part 4 is processing')
def histogram(I):
    hist = np.zeros([256, 3], dtype=np.uint32)
    for i in range(3):
        for g in range(256):
            #hist[g,i] = np.sum(np.sum(I[...,i] == g, 0), 0)
            hist[g][i] = (I[...,i] == g).sum()
    hist = hist.astype(float)
    for j in range(3):
        hist[:, j] /= np.sum(hist[:, j])
    return hist

def get_cdf(h):

     cdf = np.cumsum(h, axis = 0)
     return cdf
     
def get_table(source_cdf, target_cdf):
    table = np.zeros([256, 3])
    for i in range(3):
        target = 0
        for image in range(255):
            while (target_cdf[target, i] < source_cdf[image, i] and target < 255) :
                target += 1
            table[image, i] = target
    return table

images_list = []

hist_list = []
for i in range(180):
    image = cv2.imread(main_dir + '/cat_%d.png' %i)
    image_g_channel = image[:, :, 1]
    image_r_channel = image[:, :, 0]
    
    foreground = np.logical_or(image_g_channel < 180, image_r_channel > 150) 
    nonzero_x, nonzero_y = np.nonzero(foreground)
    nonzero_cat_values = image[nonzero_x, nonzero_y, :]
    hist = histogram(nonzero_cat_values)
    
    hist_list.append(hist)
    

avg_hist = np.mean(hist_list, axis = 0)
avg_cdf = get_cdf(avg_hist)
 
target = cv2.imread('target.jpg')
target_hist = histogram(target)
target_cdf = get_cdf(target_hist)
    
table = get_table(avg_cdf, target_cdf)
   

for i in range(180):
    image = cv2.imread(main_dir + '/cat_%d.png' %i)
    image_g_channel = image[:, :, 1]
    image_r_channel = image[:, :, 2]
    
    foreground = np.logical_or(image_g_channel < 180, image_r_channel > 150) 
    nonzero_x, nonzero_y = np.nonzero(foreground)
    nonzero_cat_values = image[nonzero_x, nonzero_y, :]
    new_frame = background.copy()
    changed = np.zeros_like(nonzero_cat_values)
    for j in range(3):
        changed[:,j] = np.uint32(table[nonzero_cat_values[:, j], j])
    new_frame[nonzero_x, nonzero_y, :] = nonzero_cat_values
    new_frame[nonzero_x,  925 - nonzero_y, :] = changed
    new_frame = new_frame[:, :, [2, 1, 0]]
    images_list.append(new_frame)
        
clip = mpy.ImageSequenceClip(images_list, fps = 25)
audio = mpy.AudioFileClip('selfcontrol_part.wav').set_duration(clip.duration)
clip = clip.set_audio(audioclip = audio)
clip.write_videofile('part4_video.mp4', codec= 'libx264')

##############################################



################ Part 5 ##################################
print('Part 5 is processing')

def add_noise(img):
    noise = np.random.normal(0, 0.3, img.shape)
    img += noise
    return img


def histogram(I):
    hist = np.zeros([256, 3], dtype=np.uint32)
    for i in range(3):
        for g in range(256):
            #hist[g,i] = np.sum(np.sum(I[...,i] == g, 0), 0)
            hist[g][i] = (I[...,i] == g).sum()
    hist = hist.astype(float)
    for j in range(3):
       hist[:, j] /= np.sum(hist[:, j])
    return hist

def get_cdf(h):

     cdf = np.cumsum(h, axis = 0)
     return cdf
     
def get_table(source_cdf, target_cdf):
    table = np.zeros([256, 3])
    for i in range(3):
        target = 0
        for image in range(255):
            while (target_cdf[target, i] < source_cdf[image, i] and target < 255) :
                target += 1
            table[image, i] = target
    return table

images_list = []


for i in range(180):
    image = cv2.imread(main_dir + '/cat_%d.png' %i)
    image_g_channel = image[:, :, 1]
    image_r_channel = image[:, :, 2]
    
    foreground = np.logical_or(image_g_channel < 180, image_r_channel > 150) 
    nonzero_x, nonzero_y = np.nonzero(foreground)
    nonzero_cat_values = image[nonzero_x, nonzero_y, :]
    new_frame = background.copy()
    image_hist = histogram(nonzero_cat_values)
    noisy_image_hist = add_noise(image_hist)
    image_cdf = get_cdf(noisy_image_hist)
    
    target = cv2.imread('target.jpg')
    target_hist = histogram(target)
    target_cdf = get_cdf(target_hist)
    
    table = get_table(image_cdf, target_cdf)
    changed = np.zeros_like(nonzero_cat_values)
    for j in range(3):
        changed[:,j] = np.uint32(table[nonzero_cat_values[:, j], j])
    new_frame[nonzero_x, nonzero_y, :] = changed
    
    
    image_cdf = get_cdf(image_hist)
    
    target = cv2.imread('target.jpg')
    noisy_target_hist = add_noise(target_hist)
    target_cdf = get_cdf(noisy_target_hist)
    
    table = get_table(image_cdf, target_cdf)
    changed = np.zeros_like(nonzero_cat_values)
    for j in range(3):
        changed[:,j] = np.uint32(table[nonzero_cat_values[:, j], j])

    
    
    
    new_frame[nonzero_x,  925 - nonzero_y, :] = changed
    new_frame = new_frame[:, :, [2, 1, 0]]
    images_list.append(new_frame)
        
clip = mpy.ImageSequenceClip(images_list, fps = 25)
audio = mpy.AudioFileClip('selfcontrol_part.wav').set_duration(clip.duration)
clip = clip.set_audio(audioclip = audio)
clip.write_videofile('part5_video.mp4', codec= 'libx264')

##############################################


