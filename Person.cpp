#include <iostream>
#include "Person.h"

    Person::Person() : 
        name_("DefaultName"),
        state_(false),
        vInts_{1,2,3},
        vvDouble_{{1.23, 4.4524, 23.24}, {122, 312.313}}
    {}

    void Person::serialize()
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
            saveDouble(file);
            file.close();
        } 
    }

    void Person::deserialize()
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

    void Person::changeForTest()
    {
        name_ = "ChangedName";
        state_ = true;
        vInts_.push_back(2);
        vInts_.push_back(5);
        vvDouble_.push_back({2.432, 12.321});
    }

    void Person::saveName(std::ostream& out)
    {
        out << "name_" << sep_ << name_ << '\n';
    }

    void Person::saveState(std::ostream& out)
    {
        out << "state_" << sep_ << (state_ ? "1" : "0") << '\n';
    }

    void Person::savevInts(std::ostream& out)
    {
        out << "vInts_";
        for(const auto& v : vInts_)
        {
            out << sep_ << v; 
        }
        out << '\n';
    }

    void Person::saveDouble(std::ostream& out)
    {
        out << "vvDouble_";
        out << sep_ << vvDouble_.size();
        for(const auto& vecs : vvDouble_)
        {
            out << sep_ << vecs.size();
        }

        for(const auto& outervec : vvDouble_)
        {
            for(const auto& innervec : outervec)
            {
                out << sep_ << innervec;
            }
        }
        out << '\n';
    }

    bool Person::validateObject()
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

    void Person::fulfillObject()
    {
        for(const auto& v : innerStructure_)
        {
            if (v.first == "name_")
            {
                name_ = v.second[0];
            }

            if (v.first == "state_")
            {
                state_ = std::stoi(v.second[0]);
            }

            if (v.first == "vInts_")
            {
                vInts_.clear();
                for(const auto& value : v.second)
                    vInts_.push_back(std::stoi(value));
            }

            if (v.first == "vvDouble_")
            {
                vvDouble_.clear();
                int vecAmounts = std::stoi(v.second[0]);
                std::vector<int> vecSize;

                for(int i = 1; i < vecAmounts+1; ++i)
                {
                    vecSize.push_back(std::stoi(v.second[i]));
                }

                int valuesPos = vecAmounts+1;
                for(const auto& vec : vecSize)
                {
                    std::vector<double> toAppend;
                    for(int i = 0; i < vec; ++i)
                    {
                        toAppend.push_back(std::stod(v.second[valuesPos++]));
                    }
                    vvDouble_.push_back(toAppend);
                }
            }
        }
    }

std::ostream& operator<<(std::ostream &out, Person& p)
{
    out << "Name " <<p.name_ << '\n';
    out << "State " <<p.state_ << '\n';
    out << "vInts";
    for(const auto& v : p.vInts_)
        out << " " << v;
    out << '\n';

    out << "vvDouble" << '\n';
    for(const auto& vouter : p.vvDouble_)
    {
        for(const auto& vinner : vouter)
        {
            out << " " << vinner;
        }
        out << '\n';
    }
    out << '\n';

    return out;
}