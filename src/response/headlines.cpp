#include "headlines.hpp"

headlines::headlines() {
    this->contentType = "";
    this->contentEncoding = "";
    this->contentLenght = "";
    this->contentRange = "";
    intLenght = 0;
}

headlines::~headlines() {}


void            headlines::processingRange() {
    std::map<std::string, std::string>::iterator it = req.head.begin();
    std::string tmp;
    int pos;

    it = req.head.find("Accept-Ranges");
    if (it->second != "none") {
        contentRange = req.head["Accept-Ranges"];
        pos = contentRange.find("bytes");
        tmp = contentRange.substr(pos);
        if (std::string::npos != tmp.find("/")) {
            pos = tmp.find("/");
            tmp.erase(pos);
            if (tmp.find_first_not_of("1234567890"))
                _status.RangeNotSatisfiable();
        }
    }
}

void            headlines::searchKey(Request &requ) {
    req = requ;
    int pos;

    if (req.head.find("Accept-Encoding") != req.head.end()) {
        contentEncoding = req.head["Accept-Encoding"];
        if (std::string::npos != contentEncoding.find(",")) {
            pos = contentEncoding.find(",");
            contentEncoding.erase(pos);
        }
    }
    if (!req.body.empty()) {// if the request has body
        intLenght = strlen(req.body.c_str()); //todo: How I have to count lenght?
        std::stringstream ss;
        ss << intLenght;
        contentLenght = ss.str();
    }
    if (req.head.find("Accept") != req.head.end()) {
        contentType = req.head["Accept"];
        if (std::string::npos != contentType.find(",")) {
            pos = contentType.find(",");
            contentType.erase(pos);
        }
    }
    if (req.head.find("Accept-Ranges") != req.head.end())
        processingRange();
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

std::string     headlines::getRange() {
    return (this->contentRange);
}
