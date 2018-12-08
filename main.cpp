#include <iostream>
#include <string>
#include <fstream>


class ISerializable
{
public:
    virtual std::ostream& operator<<(std::ostream&) = 0;
};


struct A
{
    int a;
    static void dawaj()
    {
        std::cout << "To jest obiekt A"  << '\n';
    }
};
struct Person
{
    std::string name_;
    friend std::ostream& operator<<(std::ostream &out, Person& p);

    void save()
    {
        std::ofstream file("object", std::ios::out);
        if (!file) {
            std::cout<<"can not open file";
        } else {
            file <<  name_;
            file.close();
        } 
    }

    static Person load()
    {
        std::ifstream file("object", std::ios::in);
        if (!file) {
            std::cout<<"can not open file";
        } 

        std::string line;
        while (std::getline(file, line))
        {
            // std::istringstream iss(line);
            // int a, b;
            // if (!(iss >> a >> b)) { break; } // error
            // std::cout << line << '\n';
            Person p;
            p.name_ = line;
            return p;
            // process pair (a,b)
        }

        return Person();

    }


};

std::ostream& operator<<(std::ostream &out, Person& p)  
{
    out << p.name_;
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
    p.name_ = "arek";
    p.save();
    // std::cout  << p;
    // p.load();
    Person b = Person::load();
    std::cout << b;


    A::dawaj();
    A a;
    a.dawaj();
    return 0;

}