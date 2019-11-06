//Erhan Önal 05.04.2018

#include <stdio.h>
#include <stdlib.h>

const int MAX_CAPACITY = 50; // Maximum size of the parking lot grid

/**
        Takes the input for the grid
        @param grid The array representing the parking lot
        @return grid_size The size of the parking lot
*/
int grid_input(int grid[][MAX_CAPACITY]) {
  int grid_size;
  do {
    printf("Size: ");
    scanf("%d", &grid_size);
    if (grid_size > MAX_CAPACITY) {
      printf("max size must be %d\n", MAX_CAPACITY);
    } else if (grid_size < 1) {
      printf("max size must be greater than 0");
    }
  } while (grid_size < 1 || grid_size > MAX_CAPACITY);

  return grid_size;
}

/**
        Fills the parking lot grid with 0's representing empty spaces
        @param grid The array representing the parking lot
*/
void array_filler(int grid[][MAX_CAPACITY]) {
  for (int i = 0; i < MAX_CAPACITY; i++) {
    for (int j = 0; j < MAX_CAPACITY; j++) {
      grid[i][j] = 0;
    }
  }
}

/**
        Takes the input for the car locations
        @param grid The array representing the parking lot
        @param car_locations The array containing the locations for cars
        @param grid_size The size of the parking lot
        @return car_number The number of cars
*/
int car_input(int grid[][MAX_CAPACITY], int car_locations[][2], int grid_size) {
  int car_number;
  printf("Cars: ");
  scanf("%d", &car_number);
  if (car_number >= grid_size * grid_size) {
    return car_number;
  }
  int input_number = car_number;
  for (int i = 0; i < input_number; i++) {
    int x, y;
    printf("Locations: ");
    scanf("%d %d", &x, &y);
    if (x < 1 || y < 1 || x > grid_size || y > grid_size) {
      car_number--;
    } else {
      grid[y - 1][x - 1] = 1;
      car_locations[i][0] = x;
      car_locations[i][1] = y;
    }
  }
  return car_number;
}

/**
        Finds the locations of empty spots in the parking lot in the order of
   their x and y coordinates respectively
        @param empty_locations The array containing the locations of empty spots
        @param grid The array representing the parking lot
        @param grid_size The size of the parking lot
        @return empty_location_number The number of empty spaces
*/
int empty_location_finder(int empty_locations[][2], int grid[][MAX_CAPACITY],
                          int grid_size) {
  int empty_location_number = 0;
  for (int i = 0; i < grid_size; i++) {
    for (int j = 0; j < grid_size; j++) {
      if (grid[j][i] == 0) {
        empty_locations[empty_location_number][0] = i + 1;
        empty_locations[empty_location_number][1] = j + 1;
        empty_location_number++;
      }
    }
  }
  return empty_location_number;
}

/**
        Calculates the Manhattan Distance between two points
        @param x1 X coordinate of point 1
        @param y1 Y coordinate of point 1
        @param x2 X coordinate of point 2
        @param y2 Y coordinate of point 2
        @return Manhattan distance between points
*/

int manhattan_distance(int x1, int y1, int x2, int y2) {
  int x_difference, y_difference;
  x_difference = x1 - x2 > 0 ? x1 - x2 : x2 - x1;
  y_difference = y1 - y2 > 0 ? y1 - y2 : y2 - y1;
  return x_difference + y_difference;
}

/**
        Finds the distance between an empty location and the nearest car for
   every empty location
        @param distance_to_cars Array containing the distance to the nearest car
   for every empty location
        @param empty_locations Array contaning the locations of empty points
        @param car_locations Array_containing the locations of cars
        @param empty_location_number The number of empty locations
        @param car_number The number of cars
*/

void distance_to_cars_finder(int distance_to_cars[], int empty_locations[][2],
                             int car_locations[][2], int empty_location_number,
                             int car_number) {
  for (int i = 0; i < empty_location_number; i++) {
    int minimum_distance = 2 * MAX_CAPACITY;
    for (int j = 0; j < car_number; j++) {
      if (manhattan_distance(empty_locations[i][0], empty_locations[i][1],
                             car_locations[j][0],
                             car_locations[j][1]) < minimum_distance) {
        minimum_distance =
            manhattan_distance(empty_locations[i][0], empty_locations[i][1],
                               car_locations[j][0], car_locations[j][1]);
        distance_to_cars[i] = minimum_distance;
      }
    }
  }
}
/**
        Finds the empty position with the greatest distance to the closest car
        @param distance_to_cars Array containing the distance to the nearest car
   for every empty location
        @param empty_location_number The number of empty locations
        @return max_position Array position of the empty point with the greatest
   distance to closest car
*/

//  Since we saved the empty positions in the array first by the order of their
//  X coordinates and
//  if they have the same X by their Y coordinates , if two or more empty
//  locations have the same distance
//  the function returns the on with smaller X coordinates or if X coordinates
//  are the same the location with smaller Y Coordinate

int max_pos_finder(int distance_to_cars[], int empty_location_number) {
  int max_position = 0;
  for (int i = 1; i < empty_location_number; i++) {
    if (distance_to_cars[i] > distance_to_cars[max_position]) {
      max_position = i;
    }
  }
  return max_position;
}

int main() {
  int grid[MAX_CAPACITY][MAX_CAPACITY];
  array_filler(grid);
  int grid_size = grid_input(grid);
  int car_locations[MAX_CAPACITY * MAX_CAPACITY][2];
  int car_number = car_input(grid, car_locations, grid_size);
  if (car_number >= grid_size * grid_size) {
    printf("Best Slot Found In: 0 0\n");
    return EXIT_SUCCESS;
  }
  if (car_number <= 0) {
    printf("Best Slot Found In: 1 1\n");
    return EXIT_SUCCESS;
  }
  int empty_locations[MAX_CAPACITY * MAX_CAPACITY - car_number][2];
  int empty_location_number =
      empty_location_finder(empty_locations, grid, grid_size);
  int distance_to_cars[empty_location_number];
  distance_to_cars_finder(distance_to_cars, empty_locations, car_locations,
                          empty_location_number, car_number);

  int best_position = max_pos_finder(distance_to_cars, empty_location_number);
  printf("Best Slot Found In: %d %d\n", empty_locations[best_position][0],
         empty_locations[best_position][1]);

  return EXIT_SUCCESS;
}
