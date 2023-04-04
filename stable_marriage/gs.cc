#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

const bool DEBUG = false;

int get_res_index(int n, int i, int j) { return (n * i) + j; }

// companies numbered [0, n-1], applicants numbered [0, n-1].
// 0 is best choice, n-1 is worst choice
map<int, int> match_couples(int n, const int* company_prefs,
                            const int* applicant_prefs) {
  // Create and compute inverted applicants preference list.
  int* applicants_inv = (int*)malloc(n * n * sizeof(int));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      applicants_inv[get_res_index(
          n, i, applicant_prefs[get_res_index(n, i, j)])] = j;
    }
  }

  // Queue of free companies (initially [0, n-1])
  queue<int> free_companies;
  for (int i = 0; i < n; i++) free_companies.push(i);

  // Currently assigned applicants for each company [0, n-1]
  // (if an element is -1, it is unassigned)
  int* companies_assn = (int*)malloc(n * sizeof(int));
  int* applicants_assn = (int*)malloc(n * sizeof(int));
  memset(companies_assn, -1, n * sizeof(int));
  memset(applicants_assn, -1, n * sizeof(int));

  // Algorithm terminates when all unmatched companies are matched
  // (iff free_companies is empty)
  while (!free_companies.empty()) {
    // Create tentative pairing for each unmatched company.
    int company_id = free_companies.front();
    free_companies.pop();

    // Advance to next company assignment.
    companies_assn[company_id]++;

    // Get the first applicant for which company_id has not proposed yet
    // company_prefs[company_id][companies_assn[company_id]];
    int applicant_id =
        company_prefs[get_res_index(n, company_id, companies_assn[company_id])];

    if (DEBUG) cerr << company_id << " tries " << applicant_id << endl;

    if (applicants_assn[applicant_id] == -1) {
      // applicant_id is free! Assign this company to this applicant.
      applicants_assn[applicant_id] = company_id;
      if (DEBUG)
        cerr << company_id << " is assigned (free) to " << applicant_id << endl;
    } else if (applicants_inv[get_res_index(n, applicant_id, company_id)] <
               applicants_inv[get_res_index(n, applicant_id,
                                            applicants_assn[applicant_id])]) {
      // applicant_id prefers company_id to its old company. Elope.
      free_companies.push(applicants_assn[applicant_id]);
      applicants_assn[applicant_id] = company_id;
      if (DEBUG)
        cerr << company_id << " is assigned (better) to " << applicant_id
             << endl;
    } else {
      free_companies.push(company_id);
      if (DEBUG)
        cerr << company_id << " is NOT assigned to " << applicant_id << endl;
    }
  }

  map<int, int> sol;

  for (int i = 0; i < n; i++) {
    sol[i] = company_prefs[get_res_index(n, i, companies_assn[i])];
  }

  free(companies_assn);
  free(applicants_assn);
  free(applicants_inv);

  return sol;
}

int main(int argc, char** argv) {
  int n;

  cout << "How many company-applicant pairs?" << endl;
  cin >> n;

  int* company_prefs = static_cast<int*>(malloc(n * n * sizeof(int)));
  int* applicant_prefs = static_cast<int*>(malloc(n * n * sizeof(int)));

  int input;

  for (int i = 0; i < n; i++) {
    cout << "Company " << i
         << ", enter preferred applicants, separated by spaces, in descending "
            "order:"
         << endl;
    for (int j = 0; j < n; j++) {
      cin >> input;
      company_prefs[get_res_index(n, i, j)] = input;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << "Applicant " << i
         << ", enter preferred companies, separated by spaces, in descending "
            "order:"
         << endl;
    for (int j = 0; j < n; j++) {
      cin >> input;
      applicant_prefs[get_res_index(n, i, j)] = input;
    }
  }

  map<int, int> couples = match_couples(n, company_prefs, applicant_prefs);

  free(company_prefs);
  free(applicant_prefs);

  cout << endl << "Best company-applicant matchings are: " << endl;
  for (const auto& pair : couples) {
    cout << pair.first << "-" << pair.second << endl;
  }

  return EXIT_SUCCESS;
}