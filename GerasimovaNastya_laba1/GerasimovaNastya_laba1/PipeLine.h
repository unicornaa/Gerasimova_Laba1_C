#pragma once
#include <string>
#include <fstream>


class PipeLine
{
    int id;
    double length;
    int diameter;
public:
    //static void Reset();
    static int PipeID;
    std::string namePipe;
    
    bool InRepairs;
    void loadPipe(std::ifstream& fin);
    void savePipe(std::ofstream& fout);
    void EditPipe();
    void addPipe();
    void printPipe();
    

    PipeLine();

    int getPipeID() const;
    int getDiameter() const;

    /*friend std::istream& operator >> (std::istream& in, PipeLine& pipe);
    friend std::ostream& operator << (std::ostream& out, const PipeLine& pipe);*/
};

