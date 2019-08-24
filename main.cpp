#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;
vector<string> GetFileList(){
    struct dirent *ptr;
    DIR *dir;
    string PATH = "./";
    dir=opendir(PATH.c_str());
    vector <string> files;
    cout << "file list: "<< endl;
    while((ptr=readdir(dir))!=NULL)
    {

        //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
            continue;
        //cout << ptr->d_name << endl;
        files.push_back(ptr->d_name);
    }

    for (int i = 0; i < files.size(); ++i)
    {
        cout << files[i] << endl;
    }
    closedir(dir);
    return  files;
}
int main(int argc, char* argv[]) {
    ifstream in;
    ofstream out;
    string ss;

    vector<string> files = GetFileList();
    for(auto n:files){
        in.open(n);
        if(in.fail()) cerr<<"open in file fail"<<endl;

        string outfile = "new_"+n;
        out.open(outfile,ios::out);
        if(out.fail()) cerr<<"open out file fail"<<endl;
        cout<<"reading from "<<n<<endl;
        //skip trace's metadata
        for(int i=0; i<33; i++) getline(in,ss);
        while(getline(in,ss)){
            if(ss.size()==0){
                //begin format file
                //skip file's metadata
                for(int i=0; i<12; i++) getline(in,ss);
                continue;
            }
            if(ss.substr(0,2) == "SV" || ss.substr(0,1) == "V") continue;
            if(ss.substr(0,1) == "A") continue;
            out<<ss.substr(0,10)<<"\n";
        }
        in.close();
        out.close();
    }
    return 0;
}