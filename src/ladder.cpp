#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg){
    std::cout << "ERROR: " << word1 << " " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int str1_len = str1.length();
    int str2_len = str2.length();

    // create 2D Vector
    vector<vector<int>> d_path(str1_len + 1, vector<int>(str2_len + 1));

    // initialize 1st row and 1st column
    for(int i = 0; i <= str1_len; i++){
        d_path[i][0] = i;
    }

    for(int j = 0; j <= str2_len; j++){
        d_path[0][j] = j;
    }

    for(int i = 1; i <= str1_len; i++){
        for(int j = 1; j <= str2_len; j++){
            if(str1[i - 1] == str2[j - 1]){
                d_path[i][j] = d_path[i - 1][j - 1];
            }else{
                d_path[i][j] = 1 + min({d_path[i - 1][j - 1], d_path[i][j - 1], d_path[i - 1][j]});

            }
        }
    }
    return d_path[str1_len][str2_len];
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for(const string& word : word_list){
            if(is_adjacent(last_word, word)){
                if( visited.find(word) == visited.end() ){
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if(word == end_word){
                        return new_ladder;
                    }

                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream input_file(file_name);
    string word;

    while(getline(input_file, word)){
        word_list.insert(word);
    }

    input_file.close();
}

void print_word_ladder(const vector<string>& ladder){
    for(string word : ladder){
        cout << word << " ";
    }
}

void verify_word_ladder(){

}