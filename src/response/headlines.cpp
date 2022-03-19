#include "headlines.hpp"

headlines::headlines() {
    this->contentType = "";
    this->contentEncoding = "";
    this->contentLenght = "";
    this->contentRange = "";
    this->expires = "";
    intLenght = 0;
}

headlines::~headlines() {}

//const int       headlines::NotAcceptable::what() const throw() {
//    return (_status.setCode())
//}


std::string     headlines::sortData(std::string tmp) {
    int         pos;
    std::string final;
    std::string day, month, number, time, year;
    std::string probel = " ";

    tmp.append(" ");
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        day = tmp.substr(0, pos);
        tmp.erase(0, day.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        month = tmp.substr(0, pos);
        tmp.erase(0, month.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        number = tmp.substr(0, pos);
        tmp.erase(0, number.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        time = tmp.substr(0, pos);
        tmp.erase(0, time.size() + 1);
    }
    if (tmp.find(probel) != std::string::npos) {
        pos = tmp.find(probel);
        year = tmp.substr(0, pos - 1);
        tmp.erase(0, year.size());
    }
    final = day + ", " + number + " " + month + " " + year + " " + time + " GMT";
    return (final);
}

void            headlines::expiresTime() {
    time_t now = time(0);
    std::string tmp;

    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    tmp = dt;
    expires = sortData(tmp);
}


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

void            headlines::processingEncoding() {
    std::map<std::string, std::string>::iterator it = req.head.begin();
    int pos;

    it = req.head.find("Accept-Encoding");
    if (!it->second.empty()) {
        if (it->second.find("identity;q=0") || it->second.find("*;q=0"))
            _status.NotAcceptable();
        contentEncoding = req.head["Accept-Encoding"];
        if (std::string::npos != contentEncoding.find(",")) {
            pos = contentEncoding.find(",");
            contentEncoding.erase(pos);
        }
    }
    else
        contentEncoding = "identity";
}


void            headlines::searchKey(Request &requ) {
    req = requ;
    int pos;

    if (req.head.find("Accept-Encoding") != req.head.end())
        processingEncoding();
    if (!req.body.empty()) {// if the request has body
        intLenght = strlen(req.body.c_str());
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
    if (!contentType.empty()) {
        if (contentType == "image/png" || contentType == "image/jpeg" || \
            contentType == "image/gif" || contentType == "text/html" || contentType == "application/javascript")
                expiresTime();
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

std::string     headlines::getExpires() {
    return (this->expires);
}