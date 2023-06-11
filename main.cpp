#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

double accuracy();
void forward_selection(int num_features);

int main() {
  // Receive Input BEGIN
  cout << "Welcome to Matthew O'Grady & Gary Ou Feature Selection Algorithm" << endl;

  cout << "Please enter total number of features: " << endl;
  int num_features = 0;
  cin >> num_features;

  cout << "Type the number of the algorithm you want to run." << endl << endl;
  cout << "1. Forward Selection" << endl;
  cout << "2. Backward Elimination" << endl;
  cout << "3. Matthew & Gary's Special Algorithm." << endl;
  int alg_choice = 0;
  cin >> alg_choice;
  // Receive Input END

  return 0;
}

void forward_selection(int num_features) {
  // Set of best features
  vector<int> feature_set;
  // Best feature to add at current iteration
  int add_feature

  double best_accuracy = 0;
  double curr_accuracy = 0;
  for (unsigned i = 1; i < num_features + 1; ++i) {
    // Compute accuracy of each feature
    curr_accuracy = accuracy();
    // Check if this is 
    if ()
  }
}

// Accuracy placeholder
double accuracy() {
  double acc = rand() % 101;

  return acc;
}

