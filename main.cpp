#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

double accuracy(vector<int> feature_set);
void forward_selection(int num_features);
string print_features(vector<int> feature_set);

int main() {
  // Receive Input BEGIN
  cout << "Welcome to Matthew O'Grady & Gary Ou Feature Selection Algorithm" << endl;

  cout << "Please enter total number of features: " << endl;
  int num_features = 0;
  cin >> num_features;

  cout << "\nType the number of the algorithm you want to run." << endl << endl;
  cout << "\t1. Forward Selection" << endl;
  cout << "\t2. Backward Elimination" << endl;
  cout << "\t3. Matthew & Gary's Special Algorithm." << endl;
  int alg_choice = 0;
  cin >> alg_choice;
  // Receive Input END

  if (alg_choice == 1) {
    // Run forward selection
    forward_selection(num_features);
  }
  else if (alg_choice == 2) {
    // Run backwards elimination
  }
  else {
    cout << "Matthew & Gary's Special Algorithm is not yet ready." << endl;
  }

  return 0;
}

void forward_selection(int num_features) {
  // Set of best features
  vector<int> best_set;
  // Best feature to add at current iteration
  int add_feature = 0;

  // Compute default rate (compute accuracy with empty feature set)
  // # instances most probable class / # total instances
  cout << "\nUsing no features and 'random' evaluation, I get an accuracy of FIXME%.\n\n";
  cout << "Beginning search.\n\n";

  double curr_best_accuracy = 0, curr_accuracy = 0, top_accuracy = 0;
  vector<int> curr_set;
  for (unsigned i = 0; i < num_features; ++i) {
    // Loop through feature set and observe accuracies of curr_set + jth feature
    curr_best_accuracy = 0;
    for (unsigned j = 1; j < num_features + 1; ++j) {
      // If j is already in feature set, continue to next iteration
      if (count(curr_set.begin(), curr_set.end(), j)) continue;
      // Compute accuracy of feature set + j
      curr_set.push_back(j);
      curr_accuracy = accuracy(curr_set);
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

// Accuracy placeholder
double accuracy(vector<int> feature_set) {
  double acc = rand() % 101;

  return acc;
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

