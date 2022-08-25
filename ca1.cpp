#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define CONNECTIONS_FILE "people.txt"
#define SHOW_MSG "show_msg"
#define FAILED "failed"
#define SENT "sent"
#define TEXT ".txt"

using namespace std;

vector< vector<int> > make_connection_matrix(int &counter)
{
    ifstream file(CONNECTIONS_FILE);
    string str;
    vector<vector<int>> connections ;
    while (getline(file, str))
    {   
        counter ++;
    }
    vector<int> connect;
    for (int i=0;i<counter;i++)
        connect.push_back(0);
    for( int i=0;i<counter;i++)
        connections.push_back(connect);
    return connections;
}

void set_connections(vector< vector<int> > &connections)
{
    ifstream _file(CONNECTIONS_FILE);
    int line_counter=0;
    string file_contents;
    string str;
    while (getline(_file, str))
    {    
        file_contents += str;
        vector<int> connected;
        string buffer;
        stringstream stream(str);
        while (stream >> buffer) 
        {
            connected.push_back(stoi(buffer));
        }
        for(int j=1;j<connected.size();j++)
        {
            connections[line_counter][connected[j]] = 1;
            connections[connected[j]][line_counter] = 1;
        }
        line_counter++;
    }
}

void make_text_files(int counter)
{
    for( int i=0;i<counter;i++)
    {
        ofstream myfile;
        myfile. open (to_string(i) + TEXT);
    }
}

void show_msg(string input)
{
    ifstream _file(to_string(input[9]-48) + TEXT);
    string str;
    string file_contents;    
    while (getline(_file, str))
    {    
        file_contents += str;
        file_contents.push_back('\n');
    }
    cout<<file_contents;
}

void send_msg(string input)
{
    string msg;
    for(int i=3;i<input.size();i++)
        msg+=input[i];
    
    ofstream file(to_string(input[2]-48) + TEXT, ios::app);
    file << to_string(input[0]-48)  + msg + "\n";
    file.close();
    cout<<SENT<<endl;
}

int main()
{
    vector<vector<int>> connections ;
    int counter =0;
    connections = make_connection_matrix(counter);
    make_text_files(counter);
    set_connections(connections);
    string input;
    while(getline(cin,input))
    {
        if (input.substr(0,8) == SHOW_MSG && input.size()>9 )
        {
            show_msg(input);
            continue;
        }
        else if((int)input[0]-48 <=counter && (int)input[2]-48 <=counter)
        {
            if (connections[(int)input[0]-48][(int)input[2]-48] != 1)
            {
                cout <<FAILED<<endl;
                continue;
            }
            else if (connections[(int)input[0]-48][(int)input[2]-48] == 1)
            {
                send_msg(input);
                continue;
            }
        }
        cout<<FAILED<<endl;
    }
}