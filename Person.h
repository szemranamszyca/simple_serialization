#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

class Serializable
{
public:
    virtual void serialize() = 0;
    virtual void deserialize() = 0;
private:
    virtual bool validateObject() = 0;
    virtual void fulfillObject() = 0;
};


class Person : public Serializable
{
    char sep_ = ':';

    std::string name_;
    bool state_;
    std::vector<int> vInts_;
    std::vector<std::vector<double>> vvDouble_;

    std::map<std::string, std::vector<std::string>> innerStructure_;

public:
    Person();

    void serialize() override;
    void deserialize() override;
    void changeForTest();
private:
    void saveName(std::ostream& out);
    void saveState(std::ostream& out);
    void savevInts(std::ostream& out);
    void saveDouble(std::ostream& out);
    bool validateObject() override;
    void fulfillObject() override;

    friend std::ostream& operator<<(std::ostream &out, Person& p);
};
