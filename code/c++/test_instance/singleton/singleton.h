#include <string>
#include <memory>

class SingleTon {
public:
    static SingleTon& instance() {
        static SingleTon ins_;
        return ins_;
    }

    static bool init(std::string& name, std::string& university) {
        return instance().init_conf(name, university);    
    }
    
    bool init_conf(std::string& name, std::string& university) {
        this->name = name;
        this->university = university;
        return true;
    }

    std::string get_name() {
        return name;
    }

    std::string get_university() {
        return university;
    }

    void set_name(std::string& name) {
        this->name = name;
    }

    void set_university(std::string& university) {
        this->university = university;
    }

    SingleTon(const SingleTon& rhs) = delete;
    SingleTon& operator=(const SingleTon& rhs) = delete;
private:
    SingleTon() : name(), university() {}

private:
    std::string name;
    std::string university;
};
