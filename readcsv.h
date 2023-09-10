#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<int>> readCSV(string filename) {
  vector<vector<int>> content;
  vector<int> row;
  string line, word;
  fstream file(filename, ios::in);
  if(file.is_open())
  {
    while(getline(file, line))
    {
      row.clear();

      stringstream str(line);

      while(getline(str, word, ','))
        row.push_back(stoi(word));
      content.push_back(row);
    }
  }
  else
    cout<<"Could not open the file\n";

  for (int i = 0; i < content.size(); i++)
  {
    for (int j = 0; j < content[i].size(); j++)
    {
      cout << content[i][j] << " ";
    }
    cout << "\n";
  }

  return content;
}
