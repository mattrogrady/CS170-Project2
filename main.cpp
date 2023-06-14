#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct instance {
  int classification;
  vector<double> features; 
};

void forward_selection(vector<instance> dataset);
void backward_elimination(vector<instance> dataset);
double validator(vector<int> feature_set, vector<instance> dataset);
bool test(int test_index, vector<instance> dataset, vector<int> feature_set);
double e_distance(instance test, instance train, vector<int> feature_set);
string print_features(vector<int> feature_set);
vector<instance> get_data(string filename);

int main() {
  // Receive Input BEGIN
  cout << "Welcome to Matthew O'Grady & Gary Ou Feature Selection Algorithm" << endl;

  cout << "Type the number of the dataset you want to use." << endl;
  cout << "\t1. Small Dataset" << endl;
  cout << "\t2. Large Dataset" << endl;
  cout << "\t3. Small Personal Dataset" << endl;
  cout << "\t4. Large Personal Dataset" << endl;
  int data_choice = 0;
  cin >> data_choice;
  string filename = "";
  if (data_choice == 1) {
    filename = "small-test-dataset.txt";
  }
  else if (data_choice == 2) {
    filename = "large-test-dataset-1.txt";
  }
  else if (data_choice == 3) {
    filename = "CS170_Spring_2023_Small_data__80.txt";
  }
  else {
    filename = "CS170_Spring_2023_Large_data__80.txt";
  }
  vector<instance> dataset = get_data(filename);

  cout << "\nType the number of the algorithm you want to run." << endl << endl;
  cout << "\t1. Forward Selection" << endl;
  cout << "\t2. Backward Elimination" << endl;
  cout << "\t3. Matthew & Gary's Special Algorithm." << endl;
  int alg_choice = 0;
  cin >> alg_choice;
  // Receive Input END

  if (alg_choice == 1) {
    // Run forward selection
    forward_selection(dataset);
  }
  else if (alg_choice == 2) {
    // Run backwards elimination
    backward_elimination(dataset);
  }
  else {
    cout << "Matthew & Gary's Special Algorithm is not yet ready." << endl;
  }

  return 0;
}

void forward_selection(vector<instance> dataset) {
  // Set of best features
  vector<int> best_set;
  // Best feature to add at current iteration
  int add_feature = 0;
  // Accuracies that we need to track
  double curr_best_accuracy = 0, curr_accuracy = 0, top_accuracy = 0;

  // Compute default rate (compute accuracy with empty feature set)
  // # instances most probable class / # total instances
  int ones = 0;
  for (unsigned i = 0; i < dataset.size(); ++i) {
    if (dataset.at(i).classification == 1) ones++;
  }
  if (ones >= (dataset.size() / 2)) curr_best_accuracy = 100.0 * ones / dataset.size();
  else curr_best_accuracy = 100.0 * (dataset.size() - ones) / dataset.size();
  cout << "\nUsing no features and 'random' evaluation, I get an accuracy of " << curr_best_accuracy << "%.\n\n";
  cout << "Beginning search.\n\n";

  vector<int> curr_set;
  int num_features = dataset.at(0).features.size();
  for (unsigned i = 0; i < num_features; ++i) {
    // Loop through feature set and observe accuracies of curr_set + jth feature
    curr_best_accuracy = 0;
    for (unsigned j = 1; j < num_features + 1; ++j) {
      // If j is already in feature set, continue to next iteration
      if (count(curr_set.begin(), curr_set.end(), j)) continue;
      // Compute accuracy of feature set + j
      curr_set.push_back(j);
      curr_accuracy = validator(curr_set, dataset);
      cout << "\tUsing feature(s) " << print_features(curr_set) << " accuracy is " << curr_accuracy << "%\n";
      // If this our best seen accuracy for this loop, save it
      if (curr_best_accuracy < curr_accuracy) {
        curr_best_accuracy = curr_accuracy;
        add_feature = j;
      }
      // Return set to start form
      curr_set.pop_back();
    }
    // Add best new feature seen for this iteration
    curr_set.push_back(add_feature);
    // If this is our best performing set in all iterations so far, save it
    if (top_accuracy < curr_best_accuracy) {
      best_set = curr_set;
      top_accuracy = curr_best_accuracy;
    }

    // Print best set for this iteration
    cout << "\nFeature set " << print_features(curr_set) << " was best, accuracy is " << curr_best_accuracy << "%\n\n";
  }

  // Algorithm complete, print best feature subset
  cout << "Finished search!! The best feature subset is " << print_features(best_set) << ", which has an accuracy of " << top_accuracy << "%\n";
}

