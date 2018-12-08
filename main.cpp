#include <iostream>
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

    std::map<std::string, std::vector<std::string>> innerStructure_;

public:
    Person() : 
        name_("DefaultName"),
        state_(false),
        vInts_{1,2,3} 
    {}

    void serialize() override
    {
        std::ofstream file("Object", std::ios::out);
        if (!file) 
        {
            std::cout<<"Can not open file\n";
        } 
        else 
        {
            file << "class:Person\n";
            saveName(file);
            saveState(file);
            savevInts(file);
            file.close();
        } 
    }

    void deserialize() override
    {
        std::ifstream file("Object", std::ios::in);
        if (!file) 
        {
            std::cout<<"can not open file";
        } 

        std::string line;
        std::vector<std::string> objectInTokens;

        while (getline(file, line))
        {
            std::istringstream iss(line);
            int position = 0;
            std::string property;
            for(std::string each; getline(iss, each, sep_); objectInTokens.push_back(each))
            {
                if (position == 0)
                {
                    property = each;
                    innerStructure_.insert(std::make_pair(property, std::vector<std::string>()));
                }   
                else
                {

                    auto dataIt = innerStructure_.find(property);
                    if (dataIt == innerStructure_.end())
                    {
                        std::cout << "No " << property << " found. Shouldn't happend!\n";
                        continue;
                    }
                    else
                    {
                        dataIt->second.push_back(each);
                    }
                }
                ++position;
            }
        }            

        validateObject();
        fulfillObject();
    }

private:
    void saveName(std::ostream& out)
    {
        out << "name_" << sep_ << name_ << '\n';
    }

    void saveState(std::ostream& out)
    {
        out << "state_" << sep_ << (state_ ? "1" : "0") << '\n';
    }

    void savevInts(std::ostream& out)
    {
        out << "vInts_";
        for(const auto& v : vInts_)
        {
            out << sep_ << v; 
        }
        out << '\n';
    }

    bool validateObject() override
    {
        // std::map<std::string, bool> checkList_ =
        // {
        //     {"name_", false}
        // };

        // for(const auto& v : innerStructure_)
        // {
        //     auto itAuto
        // }
        return true;
    }

    void fulfillObject() override
    {
        for(const auto& v : innerStructure_)
        {
            if (v.first == "name_")
            {
                name_ = v.second[0];
            }
        }
    }

    friend std::ostream& operator<<(std::ostream &out, Person& p);
};

std::ostream& operator<<(std::ostream &out, Person& p)
{
    out << "Name " <<p.name_ << '\n';
    out << "State " <<p.state_ << '\n';
    out << "vInts";
    for(const auto& v : p.vInts_)
        out << " " << v;
    std::cout << '\n';

    return out;
}

// void save()
// {
//        std::ofstream file("file", std::ios::out | std::ios::binary);
//     if (!file) {
//     std::cout<<"can not open file";
//     } else {
    
        
//     } 
// }
int main()
{
    Person p;
    p.serialize();

    Person b;
    b.deserialize();
    std::cout << b;


    return 0;

}