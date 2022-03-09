#include "headlines.hpp"

headlines::headlines() {
    this->contentType = "";
    this->contentEncoding = "";
    this->contentLenght = "";
    intLenght = 0;
}

headlines::~headlines() {}


void            headlines::searchKey(Request &req) {
    int pos;

    if (req.head.find("Accept-Encoding") != req.head.end()) {
        contentEncoding = req.head["Accept-Encoding"];
        pos = contentEncoding.find(",");
        contentEncoding.erase(pos);
    }
    if (!req.body.empty()) {// if the request has body
        intLenght = strlen(req.body.c_str()); //todo: How I have to count lenght?
        std::stringstream ss;
        ss << intLenght;
        contentLenght = ss.str();
        std::cout << "CL: " << contentLenght << std::endl;
    }
    if (req.head.find("Accept") != req.head.end()) {
        contentType = req.head["Accept"];
        pos = contentType.find(",");
        contentType.erase(pos);
    }
}

std::string     headlines::getType() {
    return (this->contentType);
}

std::string     headlines::getEncoding() {
    return (this->contentEncoding);
}

std::string     headlines::getLenght() {
    return (this->contentLenght);
}