void backward_elimination(vector<instance> dataset){
  vector<int> best_set;   //vector recording the best set found
  vector<int> curr_set;   //vector recording current set being evaluated
  double curr_best_accuracy = 0.01;
  double temp_accuracy = 0;
  double curr_feature = 0;
  double curr_accuracy;


  // Compute default rate (compute accuracy with empty feature set)
  // # instances most probable class / # total instances
  int ones = 0;
  for (unsigned i = 0; i < dataset.size(); ++i) {
    if (dataset.at(i).classification == 1) ones++;
  }
  if (ones >= (dataset.size() / 2)) curr_best_accuracy = 100.0 * ones / dataset.size();
  else curr_best_accuracy = 100.0 * (dataset.size() - ones) / dataset.size();
  cout << "\nUsing no features and 'random' evaluation, I get an accuracy of " << curr_best_accuracy << "%.\n\n";
  cout << "Beginning search.\n\n";
  int num_features = dataset.at(0).features.size();
  for(int i = 1; i < num_features + 1; i++){
    best_set.push_back(i); //populate vector with features
  }

  curr_best_accuracy = 0.01;
  while(temp_accuracy < curr_best_accuracy){ 
    temp_accuracy = curr_best_accuracy;
    for(int i = 0; i < best_set.size(); i++){ //loop through all features 
      curr_set = best_set;
      curr_set.erase(curr_set.begin() + i); //remove the feature at i, creating a new feature subset
      curr_accuracy = validator(curr_set, dataset); //assign a random value for now
      cout << "\tUsing feature(s) " << print_features(curr_set) << " accuracy is " << curr_accuracy << "%\n"; 

      if(curr_accuracy > curr_best_accuracy){ //if we find a feature with higher accuracy, record it as new best feature
        curr_best_accuracy = curr_accuracy;
        curr_feature = i;
      }
    }
    if(temp_accuracy == curr_best_accuracy){ // when our accuracy stops improving, 
      cout << endl;
      break;
    }
    best_set.erase(best_set.begin() + curr_feature); //delete feature not in best feature 

    cout << "\nFeature set " << print_features(best_set) << " was best, accuracy is " << curr_best_accuracy << "%\n\n";
  }

  cout << "Finished search!! The best feature subset is " << print_features(best_set) << ", which has an accuracy of " << curr_best_accuracy << "%\n";
}

// Leave-one-out validation function
double validator(vector<int> feature_set, vector<instance> dataset) {
  int correct = 0;

  // Loop through dataset, selecting an instance and classifying it relative to the rest of the dataset
  for (unsigned i = 0; i < dataset.size(); ++i) {
    if (test(i, dataset, feature_set)) correct++;
  }

  return 100.0 * correct / dataset.size();
}

// Runs KNN with k=1 for test index, returns true if classification is correct and false otherwise
bool test(int test_index, vector<instance> dataset, vector<int> feature_set) {
  int closest_index = -1;
  double curr_distance = 9999999;
  double smallest_distance = 99999999;

  for (unsigned i = 0; i < dataset.size(); ++i) {
    if (i == test_index) {
      // Skip because this is the instance we are using as test data
      continue;
    }
    // Calculate distance between test and training instance, save if smallest distance so far
    curr_distance = e_distance(dataset.at(test_index), dataset.at(i), feature_set);
    if (curr_distance < smallest_distance) {
      smallest_distance = curr_distance;
      closest_index = i;
    }
  }

  // We have now found our classification via closest neighbor, check if it is correct
  if (dataset.at(closest_index).classification == dataset.at(test_index).classification) {
    return true;
  }
  else {
    return false;
  }
}

// Returns the euclidean distance between two instances with respect to the feature_set
double e_distance(instance test, instance train, vector<int> feature_set) {
  double distance = 0;
  for (unsigned i = 0; i < feature_set.size(); ++i) {
    distance += pow(train.features.at(feature_set.at(i) - 1) - test.features.at(feature_set.at(i) - 1), 2);
  }
  return sqrt(distance);
}


// Print a set of features to output
string print_features(vector<int> feature_set) {
  string stmt = "{";
  for (unsigned i = 0; i < feature_set.size(); ++i) {
    if (i == feature_set.size()-1) {
      stmt += (to_string(feature_set.at(i)) + "}");
    }
    else {
      stmt += (to_string(feature_set.at(i)) + ",");
    }
  }
  return stmt;
}

// Read data from a file and separate by classification and features
vector<instance> get_data(string filename) {
  ifstream input(filename);
  string line = "";
  vector<instance> data;

  double i;
  while (getline(input, line)) {
    instance curr;
    istringstream ss(line);
    ss >> i;
    curr.classification = i;
    while (ss >> i) curr.features.push_back(i);
    data.push_back(curr);
  }

  input.close();
  return data;
}
