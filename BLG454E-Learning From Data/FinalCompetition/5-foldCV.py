
import pandas as pd
from sklearn.model_selection import KFold
import numpy as np
from sklearn.metrics import mean_squared_error


from sklearn.neighbors import NearestNeighbors

def weightedNeighbourSingularTest(data_t0, data_t1, neighbourCount):
    kf = KFold(n_splits=5)
    prediction_all = np.zeros_like(data_t1)
    for trainIndex, testIndex in kf.split(data_t0):
        train_t0, test_t0 = data_t0[trainIndex], data_t0[testIndex] #Split Data into train and test sets
        train_t1, test_t1 = data_t1[trainIndex], data_t1[testIndex]
        train_t0_single = np.transpose(train_t0) # Use features as rows and subjects as columns
        train_t1_single = np.transpose(train_t1)
        test_t0_single = np.transpose(test_t0) 
        
        prediction = np.zeros_like(test_t0)
        for i in range(train_t0_single.shape[0]): #Loop through each feature
            nbrs = NearestNeighbors(n_neighbors= neighbourCount, algorithm='ball_tree').fit(train_t0_single[i].reshape(-1,1))
            distances, indices = nbrs.kneighbors(test_t0_single[i].reshape(-1,1))# Calculate the distances and indices of K closest neighbours of test subjects and train subjects in t0 
            distances = np.ones_like(distances)* 0.7 - distances # Set distances to (0.7 - d). Neighbours with low distance get larger values and vice versa  
            mul = np.multiply(distances, train_t1_single[i,indices])  # Use the changed distances as weights and multiply the corresponding t1 of the neighbours 
            pred = np.divide(np.mean(mul,axis =1),np.mean(distances, axis = 1)) #Take the mean of the weighted t1's and divide by the mean of distances to normalize 
            prediction[:,i] = pred.reshape(-1) #This is the prediction for this feature acroos all test subjects
        nanLocations = np.isnan(prediction)
        prediction[nanLocations] = 0   # Set nan locations to 0
        prediction_all[testIndex] = prediction # Put all predictions for each CV fold into prediction_all
    error = mean_squared_error(data_t1, prediction_all)
    return error


train_t0 = pd.read_csv("train_t0.csv", sep=',')
train_t1 = pd.read_csv("train_t1.csv", sep=',')

test_t0 = pd.read_csv("test_t0.csv", sep=',')

train_t0 = train_t0.drop(columns=['ID'])
train_t1 = train_t1.drop(columns=['ID'])
test_t0 = test_t0.drop(columns=['ID'])

train_t0_np = train_t0.to_numpy()
train_t1_np = train_t1.to_numpy()
test_t0_np = test_t0.to_numpy()
      
neighbourCount = 55

error_weightedNeighbourSingular = weightedNeighbourSingularTest(train_t0_np, train_t1_np,neighbourCount)





